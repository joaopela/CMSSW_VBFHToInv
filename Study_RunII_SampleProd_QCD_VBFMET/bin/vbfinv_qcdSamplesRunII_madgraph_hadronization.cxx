
// My includes
#include "CMSSW_VBFHToInv/Plots/interface/Style.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TCanvas.h"

// C++ STD includes
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

void drawPlot(string filename,TFile* f){
  
  TH1D* hEventCount = (TH1D*) f->Get("EventCount");
  double evTotal = hEventCount->GetBinContent(1);
  cout << "Total number of events: " << evTotal << endl;
  
  TH1D* hMatchingResults = (TH1D*) f->Get("MatchingResults");
  hMatchingResults->Draw();
  cout << hMatchingResults->GetXaxis()->GetBinLabel(1) << " : " << hMatchingResults->GetBinContent(1) << endl;
  cout << hMatchingResults->GetXaxis()->GetBinLabel(2) << " : " << hMatchingResults->GetBinContent(2) << endl;
  cout << hMatchingResults->GetXaxis()->GetBinLabel(3) << " : " << hMatchingResults->GetBinContent(3) << endl;
  cout << hMatchingResults->GetXaxis()->GetBinLabel(4) << " : " << hMatchingResults->GetBinContent(4) << endl;  
  
  TCanvas c;
  
  string name = "PartonvsGenJet_DiffPt";
  TH1D* hPartonvsGenJet_DiffPt  = (TH1D*) f->Get(name.c_str());
  hPartonvsGenJet_DiffPt->GetXaxis()->SetTitle("Parton - Matched Generator Jet p_{#perp}");
  hPartonvsGenJet_DiffPt->GetYaxis()->SetTitle("Number of events");
  hPartonvsGenJet_DiffPt->GetYaxis()->SetTitleOffset(1.75);
  hPartonvsGenJet_DiffPt->Draw();
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));

  name = "PartonvsGenJet_DiffEta";
  TH1D* hPartonvsGenJet_DiffEta = (TH1D*) f->Get(name.c_str());
  hPartonvsGenJet_DiffEta->GetXaxis()->SetTitle("Parton - Matched Generator Jet #eta");
  hPartonvsGenJet_DiffEta->GetYaxis()->SetTitle("Number of events");
  hPartonvsGenJet_DiffEta->GetYaxis()->SetTitleOffset(1.75);
  hPartonvsGenJet_DiffEta->Draw();
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));
  
  name = "Profile_PartonvsGenJet_DiffPt";
  TProfile* hProfile_PartonvsGenJet_DiffPt  = (TProfile*) f->Get(name.c_str());
  hProfile_PartonvsGenJet_DiffPt->Rebin(10);
  hProfile_PartonvsGenJet_DiffPt->GetXaxis()->SetTitle("Parton p_{#perp}");
  hProfile_PartonvsGenJet_DiffPt->GetYaxis()->SetTitle("abs(Parton - Matched Generator Jet pT)");
  hProfile_PartonvsGenJet_DiffPt->GetYaxis()->SetTitleOffset(1.75);
  hProfile_PartonvsGenJet_DiffPt->Draw();
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));
  
  name = "Profile_PartonvsGenJet_DiffEta";
  TProfile* hProfile_PartonvsGenJet_DiffEta = (TProfile*) f->Get(name.c_str());
  hProfile_PartonvsGenJet_DiffEta->Rebin(2);
  hProfile_PartonvsGenJet_DiffEta->GetXaxis()->SetTitle("Parton #eta");
  hProfile_PartonvsGenJet_DiffEta->GetYaxis()->SetTitle("abs(Parton - Matched Generator Jet #eta)");
  hProfile_PartonvsGenJet_DiffEta->GetYaxis()->SetTitleOffset(1.75);
  hProfile_PartonvsGenJet_DiffEta->Draw();
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));
  
  name = "PartonvsGenJet_Pt";
  TH2D* hPartonvsGenJet_Pt  = (TH2D*) f->Get(name.c_str());
  hPartonvsGenJet_Pt->GetXaxis()->SetTitle("Parton p_{#perp}");
  hPartonvsGenJet_Pt->GetYaxis()->SetTitle("Matched Generator Jet p_{#perp}");
  hPartonvsGenJet_Pt->GetYaxis()->SetTitleOffset(1.75);
  hPartonvsGenJet_Pt->Draw("colz");
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));

  name = "PartonvsGenJet_Eta";
  TH2D* hPartonvsGenJet_Eta = (TH2D*) f->Get(name.c_str());
  hPartonvsGenJet_Eta->GetXaxis()->SetTitle("Parton #eta");
  hPartonvsGenJet_Eta->GetYaxis()->SetTitle("Matched Generator Jet #eta");
  hPartonvsGenJet_Eta->Draw("colz");
  c.SaveAs(Form("%s.C",  name.c_str()));
  c.SaveAs(Form("%s.jpg",name.c_str()));
  c.SaveAs(Form("%s.pdf",name.c_str()));
  
//   TLegend l(0.55,0.75,0.85,0.95);
//   l.SetHeader("QCD p_{T} Hat");
//   l.SetFillColor(kWhite);
//   
//   for(unsigned i=0; i<order.size(); i++){
//     
//     string index = order[i];
//     TH1D* h      = hist [index];
//     
//     h->SetLineColor(color[index]);
//     
//     double fullIntegral = h->Integral(0,h->GetNbinsX()+1);
//     h->Scale(1/fullIntegral);
//     h->GetYaxis()->SetTitle("Scaled to 1");
//     
//     if(i==0){h->Draw();}
//     else    {h->Draw("same");}
//     
//     l.AddEntry(h,index.c_str(),"l");
//   }
//   
//   l.Draw();
//   
}

bool checkFiles(map<string,string> files){
  
  bool out = true;
  
  for(auto i=files.begin(); i!=files.end(); i++){
    
    ifstream my_file(i->second.c_str());
    if (!my_file.good()){
      cout << "File '" << i->second.c_str() << "' does not exist!" << endl;
      out = false;
    }
    my_file.close();
  }
  
  return out;
}

int main(){
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  // Defining all alias for the input filenames
  map<string,string> fileNames;
  fileNames["30to50"]   = "PartonGenJetAnalyzerResults_pp_jj_etaj4p8_ptj1min40_ptj2min40_mmjj800_ev1000k.root";
  
  if(!checkFiles(fileNames)){
    cout << "FATAL ERROR: One or more files missing!" << endl;
    return 1;
  }
  
  map<string,TFile*> files;
  for(auto i=fileNames.begin(); i!=fileNames.end(); i++){
    files[i->first] = new TFile(i->second.c_str(),"READ");
    
    drawPlot(i->first,files[i->first]);
  }
  
  return 0;
}
