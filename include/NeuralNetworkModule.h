#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>
#include <UHH2/core/include/LorentzVector.h>

#include "UHH2/common/include/NeuralNetworkBase.hpp"

using namespace std;
using namespace uhh2;
//using namespace uhh2examples;


class NeuralNetworkModule: public NeuralNetworkBase {
public:
  explicit NeuralNetworkModule(uhh2::Context&, const std::string & ModelName, const std::string& ConfigName);
  virtual void CreateInputs(uhh2::Event & event) override;
protected:
  uhh2::Event::Handle<float> h_eventweight;

  uhh2::Event::Handle<float> h_mbb, h_mWW, h_mlnu, h_mqq;
  uhh2::Event::Handle<float> h_DeltaRlnu, h_DeltaRbb, h_DeltaRqq;
  uhh2::Event::Handle<float> h_minDeltaRlj, h_minDeltaRjj;
  uhh2::Event::Handle<float> h_HT;
  uhh2::Event::Handle<float> h_N_BTag, h_N_Ak4;
  uhh2::Event::Handle<float> h_mtop_lep_hyp1, h_mtop_lep_hyp2, h_mtop_had_hyp1, h_mtop_had_hyp2, h_MTtop_lep_hyp1, h_MTtop_lep_hyp2;
  uhh2::Event::Handle<float> h_MH_bb, h_MH_WW;

  uhh2::Event::Handle<float> h_Lep_pt, h_Lep_eta, h_Lep_phi, h_Lep_E;
  uhh2::Event::Handle<float> h_MET_pt, h_MET_phi;

  uhh2::Event::Handle<float> h_deepjetbmean_3jets, h_deepjetbmean_4jets;
  uhh2::Event::Handle<float> h_b1_pt, h_b2_pt, h_b1_deepjetbscore, h_b2_deepjetbscore;
  uhh2::Event::Handle<float> h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle<float> h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  uhh2::Event::Handle<float> h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;


  string NNmodel;
  int N_variables;
  
  map<string, uhh2::Event::Handle<float>> NNInputs_map = {
    {"mbb", h_mbb},
    {"mWW", h_mWW},
    {"mqq", h_mqq},
    {"mlnu", h_mlnu},
    {"DeltaRlnu", h_DeltaRlnu},
    {"DeltaRbb", h_DeltaRbb},
    {"DeltaRqq", h_DeltaRqq},
    {"minDeltaRlj", h_minDeltaRlj},
    {"minDeltaRjj", h_minDeltaRjj},
    {"HT", h_HT},
    {"N_BTag", h_N_BTag},
    {"N_Ak4", h_N_Ak4},
    {"mtop_lep_hyp1", h_mtop_lep_hyp1},
    {"mtop_lep_hyp2", h_mtop_lep_hyp2},
    {"mtop_had_hyp1", h_mtop_had_hyp1},
    {"mtop_had_hyp2", h_mtop_had_hyp2},
    {"MTtop_lep_hyp1", h_MTtop_lep_hyp1},
    {"MTtop_lep_hyp2", h_MTtop_lep_hyp2},
    {"MH_bb", h_MH_bb},
    {"MH_WW", h_MH_WW},
    {"Lep_pt", h_Lep_pt},    
    {"Lep_eta", h_Lep_eta},
    {"Lep_phi", h_Lep_phi},
    {"Lep_E", h_Lep_E},
    {"MET_pt", h_MET_pt},    
    {"MET_phi", h_MET_phi},
    {"b1_pt", h_b1_pt},
    {"b2_pt", h_b2_pt},
    {"b1_deepjetbscore", h_b1_deepjetbscore},
    {"b2_deepjetbscore", h_b2_deepjetbscore},
    {"Ak4_j1_pt", h_Ak4_j1_pt},    
    {"Ak4_j1_eta", h_Ak4_j1_eta},
    {"Ak4_j1_phi", h_Ak4_j1_phi},
    {"Ak4_j1_E", h_Ak4_j1_E},
    {"Ak4_j1_m", h_Ak4_j1_E},
    {"Ak4_j1_deepjetbscore", h_Ak4_j1_deepjetbscore},
    {"Ak4_j2_pt", h_Ak4_j2_pt},    
    {"Ak4_j2_eta", h_Ak4_j2_eta},
    {"Ak4_j2_phi", h_Ak4_j2_phi},
    {"Ak4_j2_E", h_Ak4_j2_E},
    {"Ak4_j2_m", h_Ak4_j2_E},
    {"Ak4_j2_deepjetbscore", h_Ak4_j2_deepjetbscore},
    {"Ak4_j3_pt", h_Ak4_j3_pt},    
    {"Ak4_j3_eta", h_Ak4_j3_eta},
    {"Ak4_j3_phi", h_Ak4_j3_phi},
    {"Ak4_j3_E", h_Ak4_j3_E},
    {"Ak4_j3_m", h_Ak4_j3_E},
    {"Ak4_j3_deepjetbscore", h_Ak4_j3_deepjetbscore}
  };

};
