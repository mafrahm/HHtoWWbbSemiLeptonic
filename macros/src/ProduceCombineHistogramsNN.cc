#include "../include/cosmetics.h"
#include "../include/Tools.h"
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
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>

using namespace std;

void AnalysisTool::ProduceCombineHistogramsNN(){
  cout << "ProduceCombinedHistograms:"<< endl;
  cout << "year: " << AnalysisTool::yeartag << endl;
  cout << "Line: " << __LINE__ << endl;


  vector<TString> systematics = {"NOMINAL"};
  vector<TString> region_tags = {"catA"};
  //vector<TString> channel_tags = {"srmu", "srele"};
  //vector<TString> channel_tags = {"srmu"};
  vector<TString> channel_tags = {"srmu", "ttcrmu", "stcrmu", "wdycrmu"};
  vector<TString> histinname_base = {"DNN_output0_srmu_NNOutput/NN_out0", "DNN_output1_srmu_NNOutput/NN_out1", "DNN_output2_srmu_NNOutput/NN_out2", "DNN_output3_srmu_NNOutput/NN_out3"};
  //vector<TString> histinname_base = {"NN_out0"};
  vector<TString> histoutname_base = {"mH"};
  vector<TString> samples_base = {"HHtoWWbbSemiLeptonic_SM", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets", "DATA"}; //, "DATA"

  TString outfilename = AnalysisTool::combine_path + "input/NN_combine_histograms_" + AnalysisTool::year + ".root"; 
  TFile* f_out = new TFile(outfilename, "RECREATE");

  /*
    for(region)
    for(channel)
    for(systematics)
    for(systshift)
    for(samples)
  */
  for(unsigned int region = 0; region <region_tags.size(); region++) {
    for(unsigned int channel=0; channel<channel_tags.size(); channel++) {
      cout << "============= Channel: " << channel_tags[channel] << ", Region: " << region_tags[region] << endl;
      for(unsigned int k=0; k<systematics.size(); k++) {
	TString syst = systematics[k];
	  cout << "========== Syst: " << syst << endl;
	  TString infilename_base = AnalysisTool::base_path  + AnalysisTool::year + "/" + AnalysisTool::NN_tag + syst + "/uhh2.AnalysisModuleRunner."; // should be inside systematics loop
	cout << infilename_base << endl;
	// for(unsigned int j=0; j<systshift.size(); j++)
	for(unsigned int i=0; i<samples_base.size(); i++) {
	  TString proc = samples_base[i];
	  // change qcd and data to required input name
	  if (proc == "DATA") {
	    if(channel_tags[channel].Contains("ele")) proc += "_Electron";
	    else proc += "_Muon";
	  }
	  if (proc == "QCD") {
	    if(channel_tags[channel].Contains("ele")) proc += "Ele";
	    else proc += "Mu";
	  }
	  cout << "======= Sample " << proc << endl;
	  TString tag = "MC.";
	  if(proc.Contains("DATA")) tag ="DATA.";
	  TString infilename = infilename_base + tag + proc + "_" + yeartag + ".root";	  
	  //cout << infilename << endl;
	  TFile* f_in = new TFile(infilename);
	  //TString histname = "Finalselection_mHH_reconstructed_" + channel_tags[channel] + "_General/" + histinname_base[channel];  
	  //TString histname = "Finalselection_srmu_NNOutput/" + histinname_base[channel];
	  TString histname = histinname_base[channel];
	  //cout << histname << endl;
	  TH1F* h_out = (TH1F*) f_in->Get(histname);
	  //if(proc.Contains("HHtoWWbb")) h_out->Scale(10.);
	  //h_out->Scale(3.8);

	  // change data and qcd to the required output name
	  if(proc.Contains("DATA")) proc = "data_obs";
	  if(proc.Contains("QCD")) proc = "QCD";
	  TString histname_out = histoutname_base[region] + "_" + channel_tags[channel] + "_" + region_tags[region] + "__" + proc + "_" + AnalysisTool::yeartag;
	  //cout << histname_out << endl;

	  h_out->SetName(histname_out);
	  f_out->cd();
	  h_out->Write();
	  f_in->Close();
	}
      }
    }
  }
  
  




  cout << "finished!" << endl;

  
}
