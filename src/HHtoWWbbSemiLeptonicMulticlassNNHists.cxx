#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicMulticlassNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
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

NN_out0 = book<TH1F>("NN_out0", "NN output 0", 40, 0, 1);
NN_out1 = book<TH1F>("NN_out1", "NN output 1", 40, 0, 1);
NN_out2 = book<TH1F>("NN_out2", "NN output 2", 40, 0, 1);
NN_out3 = book<TH1F>("NN_out3", "NN output 3", 40, 0, 1);
NN_out4 = book<TH1F>("NN_out4", "NN output 4", 40, 0, 1);

NN_out0_rebin = book<TH1F>("NN_out0_rebin", "NN output 0", 10, 0, 1);
NN_out1_rebin = book<TH1F>("NN_out1_rebin", "NN output 1", 10, 0, 1);
NN_out2_rebin = book<TH1F>("NN_out2_rebin", "NN output 2", 10, 0, 1);
NN_out3_rebin = book<TH1F>("NN_out3_rebin", "NN output 3", 10, 0, 1);
NN_out4_rebin = book<TH1F>("NN_out4_rebin", "NN output 4", 10, 0, 1);
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
}

HHtoWWbbSemiLeptonicMulticlassNNHists::~HHtoWWbbSemiLeptonicMulticlassNNHists(){}








HHtoWWbbSemiLeptonicMulticlassNNInputHists::HHtoWWbbSemiLeptonicMulticlassNNInputHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {
  cout << "HHtoWWbbSemiLeptonicHists" << endl;


  // fill the map
  fill_map(ctx, "mbb", NN_mbb, {40,0,400});
  fill_map(ctx, "mWW", NN_mWW, {40,0,400});
  fill_map(ctx, "mlnu", NN_mlnu, {40,0,400});
  fill_map(ctx, "mqq", NN_mqq, {40,0,400});
  fill_map(ctx, "DeltaRlnu", NN_DeltaRlnu, {40,0,6});
  fill_map(ctx, "DeltaRbb", NN_DeltaRbb, {40,0,6});
  fill_map(ctx, "DeltaRqq", NN_DeltaRqq, {40,0,6});
  fill_map(ctx, "minDeltaRlj", NN_minDeltaRlj, {40,0,6});
  fill_map(ctx, "minDeltaRbj", NN_minDeltaRbj, {40,0,6});
  fill_map(ctx, "minDeltaRjj", NN_minDeltaRjj, {40,0,6});
  fill_map(ctx, "minDeltaRb1j", NN_minDeltaRb1j, {40,0,6});
  fill_map(ctx, "minDeltaRb2j", NN_minDeltaRb2j, {40,0,6});

  fill_map(ctx, "minDeltaEtalj", NN_minDeltaEtalj, {40,0,3});
  fill_map(ctx, "minDeltaEtabj", NN_minDeltaEtabj, {40,0,3});
  fill_map(ctx, "minDeltaEtajj", NN_minDeltaEtajj, {40,0,3});

  fill_map(ctx, "HT", NN_HT, {60,0,1500});
  fill_map(ctx, "N_BTag", NN_NBTag, {4,-0,5,5,5});
  fill_map(ctx, "N_Ak4", NN_NAk4, {11,-0.5,10.5});
  fill_map(ctx, "mtop_lep_hyp1", NN_mtop_lep1, {40,0,800});
  fill_map(ctx, "mtop_lep_hyp2", NN_mtop_lep2, {40,0,800});
  fill_map(ctx, "mtop_had_hyp1", NN_mtop_had1, {40,0,800});
  fill_map(ctx, "mtop_had_hyp2", NN_mtop_had2, {40,0,800});
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
