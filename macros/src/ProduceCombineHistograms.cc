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

void AnalysisTool::ProduceCombineHistograms(){
  cout << "ProduceCombinedHistograms:"<< endl;
  cout << "year: " << AnalysisTool::yeartag << endl;

  

    /*
      limits: chi2,chi2
      limits1: highPt,chi2
      limits2: highPt,highPt
      limits3: highPt,lowPt
    */
  vector<TString> systematics = {"NOMINAL"};
  vector<TString> region_tags = {"catA"};
  vector<TString> channel_tags = {"srmu", "srele"};
  //vector<TString> channel_tags = {"srmu"};
  vector<TString> histinname_base = {"Mbb_vs_MWW_limits2"};
  vector<TString> histoutname_base = {"mH"};
  vector<TString> samples_base = {"HHtoWWbbSemiLeptonic_SM", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets", "DATA"};

  TString outfilename = AnalysisTool::combine_path + "input/combine_histograms_" + AnalysisTool::year + ".root"; 
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
	TString infilename_base = AnalysisTool::base_path  + AnalysisTool::year + "/" + full_tag + syst + "/uhh2.AnalysisModuleRunner."; // should be inside systematics loop

	// for(unsigned int j=0; j<systshift.size(); j++)
	for(unsigned int i=0; i<samples_base.size(); i++) {
	  TString proc = samples_base[i];
	  // change qcd and data to required input name
	  if (proc == "DATA") {
	    if(channel_tags[channel] == "srele") proc += "_Electron";
	    else proc += "_Muon";
	  }
	  if (proc == "QCD") {
	    if(channel_tags[channel] == "srele") proc += "Ele";
	    else proc += "Mu";
	  }
	  cout << "======= Sample " << proc << endl;
	  TString tag = "MC.";
	  if(proc.Contains("DATA")) tag ="DATA.";
	  TString infilename = infilename_base + tag + proc + "_" + yeartag + ".root";
	  TFile* f_in = new TFile(infilename);
	  TString histname = "mHH_reconstructed_" + channel_tags[channel] + "_General/" + histinname_base[region];  
	  TH2F* h_in = (TH2F*) f_in->Get(histname); // unroll

	  TH1F* h_out = new TH1F("h_out", histoutname_base[region], (h_in->GetNbinsX()+2)*(h_in->GetNbinsY()+2), -0.5, (h_in->GetNbinsX()+2)*(h_in->GetNbinsY()+2)+0.5);
	  for(int a=0; a<h_in->GetNbinsX()+2; a++) {
	    cout << " >>>>>>>>>>>>>>  a=" << a << endl;
	    for(int b=0; b<h_in->GetNbinsY()+2; b++) {
	      cout << " >>>>>>>>  b=" << b << endl;
	      int bin = h_in->GetBin(a,b);
	      
	      cout << "bin: " << bin << endl;
	      //cout << "true bin: " << bin-13-2*b << endl;
	      cout << "content: " << h_in->GetBinContent(bin) << endl;
	      
	      h_out->SetBinContent(bin, h_in->GetBinContent(bin));
	      //h_out->SetBinContent(bin-13-2*b, h_in->GetBinContent(bin));

	    }
	  }
	  // unrolling done

	  //if(proc.Contains("HHtoWWbb")) h_out->Scale(10.);
	  //h_out->Scale(3.8);

	  // change data and qcd to the required output name
	  if(proc.Contains("DATA")) proc = "data_obs";
	  if(proc.Contains("QCD")) proc = "QCD";
	  TString histname_out = histoutname_base[region] + "_" + channel_tags[channel] + "_" + region_tags[region] + "__" + proc + "_" + AnalysisTool::yeartag;

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
