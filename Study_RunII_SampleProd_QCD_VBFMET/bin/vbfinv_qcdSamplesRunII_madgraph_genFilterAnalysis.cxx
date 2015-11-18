// My includes
#include "CMSSW_VBFHToInv/Plots/interface/Style.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"

// C++ STD includes
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

void drawTDir(TFile* f,string outDir,string dir){
  
  //################################################################
  //## Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj1000
  //################################################################
  // h1D->Rebin(5);
  // h1D->GetXaxis()->SetRangeUser(0.0,250.0);
  
  map<string,TH1D*>     hist1D;
  
  TCanvas  c;
  string   name = "";
  TH1D    *h1D  = 0;

  cout << "#######################################################" << endl;
  cout << "Printing cuts: " << dir << endl;
  cout << endl;
  
  name = dir+"/Jets_Multiplicity";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetRangeUser(-0.5,10.5);
  h1D->GetXaxis()->SetTitle("Generator Jet Multiplicity");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  cout << endl;
  cout << "=> Jets Passing cuts multiplicity:" << endl;
  for(int i=1; i<=11; i++){
    double value    = h1D->GetBinContent(i);
    double fraction = value/double(h1D->GetEntries());
    double error    = TMath::Sqrt(value)/double(h1D->GetEntries());
    printf("N_Jets=%2d entries=%10d fraction=%8.6f +/- %8.6f\n",(int) h1D->GetBinCenter(i),(int) value,fraction,error);
  }
  cout << endl;
  
  name = dir+"/Jet0_maxPt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetTitle("Leading Generator Jet p_{T} [GeV]");
  h1D->GetXaxis()->SetRangeUser(0.0,300.0);
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/Jet1_maxPt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetRangeUser(0.0,300.0);
  h1D->GetXaxis()->SetTitle("Subleading Generator Jet p_{T} [GeV]");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/Dijet_minEtaProduct";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetTitle("Min(Dijet #eta product)");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/Dijet_MaxMjj";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(5);
  h1D->GetXaxis()->SetRangeUser(0.0,3500.0);
  h1D->GetXaxis()->SetTitle("Dijet Max(m_{jj}) [GeV]");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/Dijet_MaxDEta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(4);
  h1D->GetXaxis()->SetTitle("Dijet Min(#Delta#eta)");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/Dijet_MultiplicityPass";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->GetXaxis()->SetRangeUser(-0.5,10.5);
  h1D->GetXaxis()->SetTitle("Dijet Passing All Cuts Multiplicity");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  cout << endl;
  cout << "=> Dijets passing all cuts multiplicity:" << endl;
  for(int i=1; i<=11; i++){
    double value    = h1D->GetBinContent(i);
    double fraction = value/double(h1D->GetEntries());
    double error    = TMath::Sqrt(value)/double(h1D->GetEntries());
    printf("N_Dijets=%2d entries=%10d fraction=%8.6f +/- %8.6f\n",(int) h1D->GetBinCenter(i),(int) value,fraction,error);
  }
  cout << endl;
  
  name = dir+"/LeadDijet_Jet0_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetRangeUser(0.0,300.0);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet - Leading Jet p_{T} [GeV]");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_Jet1_Pt";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetRangeUser(0.0,300.0);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet - Subleading Jet p_{T} [GeV]");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_Jet0_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet - Leading Jet #eta");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_Jet1_Eta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet - Subleading Jet #eta");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_Mjj";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(5);
  h1D->GetXaxis()->SetRangeUser(0.0,3500.0);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet m_{jj}");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_DEta";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(4);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet #Delta#eta");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
  name = dir+"/LeadDijet_DPhi";
  h1D  = (TH1D*) f->Get(name.c_str());
  hist1D[name] = h1D;
  h1D->Rebin(2);
  h1D->GetXaxis()->SetTitle("Lead Generator Dijet #Delta#phi");
  h1D->GetYaxis()->SetTitle("Events");
  h1D->GetYaxis()->SetTitleOffset(1.75);
  
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
}

void drawPlot(TFile* f,string outDir){
  
  TH1D* hEventCount = (TH1D*) f->Get("EventCount");
  double evTotal = hEventCount->GetBinContent(1);
  cout << "Total number of events: " << evTotal << endl;
  cout << endl;
  
  
  cout << "=> Event counters:" << endl;
  for(int i=2; i<=hEventCount->GetNbinsX(); i++){
    double value = hEventCount->GetBinContent(i);
    cout << hEventCount->GetXaxis()->GetBinLabel(i) << " : " << value << endl;
  }
  cout << endl;
  
  // Parton pT
//   name = "plots/Jets_Multiplicity";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Generator Jet Multiplicity");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
//   
//   name = "plots/Jet0_Pt";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Leading Generator Jet p_{T} [GeV]");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
//   
//   name = "plots/Jet1_Pt";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Subleading Generator Jet p_{T} [GeV]");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
//   
//   name = "plots/Dijet_MaxMjj";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Dijet Max(m_{jj}) [GeV]");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
//   
//   name = "plots/Dijet_MaxDEta";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Dijet Min(#Delta#eta)");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
//   
//   name = "plots/Dijet_MinDPhi";
//   h1D  = (TH1D*) f->Get(name.c_str());
//   hist1D[name] = h1D;
//   h1D->GetXaxis()->SetTitle("Dijet Min(#Delta#phi)");
//   h1D->GetYaxis()->SetTitle("Events");
//   h1D->GetYaxis()->SetTitleOffset(1.75);
  
  drawTDir(f,outDir,"Pt40_Eta4p8_DEta3p0_Mjj1000");
  drawTDir(f,outDir,"Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj1000");
  drawTDir(f,outDir,"Pt40_Eta4p8_DEta3p0_MinDphi2p15_Mjj1000");

}

bool checkFiles(string files){

  bool out = true;
  
  ifstream my_file(files);
  if (!my_file.good()){
    cout << "File '" << files << "' does not exist!" << endl;
    out = false;
  }
  my_file.close();

  return out;
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
  
  if(!checkFiles(inputFile)){
    cout << "FATAL ERROR: files missing!" << endl;
    return 1;
  }
  
  
  map<string,TFile*> files;
  TFile* file = new TFile(inputFile.c_str(),"READ");
  drawPlot(file,outputDir);
  
  return 0;
}