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

  void FindOptimizeBinning(int N_bins, TString signal, vector<TString> backgrounds, TString region);
  TH1F* ApplyOptimizeBinning(TH1F *hist, vector<double> bins);
  void ProduceCombineHistograms();
  void ProduceCombineHistogramsNN(bool use_data);

  void PlotSystematicHists();
  
  // only after running NNsteer.py
  void PlotLimitsCombine(TString channel);
  void PlotPostfitDistribution(bool do_prefit=false, bool scale_to_width=false);



private:
  TString base_path, uhh2_path, combine_path;
  TString pre_tag, full_tag, NN_tag;
  TString channel, ptjet, nnmodel;
  TString year;
  TString yeartag;

  TString signal_tag;
  vector<TString> backgrounds_tag;
  vector<TString> main_backgrounds_tag;

  //vector<double> srmuch_bins, ttcrmuch_bins, stcrmuch_bins, wdycrmuch_bins, qcdcrmuch_bins, srech_bins, ttcrech_bins, stcrech_bins, wdycrech_bins, qcdcrech_bins;

  map<const TString, Color_t> proc_colors;
  map<TString, TString> channel_to_histname;
  map<TString, vector<double>> channel_to_bins;
  map<TString, TString> channel_to_chNumber;


  // bool debug;
};
