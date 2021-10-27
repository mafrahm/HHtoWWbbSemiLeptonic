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

  channel = "Inclusive";
  NN_channel = "Inclusive";
  //NN_channel = "Inclusive";
  ptjet = "30";
  // TrainOn = "50";
  nnmodel = "bkgweightX8_removeQCD_classes4_TrainOn30";

  pre_tag = "Preselection/"+channel+"_PTJet"+ptjet+"/";
  full_tag = "Fullselection/"+channel+"_PTJet"+ptjet; //+"_TrainOn50/";
  NN_tag = "NNApplication/"+NN_channel+"_PTJet"+ptjet+"_NN"+nnmodel+"/";

  year = "";
  year += year_;
  yeartag = "";
  if(year == "2016") yeartag = "2016v3";
  else if (year == "2017") yeartag = "2017v2";
  else if (year == "2018") yeartag = "2018";
  else throw runtime_error("Invalid year_ specified");

  combineInputName_allShape = combine_path + "input/combineAllShape_" + NN_channel + "_NN" + nnmodel + "_" + AnalysisTool::year + ".root";
  combineInputName_rateShape = combine_path + "input/combineRateShape_" + NN_channel + "_NN" + nnmodel + "_" + AnalysisTool::year + ".root";

  histsForSyst_name = combine_path + "input/histsForSyst_PTJet" + ptjet + "_NN" + nnmodel + "_" + AnalysisTool::year + ".root";

  // processes
  signal_tag = "HHtoWWbbSemiLeptonic_SM";
  backgrounds_tag = {"TTbar", "DYJets", "QCDMu", "Diboson", "SingleTop", "TTV", "WJets"};
  main_backgrounds_tag = {"TTbar", "DYJets", "WJets"};

  //colors
  proc_colors = {
    {"HHtoWWbbSemiLeptonic_SM", 1},
    {"HHtoWWbbSL_cHHH0", 319},
    {"HHtoWWbbSL_cHHH1", 1},
    {"HHtoWWbbSL_cHHH2p45", 901},
    {"HHtoWWbbSL_cHHH5", 956},
    {"DATA_Muon", 1},
    {"TTbar", 810},
    {"DYJets", 798},
    {"QCDMu", 867},
    {"QCDEle", 867},
    {"QCD", 867},
    {"Diboson", 860},
    {"SingleTop", 801},
    {"TTV", 413},
    {"WJets", 613}
  };

  /*
  channel_to_histname = {
    {"srmuch", "much_DNNoutput0_nominal/NN_out0"},
    {"ttcrmuch", "much_DNNoutput1_nominal/NN_out1"},
    {"stcrmuch", "much_DNNoutput2_nominal/NN_out2"},
    {"wdycrmuch", "much_DNNoutput3_nominal/NN_out3"},
    //{"qcdcrmuch", "much_DNNoutput4_nominal/NN_out4"},
    {"srech", "ech_DNNoutput0_nominal/NN_out0"},
    {"ttcrech", "ech_DNNoutput1_nominal/NN_out1"},
    {"stcrech", "ech_DNNoutput2_nominal/NN_out2"},
    {"wdycrech", "ech_DNNoutput3_nominal/NN_out3"},
    //{"qcdcrech", "ech_DNNoutput4_nominal/NN_out4"}
  };
  */
  channel_to_histname = {
    {"srmuch", "much_DNNoutput0_nominal/max_NN_out"},
    {"ttcrmuch", "much_DNNoutput1_nominal/max_NN_out"},
    {"stcrmuch", "much_DNNoutput2_nominal/max_NN_out"},
    {"wdycrmuch", "much_DNNoutput3_nominal/max_NN_out"},
    //{"qcdcrmuch", "much_DNNoutput4_nominal/max_NN_out"},
    {"srech", "ech_DNNoutput0_nominal/max_NN_out"},
    {"ttcrech", "ech_DNNoutput1_nominal/max_NN_out"},
    {"stcrech", "ech_DNNoutput2_nominal/max_NN_out"},
    {"wdycrech", "ech_DNNoutput3_nominal/max_NN_out"},
    //{"qcdcrech", "ech_DNNoutput4_nominal/max_NN_out"}
  };

  channel_to_node = {
    {"srmuch", "much_DNNoutput0"},
    {"ttcrmuch", "much_DNNoutput1"},
    {"stcrmuch", "much_DNNoutput2"},
    {"wdycrmuch", "much_DNNoutput3"},
    {"qcdcrmuch", "much_DNNoutput4"},
    {"srech", "ech_DNNoutput0"},
    {"ttcrech", "ech_DNNoutput1"},
    {"stcrech", "ech_DNNoutput2"},
    {"wdycrech", "ech_DNNoutput3"},
    {"qcdcrech", "ech_DNNoutput4"}
};

  channel_to_xAxisTitle = {
    {"srmuch", "Signal Region output node (much)"},
    {"ttcrmuch", "TTbar CR output node (much)"},
    {"stcrmuch", "SingleTop CR output node (much)"},
    {"wdycrmuch", "W+DY CR output node (much)"},
    {"srech", "Signal Region output node (ech)"},
    {"ttcrech", "TTbar CR output node (ech)"},
    {"stcrech", "SingleTop CR output node (ech)"},
    {"wdycrech", "W+DY CR output node (ech)"}
  };

  
  /*
  channel_to_chNumber = {
    {"ch1", "srmuch"},
    {"ch2", "srech"},
  };
  */
  
  channel_to_chNumber = {
    {"ch1", "srmuch"},
    {"ch2", "ttcrmuch"},
    {"ch3", "stcrmuch"},
    {"ch4", "wdycrmuch"},
    {"ch5", "srech"},
    {"ch6", "ttcrech"},
    {"ch7", "stcrech"},
    {"ch8", "wdycrech"},
  };
  
  /*
  channel_to_chNumber = {
    {"ch1", "srmuch"},
    {"ch2", "ttcrmuch"},
    {"ch3", "stcrmuch"},
    {"ch4", "wdycrmuch"},
    {"ch5", "qcdcrmuch"},
    {"ch6", "srech"},
    {"ch7", "ttcrech"},
    {"ch8", "stcrech"},
    {"ch9", "wdycrech"},
    {"ch10", "qcdcrech"},
  };
  */
  //debug = false;
  
}
