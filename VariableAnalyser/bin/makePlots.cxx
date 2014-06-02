// Standard libraries includes

#include <iostream>
#include <string>

#include <vector>
#include <map>
#include <utility>

#include "TFile.h"
#include "TH1D.h"

using namespace std;

int main(int argc, char *argv[]){
    
  double lumi = 19000;
  
  map<string,double> xsec;
  xsec["QCD-Pt-30to50"]     = 66285328;
  xsec["QCD-Pt-50to80"]     =  8148778.0;
  xsec["QCD-Pt-80to120"]    =  1033680.0;
  xsec["QCD-Pt-120to170"]   =   156293.3;
  xsec["QCD-Pt-170to300"]   =    34138.15;
  xsec["QCD-Pt-300to470"]   =     1759.549;
  xsec["QCD-Pt-470to600"]   =      113.8791;
  xsec["QCD-Pt-600to800"]   =       26.9921;
  xsec["QCD-Pt-800to1000"]  =        3.550036;
  xsec["QCD-Pt-1000to1400"] =        0.737844;
  xsec["QCD-Pt-1400to1800"] =        0.03352235;
  xsec["QCD-Pt-1800"]       =        0.001829005;
  
  map<string,double> evQCDVBF;  
  evQCDVBF["QCD-Pt-80to120"]  = 39376000000;
  evQCDVBF["QCD-Pt-120to170"] = 7000000000;
  evQCDVBF["QCD-Pt-170to300"] = 1375000000;
  evQCDVBF["QCD-Pt-300to470"] = 80000000;
  evQCDVBF["QCD-Pt-470to600"] = 25000000;
  
  map<string,double> evEffective; //TODO: Check this 
  evEffective["QCD-Pt-80to120"]  = 1938948;
  evEffective["QCD-Pt-120to170"] = 1983695;
  evEffective["QCD-Pt-170to300"] = 1357286;
  evEffective["QCD-Pt-300to470"] =  212745;
  evEffective["QCD-Pt-470to600"] =  103174;
  
  map<string,TFile*> files;
  files["Htoinv"]          = new TFile("Powheg-Htoinv-mH125.root",      "READ"); 
  files["QCD-Pt-80to120"]  = new TFile("QCD-Pt-80to120_VBF-MET40.root", "READ");
  files["QCD-Pt-120to170"] = new TFile("QCD-Pt-120to170_VBF-MET40.root","READ");
  files["QCD-Pt-170to300"] = new TFile("QCD-Pt-170to300_VBF-MET40.root","READ");
  files["QCD-Pt-300to470"] = new TFile("QCD-Pt-300to470_VBF-MET40.root","READ");
  files["QCD-Pt-470to600"] = new TFile("QCD-Pt-470to600_VBF-MET40.root","READ");
  
  vector<string> plots;
  plots.push_back("count");
  plots.push_back("Tracks0/TracksNRation");
  plots.push_back("Tracks0/TracksERation");
  
  
  map<pair<string,string>,TH1D*> hist;
  for(map<string,TFile*>::iterator f=files.begin(); f!=files.end(); f++){
    for(unsigned h=0; h<plots.size(); h++){
      
      pair<string,string> key;
      key.first = f->first;
      key.second = plots[h];
      
      printf("From file %50s retriving histogram: %s\n",key.first.c_str(),key.second.c_str());
      hist[key] = (TH1D*) f->second->Get(key.second.c_str());
      
    }
  }
  
  map<string,double> ev;  
  ev["QCD-Pt-80to120"]  = hist[pair<string,string>("QCD-Pt-80to120" ,"count")]->GetBinContent(1);
  ev["QCD-Pt-120to170"] = hist[pair<string,string>("QCD-Pt-120to170","count")]->GetBinContent(1);
  ev["QCD-Pt-170to300"] = hist[pair<string,string>("QCD-Pt-170to300","count")]->GetBinContent(1);
  ev["QCD-Pt-300to470"] = hist[pair<string,string>("QCD-Pt-300to470","count")]->GetBinContent(1);
  ev["QCD-Pt-470to600"] = hist[pair<string,string>("QCD-Pt-470to600","count")]->GetBinContent(1);
  for(map<string,double>::iterator i=ev.begin(); i!=ev.end(); i++){printf("Sample: %50s Events: %12.2f\n",i->first.c_str(),i->second);}
  
  map<string,double> factor;
  factor["QCD-Pt-80to120"]  = ev["QCD-Pt-80to120"]  / evEffective["QCD-Pt-80to120"] ;
  factor["QCD-Pt-120to170"] = ev["QCD-Pt-120to170"] / evEffective["QCD-Pt-120to170"];
  factor["QCD-Pt-170to300"] = ev["QCD-Pt-170to300"] / evEffective["QCD-Pt-170to300"];
  factor["QCD-Pt-300to470"] = ev["QCD-Pt-300to470"] / evEffective["QCD-Pt-300to470"];
  factor["QCD-Pt-470to600"] = ev["QCD-Pt-470to600"] / evEffective["QCD-Pt-470to600"];
  for(map<string,double>::iterator i=factor.begin(); i!=factor.end(); i++){printf("Sample: %50s processing efficiency factor: %8.6f\n",i->first.c_str(),i->second);}
  
  map<string,double> wgt;  
  wgt["QCD_VBF-Pt-80to120"]  = (lumi*xsec["QCD-Pt-80to120"])   /(evQCDVBF["QCD-Pt-80to120"] *factor["QCD-Pt-80to120"] );  
  wgt["QCD_VBF-Pt-120to170"] = (lumi*xsec["QCD-Pt-120to170"])  /(evQCDVBF["QCD-Pt-120to170"]*factor["QCD-Pt-120to170"]);  
  wgt["QCD_VBF-Pt-170to300"] = (lumi*xsec["QCD-Pt-170to300"])  /(evQCDVBF["QCD-Pt-170to300"]*factor["QCD-Pt-170to300"]);  
  wgt["QCD_VBF-Pt-300to470"] = (lumi*xsec["QCD-Pt-300to470"])  /(evQCDVBF["QCD-Pt-300to470"]*factor["QCD-Pt-300to470"]);  
  wgt["QCD_VBF-Pt-470to600"] = (lumi*xsec["QCD-Pt-470to600"])  /(evQCDVBF["QCD-Pt-470to600"]*factor["QCD-Pt-470to600"]);
  for(map<string,double>::iterator i=wgt.begin(); i!=wgt.end(); i++){printf("Sample: %50s Event weight: %8.6f\n",i->first.c_str(),i->second);}

  
  
  
  return 0;
    
}