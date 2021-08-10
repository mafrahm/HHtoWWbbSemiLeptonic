 #include <TString.h>
#include <TFile.h>
#include <iostream>

#include "../include/Tools.h"

using namespace std;

AnalysisTool::AnalysisTool(int year_) {
  base_path = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/";
  uhh2_path = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/";
  //combine_path ="../data/datacards/";
  combine_path = "/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/datacards/";
  pre_tag = "Preselection/";
  full_tag = "Fullselection/";
  NN_tag = "NNApplied/";


  year = "";
  year += year_;
  yeartag = "";
  if(year == "2016") yeartag = "2016v3";
  else if (year == "2017") yeartag = "2017v2";
  else if (year == "2018") yeartag = "2018";
  else throw runtime_error("Invalid year_ specified");


  // processes
  signal_tag = "HHtoWWbbSemiLeptonic_SM";
  backgrounds_tag = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  main_backgrounds_tag = {"TTbar", "DYJets", "WJets"};

  //colors
  proc_colors = {
    {"HHtoWWbbSemiLeptonic_SM", 1},
    {"DATA_Muon", 1},
    {"TTbar", 810},
    {"DYJets", 798},
    {"QCDMu", 867},
    {"QCD", 867},
    {"Diboson", 860},
    {"SingleTop", 801},
    {"TTV", 413},
    {"WJets", 613}
  };

}
