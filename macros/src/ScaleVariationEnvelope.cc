#include "../include/Tools.h"

#include <TString.h>
#include <TVirtualFitter.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TFitResult.h>
#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TVectorD.h>
#include <TDecompSVD.h>
#include <sstream>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <string>
#include <TROOT.h>
#include <TRint.h>
#include <TClass.h>
#include <TKey.h>


using namespace std;

vector<double> AnalysisTool::findScaleRescaleValues(TString process) {
  
  TString infolder = AnalysisTool::base_path + AnalysisTool::year + "/CountEvents/uhh2.AnalysisModuleRunner.MC." + process + ".root";
  TFile* f_in = new TFile(infolder);
  TH1F* h_uu = (TH1F*) f_in->Get("Hists/murmuf_upup");
  TH1F* h_un = (TH1F*) f_in->Get("Hists/murmuf_upnone");
  TH1F* h_nu = (TH1F*) f_in->Get("Hists/murmuf_noneup");
  TH1F* h_nd = (TH1F*) f_in->Get("Hists/murmuf_nonedown");
  TH1F* h_dn = (TH1F*) f_in->Get("Hists/murmuf_downnone");
  TH1F* h_dd = (TH1F*) f_in->Get("Hists/murmuf_downdown");
  TH1F* h_nom = (TH1F*) f_in->Get("Hists/nominal");

  vector<double> Rescale;
  double nom = h_nom->Integral();
  Rescale.push_back(nom/h_uu->Integral());
  Rescale.push_back(nom/h_un->Integral());
  Rescale.push_back(nom/h_nu->Integral());
  Rescale.push_back(nom/h_nd->Integral());
  Rescale.push_back(nom/h_dn->Integral());
  Rescale.push_back(nom/h_dd->Integral());
  return Rescale;
}


void AnalysisTool::ScaleVariationEnvelope(){
  cout << "ScaleVariationEnvelope: " << endl;
  //Files & histograms for other processes
  TString path = AnalysisTool::base_path + AnalysisTool::year + "/" + AnalysisTool::NN_tag; // Finalselection == NNApplied
  cout << path << endl;
  vector<TString> processes = {"TTbar_" + AnalysisTool::yeartag,"SingleTop_" + AnalysisTool::yeartag, "DYJets_" + AnalysisTool::yeartag, "Diboson_" + AnalysisTool::yeartag, "TTV_" + AnalysisTool::yeartag, "WJets_" + AnalysisTool::yeartag, "QCDMu_" + AnalysisTool::yeartag, "QCDEle_" + AnalysisTool::yeartag, "HHtoWWbbSL_cHHH0_" + AnalysisTool::yeartag, "HHtoWWbbSL_cHHH1_" + AnalysisTool::yeartag, "HHtoWWbbSL_cHHH2p45_" + AnalysisTool::yeartag, "HHtoWWbbSL_cHHH5_" + AnalysisTool::yeartag};
  unique_ptr<TFile> f_in;

  for(unsigned int aa=0; aa< processes.size();aa++){
    TString process =  processes[aa];

  // Read out Rescale Values
  vector<double> Rescale = findPDFRescaleValues(process);

    f_in.reset (new TFile(path + "NOMINAL/uhh2.AnalysisModuleRunner.MC." + process  + ".root","READ"));

    vector<TString> histfolders = {""};
    
    // check again and implement correctly
    map<TString, TString> cat_tags = {
      {"HH", "output0"},
      {"TTbar", "output1"},
      {"SingleTop", "output2"},
      {"WJets+DYJets", "output3"},
      {"QCD", "output4"}
    };
    vector<TString> channel_tags = {"much", "ech"};
    // vector<TString> region_tags = {"catA", "catB"}; // probably not necessary / exchange with cat_tags
    vector<TString> region_tags = {"DNNoutput0", "DNNoutput1", "DNNoutput2", "DNNoutput3", "DNNoutput4"};
    
    // check again and implement correctly
    /*
    map<TString, TString> region_tags = {
      {"HH", "output0"},
      {"TTbar", "output1"},
      {"SingleTop", "output2"},
      {"WJets+DYJets", "output3"}
    }
    */

    unique_ptr<TFile> f_out;
    f_out.reset(new TFile(path + "scale/" + process  + ".root","RECREATE"));

    for(unsigned int i=0; i<channel_tags.size(); i++){
      for(unsigned int j=0; j<region_tags.size(); j++){

	// change to correct foldername
	TString histfolder = channel_tags[i] + "_" + region_tags[j];

	f_out->mkdir(histfolder + "_scale_up");
	f_out->mkdir(histfolder + "_scale_down");
	f_out->mkdir(histfolder + "_MuR_up");
	f_out->mkdir(histfolder + "_MuR_down");
	f_out->mkdir(histfolder + "_MuF_up");
	f_out->mkdir(histfolder + "_MuF_down");


	unique_ptr<TH1F> h_uu, h_un, h_nu, h_nd, h_dn, h_dd, h_nom;
	TString histname = "";
	f_in->cd(histfolder+"_nominal");
	TDirectory* dir = gDirectory;
	TIter iter(dir->GetListOfKeys());
	TKey *key;
	TH1F* h;
	while ((key = (TKey*)iter())) {
	  TClass *cl = gROOT->GetClass(key->GetClassName());
	  if (!cl->InheritsFrom("TH1")) continue;
	  h = (TH1F*)key->ReadObj();
	  histname = h->GetName();
	  std::cout<<"histname  "<<histname<<std::endl;
	  h_uu.reset((TH1F*)f_in->Get(histfolder + "_scale_upup/" + histname));
	  h_un.reset((TH1F*)f_in->Get(histfolder + "_scale_upnone/" + histname));
	  h_nu.reset((TH1F*)f_in->Get(histfolder + "_scale_noneup/" + histname));
	  h_nd.reset((TH1F*)f_in->Get(histfolder + "_scale_nonedown/" + histname));
	  h_dn.reset((TH1F*)f_in->Get(histfolder + "_scale_downnone/" + histname));
	  h_dd.reset((TH1F*)f_in->Get(histfolder + "_scale_downdown/" + histname));
	  h_nom.reset((TH1F*)f_in->Get(histfolder + "_nominal/" + histname));

	  // Rescale
	  h_uu->Scale(Rescale[0]);
	  h_un->Scale(Rescale[1]);
	  h_nu->Scale(Rescale[2]);
	  h_nd->Scale(Rescale[3]);
	  h_dn->Scale(Rescale[4]);
	  h_dd->Scale(Rescale[5]);

	  // Write out rescaled MuR and MuF
	  f_out->cd(histfolder + "_MuR_up");
	  h_un->Write();
	  f_out->cd(histfolder + "_MuR_down");
	  h_dn->Write();
	  f_out->cd(histfolder + "_MuF_up");
	  h_nu->Write();
	  f_out->cd(histfolder + "_MuF_down");
	  h_nd->Write();
	  

	  const int nbins = h_nom->GetNbinsX();
	  vector<double> min_bins, max_bins, max_err, min_err;

	  for(int ii=1; ii<h_nom->GetNbinsX()+1; ii++){
	    double entries[7] = {h_uu->GetBinContent(ii),h_un->GetBinContent(ii),h_nu->GetBinContent(ii),h_nd->GetBinContent(ii),h_dn->GetBinContent(ii),h_dd->GetBinContent(ii),h_nom->GetBinContent(ii)};
	    double errors[7] = {h_uu->GetBinError(ii),h_un->GetBinError(ii),h_nu->GetBinError(ii),h_nd->GetBinError(ii),h_dn->GetBinError(ii),h_dd->GetBinError(ii),h_nom->GetBinError(ii)};
	    double min = 9999999;
	    double max_error = 0, min_error = 0;
	    double max = 0;
	    for(int jj=0; jj<7; jj++){
	      if(entries[jj] > max) {max = entries[jj]; max_error = errors[jj];}
	      if(entries[jj] < min) {min = entries[jj]; min_error = errors[jj];}
	    }

	    min_bins.push_back(min);
	    max_bins.push_back(max);
	    min_err.push_back(min_error);
	    max_err.push_back(max_error);
	  }

	  vector<double> bins_low;
	  for(int ii=1; ii<h_nom->GetNbinsX()+2; ii++){
	    bins_low.push_back(h_nom->GetBinLowEdge(ii));
	  }

	  unique_ptr<TH1F> hist_out_up, hist_out_dn;
	  hist_out_up.reset(new TH1F(histname,"",  nbins, &bins_low[0]));
	  for(int ii=1; ii<h_nom->GetNbinsX()+1; ii++){
	    hist_out_up->SetBinContent(ii,max_bins[ii-1]);
	    hist_out_up->SetBinError(ii, max_err[ii-1]);
	  }


	  hist_out_dn.reset(new TH1F(histname,"",  nbins, &bins_low[0]));
	  for(int ii=1; ii<h_nom->GetNbinsX()+1; ii++){
	    hist_out_dn->SetBinContent(ii,min_bins[ii-1]);
	    hist_out_dn->SetBinError(ii, min_err[ii-1]);
	  }


	  cout << "histname: " << histname << endl;
	  f_out->cd(histfolder + "_scale_up");
	  hist_out_up->Write();
	  f_out->cd(histfolder + "_scale_down");
	  hist_out_dn->Write();
	}
      }
    }

    f_out->Close();
  }
}
