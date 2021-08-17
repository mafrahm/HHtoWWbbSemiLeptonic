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
#include <TFitResult.h>
#include <fstream>

using namespace std;

void FindRMS(TString infolder, map<TString, TString> samplemap, TString sample);

void AnalysisTool::PDFRMS() {
  cout << "starting PDFRMS, year: " << yeartag << endl;

  // should also include 2017, 2018 -> use yeartag instead of "2016v3"
  map<TString, TString> samplemap;
  samplemap["TTbar_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.TTbar_" +yeartag + ".root";
  samplemap["DYJets_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.DYJets_" + yeartag + ".root";
  samplemap["Diboson_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.Diboson_" + yeartag + ".root";
  samplemap["QCDMu_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.QCDMu_" + yeartag + ".root";
  samplemap["QCDEle_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.QCDEle_" + yeartag + ".root";
  samplemap["TTV_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.TTV_" + yeartag + ".root";
  samplemap["WJets_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.WJets_" + yeartag + ".root";
  samplemap["SingleTop_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.SingleTop_" + yeartag + ".root";
  samplemap["HHtoWWbbSemiLeptonic_SM_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.HHtoWWbbSemiLeptonic_SM_" +yeartag + ".root";
  samplemap["HHtoWWbbSL_cHHH0_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH0_" +yeartag + ".root";
  samplemap["HHtoWWbbSL_cHHH1_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH1_" +yeartag + ".root";
  samplemap["HHtoWWbbSL_cHHH2p45_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH2p45_" +yeartag + ".root";
  samplemap["HHtoWWbbSL_cHHH5_" + yeartag] = "uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH5_" +yeartag + ".root";



  // cout << "samplemap: " << samplemap["TTbar_2016v3"] << endl;




  TString infolder = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::NN_tag;
  cout << infolder << endl;
  FindRMS(infolder, samplemap, "TTbar_" + yeartag);
  FindRMS(infolder, samplemap, "DYJets_" + yeartag);
  FindRMS(infolder, samplemap, "Diboson_" + yeartag);
  FindRMS(infolder, samplemap, "QCDMu_" + yeartag);
  FindRMS(infolder, samplemap, "QCDEle_" + yeartag);
  FindRMS(infolder, samplemap, "TTV_" + yeartag);
  FindRMS(infolder, samplemap, "WJets_" + yeartag);
  FindRMS(infolder, samplemap, "SingleTop_" + yeartag);
  FindRMS(infolder, samplemap, "HHtoWWbbSemiLeptonic_SM_" + yeartag);
  FindRMS(infolder, samplemap, "HHtoWWbbSL_cHHH0_" + yeartag);
  FindRMS(infolder, samplemap, "HHtoWWbbSL_cHHH1_" + yeartag);
  FindRMS(infolder, samplemap, "HHtoWWbbSL_cHHH2p45_" + yeartag);
  FindRMS(infolder, samplemap, "HHtoWWbbSL_cHHH5_" + yeartag);



}


void FindRMS(TString infolder, map<TString, TString> samplemap, TString sample){
  gStyle->SetOptStat(0);

  // Open File
  // ==========

  // infiles
  TString infilename = infolder +"NOMINAL/"+ samplemap[sample];
  TFile* infile = new TFile(infilename, "READ");
  // cout << "infilename: " << infilename << endl;
  // outfiles
  TString outfilename = infolder + "pdf/" + sample + ".root";
  TFile* outfile = new TFile(outfilename, "RECREATE");




  // Loop through the entire file and subtract minor backgrounds from data in every single histogram in the "General"-folder (!)
  // ===========================================================================================================================

  // get list of foldernames: The PDF folders have "pdf" in their name
  infile->cd();
  vector<TString> foldernames;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile")){
      TString name = key->ReadObj()->GetName();
      if(name != "SFrame" && name.Contains("_pdf")){
        foldernames.emplace_back(name);

        // make dirs without "pdf"
        TString makedirname = name;
	// cout << "foldername: " << makedirname << endl;

        makedirname.ReplaceAll("_pdf", "_pdf_up");
        outfile->mkdir(makedirname);
        makedirname.ReplaceAll("_pdf_up", "_pdf_down");
        outfile->mkdir(makedirname);
      }
    }
  }

  // cout << foldernames.size() << endl;
  for(size_t i=0; i<foldernames.size(); i++) {
    TString foldername = foldernames.at(i);
    // cout << "foldername: " << foldername << endl;
    // create list of histogram names (without the _xx tag for the number of the PDF variation)
    infile->cd(foldername);
    dir = gDirectory;
    iter = dir->GetListOfKeys();

    vector<TString> histnames;
    // Loop over all objects in this dir
    while ((key = (TKey*)iter())) {
      TString myclass = "TH1F";

      // Consider only TH1F objects
      if(!(key->GetClassName() == myclass)) continue;
      TString histname = key->ReadObj()->GetName();
      if(histname.Contains("_99")){
        TString histname_base = histname;
        histname_base.ReplaceAll("_99", "");
        histnames.emplace_back(histname_base);
      }
    }

    // go through all PDF variations, there have to be ==100 of them per histogram
    vector<vector<TH1F*>> histograms;
    vector<TH1F*> histograms_nom;
    // cout << histnames.size() << endl;
    for(size_t j=0; j<histnames.size(); j++){
      TString histname = histnames[j];


      // systematic histograms (100)
      vector<TH1F*> hists_thisvar;
      for(size_t k=1; k<101; k++){
        TString readoutname = foldername + "/" + histname + "_";
        readoutname += k;
        TH1F* h = (TH1F*)infile->Get(readoutname);
        hists_thisvar.emplace_back(h);
      }
      histograms.emplace_back(hists_thisvar);


      // nominal histograms (1)
      TString foldername_nom = foldername;
      foldername_nom.ReplaceAll("_pdf", "_nominal");
      // cout << "foldername_nom: " << foldername_nom << endl;
      TString histname_nom = histname;
      histname_nom.ReplaceAll("_PDF", "");
      histname_nom+="_limits"; // quick fix for histname convention
      // cout << "histname_nom: " << histname_nom << endl;
      TString readoutname = foldername_nom + "/" + histname_nom;
      TH1F* h = (TH1F*)infile->Get(readoutname);
      histograms_nom.emplace_back(h);
    }


    // Now calculate RMS in current folder, in each variable, in each bin
    // ===============================================================

    vector<TH1F*> hists_up, hists_down;

    // loop through variables
    for(size_t j=0; j<histograms_nom.size(); j++){
      TH1F* h_up = (TH1F*)histograms_nom[j]->Clone();
      TH1F* h_down = (TH1F*)histograms_nom[j]->Clone();

      // loop through bins
      for(int k=1; k<histograms_nom[j]->GetNbinsX()+1; k++){
        float nom = histograms_nom[j]->GetBinContent(k);

        // loop through 100 PDF histograms
        float rms = 0.;
        for(size_t l=0; l<histograms[j].size(); l++){
          if (sample.Contains("LQto") && k==1) histograms[j][l]->Scale(histograms_nom[j]->Integral()/histograms[j][l]->Integral());
          rms += pow(histograms[j][l]->GetBinContent(k) - nom, 2);
        }
        rms /= histograms[j].size()-1; // evtl. die "-1" weglassen
        rms = sqrt(rms);
	//cout << "rms: " << rms << endl;
	//cout << "nom: " << nom << endl;
        h_up->SetBinContent(k, nom + rms);
        h_down->SetBinContent(k, max((float)0., nom - rms));

      }

      hists_up.emplace_back(h_up);
      hists_down.emplace_back(h_down);
    }


    // Write histograms into file, chosing the correct folder
    TString writefoldername = foldername;
    writefoldername.ReplaceAll("_pdf", "_pdf_up");
    outfile->cd(writefoldername);
    for(size_t j=0; j<hists_up.size(); j++){
      hists_up[j]->Write();
    }
    writefoldername.ReplaceAll("_pdf_up", "_pdf_down");
    outfile->cd(writefoldername);
    for(size_t j=0; j<hists_down.size(); j++){
      hists_down[j]->Write();
    }


  }
  outfile->Close();


  delete outfile;
  delete infile;

}
