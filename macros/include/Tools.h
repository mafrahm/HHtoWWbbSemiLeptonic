#pragma once

#include <cmath>
#include <map>
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>
//#include <THStack>



using namespace std;

class AnalysisTool {

public:

  // Constructors, destructor
  AnalysisTool(int year_);
  AnalysisTool(const AnalysisTool &) = default;
  AnalysisTool & operator = (const AnalysisTool &) = default;
  ~AnalysisTool() = default;

  // Main functions
  void Efficiencies(TString selection, TString cuts, vector<TString> processes);
  void ControlPlots(TString selection, TString cuts, vector<TString> processes);
  void SignalToBackground(TString cuts, TString plotname);


  void ScaleVariationEnvelope();
  void PDFRMS();

  void ProduceCombineHistograms();
  void ProduceCombineHistogramsNN();

  void PlotSystematicHists();
  
  // only after running NNsteer.py
  void PlotLimitsCombine(TString channel);
  void PlotPostfitDistribution(bool do_prefit=false);


private:
  TString base_path, uhh2_path, combine_path;
  TString pre_tag, full_tag, NN_tag;
  TString run;
  TString year;
  TString yeartag;
  map<char,int> test;

  TString signal_tag;
  vector<TString> backgrounds_tag;
  vector<TString> main_backgrounds_tag;

  map<const TString, Color_t> proc_colors;




};
