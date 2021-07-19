#include "../include/Tools.h"

#include <cmath>
#include <iostream>
#include <TString.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>


using namespace std;

// this is my very sloppy script to make efficiency plots
void AnalysisTool::SignalToBackground(TString cuts, TString plotname) {

  cout << "hey there, general Kenobi!" << endl;
  cout << "Line: " << __LINE__ << endl;

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/" + pre_tag + cuts + "/uhh2.AnalysisModuleRunner.";
  TString tag = "MC."; // no data included

  // get signal
  TString infilename_sig = filename + tag + signal_tag + "_" + yeartag + ".root";
  TFile* infile_sig = new TFile(infilename_sig);
  cout << "Infilename Signal: " << infilename_sig << endl;

  TH1F* h_signal = (TH1F*) infile_sig->Get(plotname);
  cout << "Line: " << __LINE__ << endl;


  // get background
  vector<TH1F*> h_backgr;
  for(unsigned int i=0; i<backgrounds_tag.size(); i++) {
    TString proc = backgrounds_tag[i];
    TString infilename_backgr = filename + tag + proc + "_" + yeartag + ".root";
    TFile* infile_backgr = new TFile(infilename_backgr);
    TH1F* h_backgr_in = (TH1F*) infile_backgr->Get(plotname);
    h_backgr.push_back(h_backgr_in);
  }
  
  cout << "Line: " << __LINE__ << endl;



  // prepare plotting
  int n_bins = h_signal->GetNbinsX();
  int min = h_signal->GetBinLowEdge(1);
  int max = h_signal->GetBinLowEdge(n_bins+2);
  cout << "total number of bins: " << n_bins << endl;

  // cosmetics
  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TH1F* h_out1 = new TH1F("h_out", "S/#sqrt{B}", n_bins, min, max);
  TH1F* h_out2 = new TH1F("h_out", "S/B", n_bins, min, max);
  h_out1->SetAxisRange(10., 100.);
  h_out2->SetAxisRange(10., 100.);

  h_out1->SetYTitle("S/#sqrt{B}");
  h_out2->SetYTitle("S/B");

  if(plotname.Contains("pt_jet")) {
  h_out1->SetXTitle("p_{T,min}^{Jets}");
  h_out2->SetXTitle("p_{T,min}^{Jets}");
  }
  else if(plotname.Contains("pt_mu")) {
  h_out1->SetXTitle("p_{T,min}^{#mu}");
  h_out2->SetXTitle("p_{T,min}^{#mu}");
  }

  h_out1->SetTitle("");
  h_out2->SetTitle("");
  h_out1->SetStats(0);
  h_out2->SetStats(0);

  // CMS Text

  bool right = true; // CMS text on the right side
  TLatex *text2 = new TLatex(3.5, 24, "CMS");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.24);
  if(right) text2->SetX(0.7);
  text2->SetTextFont(62);
  text2->SetTextSize(0.05);
  //text2->SetY(0.87);
  text2->SetY(0.92);
  text2->Draw();

  TLatex *text3 = new TLatex(3.5, 24, "Work in progress");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.24);
  if(right) text3->SetX(0.7);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  //text3->SetY(0.78);
  text3->SetY(0.83);
  text3->Draw();

  // Simulation:
  TLatex *text4 = new TLatex(3.5, 24, "Simulation");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.24);
  if(right) text4->SetX(0.7);
  text4->SetTextFont(52);
  text4->SetTextSize(0.035);
  //text4->SetY(0.82);
  text4->SetY(0.87);
  text4->Draw();



  // loop over all bins;
  for(int i=1; i<n_bins+1; i++) {
    float bin = h_signal->GetBinLowEdge(i);
    cout << "bin low edge: " << bin << endl;
    float S = h_signal->Integral(i,n_bins);
    //cout << S << endl;
    float B = 0;
    for(unsigned int j=0; j<h_backgr.size(); j++) {
      B+= h_backgr[j]->Integral(i,n_bins);
    }
    //cout << B << endl;
    cout << "S/sqrt(B): " << S/sqrt(B) << endl;
    h_out1->SetBinContent(i, S/sqrt(B));
    h_out2->SetBinContent(i, S/B);
  }
  c1->SetLeftMargin(0.16);
  c1->cd();
  h_out1->Draw("HIST");
  c1->SaveAs(uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/sigToSqrtBackgr_" + year + "_" + cuts + ".eps");
  c1->Clear();
  h_out2->Draw("HIST");
  c1->SaveAs(uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/sigToBackgr_" + year + "_" + cuts + ".eps");


  cout << "Line: " << __LINE__ << endl;


}
