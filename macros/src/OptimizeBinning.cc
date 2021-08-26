#include "../include/cosmetics.h"
#include "../include/Tools.h"

using namespace std;


// optimizeBinning: speichert Vektor ab, mit welchem rebinned werden soll
// signal: soll flat sein. backgrounds: soll nicht komplett leer sein


void AnalysisTool::FindOptimizeBinning(int N_bins, TString signal, vector<TString> backgrounds, TString channel){
  bool debug = false;
  if(debug) cout << "hello from FindOptimizeBinning :>" << endl;
  TString infilename_signal = AnalysisTool::base_path  + AnalysisTool::year + "/" + AnalysisTool::NN_tag + "NOMINAL/uhh2.AnalysisModuleRunner.MC." + signal + "_" + yeartag + ".root"; 
  TFile* f_signal = new TFile(infilename_signal);

  
  TString histname = channel_to_histname[channel];
  if(debug) cout << "histname: " << histname << endl;
  //TString histname_signal = channel + "_DNNoutput" + to_string(region) + "_nominal/NNout" + to_string(region);
  TH1F* h_signal = (TH1F*) f_signal->Get(histname);
  double events_per_bin = h_signal->Integral()/N_bins;
  if(debug) cout << "Events per bin in final result: " << events_per_bin << endl;
  vector<double> bins = {0.};
  int bin_count = 1;
  double N_events = 0;
  if(debug) cout << "Number of bins in input histogram (should be 1000): "<< h_signal->GetNbinsX() << endl;
  for(int i=1; i<h_signal->GetNbinsX()+1; i++){
    //if(debug) cout << "bin count: " << bin_count << endl;
    if(bin_count==N_bins) break;
    N_events+= h_signal->GetBinContent(i);
    //if(debug) cout << "N events: " << N_events << endl;
    if(N_events >= (double)(events_per_bin*bin_count)) {
      if(debug) cout << "bin: " << h_signal->GetBinLowEdge(i) << endl;
      if(debug) cout << "N events: " << N_events << endl;

      bins.push_back(h_signal->GetBinLowEdge(i));
      bin_count++;
    }
  }
  bins.push_back(1.0);
  //if(debug) cout << "number of bins: " << bins.size()-1 << endl;
  for(unsigned int i=0; i<bins.size(); i++){
    //if(debug) cout << "binEdge at " << i << ": " << bins.at(i) << endl;
  }
    
  channel_to_bins.insert(pair<TString, vector<double>>(channel, bins));
  //ApplyOptimizeBinning(h_signal, bins);
}

// ApplyOptimizeBinning; wendet optimales Binning an

TH1F* AnalysisTool::ApplyOptimizeBinning(TH1F *hist, vector<double> bins){
  bool debug = false;
  // if(debug) cout << "Hello from ApplyOptimizeBinning :)" << endl;
  
  TH1F* h_out = dynamic_cast<TH1F*>(hist->Rebin(bins.size()-1, "hnew", &bins[0]));

  if(debug) cout << "ApplyOptimizeBinning: Number of bins in output hist: " << h_out->GetNbinsX() << endl;
  for(int i=1; i<h_out->GetNbinsX()+1; i++){
    if(h_out->Integral() < 100.) break; // quick hack to not consider HH here
    if(h_out->GetBinContent(i)<1){
      TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
      c1->cd();
      h_out->Draw("HIST");
      c1->SaveAs(uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/test.eps");
      c1->Close();
      //throw runtime_error("not enough events in this hist in bin "+to_string(i));
    }
    //if(h_out->GetBinError(i)>10) throw runtime_error("BinError is too large in bin "+to_string(i));
    }

  /*
  TCanvas* c2 = new TCanvas("c1", "c1", 600, 600);
  c2->cd();
  h_out->Draw("HIST");
  c2->SaveAs(uhh2_path + "HHtoWWbbSemiLeptonic/macros/Plots/test.eps");
  c2->Close/();
  */

  return h_out;
}
