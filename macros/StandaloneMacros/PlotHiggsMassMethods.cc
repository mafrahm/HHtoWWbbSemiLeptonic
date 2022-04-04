
using namespace std;

void PlotHiggsMassMethods() {
  
  TString type = "b"; // "b" or "W"

  TString infilename = "/nfs/dust/cms/user/frahmmat/HHtoWWbbSemiLeptonic/2016/Fullselection/ForMassReco_PTJet30/NOMINAL/uhh2.AnalysisModuleRunner.MC.HHtoWWbbSL_cHHH1_2016v3.root";

  TFile* infile = new TFile(infilename);
  TH1F* h_matched = (TH1F*)infile->Get("mHH_reconstructed_much_Matched/M_H_"+type+"_matched");
  TH1F* h_highestPt = (TH1F*)infile->Get("mHH_reconstructed_much_General/MH_"+type+type+"_simple_rebin2");
  TH1F* h_chi2 = (TH1F*)infile->Get("mHH_reconstructed_much_General/MH_"+type+type+"_rebin2");

  h_matched->SetLineColor(1);
  h_highestPt->SetLineColor(810);
  h_chi2->SetLineColor(860);
  h_matched->SetLineWidth(3.);
  h_highestPt->SetLineWidth(3.);
  h_chi2->SetLineWidth(3.);
  
  h_matched->Scale(1/h_matched->Integral());
  h_highestPt->Scale(1/h_highestPt->Integral());
  h_chi2->Scale(1/h_chi2->Integral());
  
  if(type=="b") h_matched->GetXaxis()->SetTitle("M_{bb} [GeV]"); 
  if(type=="W") h_matched->GetXaxis()->SetTitle("M_{T,WW} [GeV]"); 
  h_matched->SetTitle("");
  h_matched->GetYaxis()->SetTitle("#DeltaN/N");
  h_matched->SetStats(0);
  h_matched->GetXaxis()->SetTitleSize(.045);
  h_matched->GetYaxis()->SetTitleSize(.045);
  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  TLegend *leg = new TLegend(0.47,0.76,0.90,0.89,"");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.032);
  //leg->SetHeader("reconstruction method");
  //leg->AddEntry(h_matched, "matched", "L");
  //leg->AddEntry(h_highestPt, "highest-p_{T}","L");
  //leg->AddEntry(h_chi2, "#chi^{2}","L");
  leg->AddEntry(h_matched, "correct assignment", "L");
  leg->AddEntry(h_highestPt, "highest-p_{T} reconstruction","L");
  leg->AddEntry(h_chi2, "#chi^{2} reconstruction","L");

  //h_matched->SetMaximum(0.15);
  h_matched->Draw("HIST");
  h_chi2->Draw("HIST SAME");
  h_highestPt->Draw("HIST SAME");
  


  TString infotext = "35.9 fb^{-1} (13 TeV)";
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.90);
  text1->SetTextFont(42);
  text1->SetTextSize(0.045);
  text1->SetY(0.948);
  text1->Draw("SAME");

  // CMS Text
  bool right = false; // CMS text on the right side
  TLatex *text2 = new TLatex(3.5, 24, "CMS");
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.20);
  if(right) text2->SetX(0.7);
  text2->SetTextFont(62);
  text2->SetTextSize(0.05);
  text2->SetY(0.87);
  //text2->SetY(0.92);
  text2->Draw();

  //TLatex *text3 = new TLatex(3.5, 24, "Work in progress");
  TLatex *text3 = new TLatex(3.5, 24, "Private work");
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.20);
  if(right) text3->SetX(0.7);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  text3->SetY(0.78);
  //text3->SetY(0.83);
  text3->Draw();

  // Simulation:
  TLatex *text4 = new TLatex(3.5, 24, "Simulation");
  text4->SetNDC();
  text4->SetTextAlign(13);
  text4->SetX(0.20);
  if(right) text4->SetX(0.7);
  text4->SetTextFont(52);
  text4->SetTextSize(0.035);
  text4->SetY(0.82);
  //text4->SetY(0.87);
  text4->Draw();

  leg->Draw();
  c1->SetLeftMargin(0.16);
  c1->SetBottomMargin(0.13);
  c1->SaveAs(type+type+"_massRecoMethods.pdf");
  delete c1;
}
