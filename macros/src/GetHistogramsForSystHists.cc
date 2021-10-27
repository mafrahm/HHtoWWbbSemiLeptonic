#include "../include/cosmetics.h"
#include "../include/Tools.h"

using namespace std;


// just a copy of ProduceCombineHistograms, but reading in other hists
// will only work for JEC/JER: for other systs we only plot the NNOutput (could of course be changed, but that would mean even more histograms)
void AnalysisTool::GetHistogramsForSystHists(TString histname_base){
  bool debug = true;
  bool use_data = false;
  if(debug){
    cout << "GetHistogramsForSystHists:"<< endl;
    cout << "year: " << AnalysisTool::yeartag << endl;
    cout << "Line: " << __LINE__ << endl;
  }

  //vector<TString> systematics = {"NOMINAL"};
  vector<TString> systematics = {
    "nominal", "muid", "pu", "eleid", "elereco", "muiso", "btag_bc", "btag_udsg",/* "pdf",*/
    "MuR_TTbar", "MuR_DYJets", "MuR_WJets", "MuR_SingleTop", "MuR_Diboson", "MuR_TTV",
    "MuF_TTbar", "MuF_DYJets", "MuF_WJets", "MuF_SingleTop", "MuF_Diboson", "MuF_TTV",
    "scale_TTbar", "scale_DYJets", "scale_WJets", "scale_SingleTop", "scale_Diboson", "scale_TTV",
    //"pdf_TTbar", "pdf_DYJets", "pdf_WJets", "pdf_SingleTop", "pdf_Diboson", "pdf_TTV", // pdf hists only include DNN output nodes :(
    "MuR_HH", "MuF_HH", "scale_HH", //"pdf_HH",
    "JEC", "JER"
  };
  vector<TString> syst_shift = {"up", "down"};
  vector<TString> syst_shift_combine = {"Up", "Down"};
  vector<TString> channel_tags = {"much", "ech"};
  vector<TString> region_tags = {"sr", "ttcr", "stcr", "wdycr"/*, "qcdcr"*/};
  vector<TString> samples_base = {/*"HHtoWWbbSemiLeptonic_SM",*/ "HHtoWWbbSL_cHHH0", "HHtoWWbbSL_cHHH1", "HHtoWWbbSL_cHHH2p45", "HHtoWWbbSL_cHHH5", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets", "DATA"};

  TFile* f_out = new TFile(AnalysisTool::histsForSyst_name, "RECREATE");

  for(unsigned int region = 0; region <region_tags.size(); region++) {
    if(region!=0) continue; // for only getting srmuch,srech hists
    for(unsigned int channel=0; channel<channel_tags.size(); channel++) {
      if(debug) cout << "============= Channel: " << channel_tags[channel] << ", Region: " << region_tags[region] << endl;

      for(unsigned int k=0; k<systematics.size(); k++) {
	TString syst = systematics[k];
	if(debug) cout << "========== Syst: " << syst << endl;
	for(unsigned int j=0; j<syst_shift.size(); j++) {
	  //if(debug) cout << " === syst_shift: " << systshift[j] << endl;

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
            if(!proc.Contains("TTbar") && syst == "scale_TTbar") force_nominal = true;
            if(!proc.Contains("SingleTop") && syst == "scale_SingleTop") force_nominal = true;
            if(!proc.Contains("DYJets") && syst == "scale_DYJets") force_nominal = true;
            if(!proc.Contains("Diboson") && syst == "scale_Diboson") force_nominal = true;
            if(!proc.Contains("TTV") && syst == "scale_TTV") force_nominal = true;
            if(!proc.Contains("WJets") && syst == "scale_WJets") force_nominal = true;
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

	    // note: 'region' is an integer from 0 to 3
	    TString histname = channel_tags[channel] + "_DNNoutput"+to_string(region)+"_";
	    if(force_nominal || syst=="nominal") histname+="nominal";
	    else if(syst.Contains("scale")) histname+="scale_" + syst_shift[j];
	    else if(syst.Contains("MuR")) histname+="MuR_" + syst_shift[j];
	    else if(syst.Contains("MuF")) histname+="MuF_" + syst_shift[j];
	    else if(syst.Contains("pdf_")) histname+="pdf_" + syst_shift[j];
	    else if(syst=="JEC" || syst=="JER") histname+=syst+syst_shift_combine[j];
	    else histname += syst + "_" + syst_shift[j];
	    histname += "/" + histname_base;

	    //TString histname = "Finalselection_"+channel_tags[channel]+"_NNInput/" + histname_base; 

	    if(debug) cout << "histname: " << histname << endl;

	    TH1F* h_out = (TH1F*) f_in->Get(histname);


	    //h_out->Scale(3.8);
	    // change data and qcd to the required output name
	    if(proc.Contains("DATA")) proc = "data_obs";
	    if(proc.Contains("QCD")) proc = "QCD";
	    if(proc.Contains("HHtoWWbbSL")){ // for inference: change HH names
	      proc.ReplaceAll("HHtoWWbbSL_cHHH", "ggHH_kl_");
	      proc += "_kt_1_hbbhww";
	    }
	    TString histname_out = histname_base + "_" + region_tags[region] + channel_tags[channel] + "__" + proc + "_" + AnalysisTool::yeartag;
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
