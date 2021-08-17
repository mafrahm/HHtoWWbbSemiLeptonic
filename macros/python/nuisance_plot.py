import ROOT
import tdrstyle
import pandas as pd
import numpy as np

df = pd.read_csv('nuisances.csv')
df = df.iloc[::-1].reset_index()

tdrstyle.setTDRStyle()

g_prefit = ROOT.TGraph()
g_prefit_68 = ROOT.TGraphErrors()
g_prefit_68.SetFillStyle(1001)
g_prefit_68.SetFillColor(ROOT.kGreen + 1)

g_prefit_95 = ROOT.TGraphErrors()
g_prefit_95.SetFillStyle(1001)
g_prefit_95.SetFillColor(ROOT.kOrange)

g_postfit_b = ROOT.TGraphAsymmErrors()
g_postfit_b.SetLineColor(ROOT.kBlack)
g_postfit_b.SetMarkerColor(ROOT.kBlack)
g_postfit_s = ROOT.TGraphAsymmErrors()
g_postfit_s.SetLineColor(ROOT.kGray+1)
g_postfit_s.SetMarkerColor(ROOT.kGray+1)

# f*!&ing ROOT!
for i, row in df.iterrows():
    g_prefit.SetPoint(i,row["prefit"],i+0.5)
    # g_prefit_68.SetPoint(i,row["prefit"],i+0.5)
    # g_prefit_68.SetPointError(i,row["prefit_e"),0
    # g_prefit_95.SetPoint(i,i+0.5,row["prefit"])
    # g_prefit_95.SetPointError(i,0,row["prefit_e"]*2)
    g_postfit_b.SetPoint(i,row["postfit_b"],i+0.35)
    g_postfit_b.SetPointError(i,row["postfit_b_up"],row["postfit_b_down"],0,0)
    g_postfit_s.SetPoint(i,row["postfit_s"],i+0.65)
    g_postfit_s.SetPointError(i,row["postfit_s_up"],row["postfit_s_down"],0,0)

h = ROOT.TH1F("h","axis",df.shape[0],0,df.shape[0])
for i in range(1,df.shape[0]+1): 
    h.GetXaxis().SetBinLabel(i,df["label"][i-1])
    h.SetBinContent(i, -20)
h.SetFillStyle(0)
h.SetFillColor(0)

leg = ROOT.TLegend(0.3,0.95,0.9,0.99)
leg.SetNColumns(2)
leg.SetBorderSize(0)
leg.SetFillStyle(0)
leg.SetTextSize(0.025)
leg.SetTextFont(42)
leg.AddEntry(g_postfit_b, "background only fit","pl")
leg.AddEntry(g_postfit_s, "signal+background fit","pl")

c = ROOT.TCanvas("c","c",600,800)
pad = ROOT.TPad("pad","pad",0.01,0.01,0.99,0.99)
pad.SetTopMargin(0.05)
pad.SetBottomMargin(0.075)
pad.SetLeftMargin(0.25)
pad.SetRightMargin(0.05)
pad.Draw()
pad.cd()
box_68 = ROOT.TBox(-1,0,1,df.shape[0])
box_68.SetFillStyle(1001)
box_68.SetFillColor(ROOT.kGreen+1)
box_95 = ROOT.TBox(-2,0,2,df.shape[0])
box_95.SetFillStyle(1001)
box_95.SetFillColor(ROOT.kOrange)


h.Draw("hbar")
h.GetYaxis().SetTitle("nuisance parameter pull")
h.GetXaxis().SetLabelSize(0.033)
h.GetYaxis().SetLabelSize(0.033)
h.GetYaxis().SetTitleSize(0.04)
h.GetYaxis().SetTitleOffset(0.9)
h.GetYaxis().CenterTitle(True)
h.GetYaxis().SetRangeUser(-2.49,2.49)
box_95.Draw()
box_68.Draw()
# h.Draw("hbar2SAME")
# g_prefit_95.Draw("SAME3")
# g_prefit_68.Draw("SAME3")
# g_prefit.Draw("LSAME")
g_postfit_s.Draw("PSAME")
g_postfit_b.Draw("PSAME")
leg.Draw()
ROOT.gPad.RedrawAxis()

c.Print("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/nuisance_plot.pdf")
c.Print("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/nuisance_plot.eps")
c.Print("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/macros/Plots/nuisance_plot.png")
