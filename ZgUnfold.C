//#define ZgUnfold_c
//#include ZgUnfold.h

//#include "RooUnfoldResponse.h"
//#include "RooUnfoldBayes.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldResponse.h"
#include "/opt/local/libexec/RooUnfold/src/RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"

//void ZgUnfold::MakeHistos(int which)
int ZgUnfold(int which)
{

//gSystem->Load("/opt/local/libexec/RooUnfold/libRooUnfold.so");
gSystem->Load("libRooUnfold");

const int nbinsD= 13;
const int nbinsMC = 13;
const int nbinsDm = nbinsD-1;
const float xbinsD[nbinsD] = {15,20,25,30,35,40,45,50,55,60,70,80,100};
const float xbinsMC[nbinsMC] = {15,20,25,30,35,40,45,50,55,60,70,80,100};

float fakeRate0[nbinsDm] = {0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15};
float fakeRate1[nbinsDm] = {0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15,0.15};
float fakeRate[nbinsDm] = {0,0,0,0,0.,0.,0.,0.,0.,0.,0.,0.};

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
  for (int i=0;i<nbinsDm;i++){
    fakeRate[i]=fakeRate0[i];
  }
} else if (which == 1) {
  fileD = TFile::Open("13TeV_Zg/data_ch1.root");
  fileMC = TFile::Open("13TeV_Zg/mc_ch1.root");
  for (int i=0;i<nbinsDm;i++){
    fakeRate[i]=fakeRate1[i];
  } 
} else {
  cout << "Please input 0 or 1!" << endl;
}
if(!fileD || !fileD->IsOpen() || !fileMC || !fileMC->IsOpen() ) { 
  cout<<"Cannot open file"<<endl;
  return 0;
}

TTree *treeD = (TTree*) fileD->Get("tZg");
TTree *treeMC = (TTree*) fileMC->Get("tZg");
 
float phoPtD; 
treeD->SetBranchAddress("phoPt",&phoPtD);

float phoPtMC,mcPhoPtMC; 
treeMC->SetBranchAddress("phoPt",&phoPtMC);
treeMC->SetBranchAddress("mcPhoPt",&mcPhoPtMC);
 
treeD->Project("inHistProj","phoPt");   
treeMC->Project("inHistMCProj","phoPt");   
treeMC->Project("trueHistMCProj","mcPhoPt");   
treeMC->Project("responseMCProj","phoPt:mcPhoPt");   

int nMC = treeMC->GetEntries();
for (int i=0;i<nMC;i++){
  treeMC->GetEntry(i);
  inHistMC->Fill(phoPtMC);
  trueHistMC->Fill(mcPhoPtMC);
  responseMC->Fill(phoPtMC,mcPhoPtMC);
  //check selection!!!!
  if(true) response.Fill(phoPtMC,mcPhoPtMC);
  else response.Miss(mcPhoPtMC);
}

int nD = treeD->GetEntries();
for (int i=0;i<nMC;i++){
  treeD->GetEntry(i);
  float w = 1.;
  inHist->Fill(phoPtD, w);
}

int nIter = 4;
RooUnfoldBayes    unfoldD (&response, inHist, nIter);
RooUnfoldBayes    unfoldMC (&response, inHistMC, nIter);

outHist = (TH1F*) unfoldD.Hreco();
outHistMC = (TH1F*) unfoldMC.Hreco();

TCanvas *zgInP = new TCanvas("zgInP","zgInP",500,500);
zgInP->Divide(2,2);
zgInP->cd(1);
inHist->Draw();
zgInP->cd(2);
inHistMC->Draw();
zgInP->cd(3);
trueHistMC->Draw();
zgInP->cd(4);
responseMC->Draw("text");
zgInP->Print("ZgUnfold_input_projections.pdf");

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
zgIn->Print("ZgUnfold_input.pdf");

TCanvas *zg = new TCanvas("zg","zg",500,500);
//zg->Divide(2,2);
//zg->cd(1);
inHistMC->SetLineStyle(2);
inHistMC->SetLineColor(3);
inHistMC->Draw();
trueHistMC->SetLineStyle(2);
trueHistMC->SetLineColor(1);
trueHistMC->Draw("same");
outHistMC->SetLineColor(2);
outHistMC->SetLineStyle(2);
outHistMC->Draw("same");

TLegend *leg = new TLegend(0.7,0.5,0.9,0.7,NULL,"brNDC");
leg->SetTextFont(62);
leg->SetLineColor(0);
leg->SetLineStyle(1);
leg->SetLineWidth(1);
leg->SetFillColor(19);
leg->SetFillStyle(0);
TLegendEntry *entry=leg->AddEntry("trueHistMC","trueHistMC","L");
entry->SetLineStyle(2);
entry->SetLineColor(1);
TLegendEntry *entry=leg->AddEntry("outHistMC","outHistMC","L");
entry->SetLineColor(2);
entry->SetLineStyle(2);
TLegendEntry *entry=leg->AddEntry("inHistMC","inHistMC","L");
entry->SetLineStyle(2);
entry->SetLineColor(3);
leg->Draw();

//outHist->SetLineColor(2);
//outHist->Draw("same");
//inHist->SetLineColor(3);
//inHist->Draw("same");

zg->Print("ZgUnfold_output.pdf");

return 1;
}
