
// My includes
#include "CMSSW_VBFHToInv/Plots/interface/Style.h"

// ROOT includes
#include "TFile.h"
#include "TH1D.h"
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
  }
  
  
  
  return 0;
}
