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

void AnalysisTool::SignalToBackgroundPTMu() {
  cout << "hey there, general Kenobi!" << endl;
  cout << "Line: " << __LINE__ << endl;

  bool with_qcd = true;
  vector<TString> backgrounds = {"TTbar", "DYJets", "Diboson", "SingleTop", "TTV", "WJets"};
  if(with_qcd) backgrounds.push_back("QCDMu");
  
  TString cuts = "jet30lep5";
  vector<TString> dirnames = {"1MuonCategory", "3Jets", "1Bjet"};
  vector<Color_t> colors = {1, 810, 867};

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/Preselection/" + cuts + "/uhh2.AnalysisModuleRunner.MC."; // no data included

  // get signal + backgrounds
  TString infilename_sig = filename + signal_tag + "_" + yeartag + ".root";
  TFile* infile_sig = new TFile(infilename_sig);
  cout << "Infilename Signal: " << infilename_sig << endl;

  vector<TH1F*> h_signals;
  vector<vector<TH1F*>> h_vec_backgr;
  for(unsigned int i=0; i<dirnames.size(); i++) {
    TString dir = dirnames[i];
    TString plotname = dir + "_General/pt_mu";
    TH1F* h_sig = (TH1F*) infile_sig->Get(plotname);
    h_signals.push_back(h_sig);
    // get background for this choice of cuts
    vector<TH1F*> h_backgr;
    for(unsigned int j=0; j<backgrounds.size(); j++) {
      TString proc = backgrounds[j];
      TString infilename_backgr = filename + proc + "_" + yeartag + ".root";
      TFile* infile_backgr = new TFile(infilename_backgr);
      TH1F* h_backgr_in = (TH1F*) infile_backgr->Get(plotname);
      h_backgr.push_back(h_backgr_in);
    }
    h_vec_backgr.push_back(h_backgr);
  }
  cout << "Line: " << __LINE__ << endl;


  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);

  TLegend *leg = new TLegend(0.57,0.74,0.90,0.88,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  for(unsigned int i=0; i<dirnames.size(); i++) {
    TString dir = dirnames[i];
    TString plotname = dir + "_General/pt_mu";

    TH1F* h_signal = h_signals[i];
    vector<TH1F*> h_backgr = h_vec_backgr[i];

    // prepare plotting
    int n_bins = h_signal->GetNbinsX();
    int min = h_signal->GetBinLowEdge(1);
    int max = h_signal->GetBinLowEdge(n_bins+2);
    cout << "total number of bins: " << n_bins << endl;

    // cosmetics
    TH1F* h_out1 = new TH1F("h_out", "S/#sqrt{B}", n_bins, min, max);
    TH1F* h_out2 = new TH1F("h_out", "S/B", n_bins, min, max);
    h_out1->SetAxisRange(10., 100.);
    h_out2->SetAxisRange(10., 100.);

    h_out1->SetLineWidth(2.);
    h_out2->SetLineWidth(2.);

    //h_out1->SetMaximum(8e-3);
    //h_out1->SetMinimum(1e-4);
    h_out1->SetMaximum(7e-3);
    h_out1->SetMinimum(0);

    //h_out2->SetMaximum(2e-7);
    //h_out2->SetMinimum(1e-9);
    h_out2->SetMaximum(6e-6);
    h_out2->SetMinimum(0);

    if(!with_qcd) {
      h_out1->SetMaximum(1.05e-2);
      
      h_out2->SetMaximum(6e-6);
    }

    h_out1->SetYTitle("Signal / #sqrt{Background}");
    h_out2->SetYTitle("Signal / Background");

    if(plotname.Contains("pt_jet")) {
      h_out1->SetXTitle("p_{T,min}^{Jets} [GeV]");
      h_out2->SetXTitle("p_{T,min}^{Jets} [GeV]");
    }
    else if(plotname.Contains("pt_mu")) {
      h_out1->SetXTitle("p_{T,min}^{#mu} [GeV]");
      h_out2->SetXTitle("p_{T,min}^{#mu} [GeV]");
    }

    h_out1->SetTitle("");
    h_out2->SetTitle("");
    h_out1->SetStats(0);
    h_out2->SetStats(0);
    h_out1->GetXaxis()->SetTitleSize(.05);
    h_out1->GetYaxis()->SetTitleSize(.05);
    h_out2->GetXaxis()->SetTitleSize(.05);
    h_out2->GetYaxis()->SetTitleSize(.05);
    h_out1->GetXaxis()->SetTitleOffset(1.1);
    h_out2->GetXaxis()->SetTitleOffset(1.1);

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
      cout << "Sig / sqrt(BG): " << S/sqrt(B) << endl;
      h_out1->SetBinContent(i, S/sqrt(B));
      h_out2->SetBinContent(i, S/B);
    }
    
    h_out1->SetLineColor(colors[i]);
    h_out2->SetLineColor(colors[i]);

    TString legtitle;
    if(dir=="1MuonCategory") legtitle= "no additional cuts";
    else if(dir=="3Jets") legtitle= "N_{Jets} #geq 3";
    else if(dir=="1Bjet") legtitle= "N_{Jets} #geq 3, N_{BTag} #geq 1";
    leg->AddEntry(h_out1, legtitle, "L");
    //leg->AddEntry(h_out2, legtitle, "L");

    c1->SetLeftMargin(0.16);
    c1->SetBottomMargin(0.13);
    c1->cd();
    h_out1->Draw("HIST SAME");
    c2->SetLeftMargin(0.16);
    c2->SetBottomMargin(0.13);
    c2->cd();
    h_out2->Draw("HIST SAME");
  }

  // Lumi text
  TString infotext = "35.9 fb^{-1} (13 TeV)";
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.90);
  text1->SetTextFont(42);
  text1->SetTextSize(0.045);
  text1->SetY(0.95);
  // CMS Text
  bool right = false; // CMS text on the right side
  TLatex *text2 = new TLatex(3.5, 24, "CMS");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.24);
  if(right) text2->SetX(0.7);
  text2->SetTextFont(62);
  text2->SetTextSize(0.05);
  text2->SetY(0.87);
  //text2->SetY(0.92);

  TLatex *text3 = new TLatex(3.5, 24, "Work in progress");
  //TLatex *text3 = new TLatex(3.5, 24, "Private work");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.24);
  if(right) text3->SetX(0.7);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  text3->SetY(0.78);
  //text3->SetY(0.83);

  // Simulation:
  TLatex *text4 = new TLatex(3.5, 24, "Simulation");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.24);
  if(right) text4->SetX(0.7);
  text4->SetTextFont(52);
  text4->SetTextSize(0.035);
  text4->SetY(0.82);
  //text4->SetY(0.87);

  TString outfilename = uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/SigToSqrtBackgr_noQCD_"  + "pt_mu" + "__" + year + ".pdf";
  if(with_qcd) outfilename.ReplaceAll("noQCD_","");
  c1->cd();
  text1->Draw();
  text2->Draw();
  text3->Draw();
  text4->Draw();
  //c1->SetLogy();
  leg->Draw();
  c1->SaveAs(outfilename);

  c2->cd();
  text1->Draw();
  text2->Draw();
  text3->Draw();
  text4->Draw();
  //c2->SetLogy();
  leg->Draw();
  c2->SaveAs(outfilename.ReplaceAll("Sqrt",""));


  //TString outfilename = uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/sigToSqrtBackgr_noQCD_" + dirname + "__" + varname + "__" + year + ".pdf";


  cout << "SignaltoBackgroundPTMu: finished! " << endl;
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!  DIFFERENT SCRIPT  !!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void AnalysisTool::SignalToBackgroundPTJet() {
  cout << "hey there, general Kenobi!" << endl;
  cout << "Line: " << __LINE__ << endl;

  bool with_qcd = true;
  vector<TString> backgrounds = {"TTbar", "DYJets", "Diboson", "SingleTop", "TTV", "WJets"};
  if(with_qcd) backgrounds.push_back("QCDMu");
  
  TString cuts = "mu24jet10";
  TString dirname = "1MuonCategory";
  //TString dirname = "1Bjet";
  vector<TString> varnames = {"pt_jet2","pt_jet3","pt_jet4"};
  vector<Color_t> colors = {1, 810, 867};

  TString filename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/" + year + "/Preselection/" + cuts + "/uhh2.AnalysisModuleRunner.MC."; // no data included

  // get signal + backgrounds
  TString infilename_sig = filename + signal_tag + "_" + yeartag + ".root";
  TFile* infile_sig = new TFile(infilename_sig);
  cout << "Infilename Signal: " << infilename_sig << endl;

  vector<TH1F*> h_signals;
  vector<vector<TH1F*>> h_vec_backgr;
  for(int i=0; i<varnames.size(); i++) {
    TString plotname = dirname + "_General/"+varnames[i];
    TH1F* h_sig = (TH1F*) infile_sig->Get(plotname);
    h_signals.push_back(h_sig);
    // get background for this choice of cuts
    vector<TH1F*> h_backgr;
    for(unsigned int j=0; j<backgrounds.size(); j++) {
      TString proc = backgrounds[j];
      TString infilename_backgr = filename + proc + "_" + yeartag + ".root";
      TFile* infile_backgr = new TFile(infilename_backgr);
      TH1F* h_backgr_in = (TH1F*) infile_backgr->Get(plotname);
      h_backgr.push_back(h_backgr_in);
    }
    h_vec_backgr.push_back(h_backgr);
  }
  cout << "Line: " << __LINE__ << endl;


  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);

  TLegend *leg = new TLegend(0.57,0.74,0.90,0.88,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  for(unsigned int i=0; i<varnames.size(); i++) {
    TString varname = varnames[i];
    TString plotname = dirname + "_General/"+varname;

    TH1F* h_signal = h_signals[i];
    vector<TH1F*> h_backgr = h_vec_backgr[i];

    // prepare plotting
    int n_bins = h_signal->GetNbinsX();
    int min = h_signal->GetBinLowEdge(1);
    int max = h_signal->GetBinLowEdge(n_bins+2);
    cout << "total number of bins: " << n_bins << endl;

    // cosmetics
    TH1F* h_out1 = new TH1F("h_out", "S/#sqrt{B}", n_bins, min, max);
    TH1F* h_out2 = new TH1F("h_out", "S/B", n_bins, min, max);
    h_out1->SetAxisRange(10., 100.);
    h_out2->SetAxisRange(10., 100.);

    h_out1->SetLineWidth(2.);
    h_out2->SetLineWidth(2.);

    //h_out1->SetMaximum(8e-3);
    //h_out1->SetMinimum(1e-4);
    h_out1->SetMaximum(6e-3);
    h_out1->SetMinimum(0);

    //h_out2->SetMaximum(2e-7);
    //h_out2->SetMinimum(1e-9);
    h_out2->SetMaximum(8.5e-6);
    h_out2->SetMinimum(0);

    h_out1->GetXaxis()->SetTitleSize(.05);
    h_out1->GetYaxis()->SetTitleSize(.05);
    h_out2->GetXaxis()->SetTitleSize(.05);
    h_out2->GetYaxis()->SetTitleSize(.05);
    h_out1->GetXaxis()->SetTitleOffset(1.1);
    h_out2->GetXaxis()->SetTitleOffset(1.1);

    if(!with_qcd) {
      h_out1->SetMaximum(7e-3);
      
      h_out2->SetMaximum(1e-5);
    }

    h_out1->SetYTitle("Signal / #sqrt{Background}");
    h_out2->SetYTitle("Signal / Background");

    if(plotname.Contains("pt_jet")) {
      h_out1->SetXTitle("p_{T,min}^{jets} [GeV]");
      h_out2->SetXTitle("p_{T,min}^{jets} [GeV]");
    }
    else if(plotname.Contains("pt_mu")) {
      h_out1->SetXTitle("p_{T,min}^{#mu} [GeV]");
      h_out2->SetXTitle("p_{T,min}^{#mu} [GeV]");
    }

    h_out1->SetTitle("");
    h_out2->SetTitle("");
    h_out1->SetStats(0);
    h_out2->SetStats(0);

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
      cout << "Sig / sqrt(BG): " << S/sqrt(B) << endl;
      h_out1->SetBinContent(i, S/sqrt(B));
      h_out2->SetBinContent(i, S/B);
    }
    
    h_out1->SetLineColor(colors[i]);
    h_out2->SetLineColor(colors[i]);

    TString legtitle = "N_{Jets} #geq " + varname;
    legtitle.ReplaceAll("pt_jet","");
    leg->AddEntry(h_out1, legtitle, "L");

    c1->SetLeftMargin(0.16);
    c1->SetBottomMargin(0.13);
    c1->cd();
    h_out1->Draw("HIST SAME");
    c2->SetLeftMargin(0.16);
    c2->SetBottomMargin(0.13);
    c2->cd();
    h_out2->Draw("HIST SAME");
  }

  // Lumi text
  TString infotext = "35.9 fb^{-1} (13 TeV)";
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.90);
  text1->SetTextFont(42);
  text1->SetTextSize(0.045);
  text1->SetY(0.95);
  // CMS Text
  bool right = false; // CMS text on the right side
  TLatex *text2 = new TLatex(3.5, 24, "CMS");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.24);
  if(right) text2->SetX(0.7);
  text2->SetTextFont(62);
  text2->SetTextSize(0.05);
  text2->SetY(0.87);
  //text2->SetY(0.92);

  TLatex *text3 = new TLatex(3.5, 24, "Work in progress");
  //TLatex *text3 = new TLatex(3.5, 24, "Private work");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.24);
  if(right) text3->SetX(0.7);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  text3->SetY(0.78);
  //text3->SetY(0.83);

  // Simulation:
  TLatex *text4 = new TLatex(3.5, 24, "Simulation");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.24);
  if(right) text4->SetX(0.7);
  text4->SetTextFont(52);
  text4->SetTextSize(0.035);
  text4->SetY(0.82);
  //text4->SetY(0.87);

  TString outfilename = uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/SigToSqrtBackgr_noQCD_"  + "pt_jets" + "__" + year + ".pdf";
  if(with_qcd) outfilename.ReplaceAll("noQCD_","");
  c1->cd();
  text1->Draw();
  text2->Draw();
  text3->Draw();
  text4->Draw();
  //c1->SetLogy();
  leg->Draw();
  c1->SaveAs(outfilename);

  c2->cd();
  text1->Draw();
  text2->Draw();
  text3->Draw();
  text4->Draw();
  //c2->SetLogy();
  leg->Draw();
  c2->SaveAs(outfilename.ReplaceAll("Sqrt",""));

  cout << "SignaltoBackgroundPTJets: finished! " << endl;
}
