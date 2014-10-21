#include "VBFHiggsToInvisible/TriggerStudies/interface/L1TPlots.h"

#include "TDirectory.h"
#include "TMath.h"

using namespace std;

L1TPlots::L1TPlots(){
  l1t_ett     = 0;
  l1t_etm     = 0;
  l1t_htt     = 0;
  l1t_mht     = 0;
  
  nJets_total   = 0;
  nJets_central = 0;
  nJets_forward = 0;
  
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

  jets_mindeta     = 0;
  jets_maxdeta     = 0;
  jets_mindphi     = 0;
  jets_maxdphi     = 0;
  jets_minmjj      = 0;
  jets_maxmjj      = 0;
  
  jets_met_mindphi   = 0;
  jets_met_maxdphi   = 0;
  jets40_met_mindphi = 0;
  jets40_met_maxdphi = 0;
  
  MHToverHTT = 0;
  
}

L1TPlots::L1TPlots(TDirectory* d){
  
  l1t_ett = new TH1D("l1t_ett",   "L1T ETT"  , 500,0,500);
  l1t_ett->GetXaxis()->SetTitle("L1T ETT [GeV]");
  l1t_ett->GetYaxis()->SetTitle("Entries");
  l1t_ett->SetDirectory(d);

  l1t_etm = new TH1D("l1t_etm",   "L1T ETM"  , 500,0,500);
  l1t_etm->GetXaxis()->SetTitle("L1T ETM [GeV]");
  l1t_etm->GetYaxis()->SetTitle("Entries");
  l1t_etm->SetDirectory(d);
  
  l1t_htt = new TH1D("l1t_htt",   "L1T HTT"  , 500,0,500);
  l1t_htt->GetXaxis()->SetTitle("L1T HTT [GeV]");
  l1t_htt->GetYaxis()->SetTitle("Entries");
  l1t_htt->SetDirectory(d);
  
  l1t_mht = new TH1D("l1t_mht",   "L1T MHT"  , 500,0,500);
  l1t_mht->GetXaxis()->SetTitle("L1T MHT [GeV]");
  l1t_mht->GetYaxis()->SetTitle("Entries");
  l1t_mht->SetDirectory(d);
  
  nJets_total = new TH1D("nJets_total",   "n_{Jets} Total"  , 21,-0.5,20.5);
  nJets_total->GetXaxis()->SetTitle("n_{Jets} Total [GeV]");
  nJets_total->GetYaxis()->SetTitle("Entries");
  nJets_total->SetDirectory(d);
  
  nJets_central = new TH1D("nJets_central",   "n_{Jets} Central"  , 21,-0.5,20.5);
  nJets_central->GetXaxis()->SetTitle("n_{Jets} Central [GeV]");
  nJets_central->GetYaxis()->SetTitle("Entries");
  nJets_central->SetDirectory(d);
  
  nJets_forward = new TH1D("nJets_forward",   "n_{Jets} Forward"  , 21,-0.5,20.5);
  nJets_forward->GetXaxis()->SetTitle("n_{Jets} Forward [GeV]");
  nJets_forward->GetYaxis()->SetTitle("Entries");
  nJets_forward->SetDirectory(d);
  
  dijet_pt0 = new TH1D("dijet_pt0 ","dijet_pt0", 500, 0,500);
  dijet_pt0->GetXaxis()->SetTitle("Dijet p_{#perp}^{Jet0}");  
  dijet_pt0->GetYaxis()->SetTitle("Entries");
  dijet_pt0->SetDirectory(d);
  
  dijet_pt1 = new TH1D("dijet_pt1 ","dijet_pt1", 500,0,500);
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
  
  jets_mindeta = new TH1D("jets_mindeta","jets_mindeta",100,0,10.0); 
  jets_mindeta->GetXaxis()->SetTitle("Min(#Delta#eta(jet,jet))");
  jets_mindeta->GetYaxis()->SetTitle("Entries");
  jets_mindeta->SetDirectory(d);
  
  jets_maxdeta = new TH1D("jets_maxdeta","jets_maxdeta",100,0,10.0); 
  jets_maxdeta->GetXaxis()->SetTitle("Max(#Delta#eta(jet,jet))");
  jets_maxdeta->GetYaxis()->SetTitle("Entries");
  jets_maxdeta->SetDirectory(d);
  
  jets_mindphi = new TH1D("jets_mindphi","jets_mindphi",32,0,TMath::Pi()); 
  jets_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(jet,jet))");
  jets_mindphi->GetYaxis()->SetTitle("Entries");
  jets_mindphi->SetDirectory(d);
  
  jets_maxdphi = new TH1D("jets_maxdphi","jets_maxdphi",32,0,TMath::Pi()); 
  jets_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(jet,jet))");
  jets_maxdphi->GetYaxis()->SetTitle("Entries");
  jets_maxdphi->SetDirectory(d);

  jets_minmjj = new TH1D("jets_minmjj","jets_minmjj",500,0,2000); 
  jets_minmjj->GetXaxis()->SetTitle("Min(m_{jj}(jet,jet))");
  jets_minmjj->GetYaxis()->SetTitle("Entries");
  jets_minmjj->SetDirectory(d);
  
  jets_maxmjj = new TH1D("jets_maxmjj","jets_maxmjj",500,0,2000); 
  jets_maxmjj->GetXaxis()->SetTitle("Max(m_{jj}(jet,jet))");
  jets_maxmjj->GetYaxis()->SetTitle("Entries");
  jets_maxmjj->SetDirectory(d);
  
  jets_met_mindphi = new TH1D("jets_met_mindphi","jets_met_mindphi",32,0,TMath::Pi()); 
  jets_met_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(met,jets))");
  jets_met_mindphi->GetYaxis()->SetTitle("Entries");
  jets_met_mindphi->SetDirectory(d);
  
  jets_met_maxdphi = new TH1D("jets_met_maxdphi","jets_met_maxdphi",32,0,TMath::Pi()); 
  jets_met_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(met,jets))");
  jets_met_maxdphi->GetYaxis()->SetTitle("Entries");
  jets_met_maxdphi->SetDirectory(d);
  
  jets40_met_mindphi = new TH1D("jets40_met_mindphi","jets40_met_mindphi",32,0,TMath::Pi()); 
  jets40_met_mindphi->GetXaxis()->SetTitle("Min(#Delta#phi(met,jets40))");
  jets40_met_mindphi->GetYaxis()->SetTitle("Entries");
  jets40_met_mindphi->SetDirectory(d);
  
  jets40_met_maxdphi = new TH1D("jets40_met_maxdphi","jets40_met_maxdphi",32,0,TMath::Pi()); 
  jets40_met_maxdphi->GetXaxis()->SetTitle("Max(#Delta#phi(met,jets40))");
  jets40_met_maxdphi->GetYaxis()->SetTitle("Entries");
  jets40_met_maxdphi->SetDirectory(d);
  
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
  
  if(data.l1t_ett.first){l1t_ett->Fill(data.l1t_ett.second);}
  if(data.l1t_etm.first){l1t_etm->Fill(data.l1t_etm.second);}
  if(data.l1t_htt.first){l1t_htt->Fill(data.l1t_htt.second);}
  if(data.l1t_mht.first){l1t_mht->Fill(data.l1t_mht.second);}
  
  if(data.nJets_total  .first){nJets_total  ->Fill(data.nJets_total  .second);}
  if(data.nJets_central.first){nJets_central->Fill(data.nJets_central.second);}
  if(data.nJets_forward.first){nJets_forward->Fill(data.nJets_forward.second);}
  
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

  if(data.jets_mindeta.first)    {jets_mindeta    ->Fill(data.jets_mindeta.second);}
  if(data.jets_maxdeta.first)    {jets_maxdeta    ->Fill(data.jets_maxdeta.second);}
  if(data.jets_mindphi.first)    {jets_mindphi    ->Fill(data.jets_mindphi.second);}
  if(data.jets_maxdphi.first)    {jets_maxdphi    ->Fill(data.jets_maxdphi.second);}
  if(data.jets_minmjj.first)     {jets_minmjj     ->Fill(data.jets_minmjj.second);}
  if(data.jets_maxmjj.first)     {jets_maxmjj     ->Fill(data.jets_maxmjj.second);}
  
  if(data.jets_met_mindphi.first){jets_met_mindphi->Fill(data.jets_met_mindphi.second);}
  if(data.jets_met_maxdphi.first){jets_met_maxdphi->Fill(data.jets_met_maxdphi.second);}

  if(data.jets40_met_mindphi.first){jets40_met_mindphi->Fill(data.jets40_met_mindphi.second);}
  if(data.jets40_met_maxdphi.first){jets40_met_maxdphi->Fill(data.jets40_met_maxdphi.second);}
  
  if(data.MHToverHTT.first)       {MHToverHTT       ->Fill(data.MHToverHTT.second);}
}

L1TPlots::~L1TPlots(){
  delete l1t_ett;
  delete l1t_etm;
  delete l1t_htt;
  delete l1t_mht;
  
  delete nJets_total;
  delete nJets_central;
  delete nJets_forward;
  
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
  
  delete jets_mindeta;
  delete jets_maxdeta;
  delete jets_mindphi;
  delete jets_maxdphi;
  delete jets_minmjj;
  delete jets_maxmjj;
  
  delete jets_met_mindphi;
  delete jets_met_maxdphi;
  delete jets40_met_mindphi;
  delete jets40_met_maxdphi;
  
  delete MHToverHTT;
}
