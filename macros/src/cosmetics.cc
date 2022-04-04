#include <TMultiGraph.h>
#include <TPad.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TLatex.h>
#include "../include/cosmetics.h"


void DrawCMSText(bool bottom) {
  // Lumi text
  TString infotext = "35.9 fb^{-1} (13 TeV)";
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.90);
  text1->SetTextFont(42);
  text1->SetTextSize(0.045);
  text1->SetY(0.95);
  text1->Draw("SAME");
  // CMS Text
  bool right = false; // CMS text on the right side
  TLatex *text2 = new TLatex(3.5, 24, "CMS");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.22);
  if(right) text2->SetX(0.7);
  text2->SetTextFont(62);
  text2->SetTextSize(0.05);
  text2->SetY(0.77);
  if(bottom) text2->SetY(0.37);
  //text2->SetY(0.92);
  text2->Draw();

  TLatex *text3 = new TLatex(3.5, 24, "Work in progress");
  //TLatex *text3 = new TLatex(3.5, 24, "Private work");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.22);
  if(right) text3->SetX(0.7);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  text3->SetY(0.68);
  if(bottom) text3->SetY(0.28);
  //text3->SetY(0.83);
  text3->Draw();

  // Simulation:
  TLatex *text4 = new TLatex(3.5, 24, "Simulation");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.22);
  if(right) text4->SetX(0.7);
  text4->SetTextFont(52);
  text4->SetTextSize(0.035);
  text4->SetY(0.72);
  if(bottom) text4->SetY(0.32);
  //text4->SetY(0.87);
  text4->Draw();
}

TPad* SetupPad() {
  Float_t yplot = 0.65;
  Float_t yratio = 0.34;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y1, y2, y3;                           //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3-yplot;                                //     |     pad1    |
  y1 = y2-yratio;                               //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_pad = new TPad("pad1", "Control Plots 2", x1, y1, x2, y3);

  m_pad->SetTopMargin(0.05);
  m_pad->SetBottomMargin(0.16);
  m_pad->SetLeftMargin(0.19);
  m_pad->SetRightMargin(0.05);

  return m_pad;
}

TPad* SetupRatioPad() {
  Float_t yplot = 0.65;
  Float_t yratio = 0.34;
  Float_t yspace = 0.02;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y1, y2, y3;                           //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3 - yplot - yspace/2.;                  //     |     pad1    |
  y1 = y2 + yspace/2. - yratio;                 //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_rp = new TPad("rp1", "Ratio2", x1, y1, x2, y2);

  m_rp->SetTopMargin(0.0);
  m_rp->SetBottomMargin(0.35);
  m_rp->SetLeftMargin(0.19);
  m_rp->SetRightMargin(0.05);

  return m_rp;
}

TPad* SetupRatioPadTop() {
  Float_t yplot = 0.65;
  Float_t yspace = 0.02;

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //  coordinates:
  // set up the coordinates of the two pads:    //
  Float_t y2, y3;                               //  y3 +-------------+
  y3 = 0.99;                                    //     |             |
  y2 = y3 - yplot + yspace/2.;                  //     |     pad1    |
  //                                            //  y2 |-------------|
  Float_t x1, x2;                               //     |     rp1     |
  x1 = 0.01;                                    //  y1 +-------------+
  x2 = 0.99;                                    //     x1            x2
  //
  // No Pad 2!

  TPad* m_rp_top = new TPad("pad1", "Control Plots 2", x1, y2, x2, y3);


  m_rp_top->SetTopMargin(0.085);
  m_rp_top->SetBottomMargin(0.0);
  m_rp_top->SetLeftMargin(0.19);
  m_rp_top->SetRightMargin(0.05);

  return m_rp_top;
}

void HistCosmetics(TH1* hist, bool ratio) {
  hist->SetLineWidth(2);
  //hist->SetMarkerStyle(8);
  //hist->SetMarkerSize(0.4);
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  hist->GetYaxis()->SetNdivisions(505);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset
  hist->GetYaxis()->SetTitleOffset(1.55);

  if (ratio)
  {
    hist->GetYaxis()->SetTitleOffset(1.7);
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetXaxis()->SetTickSize(0.07);
    hist->GetYaxis()->SetTitleSize(15);
    hist->GetYaxis()->CenterTitle();
    //hist->GetYaxis()->SetRangeUser(0.3, 1.7);
    hist->GetYaxis()->SetRangeUser(0.5, 1.5);
    hist->GetYaxis()->SetLabelSize(14);
  }
  else
  {
    hist->GetXaxis()->SetTitleOffset(1.3);
  }
}

void HistCosmetics(TGraph* hist, bool ratio) {
  hist->SetLineWidth(2);
  //hist->SetMarkerStyle(8);
  //hist->SetMarkerSize(0.4);
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset
  hist->GetYaxis()->SetTitleOffset(2);
  if (ratio)
  {
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetYaxis()->SetTitleOffset(2);
    hist->GetYaxis()->SetTitleSize(18);
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetLabelSize(12);
    hist->GetXaxis()->SetTickSize(0.07);
  }
}


void HistCosmetics(TMultiGraph* hist, bool ratio) {
  hist->SetTitle("");

  // X label
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetLabelSize(16);
  // X title
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetTitleSize(18);

  // Y label
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetLabelSize(16);
  // Y title
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetTitleSize(18);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetTickSize(0.037);
  // hist->SetMinimum(0);

  // offset
  hist->GetYaxis()->SetTitleOffset(2);
  if (ratio)
  {
    hist->GetXaxis()->SetTitleOffset(3);
    hist->GetYaxis()->SetTitleOffset(2);
    hist->GetXaxis()->SetTickSize(0.07);
    hist->GetYaxis()->SetTitleSize(18);
    hist->GetYaxis()->CenterTitle();
  }
}
