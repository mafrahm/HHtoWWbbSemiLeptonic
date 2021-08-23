#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/AdditionalSelections.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/Utils.h"

#include "UHH2/common/include/NeuralNetworkBase.hpp"
#include "UHH2/HHtoWWbbSemiLeptonic/include/NeuralNetworkModule.h"

// my own classes
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicSelections.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMatchedHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"


#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHPDFHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHMassReconstruction.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
//#include "UHH2/LQTopLep/include/LQTopLepModules.h" // for trigger SF's

#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h>



using namespace std;
using namespace uhh2;
using namespace uhh2examples;

  
class HHtoWWbbSemiLeptonicNNApplication: public ModuleBASE {
public:

  explicit HHtoWWbbSemiLeptonicNNApplication(Context & ctx);
  virtual bool process(Event & event) override;
  void book_histograms(uhh2::Context&, vector<string> tags);
  void fill_histograms(uhh2::Event&, string tag, string region);

  void book_syst_histograms(uhh2::Context&, vector<string> syst_tags);
  void book_pdf_histograms(uhh2::Context&, vector<string> syst_tags);
  void fill_syst_histograms(uhh2::Event&, string tag, string region, string systtag);

private:

  std::unique_ptr<CommonModules> common;

  unique_ptr<Hists> h_btageff, h_MulticlassNN_output, h_NNInputVariables;

  std::unique_ptr<Selection> njet4_sel;


  // NN Stuff
  unique_ptr<Variables_NN> Variables_module;
  Event::Handle<vector<tensorflow::Tensor>> h_NNoutput;
  Event::Handle<double> h_NNoutput0, h_NNoutput1, h_NNoutput2, h_NNoutput3, h_NNoutput4;
  unique_ptr<NeuralNetworkModule> NNModule;
  int NN_classes;

  uhh2::Event::Handle<TString> h_region;



  bool is_mc, do_permutations;
  bool is_signal;
  string s_permutation;

  uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;


  TString dataset_version;
  Year year;

  // for Systematics
  vector<TString> handlenames, systnames, systshift, systshift_scale;
  vector<string> histogramtags_syst, histogramtags_scale, histogramtags_pdf;
  vector<uhh2::Event::Handle<float>> systweight_handles, systweight_scale_handles, scalefactor_handles;

};

void HHtoWWbbSemiLeptonicNNApplication::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    cout << "booking histograms with tag " << tag << endl;
    string mytag;
    //mytag = tag + "_ech" + "_General";
    //book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
    mytag = tag + "_ech" + "_NNInput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx,mytag));
    mytag = tag + "_ech" + "_NNOutput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx,mytag));

    //mytag = tag + "_much" + "_General";
    //book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
    mytag = tag + "_much" + "_NNInput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx,mytag));
    mytag = tag + "_much" + "_NNOutput";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx,mytag));
  }
}




void HHtoWWbbSemiLeptonicNNApplication::fill_histograms(uhh2::Event& event, string tag, string region){
  string mytag;
  //string mytag = tag + "_" + region + "_General";
  //HFolder(mytag)->fill(event);
  mytag = tag + "_" + region + "_NNInput";
  HFolder(mytag)->fill(event);
  mytag = tag + "_" + region + "_NNOutput";
  HFolder(mytag)->fill(event);
}


void HHtoWWbbSemiLeptonicNNApplication::book_syst_histograms(uhh2::Context& ctx, vector<string> syst_tags){
  vector<string> tags = {"DNNoutput0", "DNNoutput1", "DNNoutput2", "DNNoutput3", "DNNoutput4"};
  for(const auto & tag : tags){
    cout << "booking syst histograms with tag " << tag << endl;
    for(const auto & systtag : syst_tags){
      cout << " booking histograms with systtag " << systtag << endl;
      string mytag = "much_" + tag + "_" + systtag;
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx,mytag));
      mytag = "ech_" + tag + "_" + systtag;
      book_HFolder(mytag, new HHtoWWbbSemiLeptonicMulticlassNNHists(ctx,mytag));
    }
  }
}


void HHtoWWbbSemiLeptonicNNApplication::book_pdf_histograms(uhh2::Context& ctx, vector<string> syst_tags){
  vector<string> tags = {"DNNoutput0", "DNNoutput1", "DNNoutput2", "DNNoutput3", "DNNoutput4"};
  for(const auto & tag : tags){
    cout << "booking pdf histograms with tag " << tag << endl;
    for(const auto & systtag : syst_tags){
      cout << " booking histograms with systtag " << systtag << endl;
      string mytag = "much_" + tag + "_" + systtag;
      book_HFolder(mytag, new HHPDFHists(ctx,mytag));
      mytag = "ech_" + tag + "_" + systtag;
      book_HFolder(mytag, new HHPDFHists(ctx,mytag));

    }
  }
}


void HHtoWWbbSemiLeptonicNNApplication::fill_syst_histograms(uhh2::Event& event, string tag, string region, string systtag){
  string  mytag = region + "_" + tag + "_" + systtag;
  HFolder(mytag)->fill(event);
}





HHtoWWbbSemiLeptonicNNApplication::HHtoWWbbSemiLeptonicNNApplication(Context & ctx){
  
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  h_eventweight_lumi = ctx.get_handle<float>("eventweight_lumi");
  h_eventweight_final = ctx.get_handle<float>("eventweight_final");

  h_region = ctx.get_handle<TString>("region");
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);
  dataset_version = ctx.get("dataset_version");
  is_signal = dataset_version.Contains("HHtoWWbb");


  // Selections
  //njet4_sel.reset(new NJetSelection(4, -1));


  // NN Stuff
  Variables_module.reset(new Variables_NN(ctx));
  h_NNoutput = ctx.get_handle<vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  h_NNoutput3 = ctx.declare_event_output<double>("NNoutput3");
  h_NNoutput4 = ctx.declare_event_output<double>("NNoutput4");

  string data_dir = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data//";
  string NNmodel = ctx.get("NNModel");
  NNModule.reset(new NeuralNetworkModule(ctx, data_dir+"NNModel/"+NNmodel+"/model.pb", data_dir+"NNModel/"+NNmodel+"/model.config.pbtxt"));
  NN_classes = stoi(ctx.get("NN_Classes"));

  // Book histograms
  vector<string> histogram_tags = {"Finalselection", "DNNoutput0", "DNNoutput1", "DNNoutput2", "DNNoutput3", "DNNoutput4"};
  book_histograms(ctx, histogram_tags);

  //h_xx = ctx.get_handle<float>("xx");

  
  histogramtags_syst = {};
  histogramtags_syst.emplace_back("nominal");

  // for Systematics

  // Declare all systematics names in consistent ordering
  systnames = {"muid", "pu", "eleid", "elereco",/* "eletrigger",*/ "muiso",/* "mutrigger",*/ "btag_bc", "btag_udsg"};

  // !!! check if all these handles exist
  handlenames = {"weight_sfmu_id", "weight_pu", "weight_sfelec_id", "weight_sfelec_reco",/* "weight_sfelec_trigger",*/ "weight_sfmu_iso",/* "weight_sfmu_trigger",*/ "weight_btag" , "weight_btag"};
  systshift = {"up", "down"};
  if(systnames.size() != handlenames.size()) throw runtime_error("In HHtoWWbbSemiLeptonicNNApplication.cxx: Length of systnames and handlenames is not equal.");

  histogramtags_syst = {};
  histogramtags_syst.emplace_back("nominal");

  for(unsigned int i=0; i<systnames.size(); i++){
    for(unsigned int j=0; j<systshift.size(); j++){

      TString handlename = handlenames[i] + "_" + systshift[j];
      TString sf_name = handlenames[i];

      // PU doesn't exist in data (grr!!). Give it a dummy and never use it again. Doesn't matter on data anyway.
      if(systnames[i] == "pu" && !is_mc){
	handlename = "eventweight_final";
	sf_name = "eventweight_final";
      }

      // B-tagging uncertainties require a special treatment
      if(systnames[i] == "btag_bc"){
	handlename = handlenames[i] + "_bc_" + systshift[j];
      }
      else if(systnames[i] == "btag_udsg"){
	handlename = handlenames[i] + "_udsg_" + systshift[j];
      }

      uhh2::Event::Handle<float> handle1 = ctx.declare_event_output<float>((string)handlename);
      uhh2::Event::Handle<float> handle2 = ctx.declare_event_output<float>((string)sf_name);
      systweight_handles.emplace_back(handle1);
      scalefactor_handles.emplace_back(handle2);

      TString histname = systnames[i] + "_" + systshift[j];
      histogramtags_syst.emplace_back(histname);
    }
  }
  
  //book all the histogram folders 
  book_syst_histograms(ctx, histogramtags_syst);
  
  // Scale variation
  histogramtags_scale = {};
  systshift_scale = {"upup", "upnone", "noneup", "nonedown", "downnone", "downdown"};
  for(unsigned int i=0; i<systshift_scale.size(); i++){
    TString handlename = "weight_murmuf_" + systshift_scale[i];

    uhh2::Event::Handle<float> handle = ctx.declare_event_output<float>((string)handlename);
    systweight_scale_handles.emplace_back(handle);

    TString histname = "scale_" + systshift_scale[i];
    histogramtags_scale.emplace_back(histname);
  }

  book_syst_histograms(ctx, histogramtags_scale);




  // Separately book one set of PDF hists (each contains the 100 variations for M_Tprime)
  cout << "Line: " << __LINE__ << endl;
  book_pdf_histograms(ctx, {"pdf"});

}


bool HHtoWWbbSemiLeptonicNNApplication::process(Event & event) {
  //cout << "NNApplication: process" << endl;



  //double eventweight_lumi = event.weight;
    

  string region = (string)event.get(h_region);

  // just for running the NJets>=4 category (testing purpose only)
  //if(!njet4_sel->passes(event)) return false;


  //Variables_module->process(event); // (hopefully) not needed anymore :)
  NNModule->process(event);


  vector<tensorflow::Tensor> NNoutputs = NNModule->GetOutputs();
  event.set(h_NNoutput, NNoutputs);

  double out0 =  (double)(NNoutputs[0].tensor<float, 2>()(0,0));
  double out1 =  (double)(NNoutputs[0].tensor<float, 2>()(0,1));
  double out2 =  (double)(NNoutputs[0].tensor<float, 2>()(0,2));
  double out3 =  (double)(NNoutputs[0].tensor<float, 2>()(0,3));
  double out4 =  (double)(NNoutputs[0].tensor<float, 2>()(0,4));
  //double out5 =  (double)(NNoutputs[0].tensor<float, 2>()(0,5));

  vector<double> out_event = {out0,out1,out2,out3,out4};
  if(NN_classes>5)runtime_error("In HHtoWWbbSemiLeptonicNNApplication: max. 5 NN categories are implemented ATM");
  /*
  cout << "out0= " << out0 << endl;
  cout << "out1= " << out1 << endl;
  cout << "out2= " << out2 << endl;
  cout << "out3= " << out3 << endl;
  cout << "out4= " << out4 << endl;
  */
  event.set(h_NNoutput0, out0);
  event.set(h_NNoutput1, out1);
  event.set(h_NNoutput2, out2);
  event.set(h_NNoutput3, out3);
  event.set(h_NNoutput4, out4);
  fill_histograms(event, "Finalselection", region);

  // Categorization using NN output
  double max_score = 0.0;
  string max_score_tag = "";
  for (int i = 0; i < NN_classes; i++ ) {
    if ( out_event[i] > max_score) {
    max_score = out_event[i];
    max_score_tag = std::to_string(i);
    }
  }
  string DNN_hist_tag  = "DNNoutput"+max_score_tag;
  fill_histograms(event, DNN_hist_tag, region);


  // !!! for Systematics

  
  // Read out nominal eventweight
  float weight_nominal = event.get(h_eventweight_final);

  // Fill histograms once with nominal weights
  event.weight = weight_nominal;

  fill_syst_histograms(event, DNN_hist_tag, region, "nominal");

  // Loop over easy systematics
  
  for(unsigned int i=0; i<systnames.size(); i++){    
    for(unsigned int j=0; j<systshift.size(); j++){

      int idx = 2*i + j;
      float systweight = event.get(systweight_handles[idx]);
      float sfweight = event.get(scalefactor_handles[idx]);
      event.weight = weight_nominal * systweight / sfweight;
      TString tag = systnames[i] + "_" + systshift[j];

      fill_syst_histograms(event, DNN_hist_tag, region, (string)tag);
    }
  }

  // Loop over scale systematics
  for(unsigned int j=0; j<systshift_scale.size(); j++){

    float systweight = event.get(systweight_scale_handles[j]);
    event.weight = weight_nominal * systweight;

    TString tag = "scale_" + systshift_scale[j];      
    fill_syst_histograms(event, DNN_hist_tag, region, (string)tag);
  }

  // Fill PDF histograms
  event.weight = weight_nominal;

  fill_syst_histograms(event, DNN_hist_tag, region, "pdf");



  // event.set(h_eventweight_final, event.weight);
  // event.set(h_region, region);

  // we don't need the AnalysisTree anymore, just return false
  return false;
  //return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HHtoWWbbSemiLeptonicNNApplication is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicNNApplication)
