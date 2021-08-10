#include "../include/cosmetics.h"
#include "../include/plot_styles.C"
#include "../include/Tools.h"
#include <THStack.h>

void AnalysisTool::postFitPlot() {
  cout << "postFitPlot:" << endl;
  cout << "Line: " << __LINE__ << endl;

  const TString signaltag = "HHtoWWbbSL_cHHH1";


  const TString file_name_shapes = AnalysisTool::combine_path + "input/NN_combine_histograms_" + AnalysisTool::year + ".root";
  const TString file_name_postfit = AnalysisTool::combine_path + "output/fitDiagnostics" + signaltag + ".root";
  cout << file_name_postfit << endl;
  const TString prefix = "shapes_fit_b/";
  // const TString prefix = "shapes_prefit/";
  const TString channel = "ch1"; // ch1-ch8
  const TString postfix = "";

  const vector<TString> backgrounds = {"Diboson", "TTV", "DYJets", "WJets", "SingleTop", "QCD", "TTbar"};

  // binning ...

  vector<TH1F*> h_backgrounds = {}; 

  TFile *fpostfit = new TFile(file_name_postfit);
  cout << prefix+channel+postfix << endl;
  TGraphAsymmErrors *h_data = (TGraphAsymmErrors*) fpostfit->Get(prefix + channel + postfix + "/data")->Clone();
  TH1F *h_signal = (TH1F*) fpostfit->Get("shapes_fit_s/" + channel + postfix + "/" + signaltag)->Clone();
  h_signal->SetDirectory(0);
  h_signal->Scale(((TH1F*)fpostfit->Get("shapes_prefit/" + channel + postfix + "/" + signaltag))->Integral()/h_signal->Integral());
  TH1F *h_err =  (TH1F*) fpostfit->Get(prefix + channel + postfix + "/total_background")->Clone();
  h_err->SetDirectory(0);

  for(unsigned int i=0; i<backgrounds.size(); i++){
    TH1F *h_bckg = (TH1F*) fpostfit->Get(prefix + channel + postfix + "/" + backgrounds[i])->Clone();
    h_bckg->SetDirectory(0);
    h_backgrounds.emplace_back(h_bckg);
  }
  fpostfit->Close();
  delete fpostfit;




  TGraphErrors* g_ratio = new TGraphErrors(h_err->GetNbinsX());
  TGraphErrors* g_ratio_err_stat = new TGraphErrors(h_err->GetNbinsX());
  TGraphErrors* g_ratio_err_tot = new TGraphErrors(h_err->GetNbinsX());

  int nbins = h_err->GetNbinsX();
  cout << nbins << endl;
  for (int i = 1; i <= nbins; ++i) {
      // double err_stat = h_stat->GetBinError(i);
      double err_tot = h_err->GetBinError(i);
      double err_num = h_data->GetErrorY(i-1);
      double x,num;
      h_data->GetPoint(i-1,x,num);
      double den = h_err->GetBinContent(i);
      // double ratio_err_stat = err_stat / h_stat->GetBinContent(i);

      // std::cout << "Error in bin " << i << std::endl;
      // std::cout << "total: " << ratio_err_tot << std::endl;
      // std::cout << "syst: " << ratio_err_stat << std::endl;

      x = h_err->GetBinCenter(i);

      double w = h_err->GetBinWidth(i);
      double ratio_err_tot = err_tot / den;
      double ratio_err_num = err_num / num;
      g_ratio->SetPoint(i-1, x, num / den);
      g_ratio->SetPointError(i-1,w/2.,ratio_err_num * (num/den));
      // g_ratio_err_stat->SetPoint(i,x,1.);
      g_ratio_err_tot->SetPoint(i-1,x,1.);
      // g_ratio_err_stat->SetPointError(i,h_data->GetBinWidth(i)/2.,ratio_err_stat);
      g_ratio_err_tot->SetPointError(i-1,w/2.,ratio_err_tot);

      num /= w;
      err_num /= w;
      h_data->SetPoint(i-1,x,num);
      h_data->SetPointError(i-1,0,0,err_num,err_num);
  }

  setCMSStyle();
  THStack *h_bkg = new THStack("hs","");


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_signal->SetLineColor(1);
  h_signal->SetLineStyle(2);
  h_signal->SetLineWidth(2);


  for(unsigned int i=0; i<backgrounds.size(); i++){
    h_backgrounds[i]->SetFillColor(proc_colors[backgrounds[i]]);
    h_backgrounds[i]->SetLineWidth(0);
    h_backgrounds[i]->Scale(1., "width");
  }
  // h_data->Scale(1.,"width");
  h_err->Scale(1., "width");
  h_signal->Scale(1.,"width");

  for(unsigned int i=0; i<backgrounds.size(); i++){
    h_bkg->Add(h_backgrounds[i], "hist");
  }
  


  TCanvas* c = new TCanvas("cfit","cfit",600,600);
  TPad* pad_top = SetupRatioPadTop();
  TPad* pad_bot = SetupRatioPad();
  pad_top->Draw();
  pad_bot->Draw();
  pad_top->cd();
  pad_top->SetLogy(true);

  h_bkg->SetMaximum(max(h_bkg->GetMaximum()*3, h_data->GetMaximum())*3);
  // h_bkg->SetMinimum(min(h_bkg->GetMinimum()/3, h_data->GetMinimum())/3);
  h_bkg->SetMinimum(1e-4);
  h_err->SetFillColor(921);
  h_err->SetLineWidth(0);
  h_err->SetFillStyle(3005);
  h_bkg->Draw();
  h_bkg->GetYaxis()->SetTitle("Events/GeV");
  h_bkg->GetXaxis()->SetLabelSize(h_bkg->GetXaxis()->GetLabelSize()/0.65);
  h_bkg->GetYaxis()->SetLabelSize(h_bkg->GetYaxis()->GetLabelSize()/0.65);
  h_bkg->GetXaxis()->SetTitleSize(h_bkg->GetXaxis()->GetTitleSize()/0.65);
  h_bkg->GetYaxis()->SetTitleSize(h_bkg->GetYaxis()->GetTitleSize()/0.65);
  h_bkg->GetYaxis()->SetTitleOffset(1.);
  h_err->Draw("E2SAME");
  h_signal->Draw("HIST SAME");
  h_data->Draw("PZSAME");

  TLegend* leg = new TLegend(0.55,0.5,0.95,0.9);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h_data, "Data", "pl");
  for(unsigned int i=0; i<backgrounds.size(); i++){
    leg->AddEntry(h_backgrounds[i], backgrounds[i], "f");
  }
  leg->AddEntry(h_err, "tot. uncertainty", "f");
  leg->AddEntry(h_signal, "signal", "l");
  leg->Draw();

  gPad->RedrawAxis();

  pad_bot->cd();
  pad_bot->SetLogy(false);

  g_ratio_err_tot->GetXaxis()->SetLimits(h_err->GetXaxis()->GetXmin(), h_err->GetXaxis()->GetXmax());
  g_ratio_err_stat->SetFillColor(920);
  g_ratio_err_tot->SetFillColor(921);
  g_ratio_err_tot->GetYaxis()->SetRangeUser(0.35, 1.65);
  g_ratio_err_tot->GetYaxis()->CenterTitle();
  g_ratio_err_tot->GetYaxis()->SetTitle("data/bkg.");
  g_ratio_err_tot->GetXaxis()->SetTitle("output node");
  g_ratio_err_tot->GetXaxis()->SetLabelSize(g_ratio_err_tot->GetXaxis()->GetLabelSize()/0.33);
  g_ratio_err_tot->GetYaxis()->SetLabelSize(g_ratio_err_tot->GetYaxis()->GetLabelSize()/0.33);
  g_ratio_err_tot->GetXaxis()->SetTitleSize(g_ratio_err_tot->GetXaxis()->GetTitleSize()/0.33);
  g_ratio_err_tot->GetYaxis()->SetTitleSize(g_ratio_err_tot->GetYaxis()->GetTitleSize()/0.33);
  g_ratio_err_tot->GetYaxis()->SetTitleOffset(.5);
  g_ratio_err_tot->GetXaxis()->SetNdivisions(505);
  g_ratio_err_tot->GetYaxis()->SetNdivisions(505);
  g_ratio->SetMarkerStyle(8);
  g_ratio_err_tot->Draw("A2");
  // g_ratio_err_stat->Draw("SAME 2");
  g_ratio->Draw("SAME PZ");
  gPad->RedrawAxis();

  TString hist_name = channel;
  c->Print(hist_name+".eps");
  c->Print(hist_name+".png");
  c->Print(hist_name+".pdf");

}



