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
    
//     drawPlot(file,outputDir);
  }
  
  return 0;
}