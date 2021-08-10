#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
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

void AnalysisTool::PlotSystematicHists(){

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = 2002;


  TString outdir = AnalysisTool::base_path + AnalysisTool::year + "/SystematicHists/";
  //TString srtag = "withcrs";
  //if(!use_crs) srtag = "sronly";

  // Open File
  // ==========
  TString infilename = AnalysisTool::combine_path + "input/NN_combine_histograms_" + AnalysisTool::year + ".root";

  cout << "infilename: " << infilename << endl;
  TFile* infile = new TFile(infilename, "READ");

  // Get histograms (only TH1), tokenize them to get all vars, processes, systs
  // ==========================================================================

  TDirectory* dir = gDirectory;
  TIter iter = dir->GetListOfKeys();
  TKey* key;

  // Lists of variable names, processes, systematics
  vector<TString> varnames, procnames;
  map<TString, vector<TString>> systs_for_procs;

  // Loop over all objects in this dir
  while ((key = (TKey*)iter())) {
    TString myclass = "TH1F";

    // Consider only TH1F objects
    if(key->GetClassName() == myclass){
      TString histname = key->ReadObj()->GetName();
      cout << "histname: " << histname << endl;
      TString tokendummy = histname;
      tokendummy.ReplaceAll("__", "#");
      TObjArray* histnamePieces = tokendummy.Tokenize("#");
      TString varname =  ((TObjString*)histnamePieces->At(0))-> GetString();
      TString procname =  ((TObjString*)histnamePieces->At(1))-> GetString();
      TString systname = "NOMINAL";
      if(histnamePieces->GetEntriesFast() > 2) systname = ((TObjString*)histnamePieces->At(2))-> GetString();
      systname.ReplaceAll("Up", "");
      systname.ReplaceAll("Down", "");
      cout << "varname: " << varname << ", procname: " << procname << ", systname: " << systname << endl;

      // fill lists
      bool addthis = true;
      for(size_t i=0; i<varnames.size(); i++){
        if(varname == varnames[i]) addthis = false;
      }
      if(addthis) varnames.emplace_back(varname);

      addthis = true;
      for(size_t i=0; i<procnames.size(); i++){
        if(procname == procnames[i]) addthis = false;
      }
      if(addthis) procnames.emplace_back(procname);

      // addthis = true;
      // for(size_t i=0; i<systnames.size(); i++){
      //   if(systname == systnames[i]) addthis = false;
      // }
      // if(addthis) systnames.emplace_back(systname);

      if(systname == "NOMINAL") continue;
      bool thisprocexists = false;
      for (map<TString, vector<TString>>::iterator it=systs_for_procs.begin(); it!=systs_for_procs.end(); ++it){
        if(procname == it->first) thisprocexists = true;
      }
      bool prochassyst = false;
      if(thisprocexists){
        for(size_t i=0; i<systs_for_procs[procname].size(); i++){
          if(systname == systs_for_procs[procname][i]) prochassyst = true;
        }
      }
      if(!prochassyst){
        if(thisprocexists){
          vector<TString> dummy = systs_for_procs[procname];
          dummy.emplace_back(systname);
          systs_for_procs[procname] = dummy;
        }
        else{
          vector<TString> dummy = {systname};
          systs_for_procs[procname] = dummy;
        }
      }
    }
  }


  // Now that we have everything, loop through the variables and the processes, plotting each systematic and the nominal one
  // =======================================================================================================================

  for(size_t i=0; i<varnames.size(); i++){
    TString var = varnames[i];
    for(size_t j=0; j<procnames.size(); j++){
      TString proc = procnames[j];

      // loop through syst vector for this process
      for(size_t k=0; k<systs_for_procs[proc].size(); k++){
        TString syst = systs_for_procs[proc][k];



	// don't use plots where no systematics were used
	if(syst.Contains("scale") && proc.Contains("HHtoWWbb")) continue;
	//if(syst == "PDF" && proc.Contains("HHtoWWbb"))          continue;
	if(syst == "scale_DYJets"    && !proc.Contains("DYJets"))    continue;
	if(syst == "scale_Diboson"   && !proc.Contains("Diboson"))   continue;
	if(syst == "scale_SingleTop" && !proc.Contains("SingleTop")) continue;
	if(syst == "scale_TTV"       && !proc.Contains("TTV"))       continue;
	if(syst == "scale_TTbar"     && !proc.Contains("TTbar"))     continue;
	if(syst == "scale_WJets"     && !proc.Contains("WJets"))     continue;


        TString histname_nom = var + "__" + proc;
        TString histname_up = var + "__" + proc + "__" + syst +"Up";
        TString histname_down = var + "__" + proc + "__" + syst +"Down";
        cout << "nom: " << histname_nom << ", up: " << histname_up << ", down: " << histname_down << endl;

        // get histograms
        TH1F* h_nom  = (TH1F*)infile->Get(histname_nom);
        TH1F* h_up   = (TH1F*)infile->Get(histname_up);
        TH1F* h_down = (TH1F*)infile->Get(histname_down);

        // build ratio
        TH1F* ratio_up = (TH1F*)h_up->Clone();
        ratio_up->Divide(h_nom);
        TH1F* ratio_down = (TH1F*)h_down->Clone();
        ratio_down->Divide(h_nom);

        // cosmetics
	gROOT->SetBatch(kTRUE); // don't draw every hist
        HistCosmetics(h_nom, false);
        HistCosmetics(h_up, false);
        HistCosmetics(h_down, false);
        HistCosmetics(ratio_up, true);
        HistCosmetics(ratio_down, true);
        h_up->SetLineColor(kRed+1);
        ratio_up->SetLineColor(kRed+1);
        h_up->SetMarkerColor(kRed+1);
        ratio_up->SetMarkerColor(kRed+1);
        h_down->SetLineColor(kAzure-1);
        ratio_down->SetLineColor(kAzure-1);
        h_down->SetMarkerColor(kAzure-1);
        ratio_down->SetMarkerColor(kAzure-1);
        h_nom->SetMarkerColor(kBlack);
        h_nom->SetLineColor(kBlack);
        h_nom->GetYaxis()->SetTitle("Events / bin");
        TH1F* h_axis = (TH1F*)h_nom->Clone();
        h_axis->GetYaxis()->SetTitle("var / nom");
        h_axis->GetYaxis()->SetLabelSize(12);
	if(var=="srmu_catA") h_axis->GetXaxis()->SetTitle("srmu output node");
	if(var=="ttcrmu_catA") h_axis->GetXaxis()->SetTitle("ttcrmu output node");
	if(var=="stcrmu_catA") h_axis->GetXaxis()->SetTitle("stcrmu output node");
	if(var=="wdycrmu_catA") h_axis->GetXaxis()->SetTitle("wdycrmu output node");

        HistCosmetics(h_axis, true);

        TCanvas* c = new TCanvas("c", "systematic plots", 400, 400);
        TPad* pad_top = SetupRatioPadTop();
        TPad* pad_bot = SetupRatioPad();
        pad_top->Draw();
        pad_bot->Draw();
        pad_top->cd();
        h_nom->Draw("HIST");
        h_up->Draw("HIST SAME");
        h_down->Draw("HIST SAME");

        TLegend* leg1 = new TLegend(0.70, 0.55, 0.94, 0.85);
        leg1->SetFillStyle(0);
        leg1->SetLineWidth(0);
        leg1->SetHeader(syst);
        leg1->AddEntry(h_nom, "Nominal", "l");
        leg1->AddEntry(h_up, "+1#sigma", "l");
        leg1->AddEntry(h_down, "-1#sigma", "l");
        leg1->Draw("SAME");
        pad_top->SetLogy();

        pad_bot->cd();
        h_axis->Draw("AXIS");
        ratio_up->Draw("HIST SAME");
        ratio_down->Draw("HIST SAME");

        TLine* line1 = new TLine(h_axis->GetBinLowEdge(1), 1, h_axis->GetBinLowEdge(h_axis->GetNbinsX()+1), 1);
        line1->SetLineWidth(2);
        line1->SetLineColor(kBlack);
        line1->SetLineStyle(2);
        line1->Draw("SAME");

        pad_top->cd();
        TString infotext = "35.9 fb^{-1} (13 TeV)";
        TLatex *text1 = new TLatex(3.5, 24, infotext);
        text1->SetNDC();
        text1->SetTextAlign(33);
        text1->SetX(0.94);
        text1->SetTextFont(43);
        text1->SetTextSize(16);
        text1->SetY(0.995);
        text1->Draw("SAME");

        TString sampletext = proc;
        TLatex *text2 = new TLatex(3.5, 24, sampletext);
        text2->SetNDC();
        text2->SetTextAlign(33);
        text2->SetX(0.3);
        text2->SetTextFont(43);
        text2->SetTextSize(16);
        text2->SetY(0.98);
        text2->Draw("SAME");


        c->SaveAs(outdir + "SysVars_" + var + "_" + proc + "_" + syst + ".eps");
        // delete c_out;

	/*
        delete h_axis;
        delete ratio_down;
        delete ratio_up;
        delete h_nom;
        delete h_up;
        delete h_down;
	*/
      }
    }
  }




  cout << "VARNAMES: " << endl;
  for(size_t i=0; i<varnames.size(); i++) cout << varnames[i] << endl;
  cout << "PROCNAMES (with systs): " << endl;
  for(size_t i=0; i<procnames.size(); i++){
    cout << procnames[i] << endl;
    for(size_t j=0; j<systs_for_procs[procnames[i]].size(); j++){
      cout << "   " << systs_for_procs[procnames[i]][j] << endl;
    }
  }
  delete infile;
}
