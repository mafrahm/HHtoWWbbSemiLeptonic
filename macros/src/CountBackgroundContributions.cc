#include "../include/cosmetics.h"
#include "../include/Tools.h"

using namespace std;
// TODO: also get these values from NNApplication output (sanity check)
void AnalysisTool::CountBackgroundContributions(TString channel, TString region){
  bool debug = false;

  // save in csv aswell?
  cout << "CountBackgroundContributions: percentage values of each background after Fullselection :-]" << endl;
  cout << "channel: " << channel << ", region: " << region << ", year: " << AnalysisTool::year << endl;

  vector<TString> backgrounds = {"TTbar", "SingleTop", "WJets", "DYJets", "Diboson", "TTV"};
  if(channel=="ech") backgrounds.push_back("QCDEle");
  else if(channel=="much") backgrounds.push_back("QCDMu");
  else throw runtime_error("only channels that are implemented are ech and much :-[");
  if(debug) cout << AnalysisTool::NN_tag << endl;

  //TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::full_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
  TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::NN_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
  // histname from Fullselection
  //TString histname = "NNInputVariables_"+channel+"/sum_event_weights";
  
  
  map<TString,TString> region_to_histtag = {
    {"Inclusive", "Finalselection"},
    {"sr", "DNNoutput0"},
    {"ttcr", "DNNoutput1"},
    {"stcr", "DNNoutput2"},
    {"wdycr", "DNNoutput3"},
    {"qcdcr", "DNNoutput4"}
  };
  if(debug) cout << region_to_histtag[region] << endl;
  TString histname = region_to_histtag[region] + "_" + channel + "_NNInput/sum_event_weights";
  if(debug) cout << histname << endl;
  double N_events_total = 0;
  vector<double> N_events_backgrounds;

  for(unsigned int i=0; i<backgrounds.size(); i++) {
    TString proc = backgrounds[i];
    TString infilename = infilename_base + proc + "_" + yeartag + ".root";
    TFile *f_in = new TFile(infilename);
    double N_events = ((TH1F*)f_in->Get(histname))->Integral();
    
    N_events_total += N_events;
    N_events_backgrounds.push_back(N_events);
    
  }

  for(unsigned int i=0; i<backgrounds.size(); i++) cout << "Background " << backgrounds[i] << " contributes " << 100*N_events_backgrounds[i]/N_events_total << "% to the background in " << region << channel << endl;
}

void AnalysisTool::CountBackgroundContributions(){
  bool debug = false;

  // save in csv aswell?
  cout << "CountBackgroundContributions: percentage values of each background after Fullselection :-]" << endl;

  vector<TString> channels = {"ech", "much"};
  vector<TString> regions = {"Inclusive", "sr", "ttcr", "stcr", "wdycr"};

  for(TString channel: channels) {
    for(TString region: regions) {

      cout << "channel: " << channel << ", region: " << region << ", year: " << AnalysisTool::year << endl;

      vector<TString> backgrounds = {"TTbar", "SingleTop", "WJets", "DYJets", "Diboson", "TTV"};
      if(channel=="ech") backgrounds.push_back("QCDEle");
      else if(channel=="much") backgrounds.push_back("QCDMu");
      else throw runtime_error("only channels that are implemented are ech and much :-[");
      if(debug) cout << AnalysisTool::NN_tag << endl;

      //TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::full_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
      TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::NN_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
      // histname from Fullselection
      //TString histname = "NNInputVariables_"+channel+"/sum_event_weights";
  
  
      map<TString,TString> region_to_histtag = {
	{"Inclusive", "Finalselection"},
	{"sr", "DNNoutput0"},
	{"ttcr", "DNNoutput1"},
	{"stcr", "DNNoutput2"},
	{"wdycr", "DNNoutput3"},
	{"qcdcr", "DNNoutput4"}
      };
      if(debug) cout << region_to_histtag[region] << endl;
      TString histname = region_to_histtag[region] + "_" + channel + "_NNInput/sum_event_weights";
      if(debug) cout << histname << endl;
      double N_events_total = 0;
      vector<double> N_events_backgrounds;

      for(unsigned int i=0; i<backgrounds.size(); i++) {
	TString proc = backgrounds[i];
	TString infilename = infilename_base + proc + "_" + yeartag + ".root";
	TFile *f_in = new TFile(infilename);
	double N_events = ((TH1F*)f_in->Get(histname))->Integral();
    
	N_events_total += N_events;
	N_events_backgrounds.push_back(N_events);
    
      }
      
      

      for(unsigned int i=0; i<backgrounds.size(); i++) {
	cout << "Background " << backgrounds[i] << " contributes " << 100*N_events_backgrounds[i]/N_events_total << "% to the background in " << region << channel << endl;
	cout << "---- "<< N_events_backgrounds[i] << " events from process " << backgrounds[i] << " in " << region << channel << endl;
      }
    }
  }
}

void AnalysisTool::CountBackgroundDistribution(){
  bool debug = false;

  // save in csv aswell?
  cout << "CountBackgroundContributions: percentage values of each background after Fullselection :-]" << endl;

  vector<TString> channels = {"ech", "much"};
  vector<TString> regions = {"Inclusive", "sr", "ttcr", "stcr", "wdycr"};

  for(TString channel: channels) {

      cout << "channel: " << channel << ", year: " << AnalysisTool::year << endl;

      vector<TString> backgrounds = {"HHtoWWbbSL_cHHH1", "TTbar", "SingleTop", "WJets", "DYJets", "Diboson", "TTV"};
      if(channel=="ech") backgrounds.push_back("QCDEle");
      else if(channel=="much") backgrounds.push_back("QCDMu");
      else throw runtime_error("only channels that are implemented are ech and much :-[");
      if(debug) cout << AnalysisTool::NN_tag << endl;

      //TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::full_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
      TString infilename_base = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::NN_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC.";
      // histname from Fullselection
      //TString histname = "NNInputVariables_"+channel+"/sum_event_weights";
  
  
      map<TString,TString> region_to_histtag = {
	{"Inclusive", "Finalselection"},
	{"sr", "DNNoutput0"},
	{"ttcr", "DNNoutput1"},
	{"stcr", "DNNoutput2"},
	{"wdycr", "DNNoutput3"},
	{"qcdcr", "DNNoutput4"}
      };

      for(unsigned int i=0; i<backgrounds.size(); i++) {
	TString proc = backgrounds[i];
	TString infilename = infilename_base + proc + "_" + yeartag + ".root";
	TFile *f_in = new TFile(infilename);

	
	double N_events_total = 0;
	vector<double> N_events_regions;
	for(TString region: regions) {

	  if(debug) cout << region_to_histtag[region] << endl;
	  TString histname = region_to_histtag[region] + "_" + channel + "_NNInput/sum_event_weights";
	  if(debug) cout << histname << endl;
	  
	  double N_events = ((TH1F*)f_in->Get(histname))->Integral();
    
	  if(region!="Inclusive") N_events_total += N_events;
	  N_events_regions.push_back(N_events);
	}

	cout << "Background " << backgrounds[i] << " has " << N_events_total << " in channel " << channel << endl;

	for(unsigned int j=0; j<regions.size(); j++) {
	  cout << 100*N_events_regions[j]/N_events_total << "% of Background " << backgrounds[i] << " in Channel " << channel << " is in Region " << regions[j] << endl;
	}
      }
  }
}
