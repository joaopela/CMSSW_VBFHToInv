
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

void drawPlot(TFile* f,string outDir){
  
  TH1D* hEventCount = (TH1D*) f->Get("EventCount");
  double evTotal = hEventCount->GetBinContent(1);
  cout << "Total number of events: " << evTotal << endl;
  cout << endl;
  
  cout << "=> Event counters:" << endl;
  TH1D* hCounters = (TH1D*) f->Get("Counters");
  for(int i=1; i<=hCounters->GetNbinsX(); i++){
    double value = hCounters->GetBinContent(i);
    cout << hCounters->GetXaxis()->GetBinLabel(i) << " : " << value << endl;
  }
  cout << endl;
  
  cout << "=> Parton to GenJet matching results:" << endl;
  TH1D* hParton_NMatched = (TH1D*) f->Get("Parton_NMatched");
  for(int i=1; i<=hParton_NMatched->GetNbinsX(); i++){
    double value = hParton_NMatched->GetBinContent(i);
    if(value>0){
      cout << "Matched #" << i << " partons: " << value << " fraction: " << value/evTotal << endl;
    }
  }
  cout << endl;
  
  map<string,TH1D*>     hist1D;
  map<string,TH2D*>     hist2D;
  map<string,TProfile*> histPr;
  
  TCanvas c;
  string    name = "";
  TH1D     *h1D  = 0;
  TH2D     *h2D  = 0;
  TProfile *hPr  = 0;
  
  // Parton pT
  name = "Parton_Jet1_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #1 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet2_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #2 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet3_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #3 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet4_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #4 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  // Parton eta
  name = "Parton_Jet1_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #1 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet2_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #2 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet3_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #3 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Parton_Jet4_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton #4 - p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "PartonvsGenJet_DiffPt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton - Matched Generator Jet p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);

  name = "PartonvsGenJet_DiffEta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Parton - Matched Generator Jet #eta");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_Parton1_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(5);
  h1D->GetXaxis()->SetRangeUser(0.0,250.0);
  h1D->GetXaxis()->SetTitle("Selected Diparton - Lead parton p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_Parton2_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(5);
  h1D->GetXaxis()->SetRangeUser(0.0,250.0);
  h1D->GetXaxis()->SetTitle("Selected Diparton - Sublead parton p_{#perp}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_Parton1_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Selected Diparton - Lead parton #eta");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_Parton2_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Selected Diparton - Sublead parton #eta");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_DEta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetTitle("Selected Diparton - #Delta#eta");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_Mjj";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(5);
  h1D->GetXaxis()->SetRangeUser(0.0,3000.0);
  h1D->GetXaxis()->SetTitle("Selected Diparton - m_{jj}");
  h1D->GetYaxis()->SetTitle("Number of events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  //###############################################################
  // TProfile
  //###############################################################
  name = "Profile_PartonvsGenJet_DiffPt";
  hPr  = (TProfile*) f->Get(name.c_str());
  histPr[name] = hPr;
  hPr->Rebin(10);
  hPr->GetXaxis()->SetTitle("Parton p_{#perp}");
  hPr->GetYaxis()->SetTitle("abs(Parton - Matched Generator Jet pT)");
  hPr->GetYaxis()->SetTitleOffset(1.75);
  
  name = "Profile_PartonvsGenJet_DiffEta";
  hPr  = (TProfile*) f->Get(name.c_str());
  histPr[name] = hPr;
  hPr->Rebin(2);
  hPr->GetXaxis()->SetTitle("Parton #eta");
  hPr->GetYaxis()->SetTitle("abs(Parton - Matched Generator Jet #eta)");
  hPr->GetYaxis()->SetTitleOffset(1.75);
  
  //###############################################################
  // 2D Plots
  //###############################################################
  name = "PartonvsGenJet_Pt";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->GetXaxis()->SetTitle("Parton p_{#perp}");
  h2D->GetYaxis()->SetTitle("Matched Generator Jet p_{#perp}");
  h2D->GetYaxis()->SetTitleOffset(1.75);

  name = "PartonvsGenJet_Eta";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->GetXaxis()->SetTitle("Parton #eta");
  h2D->GetYaxis()->SetTitle("Matched Generator Jet #eta");
  
  // Selected Diparton - Generator jet match
  name = "SelDiParton_MatchedGenJet_Parton1_Pt";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->Rebin2D(2,2);
  h2D->GetXaxis()->SetRangeUser(0.0,250.0);
  h2D->GetYaxis()->SetRangeUser(0.0,250.0);
  h2D->GetXaxis()->SetTitle("Diparton Lead Parton p_{#perp}");
  h2D->GetYaxis()->SetTitle("Matched generator jet p_{#perp}");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_MatchedGenJet_Parton2_Pt";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->Rebin2D(2,2);
  h2D->GetXaxis()->SetRangeUser(0.0,250.0);
  h2D->GetYaxis()->SetRangeUser(0.0,250.0);
  h2D->GetXaxis()->SetTitle("Diparton sublead parton p_{#perp}");
  h2D->GetYaxis()->SetTitle("Matched generator jet p_{#perp}");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_MatchedGenJet_Parton1_Eta";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->GetXaxis()->SetTitle("Diparton Lead Parton #eta");
  h2D->GetYaxis()->SetTitle("Matched generator jet #eta");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_MatchedGenJet_Parton2_Eta";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->GetXaxis()->SetTitle("Diparton sublead parton #eta");
  h2D->GetYaxis()->SetTitle("Matched generator jet #eta");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_MatchedGenJet_DEta";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->Rebin2D(2,2);
  h2D->GetXaxis()->SetTitle("Diparton #Delta#eta");
  h2D->GetYaxis()->SetTitle("Matched generator dijet #Delta#eta");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  name = "SelDiParton_MatchedGenJet_Mjj";
  h2D  = (TH2D*) f->Get(name.c_str());
  hist2D[name] = h2D;
  h2D->Rebin2D(5,5);
  h2D->GetXaxis()->SetRangeUser(0.0,3000.0);
  h2D->GetYaxis()->SetRangeUser(0.0,3000.0);
  h2D->GetXaxis()->SetTitle("Diparton m_{jj}");
  h2D->GetYaxis()->SetTitle("Matched generator dijet m_{jj}");
  h2D->GetYaxis()->SetTitleOffset(1.75);
  
  //###############################################################
  // Output of the plots
  //###############################################################
  for(auto i=hist1D.begin(); i!=hist1D.end(); i++){
    TCanvas c;
    i->second->Draw();
    c.SaveAs(Form("%s/%s.C",  outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.png",outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.pdf",outDir.c_str(),i->first.c_str()));
  }
  
  for(auto i=histPr.begin(); i!=histPr.end(); i++){
    TCanvas c;
    i->second->Draw("colz");
    c.SaveAs(Form("%s/%s.C",  outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.png",outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.pdf",outDir.c_str(),i->first.c_str()));
  }
  
  for(auto i=hist2D.begin(); i!=hist2D.end(); i++){
    TCanvas c;
    i->second->Draw("colz");
    c.SaveAs(Form("%s/%s.C",  outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.png",outDir.c_str(),i->first.c_str()));
    c.SaveAs(Form("%s/%s.pdf",outDir.c_str(),i->first.c_str()));
  }
  
  
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

int main(int argc, char* argv[]){
 
  // Check the number of parameters
  if (argc < 2) {
    // Tell the user how to run the program
    std::cerr << "Usage: " << argv[0] << " file" << std::endl;
    std::cerr << "Usage: -i INPUTFILE" << std::endl;
    std::cerr << "Usage: -d OUTPUTDIR" << std::endl;
    return 1;
  }
  
  std::string inputFile = "";
  std::string outputDir = "";
  
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if((arg == "-h") || (arg == "--help")) {
      std::cerr << "Usage: " << argv[0] << " file" << std::endl;
      return 0;
    }else if(arg == "-i"){
      if(i + 1 < argc){
        i++;
        inputFile = argv[i];
      } 
    }else if(arg == "-d"){
      if(i + 1 < argc){
        i++;
        outputDir = argv[i];
      } 
    } 
  }
  
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  // Defining all alias for the input filenames
  map<string,string> fileNames;
  fileNames["30to50"]   = inputFile;
  
  if(!checkFiles(fileNames)){
    cout << "FATAL ERROR: One or more files missing!" << endl;
    return 1;
  }
  
  map<string,TFile*> files;
  for(auto i=fileNames.begin(); i!=fileNames.end(); i++){
    TFile* file = new TFile(inputFile.c_str(),"READ");
    
    drawPlot(file,outputDir);
  }
  
  return 0;
}
