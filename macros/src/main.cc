#include <cmath>
#include <iostream>
#include "../include/Tools.h"
#include <TString.h>

using namespace std;

int main(){
  cout << "Hello from main()." << endl;

  AnalysisTool Analysis16(2016);
  AnalysisTool Analysis17(2017);
  AnalysisTool Analysis18(2018);


  // analysis of the Pre-Selection

  TString selection = "Preselection";
  TString cutsJet10 = "mu24jet10";
  //TString cutsLep5 = "e05mu05eta5";
  TString cutsLep5 = "jet30lep5";
  vector<TString> allProcesses = {"HHtoWWbbSemiLeptonic_SM",/* "DATA_Muon",*/ "TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  // vector<TString> someProcesses = {"HHtoWWbbSemiLeptonic_SM", "TTbar", "DYJets", "QCDMu"};
  vector<TString> someProcesses = {"HHtoWWbbSemiLeptonic_SM", "TTbar", "DYJets", "WJets", "QCDMu"};

  //Analysis16.Efficiencies(selection, cutsJet10, someProcesses);
  //Analysis16.ControlPlots(selection, cutsJet10, someProcesses);
  //Analysis16.ControlPlots(selection, cutsLep5, someProcesses);


  //TString plot_ptJet3 = "1MuonCategory_General/pt_jet3";
  TString plot_ptJet3 = "1MuonCategory_General/pt_jet3";
  TString plot_ptJet4 = "1MuonCategory_General/pt_jet4";
  //TString plot_ptMu = "Cleaner_General/pt_mu";
  //TString plot_ptMu = "3Jets_General/pt_mu";
  TString plot_ptMu = "1Bjet_General/pt_mu_rebin";


  //  Analysis16.SignalToBackground(cutsJet10, plot_ptJet3);
  //  Analysis16.SignalToBackground(cutsJet10, plot_ptJet3);
  //  Analysis16.SignalToBackground(cutsLep5, plot_ptMu);


  //Analysis16.ScaleVariationEnvelope();
  //Analysis16.PDFRMS();

  //Analysis16.ProduceCombineHistograms();
  //Analysis16.ProduceCombineHistogramsNN();
 

  //Analysis16.PlotSystematicHists();


  Analysis16.PlotLimitsCombine("comb");
  //Analysis16.PlotPostfitDistribution();
  //Analysis16.PlotPostfitDistribution(true);


  cout << "Finished main(). cya." << endl;
}
