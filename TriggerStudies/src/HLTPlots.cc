#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPlots.h"

#include "TDirectory.h"
#include "TMath.h"

using namespace std;

HLTPlots::HLTPlots(){

  pf_met           = 0;
  pf_dijet_maxDEta = 0;
  pf_dijet_maxMjj  = 0;
  
  calo_met           = 0;
  calo_dijet_maxDEta = 0;
  calo_dijet_maxMjj  = 0;

}

HLTPlots::HLTPlots(TDirectory* d){

  // PF plots
  pf_met = new TH1D("pf_met","HLT PF MET",500,0,500);
  pf_met->GetXaxis()->SetTitle("MET [GeV]");
  pf_met->GetYaxis()->SetTitle("Entries");
  pf_met->SetDirectory(d);
  
  pf_dijet_maxDEta = new TH1D("pf_dijet_maxDEta","HLT PF Dijet max(#Delta#eta)" ,100,0,10);
  pf_dijet_maxDEta->GetXaxis()->SetTitle("Dijet max(#Delta#eta)");
  pf_dijet_maxDEta->GetYaxis()->SetTitle("Entries");
  pf_dijet_maxDEta->SetDirectory(d);
  
  pf_dijet_maxMjj = new TH1D("pf_dijet_maxMjj","HLT PF Dijet max(m_{jj})"  , 400,  0,2000);
  pf_dijet_maxMjj->GetXaxis()->SetTitle("Dijet max(m_{jj} [GeV]");
  pf_dijet_maxMjj->GetYaxis()->SetTitle("Entries");
  pf_dijet_maxMjj->SetDirectory(d);
  
  // Calo plots
  calo_met = new TH1D("calo_met","HLT PF MET"  , 500, 0,500);
  calo_met->GetXaxis()->SetTitle("HLT MET [GeV]");
  calo_met->GetYaxis()->SetTitle("Entries");
  calo_met->SetDirectory(d);
  
  calo_dijet_maxDEta = new TH1D("calo_dijet_maxDEta","HLT PF Dijet max(#Delta#eta)" ,100,0,10);
  calo_dijet_maxDEta->GetXaxis()->SetTitle("Dijet max(#Delta#eta)");
  calo_dijet_maxDEta->GetYaxis()->SetTitle("Entries");
  calo_dijet_maxDEta->SetDirectory(d);
  
  calo_dijet_maxMjj = new TH1D("calo_dijet_maxMjj","HLT PF Dijet max(m_{jj})"  , 400, 0,2000);
  calo_dijet_maxMjj->GetXaxis()->SetTitle("Dijet max(m_{jj} [GeV]");
  calo_dijet_maxMjj->GetYaxis()->SetTitle("Entries");
  calo_dijet_maxMjj->SetDirectory(d);
  
}

void HLTPlots::fill(HLTPlotsData data){
  
  if(data.pf_met          .first){pf_met          ->Fill(data.pf_met          .second);}
  if(data.pf_dijet_maxDEta.first){pf_dijet_maxDEta->Fill(data.pf_dijet_maxDEta.second);}
  if(data.pf_dijet_maxMjj .first){pf_dijet_maxMjj ->Fill(data.pf_dijet_maxMjj .second);}
  
  if(data.calo_met          .first){calo_met          ->Fill(data.calo_met          .second);}
  if(data.calo_dijet_maxDEta.first){calo_dijet_maxDEta->Fill(data.calo_dijet_maxDEta.second);}
  if(data.calo_dijet_maxMjj .first){calo_dijet_maxMjj ->Fill(data.calo_dijet_maxMjj .second);}
  
}

HLTPlots::~HLTPlots(){
  delete pf_met;
  delete pf_dijet_maxDEta;
  delete pf_dijet_maxMjj;
  
  delete calo_met;
  delete calo_dijet_maxDEta;
  delete calo_dijet_maxMjj;
}
