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


void AnalysisTool::ProduceCombineHistogramsNN(bool use_data){
  bool debug = true;
  if(debug){
    cout << "ProduceCombinedHistograms:"<< endl;
    cout << "year: " << AnalysisTool::yeartag << endl;
    cout << "Line: " << __LINE__ << endl;
  }

  //vector<TString> systematics = {"NOMINAL"};
  vector<TString> systematics = {
    "nominal", "muid", "pu", "eleid", "elereco", "muiso", "btag_bc", "btag_udsg", "pdf",
    "MuR_TTbar", "MuR_DYJets", "MuR_WJets", "MuR_SingleTop", "MuR_Diboson", "MuR_TTV",
    "MuF_TTbar", "MuF_DYJets", "MuF_WJets", "MuF_SingleTop", "MuF_Diboson", "MuF_TTV",
    "scale_TTbar", "scale_DYJets", "scale_WJets", "scale_SingleTop", "scale_Diboson", "scale_TTV",
    "pdf_TTbar", "pdf_DYJets", "pdf_WJets", "pdf_SingleTop", "pdf_Diboson", "pdf_TTV",
    "MuR_HH", "MuF_HH", "scale_HH", "pdf_HH",
    //"JEC", "JER"
  };
  vector<TString> syst_shift = {"up", "down"};
  vector<TString> syst_shift_combine = {"Up", "Down"};
  vector<TString> channel_tags = {"much", "ech"};
  vector<TString> region_tags = {"sr", "ttcr", "stcr", "wdycr"/*, "qcdcr"*/};
  vector<TString> samples_base = {"HHtoWWbbSemiLeptonic_SM", "HHtoWWbbSL_cHHH0", "HHtoWWbbSL_cHHH1", "HHtoWWbbSL_cHHH2p45", "HHtoWWbbSL_cHHH5", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets", "DATA"};

  TFile* f_out = new TFile(AnalysisTool::combineInputName_allShape, "RECREATE");

  for(unsigned int region = 0; region <region_tags.size(); region++) {
    for(unsigned int channel=0; channel<channel_tags.size(); channel++) {
      if(debug) cout << "============= Channel: " << channel_tags[channel] << ", Region: " << region_tags[region] << endl;

      for(unsigned int k=0; k<systematics.size(); k++) {
	TString syst = systematics[k];
	if(debug) cout << "========== Syst: " << syst << endl;
	for(unsigned int j=0; j<syst_shift.size(); j++) {
	  if(debug) cout << " === syst_shift: " << syst_shift[j] << endl;

	  TString infilename_base = AnalysisTool::base_path  + AnalysisTool::year + "/" + AnalysisTool::NN_tag; 
	  if(debug) cout << infilename_base << endl;



	  for(unsigned int i=0; i<samples_base.size(); i++) {
	    TString proc = samples_base[i];

            TString tag = "MC.";
            if(use_data && proc == "DATA") tag = "DATA.";

	    // change qcd and data to required input name
	    if (proc == "DATA") {
	      if(channel_tags[channel]=="ech") proc += "_Electron";
	      else proc += "_Muon";
	    }
	    if (proc == "QCD") {
	      if(channel_tags[channel]=="ech") proc += "Ele";
	      else proc += "Mu";
	    }

	    bool force_nominal = false;
            if(proc.Contains("DATA") && syst != "nominal") force_nominal = true;
            if(!proc.Contains("TTbar") && syst.Contains("_TTbar")) force_nominal = true;
            if(!proc.Contains("SingleTop") && syst.Contains("_SingleTop")) force_nominal = true;
	    if(!proc.Contains("DYJets") && syst.Contains("_DYJets")) force_nominal = true;
	    if(!proc.Contains("Diboson") && syst.Contains("_Diboson")) force_nominal = true;
	    if(!proc.Contains("TTV") && syst.Contains("_TTV")) force_nominal = true;
	    if(!proc.Contains("WJets") && syst.Contains("_WJets")) force_nominal = true;
	    if(!proc.Contains("HHtoWWbbSL") && syst.Contains("_HH")) force_nominal = true;

	    if(debug) cout << "======= Sample " << proc << endl;

	    TString infilename = infilename_base;
	    if((syst.Contains("scale") || syst.Contains("MuR") || syst.Contains("MuF")) && !force_nominal) infilename += "scale/";
	    else if(syst.Contains("pdf") && !force_nominal) infilename += "pdf/";
	    else if((syst=="JEC" || syst =="JER") && !force_nominal) infilename+= syst + syst_shift_combine[j] + "/uhh2.AnalysisModuleRunner."+tag;
	    else infilename += "NOMINAL/uhh2.AnalysisModuleRunner."+tag;
	    infilename += proc + "_" + yeartag + ".root";
	  
	    // if running blind & data is not processed yet: use dummy
	    if(!use_data && proc.Contains("DATA")) {
	      infilename.ReplaceAll("DATA_Electron", "TTbar");
	      infilename.ReplaceAll("DATA_Muon", "TTbar");
	    }

	    if(debug) cout << "infilename: " << infilename << endl;
	    TFile* f_in = new TFile(infilename);
	    //TString histname = histinname_base[channel] + "_";

	    // note: 'region' is an integer from 0 to 3
	    TString histname = channel_tags[channel] + "_DNNoutput"+to_string(region)+"_";
	    if(force_nominal || syst=="nominal") histname+="nominal";
	    else if(syst.Contains("scale")) histname+="scale_" + syst_shift[j];
	    else if(syst.Contains("MuR")) histname+="MuR_" + syst_shift[j];
	    else if(syst.Contains("MuF")) histname+="MuF_" + syst_shift[j];
	    else if(syst.Contains("pdf_")) histname+="pdf_" + syst_shift[j];
	    else if(syst=="JEC" || syst=="JER") histname+=syst+syst_shift_combine[j];
	    else histname += syst + "_" + syst_shift[j];

	    histname+="/max_NN_out";
	    //histname+="/NN_out"+to_string(region);
	    //histname+="/NN_out"+to_string(region) + "_" + histinname_tag[region];
	    // e.g. histname = much_DNNoutput0_scale_up/NNout0
	    if(debug) cout << "force_nominal: " << force_nominal << endl;
	    if(debug) cout << "histname: " << histname << endl;

	    //TH1F* h_out = (TH1F*) f_in->Get(histname);
	    TH1F* h_out;
	    if(!force_nominal && (syst.Contains("scale") || syst.Contains("pdf"))) h_out = (TH1F*) f_in->Get(histname);
	    else h_out = AnalysisTool::ApplyOptimizeBinning((TH1F*)f_in->Get(histname), region_tags[region]+channel_tags[channel], proc);


	    //h_out->Scale(3.8);
	    // change data and qcd to the required output name
	    if(proc.Contains("DATA")) proc = "data_obs";
	    if(proc.Contains("QCD")) proc = "QCD";
	    if(proc.Contains("HHtoWWbbSL")){ // for inference: change HH names
	      proc.ReplaceAll("HHtoWWbbSL_cHHH", "ggHH_kl_");
	      proc += "_kt_1_hbbhww";
	    }
	    TString histname_out = region_tags[region] + channel_tags[channel] + "__" + proc + "_" + AnalysisTool::yeartag;
	    if(syst != "nominal") histname_out += "__" + syst + syst_shift_combine[j];
	    // e.g. histname_out = srmuch_TTbar_2016v3__scale_TTbarUp
	    if(debug) cout << "histname_out: " << histname_out << endl;

	    h_out->SetName(histname_out);
	    f_out->cd();
	    h_out->Write();
	    f_in->Close();
	  }
	}
      }
    }
  }
  f_out->Close();
  
  cout << "finished!" << endl;
}

void AnalysisTool::ConvertShapeToRate(){
  bool debug = false;
  if(debug) cout << "Hello World from ConvertShapeToRate!" << endl;

  cout << "infilename" << AnalysisTool::combineInputName_allShape << endl;
  TFile* infile = new TFile(AnalysisTool::combineInputName_allShape, "READ");



  // map: systematic to vector of processes that are supposted to be flattened
  //TString channels = "srmuch,srech";
  TString systematics = "JEC,JER,pu";
  TString processes = "ggHH_kl_0_kt_1_hbbhww,ggHH_kl_1_kt_1_hbbhww,ggHH_kl_2p45_kt_1_hbbhww,ggHH_kl_5_kt_1_hbbhww,SingleTop,TTbar,DYJets,Diboson,QCD,TTV,WJets";

  //vector<TString> channels = {"srmuch", "srech"};
  //vector<TString> systematics = {"JEC", "JER", "pu"};
  //vector<TString> processes = {"ggHH_kl_0_kt_1_hbbhww", "ggHH_kl_1_kt_1_hbbhww", "ggHH_kl_2p45_kt_1_hbbhww", "ggHH_kl_5_kt_1_hbbhww", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets"};

  map<TString,TString> syst_to_procs = {
    {"JEC", "DYJets,Diboson,TTV,QCD,ggHH_kl_0_kt_1_hbbhww,ggHH_kl_1_kt_1_hbbhww,ggHH_kl_2p45_kt_1_hbbhww,ggHH_kl_5_kt_1_hbbhww"},
    {"JER", processes},
    {"pu", processes}
  };


  


  // Get histograms (only TH1), tokenize them to get all vars, processes, systs
  // ==========================================================================
  TDirectory* dir = gDirectory;
  TIter iter = dir->GetListOfKeys();
  TKey* key;
  cout << "outfilename" << AnalysisTool::combineInputName_rateShape << endl;
  TFile* outfile = new TFile(AnalysisTool::combineInputName_rateShape, "RECREATE");

  while ((key = (TKey*)iter())) {
    TString myclass = "TH1F";

    // Consider only TH1F objects
    if(key->GetClassName() == myclass){
      TString histname = key->ReadObj()->GetName();
      //cout << "histname: " << histname << endl;
      TString tokendummy = histname;
      tokendummy.ReplaceAll("__", "#");

      TObjArray* histnamePieces = tokendummy.Tokenize("#");
      TString channelname =  ((TObjString*)histnamePieces->At(0))-> GetString();
      TString procname =  ((TObjString*)histnamePieces->At(1))-> GetString();
      procname.ReplaceAll("_"+yeartag, "");
      TString systname = "NOMINAL";
      if(histnamePieces->GetEntriesFast() > 2) systname = ((TObjString*)histnamePieces->At(2))-> GetString();
      systname.ReplaceAll("Up",  "");
      systname.ReplaceAll("Down","");

	
      if(/*!channels.Contains(channelname) ||*/ !systematics.Contains(systname)) {
	// this channel/syst should be shape: just copy the existing histogram
	TH1F* h_out = (TH1F*)infile->Get(histname);
	outfile->cd();
	h_out->Write();
      }
      else{
	map<TString,TString>::iterator it;
	for(it=syst_to_procs.begin(); it != syst_to_procs.end(); it++) {
	  TString syst = it->first;
	  if(syst!=systname) continue;
	  if(debug) cout << "================ syst: " << syst << endl;
	  TString procs = it->second;
	  if(!procs.Contains(procname)) {
	    // this process should be shape: just copy the existing histogram
	    TH1F* h_out = (TH1F*)infile->Get(histname);
	    outfile->cd();
	    h_out->Write();
	  }
	  else{
	    // these histograms are supposed to be rate: let's change them!
	    cout << "rate histname: " << histname << endl;
	    TString histname_nom = channelname + "__" + procname + "_" + yeartag;
	    TH1F* h_out = (TH1F*)infile->Get(histname_nom);
	    double int_nom = h_out->Integral();
	    double int_var = ((TH1F*)infile->Get(histname))->Integral();
	    
	    h_out->Scale(int_var/int_nom);
	    h_out->SetName(histname);
	    cout << "int_var/int_nom: " << int_var/int_nom << endl; 

	    outfile->cd();
	    h_out->Write();
	  }
	}
      }
    }
  }
}




	/*
	for(TString ch: channels) {
	  if(debug) cout << "========================== channel: " << ch << endl;
	  for(it=syst_to_procs.begin(); it != syst_to_procs.end(); it++) {
	    TString syst = it->first;
	    if(debug) cout << "================ syst: " << syst << endl;
	    vector<TString> procs = it->second;
	    for(TString proc: procs) {
	      if(debug) cout << "====== proc: " << proc << endl;
	      TString histname_nom = ch + "__" + proc + "_" + yeartag;
	      TString histname_up = histname_nom + "__" + syst + "Up";
	      TString histname_down = histname_nom + "__" + syst + "Down";
	
	      TH1F* h_nom = (TH1F*)infile->Get(histname_nom);

	      double int_nom = h_nom->Integral();
	      double int_up = ((TH1F*)infile->Get(histname_up))->Integral();
	      double int_down = ((TH1F*)infile->Get(histname_down))->Integral();

	      TH1F* h_up = (TH1F*)h_nom->Clone();
	      h_up->Scale(int_up/int_nom);
	      h_up->SetName(histname_up);
	      TH1F* h_down = (TH1F*)h_nom->Clone();
	      h_down->Scale(int_down/int_nom);
	      h_down->SetName(histname_down);

	      if(debug){
		cout << "int_up   before: " << int_up << ", after: " << h_up->Integral() << endl;
		cout << "int_down before: " << int_down << ", after: " << h_down->Integral() << endl;
	      }

	      outfile->cd();
	      //file->Delete(histname_up);
	      //file->Delete(histname_down);
	      h_up->Write();
	      h_down->Write();
	    }
	  }
	}
      }
    }
  }
}
*/
