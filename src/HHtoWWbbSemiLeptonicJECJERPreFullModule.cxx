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

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicSelections.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicModules.h"


#include <UHH2/HHtoWWbbSemiLeptonic/include/ModuleBASE.h>


using namespace std;
using namespace uhh2;
using namespace uhh2examples;

  
class HHtoWWbbSemiLeptonicJECJERPreFullModule: public ModuleBASE {
public:

  explicit HHtoWWbbSemiLeptonicJECJERPreFullModule(Context & ctx);
  virtual bool process(Event & event) override;
  void book_histograms(uhh2::Context&, vector<string> tags);
  void fill_histograms(uhh2::Event&, string tag, string region);

  void book_syst_histograms(uhh2::Context&, vector<string> syst_tags);
  void fill_syst_histograms(uhh2::Event&, string tag, string region, string systtag);

private:

  std::unique_ptr<CommonModules> common;

  unique_ptr<Hists> h_NNInputVariables_Inclusive, h_NNInputVariables_ech, h_NNInputVariables_much;

  std::unique_ptr<AnalysisModule> SF_muonIso, SF_muonID, SF_muonTrigger, SF_eleReco, SF_eleID, SF_eleTrigger, SF_btag, scale_variation_module;
  std::unique_ptr<Selection> njet3_sel, electron_sel, muon_sel, noElectron_sel, noMuon_sel, nbtag_medium_sel;
  std::unique_ptr<Selection> muon_trigger_sel1, muon_trigger_sel2, ele_trigger_sel1, ele_trigger_sel2, ele_trigger_sel3;
  ElectronId EleId;
  JetId Jet_ID;
  MuonId MuId;

  JetId Btag_loose;
  BTag::algo btag_algo;
  BTag::wp wp_btag_medium;

  uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
  uhh2::Event::Handle<float> h_mH_bb, h_mH_WW;

  // NN Stuff
  unique_ptr<Variables_NN> Variables_module;

  uhh2::Event::Handle<TString> h_region;
    
  bool forTraining;
  int trainingfraction;


  // Cleaner
  std::unique_ptr<AnalysisModule> cl_mu, cl_ele, cl_jets, cl_genjets;

  bool is_mc, do_permutations;
  bool is_signal;

  uhh2::Event::Handle<float> h_eventweight_lumi, h_eventweight_final;


  TString dataset_version;
  Year year;
};

void HHtoWWbbSemiLeptonicJECJERPreFullModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    cout << "booking histograms with tag " << tag << endl;
    string mytag = tag + "_ech" + "_General";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));

    mytag = tag + "_much" + "_General";
    book_HFolder(mytag, new HHtoWWbbSemiLeptonicHists(ctx,mytag));
  }
}




void HHtoWWbbSemiLeptonicJECJERPreFullModule::fill_histograms(uhh2::Event& event, string tag, string region){
  string mytag = tag + "_" + region + "_General";
  HFolder(mytag)->fill(event);
}






HHtoWWbbSemiLeptonicJECJERPreFullModule::HHtoWWbbSemiLeptonicJECJERPreFullModule(Context & ctx){
  
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  h_eventweight_lumi = ctx.declare_event_output<float>("eventweight_lumi");
  h_eventweight_final = ctx.declare_event_output<float>("eventweight_final");

  h_region = ctx.declare_event_output<TString>("region");
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);
  dataset_version = ctx.get("dataset_version");
  is_signal = dataset_version.Contains("HHtoWWbb");

  h_is_mHH_reconstructed = ctx.declare_event_output<bool>("is_mHH_reconstructed");
  h_mH_bb = ctx.declare_event_output<float>("mH_bb");
  h_mH_WW = ctx.declare_event_output<float>("mH_WW");


  // Object IDs
  //cout << "Year: " << year << endl;
  int jetpt = std::stoi(ctx.get("PTJet"));
  cout << "PTJet for Jet_ID is: " << jetpt << endl;

  JetId jet_pfid = JetPFID(JetPFID::WP_TIGHT_CHS);
  EleId = AndId<Electron>(ElectronID_Fall17_tight, PtEtaCut(28.0, 2.4));
  if (year == Year::is2016v2) MuId = AndId<Muon>(MuonID(Muon::Tight), PtEtaCut(25.0, 2.4), MuonIso(0.15));
  else                        MuId = AndId<Muon>(MuonID(Muon::CutBasedIdTight), PtEtaCut(25.0, 2.4), MuonID(Muon::PFIsoTight));
  Jet_ID = AndId<Jet>(jet_pfid, PtEtaCut(jetpt, 2.4));


  // BTagging
  btag_algo = BTag::DEEPJET;
  wp_btag_medium = BTag::WP_MEDIUM;
  JetId DeepjetMedium = BTag(btag_algo, wp_btag_medium);


  // Triggers
  if(year == Year::is2016v2 || year == Year::is2016v3){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoTkMu24_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele27_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon175_v*"));

  }
  else if(year == Year::is2017v1 || year == Year::is2017v2){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu27_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu27_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele35_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*")); // this trigger does not work for some 2017 Electron+Photon B events
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Photon200_v*"));
  }
  else if(year == Year::is2018){
    muon_trigger_sel1.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    muon_trigger_sel2.reset(new TriggerSelection("HLT_IsoMu24_v*"));
    ele_trigger_sel1.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
    ele_trigger_sel2.reset(new TriggerSelection("HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"));
    ele_trigger_sel3.reset(new TriggerSelection("HLT_Ele32_WPTight_Gsf_v*"));
  }


  // scale factors

  SF_muonID.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightID_DEN_genTracks_eta_pt", 0., "id", false, "nominal"));
  SF_muonIso.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonIso_EfficienciesAndSF_average_RunBtoH.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt", 0., "iso", false, "nominal"));
  //SF_muonTrigger.reset(new MuonTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins"), 0.);
  //SF_muonTrigger.reset(new MuonTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/LQTopLep/data", year));

  SF_eleReco.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root", 1, "reco", "nominal"));
  SF_eleID.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/2016LegacyReReco_ElectronTight_Fall17V2.root", 1, "id", "nominal"));
  //SF_eleTrigger.reset(new ElectronTriggerWeights(ctx, "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/LQTopLep/data", year));

  SF_btag.reset(new MCBTagScaleFactor(ctx, btag_algo, wp_btag_medium, "jets", "central")); // comment out when re-doing SF_btag



  // CommonModules
  common.reset(new CommonModules());
  common->switch_jetlepcleaner(true);
  common->set_electron_id(EleId);
  common->set_muon_id(MuId);
  common->set_jet_id(Jet_ID);
  common->switch_jetPtSorter();
  common->init(ctx);

  // Selections
  njet3_sel.reset(new NJetSelection(3, -1));
  muon_sel.reset(new NMuonSelection(1, 1));
  electron_sel.reset(new NElectronSelection(1, 1));
  noMuon_sel.reset(new NMuonSelection(0, 0));
  noElectron_sel.reset(new NElectronSelection(0, 0));
  nbtag_medium_sel.reset(new NJetSelection(1, -1, DeepjetMedium));


  // NN Stuff
  Variables_module.reset(new Variables_NN(ctx));

  // not used here
  forTraining = (ctx.get("RunFor") == "DNNTraining");
  trainingfraction = std::stoi(ctx.get("TrainingFraction"));


  // Book histograms
  vector<string> histogram_tags = {"1Lepton", "3Jets", "Trigger", "BTag"};

  h_NNInputVariables_Inclusive.reset(new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx, "NNInputVariables_Inclusive"));
  h_NNInputVariables_ech.reset(new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx, "NNInputVariables_ech"));
  h_NNInputVariables_much.reset(new HHtoWWbbSemiLeptonicMulticlassNNInputHists(ctx, "NNInputVariables_much"));

  // Cleaning
  MuonId cleanerId_mu = AndId<Muon>(MuonID(Muon::CutBasedIdTight), PtEtaCut(9999,0.1));
  ElectronId cleanerId_ele = AndId<Electron>(ElectronID_Fall17_tight, PtEtaCut(9999,0.1));
  JetId cleanerId_jets = PtEtaCut(9999,0.1);

  cl_mu.reset(new MuonCleaner(cleanerId_mu));
  cl_ele.reset(new ElectronCleaner(cleanerId_ele));
  cl_jets.reset(new JetCleaner(ctx, cleanerId_jets));
  cl_genjets.reset(new GenJetCleaner(ctx, 9999, 0.1));
}


bool HHtoWWbbSemiLeptonicJECJERPreFullModule::process(Event & event) {
  //cout << "JECJERPreFullModule: process" << endl;

  // dummys; they're not used anyways
  event.set(h_is_mHH_reconstructed, false);
  event.set(h_mH_bb, -1);
  event.set(h_mH_WW, -1);

  bool pass_common = common->process(event);
  if(!pass_common) return false;
  // fill_histograms(event,"Cleaner");
    

  // Splitting the dataset into a set for training and a set for stat. analysis -> for JEC/JER, do this in NNApplication!





  bool electronCategory = electron_sel->passes(event) && noMuon_sel->passes(event); // N_e == 1, N_mu == 0
  bool muonCategory = muon_sel->passes(event) && noElectron_sel->passes(event); // N_e == 0, N_mu == 1

  string region = "";
  if(electronCategory)  region = "ech";
  else if(muonCategory) region = "much";
  else return false;
  event.set(h_region, region);
  //fill_histograms(event, "1Lepton");
  if(!njet3_sel->passes(event)) return false;
  //fill_histograms(event, "3Jets");

  // eventweight based only on lumi
  double eventweight_lumi = event.weight;
  event.set(h_eventweight_lumi, eventweight_lumi);
    
  // Scale Factors
  SF_eleReco->process(event);
  SF_eleID->process(event);

  SF_muonID->process(event);
  SF_muonIso->process(event);



  // Trigger

  if(region == "much"){
    // Muon regions
    if(!(muon_trigger_sel1->passes(event) || muon_trigger_sel2->passes(event))) return false;

    //cout << "dataset_version: " << dataset_version << endl;
    // Reject electron and photon data
    if(!is_mc && !dataset_version.Contains("Muon")) return false;
  }
  else{
    // Electron regions
    if(!is_mc && (year == Year::is2017v1 || year == Year::is2017v2) && event.run < 299368) { // Trigger 2 does not work here
      if(dataset_version.Contains("Electron")){
	if(!(ele_trigger_sel1->passes(event))) return false;
      }
      else if(dataset_version.Contains("Photon")){
	// Automatically discards photon data in 2018
	if(!(!ele_trigger_sel1->passes(event) && ele_trigger_sel3->passes(event))) return false;
      }
    }
    else if(!is_mc){
      if(dataset_version.Contains("Electron")){
	if(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event))) return false;
      }
      else if(dataset_version.Contains("Photon")){
	// Automatically discards photon data in 2018
	if(!(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event)) && ele_trigger_sel3->passes(event))) return false;
      }
      // Reject muon data
      else return false;
    }
    else{
      // Just a simple OR for MC
      if(!(ele_trigger_sel1->passes(event) || ele_trigger_sel2->passes(event) || ele_trigger_sel3->passes(event))) return false;
    }
  }
  // fill_histograms(event, "Trigger", region);


  SF_btag->process(event);
  if(!nbtag_medium_sel->passes(event)) return false;
  //fill_histograms(event,"BTag", region);
    
  // weight after applying all SF's
  event.set(h_eventweight_final, event.weight);
  event.set(h_region, region);



  Variables_module->process(event);

  h_NNInputVariables_Inclusive->fill(event);
  if(region=="ech")       h_NNInputVariables_ech->fill(event);
  else if(region=="much") h_NNInputVariables_much->fill(event);

  // Cleaning: 
  // at this point, we have saved (hopefully) everything important in handles
  // so just get rid of all the collections

  cl_mu->process(event);
  cl_ele->process(event);
  cl_jets->process(event);
  cl_genjets->process(event);

  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HHtoWWbbSemiLeptonicJECJERPreFullModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HHtoWWbbSemiLeptonicJECJERPreFullModule)
