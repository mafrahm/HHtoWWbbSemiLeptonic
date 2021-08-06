#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

using namespace std;

struct HHAutoHist {
  //string histname;
  TH1F *hist;
  vector<float> bins;
  uhh2::Event::Handle<float> h_var;
};

class HHtoWWbbSemiLeptonicMulticlassNNHists: public uhh2::Hists {
public:
  explicit HHtoWWbbSemiLeptonicMulticlassNNHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 protected:
  void init();

  TH1F *NN_out0, *NN_out1, *NN_out2, *NN_out3, *NN_out4;
  TH1F *NN_out0_rebin, *NN_out1_rebin, *NN_out2_rebin, *NN_out3_rebin, *NN_out4_rebin;
  uhh2::Event::Handle<double> h_NNoutput0;
  uhh2::Event::Handle<double> h_NNoutput1;
  uhh2::Event::Handle<double> h_NNoutput2;
  uhh2::Event::Handle<double> h_NNoutput3;
  uhh2::Event::Handle<double> h_NNoutput4;

  virtual ~HHtoWWbbSemiLeptonicMulticlassNNHists();
};
          
class HHtoWWbbSemiLeptonicMulticlassNNInputHists: public uhh2::Hists {
public:
  explicit HHtoWWbbSemiLeptonicMulticlassNNInputHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 protected:
  void fill_map(uhh2::Context& ctx, string id, TH1F *hist, vector<float> bins);
  void init();

  map<string, HHAutoHist> histMap;


  TH1F *NN_mbb, *NN_mWW, *NN_mlnu, *NN_mqq;
  TH1F *NN_DeltaRlnu, *NN_DeltaRbb, *NN_DeltaRqq;
  TH1F *NN_DeltaEtalnu, *NN_DeltaEtabb, *NN_DeltaEtaqq;
  TH1F *NN_DeltaPhilnu, *NN_DeltaPhibb, *NN_DeltaPhiqq;
  
  TH1F *NN_minDeltaRlj, *NN_minDeltaRjj;
  TH1F *NN_HT, *NN_NBTag, *NN_NAk4, *NN_mtop_lep1, *NN_mtop_lep2, *NN_mtop_had1, *NN_mtop_had2, *NN_mbb_chi2, *NN_mWW_chi2;
  TH1F *NN_MTtop_lep1, *NN_MTtop_lep2;

  TH1F *NN_minDeltaRb1j, *NN_minDeltaRb2j, *NN_minDeltaEtab1j, *NN_minDeltaEtab2j, *NN_minDeltaPhib1j, *NN_minDeltaPhib2j;
  TH1F *NN_minDeltaEtalj, *NN_minDeltaEtajj;
  TH1F *NN_minDeltaPhilj, *NN_minDeltaPhijj;

  TH1F *HT_rebin1, *HT_rebin2;

  TH1F *NN_Lep_pt, *NN_Lep_eta, *NN_Lep_phi, *NN_Lep_E;
  TH1F *NN_MET_pt, *NN_MET_phi;
  TH1F *NN_deepjetbmean_3jets, *NN_deepjetbmean_4jets;
  TH1F *NN_b1_pt, *NN_b2_pt, *NN_b1_deepjetbscore, *NN_b2_deepjetbscore;
  TH1F *NN_Ak4_j1_pt, *NN_Ak4_j1_eta, *NN_Ak4_j1_phi, *NN_Ak4_j1_E, *NN_Ak4_j1_m, *NN_Ak4_j1_deepjetbscore;;
  TH1F *NN_Ak4_j2_pt, *NN_Ak4_j2_eta, *NN_Ak4_j2_phi, *NN_Ak4_j2_E, *NN_Ak4_j2_m, *NN_Ak4_j2_deepjetbscore;;
  TH1F *NN_Ak4_j3_pt, *NN_Ak4_j3_eta, *NN_Ak4_j3_phi, *NN_Ak4_j3_E, *NN_Ak4_j3_m, *NN_Ak4_j3_deepjetbscore;;
  TH1F *NN_Ak4_j4_pt, *NN_Ak4_j4_eta, *NN_Ak4_j4_phi, *NN_Ak4_j4_E, *NN_Ak4_j4_m, *NN_Ak4_j4_deepjetbscore;;
  TH1F *NN_Ak4_j5_pt, *NN_Ak4_j5_eta, *NN_Ak4_j5_phi, *NN_Ak4_j5_E, *NN_Ak4_j5_m, *NN_Ak4_j5_deepjetbscore;;
  TH1F *NN_Ak4_j6_pt, *NN_Ak4_j6_eta, *NN_Ak4_j6_phi, *NN_Ak4_j6_E, *NN_Ak4_j6_m, *NN_Ak4_j6_deepjetbscore;;


  virtual ~HHtoWWbbSemiLeptonicMulticlassNNInputHists();
};
