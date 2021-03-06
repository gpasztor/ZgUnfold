{

gStyle->SetOptStat(0);
gStyle->SetPadLeftMargin(0.18);
gStyle->SetPadRightMargin(0.18);
gStyle->SetPadBottomMargin(0.13);

TCanvas* Resp = new TCanvas ("Response", "Response", 700, 650); 
Resp->Divide(2,2); 

TFile *file=0; 
file=TFile::Open("Histos_ch0_err3_sm0_MCf0_PID1_smear0_scale0.root"); 

Resp->cd(1); 
gPad->SetLogx();
gPad->SetLogy();
gPad->SetLogz();
gPad->SetTicks();
responseMC->SetTitle("Electron channel");
responseMC->GetXaxis()->SetTitle("Reconstructed photon p_{T} [GeV]"); 
responseMC->GetYaxis()->SetTitle("True photon p_{T} [GeV]"); 
responseMC->GetZaxis()->SetTitle("Entries"); 
responseMC->GetXaxis()->SetMoreLogLabels(); 
responseMC->GetYaxis()->SetMoreLogLabels(); 
responseMC->GetXaxis()->SetTitleOffset(1.3); 
responseMC->GetYaxis()->SetTitleOffset(1.7); 
responseMC->GetZaxis()->SetTitleOffset(1.4); 
responseMC->GetXaxis()->SetLabelFont(62); 
responseMC->GetYaxis()->SetLabelFont(62); 
responseMC->GetZaxis()->SetLabelFont(62); 
responseMC->GetXaxis()->SetTitleFont(62); 
responseMC->GetYaxis()->SetTitleFont(62); 
responseMC->GetZaxis()->SetTitleFont(62); 
responseMC->GetXaxis()->SetLabelSize(0.045); 
responseMC->GetYaxis()->SetLabelSize(0.045); 
responseMC->GetZaxis()->SetLabelSize(0.045); 
responseMC->GetXaxis()->SetTitleSize(0.048); 
responseMC->GetYaxis()->SetTitleSize(0.048); 
responseMC->GetZaxis()->SetTitleSize(0.048); 
responseMC->GetXaxis()->SetNoExponent(); 
responseMC->GetYaxis()->SetNoExponent(); 
responseMC->Draw("COLZ"); 

TLatex latex;
latex.SetTextFont(62);
latex.SetTextSize(0.055);    
latex.DrawLatex(12,700,"CMS simulation internal");

Resp->cd(3); 
gPad->SetLogx();
gPad->SetLogy();
gPad->SetLogz();
gPad->SetTicks();
responseMassMC->SetTitle("Muon channel");
responseMassMC->GetXaxis()->SetTitle("Reconstructed ll#gamma mass [GeV]"); 
responseMassMC->GetYaxis()->SetTitle("True ll#gamma mass [GeV]"); 
responseMassMC->GetZaxis()->SetTitle("Entries"); 
responseMassMC->GetXaxis()->SetMoreLogLabels(); 
responseMassMC->GetYaxis()->SetMoreLogLabels(); 
responseMassMC->GetXaxis()->SetTitleOffset(1.3); 
responseMassMC->GetYaxis()->SetTitleOffset(1.7); 
responseMassMC->GetZaxis()->SetTitleOffset(1.4); 
responseMassMC->GetXaxis()->SetLabelFont(62); 
responseMassMC->GetYaxis()->SetLabelFont(62); 
responseMassMC->GetZaxis()->SetLabelFont(62); 
responseMassMC->GetXaxis()->SetTitleFont(62); 
responseMassMC->GetYaxis()->SetTitleFont(62); 
responseMassMC->GetZaxis()->SetTitleFont(62); 
responseMassMC->GetXaxis()->SetLabelSize(0.045); 
responseMassMC->GetYaxis()->SetLabelSize(0.045); 
responseMassMC->GetZaxis()->SetLabelSize(0.045); 
responseMassMC->GetXaxis()->SetTitleSize(0.048); 
responseMassMC->GetYaxis()->SetTitleSize(0.048); 
responseMassMC->GetZaxis()->SetTitleSize(0.048); 
responseMassMC->GetXaxis()->SetNoExponent(); 
responseMassMC->GetYaxis()->SetNoExponent(); 
responseMassMC->Draw("COLZ"); 

TLatex latex;
latex.SetTextFont(62);
latex.SetTextSize(0.055);    
latex.DrawLatex(55,800,"CMS simulation internal");

file=TFile::Open("Histos_ch1_err3_sm0_MCf0_PID1_smear0_scale0.root"); 

Resp->cd(2); 
gPad->SetLogx();
gPad->SetLogy();
gPad->SetLogz();
gPad->SetTicks();
responseMC->SetTitle("Muon channel");
responseMC->GetXaxis()->SetTitle("Reconstructed photon p_{T} [GeV]"); 
responseMC->GetYaxis()->SetTitle("True photon p_{T} [GeV]"); 
responseMC->GetZaxis()->SetTitle("Entries"); 
responseMC->GetXaxis()->SetMoreLogLabels(); 
responseMC->GetYaxis()->SetMoreLogLabels(); 
responseMC->GetXaxis()->SetTitleOffset(1.3); 
responseMC->GetYaxis()->SetTitleOffset(1.7); 
responseMC->GetZaxis()->SetTitleOffset(1.4); 
responseMC->GetXaxis()->SetLabelFont(62); 
responseMC->GetYaxis()->SetLabelFont(62); 
responseMC->GetZaxis()->SetLabelFont(62); 
responseMC->GetXaxis()->SetTitleFont(62); 
responseMC->GetYaxis()->SetTitleFont(62); 
responseMC->GetZaxis()->SetTitleFont(62); 
responseMC->GetXaxis()->SetLabelSize(0.045); 
responseMC->GetYaxis()->SetLabelSize(0.045); 
responseMC->GetZaxis()->SetLabelSize(0.045); 
responseMC->GetXaxis()->SetTitleSize(0.048); 
responseMC->GetYaxis()->SetTitleSize(0.048); 
responseMC->GetZaxis()->SetTitleSize(0.048); 
responseMC->GetXaxis()->SetNoExponent(); 
responseMC->GetYaxis()->SetNoExponent(); 
responseMC->Draw("COLZ"); 

TLatex latex;
latex.SetTextFont(62);
latex.SetTextSize(0.055);    
latex.DrawLatex(12,700,"CMS simulation internal");

Resp->cd(4); 
gPad->SetLogx();
gPad->SetLogy();
gPad->SetLogz();
gPad->SetTicks();
responseMassMC->SetTitle("Muon channel");
responseMassMC->GetXaxis()->SetTitle("Reconstructed ll#gamma mass [GeV]"); 
responseMassMC->GetYaxis()->SetTitle("True ll#gamma mass [GeV]"); 
responseMassMC->GetZaxis()->SetTitle("Entries"); 
responseMassMC->GetXaxis()->SetMoreLogLabels(); 
responseMassMC->GetYaxis()->SetMoreLogLabels(); 
responseMassMC->GetXaxis()->SetTitleOffset(1.3); 
responseMassMC->GetYaxis()->SetTitleOffset(1.7); 
responseMassMC->GetZaxis()->SetTitleOffset(1.4); 
responseMassMC->GetXaxis()->SetLabelFont(62); 
responseMassMC->GetYaxis()->SetLabelFont(62); 
responseMassMC->GetZaxis()->SetLabelFont(62); 
responseMassMC->GetXaxis()->SetTitleFont(62); 
responseMassMC->GetYaxis()->SetTitleFont(62); 
responseMassMC->GetZaxis()->SetTitleFont(62); 
responseMassMC->GetXaxis()->SetLabelSize(0.045); 
responseMassMC->GetYaxis()->SetLabelSize(0.045); 
responseMassMC->GetZaxis()->SetLabelSize(0.045); 
responseMassMC->GetXaxis()->SetTitleSize(0.048); 
responseMassMC->GetYaxis()->SetTitleSize(0.048); 
responseMassMC->GetZaxis()->SetTitleSize(0.048); 
responseMassMC->GetXaxis()->SetNoExponent(); 
responseMassMC->GetYaxis()->SetNoExponent(); 
responseMassMC->Draw("COLZ"); 

TLatex latex;
latex.SetTextFont(62);
latex.SetTextSize(0.055);    
latex.DrawLatex(55,800,"CMS simulation internal");

Resp->Print("Response.pdf"); 
}
