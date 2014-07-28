#include "TFile.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TPaveText.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

#include "Plots/Style/interface/Style.h"
#include "Latex/Table/interface/LatexTabular.h"
#include "Histograms/Analysis/interface/HistogramCollection.h"


using namespace std;

//####################################################################
map<string,double> getEff(TFile* f,int run,string histname,double multiplier=1){
  
  TH1I* hTotal = (TH1I*) f->Get(Form("Run_%d/EventCount",run));
  double nEvents = hTotal->GetBinContent(1);

  TH1I* hL1T = (TH1I*) f->Get(Form("Run_%d/%s",run,histname.c_str()));
  map<string,double> out;
  
  for(int i=1; i<hL1T->GetXaxis()->GetNbins()+1; i++){
    out[hL1T->GetXaxis()->GetBinLabel(i)] = (hL1T->GetBinContent(i)/nEvents)*multiplier;
  }
  
  return out;
}

//####################################################################
map<string,double> getEff_partial(TFile* f,int run,string nNum,string nDen,double multiplier=1){
  
  TH1I* hNum = (TH1I*) f->Get(Form("Run_%d/%s",run,nNum.c_str()));  
  TH1I* hDen = (TH1I*) f->Get(Form("Run_%d/%s",run,nDen.c_str()));
    
  map<string,double> out;
  for(int i=1; i<hNum->GetXaxis()->GetNbins()+1; i++){
  
    string trigName = hNum->GetXaxis()->GetBinLabel(i);

    int iDen=0;
    for(unsigned a=1; a<hDen->GetNbinsX()+1; a++){ 
      if(hDen->GetXaxis()->GetBinLabel(a)==trigName){iDen=a; break;}
    }
    
    out[hNum->GetXaxis()->GetBinLabel(i)] = (hNum->GetBinContent(i)/hDen->GetBinContent(iDen))*multiplier;
  }
  
  return out;
}


std::string parseToLaTeX(std::string s) {
  
  boost::replace_all(s,"_","\\_");
  return s;
}

//####################################################################
void doTableL1T(vector<string> &selL1T,map<string,double> &pu20bx25, map<string,double> &pu40bx50, map<string,double> &pu40bx25, string filename){
  
  rat::LatexTabular tabular0(selL1T.size()+1,4);
  
  tabular0.setColumnDecorationBefore(0,"|");
  tabular0.setColumnDecorationBefore(1,"||");
  tabular0.setColumnDecorationBefore(2,"|");
  tabular0.setColumnDecorationBefore(3,"|");
  tabular0.setColumnDecorationAfter (3,"|");
  
  tabular0.setRowDecorationBefore(0,"\\hline");
  tabular0.setRowDecorationBefore(1,"\\hline \\hline");
  tabular0.setRowDecorationAfter (selL1T.size(),"\\hline");
  
  tabular0.setCellContent(0,0,"L1T");
  tabular0.setCellContent(0,1,"PU20bx25");
  tabular0.setCellContent(0,2,"PU40bx50");
  tabular0.setCellContent(0,3,"PU40bx25");
  
  for(unsigned i=0; i<selL1T.size(); i++){
    tabular0.setCellContent(i+1,0,parseToLaTeX(selL1T[i]).c_str());
    tabular0.setCellContent(i+1,1,pu20bx25[selL1T[i]]);  
    tabular0.setCellContent(i+1,2,pu40bx50[selL1T[i]]);
    tabular0.setCellContent(i+1,3,pu40bx25[selL1T[i]]);
  }
  
  tabular0.saveAs(filename);
  
}

//####################################################################
void doTableHLT(vector<string> &selHLT,map<string,double> &pu20bx25, map<string,double> &pu40bx50, map<string,double> &pu40bx25, string filename){
  
  rat::LatexTabular tabular0(selHLT.size()+1,4);
  
  tabular0.setColumnDecorationBefore(0,"|");
  tabular0.setColumnDecorationBefore(1,"||");
  tabular0.setColumnDecorationBefore(2,"|");
  tabular0.setColumnDecorationBefore(3,"|");
  tabular0.setColumnDecorationAfter (3,"|");
  
  tabular0.setRowDecorationBefore(0,"\\hline");
  tabular0.setRowDecorationBefore(1,"\\hline \\hline");
  tabular0.setRowDecorationAfter (selHLT.size(),"\\hline");
  
  tabular0.setCellContent(0,0,"HLT");
  tabular0.setCellContent(0,1,"PU20bx25");
  tabular0.setCellContent(0,2,"PU40bx50");
  tabular0.setCellContent(0,3,"PU40bx25");
  
  for(unsigned i=0; i<selHLT.size(); i++){
    tabular0.setCellContent(i+1,0,parseToLaTeX(selHLT[i]).c_str());
    tabular0.setCellContent(i+1,1,pu20bx25[selHLT[i]]);  
    tabular0.setCellContent(i+1,2,pu40bx50[selHLT[i]]);
    tabular0.setCellContent(i+1,3,pu40bx25[selHLT[i]]);
  }
  
  tabular0.saveAs(filename);
  
}

//####################################################################
THStack* doTrigSeedStack(map<string,TFile*> f,string trigName){
  
  TH1I *h;
  TH1D *hETM = new TH1D("hETM","hETM",3,-0.5,2.5);
  hETM->SetFillColor(kRed);
  hETM->GetXaxis()->SetBinLabel(1,"PU20bx25");
  hETM->GetXaxis()->SetBinLabel(2,"PU40bx50");
  hETM->GetXaxis()->SetBinLabel(3,"PU40bx25");
  hETM->GetYaxis()->SetTitle("Entries");
  h=(TH1I*) f["PU20bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_ETM");  hETM->SetBinContent(1,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx50_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_ETM");  hETM->SetBinContent(2,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_ETM");  hETM->SetBinContent(3,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  TH1D* hHTT = new TH1D("hHTT","hHTT",3,-0.5,2.5);
  hHTT->SetFillColor(kBlue);
  hHTT->GetXaxis()->SetBinLabel(1,"PU20bx25");
  hHTT->GetXaxis()->SetBinLabel(2,"PU40bx50");
  hHTT->GetXaxis()->SetBinLabel(3,"PU40bx25");
  hHTT->GetYaxis()->SetTitle("Entries");
  h=(TH1I*) f["PU20bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_HTT");  hHTT->SetBinContent(1,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx50_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_HTT");  hHTT->SetBinContent(2,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_HTT");  hHTT->SetBinContent(3,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  TH1D* hBoth = new TH1D("hBoth","hBoth",3,-0.5,2.5);
  hBoth->SetFillColor(kGreen);
  hBoth->GetXaxis()->SetBinLabel(1,"PU20bx25");
  hBoth->GetXaxis()->SetBinLabel(2,"PU40bx50");
  hBoth->GetXaxis()->SetBinLabel(3,"PU40bx25");
  hBoth->GetYaxis()->SetTitle("Entries");
  h=(TH1I*) f["PU20bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_Both"); hBoth->SetBinContent(1,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx50_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_Both"); hBoth->SetBinContent(2,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  h=(TH1I*) f["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get("Run_1/HLTAlgoCounts_Both"); hBoth->SetBinContent(3,h->GetBinContent(h->GetXaxis()->FindBin(trigName.c_str())));
  
  THStack *st = new THStack(trigName.c_str(),trigName.c_str());
  st->Add(hBoth);
  st->Add(hHTT);
  st->Add(hETM);
  
  TLegend *l = new TLegend(0.50,0.80,0.85,0.95);
  l->SetBorderSize(1);
  l->AddEntry(hBoth,"ETM and HTT Seeded");
  l->AddEntry(hHTT, "HTT Seeded");
  l->AddEntry(hETM, "ETM Seeded");
  
  TPaveText *pt = new TPaveText(.15,.955,.85,.99,"NDC");
  pt->SetBorderSize(1);
  pt->AddText(trigName.c_str());
  
  TCanvas *c = new TCanvas();
  st->Draw();
  st->GetYaxis()->SetTitle("Entries");
//   st->GetYaxis()->SetTitleOffset(1.5);
  st->GetYaxis()->SetLabelSize(0.02);
  st->Draw();
  l ->Draw();
  pt->Draw();
  c->SaveAs(Form("%s.pdf",trigName.c_str()));  
  
  delete hETM,hHTT,hBoth,st,l,c,pt;
  
  return st;
  
}

//####################################################################
int main(){

  rat::Style myStyle;
  myStyle.setTDRStyle();

  // Constants for rate calculations  
  const int nMaxBunch50ns = 1380;
  const int nMaxBunch25ns = 2808;
  const int ratePerBunch  = 11246;

  // Getting files
  map<string,TFile*> fNG,fSig;
  fNG["PU20bx25_Neutrino_gun"]            = new TFile("PU20bx25_Neutrino_Pt-2to20_gun.root");
  fNG["PU40bx50_Neutrino_gun"]            = new TFile("PU40bx50_Neutrino_Pt-2to20_gun.root");
  fNG["PU40bx25_Neutrino_gun"]            = new TFile("PU40bx25_Neutrino_Pt-2to20_gun.root");

  fSig["PU20bx25_VBF_HToInv_M-125_13TeV"] = new TFile("PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
  fSig["PU40bx50_VBF_HToInv_M-125_13TeV"] = new TFile("PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
  fSig["PU40bx25_VBF_HToInv_M-125_13TeV"] = new TFile("PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
  
  // Selected trigger
  vector<string> selL1T;
  selL1T.push_back("L1_ETM30");
  selL1T.push_back("L1_ETM36");
  selL1T.push_back("L1_ETM40");
  selL1T.push_back("L1_ETM50");
  selL1T.push_back("L1_ETM70");
  selL1T.push_back("L1_ETM100");
  selL1T.push_back("L1_HTT150");
  selL1T.push_back("L1_HTT175");
  selL1T.push_back("L1_HTT200");  
  
  vector<string> selHLT;
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v");
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v");
  selHLT.push_back("HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v");
  selHLT.push_back("HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v");
  selHLT.push_back("HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v");
  selHLT.push_back("HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v");  
  selHLT.push_back("HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v");  

  // Signal: Trigger efficiency
  map<string,double> l1tPU20bx25v = getEff(fSig["PU20bx25_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  map<string,double> l1tPU40bx50v = getEff(fSig["PU40bx50_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  map<string,double> l1tPU40bx25v = getEff(fSig["PU40bx25_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  doTableL1T(selL1T,l1tPU20bx25v,l1tPU40bx50v,l1tPU40bx25v,"VBFInv_L1TSignalEffiency.tex");

  map<string,double> hltPU20bx25v = getEff(fSig["PU20bx25_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx50v = getEff(fSig["PU40bx50_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx25v = getEff(fSig["PU40bx25_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25v,hltPU40bx50v,hltPU40bx25v,"VBFInv_HLTSignalEffiency.tex");

  // Neutrino Gun: Trigger efficiency
  map<string,double> l1tPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts" );
  map<string,double> l1tPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts" );
  map<string,double> l1tPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts" );
  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TBunchEff.tex");
  
  map<string,double> hltPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff.tex");
  
  // Neutrino Gun: Trigger efficiency by seed
  hltPU20bx25n = getEff_partial(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_ETM","HLTAlgoCounts");
  hltPU40bx50n = getEff_partial(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_ETM","HLTAlgoCounts");
  hltPU40bx25n = getEff_partial(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_ETM","HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_ETM.tex");
  
  hltPU20bx25n = getEff_partial(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_HTT","HLTAlgoCounts");
  hltPU40bx50n = getEff_partial(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_HTT","HLTAlgoCounts");
  hltPU40bx25n = getEff_partial(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_HTT","HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_HTT.tex");
  
  hltPU20bx25n = getEff_partial(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_Both","HLTAlgoCounts");
  hltPU40bx50n = getEff_partial(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_Both","HLTAlgoCounts");
  hltPU40bx25n = getEff_partial(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_Both","HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_Both.tex");
  
  hltPU20bx25n = getEff_partial(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_None","HLTAlgoCounts");
  hltPU40bx50n = getEff_partial(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_None","HLTAlgoCounts");
  hltPU40bx25n = getEff_partial(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_None","HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_None.tex");
  
  // Making tables for rate per bunch  
  l1tPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  l1tPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  l1tPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TBunchRate.tex");

  hltPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  hltPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  hltPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchRate.tex");

  // Making tables for maximum rate
  l1tPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch25ns));
  l1tPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch50ns));
  l1tPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch25ns));

  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TMaxRate.tex");
  hltPU20bx25n = getEff(fNG["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch25ns));
  hltPU40bx50n = getEff(fNG["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch50ns));
  hltPU40bx25n = getEff(fNG["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch25ns));
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTMaxRate.tex");

  //____________________________________________________________  
  // Calculations
  //____________________________________________________________
  
  cout << "Saturation Probability ECAL TT:" << endl;
  rat::HistogramCollection<string,TH1I> hEcalTT_NSaturated_NG (fNG, Form("Run_%d/hEcalTT_NSaturated",1));
  cout << "Neutrino Gun (PU20bx25) num=" << hEcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetBinContent(1) 
       << " den="  << hEcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetEntries() 
       << " prob=" << hEcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetBinContent(1)/hEcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetEntries() 
       << endl;
  cout << "Neutrino Gun (PU40bx50) num=" << hEcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetBinContent(1) 
       << " den="  << hEcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetEntries() 
       << " prob=" << hEcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetBinContent(1)/hEcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetEntries() 
       << endl;
  cout << "Neutrino Gun (PU40bx25) num=" << hEcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetBinContent(1) 
       << " den="  << hEcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetEntries() 
       << " prob=" << hEcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetBinContent(1)/hEcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetEntries() 
       << endl;
  
  rat::HistogramCollection<string,TH1I> hEcalTT_NSaturated_Sig(fSig,Form("Run_%d/hEcalTT_NSaturated",1));
  cout << "VBF H(Inv) (PU20bx25): " << hEcalTT_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hEcalTT_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx50): " << hEcalTT_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hEcalTT_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx25): " << hEcalTT_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hEcalTT_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  
  cout << "Saturation Probability HCAL TT:" << endl;
  rat::HistogramCollection<string,TH1I> hHcalTT_NSaturated_NG (fNG, Form("Run_%d/hHcalTT_NSaturated",1));
  cout << "Neutrino Gun (PU20bx25) num=" << hHcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetBinContent(1)
       << " den="  << hHcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetEntries()
       << " prob=" << hHcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetBinContent(1)/hHcalTT_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetEntries() 
       << endl;
  cout << "Neutrino Gun (PU40bx50) num=" << hHcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetBinContent(1)
       << " den="  << hHcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetEntries()
       << " prob=" << hHcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetBinContent(1)/hHcalTT_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetEntries() 
       << endl;
  cout << "Neutrino Gun (PU40bx25)  num=" << hHcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetBinContent(1)
       << " den="  << hHcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetEntries()
       << " prob=" << hHcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetBinContent(1)/hHcalTT_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetEntries() 
       << endl;
  
  rat::HistogramCollection<string,TH1I> hHcalTT_NSaturated_Sig(fSig,Form("Run_%d/hHcalTT_NSaturated",1));
  cout << "VBF H(Inv) (PU20bx25): " << hHcalTT_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hHcalTT_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx50): " << hHcalTT_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hHcalTT_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx25): " << hHcalTT_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hHcalTT_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  
  cout << "Saturation Probability RCT Region:" << endl;
  rat::HistogramCollection<string,TH1I> hRCTRegion_NSaturated_NG (fNG, Form("Run_%d/hRCTRegion_NSaturated",1));
  cout << "Neutrino Gun (PU20bx25): " << hRCTRegion_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetBinContent(1)/hRCTRegion_NSaturated_NG["PU20bx25_Neutrino_gun"]->GetEntries() << endl;
  cout << "Neutrino Gun (PU40bx50): " << hRCTRegion_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetBinContent(1)/hRCTRegion_NSaturated_NG["PU40bx50_Neutrino_gun"]->GetEntries() << endl;
  cout << "Neutrino Gun (PU40bx25): " << hRCTRegion_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetBinContent(1)/hRCTRegion_NSaturated_NG["PU40bx25_Neutrino_gun"]->GetEntries() << endl;
  
  rat::HistogramCollection<string,TH1I> hRCTRegion_NSaturated_Sig(fSig,Form("Run_%d/hRCTRegion_NSaturated",1));
  cout << "VBF H(Inv) (PU20bx25): " << hRCTRegion_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hRCTRegion_NSaturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx50): " << hRCTRegion_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hRCTRegion_NSaturated_Sig["PU40bx50_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;
  cout << "VBF H(Inv) (PU40bx25): " << hRCTRegion_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetBinContent(1)/hRCTRegion_NSaturated_Sig["PU40bx25_VBF_HToInv_M-125_13TeV"]->GetEntries() << endl;  
  
  //____________________________________________________________  
  // Doing plots
  //____________________________________________________________
  
  map<string,int> attLineColor;
  attLineColor["PU20bx25_Neutrino_gun"]           = kRed;
  attLineColor["PU40bx50_Neutrino_gun"]           = kGreen;
  attLineColor["PU40bx25_Neutrino_gun"]           = kBlue;
  attLineColor["PU20bx25_VBF_HToInv_M-125_13TeV"] = kRed;
  attLineColor["PU40bx50_VBF_HToInv_M-125_13TeV"] = kGreen;
  attLineColor["PU40bx25_VBF_HToInv_M-125_13TeV"] = kBlue;
  
  map<string,string> attLegendText;
  attLegendText["PU20bx25_Neutrino_gun"]           = "#nu_{gun} PU20bx25";
  attLegendText["PU40bx50_Neutrino_gun"]           = "#nu_{gun} PU40bx50";        
  attLegendText["PU40bx25_Neutrino_gun"]           = "#nu_{gun} PU40bx25";
  attLegendText["PU20bx25_VBF_HToInv_M-125_13TeV"] = "VBF H(Inv) PU20bx25";
  attLegendText["PU40bx50_VBF_HToInv_M-125_13TeV"] = "VBF H(Inv) PU40bx50";
  attLegendText["PU40bx25_VBF_HToInv_M-125_13TeV"] = "VBF H(Inv) PU40bx25";
  
  map<string,string> attLegendAttribute;
  attLegendAttribute["PU20bx25_Neutrino_gun"]           = "l";
  attLegendAttribute["PU40bx50_Neutrino_gun"]           = "l";
  attLegendAttribute["PU40bx25_Neutrino_gun"]           = "l";
  attLegendAttribute["PU20bx25_VBF_HToInv_M-125_13TeV"] = "l";
  attLegendAttribute["PU40bx50_VBF_HToInv_M-125_13TeV"] = "l";
  attLegendAttribute["PU40bx25_VBF_HToInv_M-125_13TeV"] = "l"; 
    
  vector< pair<string,Option_t*> > attDrawAttributesNG;
  attDrawAttributesNG.push_back(pair<string,Option_t*>("PU20bx25_Neutrino_gun",""));
  attDrawAttributesNG.push_back(pair<string,Option_t*>("PU40bx50_Neutrino_gun","same"));
  attDrawAttributesNG.push_back(pair<string,Option_t*>("PU40bx25_Neutrino_gun","same"));
  
  vector< pair<string,Option_t*> > attDrawAttributesSig;  
  attDrawAttributesSig.push_back(pair<string,Option_t*>("PU20bx25_VBF_HToInv_M-125_13TeV",""));
  attDrawAttributesSig.push_back(pair<string,Option_t*>("PU40bx50_VBF_HToInv_M-125_13TeV","same"));
  attDrawAttributesSig.push_back(pair<string,Option_t*>("PU40bx25_VBF_HToInv_M-125_13TeV","same"));

  TCanvas* c = new TCanvas();

  c->SetLogy(true);
  TH1D *hSat_All = (TH1D*) fSig["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get(Form("Run_%d/L1ETM",1))           ->Clone("hSat_All");
  TH1D *hSat_Sat = (TH1D*) fSig["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get(Form("Run_%d/hL1ETM_Saturated",1))->Clone("hSat_Sat");
  hSat_All->Rebin(4);
  hSat_All->GetXaxis()->SetTitle("L1T ETM [GeV]");
  hSat_All->GetYaxis()->SetTitle("Entries");
  hSat_All->GetYaxis()->SetTitleOffset(1.2);
  hSat_All->GetYaxis()->SetRangeUser(0.1,10e5);
  hSat_Sat->Rebin(4);
  hSat_Sat->SetLineStyle(2);
  hSat_Sat->SetFillStyle(3001);
  hSat_Sat->SetFillColor(kBlue);
  hSat_All->Draw("");
  hSat_Sat->Draw("same");
  
  TLegend l(0.50,0.80,0.85,0.95);
  l.SetBorderSize(1);
  l.AddEntry(hSat_All,"VBF H(Inv) PU40bx25 - All");
  l.AddEntry(hSat_Sat,"VBF H(Inv) PU40bx25 - Saturated");
  l.Draw();
  
  c->SaveAs("L1ETM_Overlap.pdf");
  
  doTrigSeedStack(fSig,"HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v");
  doTrigSeedStack(fSig,"HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v");
  doTrigSeedStack(fSig,"HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v");
  doTrigSeedStack(fSig,"HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v");
  doTrigSeedStack(fSig,"HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v");
  
  //_______________________________________________________________________________
  // L1 Quantities
  //_______________________________________________________________________________
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcL1ETM_NG(fNG,Form("Run_%d/L1ETM",1));
  hcL1ETM_NG.scaleTo1();
  hcL1ETM_NG.setLineColor(attLineColor);
  hcL1ETM_NG.setLegend(attLegendText,attLegendAttribute);
  hcL1ETM_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,200);
  hcL1ETM_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("L1ETM [GeV]");
  hcL1ETM_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-8,1);
  hcL1ETM_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("L1ETM_NG.pdf");
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcL1HTT_NG(fNG,Form("Run_%d/L1HTT",1));
  hcL1HTT_NG.scaleTo1();
  hcL1HTT_NG.setLineColor(attLineColor);
  hcL1HTT_NG.setLegend(attLegendText,attLegendAttribute);  
  hcL1HTT_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,1200);
  hcL1HTT_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetTitle("L1HTT [GeV]");
  hcL1HTT_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-6,1);
  hcL1HTT_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetTitle("Entries");
  hcL1HTT_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("L1HTT_NG.pdf");

  rat::HistogramCollection<string,TH1D> hcL1ETM_Sig(fSig,Form("Run_%d/L1ETM",1));
  hcL1ETM_Sig.scaleTo1();
  hcL1ETM_Sig.setLineColor(attLineColor);
  hcL1ETM_Sig.setLegend(attLegendText,attLegendAttribute);
  hcL1ETM_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,1000);
  hcL1ETM_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("L1ETM [GeV]");
  hcL1ETM_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-7,0.1);
  hcL1ETM_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("L1ETM_Sig.pdf");
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcL1HTT_Sig(fSig,Form("Run_%d/L1HTT",1));
  hcL1HTT_Sig.scaleTo1();
  hcL1HTT_Sig.setLineColor(attLineColor);
  hcL1HTT_Sig.setLegend(attLegendText,attLegendAttribute);  
  hcL1HTT_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,1200);
  hcL1HTT_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetTitle("L1HTT [GeV]");
  hcL1HTT_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-7,0.1);
  hcL1HTT_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("L1HTT_Sig.pdf");
  
  // L1 Quantities Saturated
  //_______________________________________________________________________________  
  rat::HistogramCollection<string,TH1D> hcL1ETM_Saturated_NG(fNG,Form("Run_%d/hL1ETM_Saturated",1));
  hcL1ETM_Saturated_NG.scaleTo1();
  hcL1ETM_Saturated_NG.setLineColor(attLineColor);
  hcL1ETM_Saturated_NG.setLegend(attLegendText,attLegendAttribute);
  //hcL1ETM_Saturated_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,200);
  hcL1ETM_Saturated_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("L1ETM [GeV]");
  hcL1ETM_Saturated_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-6,0.1);
  hcL1ETM_Saturated_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("L1ETM_Saturated_NG.pdf");
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcL1HTT_Saturated_NG(fNG,Form("Run_%d/hL1HTT_Saturated",1));  
  hcL1HTT_Saturated_NG.scaleTo1();
  hcL1HTT_Saturated_NG.setLineColor(attLineColor);
  hcL1HTT_Saturated_NG.setLegend(attLegendText,attLegendAttribute);  
  hcL1HTT_Saturated_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,1200);
  hcL1HTT_Saturated_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("L1HTT [GeV]");
  hcL1HTT_Saturated_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-6,0.1);
  hcL1HTT_Saturated_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("L1HTT_Saturated_NG.pdf");

  rat::HistogramCollection<string,TH1D> hcL1ETM_Saturated_Sig(fSig,Form("Run_%d/hL1ETM_Saturated",1));
  hcL1ETM_Saturated_Sig.scaleTo1();
  hcL1ETM_Saturated_Sig.rebin(5);
  hcL1ETM_Saturated_Sig.setLineColor(attLineColor);
  hcL1ETM_Saturated_Sig.setLegend(attLegendText,attLegendAttribute);
  //hcL1ETM_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,200);
  hcL1ETM_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("L1ETM [GeV]");
  hcL1ETM_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-7,0.1);
  hcL1ETM_Saturated_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("L1ETM_Saturated_Sig.pdf");
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcL1HTT_Saturated_Sig(fSig,Form("Run_%d/hL1HTT_Saturated",1));
  hcL1HTT_Saturated_Sig.scaleTo1();
  hcL1HTT_Saturated_Sig.rebin(5);
  hcL1HTT_Saturated_Sig.setLineColor(attLineColor);
  hcL1HTT_Saturated_Sig.setLegend(attLegendText,attLegendAttribute);  
  hcL1HTT_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,1200);
  hcL1HTT_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("L1HTT [GeV]");
  hcL1HTT_Saturated_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-7,0.1);
  hcL1HTT_Saturated_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("L1HTT_Saturated_Sig.pdf");
  
  //_______________________________________________________________________________
  // ECAL TT HCAL TT and RCT Regions
  //_______________________________________________________________________________ 
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcECALTT_Val_NG(fNG,Form("Run_%d/hEcalTT_Val",1));
  hcECALTT_Val_NG.scaleTo1();
  hcECALTT_Val_NG.rebin(2);
  hcECALTT_Val_NG.setLineColor(attLineColor);
  hcECALTT_Val_NG.setLegend(attLegendText,attLegendAttribute);  
  hcECALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,300);
  hcECALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcECALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcECALTT_Val_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("EcalTT_Val_NG.pdf"); 
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcHCALTT_Val_NG(fNG,Form("Run_%d/hHcalTT_Val",1));  
  hcHCALTT_Val_NG.scaleTo1();
  hcHCALTT_Val_NG.rebin(2);
  hcHCALTT_Val_NG.setLineColor(attLineColor);
  hcHCALTT_Val_NG.setLegend(attLegendText,attLegendAttribute);  
  hcHCALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,300);
  hcHCALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcHCALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcHCALTT_Val_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetTitle("Entries");
  hcHCALTT_Val_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("HcalTT_Val_NG.pdf"); 

  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcRCTRegion_Val_NG(fNG,Form("Run_%d/hRCTRegion_Val",1));  
  hcRCTRegion_Val_NG.scaleTo1();
  hcRCTRegion_Val_NG.rebin(4);
  hcRCTRegion_Val_NG.setLineColor(attLineColor);
  hcRCTRegion_Val_NG.setLegend(attLegendText,attLegendAttribute);  
  hcRCTRegion_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetRangeUser(0,1100);
  hcRCTRegion_Val_NG["PU20bx25_Neutrino_gun"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcRCTRegion_Val_NG["PU20bx25_Neutrino_gun"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcRCTRegion_Val_NG.draw(c,attDrawAttributesNG);
  c->SetLogy();
  c->SaveAs("RCTRegion_Val_NG.pdf");
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcECALTT_Val_Sig(fSig,Form("Run_%d/hEcalTT_Val",1));
  hcECALTT_Val_Sig.scaleTo1();
  hcECALTT_Val_Sig.rebin(2);
  hcECALTT_Val_Sig.setLineColor(attLineColor);
  hcECALTT_Val_Sig.setLegend(attLegendText,attLegendAttribute);
  hcECALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,300);
  hcECALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcECALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcECALTT_Val_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("EcalTT_Val_Sig.pdf"); 
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcHCALTT_Val_Sig(fSig,Form("Run_%d/hHcalTT_Val",1));  
  hcHCALTT_Val_Sig.scaleTo1();
  hcHCALTT_Val_Sig.rebin(2);
  hcHCALTT_Val_Sig.setLineColor(attLineColor);
  hcHCALTT_Val_Sig.setLegend(attLegendText,attLegendAttribute);  
  hcHCALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,300);
  hcHCALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcHCALTT_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcHCALTT_Val_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("HcalTT_Val_Sig.pdf"); 
  
  c->SetLogy(false);
  rat::HistogramCollection<string,TH1D> hcRCTRegion_Val_Sig(fSig,Form("Run_%d/hRCTRegion_Val",1));  
  hcRCTRegion_Val_Sig.scaleTo1();
  hcRCTRegion_Val_Sig.rebin(4);
  hcRCTRegion_Val_Sig.setLineColor(attLineColor);
  hcRCTRegion_Val_Sig.setLegend(attLegendText,attLegendAttribute);  
  hcRCTRegion_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetRangeUser(0,1100);
  hcRCTRegion_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hcRCTRegion_Val_Sig["PU20bx25_VBF_HToInv_M-125_13TeV"]->GetYaxis()->SetRangeUser(10e-13,0.1);
  hcRCTRegion_Val_Sig.draw(c,attDrawAttributesSig);
  c->SetLogy();
  c->SaveAs("RCTRegion_Val_Sig.pdf");
  
  //_______________________________________________________________________________
  // 127 Saturation
  //_______________________________________________________________________________
  TH1D *hECALTT_Barrel_CompressedEt = (TH1D*) fSig["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get(Form("Run_%d/EcalTT/ECALTT_Barrel_CompressedEt",1));
  hECALTT_Barrel_CompressedEt->SetLineColor(kBlue);
  hECALTT_Barrel_CompressedEt->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hECALTT_Barrel_CompressedEt->GetYaxis()->SetTitle("Entries");
  hECALTT_Barrel_CompressedEt->Draw();
  c->SetLogy();
  c->SaveAs("ECALTT_Barrel_CompressedEt.pdf");
  
  TH1D *hECALTT_Endcap_CompressedEt = (TH1D*) fSig["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get(Form("Run_%d/EcalTT/ECALTT_Endcap_CompressedEt",1));
  hECALTT_Endcap_CompressedEt->SetLineColor(kBlue);
  hECALTT_Endcap_CompressedEt->GetXaxis()->SetTitle("Compressed E_{T} [GeV]");
  hECALTT_Endcap_CompressedEt->GetYaxis()->SetTitle("Entries");
  hECALTT_Endcap_CompressedEt->Draw();
  c->SetLogy();
  c->SaveAs("ECALTT_Endcap_CompressedEt.pdf");
  
  c->SetLogy(false);
  TH2D *hECALTT_CompressedEt127_EtaPhiTotal = (TH2D*) fSig["PU40bx25_VBF_HToInv_M-125_13TeV"]->Get(Form("Run_%d/EcalTT/ECALTT_CompressedEt127_EtaPhiTotal",1));
  hECALTT_CompressedEt127_EtaPhiTotal->SetLineColor(kBlue);
  hECALTT_CompressedEt127_EtaPhiTotal->GetXaxis()->SetTitle("RCT iEta");
  hECALTT_CompressedEt127_EtaPhiTotal->GetXaxis()->SetLabelSize(0.015);
  hECALTT_CompressedEt127_EtaPhiTotal->GetYaxis()->SetTitle("RCT iPhi");
  hECALTT_CompressedEt127_EtaPhiTotal->GetYaxis()->SetLabelSize(0.015);
  hECALTT_CompressedEt127_EtaPhiTotal->Draw("colz");
  c->SaveAs("ECALTT_CompressedEt127_EtaPhiTotal.pdf");  
  
  delete c;
  
  return 0;  
  
};
