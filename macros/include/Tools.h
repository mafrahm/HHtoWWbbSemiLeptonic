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
  void Efficiencies(TString channel);
  void ControlPlots(TString selection, TString cuts, vector<TString> processes);
  void SignalToBackground(TString cuts, TString plotname);
  void CountBackgroundContributions(TString channel, TString region);
  void CountBackgroundContributions();
  void CountBackgroundDistribution();

  vector<double> findScaleRescaleValues(TString process);
  vector<double> findPDFRescaleValues(TString process);
  void FindRMS(TString infolder, map<TString, TString> samplemap, TString sample);
  void ScaleVariationEnvelope();
  void PDFRMS();

  

  void FindOptimizeBinning(int N_bins, TString signal, vector<TString> backgrounds, TString region, bool flat_in_background);
  TH1F* ApplyOptimizeBinning(TH1F *hist, TString channel, TString proc);
  TH1F* ApplyOptimizeBinning(TH1F *hist, vector<double> bins);
  void ProduceCombineHistograms();
  void ProduceCombineHistogramsNN(bool use_data);
  void ProduceCombineHistogramsSimple(bool use_data);
  void GetHistogramsForSystHists(TString histname_base);
  void ConvertShapeToRate();

  void CombineHistogramsRMS();

  void PlotSystematicHists(bool combine_hist=true);
  
  // only after running NNsteer.py
  void PlotLimitsCombine(TString channel);
  void PlotPostfitDistribution(bool do_prefit=false, bool scale_to_width=false);



 private:
  TString base_path, uhh2_path, combine_path;
  TString pre_tag, full_tag, NN_tag;
  TString channel, NN_channel, ptjet, nnmodel;
  TString year;
  TString yeartag;

  TString combineInputName_allShape, combineInputName_rateShape, histsForSyst_name;


  TString signal_tag;
  vector<TString> backgrounds_tag;
  vector<TString> main_backgrounds_tag;

  map<const TString, Color_t> proc_colors;
  map<TString, TString> channel_to_histname;
  map<TString, TString> channel_to_node;
  map<TString, vector<double>> channel_to_bins;
  map<TString, TString> channel_to_chNumber;
  map<TString,TString> channel_to_xAxisTitle;

  // bool debug;
};
