#include "TFile.h"
#include "TH1D.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

using namespace std;

map<string,double> doEffL1T(TFile* f,int run){
  
  TH1D* hTotal = (TH1D*) f->Get(Form("Run_%d/EventCount",run));
  double nEvents = hTotal->GetBinContent(1);

  TH1D* hL1T = (TH1D*) f->Get(Form("Run_%d/L1AlgoCounts",run));
  map<string,double> out;
  
  for(int i=1; i<hL1T->GetXaxis()->GetNbins()+1; i++){
    out[hL1T->GetXaxis()->GetBinLabel(i)] = (hL1T->GetBinContent(i)/nEvents);
  }
  
  return out;
}

std::string parseToLaTeX(std::string s) {
  
  boost::replace_all(s,"_","\\_");
  return s;
}

map<string,double> doEffHLT(TFile* f,int run){
  
  TH1D* hTotal = (TH1D*) f->Get(Form("Run_%d/EventCount",run));
  double nEvents = hTotal->GetBinContent(1);

  TH1D* hHLT = (TH1D*) f->Get(Form("Run_%d/HLTAlgoCounts",run));
  map<string,double> out;
  
  for(int i=1; i<hHLT->GetXaxis()->GetNbins()+1; i++){
    out[hHLT->GetXaxis()->GetBinLabel(i)] = (hHLT->GetBinContent(i)/nEvents);
  }
  
  return out;
}

int main(){

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

  // For rate
  map<string,double> l1tPU20bx25n = doEffL1T(files["PU20bx25_Neutrino_gun"],1);
  map<string,double> l1tPU40bx50n = doEffL1T(files["PU40bx50_Neutrino_gun"],1);
  map<string,double> l1tPU40bx25n = doEffL1T(files["PU40bx25_Neutrino_gun"],1);
  
  map<string,double> hltPU20bx25n = doEffHLT(files["PU20bx25_Neutrino_gun"],1);
  map<string,double> hltPU40bx50n = doEffHLT(files["PU40bx50_Neutrino_gun"],1);
  map<string,double> hltPU40bx25n = doEffHLT(files["PU40bx25_Neutrino_gun"],1);
  
  // For eff
  map<string,double> l1tPU20bx25v = doEffL1T(files["PU20bx25_VBF_HToInv_M-125_13TeV"],1);
  map<string,double> l1tPU40bx50v = doEffL1T(files["PU40bx50_VBF_HToInv_M-125_13TeV"],1);
  map<string,double> l1tPU40bx25v = doEffL1T(files["PU40bx25_VBF_HToInv_M-125_13TeV"],1);
  
  map<string,double> hltPU20bx25v = doEffHLT(files["PU20bx25_VBF_HToInv_M-125_13TeV"],1);
  map<string,double> hltPU40bx50v = doEffHLT(files["PU40bx50_VBF_HToInv_M-125_13TeV"],1);
  map<string,double> hltPU40bx25v = doEffHLT(files["PU40bx25_VBF_HToInv_M-125_13TeV"],1);
  
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
    
  FILE* pFile = fopen("VBFInv_L1TSignalEffiency.tex","w");
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%20s & %8s & %8s & %8s \\\\\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selL1T.size(); i++){
    fprintf (pFile,"%20s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selL1T[i]).c_str(),
           l1tPU20bx25v[selL1T[i]],
           l1tPU40bx50v[selL1T[i]],
           l1tPU40bx25v[selL1T[i]]);    
  }
  fprintf (pFile,"\\hline");
  fprintf (pFile,"\\end{tabular}");
  fclose (pFile);
  
  
  pFile = fopen ("VBFInv_HLTSignalEffiency.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%50s & %8s & %8s & %8s \\\\\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selHLT.size(); i++){
    fprintf(pFile,"%50s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selHLT[i]).c_str(),
           hltPU20bx25v[selHLT[i]],
           hltPU40bx50v[selHLT[i]],
           hltPU40bx25v[selHLT[i]]); 
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_L1TBunchEff.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%20s & %8s & %8s & %8s \\\\\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selL1T.size(); i++){
    fprintf(pFile,"%20s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selL1T[i]).c_str(),
           l1tPU20bx25n[selL1T[i]],
           l1tPU40bx50n[selL1T[i]],
           l1tPU40bx25n[selL1T[i]]);    
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_HLTBunchEff.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%50s & %8s & %8s & %8s \\\\\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selHLT.size(); i++){
    fprintf(pFile,"%50s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selHLT[i]).c_str(),
           hltPU20bx25n[selHLT[i]],
           hltPU40bx50n[selHLT[i]],
           hltPU40bx25n[selHLT[i]]); 
  }  
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_L1TBunchRate.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%20s & %8s & %8s & %8s \\\\\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selL1T.size(); i++){
    fprintf(pFile,"%20s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selL1T[i]).c_str(),
           l1tPU20bx25n[selL1T[i]]*double(ratePerBunch),
           l1tPU40bx50n[selL1T[i]]*double(ratePerBunch),
           l1tPU40bx25n[selL1T[i]]*double(ratePerBunch));    
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_HLTBunchRate.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%50s & %8s & %8s & %8s \\\\\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selHLT.size(); i++){
    fprintf(pFile,"%50s & %8.6f & %8.6f & %8.6f \\\\\n",parseToLaTeX(selHLT[i]).c_str(),
           hltPU20bx25n[selHLT[i]]*double(ratePerBunch),
           hltPU40bx50n[selHLT[i]]*double(ratePerBunch),
           hltPU40bx25n[selHLT[i]]*double(ratePerBunch)); 
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_L1TMaxRate.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%20s & %10s & %10s & %10s \\\\\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selL1T.size(); i++){
    fprintf(pFile,"%20s & %10.2f & %10.2f & %10.2f \\\\\n",parseToLaTeX(selL1T[i]).c_str(),
           l1tPU20bx25n[selL1T[i]]*double(ratePerBunch)*double(nMaxBunch25ns),
           l1tPU40bx50n[selL1T[i]]*double(ratePerBunch)*double(nMaxBunch50ns),
           l1tPU40bx25n[selL1T[i]]*double(ratePerBunch)*double(nMaxBunch25ns));    
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  pFile = fopen ("NeutrinoGun_HLTMaxRate.tex","w");;
  fprintf(pFile,"\\begin{tabular}{|l|c|c|c|}\n");
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"%50s & %8s & %8s & %8s \\\\\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  fprintf(pFile,"\\hline\\hline\n");
  for(unsigned i=0; i<selHLT.size(); i++){
    fprintf(pFile,"%50s & %8.2f & %8.2f & %8.2f \\\\\n",parseToLaTeX(selHLT[i]).c_str(),
           hltPU20bx25n[selHLT[i]]*double(ratePerBunch)*double(nMaxBunch25ns),
           hltPU40bx50n[selHLT[i]]*double(ratePerBunch)*double(nMaxBunch50ns),
           hltPU40bx25n[selHLT[i]]*double(ratePerBunch)*double(nMaxBunch25ns)); 
  }
  fprintf(pFile,"\\hline\n");
  fprintf(pFile,"\\end{tabular}\n");
  fclose (pFile);
  
  return 0;  
  
};
