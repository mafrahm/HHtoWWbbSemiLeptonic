#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

namespace uhh2examples {

  /**  \brief Example class for booking and filling histograms
   * 
   * NOTE: This class uses the 'hist' method to retrieve histograms.
   * This requires a string lookup and is therefore slow if you have
   * many histograms. Therefore, it is recommended to use histogram
   * pointers as member data instead, like in 'common/include/ElectronHists.h'.
   */
  class HHtoWWbbSemiLeptonicHists: public uhh2::Hists {
  public:
    // use the same constructor arguments as Hists for forwarding:
    HHtoWWbbSemiLeptonicHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~HHtoWWbbSemiLeptonicHists();

  protected:
    // double TransverseMass(LorentzVector A, LorentzVector B, double mA, double mB);
    uhh2::Event::Handle<HHGenRecoMatching> h_HHgenreco;

    

    // Jets
    TH1F *N_jets, *N_PU, *pt_jets, *pt_jet1, *pt_jet2, *pt_jet3, *pt_jet4, *eta_jets, *eta_jets_rebin, *eta_jet1, *eta_jet2, *eta_jet3, *eta_jet4;
    TH2F *N_jet_vs_pt_jet, *N_jet_vs_eta_jet;

    TH1F *EMcharged_jet1, *EMneutral_jet1, *HADcharged_jet1, *HADneutral_jet1;

    // bjets
    TH1F *N_bJets_loose, *N_bJets_med, *N_bJets_tight, *N_deepjet_loose, *N_deepjet_med, *N_deepjet_tight, *DeltaR_bjets;

    // leptons
    TH1F *N_mu, *pt_mu, *eta_mu, *eta_mu_rebin, *reliso_mu;
    TH1F *N_ele, *pt_ele, *eta_ele, *eta_ele_rebin, *reliso_ele;
    TH1F *N_lep;

    // MET
    TH1F *MET, *MET_rebin, *MET_rebin2;

    // ST
    TH1F *ST, *STjets, *STlep;
    TH2F *N_jets_vs_STjets;

    // M_HH
    TH1F *MHH, *CHI2;
    TH1F *MH_bb, *CHI2_H_bb, *MH_bb_simple;
    TH1F *MH_bb_rebin, *MH_bb_simple_rebin;
    TH1F *MH_WW, *CHI2_H_WW, *MH_WW_simple;
    TH1F *MH_WW_rebin, *MH_WW_simple_rebin;

    TH1F *MH_WW_lessbins, *MH_bb_lessbins;
    TH1F *MH_WW_rebin2, *MH_bb_rebin2;
    TH1F *MH_WW_simple_rebin2, *MH_bb_simple_rebin2;

    TH1F *MH_bb_limits, *MH_WW_limits;
    TH2F *Mbb_vs_MWW, *Mbb_vs_MWW_limits;
    TH2F *Mbb_vs_MWW_limits1, *Mbb_vs_MWW_limits2, *Mbb_vs_MWW_limits3;
    
    // stuff
    TH1F *sum_event_weights;
    TH1F *N_pv;


    // for reconstructed HH Mass
    bool is_mc;

    uhh2::Event::Handle<bool> h_is_mHH_reconstructed;
    uhh2::Event::Handle<float> h_mHH, h_chi2;
    uhh2::Event::Handle<float> h_mH_bb, h_chi2_H_bb;
    uhh2::Event::Handle<float> h_mH_WW, h_chi2_H_WW;

  };
}
