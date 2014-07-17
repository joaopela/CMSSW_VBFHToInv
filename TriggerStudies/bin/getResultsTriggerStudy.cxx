#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

#include "Plots/Style/interface/Style.h"
#include "Latex/Table/interface/LatexTabular.h"

using namespace std;

//####################################################################
map<string,double> getEff(TFile* f,int run,string histname,double multiplier=1){
  
  TH1D* hTotal = (TH1D*) f->Get(Form("Run_%d/EventCount",run));
  double nEvents = hTotal->GetBinContent(1);

  TH1D* hL1T = (TH1D*) f->Get(Form("Run_%d/%s",run,histname.c_str()));
  map<string,double> out;
  
  for(int i=1; i<hL1T->GetXaxis()->GetNbins()+1; i++){
    out[hL1T->GetXaxis()->GetBinLabel(i)] = (hL1T->GetBinContent(i)/nEvents)*multiplier;
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
int main(){

  rat::Style myStyle;
  myStyle.setTDRStyle();
  
  const int nMaxBunch50ns = 1380;
  const int nMaxBunch25ns = 2808;
  const int ratePerBunch  = 11246;
  
  map<string,TFile*> files;
  files["PU20bx25_Neutrino_gun"]           = new TFile("PU20bx25_Neutrino_Pt-2to20_gun.root");
  files["PU40bx50_Neutrino_gun"]           = new TFile("PU40bx50_Neutrino_Pt-2to20_gun.root");
  files["PU40bx25_Neutrino_gun"]           = new TFile("PU40bx25_Neutrino_Pt-2to20_gun.root");
  
  files["PU20bx25_VBF_HToInv_M-125_13TeV"] = new TFile("PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
  files["PU40bx50_VBF_HToInv_M-125_13TeV"] = new TFile("PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
  files["PU40bx25_VBF_HToInv_M-125_13TeV"] = new TFile("PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6.root");
 
  // For eff
  map<string,double> l1tPU20bx25v = getEff(files["PU20bx25_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  map<string,double> l1tPU40bx50v = getEff(files["PU40bx50_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  map<string,double> l1tPU40bx25v = getEff(files["PU40bx25_VBF_HToInv_M-125_13TeV"],1,"L1AlgoCounts");
  
  map<string,double> hltPU20bx25v = getEff(files["PU20bx25_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx50v = getEff(files["PU40bx50_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx25v = getEff(files["PU40bx25_VBF_HToInv_M-125_13TeV"],1,"HLTAlgoCounts");
  
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

  doTableL1T(selL1T,l1tPU20bx25v,l1tPU40bx50v,l1tPU40bx25v,"VBFInv_L1TSignalEffiency.tex");
  doTableHLT(selHLT,hltPU20bx25v,hltPU40bx50v,hltPU40bx25v,"VBFInv_HLTSignalEffiency.tex");

  map<string,double> l1tPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts" );
  map<string,double> l1tPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts" );
  map<string,double> l1tPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts" );
  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TBunchEff.tex");
  
  map<string,double> hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts");
  map<string,double> hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff.tex");
  
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_ETM");
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_ETM");
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_ETM");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_ETM.tex");
  
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_HTT");
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_HTT");
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_HTT");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_HTT.tex");
  
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_Both");
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_Both");
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_Both");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_Both.tex");
  
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts_None");
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts_None");
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts_None");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchEff_None.tex");
  
  
  l1tPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  l1tPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  l1tPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch));
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch));
  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TBunchRate.tex");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTBunchRate.tex");

  l1tPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch25ns));
  l1tPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch50ns));
  l1tPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"L1AlgoCounts", double(ratePerBunch)*double(nMaxBunch25ns));
  hltPU20bx25n = getEff(files["PU20bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch25ns));
  hltPU40bx50n = getEff(files["PU40bx50_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch50ns));
  hltPU40bx25n = getEff(files["PU40bx25_Neutrino_gun"],1,"HLTAlgoCounts",double(ratePerBunch)*double(nMaxBunch25ns));
  doTableL1T(selL1T,l1tPU20bx25n,l1tPU40bx50n,l1tPU40bx25n,"NeutrinoGun_L1TMaxRate.tex");
  doTableHLT(selHLT,hltPU20bx25n,hltPU40bx50n,hltPU40bx25n,"NeutrinoGun_HLTMaxRate.tex");
  
  map<string,TH1D*> hL1ETM,hL1HTT;
  hL1ETM["PU20bx25_Neutrino_gun"] = (TH1D*) files["PU20bx25_Neutrino_gun"]->Get(Form("Run_%d/L1ETM",1));
  hL1ETM["PU40bx50_Neutrino_gun"] = (TH1D*) files["PU40bx50_Neutrino_gun"]->Get(Form("Run_%d/L1ETM",1));
  hL1ETM["PU40bx25_Neutrino_gun"] = (TH1D*) files["PU40bx25_Neutrino_gun"]->Get(Form("Run_%d/L1ETM",1));
  hL1HTT["PU20bx25_Neutrino_gun"] = (TH1D*) files["PU20bx25_Neutrino_gun"]->Get(Form("Run_%d/L1HTT",1));
  hL1HTT["PU40bx50_Neutrino_gun"] = (TH1D*) files["PU40bx50_Neutrino_gun"]->Get(Form("Run_%d/L1HTT",1));
  hL1HTT["PU40bx25_Neutrino_gun"] = (TH1D*) files["PU40bx25_Neutrino_gun"]->Get(Form("Run_%d/L1HTT",1));
  
  TCanvas cL1ETM;
  cL1ETM.SetLogy();
  hL1ETM["PU20bx25_Neutrino_gun"]->SetLineColor(kRed);
  hL1ETM["PU40bx50_Neutrino_gun"]->SetLineColor(kGreen);
  hL1ETM["PU40bx25_Neutrino_gun"]->SetLineColor(kBlue);
  
  hL1ETM["PU20bx25_Neutrino_gun"]->Draw();
  hL1ETM["PU40bx50_Neutrino_gun"]->Draw("same");
  hL1ETM["PU40bx25_Neutrino_gun"]->Draw("same");
  
  TLegend lL1ETM(0.55,0.85,0.85,0.95); ;
  lL1ETM.AddEntry(hL1ETM["PU20bx25_Neutrino_gun"],"PU20bx25","l");
  lL1ETM.AddEntry(hL1ETM["PU40bx50_Neutrino_gun"],"PU40bx50","l");
  lL1ETM.AddEntry(hL1ETM["PU40bx25_Neutrino_gun"],"PU40bx25","l");
  lL1ETM.Draw();
  
  cL1ETM.SaveAs("cL1ETM.pdf");
  
  TCanvas cL1HTT;
  cL1HTT.SetLogy();
  hL1HTT["PU20bx25_Neutrino_gun"]->SetLineColor(kRed);
  hL1HTT["PU40bx50_Neutrino_gun"]->SetLineColor(kGreen);
  hL1HTT["PU40bx25_Neutrino_gun"]->SetLineColor(kBlue);
  
  hL1HTT["PU20bx25_Neutrino_gun"]->Draw();
  hL1HTT["PU40bx50_Neutrino_gun"]->Draw("same");
  hL1HTT["PU40bx25_Neutrino_gun"]->Draw("same");
  
  TLegend lL1HTT(0.55,0.85,0.85,0.95); ;
  lL1HTT.AddEntry(hL1ETM["PU20bx25_Neutrino_gun"],"PU20bx25","l");
  lL1HTT.AddEntry(hL1ETM["PU40bx50_Neutrino_gun"],"PU40bx50","l");
  lL1HTT.AddEntry(hL1ETM["PU40bx25_Neutrino_gun"],"PU40bx25","l");
  lL1HTT.Draw();
  
  cL1HTT.SaveAs("cL1HTT.pdf");
  
  
  return 0;  
  
};
