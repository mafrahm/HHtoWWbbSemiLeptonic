#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
#include <math.h>


#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

HHtoWWbbSemiLeptonicHists::HHtoWWbbSemiLeptonicHists(Context & ctx, const string & dirname): Hists(ctx, dirname){

  // book all histograms here
  // jets

  N_jets = book<TH1F>("N_jets", "N_{jets}", 16, -0.5, 15.5);  
  N_PU = book<TH1F>("N_PU", "N_{PU}", 100, 0, 100);  
  pt_jets = book<TH1F>("pt_jets", "p_{T}^{jets} [GeV]", 40, 10, 250);
  pt_jet1 = book<TH1F>("pt_jet1", "p_{T}^{jet 1} [GeV]", 40, 10, 250);
  pt_jet2 = book<TH1F>("pt_jet2", "p_{T}^{jet 2} [GeV]", 40, 10, 250);
  pt_jet3 = book<TH1F>("pt_jet3", "p_{T}^{jet 3} [GeV]", 40, 10, 250);
  pt_jet4 = book<TH1F>("pt_jet4", "p_{T}^{jet 4} [GeV]", 40, 10, 250);
  eta_jets = book<TH1F>("eta_jets", "#eta^{jets}", 40, -2.5, 2.5);
  eta_jets_rebin = book<TH1F>("eta_jets_rebin", "#eta^{jets}", 60, -5.0, 5.0);
  eta_jet1 = book<TH1F>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  eta_jet2 = book<TH1F>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  eta_jet3 = book<TH1F>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  eta_jet4 = book<TH1F>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);


  //N_jets_vs_pt_jets = book<TH2F>("N_jets_vs_pt_jet", "N_{jets} vs p_{T}^{jets}", 21, -0.5, 20.5, 100, 10, 500);
  N_jet_vs_pt_jet = book<TH2F>("N_jet_vs_pt_jet", "N_{jet} vs p_{T}^{jet}", 11, -0.5, 10.5, 100, 10, 500);
  N_jet_vs_eta_jet = book<TH2F>("N_jet_vs_eta_jet", "N_{jet} vs #eta^{jet}", 11, -0.5, 10.5, 40, -2.5, 2.5);


  EMcharged_jet1 = book<TH1F>("EMcharged_jet1", "EMcharged_jet1", 100,0.0,1.0);
  EMneutral_jet1 = book<TH1F>("EMneutral_jet1", "EMneutral_jet1", 100,0.0,1.0);
  HADcharged_jet1 = book<TH1F>("HADcharged_jet1", "HADcharged_jet1", 100,0.0,1.0);
  HADneutral_jet1 = book<TH1F>("HADneutral_jet1", "HADneutral_jet1", 100,0.0,1.0);

  // bjets
  N_bJets_loose= book<TH1F>("N_bJets_loose", "N_{jets}^{CSV loose}", 11, -0.5, 10.5);
  N_bJets_med = book<TH1F>("N_bJets_med", "N_{jets}^{CSV medium}", 11, -0.5, 10.5);
  N_bJets_tight = book<TH1F>("N_bJets_tight", "N_{jets}^{CSV tight}", 11, -0.5, 10.5);
  N_deepjet_loose = book<TH1F>("N_deepjet_loose", "N_{jets}^{DeepJet loose}", 11, -0.5, 10.5);
  N_deepjet_med = book<TH1F>("N_deepjet_med", "N_{jets}^{DeepJet medium}", 11, -0.5, 10.5);
  N_deepjet_tight = book<TH1F>("N_deepjet_tight", "N_{jets}^{DeepJet tight}", 11, -0.5, 10.5);
  
  DeltaR_bjets = book<TH1F>("DeltaR_bjets", "#Delta R between the highest-pt bjets", 50, 0, 5);

  // leptons
  N_mu = book<TH1F>("N_mu", "N^{#mu}", 11, -0.5, 10.5);
  pt_mu = book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV]", 40, 0, 200);
  eta_mu = book<TH1F>("eta_mu", "#eta^{#mu}", 40, -2.5, 2.5);
  eta_mu_rebin = book<TH1F>("eta_mu_rebin", "#eta^{#mu}", 60, -5.0, 5.0);
  reliso_mu = book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  N_ele = book<TH1F>("N_ele", "N^{e}", 11, -0.5, 10.5);
  pt_ele = book<TH1F>("pt_ele", "p_{T}^{e} [GeV]", 40, 0, 200);
  eta_ele = book<TH1F>("eta_ele", "#eta^{e}", 50, -2.5, 2.5);
  eta_ele_rebin = book<TH1F>("eta_ele_rebin", "#eta^{e}", 40, -5.0, 5.0);
  reliso_ele = book<TH1F>("reliso_ele", "e rel. Iso", 40, 0, 0.5);

  N_lep = book<TH1F>("N_lep", "N^{lep}", 11, -0.5, 10.5);


  // primary vertices
  N_pv = book<TH1F>("N_pv", "N^{PV}", 50, 0, 50);

  // MET, ST
  MET = book<TH1F>("MET", "missing E_{T} [GeV]", 50, 0, 1500);
  MET_rebin = book<TH1F>("MET_rebin", "missing E_{T} [GeV]", 50, 0, 800);
  ST = book<TH1F>("ST", "S_{T} [GeV]", 50, 0, 3000);
  STjets = book<TH1F>("STjets", "S_{T}^{jets} [GeV]", 50, 0, 3000);
  STlep = book<TH1F>("STlep", "S_{T}^{lep} [GeV]", 50, 0, 1500);
 
  N_jets_vs_STjets = book<TH2F>("N_jets_vs_STjets", "N_{jets} vs S_{T}^{jets}", 21, -0.5, 20.5, 100, 0, 5000);


  // Mass reconstruction
  MHH = book<TH1F>("MHH", "M^{T,HH} [GeV]", 80, 150, 1000);
  CHI2 = book<TH1F>("CHI2", "#chi^{2}", 50, 0, 25);


  MH_bb = book<TH1F>("MH_bb", "M_{bb}^{#chi2} [GeV]", 100, 0, 500);
  CHI2_H_bb = book<TH1F>("CHI2_H_bb", "#chi_{H->bb}^{2}", 50, 0, 25);
  MH_WW = book<TH1F>("MH_WW", "M_{T,WW}^{#chi2} [GeV]", 100, 0, 500);
  CHI2_H_WW = book<TH1F>("CHI2_H_WW", "#chi_{H->WW}^{2}", 50, 0, 25);

  MH_bb_rebin = book<TH1F>("MH_bb_rebin", "M_{bb}^{#chi2} [GeV]", 40, 0, 200);
  MH_WW_rebin = book<TH1F>("MH_WW_rebin", "M_{T,WW}^{#chi2} [GeV]", 40, 0, 200);



  MH_bb_simple = book<TH1F>("MH_bb_simple", "M_{bb}^{highest-pt} [GeV]", 100, 0, 500);
  MH_bb_simple_rebin = book<TH1F>("MH_bb_simple_rebin", "M_{bb}^{highest-pt} [GeV]", 40, 0, 200);


  MH_WW_simple = book<TH1F>("MH_WW_simple", "M_{T,WW}^{highest-pt} [GeV]", 100, 0, 500);
  MH_WW_simple_rebin = book<TH1F>("MH_WW_simple_rebin", "M_{T,WW}^{highest-pt} [GeV]", 40, 0, 200);

  //vector<double> bins_Mbb = {0,65,75,85,90,95,100,105,110,115,120,125,130,135,140,150,170,200};
  //vector<double> bins_MWW = {0,80,100,120,140,160,180,200,220,245,270,300,340,380,440,500};

  vector<double> bins0_Mbb = {0,70,85,95,100,105,110,115,120,125,130,140,180,200};
  vector<double> bins0_MWW = {0,100,130,160,190,220,260,300,350,410,480,500};

  vector<double> bins_Mbb = {70,85,95,100,105,110,115,120,125,130,140,160,200};
  vector<double> bins_MWW = {100,130,160,190,220,260,300,350,410,500};

  MH_bb_limits = book<TH1F>("MH_bb_limits", "M_{bb}^{highest-pt} [GeV]", bins0_Mbb.size()-1,&bins0_Mbb[0]);
  MH_WW_limits = book<TH1F>("MH_WW_limits", "M_{T,WW}^{highest-pt} [GeV]", bins0_MWW.size()-1,&bins0_MWW[0]);


  Mbb_vs_MWW  = book<TH2F>("Mbb_vs_MWW", "M_{bb}^{#chi2} [GeV] vs M_{T,WW}^{#chi2} [GeV]", 40,0,200,40,0,500);
  Mbb_vs_MWW_limits  = book<TH2F>("Mbb_vs_MWW_limits", "M_{bb}^{#chi2} [GeV] vs M_{T,WW}^{#chi2} [GeV]", bins_Mbb.size()-1,&bins_Mbb[0], bins_MWW.size()-1,&bins_MWW[0]);
  Mbb_vs_MWW_limits1 = book<TH2F>("Mbb_vs_MWW_limits1", "M_{bb}^{highest-pt} [GeV] vs M_{T,WW}^{#chi2} [GeV]", bins_Mbb.size()-1,&bins_Mbb[0], bins_MWW.size()-1,&bins_MWW[0]);
  Mbb_vs_MWW_limits2 = book<TH2F>("Mbb_vs_MWW_limits2", "M_{bb}^{highest-pt} [GeV] vs M_{T,WW}^{highest-pt} [GeV]", bins_Mbb.size()-1,&bins_Mbb[0], bins_MWW.size()-1,&bins_MWW[0]);
  Mbb_vs_MWW_limits3 = book<TH2F>("Mbb_vs_MWW_limits3", "M_{bb}^{highest-pt} [GeV] vs M_{T,WW}^{lowest-pt} [GeV]", bins_Mbb.size()-1,&bins_Mbb[0], bins_MWW.size()-1,&bins_MWW[0]);

  sum_event_weights = book<TH1F>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);


  // for reconstructed HH Mass

  h_is_mHH_reconstructed = ctx.get_handle<bool>("is_mHH_reconstructed");
  h_mHH = ctx.get_handle<float>("mHH");
  h_chi2 = ctx.get_handle<float>("chi2");
  h_mH_bb = ctx.get_handle<float>("mH_bb");
  h_chi2_H_bb = ctx.get_handle<float>("chi2_H_bb");
  h_mH_WW = ctx.get_handle<float>("mH_WW");
  h_chi2_H_WW = ctx.get_handle<float>("chi2_H_WW");




}


void HHtoWWbbSemiLeptonicHists::fill(const Event & event){
  //cout << "Hists: fill" << endl;

  /*
  const auto & HHgenreco = event.get(h_HHgenreco);
  
  HHMatchedJets B1_match = HHgenreco.B1_jets();
  HHMatchedJets B2_match = HHgenreco.B2_jets();
  HHMatchedJets Q1_match = HHgenreco.Q1_jets();
  HHMatchedJets Q2_match = HHgenreco.Q2_jets();
  // for mass reco: index of true jet combination.
  int B1_index = B1_match.jet_index;
  int B2_index = B2_match.jet_index;
  int Q1_index = Q1_match.jet_index;
  int Q2_index = Q2_match.jet_index;
  */
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  sum_event_weights->Fill(1., weight);
  
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  N_jets->Fill(Njets, weight);
  if(!event.isRealData)  N_PU->Fill(event.genInfo->pileup_TrueNumInteractions(), weight);

  if(Njets>=1){
    eta_jet1->Fill(jets->at(0).eta(), weight);
    pt_jet1->Fill(jets->at(0).pt(), weight);
    EMcharged_jet1->Fill(jets->at(0).chargedEmEnergyFraction(), weight);
    EMneutral_jet1->Fill(jets->at(0).neutralEmEnergyFraction(), weight);
    HADcharged_jet1->Fill(jets->at(0).chargedHadronEnergyFraction(), weight);
    HADneutral_jet1->Fill(jets->at(0).neutralHadronEnergyFraction(), weight);
  }
  if(Njets>=2){
    eta_jet2->Fill(jets->at(1).eta(), weight);
    pt_jet2->Fill(jets->at(1).pt(), weight);
  }
  if(Njets>=3){
    eta_jet3->Fill(jets->at(2).eta(), weight);
    pt_jet3->Fill(jets->at(2).pt(), weight);
  }
  if(Njets>=4){
    eta_jet4->Fill(jets->at(3).eta(), weight);
    pt_jet4->Fill(jets->at(3).pt(), weight);
  }
  // pt_jets, eta_jets
  for(int i=0; i<Njets; i++)  {
    pt_jets->Fill(jets->at(i).pt(), weight);
    eta_jets->Fill(jets->at(i).eta(), weight);
    eta_jets_rebin->Fill(jets->at(i).eta(), weight);
    N_jet_vs_pt_jet->Fill(i, jets->at(i).pt(), weight);
    N_jet_vs_eta_jet->Fill(i, jets->at(i).eta(), weight);

  }


  // bjets
  int Nbjets_loose = 0, Nbjets_medium = 0, Nbjets_tight = 0;
  int Ndeepjet_loose = 0, Ndeepjet_med = 0, Ndeepjet_tight = 0;
  CSVBTag Btag_loose = CSVBTag(CSVBTag::WP_LOOSE);
  CSVBTag Btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);
  CSVBTag Btag_tight = CSVBTag(CSVBTag::WP_TIGHT);

  JetId DeepjetLoose = BTag(BTag::DEEPJET, BTag::WP_LOOSE);
  JetId DeepjetMedium = BTag(BTag::DEEPJET, BTag::WP_MEDIUM);
  JetId DeepjetTight = BTag(BTag::DEEPJET, BTag::WP_TIGHT);

  //vector<Jet>* bjets;
  Jet b1;
  Jet b2;
  LorentzVector H_bb;
  vector<LorentzVector> lightjets;
  for (unsigned int i =0; i<jets->size(); i++) {
    if(Btag_loose(jets->at(i),event))  Nbjets_loose++;
    if(Btag_medium(jets->at(i),event)) Nbjets_medium++;
    if(Btag_tight(jets->at(i),event))  Nbjets_tight++;
    if(DeepjetLoose(jets->at(i),event))  Ndeepjet_loose++;
    if(DeepjetMedium(jets->at(i),event)) {
      //bjets->push_back(jets->at(i));
      Ndeepjet_med++;
      if(Ndeepjet_med == 1) {b1 =jets->at(i); H_bb+=jets->at(i).v4();}
      if(Ndeepjet_med == 2) {b2 =jets->at(i); H_bb+=jets->at(i).v4();}
    }
    else {
      lightjets.push_back(jets->at(i).v4());
    }
    if(DeepjetTight(jets->at(i),event))  Ndeepjet_tight++;
  }

  N_bJets_loose->Fill(Nbjets_loose,weight);
  N_bJets_med->Fill(Nbjets_medium,weight);
  N_bJets_tight->Fill(Nbjets_tight,weight);
  N_deepjet_loose->Fill(Ndeepjet_loose,weight);
  N_deepjet_med->Fill(Ndeepjet_med,weight);
  N_deepjet_tight->Fill(Ndeepjet_tight,weight);

  // Delta R 
  if(Ndeepjet_med >= 2) {
    double dr = deltaR(b1, b2);
    DeltaR_bjets->Fill(dr,weight);
  }
  
  // Muons
  vector<Muon>* muons = event.muons;
  int Nmuons = event.muons->size();
  N_mu->Fill(Nmuons, weight);
  for (const Muon & thismu : *event.muons){
    pt_mu->Fill(thismu.pt(), weight);
    eta_mu->Fill(thismu.eta(), weight);
    eta_mu_rebin->Fill(thismu.eta(), weight);
    reliso_mu->Fill(thismu.relIso(), weight);
  }
  
  
  // Electrons
  vector<Electron>* electrons = event.electrons;
  int Nelectrons = event.electrons->size();
  N_ele->Fill(Nelectrons, weight);
  for (const Electron & thisele : *event.electrons){
    pt_ele->Fill(thisele.pt(), weight);
    eta_ele->Fill(thisele.eta(), weight);      
    eta_ele_rebin->Fill(thisele.eta(), weight);
    reliso_ele->Fill(thisele.relIso(), weight);
  }

  N_lep->Fill(Nelectrons+Nmuons, weight);

  // General
  int Npvs = event.pvs->size();
  N_pv->Fill(Npvs, weight);



  double met = event.met->pt();
  double st = 0., st_jets = 0., st_lep = 0.;
  for(const auto & jet : *jets)           st_jets += jet.pt();
  for(const auto & electron : *electrons) st_lep += electron.pt();
  for(const auto & muon : *muons)         st_lep += muon.pt();
  st = st_jets + st_lep + met;


  MET->Fill(met, weight);
  MET_rebin->Fill(met, weight);

  ST->Fill(st, weight);

  STjets->Fill(st_jets, weight);
  N_jets_vs_STjets->Fill(Njets, st_jets, weight);

  STlep->Fill(st_lep, weight);

  // reconstructed mass
  bool is_mHH_reconstructed = false;
  if(event.is_valid(h_is_mHH_reconstructed)){
    // cout << "Line: " << __LINE__ << endl;
    is_mHH_reconstructed = event.get(h_is_mHH_reconstructed);
  }
  // cout << "is_mHH_reconstructed: " << is_mHH_reconstructed << endl;


  // Higgs Masses simple
  double mbb = H_bb.M();
  if(Ndeepjet_med >= 2) {
    MH_bb_simple->Fill(mbb, weight);
    MH_bb_simple_rebin->Fill(mbb, weight);
    if(mbb < 190) MH_bb_limits->Fill(mbb, weight);
    else          MH_bb_limits->Fill(190., weight);

    if(is_mHH_reconstructed) Mbb_vs_MWW_limits1->Fill(mbb,event.get(h_mH_WW),weight);

  }
  if(lightjets.size() >= 2) {
    LorentzVector lepton;
    if(event.muons->size() == 1) lepton = event.muons->at(0).v4();
    else if(event.electrons->size() == 1) lepton = event.electrons->at(0).v4();
    else throw runtime_error("HHtoWWbbSemiLeptonicHists: no lepton or more than one lepton");  
    LorentzVector neutrino = event.met->v4();
    /*
    for(unsigned int i=0; i<lightjets.size(); i++){
      cout << "lightjet " << i << " pt: " << lightjets[i].Pt() << endl;
    }
    */
    LorentzVector q1_highPt = lightjets[0];
    LorentzVector q2_highPt = lightjets[1];
    LorentzVector q1_lowPt = lightjets[lightjets.size()-1];
    LorentzVector q2_lowPt = lightjets[lightjets.size()-2];

    double mtWW_high = TransverseMass4particles(q1_highPt,q2_highPt,lepton,neutrino);
    double mtWW_low = TransverseMass4particles(q1_lowPt,q2_lowPt,lepton,neutrino);

    MH_WW_simple->Fill(mtWW_high, weight);
    MH_WW_simple_rebin->Fill(mtWW_high, weight);
    if(mtWW_high < 490) MH_WW_limits->Fill(mtWW_high, weight);
    else           MH_WW_limits->Fill(490., weight);
    
    if(Ndeepjet_med >= 2) {
      Mbb_vs_MWW->Fill(mbb,mtWW_low,weight);

      // overflow bins (turns out they are not necessary for 2D Histograms)
      /*
      if(mbb<190 && mtWW <490) Mbb_vs_MWW_limits->Fill(mbb,mtWW,weight);
      else if(mbb>=190 && mtWW < 490) Mbb_vs_MWW_limits->Fill(190.,mtWW,weight);
      else if(mbb< 190 && mtWW >=490) Mbb_vs_MWW_limits->Fill(mbb,490.,weight);
      else                            Mbb_vs_MWW_limits->Fill(190.,490.,weight);
      */
      Mbb_vs_MWW_limits2->Fill(mbb,mtWW_high,weight);
      Mbb_vs_MWW_limits3->Fill(mbb,mtWW_low,weight);

	    
    }
  }


  if(is_mHH_reconstructed) {
    double chi2 = event.get(h_chi2);
    double mHH = event.get(h_mHH);

    CHI2->Fill(chi2, weight);
    MHH->Fill(mHH, weight);

    double chi2_H_bb = event.get(h_chi2_H_bb);
    double mH_bb = event.get(h_mH_bb);
    //cout << "mH_bb: " << mH_bb << endl;
   
    CHI2_H_bb->Fill(chi2_H_bb, weight);
    MH_bb->Fill(mH_bb, weight); 
    MH_bb_rebin->Fill(mH_bb, weight); 

    double chi2_H_WW = event.get(h_chi2_H_WW);
    double mH_WW = event.get(h_mH_WW);
    //cout << "mH_WW: " << mH_WW << endl;
   
    CHI2_H_WW->Fill(chi2_H_WW, weight);
    MH_WW->Fill(mH_WW, weight); 
    MH_WW_rebin->Fill(mH_WW, weight); 

    Mbb_vs_MWW_limits->Fill(mH_bb,mH_WW,weight);

    //Mbb_vs_MWW->Fill(mH_bb,mH_WW,weight);




  }




}


HHtoWWbbSemiLeptonicHists::~HHtoWWbbSemiLeptonicHists(){}
