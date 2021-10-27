#include "../include/Tools.h"
//#include "../include/constants.h"

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

void AnalysisTool::Efficiencies(TString channel) {
  // vector<TString> processes = {"HHtoWWbbSL_cHHH0", "HHtoWWbbSL_cHHH1", "HHtoWWbbSL_cHHH2p45", "HHtoWWbbSL_cHHH5", "SingleTop", "TTbar", "DYJets", "QCDMu", "WJets"};

  
  vector<TString> processes = {"HHtoWWbbSL_cHHH1", "SingleTop", "TTbar", "DYJets", "WJets"};
  if(channel=="ech") processes.push_back("QCDEle");
  if(channel=="much") processes.push_back("QCDMu");
  TString channel_tag = "srmu";
  if(channel=="ech") channel_tag = "srele";
 

  vector<vector<TString>> label_histname_module= {
    /*
    {"Cleaner", "Cleaner_General/", "Pre"},
    {"N_{lep}=1", "1Lepton_General/", "Pre"},
    {"N_{#mu}=1", "1Lepton_"+channel_tag+"_General/", "Pre"}, 
    {"N_{Jets} #geq 3", "3Jets_"+channel_tag+"_General/", "Pre"},
    {"Cleaner_Full", "Cleaner_"+channel+"_General/", "Full"},
    {"Trigger", "Trigger_"+channel+"_General/", "Full"},
    {"N_{BTag} #geq 1", "BTag_"+channel+"_General/", "Full"},
    */
    {"Fullselection", "QCDcut0_"+channel+"_NNInput/", "NNAppl"},
    {"Min #Delta R (Lep,Jet)>0.2", "QCDcut1_"+channel+"_NNInput/", "NNAppl"},
    {"M_{T}^{top,lep}>60 GeV", "QCDcut2_"+channel+"_NNInput/", "NNAppl"},
    {"B2 deepjetscore>0.1", "QCDcut3_"+channel+"_NNInput/", "NNAppl"}
  }; 
  int N_hists = label_histname_module.size();

  // Setup the histogram
  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TH1F* h_base = new TH1F("Efficiencies", "Selection steps", N_hists, 0.5, N_hists+0.5);
  for(unsigned int j=0; j<label_histname_module.size();j++){
    h_base->GetXaxis()->SetBinLabel(j+1, label_histname_module[j][0].Data());
  }
  cout << "Line: " << __LINE__ << endl;
  h_base->SetMaximum(1.1);
  h_base->SetMinimum(0);
  h_base->Draw("HIST");
  TLegend *leg = new TLegend(0.25,0.67,0.95,0.91,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  //leg->SetHeader("Header");

  cout << "Line: " << __LINE__ << endl;


  TString infilename_base1 = base_path + year + "/";
  for(TString proc: processes) {
    cout << "============ proc: " << proc << endl;
    TString infilename_base2 = "/NOMINAL/uhh2.AnalysisModuleRunner.MC." + proc + "_" + yeartag + ".root";
    TString infilename_pre  = infilename_base1 + pre_tag  + infilename_base2;
    TString infilename_full = infilename_base1 + full_tag + infilename_base2;
    TString infilename_NN   = infilename_base1 + NN_tag   + infilename_base2;

    TFile* infile_pre = new TFile(infilename_pre);
    TFile* infile_full = new TFile(infilename_full);
    TFile* infile_NN = new TFile(infilename_NN);

    TH1F* h_out = new TH1F("efficiencies", "Selection steps", N_hists, 0.5, N_hists+0.5);
   
    double norm = 1;
    for(unsigned int j=0; j<label_histname_module.size(); j++) {
      TString module = label_histname_module[j][2];
      TString histname = label_histname_module[j][1] + "sum_event_weights";

      TH1F* h_in_j;
      if(module=="Pre") h_in_j = (TH1F*)infile_pre->Get(histname);
      if(module=="Full") h_in_j = (TH1F*)infile_full->Get(histname);
      if(module=="NNAppl") h_in_j = (TH1F*)infile_NN->Get(histname);
      cout << "Number of events after " << j << " cuts: " << h_in_j->Integral() << endl;
      cout << "number of events after " << j << " cuts: " << h_in_j->GetBinContent(1) << endl;
      
      if(j==0) norm = h_in_j->Integral();

      h_out->SetBinContent(j+1, h_in_j->Integral()/norm);
    }
    cout << "Line: " << __LINE__ << endl;
    cout << proc_colors[proc] << endl;
    h_out->SetLineColor(proc_colors[proc]);
    h_out->Draw("SAME");
    leg->AddEntry(h_out, proc,"L");
  }
  leg->Draw();
  //c1->SetLogy();
  c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/efficiencies_" + channel + "_" + year + ".eps");
  //c1->SaveAs("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/efficiencies_" + year + "_" + selection + "_" + cuts + ".pdf");
  delete c1;

} // end of script
