#include <iostream>

// HEPFWCommon includes
#include "HEPFWCommon/LatexTables/interface/LatexTabular.h"

// My includes
#include "CMSSW_VBFHToInv/Plots/interface/Style.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

// C++ STD includes
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

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

void getStats(map<string,TFile*> files, string name){

  TH1D *h        = (TH1D*) files.begin()->second->Get("HLTPathCount");
  int   nPaths   = h->GetNbinsX();
  int   nSamples = files.size();
  
  hepfw::LatexTabular tab(nSamples+1,nPaths+2);
  tab.setCellContent(0,0,"HLT Paths");
  tab.setCellContent(0,1,"Total");
  
  for(int i=1;i<nPaths+1;i++){
    tab.setCellContent(0,i+1,h->GetXaxis()->GetBinLabel(i));
  }
  
  int row=1;
  for(auto i=files.begin(); i!=files.end(); i++){

    
    h       = (TH1D*) i->second->Get("HLTPathCount");
    TH1D *c = (TH1D*) i->second->Get("EventCount");

    tab.setCellContent(row,0,i->first.c_str());
    
    double ProcessedEvents = c->GetBinContent(1);
    tab.setCellContent(row,1,int(ProcessedEvents));
    
    for(int i=1;i<nPaths+1;i++){
      
      tab.setCellContent(row,i+1,int(h->GetBinContent(i)));
    }

    row++;
  }
  
  tab.saveAs(name);
}

int main(){
  
  hepfw::Style myStyle;
  myStyle.setTDRStyle();
  
  map<string,string> HLTSimpleAnalyser_PU20bx25_HCALMethod0;
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["VBF_HToInv_M-125"]  = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_VBF_HToInv_M-125.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-30to50"]     = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-30to50.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-50to80"]     = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-50to80.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-80to120"]    = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-80to120.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-120to170"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-120to170.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-170to300"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-170to300.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-300to470"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-300to470.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-470to600"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-470to600.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-600to800"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-600to800.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-800to1000"]  = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-800to1000.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-1000to1400"] = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1000to1400.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-1400to1800"] = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1400to1800.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod0["QCD_Pt-1800"]       = "HLTSimpleAnalyser_PU20bx25_HCALMethod0_QCD_Pt-1800.root";
  
  if(!checkFiles(HLTSimpleAnalyser_PU20bx25_HCALMethod0)){cout << "FATAL ERROR: One or more files missing!" << endl;
    return 1;
  }
  
  map<string,TFile*> filesHLTSimpleAnalyser_PU20bx25_HCALMethod0;
  for(auto i=HLTSimpleAnalyser_PU20bx25_HCALMethod0.begin(); i!=HLTSimpleAnalyser_PU20bx25_HCALMethod0.end(); i++){
    filesHLTSimpleAnalyser_PU20bx25_HCALMethod0[i->first] = new TFile(i->second.c_str(),"READ");
  }
  
  getStats(filesHLTSimpleAnalyser_PU20bx25_HCALMethod0,"HLTSimpleAnalyser_PU20bx25_HCALMethod0.tex");
  
  
  map<string,string> HLTSimpleAnalyser_PU20bx25_HCALMethod3;
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["VBF_HToInv_M-125"]  = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_VBF_HToInv_M-125.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-30to50"]     = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-30to50.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-50to80"]     = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-50to80.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-80to120"]    = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-80to120.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-120to170"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-120to170.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-170to300"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-170to300.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-300to470"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-300to470.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-470to600"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-470to600.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-600to800"]   = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-600to800.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-800to1000"]  = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-800to1000.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-1000to1400"] = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1000to1400.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-1400to1800"] = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1400to1800.root";
  HLTSimpleAnalyser_PU20bx25_HCALMethod3["QCD_Pt-1800"]       = "HLTSimpleAnalyser_PU20bx25_HCALMethod3_QCD_Pt-1800.root";
  
  if(!checkFiles(HLTSimpleAnalyser_PU20bx25_HCALMethod3)){
    cout << "FATAL ERROR: One or more files missing!" << endl;
    return 1;
  }
  
  map<string,TFile*> filesHLTSimpleAnalyser_PU20bx25_HCALMethod3;
  for(auto i=HLTSimpleAnalyser_PU20bx25_HCALMethod3.begin(); i!=HLTSimpleAnalyser_PU20bx25_HCALMethod3.end(); i++){
    filesHLTSimpleAnalyser_PU20bx25_HCALMethod3[i->first] = new TFile(i->second.c_str(),"READ");
  }
  
  getStats(filesHLTSimpleAnalyser_PU20bx25_HCALMethod3,"HLTSimpleAnalyser_PU20bx25_HCALMethod3.tex");
  
  return 0;
}
