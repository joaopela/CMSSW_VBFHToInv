#include "VBFHiggsToInvisible/TriggerStudies/interface/HLTPlots.h"

#include "TDirectory.h"
#include "TMath.h"

using namespace std;

HLTPlots::HLTPlots(){

  met = 0;
  
}

HLTPlots::HLTPlots(TDirectory* d){
  
  met = new TH1D("hlt_etm","HLT ETM"  , 500,-0.5,495.5);
  met->GetXaxis()->SetTitle("HLT ETM [GeV]");
  met->GetYaxis()->SetTitle("Entries");
  met->SetDirectory(d);
  
}

void HLTPlots::fill(HLTPlotsData data){
  
  if(data.met.first){met->Fill(data.met.second);}

}

HLTPlots::~HLTPlots(){
  delete met;
}
