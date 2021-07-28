#pragma once

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TFile.h>
#include <map>

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

  void ProduceCombineHistograms();
  void ProduceCombineHistogramsNN();

private:
  TString base_path, pre_tag, full_tag, NN_tag, uhh2_path, combine_path;
  TString year;
  TString yeartag;
  map<char,int> test;

  TString signal_tag;
  vector<TString> backgrounds_tag;
  vector<TString> main_backgrounds_tag;

  map<const TString, Color_t> proc_colors;




};
