#include <cmath>
#include <iostream>
#include "../include/Tools.h"
#include <TString.h>

using namespace std;

void run2016Analysis();
void fullRun2Analysis();

void run2016Plots();
void fullRun2Plots();

void stuff();

int main(){
  cout << "Hello from main()." << endl;

  AnalysisTool Analysis16(2016);
  AnalysisTool Analysis17(2017);
  AnalysisTool Analysis18(2018);
  AnalysisTool AnalysisRun2(2019); // dirty hack: input variable is int; just use 2019 as tag for full RUN2 (see in Tools.cc)

  vector<TString> backgrounds_mu = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  vector<TString> backgrounds_ele = {"TTbar", "DYJets", "QCDEle", "Diboson", "SingleTop", "TTV", "WJets"};

  //run2016Analysis();
  run2016Plots();

  //stuff();

  //fullRun2Analysis();
  //fullRun2Plots();



  cout << "Finished main(). cya." << endl; 
}

void run2016Analysis() {
  AnalysisTool Analysis16(2016);
  vector<TString> backgrounds_mu = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  vector<TString> backgrounds_ele = {"TTbar", "DYJets", "QCDEle", "Diboson", "SingleTop", "TTV", "WJets"};
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis16.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);
  
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis16.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);
  
  Analysis16.ScaleVariationEnvelope();
  Analysis16.PDFRMS();
  Analysis16.ProduceCombineHistogramsNN(false); // true = using real data
  Analysis16.ConvertShapeToRate();
}

void run2016Plots() {
  AnalysisTool Analysis16(2016);
  vector<TString> backgrounds_mu = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  vector<TString> backgrounds_ele = {"TTbar", "DYJets", "QCDEle", "Diboson", "SingleTop", "TTV", "WJets"};
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis16.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);
  
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis16.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);

  Analysis16.PlotSystematicHists(false); // hists before shapeToRate
  Analysis16.PlotSystematicHists(true);    // hists after  shapeToRate

  // Get systematic variation hists for different variables
  //Analysis16.GetHistogramsForSystHists("HT"); // "N_Ak4", "Ak4_j1_pt", "Lep_pt", "HT", "mbb", ...
  //Analysis16.PlotSystematicHists(false,false);


  // only after running combine
  //Analysis16.PlotLimitsCombine("comb"); // the "comb" tag has no meaning
  //Analysis16.PlotPostfitDistribution(true); // Prefit
  //Analysis16.PlotPostfitDistribution();     // Postfit

}

void fullRun2Analysis() {
  AnalysisTool Analysis16(2016);
  AnalysisTool Analysis17(2017);
  AnalysisTool Analysis18(2018);
  AnalysisTool AnalysisRun2(2019); // dirty hack: input variable is int; just use 2019 as tag for full RUN2 (see in Tools.cc)
  // +++++++ preparing Run2 combine +++++++
  vector<TString> backgrounds_mu = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  vector<TString> backgrounds_ele = {"TTbar", "DYJets", "QCDEle", "Diboson", "SingleTop", "TTV", "WJets"};
  /*
  // optimize on full Run2 binning and then apply this binning to each year
  AnalysisRun2.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  AnalysisRun2.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  AnalysisRun2.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  AnalysisRun2.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //AnalysisRun2.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);

  AnalysisRun2.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  AnalysisRun2.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  AnalysisRun2.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  AnalysisRun2.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //AnalysisRun2.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);

  cout << __LINE__ << endl;
  // copy channel_to_bins map into each 'Analysis'
  Analysis16.channel_to_bins = AnalysisRun2.channel_to_bins;
  Analysis17.channel_to_bins = AnalysisRun2.channel_to_bins;
  Analysis18.channel_to_bins = AnalysisRun2.channel_to_bins;
  */
  // +++++++ preparing 2016 combine +++++++

  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis16.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);
  
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis16.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);

  // Re-run all 4 modules after changing binning
  Analysis16.ScaleVariationEnvelope();
  Analysis16.PDFRMS();
  Analysis16.ProduceCombineHistogramsNN(false); // true = using real data
  Analysis16.ConvertShapeToRate();
  
  // +++++++ preparing 2017 combine +++++++
  
  Analysis17.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis17.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis17.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis17.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis17.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);
  
  Analysis17.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis17.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis17.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis17.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis17.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);

  // Re-run all 4 modules after changing binning
  Analysis17.ScaleVariationEnvelope();
  Analysis17.PDFRMS();
  Analysis17.ProduceCombineHistogramsNN(false); // true = using real data
  Analysis17.ConvertShapeToRate();
  
  // +++++++ preparing 2018 combine +++++++
  
  Analysis18.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis18.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis18.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis18.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis18.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);
  
  Analysis18.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis18.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis18.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis18.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis18.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);
  // Re-run all 4 modules after changing binning
  Analysis18.ScaleVariationEnvelope();
  Analysis18.PDFRMS();
  Analysis18.ProduceCombineHistogramsNN(false); // true = using real data
  Analysis18.ConvertShapeToRate();
}





void stuff() {
  AnalysisTool Analysis16(2016);
  AnalysisTool Analysis17(2017);
  AnalysisTool Analysis18(2018);
  
  Analysis16.SignalToBackgroundPTMu();
  Analysis16.SignalToBackgroundPTJet();

  /*
  Analysis16.SignalToBackground("jet30lep5", "Cleaner_General/pt_mu");
  Analysis16.SignalToBackground("jet30lep5", "1MuonCategory_General/pt_mu");
  Analysis16.SignalToBackground("jet30lep5", "3Jets_General/pt_mu");
  Analysis16.SignalToBackground("jet30lep5", "1Bjet_General/pt_mu");

  Analysis16.SignalToBackground("mu24jet10", "1MuonCategory_General/pt_jet2");
  Analysis16.SignalToBackground("mu24jet10", "1MuonCategory_General/pt_jet3");
  Analysis16.SignalToBackground("mu24jet10", "1MuonCategory_General/pt_jet4");
  */
  

  Analysis16.Efficiencies("ech");
  Analysis16.Efficiencies("much");
  /*
  Analysis17.Efficiencies("ech");
  Analysis17.Efficiencies("much");
  Analysis18.Efficiencies("ech");
  Analysis18.Efficiencies("much");
  */
  /*
  Analysis16.CountBackgroundContributions();
  Analysis16.CountBackgroundDistribution();
  */
}

