#include <iostream>
#include <memory>


//#include <UHH2/SingleTth/include/ModuleBASE.h>
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
//hists
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/EventHists.h"
//selections
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/NSelections.h"
//IDs
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/MuonIds.h"

#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/PDFWeights.h"

#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h>


using namespace std;
using namespace uhh2;
//using namespace uhh2examples;

class CountEventsHists: public uhh2::Hists {
public: 
  CountEventsHists(uhh2::Context & ctx, const std::string & dirname);
  virtual void fill(const uhh2::Event & ev) override;
  virtual ~CountEventsHists();
  
protected:
  bool debug = false;

  TH1F *nominal;

  // PDF
  bool is_mc, take_ntupleweights;
  TString m_oname;
  std::unique_ptr<PDFWeights> m_pdfweights;
  vector<TString> histo_names;

  // Scale
  uhh2::Event::Handle<float> weight_murmuf_upup, weight_murmuf_upnone, weight_murmuf_noneup, weight_murmuf_downdown, weight_murmuf_downnone, weight_murmuf_nonedown;//, weight_murmuf_downup, weight_murmuf_updown;

  TH1F *MuR_up, *MuR_down, *MuF_up, *MuF_down;
  TH1F *murmuf_upup, *murmuf_upnone, *murmuf_noneup, *murmuf_downdown, *murmuf_downnone, *murmuf_nonedown, *murmuf_downup, *murmuf_updown;
  
};

CountEventsHists::CountEventsHists(Context & ctx, const string & dirname): Hists(ctx, dirname) {
  nominal = book<TH1F>("nominal", "nominal", 1,0.5,1.5);


  // PDF
  is_mc = ctx.get("dataset_type") == "MC";
  m_oname = ctx.get("dataset_version");
  cout << "m_oname: " << m_oname << endl;
  TString m_pdfname = "NNPDF30_lo_as_0130";
  Year year = extract_year(ctx);
  
  // take_ntupleweights not for QCD?
  if(year == Year::is2017v1 || year == Year::is2017v2){
    take_ntupleweights = !(m_oname.Contains("QCD") /*|| m_oname.Contains("HH")*/);
  }
  else if (year == Year::is2018){
    take_ntupleweights = !(m_oname.Contains("QCD") /*|| m_oname.Contains("HH")*/ || m_oname.Contains("DibosonNLO"));
  }
  else{
    take_ntupleweights = !(m_oname.Contains("QCD") || m_oname.Contains("ST_tW") || m_oname.Contains("DibosonNLO_ZZ_2L2Nu_2016v3")); // what's up with these specifications?
  }

  cout << m_pdfname << endl;
  if(is_mc && !take_ntupleweights){
    m_pdfweights.reset(new PDFWeights(m_pdfname));
  }


  for(int i=0; i<100; i++){
    TString name = "PDF_" + to_string(i+1);
    histo_names.emplace_back(name);
    book<TH1F>(name, name, 1,0.5,1.5);
  }


  // Scale
  weight_murmuf_upup = ctx.get_handle<float>("weight_murmuf_upup");
  weight_murmuf_upnone = ctx.get_handle<float>("weight_murmuf_upnone");
  weight_murmuf_noneup = ctx.get_handle<float>("weight_murmuf_noneup");
  weight_murmuf_downdown = ctx.get_handle<float>("weight_murmuf_downdown");
  weight_murmuf_downnone = ctx.get_handle<float>("weight_murmuf_downnone");
  weight_murmuf_nonedown = ctx.get_handle<float>("weight_murmuf_nonedown");
  //weight_murmuf_downup = ctx.get_handle<float>("weight_murmuf_downup");
  //weight_murmuf_updown = ctx.get_handle<float>("weight_murmuf_updown");

  MuR_up   = book<TH1F>("MuR_up"  , "MuR_up"  , 1,0.5,1.5);
  MuR_down = book<TH1F>("MuR_down", "MuR_down", 1,0.5,1.5);
  MuF_up   = book<TH1F>("MuF_up"  , "MuF_up"  , 1,0.5,1.5);
  MuF_down = book<TH1F>("MuF_down", "MuF_down", 1,0.5,1.5);


  murmuf_upup = book<TH1F>("murmuf_upup", "murmuf_upup", 1,0.5,1.5);
  murmuf_upnone = book<TH1F>("murmuf_upnone", "murmuf_upnone", 1,0.5,1.5);
  murmuf_noneup = book<TH1F>("murmuf_noneup", "murmuf_noneup", 1,0.5,1.5);
  murmuf_downdown = book<TH1F>("murmuf_downdown", "murmuf_downdown", 1,0.5,1.5);
  murmuf_downnone = book<TH1F>("murmuf_downnone", "murmuf_downnone", 1,0.5,1.5);
  murmuf_nonedown = book<TH1F>("murmuf_nonedown", "murmuf_nonedown", 1,0.5,1.5);
  murmuf_downup = book<TH1F>("murmuf_downup", "murmuf_downup", 1,0.5,1.5);
  murmuf_updown = book<TH1F>("murmuf_updown", "murmuf_updown", 1,0.5,1.5);


  //PDF_up   = book<TH1F>("PDF_up"  , "PDF_up"  , 1,0.5,1.5);
  //PDF_down = book<TH1F>("PDF_down", "PDF_down", 1,0.5,1.5);
}

void CountEventsHists::fill(const Event & event) {
  double weight_nominal = event.weight;
  nominal->Fill(1., weight_nominal);
  int N_systweights = event.genInfo->systweights().size();


     if(N_systweights < 100 && take_ntupleweights) {
       cout << "Number of systweights:"  << N_systweights << endl;
       throw runtime_error("In CountEventsModule.cxx: Systweights in event.genInfo() is empty but ntupleweights shall be taken. Is this correct? In this case add exception to take_ntupleweights.");
     }
     if(N_systweights > 110 && (!take_ntupleweights)) {
       cout << "Number of systweights:"  << N_systweights << endl;
       // Diboson has events with >110 and events with <100 systweights :/
       if(!m_oname.Contains("DibosonNLO_ZZ_2L2Nu_2016v3")) throw runtime_error("In CountEventModule.cxx: Systweights in event.genInfo() is NOT empty but take_ntupleweights is set to 'false'. Is this correct? In this case Thomas says the genInfo weight should be used. Add this sample to take_ntupleweights");
     }

  // PDF
  if(take_ntupleweights) {
    for(int i=0; i<100; i++){
      // what's up with the (i+9) ?
      double pdf_weight = event.genInfo->systweights().at(i+9);
      double fillweight = weight_nominal * pdf_weight/event.genInfo->originalXWGTUP();
      if(debug) cout << "pdf_weight " << i << ": " << pdf_weight << endl;
      if(debug) cout << "originalXWGTUP(): " << event.genInfo->originalXWGTUP() << endl;

      TString name = histo_names[i];
      hist(name)->Fill(1., fillweight);
    }
  }
  else{
    std::vector<double> weights = m_pdfweights->GetWeightList(event);
    for(int i=0; i<100; i++){
      double fillweight = weight_nominal * weights[i];
      TString name = histo_names[i];
      hist(name)->Fill(1., fillweight);
    }
  }

  // Scale
  if(!m_oname.Contains("QCD")) {

    /*
    double weight_MuR_up = event.genInfo->systweights().at(3);
    double weight_MuR_down = event.genInfo->systweights().at(6);
    double weight_MuF_up = event.genInfo->systweights().at(1);
    double weight_MuF_down = event.genInfo->systweights().at(2);
    */

    float w_murmuf_upup = event.get(weight_murmuf_upup);
    float w_murmuf_noneup = event.get(weight_murmuf_noneup);
    float w_murmuf_upnone = event.get(weight_murmuf_upnone);
    float w_murmuf_downdown = event.get(weight_murmuf_downdown);
    float w_murmuf_nonedown = event.get(weight_murmuf_nonedown);
    float w_murmuf_downnone = event.get(weight_murmuf_downnone);



    if(debug){
      cout << "w_murmuf_upnone: " << w_murmuf_upnone << endl; 
      cout << "w_murmuf_downnone: " << w_murmuf_downnone << endl; 
      cout << "w_murmuf_noneup: " << w_murmuf_noneup << endl; 
      cout << "w_murmuf_nonedown: " << w_murmuf_nonedown << endl; 
      cout << "w_murmuf_upup: " << w_murmuf_upup << endl;
      cout << "w_murmuf_downdown: " << w_murmuf_downdown << endl;
    }
    MuR_up->Fill(1., weight_nominal*w_murmuf_upnone);
    MuR_down->Fill(1., weight_nominal*w_murmuf_downnone);
    MuF_up->Fill(1., weight_nominal*w_murmuf_noneup);
    MuF_down->Fill(1., weight_nominal*w_murmuf_nonedown);

    murmuf_upup->Fill(1., weight_nominal*w_murmuf_upup);
    murmuf_upnone->Fill(1., weight_nominal*w_murmuf_upnone);
    murmuf_noneup->Fill(1., weight_nominal*w_murmuf_noneup);
    murmuf_downdown->Fill(1., weight_nominal*w_murmuf_downdown);
    murmuf_downnone->Fill(1., weight_nominal*w_murmuf_downnone);
    murmuf_nonedown->Fill(1., weight_nominal*w_murmuf_nonedown);

    if(N_systweights>7){
      float w_murmuf_updown = event.genInfo->systweights().at(5);
      float w_murmuf_downup = event.genInfo->systweights().at(7);
      if(debug) cout << "w_murmuf_updown: " << w_murmuf_updown << endl;
      if(debug) cout << "w_murmuf_downup: " << w_murmuf_downup << endl;
      murmuf_downup->Fill(1., weight_nominal*w_murmuf_downup);
      murmuf_updown->Fill(1., weight_nominal*w_murmuf_updown);
    }
}
}

CountEventsHists::~CountEventsHists(){}

class CountEventsModule: public ModuleBASE {
public:
    
  explicit CountEventsModule(Context & ctx);
  virtual bool process(Event & event) override;

  
private:
  std::unique_ptr<CommonModules> common;
  unique_ptr<Hists> h_Hists;
  std::unique_ptr<AnalysisModule> scale_variation_module;

};


CountEventsModule::CountEventsModule(Context & ctx){
    
  cout << "Hello World from CoutingEventsModule!" << endl;
    
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }


  // Common Modules
  common.reset(new CommonModules());
  common->init(ctx);


  h_Hists.reset(new CountEventsHists(ctx, "Hists"));
  scale_variation_module.reset(new MCScaleVariation(ctx));

}



bool CountEventsModule::process(Event & event) {

  bool pass_common = common->process(event);
  if(!pass_common) return false;
  scale_variation_module->process(event);

  h_Hists->fill(event);

  return false;
}

  
UHH2_REGISTER_ANALYSIS_MODULE(CountEventsModule)
