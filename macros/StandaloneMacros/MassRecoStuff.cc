#include "../include/cosmetics.h"
#include "../include/Tools.h"

using namespace std;


//void AnalysisTool::MassReco_matchedJets(){


void readout_N_matchedJets();
void readout_correctMatch();


void MassRecoStuff() {
  readout_N_matchedJets();
  readout_correctMatch();
}

void readout_N_matchedJets() {
  //TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/ForMassReco_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH1_2016v3.root";
  TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/ForMassReco_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.HHtoWWbbSemiLeptonic_SM_2016v3.root";
  TFile *infile = new TFile(infilename);
  TString cuts = "mHH_reconstructed";
  TString histname_base = cuts+"_much_Matched/";

  vector<TString> partons = {"B1","B2","Q1","Q2"};

  for(TString parton: partons) {
    TString histname = histname_base + "N_matchedJets_" + parton;
    cout << histname << endl;
    TH1F* h_in = (TH1F*) infile->Get(histname);
    
    double integral = h_in->Integral();

    for(unsigned int i=1; i<h_in->GetNbinsX(); i++) {
      double num = h_in->GetBinContent(i);
      cout << num/integral*100 << "% of events have " << i-1 << " matched jets in dR=0.4 to parton " << parton << endl;
    }
  }
}

void readout_correctMatch() {
  //TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/ForMassReco_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH1_2016v3.root";
  TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/ForMassReco_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.HHtoWWbbSemiLeptonic_SM_2016v3.root";
  TFile *infile = new TFile(infilename);
  //TString cuts = "BTag";
  TString cuts = "mHH_reconstructed";
  TString h_base = cuts+"_much_Matched/";

  vector<TString> histnames = {"Hbb_correct_chi2","Hbb_correct_highestPt","WHad_correct_chi2","WHad_correct_highestPt","WHad_correct_lowestPt"};

  for(TString histname: histnames) {

    TH1F* h_in = (TH1F*) infile->Get(h_base+histname);
    double integral = h_in->Integral();

    double integral_allJetsMatched = h_in->GetBinContent(3)+h_in->GetBinContent(4)+h_in->GetBinContent(5);



    cout << histname << endl;
    cout << h_in->GetBinContent(5)/integral_allJetsMatched*100 << "% of events have both jets correctly chosen if both jets are matched" << endl;
    cout << h_in->GetBinContent(4)/integral_allJetsMatched*100 << "% of events have one jet correctly chosen if both jets are matched" << endl;
    cout << h_in->GetBinContent(3)/integral_allJetsMatched*100 << "% of events have no jets correctly chosen if both jets are matched" << endl;
    cout << h_in->GetBinContent(5)/integral*100 << "% of events have both jets correctly chosen" << endl;
    cout << h_in->GetBinContent(4)/integral*100 << "% of events have one jet correctly chosen" << endl;
    cout << h_in->GetBinContent(1)/integral*100 << "% of events have both jets not correctly matched" << endl;
    cout << h_in->GetBinContent(2)/integral*100 << "% of events have one jet not correctly matched" << endl;
    cout << "--------------------------------------" << endl;
    }
}
