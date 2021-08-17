#include "../include/cosmetics.h"
#include "../include/Tools.h"

using namespace std;

void AnalysisTool::ProduceCombineHistogramsNN(){
  cout << "ProduceCombinedHistograms:"<< endl;
  cout << "year: " << AnalysisTool::yeartag << endl;
  cout << "Line: " << __LINE__ << endl;


  //vector<TString> systematics = {"NOMINAL"};
  vector<TString> systematics = {"nominal", "muid", "pu", "eleid", "elereco", "muiso", "btag_bc", "btag_udsg", "pdf", "scale_TTbar", "scale_DYJets", "scale_WJets", "scale_SingleTop", "scale_Diboson", "scale_TTV"}; // "JEC", "JER"
  vector<TString> syst_shift = {"up", "down"};
  vector<TString> syst_shift_combine = {"Up", "Down"};
  //vector<TString> region_tags = {"catA"};
  vector<TString> channel_tags = {"much", "ech"};
  //vector<TString> channel_tags = {"srmu"};
  vector<TString> region_tags = {"sr", "ttcr", "stcr", "wdycr"};
  //vector<TString> histinname_base = {"srmu_DNNoutput0", "srmu_DNNoutput1", "srmu_DNNoutput2", "srmu_DNNoutput3"};
  //vector<TString> histoutname_base = {"mH"};
  vector<TString> samples_base = {"HHtoWWbbSemiLeptonic_SM", "HHtoWWbbSL_cHHH0", "HHtoWWbbSL_cHHH1", "HHtoWWbbSL_cHHH2p45", "HHtoWWbbSL_cHHH5", "SingleTop", "TTbar", "DYJets", "Diboson", "QCD", "TTV", "WJets", "DATA"}; //, "DATA"

  TString outfilename = AnalysisTool::combine_path + "input/NN_combine_histograms_" + AnalysisTool::year + ".root"; 
  TFile* f_out = new TFile(outfilename, "RECREATE");



  for(unsigned int region = 0; region <region_tags.size(); region++) {
    for(unsigned int channel=0; channel<channel_tags.size(); channel++) {
      cout << "============= Channel: " << channel_tags[channel] << ", Region: " << region_tags[region] << endl;

      for(unsigned int k=0; k<systematics.size(); k++) {
	TString syst = systematics[k];
	cout << "========== Syst: " << syst << endl;
	for(unsigned int j=0; j<syst_shift.size(); j++) {
	  //cout << " === syst_shift: " << systshift[j] << endl;

	  TString infilename_base = AnalysisTool::base_path  + AnalysisTool::year + "/" + AnalysisTool::NN_tag; 
	  cout << infilename_base << endl;



	  for(unsigned int i=0; i<samples_base.size(); i++) {
	    TString proc = samples_base[i];

            TString tag = "MC.";
            if(proc == "DATA") tag = "DATA.";

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

	    cout << "======= Sample " << proc << endl;

	    TString infilename = infilename_base;
	    if(syst.Contains("scale") && !force_nominal) infilename += "scale/";
	    else if(syst=="pdf"       && !force_nominal) infilename += "pdf/";
	    else if((syst=="JEC" || syst =="JER") && !force_nominal) infilename+= syst + syst_shift_combine[j] + "/uhh2.AnalysisModuleRunner."+tag;
	    else infilename += "NOMINAL/uhh2.AnalysisModuleRunner."+tag;
	    infilename += proc + "_" + yeartag + ".root";
	  
	    cout << "infilename: " << infilename << endl;
	    TFile* f_in = new TFile(infilename);

	    //TString histname = histinname_base[channel] + "_";

	    // note: 'region' is an integer from 0 to 3
	    TString histname = channel_tags[channel] + "_DNNoutput"+to_string(region)+"_";
	    if(force_nominal || syst=="nominal") histname+="nominal";
	    else if(syst.Contains("scale")) histname+="scale_" + syst_shift[j];
	    else histname += syst + "_" + syst_shift[j];

	    histname+="/NN_out"+to_string(region) + "_limits"; // + "_rebin";
	    // e.g. histname = much_DNNoutput0_scale_up/NNout0
	    cout << "histname: " << histname << endl;

	    TH1F* h_out = (TH1F*) f_in->Get(histname);
	    //h_out->Scale(3.8);
	    cout << __LINE__ << endl;
	    // change data and qcd to the required output name
	    if(proc.Contains("DATA")) proc = "data_obs";
	    if(proc.Contains("QCD")) proc = "QCD";
	    //TString histname_out = /*histoutname_base[region] + "_" +*/ channel_tags[channel] + "_" + region_tags[region] + "__" + proc + "_" + AnalysisTool::yeartag;
	    TString histname_out = region_tags[region] + channel_tags[channel] + "_catA" + "__" + proc + "_" + AnalysisTool::yeartag;
	    if(syst != "nominal") histname_out += "__" + syst + syst_shift_combine[j];
	    // e.g. histname_out = srmuch_TTbar_2016v3__scale_TTbarUp
	    cout << "histname_out: " << histname_out << endl;

	    cout << __LINE__ << endl;
	    h_out->SetName(histname_out);
	    cout << __LINE__ << endl;
	    f_out->cd();
	    cout << __LINE__ << endl;
	    h_out->Write();
	    cout << __LINE__ << endl;
	    f_in->Close();
	  }
	}
      }
    }
  }
  
  




  cout << "finished!" << endl;

  
}
