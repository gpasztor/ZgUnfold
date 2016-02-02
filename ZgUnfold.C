//#define ZgUnfold_c
//#include ZgUnfold.h

//#include "RooUnfoldResponse.h"
//#include "RooUnfoldBayes.h"

#include "/opt/local/libexec/RooUnfold/src/RooUnfoldResponse.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldBayes.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldSvd.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldBinByBin.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldTUnfold.h"

using namespace TMath;

//void ZgUnfold::MakeHistos(int which)
int ZgUnfold(int which)
{

//gSystem->Load("/opt/local/libexec/RooUnfold/libRooUnfold.so");
gSystem->Load("libRooUnfold");

const int nbinsD= 11;
const int nbinsMC = 11;
const int nbinsDm = nbinsD-1;
const int nbinsMCm = nbinsMC-1;
const float xbinsD[nbinsD] = {15,20,25,30,35,40,60,90,120,500,1000};
const float xbinsMC[nbinsMC] = {15,20,25,30,35,40,60,90,120,500,1000};

float fakeRateB0[nbinsDm] = {0.138,0.167,0.141,0.166,0.183,0.204,0.160,0.103,0.083,0.083};
float fakeRateB1[nbinsDm] = {0.118,0.115,0.113,0.139,0.174,0.192,0.149,0.066,0.104,0.104};
// update
float fakeRateE0[nbinsDm] = {0.138,0.167,0.141,0.166,0.183,0.204,0.160,0.103,0.083,0.083}; 
float fakeRateE1[nbinsDm] = {0.118,0.115,0.113,0.139,0.174,0.192,0.149,0.066,0.104,0.104};
//float fakeRate[nbinsDm] = {0,0,0,0,0.,0.,0.,0.,0.,0.,0.,0.,0.};
//float *fakeRate;

TH1F *inHist = new TH1F("inHist","inHist", nbinsD-1, xbinsD);
TH1F *inHistMC = new TH1F("inHistMC","inHistMC", nbinsD-1, xbinsD);
TH1F *trueHistMC = new TH1F("trueHistMC","trueHistMC", nbinsMC-1, xbinsD);
TH2F *responseMC = new TH2F("responseMC","responseMC", nbinsD-1, xbinsD, nbinsMC-1, xbinsMC);
TH1F *outHist = new TH1F("outHist","outHist", nbinsMC-1, xbinsMC);
TH1F *outHistMC = new TH1F("outHistMC","outHistMC", nbinsMC-1, xbinsMC);

RooUnfoldResponse response(inHist,outHist);

cout << "which: " << which << endl;

TFile *fileD = 0;
TFile *fileMC = 0;
if (which == 0) {
  fileD = TFile::Open("13TeV_Zg/data_ch0.root");
  fileMC = TFile::Open("13TeV_Zg/mc_ch0.root");
  //for (int i=0;i<nbinsDm;i++){
  //  fakeRate[i]=fakeRate0[i];
  //}
} else if (which == 1) {
  fileD = TFile::Open("13TeV_Zg/data_ch1.root");
  fileMC = TFile::Open("13TeV_Zg/mc_ch1.root");
  //for (int i=0;i<nbinsDm;i++){
  //  fakeRate[i]=fakeRate1[i];
  //} 
} else {
  cout << "Please input 0 or 1!" << endl;
}
if(!fileD || !fileD->IsOpen() || !fileMC || !fileMC->IsOpen() ) { 
  cout<<"Cannot open file"<<endl;
  return 0;
}

TTree *treeD = (TTree*) fileD->Get("tZg");
TTree *treeMC = (TTree*) fileMC->Get("tZg");
 
float phoPtD,phoEtaD,phoSCEtaD,phoPhiD;
float lepPtD,lepEtaD,lepSCEtaD,lepPhiD;
float mllgD;
int isEBEED; 
treeD->SetBranchAddress("phoPt",&phoPtD);
treeD->SetBranchAddress("phoeEa",&phoEtaD);
treeD->SetBranchAddress("phoSCEta",&phoSCEtaD);
treeD->SetBranchAddress("phoPhi",&phoPhiD);
treeD->SetBranchAddress("lepPt",&lepPtD);
treeD->SetBranchAddress("lepEta",&lepEtaD);
treeD->SetBranchAddress("lepSCEta",&lepSCEtaD);
treeD->SetBranchAddress("lepPhi",&lepPhiD);
treeD->SetBranchAddress("mllg",&mllgD);
treeD->SetBranchAddress("isEBEE",&isEBEED);

float phoPtMC,phoEtaMC,phoSCEtaMC,phoPhiMC;
float lepPtMC,lepEtaMC,lepSCEtaMC,lepPhiMC;
float mllgMC;
int isEBEEMC; 
float mcPhoPtMC,mcPhoEtaMC,mcPhoPhiMC;
float mcLepPtMC,mcLepEtaMC,mcLepPhiMC;
float puwei,mcwei,genwei;
treeMC->SetBranchAddress("phoPt",&phoPtMC);
treeMC->SetBranchAddress("phoEta",&phoEtaMC);
treeMC->SetBranchAddress("phoSCEta",&phoSCEtaMC);
treeMC->SetBranchAddress("phoPhi",&phoPhiMC);
treeMC->SetBranchAddress("lepPt",&lepPtMC);
treeMC->SetBranchAddress("lepEta",&lepEtaMC);
treeMC->SetBranchAddress("lepSCEta",&lepSCEtaMC);
treeMC->SetBranchAddress("lepPhi",&lepPhiMC);
treeMC->SetBranchAddress("mllg",&mllgMC);
treeMC->SetBranchAddress("isEBEE",&isEBEEMC);
treeMC->SetBranchAddress("mcPhoPt",&mcPhoPtMC);
treeMC->SetBranchAddress("mcPhoEta",&mcPhoEtaMC);
treeMC->SetBranchAddress("mcPhoPhi",&mcPhoPhiMC);
treeMC->SetBranchAddress("mcLepPt",&mcLepPtMC);
treeMC->SetBranchAddress("mcLepEta",&mcLepEtaMC);
treeMC->SetBranchAddress("mcLepPhi",&mcLepPhiMC);
treeMC->SetBranchAddress("puwei",&puwei);
treeMC->SetBranchAddress("mcwei",&mcwei);
treeMC->SetBranchAddress("genwei",&genwei);
 
treeD->Project("inHistProj","phoPt");   
treeMC->Project("inHistMCProj","phoPt","(puwei*mcwei*genwei)*(1)");   
treeMC->Project("trueHistMCProj","mcPhoPt","(puwei*mcwei*genwei)*(1)");   
treeMC->Project("responseMCProj","phoPt:mcPhoPt","(puwei*mcwei*genwei)*(1)");   

int nMC = treeMC->GetEntries();
for (int i=0;i<nMC;i++){
  treeMC->GetEntry(i);
  if(mcPhoPtMC<0) continue;
  inHistMC->Fill(Min(phoPtMC,xbinsD[nbinsDm]-0.1),puwei*mcwei*genwei);
  trueHistMC->Fill(Min(mcPhoPtMC,xbinsMC[nbinsMCm]-0.1),puwei*mcwei*genwei);
  responseMC->Fill(Min(phoPtMC,xbinsD[nbinsDm]-0.1),Min(mcPhoPtMC,xbinsMC[nbinsMCm]-0.1),puwei*mcwei*genwei);
  //check selection!!!!
  if(true) response.Fill(Min(phoPtMC,xbinsD[nbinsDm]-0.1),Min(mcPhoPtMC,xbinsMC[nbinsMCm]-0.1),puwei*mcwei*genwei);
  else response.Miss(Min(mcPhoPtMC,xbinsMC[nbinsMCm]-0.1),puwei*mcwei*genwei);
}
//TH2F* responseM = (TH2F*) response.Hresponse();
responseM = (TH2F*) response.Hresponse();

int nD = treeD->GetEntries();
for (int i=0;i<nMC;i++){
  treeD->GetEntry(i);
  float w = 1.;
  for (int j=0; j<nbinsDm; j++){
    //cout << "j: " << j << " " << isEBEED << " " << fakeRateE0[j] << " " << fakeRateB0[j] << " " << fakeRateE1[j] << " " << fakeRateB1[j]<< endl;
    if (phoPtD>xbinsD[j] && phoPtD<xbinsD[j+1]){
        if (which == 0) {
	  w = (isEBEED ? (1.-fakeRateE0[j]) : (1.-fakeRateB0[j]));
	} else if {
	  w = (isEBEED ? (1.-fakeRateE1[j]) : (1.-fakeRateB1[j]));
	}
    }
  }
  inHist->Fill(Min(phoPtD,xbinsD[nbinsDm]-0.1), w);
}

RooUnfoldBinByBin unfoldBinByBinD(&response,inHist);
RooUnfoldBinByBin unfoldBinByBinMC(&response,inHistMC);
RooUnfoldBayes unfoldBayes1D(&response,inHist,1);
RooUnfoldBayes unfoldBayes1MC(&response,inHistMC,1);
RooUnfoldBayes unfoldBayes2D(&response,inHist,2);
RooUnfoldBayes unfoldBayes2MC(&response,inHistMC,2);
RooUnfoldBayes unfoldBayes3D(&response,inHist,3);
RooUnfoldBayes unfoldBayes3MC(&response,inHistMC,3);
RooUnfoldBayes unfoldBayes4D(&response,inHist,4);
RooUnfoldBayes unfoldBayes4MC(&response,inHistMC,4);
RooUnfoldBayes unfoldBayes5D(&response,inHist,5);
RooUnfoldBayes unfoldBayes5MC(&response,inHistMC,5);
RooUnfoldSvd unfoldSvd2D(&response,inHist,2);
RooUnfoldSvd unfoldSvd2MC(&response,inHistMC,2);
RooUnfoldSvd unfoldSvd5D(&response,inHist,5);
RooUnfoldSvd unfoldSvd5MC(&response,inHistMC,5);
RooUnfoldSvd unfoldSvd8D(&response,inHist,8);
RooUnfoldSvd unfoldSvd8MC(&response,inHistMC,8);
RooUnfoldSvd unfoldSvd11D(&response,inHist,11);
RooUnfoldSvd unfoldSvd11MC(&response,inHistMC,11);

outHistBinByBin = (TH1F*) unfoldBinByBinD.Hreco();
outHistBinByBinMC = (TH1F*) unfoldBinByBinMC.Hreco();
outHistBayes1 = (TH1F*) unfoldBayes1D.Hreco();
outHistBayes1MC = (TH1F*) unfoldBayes1MC.Hreco();
outHistBayes2 = (TH1F*) unfoldBayes2D.Hreco();
outHistBayes2MC = (TH1F*) unfoldBayes2MC.Hreco();
outHistBayes3 = (TH1F*) unfoldBayes3D.Hreco();
outHistBayes3MC = (TH1F*) unfoldBayes3MC.Hreco();
outHistBayes4 = (TH1F*) unfoldBayes4D.Hreco();
outHistBayes4MC = (TH1F*) unfoldBayes4MC.Hreco();
outHistBayes5 = (TH1F*) unfoldBayes5D.Hreco();
outHistBayes5MC = (TH1F*) unfoldBayes5MC.Hreco();
outHistSvd2 = (TH1F*) unfoldSvd2D.Hreco();
outHistSvd2MC = (TH1F*) unfoldSvd2MC.Hreco();
outHistSvd5 = (TH1F*) unfoldSvd5D.Hreco();
outHistSvd5MC = (TH1F*) unfoldSvd5MC.Hreco();
outHistSvd8 = (TH1F*) unfoldSvd8D.Hreco();
outHistSvd8MC = (TH1F*) unfoldSvd8MC.Hreco();
outHistSvd11 = (TH1F*) unfoldSvd11D.Hreco();
outHistSvd11MC = (TH1F*) unfoldSvd11MC.Hreco();

TCanvas *zgInP = new TCanvas("zgInP","zgInP",700,500);
zgInP->Divide(3,2);
zgInP->cd(1);
inHist->Draw();
zgInP->cd(2);
inHistMC->Draw();
zgInP->cd(4);
trueHistMC->Draw();
zgInP->cd(5);
responseMC->Draw("text");
zgInP->cd(6);
responseM->Draw("text");
zgInP->Print("ZgUnfold_input.pdf");

TCanvas *zgIn = new TCanvas("zgIn","zgIn",500,500);
zgIn->Divide(2,2);
zgIn->cd(1);
inHistProj->Draw();
zgIn->cd(2);
inHistMCProj->Draw();
zgIn->cd(3);
trueHistMCProj->Draw();
zgIn->cd(4);
responseMCProj->Draw("text");
zgIn->Print("ZgUnfold_input_projections.pdf");

TCanvas *zg = new TCanvas("zg","zg",700,700);
//zg->Divide(2,2);
//zg->cd(1);
inHistMC->SetLineWidth(3);
inHistMC->SetLineStyle(kDashed);
inHistMC->SetLineColor(kBlack);
inHistMC->Draw();
trueHistMC->SetLineWidth(3);
trueHistMC->SetLineStyle(kSolid);
trueHistMC->SetLineColor(kBlack);
trueHistMC->Draw("same");
outHistBinByBinMC->SetLineWidth(3);
outHistBinByBinMC->SetLineStyle(kDashed);
outHistBinByBinMC->SetLineColor(kGreen);
outHistBinByBinMC->Draw("same");
outHistBayes1MC->SetLineWidth(3);
outHistBayes1MC->SetLineStyle(kDotted);
outHistBayes1MC->SetLineColor(kBlue+3);
outHistBayes1MC->Draw("same");
outHistBayes2MC->SetLineWidth(3);
outHistBayes2MC->SetLineStyle(kDotted);
outHistBayes2MC->SetLineColor(kBlue);
outHistBayes2MC->Draw("same");
outHistBayes3MC->SetLineWidth(3);
outHistBayes3MC->SetLineStyle(kDotted);
outHistBayes3MC->SetLineColor(kBlue-7);
outHistBayes3MC->Draw("same");
outHistBayes4MC->SetLineWidth(3);
outHistBayes4MC->SetLineStyle(kDotted);
outHistBayes4MC->SetLineColor(kMagenta);
outHistBayes4MC->Draw("same");
outHistBayes5MC->SetLineWidth(3);
outHistBayes5MC->SetLineStyle(kDotted);
outHistBayes5MC->SetLineColor(kMagenta-9);
outHistBayes5MC->Draw("same");
outHistSvd2MC->SetLineWidth(3);
outHistSvd2MC->SetLineStyle(kDotted);
outHistSvd2MC->SetLineColor(kRed+2);
outHistSvd2MC->Draw("same");
outHistSvd5MC->SetLineWidth(3);
outHistSvd5MC->SetLineStyle(kDotted);
outHistSvd5MC->SetLineColor(kRed);
outHistSvd5MC->Draw("same");
outHistSvd8MC->SetLineWidth(3);
outHistSvd8MC->SetLineStyle(kDotted);
outHistSvd8MC->SetLineColor(kRed-9);
outHistSvd8MC->Draw("same");
outHistSvd11MC->SetLineWidth(3);
outHistSvd11MC->SetLineStyle(kDotted);
outHistSvd11MC->SetLineColor(kOrange);
outHistSvd11MC->Draw("same");

TLegend *leg = new TLegend(0.7,0.3,0.9,0.7,NULL,"brNDC");
leg->SetTextFont(62);
leg->SetLineColor(0);
leg->SetLineStyle(1);
leg->SetLineWidth(1);
leg->SetFillColor(19);
leg->SetFillStyle(0);
TLegendEntry *entry=leg->AddEntry("inHistMC","inHistMC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDashed);
entry->SetLineColor(kBlack);
TLegendEntry *entry=leg->AddEntry("trueHistMC","trueHistMC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kSolid);
entry->SetLineColor(kBlack);
TLegendEntry *entry=leg->AddEntry("outHistBinByBinMC","outHistBinByBinMC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDashed);
entry->SetLineColor(kGreen);
TLegendEntry *entry=leg->AddEntry("outHistBayes1MC","outHistBayes1MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kBlue+3);
TLegendEntry *entry=leg->AddEntry("outHistBayes2MC","outHistBayes2MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kBlue);
TLegendEntry *entry=leg->AddEntry("outHistBayes3MC","outHistBayes3MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kBlue-7);
TLegendEntry *entry=leg->AddEntry("outHistBayes4MC","outHistBayes4MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kMagenta);
TLegendEntry *entry=leg->AddEntry("outHistBayes5MC","outHistBayes5MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kMagenta-9);
TLegendEntry *entry=leg->AddEntry("outHistSvd2MC","outHistSvd2MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kRed+2);
TLegendEntry *entry=leg->AddEntry("outHistSvd5MC","outHistSvd5MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kRed);
TLegendEntry *entry=leg->AddEntry("outHistSvd8MC","outHistSvd8MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kRed-9);
TLegendEntry *entry=leg->AddEntry("outHistSvd11MC","outHistSvd11MC","L");
entry->SetLineWidth(3);
entry->SetLineStyle(kDotted);
entry->SetLineColor(kOrange);
leg->Draw();

//outHist->SetLineColor(2);
//outHist->Draw("same");
//inHist->SetLineColor(3);
//inHist->Draw("same");

zg->Print("ZgUnfold_output.pdf");

return 1;
}
