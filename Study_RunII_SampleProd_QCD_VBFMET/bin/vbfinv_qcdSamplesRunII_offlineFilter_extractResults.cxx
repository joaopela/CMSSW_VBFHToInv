#include <iostream>

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


void tresholdAnalysis(map<string,TH1D*> hist,double threshold){
  
  vector<string> order;
  order.push_back("30to50");
  order.push_back("50to80");
  order.push_back("80to120");
  order.push_back("120to170");
  order.push_back("170to300");
  order.push_back("300to470");
  order.push_back("470to600");
  order.push_back("600to800");
  
  for(unsigned i=0; i<order.size(); i++){
    
    string index = order[i];
    TH1D* h      = hist [index];
    
    
    int    bin          = h->FindBin      (threshold);
    double value        = h->GetBinLowEdge(bin);
    double fullIntegral = h->Integral(  0,h->GetNbinsX()+1);
    double relIntegral  = h->Integral(bin,h->GetNbinsX()+1);
    double fraction     = relIntegral/fullIntegral;
    
    printf("Bin: %15s hBin: %5d Cut: %10.1f Total: %10.1f Pass: %10.1f Frac: %10.8f\n",index.c_str(),bin,value,fullIntegral,relIntegral,fraction);

  }
}

void drawPlots(map<string,TH1D*> hist,string filename){
  
  vector<string> order;
  order.push_back("30to50");
  order.push_back("50to80");
  order.push_back("80to120");
  order.push_back("120to170");
  order.push_back("170to300");
  order.push_back("300to470");
  order.push_back("470to600");
  order.push_back("600to800");
  
  map<string,int> color;
  color["30to50"]   = 2;
  color["50to80"]   = 3;
  color["80to120"]  = 4;
  color["120to170"] = 5;
  color["170to300"] = 6;
  color["300to470"] = 7;
  color["470to600"] = 8;
  color["600to800"] = 9;
  
  TCanvas c;
  TLegend l(0.55,0.75,0.85,0.95);
  l.SetHeader("QCD p_{T} Hat");
  l.SetFillColor(kWhite);
  
  for(unsigned i=0; i<order.size(); i++){
    
    string index = order[i];
    TH1D* h      = hist [index];
    
    h->SetLineColor(color[index]);
    
    double fullIntegral = h->Integral(0,h->GetNbinsX()+1);
    h->Scale(1/fullIntegral);
    h->GetYaxis()->SetTitle("Scaled to 1");
    
    h->Rebin(4);
    
    if(i==0){h->Draw();}
    else    {h->Draw("same");}
    
    l.AddEntry(h,index.c_str(),"l");
  }
  
  l.Draw();
  
  c.SaveAs(Form("%s.C",filename.c_str()));
  c.SaveAs(Form("%s.jpg", filename.c_str()));
  c.SaveAs(Form("%s.pdf", filename.c_str()));
}

map<string,TH1D*> getHist1D(map<string,TFile*> files,string path){
  
  map<string,TH1D*> out;
  
  for(auto i=files.begin(); i!=files.end(); i++){
    
    out[i->first] = (TH1D*) i->second->Get(path.c_str());
  }
  
  return out;
}

void doFilterYields(map<string,TFile*> files){
  
  map<string,TH1D*> hEventCount = getHist1D(files,"EventCount");
  
  FILE *fEv,*fEf;
  fEv = fopen ("FilterYields.tex","w");
  fEf = fopen ("FilterEfficiencies.tex","w");
  
  int      nbins   = hEventCount["30to50"]->GetNbinsX();
//   double   evTotal = hEventCount["30to50"]->GetBinContent(1);
  unsigned counter = 0;
  
  fprintf(fEv,"\\begin{tabular}{|l|");
  fprintf(fEf,"\\begin{tabular}{|l|");
  for(unsigned i=0; i<hEventCount.size(); i++){
    fprintf(fEv,"c|");
    fprintf(fEf,"c|");
  }
  fprintf(fEv,"}\n");
  fprintf(fEf,"}\n");
  
  fprintf(fEv,"\\hline\n");
  fprintf(fEf,"\\hline\n");
  fprintf(fEv," %40s &","Algorithm");
  fprintf(fEf," %40s &","Algorithm");
  for(auto iHist=hEventCount.begin(); iHist!=hEventCount.end(); iHist++){
    
    fprintf(fEv," %8s ",iHist->first.c_str());
    fprintf(fEf," %8s ",iHist->first.c_str());
    if(counter<hEventCount.size()-1){
      fprintf(fEv,"&");
      fprintf(fEf,"&");
    }else{
      fprintf(fEv,"\\\\ \n");
      fprintf(fEf,"\\\\ \n");
    }
    counter++;
  }
  
  fprintf(fEv,"\\hline\n");
  fprintf(fEf,"\\hline\n");
  for(int iBin=1; iBin<=nbins; iBin++){
    fprintf(fEv," %-40s &",hEventCount["30to50"]->GetXaxis()->GetBinLabel(iBin));
    fprintf(fEf," %-40s &",hEventCount["30to50"]->GetXaxis()->GetBinLabel(iBin));
    
    counter = 0;
    for(auto iHist=hEventCount.begin(); iHist!=hEventCount.end(); iHist++){
      fprintf(fEv," %8.0f ",iHist->second->GetBinContent(iBin));
      fprintf(fEf," %8.6f ",iHist->second->GetBinContent(iBin)/iHist->second->GetBinContent(1));
      if(counter<hEventCount.size()-1){
        fprintf(fEv,"&");
        fprintf(fEf,"&");
      }
      counter++;
    }
    fprintf(fEv,"\\\\ \n");
    fprintf(fEf,"\\\\ \n");
  }
  fprintf(fEv,"\\hline\n");
  fprintf(fEf,"\\hline\n");
  fprintf(fEv,"\\end{tabular}\n");
  fprintf(fEf,"\\end{tabular}\n");
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
  fileNames["30to50"]   = "OfflineFilterAnalyzer_QCD_Pt-30to50.root";
  fileNames["50to80"]   = "OfflineFilterAnalyzer_QCD_Pt-50to80.root";
  fileNames["80to120"]  = "OfflineFilterAnalyzer_QCD_Pt-80to120.root";
  fileNames["120to170"] = "OfflineFilterAnalyzer_QCD_Pt-120to170.root";
  fileNames["170to300"] = "OfflineFilterAnalyzer_QCD_Pt-170to300.root";
  fileNames["300to470"] = "OfflineFilterAnalyzer_QCD_Pt-300to470.root";
  fileNames["470to600"] = "OfflineFilterAnalyzer_QCD_Pt-470to600.root";
  fileNames["600to800"] = "OfflineFilterAnalyzer_QCD_Pt-600to800.root";
  
  if(!checkFiles(fileNames)){
    cout << "FATAL ERROR: One or more files missing!" << endl;
    return 1;
  }
  
  map<string,TFile*> files;
  for(auto i=fileNames.begin(); i!=fileNames.end(); i++){
    files[i->first] = new TFile(i->second.c_str(),"READ");
  }
  
  doFilterYields(files);
  
  map<string,TH1D*> hL1MET = getHist1D(files,"L1Extra_MET");
  
  tresholdAnalysis(hL1MET,40);
  tresholdAnalysis(hL1MET,60);
  tresholdAnalysis(hL1MET,70);
  
  drawPlots(hL1MET,"L1Extra_MET");
  
  return 0;
}
