#include "TFile.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TGaxis.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

#include "Plots/Style/interface/Style.h"
#include "FWCore/IO/interface/File.h"

#include <boost/algorithm/string.hpp>

using namespace std;

TCanvas* doCanvas(TH1D* sig,TH1D* bkg,TH1D* notETM,const char* name,const char* path){
  
  //const int nMaxBunch50ns = 1380;
  const int nMaxBunch25ns = 2808;
  const int ratePerBunch  = 11246;
  
  TCanvas *c0 = new TCanvas(Form("rates_%s",name));
  
  TPad *pad = new TPad("pad","",0,0,1,1);
  pad->SetFillColor(0);
  pad->SetGridx();
  pad->SetTicky(false);
  pad->Draw();
  pad->cd();
  
  sig->GetYaxis()->SetTitleOffset(1.5);
  sig->GetYaxis()->SetTitle("Signal Efficiency");
  sig->Draw();
  
  if(notETM){
    notETM->GetYaxis()->SetTitleOffset(1.5);
    notETM->SetTitle("Signal Efficiency");
    notETM->SetFillColor(kGreen);
    notETM->SetFillStyle(3001);
    notETM->Draw("same");
  }

  ///////////
  c0->cd();
  TPad *overlay = new TPad("overlay","",0,0,1,1);
  overlay->SetFillStyle(4000);
  overlay->SetFillColor(0);
  overlay->SetFrameFillStyle(4000);
  overlay->Draw();
  overlay->cd();
  overlay->SetLogy();
  overlay->SetGridy();
  overlay->SetTicky(false);
  
  TH1D * rate = (TH1D*) bkg->Clone(Form("rate_%s",sig->GetTitle()));
  // rate->GetYaxis()->SetRangeUser(1,1.2e7);
  rate->GetYaxis()->SetTitle("L1T Rate (Hz)");
  rate->Scale(ratePerBunch*nMaxBunch25ns);
  rate->SetLineColor(kRed);
  rate->GetYaxis()->SetAxisColor(kRed);
  rate->GetYaxis()->SetTitleColor(kRed);
  rate->GetYaxis()->SetLabelColor(kRed);
  rate->GetYaxis()->SetTitleOffset(1.5);  
  rate->Draw("Y+");
  
  //draw an axis on the right side
  //c0->SaveAs("PU40bx50_rate_DijetVBF30_L1TETM_logScale.pdf");  
  
  for(int i=0; i<=sig->GetNbinsX()+1; i++){
    if(sig->GetBinContent(i)>=0.2 && rate->GetBinContent(i)<=5000){
      cout << "==> Path:" << path
           << " Name: " << sig->GetName() 
           << " cut: " << sig->GetXaxis()->GetBinLowEdge(i) 
           << " Rate: " << rate->GetBinContent(i)
           << " Sig eff: " << sig->GetBinContent(i);
      if(notETM){cout << " Eff not(ETM70)" << notETM->GetBinContent(i);}
      cout << endl;
      break;
    }
  }
  
  if(notETM){
  
    for(int i=0; i<=sig->GetNbinsX()+1; i++){
      if(notETM->GetBinContent(i)>=0.03 && rate->GetBinContent(i)<=5000){
        cout << "==> Path:" << path
             << " Name: " << sig->GetName() 
             << " cut: " << sig->GetXaxis()->GetBinLowEdge(i) 
             << " Rate: " << rate->GetBinContent(i)
             << " Sig eff: " << sig->GetBinContent(i);
        if(notETM){cout << " Eff not(ETM70)" << notETM->GetBinContent(i);}
        cout << endl;
        break;
      }
    }
  }
  return c0;
  
}

//####################################################################
int main(){

  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  art::File *fOut = new art::File("L1AlgoWPStudiesResults_PU40bx25_eff.root","RECREATE");
  
  art::File *fSig = new art::File("L1AlgoWPStudiesResults_L1TEmuStage1_VBFInv_PU40bx25.root");
  art::File *fBkg = new art::File("L1AlgoWPStudiesResults_L1TEmuStage1_NeutrinoGun_PU40bx25.root");
  
  vector<TH1*> hSig = fSig->getHistograms();
  vector<TH1*> hBkg = fBkg->getHistograms();
  
  TH1I* hSigTotal = (TH1I*) fSig->Get("Run_1/EventCount");
  double nSigEvents = hSigTotal->GetBinContent(1);
  
  TH1I* hBkgTotal = (TH1I*) fBkg->Get("Run_1/EventCount");
  double nBkgEvents = hBkgTotal->GetBinContent(1);

  fOut->copyDirectoryStructure(fSig);
  fOut->Write();
  
  for(unsigned s=0; s<hSig.size(); s++){
    
    TH1D *pSig = (TH1D*) hSig[s];

    string sigTitle = pSig->GetName();
    string sigPath  = pSig->GetDirectory()->GetPath();
    sigPath  = sigPath.substr(sigPath.find(':')+2,sigPath.size()-1);

    for(unsigned b=0; b<hBkg.size(); b++){
      
      TH1D *pBkg = (TH1D*) hBkg[b];
      
      string bkgTitle = pBkg->GetName();
      string bkgPath  = pBkg->GetDirectory()->GetPath();
      bkgPath = bkgPath.substr(bkgPath.find(':')+2,bkgPath.size()-1);
      
      if(sigTitle == bkgTitle && sigPath == bkgPath){
        
        //cout << "Plot: " << sigPath << " name: " << pSig->GetName() << " title: " << pSig->GetTitle() << endl;
        
        TH1D *pSigEff   = (TH1D*) pSig->Clone(Form("Sig_%s_eff",pSig->GetName()));
        TH1D *pBkgEff   = (TH1D*) pBkg->Clone(Form("Bkg_%s_eff",pBkg->GetName()));
        
        TH1D *pNoETM    = 0;
        TH1D *pNoETMEff = 0;
        if(sigPath.find("SameDijet")!=std::string::npos){
          
          string nameSameDijet = Form("%s/%s",sigPath.c_str(),sigTitle.c_str());
          
          boost::replace_all(nameSameDijet,"SameDijet","SameDijetNotETM70");
          pNoETM = (TH1D*) fSig->Get(nameSameDijet.c_str());
          
          if(pNoETM){
            pNoETMEff = (TH1D*) pNoETM->Clone(Form("ETM_%s_eff",pBkg->GetName()));
          }
        }
        
        bool reverseIntegral = false;
        
        // Plots that cut will be 'less than' so integral must be reversed
        if(string(pSig->GetName()).find("dijet_dphi")   != std::string::npos){reverseIntegral=true;}
        if(string(pSig->GetName()).find("jets_mindphi") != std::string::npos){reverseIntegral=true;}
        if(string(pSig->GetName()).find("jets_maxdphi") != std::string::npos){reverseIntegral=true;}
        
        if(reverseIntegral){
          for(int i=0; i<=pSigEff->GetNbinsX()+1; i++){pSigEff->SetBinContent(i,pSig->Integral(0,i));}
          for(int i=0; i<=pBkgEff->GetNbinsX()+1; i++){pBkgEff->SetBinContent(i,pSig->Integral(0,i));}
          
          if(pNoETMEff){
            for(int i=0; i<=pNoETMEff->GetNbinsX()+1; i++){pNoETMEff->SetBinContent(i,pNoETM->Integral(0,i));}
          }
        }else{
          for(int i=0; i<=pSigEff->GetNbinsX()+1; i++){pSigEff->SetBinContent(i,pSigEff->Integral(i,pSigEff->GetNbinsX()+1));}
          for(int i=0; i<=pBkgEff->GetNbinsX()+1; i++){pBkgEff->SetBinContent(i,pBkgEff->Integral(i,pBkgEff->GetNbinsX()+1));}
          
          if(pNoETMEff){
            for(int i=0; i<=pNoETMEff->GetNbinsX()+1; i++){pNoETMEff->SetBinContent(i,pNoETM->Integral(i,pSigEff->GetNbinsX()+1));}
          }
        }
        pSigEff  ->Scale(1/nSigEvents);
        pBkgEff  ->Scale(1/nBkgEvents);
        if(pNoETMEff){pNoETMEff->Scale(1/nSigEvents);}
        
        TCanvas* c = doCanvas(pSigEff,pBkgEff,pNoETMEff,pSig->GetName(),sigPath.c_str());
        
        TDirectoryFile *d = (TDirectoryFile*) fOut->Get(sigPath.c_str());
        d->WriteTObject(c);
        
        delete pSigEff;
        delete pBkgEff;
        delete pNoETMEff;
        delete c;
        
        break;
      }
    }  
    
  }
  
  

  
  //string subPath = iDir->substr(iDir->find(':')+1,iDir->size()-1);
  
  cout << "L1AlgoWPStudiesResults_VBFInv_PU40bx25.root      has " << hSig.size() << " histograms!" << endl;
  cout << "L1AlgoWPStudiesResults_NeutrinoGun_PU40bx25.root has " << hBkg.size() << " histograms!" << endl;
  
  fOut->Write();
  
//   TFile *fSig = new TFile("L1AlgoWPStudiesResults_VBFInv_PU40bx25.root");
                           
    
//   TH1I* hSigTotal = (TH1I*) fSig->Get("Run_1/EventCount");
//   TH1I* hBkgTotal = (TH1I*) fBkg->Get("Run_1/EventCount");

//   double nSigEvents = hSigTotal->GetBinContent(1);
//   double nBkgEvents = hSigTotal->GetBinContent(1);
  
  //___________________________________________________________

  /*
  //___________________________________________________________  
  TH1D *DijetVBF30_DEta      = (TH1D*) f->Get("Run_1/DijetVBF30/dijet_deta");
  TH1D *eff_DijetVBF30_DEta  = (TH1D*) DijetVBF30_DEta ->Clone("eff_DijetVBF30_DEta"); 
  for(int i=0; i<=eff_DijetVBF30_DEta->GetNbinsX()+1; i++){
    eff_DijetVBF30_DEta->SetBinContent(i,eff_DijetVBF30_DEta->Integral(i,eff_DijetVBF30_DEta->GetNbinsX()+1));
  }
  eff_DijetVBF30_DEta->Scale(1/nEvents);
  eff_DijetVBF30_DEta->SetDirectory(fOut);
  TH1D *rate_DijetVBF30_DEta = (TH1D*) eff_DijetVBF30_DEta ->Clone("rate_DijetVBF30_DEta");
  rate_DijetVBF30_DEta->GetYaxis()->SetTitle("L1T Rate (Hz)");
  rate_DijetVBF30_DEta->Scale(ratePerBunch*nMaxBunch25ns);
  rate_DijetVBF30_DEta->SetDirectory(fOut);
  
  TCanvas c1;
  rate_DijetVBF30_DEta->GetYaxis()->SetRangeUser(0,1.2e7);
  rate_DijetVBF30_DEta->GetYaxis()->SetTitleOffset(1.5);
  rate_DijetVBF30_DEta->GetYaxis()->SetLabelSize(0.02);
  rate_DijetVBF30_DEta->Draw();
  TLine line1 (3.0,0,3.0,1.2e7);
  line1.SetLineColor(kRed);
  line1.Draw();
  c1.SaveAs("PU40bx50_rate_DijetVBF30_DEta.pdf");
  rate_DijetVBF30_DEta->GetYaxis()->SetRangeUser(1,1.2e7);
  c1.SetLogy(true);
  c1.SaveAs("PU40bx50_rate_DijetVBF30_DEta_logScale.pdf");
  
  //___________________________________________________________
  TH1D *DijetVBF30_DEta3p0_L1TETM = (TH1D*) f->Get("Run_1/DijetVBF30_DEta3p0/L1T_ETM");
  TH1D *eff_DijetVBF30_DEta3p0_L1TETM  = (TH1D*) DijetVBF30_DEta3p0_L1TETM ->Clone("eff_DijetVBF30_DEta3p0_L1TETM"); 
  for(int i=0; i<=eff_DijetVBF30_DEta3p0_L1TETM->GetNbinsX()+1; i++){
    eff_DijetVBF30_DEta3p0_L1TETM->SetBinContent(i,eff_DijetVBF30_DEta3p0_L1TETM->Integral(i,eff_DijetVBF30_DEta3p0_L1TETM->GetNbinsX()+1));
  }
  eff_DijetVBF30_DEta3p0_L1TETM->Scale(1/nEvents);
  eff_DijetVBF30_DEta3p0_L1TETM->SetDirectory(fOut);
  TH1D *rate_DijetVBF30_DEta3p0_L1TETM = (TH1D*) eff_DijetVBF30_DEta3p0_L1TETM ->Clone("rate_DijetVBF30_DEta3p0_L1TETM"); 
  rate_DijetVBF30_DEta3p0_L1TETM->GetYaxis()->SetTitle("L1T Rate (Hz)");
  rate_DijetVBF30_DEta3p0_L1TETM->Scale(ratePerBunch*nMaxBunch25ns);
  rate_DijetVBF30_DEta3p0_L1TETM->SetDirectory(fOut);

  TCanvas c2;
  rate_DijetVBF30_DEta3p0_L1TETM->GetXaxis()->SetRangeUser(0,100);
  rate_DijetVBF30_DEta3p0_L1TETM->GetYaxis()->SetRangeUser(0,1.2e7);
  rate_DijetVBF30_DEta3p0_L1TETM->GetYaxis()->SetTitleOffset(1.5);
  rate_DijetVBF30_DEta3p0_L1TETM->GetYaxis()->SetLabelSize(0.02);
  rate_DijetVBF30_DEta3p0_L1TETM->Draw();
  TLine line2 (30,0,30,1.2e7);
  line2.SetLineColor(kRed);
  line2.Draw();
  c2.SaveAs("PU40bx50_rate_DijetVBF30_DEta3p0_L1TETM.pdf");
  rate_DijetVBF30_DEta3p0_L1TETM->GetYaxis()->SetRangeUser(1,1.2e7);
  c2.SetLogy(true);
  c2.SaveAs("PU40bx50_rate_DijetVBF30_DEta3p0_L1TETM_logScale.pdf");*/
  
  
  /*
    //
    // Example showing how to superimpose a TGraph with a different range
    // using a transparent pad.
    //
    c1 = new TCanvas("c1","gerrors2",200,10,700,500);
    TPad *pad = new TPad("pad","",0,0,1,1);
    pad->SetFillColor(42);
    pad->SetGrid();
    pad->Draw();
    pad->cd();
    
    // draw a frame to define the range
    TH1F *hr = pad->DrawFrame(-0.4,0,1.2,12);
    hr->SetXTitle("X title");
    hr->SetYTitle("Y title");
    pad->GetFrame()->SetFillColor(21);
    pad->GetFrame()->SetBorderSize(12);
    
    // create first graph
    Int_t n1 = 10;
    Double_t x1[]  = {-0.22, 0.05, 0.25, 0.35, 0.5, 0.61,0.7,0.85,0.89,0.95};
    Double_t y1[]  = {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
    Double_t ex1[] = {.05,.1,.07,.07,.04,.05,.06,.07,.08,.05};
    Double_t ey1[] = {.8,.7,.6,.5,.4,.4,.5,.6,.7,.8};
    gr1 = new TGraphErrors(n1,x1,y1,ex1,ey1);
    gr1->SetMarkerColor(kBlue);
    gr1->SetMarkerStyle(21);
    gr1->Draw("LP");
    
    // create second graph
    Int_t n2 = 10;
    Float_t x2[]  = {-0.28, 0.005, 0.19, 0.29, 0.45, 0.56,0.65,0.80,0.90,1.01};
    Float_t y2[]  = {0.82,3.86,7,9,10,10.55,9.64,7.26,5.42,2};
    Float_t ex2[] = {.04,.12,.08,.06,.05,.04,.07,.06,.08,.04};
    Float_t ey2[] = {.6,.8,.7,.4,.3,.3,.4,.5,.6,.7};
    for (Int_t i=0;i<n2;i++) {
      y2[i] *= 100;
      ey2[i] *= 100;
    }
    //create a transparent pad drawn on top of the main pad
    c1->cd();
    TPad *overlay = new TPad("overlay","",0,0,1,1);
    overlay->SetFillStyle(4000);
    overlay->SetFillColor(0);
    overlay->SetFrameFillStyle(4000);
    overlay->Draw();
    overlay->cd();
    gr2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
    gr2->SetMarkerColor(kRed);
    gr2->SetMarkerStyle(20);
    gr2->SetName("gr2");
    Double_t xmin = pad->GetUxmin();
    Double_t ymin = 0;
    Double_t xmax = pad->GetUxmax();
    Double_t ymax = 1200;
    TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);
    hframe->GetXaxis()->SetLabelOffset(99);
    hframe->GetYaxis()->SetLabelOffset(99);
    gr2->Draw("LP");
    
    
    //Draw an axis on the right side
    TGaxis *axis = new TGaxis(xmax,ymin,xmax, ymax,ymin,ymax,510,"+L");
    axis->SetLineColor(kRed);
    axis->SetLabelColor(kRed);
    axis->Draw();
  */
  

  
  return 0;  
  
};