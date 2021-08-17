#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicGenHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include <math.h>

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

HHtoWWbbSemiLeptonicGenHists::HHtoWWbbSemiLeptonicGenHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // get GenObjects
  h_HHgenobjects = ctx.get_handle<HHGenObjects>("HHgenobjects");

  // book all histograms here


  // Higgs
  book<TH1F>("pt_H_W", "p_{T}^{Higgs 1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_H_b", "p_{T}^{Higgs 2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_H", "p_{T}^{Higgs} [GeV]", 50, 0, 500);
  book<TH1F>("eta_H", "#eta^{Higgs} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR HH", "#Delta R between two H's", 50, 0, 5);
  book<TH1F>("deltaPhi HH", "#Delta #Phi between two H's", 50, -3.2, 3.2);
  book<TH1F>("deltaEta HH", "#Delta #eta between two H's", 50, -5, 5);



  book<TH1F>("M_HH", "M_{HH} [GeV]", 50, 200, 800);
  book<TH1F>("M_H_W", "M_{Higgs} [GeV] decaying to W", 50, 124.95, 125.05);
  book<TH1F>("M_H_W_reco", "M_{Higgs} [GeV] decaying to W (reco)", 50, 124.95, 125.05);
  book<TH1F>("M_H_b", "M_{Higgs} [GeV] decaying to b", 50, 124.95, 125.05);
  book<TH1F>("M_H_b_reco", "M_{Higgs} [GeV] decaying to b (reco)", 50, 124.95, 125.05);

  M_HH_vs_pt_l = book<TH2F>("M_HH_vs_pt_l", "M_{HH} [GeV] vs p_{T}^{l}", 50,200,600,40,0,200);
  pt_H_W_vs_pt_H_b = book<TH2F>("pt_H_W_vs_pt_H_b", "p_{T}^{H_W} [GeV] vs p_{T}^{H_b} [GeV]", 50, 0, 500, 50, 0, 500);
  M_H_W_vs_M_H_b = book<TH2F>("M_H_W_vs_M_H_b", "M_{H_W} [GeV] vs M_{H_b} [GeV]", 50, 124.8, 125.2, 50, 124.8, 125.2);
  deltaR_HH_vs_pt_H_W = book<TH2F>("deltaR_HH_vs_pt_H_W", "#Delta R_{HH} vs p_{T}^{H_W} [GeV]", 50, 0, 5, 50, 0, 500);

  // W's
  book<TH1F>("pt_WLep", "p_{T}^{WLep} [GeV]", 50, 0, 500);
  book<TH1F>("pt_WHad", "p_{T}^{WHad} [GeV]", 50, 0, 500);
  book<TH1F>("pt_W", "p_{T}^{W} [GeV]", 50, 0, 500);
  book<TH1F>("eta_W", "#eta^{W} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR WW", "#Delta R between two W's", 50, 0, 5);
  book<TH1F>("deltaPhi WW", "#Delta #Phi between two W's", 50, 0, 3.2);
  book<TH1F>("deltaEta WW", "#Delta #eta between two W's", 50, -5, 5);



  book<TH1F>("M_WLep", "M_{WLep} [GeV]", 80, 0, 100);
  book<TH1F>("M_WHad", "M_{WHad} [GeV]", 80, 0, 100);

  pt_WLep_vs_pt_WHad = book<TH2F>("pt_WLep_vs_pt_WHad", "p_{T}_{WLep} [GeV] vs p_{T}_{WHad} [GeV]", 50, 0, 500, 50, 0, 500);
  M_WLep_vs_M_WHad = book<TH2F>("M_WLep_vs_M_WHad", "M_{WLep} [GeV] vs M_{WHad} [GeV]", 80, 0, 100, 80, 0, 100);
  deltaR_WW_vs_pt_WLep = book<TH2F>("deltaR_WW_vs_pt_WLep", "#Delta R_{WW} vs p_{T}^{WLep} [GeV]", 50, 0, 5, 50, 0, 500);


  // W daughters
  book<TH1F>("M_W_had reco", "M^{W}_{had} [GeV] reco", 80, 0, 100);
  book<TH1F>("M_W_lep reco", "M^{W}_{lep} [GeV] reco", 80, 0, 100);

  book<TH1F>("pt_q1", "p_{T}^{q1} [GeV]", 50, 0, 200);
  book<TH1F>("pt_q2", "p_{T}^{q2} [GeV]", 50, 0, 200);
  book<TH1F>("pt_l", "p_{T}^{lepton} [GeV]", 50, 0, 200);
  book<TH1F>("pt_n", "p_{T}^{neutrino} [GeV]", 50, 0, 200);

  pt_q1_vs_pt_q2 = book<TH2F>("pt_q1_vs_pt_q2", "p_{T}^{q1} [GeV] vs p_{T}^{q2} [GeV]", 50, 0, 500, 50, 0, 500);
  eta_q1_vs_eta_q2 = book<TH2F>("eta_q1_vs_eta_q2", "#eta^{q1} [GeV] vs #eta^{q2} [GeV]", 50, -5, 5, 50, -5, 5);


  book<TH1F>("eta_q1", "#eta^{q1} [GeV]", 50, -5, 5);
  book<TH1F>("eta_q2", "#eta^{q2} [GeV]", 50, -5, 5);
  book<TH1F>("eta_l", "#eta^{lepton} [GeV]", 50, -5, 5);
  book<TH1F>("eta_n", "#eta^{neutrino} [GeV]", 50, -5, 5);

  book<TH1F>("deltaR qq", "#Delta R between two q's", 50, 0, 5);
  book<TH1F>("deltaPhi qq", "#Delta #Phi between two q's", 50, 0, 3.2);
  book<TH1F>("deltaEta qq", "#Delta #eta between two q's", 50, -5, 5);

  book<TH1F>("deltaR lnu", "#Delta R between lepton and neutrino", 50, 0, 5);
  book<TH1F>("deltaPhi lnu", "#Delta #Phi between lepton and neutrino", 50, 0, 3.2);
  book<TH1F>("deltaEta lnu", "#Delta #eta between lepton and neutrino", 50, -5, 5);


  // b's
  book<TH1F>("pt_b1", "p_{T}^{b1} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b2", "p_{T}^{b2} [GeV]", 50, 0, 500);
  book<TH1F>("pt_b", "p_{T}^{b} [GeV]", 50, 0, 500);
  book<TH1F>("eta_b", "#eta^{b} [GeV]", 50, -2.5, 2.5);
  book<TH1F>("deltaR bb", "#Delta R between two b's", 50, 0, 5);
  book<TH1F>("deltaPhi bb", "#Delta #Phi between two b's", 50, 0, 3.2);
  book<TH1F>("deltaEta bb", "#Delta #eta between two b's", 50, -5, 5);

  book<TH1F>("M_b1", "M^{b1} [GeV]", 50, 4.6, 5.2);
  book<TH1F>("M_b2", "M^{b2} [GeV]", 50, 4.6, 5.2);


  
  pt_b1_vs_pt_b2 = book<TH2F>("pt_b1_vs_pt_b2", "p_{T}^{b1} [GeV] vs p_{T}^{b2} [GeV]", 50, 0, 500, 50, 0, 500);
  M_b1_vs_M_b2 = book<TH2F>("M_b1_vs_M_b2", "M^{b1} [GeV] vs M^{b2} [GeV]", 50, 4.6, 5.2, 50, 4.6, 5.2);
  deltaR_bb_vs_pt_b1 = book<TH2F>("deltaR_bb_vs_pt_b1", "#Delta R^{bb} vs p_{T}^{b1} [GeV]", 50, 0, 5, 50, 0, 500);


}

void HHtoWWbbSemiLeptonicGenHists::fill(const Event & event){
  // Don't forget to always use the weight when filling.
  double weight = event.weight;

  const auto & HHgen = event.get(h_HHgenobjects);
  


  /*
  GenParticle higgs_W = HHgen.H_WW();
  GenParticle higgs_b = HHgen.H_bb();
  GenParticle b1 = HHgen.B1();
  GenParticle b2 = HHgen.B2();
  GenParticle wLep = HHgen.WLep();
  GenParticle wHad = HHgen.WHad();
  GenParticle chargedLepton = HHgen.ChargedLepton();
  GenParticle neutrino = HHgen.Neutrino();
  GenParticle q1 = HHgen.Q1();
  GenParticle q2 = HHgen.Q2();
  */

  
  LorentzVector Higgs_W = HHgen.H_WW().v4();
  LorentzVector Higgs_b = HHgen.H_bb().v4();
  LorentzVector B1 = HHgen.B1().v4();
  LorentzVector B2 = HHgen.B2().v4();
  LorentzVector WLep = HHgen.WLep().v4();
  LorentzVector WHad = HHgen.WHad().v4();
  LorentzVector ChargedLepton = HHgen.ChargedLepton().v4();
  LorentzVector Neutrino = HHgen.Neutrino().v4();
  LorentzVector Quark1 = HHgen.Q1().v4();
  LorentzVector Quark2 = HHgen.Q2().v4();

  // Higgs
  hist("pt_H")->Fill(Higgs_W.pt(),weight);      
  hist("eta_H")->Fill(Higgs_W.eta(),weight);
  hist("pt_H")->Fill(Higgs_b.pt(),weight);      
  hist("eta_H")->Fill(Higgs_b.eta(),weight);
  
  hist("pt_H_b")->Fill(Higgs_b.pt(),weight);
  hist("M_H_b")->Fill(Higgs_b.M(), weight);
  hist("M_H_b_reco")->Fill((B1+B2).M(), weight);

  hist("pt_H_W")->Fill(Higgs_W.pt(),weight);
  hist("M_H_W")->Fill(Higgs_W.M(), weight);
  hist("M_H_W_reco")->Fill((WLep+WHad).M(), weight);

  double m_HH = (Higgs_W + Higgs_b).M();
  double dr_HH = deltaR(Higgs_W, Higgs_b);
  double dphi_HH = deltaPhi(Higgs_W, Higgs_b);
  double deta_HH = Higgs_b.eta() - Higgs_W.eta();
  //cout << "dphi_HH = " << dphi_HH << endl;
  hist("M_HH")->Fill(m_HH, weight);
  hist("deltaR HH")->Fill(dr_HH, weight);
  hist("deltaPhi HH")->Fill(dphi_HH, weight);
  hist("deltaEta HH")->Fill(deta_HH, weight);

  M_HH_vs_pt_l->Fill(m_HH, ChargedLepton.pt(), weight);
  pt_H_W_vs_pt_H_b->Fill(Higgs_W.pt(), Higgs_b.pt(), weight);
  M_H_W_vs_M_H_b->Fill(Higgs_W.M(), Higgs_W.M(), weight);
  deltaR_HH_vs_pt_H_W->Fill(dr_HH, Higgs_W.pt(), weight);





  // bottom quarks
  hist("pt_b")->Fill(B1.pt(),weight);
  hist("pt_b")->Fill(B2.pt(),weight);
  hist("pt_b1")->Fill(B1.pt(),weight);
  hist("pt_b2")->Fill(B2.pt(),weight);

  hist("eta_b")->Fill(B1.eta(),weight);
  hist("eta_b")->Fill(B2.eta(),weight);

  hist("M_b1")->Fill(B1.M(), weight);
  hist("M_b2")->Fill(B2.M(), weight);

  M_b1_vs_M_b2->Fill(B1.M(), B2.M(), weight);
  pt_b1_vs_pt_b2->Fill(B1.pt(), B2.pt(), weight);

  double dr_B = deltaR(B1,B2);
  double dphi_B = deltaPhi(B1,B2);
  double deta_B = B1.eta() - B2.eta();

  deltaR_bb_vs_pt_b1->Fill(dr_B, B1.pt(), weight);
  hist("deltaR bb")->Fill(dr_B, weight);
  hist("deltaPhi bb")->Fill(dphi_B, weight);	
  hist("deltaEta bb")->Fill(deta_B, weight);

  // W bosons
  hist("pt_W")->Fill(WLep.pt(),weight);
  hist("pt_W")->Fill(WHad.pt(),weight);
  hist("pt_WLep")->Fill(WLep.pt(),weight);
  hist("pt_WHad")->Fill(WHad.pt(),weight);

  hist("eta_W")->Fill(WLep.eta(),weight);
  hist("eta_W")->Fill(WHad.eta(),weight);

  hist("M_WLep")->Fill(WLep.M(), weight);
  hist("M_WHad")->Fill(WHad.M(), weight);

  M_WLep_vs_M_WHad->Fill(WLep.M(), WHad.M(), weight);
  pt_WLep_vs_pt_WHad->Fill(WLep.pt(), WHad.pt(), weight);

  double dr_W = deltaR(WLep,WHad);
  double dphi_W = deltaPhi(WLep,WHad);
  double deta_W = WLep.eta() - WHad.eta();

  deltaR_WW_vs_pt_WLep->Fill(dr_W, WLep.pt(), weight);
  hist("deltaR WW")->Fill(dr_W, weight);
  hist("deltaPhi WW")->Fill(dphi_W, weight);	
  hist("deltaEta WW")->Fill(deta_W, weight);

  

  double dr_qq = deltaR(Quark1, Quark2);
  double dphi_qq = deltaPhi(Quark1, Quark2);
  double deta_qq = Quark2.eta() - Quark1.eta();
  double dr_lnu = deltaR(ChargedLepton, Neutrino);
  double dphi_lnu = deltaPhi(ChargedLepton, Neutrino);
  double deta_lnu = ChargedLepton.eta() - Neutrino.eta();


  hist("M_W_had reco")->Fill((Quark1+Quark2).M(), weight);
  hist("M_W_lep reco")->Fill((ChargedLepton+Neutrino).M(), weight);
  hist("pt_q1")->Fill(Quark1.pt(), weight);
  hist("pt_q2")->Fill(Quark2.pt(), weight);
  hist("pt_l")->Fill(ChargedLepton.pt(), weight);
  hist("pt_n")->Fill(Neutrino.pt(), weight);

  hist("eta_q1")->Fill(Quark1.eta(), weight);
  hist("eta_q2")->Fill(Quark2.eta(), weight);
  hist("eta_l")->Fill(ChargedLepton.eta(), weight);
  hist("eta_n")->Fill(Neutrino.eta(), weight);

  hist("deltaR qq")->Fill(dr_qq, weight);
  hist("deltaPhi qq")->Fill(dphi_qq, weight);	
  hist("deltaEta qq")->Fill(deta_qq, weight);
  hist("deltaR lnu")->Fill(dr_lnu, weight);
  hist("deltaPhi lnu")->Fill(dphi_lnu, weight);	
  hist("deltaEta lnu")->Fill(deta_lnu, weight);

  pt_q1_vs_pt_q2->Fill(Quark1.pt(), Quark2.pt(), weight);
  eta_q1_vs_eta_q2->Fill(Quark1.eta(), Quark2.eta(), weight);


}


HHtoWWbbSemiLeptonicGenHists::~HHtoWWbbSemiLeptonicGenHists(){}
