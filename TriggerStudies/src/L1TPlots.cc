#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TPlots.h"

#include "TDirectory.h"
#include "TMath.h"

using namespace std;

L1TPlots::L1TPlots(){
  l1t_etm     = 0;
  dijet_pt0   = 0;
  dijet_pt1   = 0; 
  dijet_eta0  = 0; 
  dijet_eta1  = 0; 
  dijet_deta  = 0; 
  dijet_dphi  = 0; 
  dijet_mjj   = 0; 
  
  jet0_met_dphi     = 0;
  jet1_met_dphi     = 0;
  dijet_met_mindphi = 0;
  dijet_met_maxdphi = 0;
  jets_met_mindphi  = 0;
  jets_met_maxdphi  = 0;
  
  MHToverHTT = 0;
  
}

L1TPlots::L1TPlots(TDirectory* d){
  
  l1t_etm = new TH1D("L1T_ETM",   "L1T ETM"  , 500,-0.5,495.5);                   
  l1t_etm->GetXaxis()->SetTitle("L1T ETM [GeV]");
  l1t_etm->GetYaxis()->SetTitle("Entries");    
  l1t_etm->SetDirectory(d);   
  
  dijet_pt0 = new TH1D("dijet_pt0 ","dijet_pt0", 500,-0.5,495.5);                   
  dijet_pt0->GetXaxis()->SetTitle("Dijet p_{#perp}^{Jet0}");  
  dijet_pt0->GetYaxis()->SetTitle("Entries");
  dijet_pt0->SetDirectory(d); 
  
  dijet_pt1 = new TH1D("dijet_pt1 ","dijet_pt1", 500,-0.5,495.5);                   
  dijet_pt1->GetXaxis()->SetTitle("Dijet p_{#perp}^{Jet1}");  
  dijet_pt1->GetYaxis()->SetTitle("Entries");  
  dijet_pt1->SetDirectory(d); 
  
  dijet_eta0 = new TH1D("dijet_eta0","dijet_eta0",100,-5.0,5.0);                   
  dijet_eta0->GetXaxis()->SetTitle("Dijet #eta^{Jet0}"); 
  dijet_eta0->GetYaxis()->SetTitle("Entries"); 
  dijet_eta0->SetDirectory(d);
  
  dijet_eta1 = new TH1D("dijet_eta1","dijet_eta1",100,-5.0,5.0);                   
  dijet_eta1->GetXaxis()->SetTitle("Dijet #eta^{Jet0}"); 
  dijet_eta1->GetYaxis()->SetTitle("Entries"); 
  dijet_eta1->SetDirectory(d);
  
  dijet_deta = new TH1D("dijet_deta","dijet_deta",100,0,10.0);                 
  dijet_deta->GetXaxis()->SetTitle("Dijet #Delta#eta"); 
  dijet_deta->GetYaxis()->SetTitle("Entries"); 
  dijet_deta->SetDirectory(d);
  
  dijet_dphi = new TH1D("dijet_dphi","dijet_dphi",32,0,TMath::Pi()); 
  dijet_dphi->GetXaxis()->SetTitle("Dijet #Delta#phi"); 
  dijet_dphi->GetYaxis()->SetTitle("Entries"); 
  dijet_dphi->SetDirectory(d);
  
  dijet_mjj = new TH1D("dijet_mjj ","dijet_mjj",500,0,2000);                   
  dijet_mjj->GetXaxis()->SetTitle("Dijet M_{jj}");  
  dijet_mjj->GetYaxis()->SetTitle("Entries");  
  dijet_mjj->SetDirectory(d);
  
  jet0_met_dphi = new TH1D("jet0_met_dphi",   "jet0_met_dphi",   32,0,TMath::Pi());  
  jet0_met_dphi->GetXaxis()->SetTitle("#Delta#phi(met,jet_{0})");
  jet0_met_dphi->GetYaxis()->SetTitle("Entries");
  jet0_met_dphi->SetDirectory(d);
  
  jet1_met_dphi = new TH1D("jet1_met_dphi",   "jet1_met_dphi",   32,0,TMath::Pi()); 
  jet1_met_dphi->GetXaxis()->SetTitle("#Delta#phi(met,jet_{1})");
  jet1_met_dphi->GetYaxis()->SetTitle("Entries");
  jet1_met_dphi->SetDirectory(d);

  dijet_met_mindphi = new TH1D("dijet_met_mindphi","dijet_met_mindphi",32,0,TMath::Pi()); 
  dijet_met_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(met,dijet))");
  dijet_met_mindphi->GetYaxis()->SetTitle("Entries");
  dijet_met_mindphi->SetDirectory(d);
  
  dijet_met_maxdphi = new TH1D("dijet_met_maxdphi","dijet_met_maxdphi",32,0,TMath::Pi()); 
  dijet_met_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(met,dijet))");
  dijet_met_maxdphi->GetYaxis()->SetTitle("Entries");
  dijet_met_maxdphi->SetDirectory(d);
  
  jets_met_mindphi = new TH1D("jets_met_mindphi","jets_met_mindphi",32,0,TMath::Pi()); 
  jets_met_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(met,jets))");
  jets_met_mindphi->GetYaxis()->SetTitle("Entries");
  jets_met_mindphi->SetDirectory(d);
  
  jets_met_maxdphi = new TH1D("jets_met_maxdphi","jets_met_maxdphi",32,0,TMath::Pi()); 
  jets_met_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(met,jets))");
  jets_met_maxdphi->GetYaxis()->SetTitle("Entries");
  jets_met_maxdphi->SetDirectory(d);
  
  MHToverHTT = new TH1D("MHToverHTT ","MHToverHTT",100,0,1.0);
  MHToverHTT->GetXaxis()->SetTitle("MHT over HTT");
  MHToverHTT->GetYaxis()->SetTitle("Entries");
  MHToverHTT->SetDirectory(d);
  
}

void L1TPlots::doEff(double entries){
  TDirectory *d    = l1t_etm->GetDirectory();
  TDirectory *dEff = d->mkdir("Efficiency");
  
  doPlotEff(l1t_etm,          entries,dEff);
  doPlotEff(dijet_pt0,        entries,dEff);
  doPlotEff(dijet_pt1,        entries,dEff);
  doPlotEff(dijet_deta,       entries,dEff);
  doPlotEff(dijet_dphi,       entries,dEff);
  doPlotEff(dijet_mjj,        entries,dEff);
  doPlotEff(jet0_met_dphi,    entries,dEff);
  doPlotEff(jet1_met_dphi,    entries,dEff);
  doPlotEff(dijet_met_mindphi,entries,dEff);
  doPlotEff(dijet_met_maxdphi,entries,dEff);
  doPlotEff(jets_met_mindphi, entries,dEff);
  doPlotEff(jets_met_maxdphi, entries,dEff);
  doPlotEff(MHToverHTT,       entries,dEff);
  
}

void L1TPlots::doPlotEff(TH1D *h,double entries,TDirectory *d){
  TH1D *eff = (TH1D*) h ->Clone(Form("eff_%s",h->GetTitle())); 
  for(int i=0; i<=eff->GetNbinsX()+1; i++){
    eff->SetBinContent(i,eff->Integral(i,eff->GetNbinsX()+1));
  }
  eff->Scale(1/entries);
  eff->SetDirectory(d);
}

void L1TPlots::fill(L1TPlotsData data){
  if(data.l1t_etm.first)          {l1t_etm          ->Fill(data.l1t_etm.second);}
  if(data.dijet_pt0.first)        {dijet_pt0        ->Fill(data.dijet_pt0.second);}
  if(data.dijet_pt1.first)        {dijet_pt1        ->Fill(data.dijet_pt1.second);}
  if(data.dijet_eta0.first)       {dijet_eta0       ->Fill(data.dijet_eta0.second);}
  if(data.dijet_eta1.first)       {dijet_eta1       ->Fill(data.dijet_eta1.second);}
  if(data.dijet_deta.first)       {dijet_deta       ->Fill(data.dijet_deta.second);}
  if(data.dijet_dphi.first)       {dijet_dphi       ->Fill(data.dijet_dphi.second);}
  if(data.dijet_mjj.first)        {dijet_mjj        ->Fill(data.dijet_mjj.second);}
  if(data.jet0_met_dphi.first)    {jet0_met_dphi    ->Fill(data.jet0_met_dphi.second);}
  if(data.jet1_met_dphi.first)    {jet1_met_dphi    ->Fill(data.jet1_met_dphi.second);}
  if(data.dijet_met_mindphi.first){dijet_met_mindphi->Fill(data.dijet_met_mindphi.second);}
  if(data.dijet_met_maxdphi.first){dijet_met_maxdphi->Fill(data.dijet_met_maxdphi.second);}
  if(data.jets_met_mindphi.first) {jets_met_mindphi ->Fill(data.jets_met_mindphi.second);}
  if(data.jets_met_maxdphi.first) {jets_met_maxdphi ->Fill(data.jets_met_maxdphi.second);}
  if(data.MHToverHTT.first)       {MHToverHTT       ->Fill(data.MHToverHTT.second);}
}

L1TPlots::~L1TPlots(){
  delete l1t_etm;  
  delete dijet_pt0;
  delete dijet_pt1;
  delete dijet_eta0;
  delete dijet_eta1;
  delete dijet_deta;
  delete dijet_dphi;
  delete dijet_mjj;
  
  delete jet0_met_dphi;
  delete jet1_met_dphi;
  delete dijet_met_mindphi;
  delete dijet_met_maxdphi;
  delete jets_met_mindphi;
  delete jets_met_maxdphi;
  
  delete MHToverHTT;
}
