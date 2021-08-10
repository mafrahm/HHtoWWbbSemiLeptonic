#include "../include/cosmetics.h"
#include "../include/constants.h"
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
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>

using namespace std;

void cosmetics();

//channel = ech, much, comb
void AnalysisTool::PlotLimitsCombine(TString channel){
  /*
  ==========================================
  |                                          |
  |  handy script to make a nice limit plot  |
  |                                          |
  ==========================================   */


  //shortcut to modifications:
  bool with_data = false;
  cout << "Channel: " << channel << endl;

  //0) general cosmetics
  cosmetics();

  //2) (TODO) Read in cross sections (?)


  // Read in limits
  TString path = AnalysisTool::combine_path + "output/";

  TString varname = "HHtoWWbbSL_cHHH";
  vector<TString> nodes_tag = {"0","1","2p45","5"};
  vector<double> nodes = {0,1,2.45,5};
  int n_points = nodes.size();

  vector<double> HHtheory_xsecs = {7.8179, 3.4490, 1.4551, 10.532}; // fb

  // Read limits from rootfiles
  vector<double> expected, expected_high_68, expected_high_95, expected_low_68, expected_low_95, observed;

  for(int i=0; i<n_points; i++){
    TString filename = path + "higgsCombine" + varname + nodes_tag[i] + ".AsymptoticLimits.mH120.root";
    TFile* infile = new TFile(filename, "READ");

    TTreeReader Reader("limit", infile);
    TTreeReaderValue<float> quantile(Reader, "quantileExpected");
    TTreeReaderValue<double> r(Reader, "limit");


    while (Reader.Next()) {
      float q = *quantile;
      double rr = *r;
      //rr *= g_theory->Eval(nodes[i]);
      rr *= HHtheory_xsecs[i];
      //rr /= HHtheory_xsecs[1]; // normalize on node 1

      if(q<0.) observed.emplace_back(rr);
      else if(q<0.1) expected_low_95.emplace_back(rr);
      else if(q<0.4) expected_low_68.emplace_back(rr);
      else if(q<0.8) expected.emplace_back(rr);
      else if(q<0.9) expected_high_68.emplace_back(rr);
      else           expected_high_95.emplace_back(rr);
    }
  }

  // (TODO) Interpolate linearly between nodes

  // (TODO) find intersections (cHHH limits)



  //5) convert to upper and lower errors to be used in TGraphAsymmErrors

  vector<double> expected_up_68, expected_down_68, expected_up_95, expected_down_95;
  for(int i=0; i<n_points; i++){
    expected_up_68.push_back(expected_high_68[i] - expected[i]);
    expected_up_95.push_back(expected_high_95[i] - expected[i]);
    expected_down_68.push_back(expected[i] - expected_low_68[i]);
    expected_down_95.push_back(expected[i] - expected_low_95[i]);
  }



  //6) build graph objects
  TGraphAsymmErrors* g_expected_68 = new TGraphAsymmErrors(n_points,&nodes[0],&expected[0],0,0,&expected_down_68[0], &expected_up_68[0]);
  TGraphAsymmErrors* g_expected_95 = new TGraphAsymmErrors(n_points,&nodes[0],&expected[0],0,0,&expected_down_95[0], &expected_up_95[0]);

  //TGraph* g_theory, g_theory_up, g_theory_down .....

  TGraph* g_expected = new TGraph(n_points,&nodes[0],&expected[0]);
  TGraph* g_observed = new TGraph(n_points,&nodes[0],&observed[0]);



  //7) cosmetics

  //g_theory ....

  g_observed->SetLineWidth(3);
  g_observed->SetLineStyle(1);
  g_expected->SetLineWidth(3);
  g_expected->SetLineStyle(2);
  g_expected_68->SetFillStyle(1001);
  g_expected_95->SetFillStyle(1001);
  g_expected_68->SetFillColor(kGreen+1);
  g_expected_95->SetFillColor(kOrange);
  g_expected_68->SetLineWidth(0);
  g_expected_95->SetLineWidth(0);

  g_expected_95->SetMaximum(10000);
  g_expected_95->SetMinimum(0.1);
  g_expected_95->SetTitle("");

  //8) Draw Graphs
  TCanvas* c = new TCanvas("c", "Nice limit plot", 800,600);
  gPad->SetLogy();
  // gPad->SetBottomMargin(0.13);
  // gPad->SetLeftMargin(0.16);
  // gPad->SetRightMargin(0.06);
  g_expected_95->Draw("A3");
  g_expected_68->Draw("3 SAME");
  g_expected->Draw("SAME");
  if(with_data) g_observed->Draw("SAME");

  //9) Legend
  TLegend *leg;
  leg = new TLegend(0.60,0.67,0.95,0.92,"");//x+0.1
  //leg->SetHeader("95% CL upper limits");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.041);
  leg->SetHeader("95% CL upper limit");
  ((TLegendEntry*)leg->GetListOfPrimitives()->First())->SetTextSize(0.045);
  if(with_data)leg->AddEntry(g_observed, "Observed","L");
  leg->AddEntry(g_expected, "Expected","L");
  leg->AddEntry(g_expected_68, "68% expected","F");
  leg->AddEntry(g_expected_95, "95% expected","F");
  leg->Draw();




  //10) CMS tags
  TString infotext = infotexts.at(AnalysisTool::year);
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.965);
  text1->SetTextFont(42);
  text1->SetTextSize(0.046);
  text1->SetY(0.99);
  text1->Draw();

  TString cmstext = "CMS work in progress";
  TLatex *text2 = new TLatex(3.5, 24, cmstext);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.15);
  text2->SetTextFont(62);
  text2->SetTextSize(0.072);
  text2->SetY(0.905);
  //text2->Draw();

  TString preltext = "Supplementary";
  TLatex *text3 = new TLatex(3.5, 24, preltext);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.263);
  text3->SetTextFont(52);
  text3->SetTextSize(0.05);
  text3->SetY(0.893);
  // text3->Draw();


  //12) care about axes
  TH1D* h = (TH1D*)g_expected_95->GetHistogram();
  h->GetXaxis()->SetRangeUser(nodes[0], nodes[n_points-1]);
  h->SetXTitle("#kappa_#lambda");
  h->SetYTitle("#sigma_{HH#rightarrow bbWW(qql#nu)} [fb]");
  //h->SetYTitle("limits");
  h->GetYaxis()->SetTitleSize(0.048);
  h->GetYaxis()->SetTitleOffset(1.05);
  h->Draw("AXIS SAME");
  gPad->SetTopMargin(0.06);
  gPad->SetLeftMargin(0.11);
  gPad->SetRightMargin(0.035);
  gPad->SetBottomMargin(0.11);




  c->SaveAs("limitplot_combine_mc_fullsyst.eps");
  c->SaveAs("limitplot_combine_mc_fullsyst.pdf");
}


void cosmetics(){

  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.055, "XYZ");
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(505, "XYZ");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
}
