#include "UHH2/HHtoWWbbSemiLeptonic/include/HHPDFHists.h"
//#include "UHH2/LQToTopMu/include/HypothesisHistsOwn.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include <math.h>
#include <sstream>

#include "TH1F.h"
#include "TH2D.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;


HHPDFHists::HHPDFHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  cout << "HHPDFHists" << endl;
  
  h_NNoutput0 = ctx.get_handle<double>("NNoutput0");
  h_NNoutput1 = ctx.get_handle<double>("NNoutput1");
  h_NNoutput2 = ctx.get_handle<double>("NNoutput2");
  h_NNoutput3 = ctx.get_handle<double>("NNoutput3");
  h_NNoutput4 = ctx.get_handle<double>("NNoutput4");


  is_mc = ctx.get("dataset_type") == "MC";
  m_oname = ctx.get("dataset_version");
  cout << "m_oname: " << m_oname << endl;
  TString m_pdfname = "NNPDF30_lo_as_0130";
  TString weightpath = ctx.get("PDFWeightPath"); // will save HH PDF weights here
  cout << "File: " << weightpath+m_oname << endl;

  Year year = extract_year(ctx);

  // take_ntupleweights not for QCD and signal ?
  if(year == Year::is2017v1 || year == Year::is2017v2){
    take_ntupleweights = !(m_oname.Contains("QCD") /*|| m_oname.Contains("HH")*/);
  }
  else if (year == Year::is2018){
    take_ntupleweights = !(m_oname.Contains("QCD") /*|| m_oname.Contains("HH")*/ || m_oname.Contains("DibosonNLO"));
  }
  else{
    take_ntupleweights = !(m_oname.Contains("QCD") || m_oname.Contains("ST_tW")/* || m_oname.Contains("HH") || m_oname.Contains("DibosonNLO_ZZ_2L2Nu_2016v3")*/); // what's up with these specifications?
  }

  cout << m_pdfname << endl;
  if(is_mc && !take_ntupleweights){
    // Only take shape effect into account for signals
    if(m_oname.Contains("HH")) m_pdfweights.reset(new PDFWeights(m_pdfname,weightpath+m_oname));
    else m_pdfweights.reset(new PDFWeights(m_pdfname));
  }

  // loop over NN output nodes (max 4)
  for(int x=0; x<4; x++){
    // still need to optimize binning. Probably individually for each output node
    /*
    vector<double> bins;
    if     (x==0) bins = {0,0.4,0.5,0.6,0.7,0.8,0.85,0.9,0.93,0.96,0.98,1.0}; //sr
    else if(x==1) bins = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0}; //ttcr
    else if(x==2) bins = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0}; //stcr
    else if(x==3) bins = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0}; //wdycr
    //else if(x==4) bins = {0,0.3,0.4,0.48,0.56,0.64,0.72,0.8,0.85,0.9,1.0}; //placeholder
*/
    vector<TString> histo_names_x;
    for(int i=0; i<100; i++){
      TString name = "NN_out" + to_string(x) + "_PDF_" + to_string(i+1);
      TString title = "NN_out" + to_string(x) + " for PDF No. " + to_string(i+1); 
      
      histo_names_x.emplace_back(name);

      book<TH1F>(name, title, 1000,0,1);
      //book<TH1F>(name, title, bins.size()-1, &bins[0]);

    }
    histo_names.emplace_back(histo_names_x);
  }
}

void HHPDFHists::fill(const Event & event){
  double weight = event.weight;
  if(!is_mc) return;

  vector<double> NNoutput;
  NNoutput.emplace_back(event.get(h_NNoutput0));
  NNoutput.emplace_back(event.get(h_NNoutput1));
  NNoutput.emplace_back(event.get(h_NNoutput2));
  NNoutput.emplace_back(event.get(h_NNoutput3));
  //NNoutput.emplace_back(event.get(h_NNoutput4));



  //cout << "Number of systweights:"  << event.genInfo->systweights().size() << endl;
  if(event.genInfo->systweights().size() < 110 && take_ntupleweights) {
    noSysweightsCount++;
    cout << "HHPDFHists: number of events with not enough systweights: " << noSysweightsCount << endl; // couting does not work properly
    return; // just sort out all the events with not enough systweights. Is that allowed?  --> probably not, should be fixed or these events should be return false'd
  }
  if(event.genInfo->systweights().size() < 100 && take_ntupleweights) throw runtime_error("In HHPDFHists.cxx: Systweights in event.genInfo() is empty but ntupleweights shall be taken. Is this correct? In this case add exception to take_ntupleweights.");
  if(event.genInfo->systweights().size() > 110 && (!take_ntupleweights)) throw runtime_error("In HHPDFHists.cxx: Systweights in event.genInfo() is NOT empty but take_ntupleweights is set to 'false'. Is this correct? In this case Thomas says the genInfo weight should be used. Add this sample to take_ntupleweights");


  // Fill histograms
  if(take_ntupleweights) {
    for(unsigned int x=0; x<NNoutput.size(); x++){
      for(int i=0; i<100; i++){

	// what's up with the (i+9) ?
	double pdf_weight = event.genInfo->systweights().at(i+9);
	double fillweight = weight * pdf_weight/event.genInfo->originalXWGTUP();
	
	TString name = histo_names[x][i];
	hist(name)->Fill(NNoutput[x], fillweight);
      }
    }
  }
  else{
    std::vector<double> weights = m_pdfweights->GetWeightList(event);
    for(unsigned int x=0; x<NNoutput.size(); x++){
      for(int i=0; i<100; i++){
	double fillweight = weight*weights[i];

	TString name = histo_names[x][i];
	hist(name)->Fill(NNoutput[x], fillweight);
      }
    }
  }
}
HHPDFHists::~HHPDFHists(){}
