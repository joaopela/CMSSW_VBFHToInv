// Standard libraries includes

#include <iostream>
#include <string>

#include <vector>
#include <map>
#include <utility>

#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"

using namespace std;

void doPlot(map<pair<string,string>,TH1D*> hist,map<string,double> wgt,string plotName, string outName,int rebin){
  
  TCanvas c;
  TH1D *hQCD,*hSig;
  
  
  hQCD = (TH1D*) hist[pair<string,string>("QCD-Pt-80to120",plotName)]->Clone(); 
  hQCD->Scale(wgt["QCD_VBF-Pt-80to120"]);
  hQCD->Add(hist[pair<string,string>("QCD-Pt-120to170",plotName)],wgt["QCD_VBF-Pt-120to170"]);
  hQCD->Add(hist[pair<string,string>("QCD-Pt-170to300",plotName)],wgt["QCD_VBF-Pt-170to300"]);
  hQCD->Add(hist[pair<string,string>("QCD-Pt-300to470",plotName)],wgt["QCD_VBF-Pt-300to470"]);
  hQCD->Add(hist[pair<string,string>("QCD-Pt-470to600",plotName)],wgt["QCD_VBF-Pt-470to600"]);
  hQCD->Scale(1/hQCD->Integral(0,hQCD->GetNbinsX()+1));
  hQCD->SetLineColor(kGreen);
  if(rebin!=1){hQCD->Rebin(rebin);}
  hQCD->Draw();
  
  hSig = hist[pair<string,string>("Htoinv",plotName)];
  hSig->Scale(1/hSig->Integral(0,hSig->GetNbinsX()+1));
  hSig->SetLineColor(kRed);
  if(rebin!=1){hSig->Rebin(rebin);}
  hSig->Draw("same");
  
  c.SaveAs(outName.c_str());
  
}

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
  plots.push_back("Tracks1/TracksNRation");
  plots.push_back("Tracks1/TracksERation");
  plots.push_back("Tracks2/TracksNRation");
  plots.push_back("Tracks2/TracksERation");
  plots.push_back("Tracks0/CJVPass/TracksNRation");
  plots.push_back("Tracks0/CJVPass/TracksERation");
  plots.push_back("Tracks1/CJVPass/TracksNRation");
  plots.push_back("Tracks1/CJVPass/TracksERation");
  plots.push_back("Tracks2/CJVPass/TracksNRation");
  plots.push_back("Tracks2/CJVPass/TracksERation");
  
  plots.push_back("BB/Tracks0/TracksNRation");
  plots.push_back("BB/Tracks0/TracksERation");
  plots.push_back("BB/Tracks1/TracksNRation");
  plots.push_back("BB/Tracks1/TracksERation");
  plots.push_back("BB/Tracks2/TracksNRation");
  plots.push_back("BB/Tracks2/TracksERation"); 
  plots.push_back("BE/Tracks0/TracksNRation");
  plots.push_back("BE/Tracks0/TracksERation");
  plots.push_back("BE/Tracks1/TracksNRation");
  plots.push_back("BE/Tracks1/TracksERation");
  plots.push_back("BE/Tracks2/TracksNRation");
  plots.push_back("BE/Tracks2/TracksERation");  
  plots.push_back("EE/Tracks0/TracksNRation");
  plots.push_back("EE/Tracks0/TracksERation");
  plots.push_back("EE/Tracks1/TracksNRation");
  plots.push_back("EE/Tracks1/TracksERation");
  plots.push_back("EE/Tracks2/TracksNRation");
  plots.push_back("EE/Tracks2/TracksERation");
  
  
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

  //_____________________________________________

  doPlot(hist,wgt,"Tracks0/TracksNRation","Tracks0_TracksNRatio.png",4);
  doPlot(hist,wgt,"Tracks0/TracksERation","Tracks0_TracksERatio.png",4);
  doPlot(hist,wgt,"Tracks1/TracksNRation","Tracks1_TracksNRatio.png",4);
  doPlot(hist,wgt,"Tracks1/TracksERation","Tracks1_TracksERatio.png",4); 
  doPlot(hist,wgt,"Tracks2/TracksNRation","Tracks2_TracksNRatio.png",4);
  doPlot(hist,wgt,"Tracks2/TracksERation","Tracks2_TracksERatio.png",4);
  
  doPlot(hist,wgt,"Tracks0/CJVPass/TracksNRation","Tracks0_CJVPass_TracksNRation.png",4);
  doPlot(hist,wgt,"Tracks0/CJVPass/TracksERation","Tracks0_CJVPass_TracksERation.png",4);
  doPlot(hist,wgt,"Tracks1/CJVPass/TracksNRation","Tracks1_CJVPass_TracksNRation.png",4);
  doPlot(hist,wgt,"Tracks1/CJVPass/TracksERation","Tracks1_CJVPass_TracksERation.png",4);
  doPlot(hist,wgt,"Tracks2/CJVPass/TracksNRation","Tracks2_CJVPass_TracksNRation.png",4);
  doPlot(hist,wgt,"Tracks2/CJVPass/TracksERation","Tracks2_CJVPass_TracksERation.png",4);
  
  doPlot(hist,wgt,"BB/Tracks0/TracksNRation","BB_Tracks0_TracksNRatio.png",4);
  doPlot(hist,wgt,"BB/Tracks0/TracksERation","BB_Tracks0_TracksERatio.png",4);
  doPlot(hist,wgt,"BB/Tracks1/TracksNRation","BB_Tracks1_TracksNRatio.png",4);
  doPlot(hist,wgt,"BB/Tracks1/TracksERation","BB_Tracks1_TracksERatio.png",4); 
  doPlot(hist,wgt,"BB/Tracks2/TracksNRation","BB_Tracks2_TracksNRatio.png",4);
  doPlot(hist,wgt,"BB/Tracks2/TracksERation","BB_Tracks2_TracksERatio.png",4);
  doPlot(hist,wgt,"BE/Tracks0/TracksNRation","BE_Tracks0_TracksNRatio.png",4);
  doPlot(hist,wgt,"BE/Tracks0/TracksERation","BE_Tracks0_TracksERatio.png",4);
  doPlot(hist,wgt,"BE/Tracks1/TracksNRation","BE_Tracks1_TracksNRatio.png",4);
  doPlot(hist,wgt,"BE/Tracks1/TracksERation","BE_Tracks1_TracksERatio.png",4); 
  doPlot(hist,wgt,"BE/Tracks2/TracksNRation","BE_Tracks2_TracksNRatio.png",4);
  doPlot(hist,wgt,"BE/Tracks2/TracksERation","BE_Tracks2_TracksERatio.png",4);
  doPlot(hist,wgt,"EE/Tracks0/TracksNRation","EE_Tracks0_TracksNRatio.png",4);
  doPlot(hist,wgt,"EE/Tracks0/TracksERation","EE_Tracks0_TracksERatio.png",4);
  doPlot(hist,wgt,"EE/Tracks1/TracksNRation","EE_Tracks1_TracksNRatio.png",4);
  doPlot(hist,wgt,"EE/Tracks1/TracksERation","EE_Tracks1_TracksERatio.png",4); 
  doPlot(hist,wgt,"EE/Tracks2/TracksNRation","EE_Tracks2_TracksNRatio.png",4);
  doPlot(hist,wgt,"EE/Tracks2/TracksERation","EE_Tracks2_TracksERatio.png",4);
  
  return 0;
    
}