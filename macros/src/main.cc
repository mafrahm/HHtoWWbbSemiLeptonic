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

  vector<TString> backgrounds_mu = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_mu, "srmuch", false); 
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_mu, "ttcrmuch", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_mu, "wdycrmuch", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_mu, "stcrmuch", true);
  //Analysis16.FindOptimizeBinning(3, "QCDMu", backgrounds_mu, "qcdcrmuch", true);

  vector<TString> backgrounds_ele = {"TTbar", "DYJets", "QCDEle", "Diboson", "SingleTop", "TTV", "WJets"};
  Analysis16.FindOptimizeBinning(15, "HHtoWWbbSL_cHHH1", backgrounds_ele, "srech", false);
  Analysis16.FindOptimizeBinning(3, "TTbar", backgrounds_ele, "ttcrech", true);
  Analysis16.FindOptimizeBinning(3, "WJets", backgrounds_ele, "wdycrech", true);
  Analysis16.FindOptimizeBinning(3, "SingleTop", backgrounds_ele, "stcrech", true);
  //Analysis16.FindOptimizeBinning(3, "QCDEle", backgrounds_ele, "qcdcrech", true);


  // Analysis16.ScaleVariationEnvelope();
  // Analysis16.PDFRMS();
 
  Analysis16.ProduceCombineHistogramsNN(false);
 

  // Analysis16.PlotSystematicHists();


  // Analysis16.PlotLimitsCombine("comb");
  // Analysis16.PlotPostfitDistribution();
  // Analysis16.PlotPostfitDistribution(true);

 
  cout << "Finished main(). cya." << endl; 
}
