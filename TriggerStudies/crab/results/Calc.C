#include "TFile.h"
#include "TH1D.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string,double> doEffL1T(TFile* f,int run){
  
  TH1D* hTotal = (TH1D*) f->Get("Runs");
  double nEvents = hTotal->GetBinContent(run);

  TH1D* hL1T = (TH1D*) f->Get(Form("L1AlgoCounts_Run%d",run));

  map<string,double> out;
  
  for(unsigned i=1; i<hL1T->GetXaxis()->GetNbins()+1; i++){
    out[hL1T->GetXaxis()->GetBinLabel(i)] = (hL1T->GetBinContent(i)/nEvents);
  }
  
  return out;
}

map<string,double> doEffHLT(TFile* f,int run){
  
  TH1D* hTotal = (TH1D*) f->Get("Runs");
  double nEvents = hTotal->GetBinContent(run);
  
  TH1D* hHLT = (TH1D*) f->Get(Form("HLTAlgoCounts_Run%d",run));
  
  map<string,double> out;
  
  for(unsigned i=1; i<hHLT->GetXaxis()->GetNbins()+1; i++){
    out[hHLT->GetXaxis()->GetBinLabel(i)] = (hHLT->GetBinContent(i)/nEvents);
  }
  
  return out;
}

int main(){

  const int nMaxBunch50ns = 1380;
  const int nMaxBunch25ns = 2808;
  const int ratePerBunch  = 11246;
   
  TFile* fPU20bx25 = new TFile("PU20bx25_Neutrino_Pt-2to20_gun.root");
  TFile* fPU40bx25 = new TFile("PU40bx25_Neutrino_Pt-2to20_gun.root");
  TFile* fPU40bx50 = new TFile("PU40bx50_Neutrino_Pt-2to20_gun.root");
 
  map<string,double> l1tPU20bx25 = doEffL1T(fPU20bx25,1);
  map<string,double> l1tPU40bx25 = doEffL1T(fPU40bx25,1);
  map<string,double> l1tPU40bx50 = doEffL1T(fPU40bx50,1);
  
  map<string,double> hltPU20bx25 = doEffHLT(fPU20bx25,1);
  map<string,double> hltPU40bx25 = doEffHLT(fPU40bx25,1);
  map<string,double> hltPU40bx50 = doEffHLT(fPU40bx50,1);
    
  vector<string> selL1T;
  selL1T.push_back("L1_ETM30");
  selL1T.push_back("L1_ETM36");
  selL1T.push_back("L1_ETM50");
  selL1T.push_back("L1_ETM70");
  selL1T.push_back("L1_ETM100");
  
  vector<string> selHLT;
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v");
  selHLT.push_back("HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v");
  selHLT.push_back("HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v");
  selHLT.push_back("HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v");
  selHLT.push_back("HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v");
  selHLT.push_back("HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v");  
  selHLT.push_back("HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v");  
    
  printf("|%20s| %8s | %8s | %8s |\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selL1T.size(); i++){
    printf("|%20s| %8.6f | %8.6f | %8.6f |\n",selL1T[i].c_str(),
           l1tPU20bx25[selL1T[i]],
           l1tPU40bx50[selL1T[i]],
           l1tPU40bx25[selL1T[i]]);    
  }
  
  printf("\n\n");
  printf("|%50s| %8s | %8s | %8s |\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selHLT.size(); i++){
    printf("|%50s| %8.6f | %8.6f | %8.6f |\n",selHLT[i].c_str(),
           hltPU20bx25[selHLT[i]],
           hltPU40bx50[selHLT[i]],
           hltPU40bx25[selHLT[i]]); 
  }
  
  //____________________________________________________________
  printf("\n\n");
  printf("|%20s| %8s | %8s | %8s |\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selL1T.size(); i++){
    printf("|%20s| %8.6f | %8.6f | %8.6f |\n",selL1T[i].c_str(),
           l1tPU20bx25[selL1T[i]]*ratePerBunch,
           l1tPU40bx50[selL1T[i]]*ratePerBunch,
           l1tPU40bx25[selL1T[i]]*ratePerBunch);    
  }
  
  printf("\n\n");
  printf("|%50s| %8s | %8s | %8s |\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selHLT.size(); i++){
    printf("|%50s| %8.6f | %8.6f | %8.6f |\n",selHLT[i].c_str(),
           hltPU20bx25[selHLT[i]]*ratePerBunch,
           hltPU40bx50[selHLT[i]]*ratePerBunch,
           hltPU40bx25[selHLT[i]]*ratePerBunch); 
  }
  
  //____________________________________________________________
  printf("\n\n");
  printf("|%20s| %10s | %10s | %10s |\n","L1T","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selL1T.size(); i++){
    printf("|%20s| %10.2f | %10.2f | %10.2f |\n",selL1T[i].c_str(),
           l1tPU20bx25[selL1T[i]]*ratePerBunch*nMaxBunch25ns,
           l1tPU40bx50[selL1T[i]]*ratePerBunch*nMaxBunch50ns,
           l1tPU40bx25[selL1T[i]]*ratePerBunch*nMaxBunch25ns);    
  }
  
  printf("\n\n");
  printf("|%50s| %8s | %8s | %8s |\n","HLT","PU20bx25","PU40bx50","PU40bx25");
  for(unsigned i=0; i<selHLT.size(); i++){
    printf("|%50s| %8.2f | %8.2f | %8.2f |\n",selHLT[i].c_str(),
           hltPU20bx25[selHLT[i]]*ratePerBunch*nMaxBunch25ns,
           hltPU40bx50[selHLT[i]]*ratePerBunch*nMaxBunch50ns,
           hltPU40bx25[selHLT[i]]*ratePerBunch*nMaxBunch25ns); 
  }
  
  
  return 0;  
  
};
