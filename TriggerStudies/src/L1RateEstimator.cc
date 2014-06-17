#include "VBFHiggsToInvisible/L1RateEstimator/interface/L1RateEstimator.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

L1RateEstimator::L1RateEstimator(const edm::ParameterSet& pset){
  
  m_verbose       = pset.getUntrackedParameter<bool>("verbose",false);
  if(m_doL1TAnalysis){
    m_InputTag_L1GTReadoutRecord = pset.getParameter<InputTag>("inputTag_L1GTReadoutRecord");
    m_selL1Trigger               = pset.getParameter<std::vector<string> >("selL1Trigger");
    
    // Initialising L1T Trigger fire counters
    for(unsigned i=0; i<m_selL1Trigger.size(); i++){
      cL1T[ m_selL1Trigger[i] ] = 0;
    }
  }
    
  // Initialising event counter 
  evCount=0;
  
}


L1RateEstimator::~L1RateEstimator(){
  
  cout << "Total Events: " << evCount << endl;
      
  cout << "*====================================*" << endl;
  cout << "| L1T Study                          |" << endl;
  cout << "*====================================*" << endl;
    
  cout << "Absolute count:" << endl;
  for(unsigned i=0; i<m_selL1Trigger.size(); i++){
    
    string *pName  = &(m_selL1Trigger[i]); 
    int    *pCount = &(cL1T[ (*pName) ]);
    double  pError = sqrt(double(*pCount));
    
    printf("%-50s : %6d +/- %8.1f\n",pName->c_str(),(*pCount),pError);
  }
  
  cout << "Efficiency:" << endl;
  for(unsigned i=0; i<m_selL1Trigger.size(); i++){
    
    string *pName  = &(m_selL1Trigger[i]); 
    int    *pCount = &(cL1T[ (*pName) ]);
    double  pError = sqrt(double(*pCount));
    
    double  pFrac    = double(*pCount)/double(evCount);
    double  pFracErr = pError/double(evCount);
    
    printf("%-50s : %6.4f +/- %6.4f\n",pName->c_str(),pFrac,pFracErr);
  }
}

void L1RateEstimator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  evCount++;
      
  // Getting Final Decision Logic (FDL) Data from GT
  Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecordData;
  iEvent.getByLabel(m_InputTag_L1GTReadoutRecord, gtReadoutRecordData);
  
  if(gtReadoutRecordData.isValid()){
    
    const vector<L1GtFdlWord>& gtFdlVectorData = gtReadoutRecordData->gtFdlVector();
    
    // Running over selected triggers
    for(unsigned i=0; i<m_selL1Trigger.size(); i++){
      
      string pName = m_selL1Trigger[i];
      
      // Running over FDL results to get which bits fired
      for(unsigned int a=0 ; a<gtFdlVectorData.size() ; a++){
        
        // Selecting the FDL that triggered
        if(gtFdlVectorData[a].bxInEvent() == 0){
          if(gtFdlVectorData[a].gtDecisionWord()[ m_algoBit[pName] ]){cL1T[pName]++;}
        }
      }
    }
  }
}

// ------------ method called once each job just before starting event loop  ------------
void 
L1RateEstimator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L1RateEstimator::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
L1RateEstimator::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
    
  ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
  const L1GtTriggerMenu* menu = menuRcd.product();
    
  // Filling Alias-Bit Map
  for (CItAlgo algo = menu->gtAlgorithmAliasMap().begin(); algo!=menu->gtAlgorithmAliasMap().end(); ++algo){
    m_algoBit[(algo->second).algoAlias()] = (algo->second).algoBitNumber();
  }
 
  
}

// ------------ method called when ending the processing of a run  ------------
void 
L1RateEstimator::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
L1RateEstimator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
L1RateEstimator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(L1RateEstimator);
