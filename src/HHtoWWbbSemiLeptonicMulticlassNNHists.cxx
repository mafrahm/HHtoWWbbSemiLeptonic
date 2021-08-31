#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include "TH2F.h"

#include <iostream>

using namespace std;
using namespace uhh2;

HHtoWWbbSemiLeptonicMulticlassNNHists::HHtoWWbbSemiLeptonicMulticlassNNHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {

  h_NNoutput0 = ctx.get_handle<double>("NNoutput0");
  h_NNoutput1 = ctx.get_handle<double>("NNoutput1");
  h_NNoutput2 = ctx.get_handle<double>("NNoutput2");
  h_NNoutput3 = ctx.get_handle<double>("NNoutput3");
  h_NNoutput4 = ctx.get_handle<double>("NNoutput4");

  init();
}

void HHtoWWbbSemiLeptonicMulticlassNNHists::init(){

  NN_out0 = book<TH1F>("NN_out0", "NN output 0", 1000, 0, 1);
  NN_out1 = book<TH1F>("NN_out1", "NN output 1", 1000, 0, 1);
  NN_out2 = book<TH1F>("NN_out2", "NN output 2", 1000, 0, 1);
  NN_out3 = book<TH1F>("NN_out3", "NN output 3", 1000, 0, 1);
  NN_out4 = book<TH1F>("NN_out4", "NN output 4", 1000, 0, 1);

  NN_out0_rebin = book<TH1F>("NN_out0_rebin", "NN output 0", 20, 0, 1);
  NN_out1_rebin = book<TH1F>("NN_out1_rebin", "NN output 1", 20, 0, 1);
  NN_out2_rebin = book<TH1F>("NN_out2_rebin", "NN output 2", 20, 0, 1);
  NN_out3_rebin = book<TH1F>("NN_out3_rebin", "NN output 3", 20, 0, 1);
  NN_out4_rebin = book<TH1F>("NN_out4_rebin", "NN output 4", 20, 0, 1);


  vector<float> limitbins_sr_0 = {0,0.4,0.48,0.56,0.72,0.8,0.84,0.88,0.92,0.95,0.98,1.0};
  vector<float> limitbins_sr_1 = {0,0.4,0.5,0.6,0.7,0.8,0.85,0.9,0.93,0.96,0.98,1.0};
  vector<float> limitbins_sr_2 = {0,0.4,0.5,0.6,0.7,0.8,0.86,0.92,0.96,1.0};
  vector<float> limitbins_sr_3 = {0,0.4,0.5,0.6,0.7,0.8,0.9,0.96,1.0};


  vector<float> limitbins_ttcr_0 = {0,0.3,0.38,0.43,0.48,0.53,0.58,0.63,0.68,0.73,0.80,1.0};
  vector<float> limitbins_ttcr_1 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.80,1.0};
  vector<float> limitbins_ttcr_2 = {0,0.3,0.4,0.48,0.56,0.64,0.72,1.0};
  vector<float> limitbins_ttcr_3 = {0,0.35,0.45,0.55,0.65,0.75,1.0};


  vector<float> limitbins_stcr_0 = {0,0.3,0.38,0.43,0.48,0.53,0.58,0.63,0.68,0.73,0.80,0.90,1.0};
  vector<float> limitbins_stcr_1 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.80,0.90,1.0};
  vector<float> limitbins_stcr_2 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.80,1.0};
  vector<float> limitbins_stcr_3 = {0,0.35,0.45,0.55,0.65,0.75,1.0};


  vector<float> limitbins_wdycr_0 = {0,0.3,0.38,0.44,0.50,0.56,0.62,0.68,0.74,0.80,0.85,0.90,0.95,1.0};
  vector<float> limitbins_wdycr_1 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.80,0.85,0.90,0.95,1.0};
  vector<float> limitbins_wdycr_2 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0};
  vector<float> limitbins_wdycr_3 = {0,0.35,0.44,0.53,0.62,0.71,0.8,0.9,1.0};

  vector<float> limitbins_qcdcr_0 = {0,0.3,0.38,0.44,0.50,0.56,0.62,0.68,0.74,0.80,0.85,0.90,0.95,1.0};
  vector<float> limitbins_qcdcr_1 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.80,0.85,0.90,0.95,1.0};
  vector<float> limitbins_qcdcr_2 = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0};
  vector<float> limitbins_qcdcr_3 = {0,0.35,0.44,0.53,0.62,0.71,0.8,0.9,1.0};


  NN_out0_limits0 = book<TH1F>("NN_out0_limits0", "NN output 0", limitbins_sr_0.size()-1, &limitbins_sr_0[0]);
  NN_out1_limits0 = book<TH1F>("NN_out1_limits0", "NN output 1", limitbins_ttcr_0.size()-1, &limitbins_ttcr_0[0]);
  NN_out2_limits0 = book<TH1F>("NN_out2_limits0", "NN output 2", limitbins_stcr_0.size()-1, &limitbins_stcr_0[0]);
  NN_out3_limits0 = book<TH1F>("NN_out3_limits0", "NN output 3", limitbins_wdycr_0.size()-1, &limitbins_wdycr_0[0]);
  NN_out4_limits0 = book<TH1F>("NN_out4_limits0", "NN output 4", limitbins_qcdcr_0.size()-1, &limitbins_qcdcr_0[0]);

  NN_out0_limits1 = book<TH1F>("NN_out0_limits1", "NN output 0", limitbins_sr_1.size()-1, &limitbins_sr_1[0]);
  NN_out1_limits1 = book<TH1F>("NN_out1_limits1", "NN output 1", limitbins_ttcr_1.size()-1, &limitbins_ttcr_1[0]);
  NN_out2_limits1 = book<TH1F>("NN_out2_limits1", "NN output 2", limitbins_stcr_1.size()-1, &limitbins_stcr_1[0]);
  NN_out3_limits1 = book<TH1F>("NN_out3_limits1", "NN output 3", limitbins_wdycr_1.size()-1, &limitbins_wdycr_1[0]);
  NN_out4_limits1 = book<TH1F>("NN_out4_limits1", "NN output 4", limitbins_qcdcr_3.size()-1, &limitbins_qcdcr_1[0]);

  NN_out0_limits2 = book<TH1F>("NN_out0_limits2", "NN output 0", limitbins_sr_2.size()-1, &limitbins_sr_2[0]);
  NN_out1_limits2 = book<TH1F>("NN_out1_limits2", "NN output 1", limitbins_ttcr_2.size()-1, &limitbins_ttcr_2[0]);
  NN_out2_limits2 = book<TH1F>("NN_out2_limits2", "NN output 2", limitbins_stcr_2.size()-1, &limitbins_stcr_2[0]);
  NN_out3_limits2 = book<TH1F>("NN_out3_limits2", "NN output 3", limitbins_wdycr_2.size()-1, &limitbins_wdycr_2[0]);
  NN_out4_limits2 = book<TH1F>("NN_out4_limits2", "NN output 4", limitbins_qcdcr_2.size()-1, &limitbins_qcdcr_2[0]);

  NN_out0_limits3 = book<TH1F>("NN_out0_limits3", "NN output 0", limitbins_sr_3.size()-1, &limitbins_sr_3[0]);
  NN_out1_limits3 = book<TH1F>("NN_out1_limits3", "NN output 1", limitbins_ttcr_3.size()-1, &limitbins_ttcr_3[0]);
  NN_out2_limits3 = book<TH1F>("NN_out2_limits3", "NN output 2", limitbins_stcr_3.size()-1, &limitbins_stcr_3[0]);
  NN_out3_limits3 = book<TH1F>("NN_out3_limits3", "NN output 3", limitbins_wdycr_3.size()-1, &limitbins_wdycr_3[0]);
  NN_out4_limits3 = book<TH1F>("NN_out4_limits3", "NN output 4", limitbins_qcdcr_3.size()-1, &limitbins_qcdcr_3[0]);

}

void HHtoWWbbSemiLeptonicMulticlassNNHists::fill(const Event & event){

double weight = event.weight;
double NNoutput0 = event.get(h_NNoutput0);
double NNoutput1 = event.get(h_NNoutput1);
double NNoutput2 = event.get(h_NNoutput2);
double NNoutput3 = event.get(h_NNoutput3);
double NNoutput4 = event.get(h_NNoutput4);

NN_out0->Fill(NNoutput0, weight);
NN_out1->Fill(NNoutput1, weight);
NN_out2->Fill(NNoutput2, weight);
NN_out3->Fill(NNoutput3, weight);
NN_out4->Fill(NNoutput4, weight);

NN_out0_rebin->Fill(NNoutput0, weight);
NN_out1_rebin->Fill(NNoutput1, weight);
NN_out2_rebin->Fill(NNoutput2, weight);
NN_out3_rebin->Fill(NNoutput3, weight);
NN_out4_rebin->Fill(NNoutput4, weight);

NN_out0_limits0->Fill(NNoutput0, weight);
NN_out1_limits0->Fill(NNoutput1, weight);
NN_out2_limits0->Fill(NNoutput2, weight);
NN_out3_limits0->Fill(NNoutput3, weight);
NN_out4_limits0->Fill(NNoutput4, weight);

NN_out0_limits1->Fill(NNoutput0, weight);
NN_out1_limits1->Fill(NNoutput1, weight);
NN_out2_limits1->Fill(NNoutput2, weight);
NN_out3_limits1->Fill(NNoutput3, weight);
NN_out4_limits1->Fill(NNoutput4, weight);

NN_out0_limits2->Fill(NNoutput0, weight);
NN_out1_limits2->Fill(NNoutput1, weight);
NN_out2_limits2->Fill(NNoutput2, weight);
NN_out3_limits2->Fill(NNoutput3, weight);
NN_out4_limits2->Fill(NNoutput4, weight);

NN_out0_limits3->Fill(NNoutput0, weight);
NN_out1_limits3->Fill(NNoutput1, weight);
NN_out2_limits3->Fill(NNoutput2, weight);
NN_out3_limits3->Fill(NNoutput3, weight);
NN_out4_limits3->Fill(NNoutput4, weight);

}

HHtoWWbbSemiLeptonicMulticlassNNHists::~HHtoWWbbSemiLeptonicMulticlassNNHists(){}








HHtoWWbbSemiLeptonicMulticlassNNInputHists::HHtoWWbbSemiLeptonicMulticlassNNInputHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {
  cout << "HHtoWWbbSemiLeptonicMulticlassNNInputHists" << endl;


  // fill the map
  fill_map(ctx, "mbb", NN_mbb, {40,0,400});
  fill_map(ctx, "mWW", NN_mWW, {40,0,400});
  fill_map(ctx, "mlnu", NN_mlnu, {40,0,400});
  fill_map(ctx, "mqq", NN_mqq, {40,0,400});
  fill_map(ctx, "DeltaRlnu", NN_DeltaRlnu, {40,0,6});
  fill_map(ctx, "DeltaRbb", NN_DeltaRbb, {40,0,6});
  fill_map(ctx, "DeltaRqq", NN_DeltaRqq, {40,0,6});
  fill_map(ctx, "DeltaEtalnu", NN_DeltaEtalnu, {40,-2.5,2.5});
  fill_map(ctx, "DeltaEtabb", NN_DeltaEtabb, {40,-2.5,2.5});
  fill_map(ctx, "DeltaEtaqq", NN_DeltaEtaqq, {40,-2.5,2.5});
  fill_map(ctx, "DeltaPhilnu", NN_DeltaPhilnu, {40,0,3.2});
  fill_map(ctx, "DeltaPhibb", NN_DeltaPhibb, {40,0,3.2});
  fill_map(ctx, "DeltaPhiqq", NN_DeltaPhiqq, {40,0,3.2});

  fill_map(ctx, "minDeltaRlj", NN_minDeltaRlj, {40,0,6});
  fill_map(ctx, "minDeltaRjj", NN_minDeltaRjj, {40,0,6});
  fill_map(ctx, "minDeltaRb1j", NN_minDeltaRb1j, {40,0,6});
  fill_map(ctx, "minDeltaRb2j", NN_minDeltaRb2j, {40,0,6});

  fill_map(ctx, "minDeltaPhilj", NN_minDeltaPhilj, {40,0,3.2});
  fill_map(ctx, "minDeltaPhijj", NN_minDeltaPhijj, {40,0,3.2});
  fill_map(ctx, "minDeltaPhib1j", NN_minDeltaPhib1j, {40,0,3.2});
  fill_map(ctx, "minDeltaPhib2j", NN_minDeltaPhib2j, {40,0,3.2});

  fill_map(ctx, "minDeltaEtalj", NN_minDeltaEtalj, {40,0,3});
  fill_map(ctx, "minDeltaEtajj", NN_minDeltaEtajj, {40,0,3});
  fill_map(ctx, "minDeltaEtab1j", NN_minDeltaEtab1j, {40,0,3});
  fill_map(ctx, "minDeltaEtab2j", NN_minDeltaEtab2j, {40,0,3});


  fill_map(ctx, "DeltaPhi_j1MET", DeltaPhi_j1MET, {40,0,3.2});
  fill_map(ctx, "DeltaPhi_j2MET", DeltaPhi_j2MET, {40,0,3.2});
  fill_map(ctx, "DeltaPhi_j3MET", DeltaPhi_j3MET, {40,0,3.2});


  fill_map(ctx, "HT", NN_HT, {60,0,1500});
  fill_map(ctx, "N_BTag", NN_NBTag, {4,-0,5,5,5});
  fill_map(ctx, "N_Ak4", NN_NAk4, {11,-0.5,10.5});
  fill_map(ctx, "mtop_lep_hyp1", NN_mtop_lep1, {40,0,800});
  fill_map(ctx, "mtop_lep_hyp2", NN_mtop_lep2, {40,0,800});
  fill_map(ctx, "mtop_had_hyp1", NN_mtop_had1, {40,0,800});
  fill_map(ctx, "mtop_had_hyp2", NN_mtop_had2, {40,0,800});
  fill_map(ctx, "MTtop_lep_hyp1", NN_MTtop_lep1, {40,0,800});
  fill_map(ctx, "MTtop_lep_hyp2", NN_MTtop_lep2, {40,0,800});
  fill_map(ctx, "MH_bb", NN_mbb_chi2, {40,0,400});
  fill_map(ctx, "MH_WW", NN_mWW_chi2, {40,0,400});

  fill_map(ctx, "Lep_pt", NN_Lep_pt, {40,0,400});
  fill_map(ctx, "Lep_eta", NN_Lep_eta, {40,-2.5,2.5});
  fill_map(ctx, "Lep_phi", NN_Lep_phi, {40,-4,4});
  fill_map(ctx, "Lep_E", NN_Lep_E, {40,0,200});
  fill_map(ctx, "MET_pt", NN_MET_pt, {40,0,400});
  fill_map(ctx, "MET_phi", NN_MET_phi, {40,-4,4});

  fill_map(ctx, "deepjetbmean_3jets", NN_deepjetbmean_3jets, {40,0,1});
  fill_map(ctx, "deepjetbmean_4jets", NN_deepjetbmean_4jets, {40,0,1});
  fill_map(ctx, "deepjetbmean", NN_deepjetbmean, {40,0,1});

  fill_map(ctx, "b1_pt", NN_b1_pt, {40,0,400});
  fill_map(ctx, "b2_pt", NN_b2_pt, {40,0,400});

  fill_map(ctx, "b1_deepjetbscore", NN_b1_deepjetbscore, {40,0,1});
  fill_map(ctx, "b2_deepjetbscore", NN_b2_deepjetbscore, {40,0,1});

  fill_map(ctx, "Ak4_j1_pt", NN_Ak4_j1_pt, {40,0,400});
  fill_map(ctx, "Ak4_j1_eta", NN_Ak4_j1_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j1_phi", NN_Ak4_j1_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j1_E", NN_Ak4_j1_E, {40,0,400});
  fill_map(ctx, "Ak4_j1_m", NN_Ak4_j1_m, {40,0,100});
  fill_map(ctx, "Ak4_j1_deepjetbscore", NN_Ak4_j1_deepjetbscore, {40,0,1});
  fill_map(ctx, "Ak4_j2_pt", NN_Ak4_j2_pt, {40,0,400});
  fill_map(ctx, "Ak4_j2_eta", NN_Ak4_j2_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j2_phi", NN_Ak4_j2_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j2_E", NN_Ak4_j2_E, {40,0,400});
  fill_map(ctx, "Ak4_j2_m", NN_Ak4_j2_m, {40,0,100});
  fill_map(ctx, "Ak4_j2_deepjetbscore", NN_Ak4_j2_deepjetbscore, {40,0,1});
  fill_map(ctx, "Ak4_j3_pt", NN_Ak4_j3_pt, {40,0,400});
  fill_map(ctx, "Ak4_j3_eta", NN_Ak4_j3_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j3_phi", NN_Ak4_j3_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j3_E", NN_Ak4_j3_E, {40,0,400});
  fill_map(ctx, "Ak4_j3_m", NN_Ak4_j3_m, {40,0,100});
  fill_map(ctx, "Ak4_j3_deepjetbscore", NN_Ak4_j3_deepjetbscore, {40,0,1});
  fill_map(ctx, "Ak4_j4_pt", NN_Ak4_j4_pt, {40,0,400});
  fill_map(ctx, "Ak4_j4_eta", NN_Ak4_j4_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j4_phi", NN_Ak4_j4_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j4_E", NN_Ak4_j4_E, {40,0,400});
  fill_map(ctx, "Ak4_j4_m", NN_Ak4_j4_m, {40,0,100});
  fill_map(ctx, "Ak4_j4_deepjetbscore", NN_Ak4_j4_deepjetbscore, {40,0,1});
  fill_map(ctx, "Ak4_j5_pt", NN_Ak4_j5_pt, {40,0,400});
  fill_map(ctx, "Ak4_j5_eta", NN_Ak4_j5_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j5_phi", NN_Ak4_j5_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j5_E", NN_Ak4_j5_E, {40,0,400});
  fill_map(ctx, "Ak4_j5_m", NN_Ak4_j5_m, {40,0,100});
  fill_map(ctx, "Ak4_j5_deepjetbscore", NN_Ak4_j5_deepjetbscore, {40,0,1});
  fill_map(ctx, "Ak4_j6_pt", NN_Ak4_j6_pt, {40,0,400});
  fill_map(ctx, "Ak4_j6_eta", NN_Ak4_j6_eta, {40,-2.5,2.5});
  fill_map(ctx, "Ak4_j6_phi", NN_Ak4_j6_phi, {40,-4,4});
  fill_map(ctx, "Ak4_j6_E", NN_Ak4_j6_E, {40,0,400});
  fill_map(ctx, "Ak4_j6_m", NN_Ak4_j6_m, {40,0,100});
  fill_map(ctx, "Ak4_j6_deepjetbscore", NN_Ak4_j6_deepjetbscore, {40,0,1});

  init();
}

void HHtoWWbbSemiLeptonicMulticlassNNInputHists::fill_map(uhh2::Context& ctx, string id, TH1F *hist, vector<float> bins){
  //cout << "fill_map" << endl;
  HHAutoHist output;
  output.hist = hist;
  output.bins = bins;
  output.h_var = ctx.get_handle<float>(id);

  histMap.insert(pair<string,HHAutoHist>(id, output));
}


void HHtoWWbbSemiLeptonicMulticlassNNInputHists::init(){
  cout << "init" << endl;
  // declare the hists 

  sum_event_weights = book<TH1F>("sum_event_weights", "BinContent = sum(eventweights)", 1, 0.5, 1.5);
  sum_event_mc = book<TH1F>("sum_event_mc", "BinContent = sum(eventmc)", 1, 0.5, 1.5);
 
  map<string,HHAutoHist>::iterator it;
  for(it=histMap.begin(); it!= histMap.end(); it++){
    string id = it->first;
    HHAutoHist *output = &(it->second);
    
    output->hist = book<TH1F>(id,id, output->bins[0],output->bins[1],output->bins[2]);    
    
  }

  HT_rebin1 = book<TH1F>("HT_rebin1", "HT_rebin1", 60,0,400);
  HT_rebin2 = book<TH1F>("HT_rebin2", "HT_rebin2", 60,0,4000);

}

void HHtoWWbbSemiLeptonicMulticlassNNInputHists::fill(const Event & event){
  //cout << "MulticlassNNInputHists::fill" << endl;
  double weight = event.weight;

  sum_event_weights->Fill(1., weight);
  sum_event_mc->Fill(1.);

  // fill the hists
  map<string,HHAutoHist>::iterator it;
  for(it=histMap.begin(); it!= histMap.end(); it++){
    string id = it->first;
    HHAutoHist *output = &(it->second);
    float var = event.get(output->h_var);
    output->hist->Fill(var, weight);
    if(id=="HT"){
      HT_rebin1->Fill(var, weight);
      HT_rebin2->Fill(var, weight);
    }
  }
  
}

HHtoWWbbSemiLeptonicMulticlassNNInputHists::~HHtoWWbbSemiLeptonicMulticlassNNInputHists(){}







HHtoWWbbSemiLeptonicMulticlassNN2DHists::HHtoWWbbSemiLeptonicMulticlassNN2DHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {
  cout << "HHtoWWbbSemiLeptonicMulticlassNN2DHists" << endl;


  fill_map(ctx, "MET_pt", "DeltaPhi_j1MET", MET_pt__DeltaPhi_j1MET, {20,0,400, 20,0,3.2});
  fill_map(ctx, "MET_pt", "DeltaPhi_j2MET", MET_pt__DeltaPhi_j2MET, {20,0,400, 20,0,3.2});
  fill_map(ctx, "MET_pt", "DeltaPhi_j3MET", MET_pt__DeltaPhi_j3MET, {20,0,400, 20,0,3.2});

  fill_map(ctx, "DeltaPhi_j1MET", "DeltaPhi_j2MET", DeltaPhi_j1MET__DeltaPhi_j2MET, {20,0,3.2, 20,0,3.2});
  fill_map(ctx, "DeltaPhi_j1MET", "DeltaPhi_j3MET", DeltaPhi_j1MET__DeltaPhi_j3MET, {20,0,3.2, 20,0,3.2});
  fill_map(ctx, "DeltaPhi_j2MET", "DeltaPhi_j3MET", DeltaPhi_j2MET__DeltaPhi_j3MET, {20,0,3.2, 20,0,3.2});

  init();
}

void HHtoWWbbSemiLeptonicMulticlassNN2DHists::fill_map(uhh2::Context& ctx, string id1, string id2, TH2F *hist, vector<float> bins){
  //cout << "fill_map" << endl;
  HH2DAutoHist output;
  output.hist = hist;
  output.bins = bins;
  output.h_var1 = ctx.get_handle<float>(id1);
  output.h_var2 = ctx.get_handle<float>(id2);

  string id = id1+"__"+id2;
  histMap.insert(pair<string,HH2DAutoHist>(id, output));
}


void HHtoWWbbSemiLeptonicMulticlassNN2DHists::init(){
  cout << "init" << endl;
  // declare the hists 
 
  map<string,HH2DAutoHist>::iterator it;
  for(it=histMap.begin(); it!= histMap.end(); it++){
    string id = it->first;
    HH2DAutoHist *output = &(it->second);
    
    output->hist = book<TH2F>(id,id, output->bins[0],output->bins[1],output->bins[2], output->bins[3], output->bins[4], output->bins[5]);
  }
}

void HHtoWWbbSemiLeptonicMulticlassNN2DHists::fill(const Event & event){
  //cout << "MulticlassNN2DHists::fill" << endl;
  double weight = event.weight;
  // fill the hists
  map<string,HH2DAutoHist>::iterator it;
  for(it=histMap.begin(); it!= histMap.end(); it++){
    string id = it->first;
    HH2DAutoHist *output = &(it->second);
    float var1 = event.get(output->h_var1);
    float var2 = event.get(output->h_var2);

    // cout << "var1: " << var1 << endl;
    // cout << "var2: " << var2 << endl;


    output->hist->Fill(var1, var2, weight);
  }
}
  
HHtoWWbbSemiLeptonicMulticlassNN2DHists::~HHtoWWbbSemiLeptonicMulticlassNN2DHists(){}
