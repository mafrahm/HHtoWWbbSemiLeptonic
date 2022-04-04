#include "../include/Tools.h"

using namespace std;

void CountBackgrounds() {
  TString cuts = "BTag";
  //TString cuts = "QCDcut3";
  //TString cuts = "DNNoutput0";
  vector<TString> backgrounds = {"TTbar", "SingleTop", "WJets", "DYJets", "Diboson", "TTV", "QCD"}; //, "QCDMu", "QCDEle"};
  
  TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/Inclusive_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.";
  //TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/NNApplication/Inclusive_PTJet30_NNbkgweightX8_removeQCD_classes4_TrainOn30/NOMINAL/uhh2.AnalysisM(oduleRunner.MC.";
  //TString histname_e = cuts+"_ech_General/sum_event_weights";
  //TString histname_mu = cuts+"_much_General/sum_event_weights";
  TString histname_e = cuts+"_ech_NNInput/sum_event_weights";
  TString histname_mu = cuts+"_much_NNInput/sum_event_weights";
  double N_events_e_total, N_events_mu_total, N_events_total = 0;
  vector<double> N_events_backgrounds, N_events_mu_backgrounds, N_events_e_backgrounds;
  
  // backgrounds
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    TString proc = backgrounds[i];
    cout << proc << endl;
    double N_events_e, N_events_mu;
    if(proc!= "QCD"){
      TFile* infile = new TFile(infilename+proc+"_2016v3.root");
      N_events_e = ((TH1F*)infile->Get(histname_e))->Integral();
      N_events_mu = ((TH1F*)infile->Get(histname_mu))->Integral();
    }
    else {
      TFile* infile_e = new TFile(infilename+"QCDEle_2016v3.root");
      N_events_e = ((TH1F*)infile_e->Get(histname_e))->Integral();
      TFile* infile_mu = new TFile(infilename+"QCDMu_2016v3.root");
      N_events_mu = ((TH1F*)infile_mu->Get(histname_mu))->Integral();
    }
    N_events_e_total += N_events_e;
    N_events_e_backgrounds.push_back(N_events_e);
    N_events_mu_total += N_events_mu;
    N_events_mu_backgrounds.push_back(N_events_mu);

    N_events_total += N_events_e+N_events_mu;
    N_events_backgrounds.push_back(N_events_e+N_events_mu);
  }

  //signals
  vector<TString> signals = {"HHtoWWbbSL_cHHH0","HHtoWWbbSL_cHHH1","HHtoWWbbSL_cHHH2p45","HHtoWWbbSL_cHHH5"};
  vector<double> N_events_signals, N_events_mu_signals, N_events_e_signals;
  for(unsigned int i=0; i<signals.size(); i++) {
    TString sig = signals[i];
    TFile* infile = new TFile(infilename+sig+"_2016v3.root");
    double N_events_e = ((TH1F*)infile->Get(histname_e))->Integral();
    double N_events_mu = ((TH1F*)infile->Get(histname_mu))->Integral();
    N_events_signals.push_back(N_events_e+N_events_mu);
    N_events_e_signals.push_back(N_events_e);
    N_events_mu_signals.push_back(N_events_mu);
  }

  
  cout << "----------- Inclusive channel (after cut: " << cuts << ") ---------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << " contributes " << 100*N_events_backgrounds[i]/N_events_total << "% to the background" << endl;
  }
  cout << "---------------- Muon channel (after cut: " << cuts << ") ---------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << " contributes " << 100*N_events_mu_backgrounds[i]/N_events_mu_total << "% to the background" << endl;
  }
  cout << "------------ Electron channel (after cut: " << cuts << ") ---------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << " contributes " << 100*N_events_e_backgrounds[i]/N_events_e_total << "% to the background" << endl;
  }
  
  cout << "----------- Inclusive channel (after cut: " << cuts << ") ---------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << ": " << N_events_backgrounds[i] << " events" << endl;
  }
  for(unsigned int i=0; i<signals.size(); i++) {
    cout << "Signal " << signals[i] << ": " << N_events_signals[i] << " events" << endl;
  }

  cout << "---------------- Muon channel (after cut: " << cuts << ")  ---------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << ": " << N_events_mu_backgrounds[i] << " events" << endl;
  }
  for(unsigned int i=0; i<signals.size(); i++) {
    cout << "Signal " << signals[i] << ": " << N_events_mu_signals[i] << " events" << endl;
  }



  cout << "------------ Electron channel (after cut: " << cuts << ") ----------" << endl;
  for(unsigned int i=0; i<backgrounds.size(); i++) {
    cout << "Background " << backgrounds[i] << ": " << N_events_e_backgrounds[i] << " events" << endl;
  }
  for(unsigned int i=0; i<signals.size(); i++) {
    cout << "Signal " << signals[i] << ": " << N_events_e_signals[i] << " events" << endl;
  }



}
