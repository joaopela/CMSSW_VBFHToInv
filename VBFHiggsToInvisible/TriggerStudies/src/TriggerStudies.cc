#include "VBFHiggsToInvisible/TriggerStudies/interface/TriggerStudies.h"

#include <stdio.h>
#include <math.h>

using namespace std;
using namespace edm;

TriggerStudies::TriggerStudies(const edm::ParameterSet& pset){

  m_verbose       = pset.getUntrackedParameter<bool>("verbose",false);
  m_doL1TAnalysis = pset.getUntrackedParameter<bool>("doL1TAnalysis",false);
  if(m_doL1TAnalysis){
    m_InputTag_L1GTReadoutRecord = pset.getParameter<InputTag>("inputTag_L1GTReadoutRecord");
    m_selL1Trigger               = pset.getParameter<std::vector<string> >("selL1Trigger");
    
    // Initialising L1T Trigger fire counters
    for(unsigned i=0; i<m_selL1Trigger.size(); i++){
      cL1T[ m_selL1Trigger[i] ] = 0;
    }
  }
  
  m_doHLTAnalysis = pset.getUntrackedParameter<bool>("doHLTAnalysis",false);  
  if(m_doHLTAnalysis){
    m_InputTag_HLTResults = pset.getParameter<InputTag>("inputTag_HLTResults");
    m_selHLTrigger        = pset.getParameter<std::vector<string> >("selHLTrigger");
    
    // Initialising HLT Path fire counters
    for(unsigned i=0; i<m_selHLTrigger.size(); i++){
      cHLT[ m_selHLTrigger[i] ] = 0;
    }
  }
 
  // Initialising event counter 
  evCount=0;
  
}


TriggerStudies::~TriggerStudies(){
  
  cout << "Total Events: " << evCount << endl;
  
  if(m_doL1TAnalysis){

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
  
  if(m_doHLTAnalysis){
    
    cout << "*====================================*" << endl;
    cout << "| HLT Study                          |" << endl;
    cout << "*====================================*" << endl;
    
    cout << "Absolute count:" << endl;
    for(unsigned i=0; i<m_selHLTrigger.size(); i++){
      
      string *pName  = &(m_selHLTrigger[i]); 
      int    *pCount = &(cHLT[ (*pName) ]);
      double  pError = sqrt(double(*pCount));
      
      printf("%-50s : %6d +/- %8.1f\n",pName->c_str(),(*pCount),pError);
    }
    
    cout << "Efficiency:" << endl;
    for(unsigned i=0; i<m_selHLTrigger.size(); i++){
      
      string *pName  = &(m_selHLTrigger[i]); 
      int    *pCount = &(cHLT[ (*pName) ]);
      double  pError = sqrt(double(*pCount));
      
      double  pFrac    = double(*pCount)/double(evCount);
      double  pFracErr = pError/double(evCount);
      
      printf("%-50s : %6.4f +/- %6.4f\n",pName->c_str(),pFrac,pFracErr);
    }
  }
  
}

void TriggerStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  if(m_doL1TAnalysis){
    
    ESHandle<L1GtTriggerMenu> menuRcd;
    iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
    const L1GtTriggerMenu* menu = menuRcd.product();
    
    // Filling Alias-Bit Map
    for (CItAlgo algo = menu->gtAlgorithmAliasMap().begin(); algo!=menu->gtAlgorithmAliasMap().end(); ++algo){
      m_algoBit[(algo->second).algoAlias()] = (algo->second).algoBitNumber();
    }
  }  
  
  evCount++;
   
  if(m_doHLTAnalysis){
   
    Handle<TriggerResults> hltresults;
    iEvent.getByLabel(m_InputTag_HLTResults, hltresults);
     
    for(unsigned i=0; i<m_selHLTrigger.size(); i++){
       
      string pName = m_selHLTrigger[i];
      if(testTrigger(iEvent,hltresults,pName)){cHLT[pName]++;}
       
    }
  }
   
  if(m_doL1TAnalysis){
      
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
}

bool TriggerStudies::testTrigger(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT, string iTriggerName){
    
  bool Triggered = false;
  
  if( !iHLT.isValid() ) Triggered = false;
  int ntrigs = iHLT->size();
  if(ntrigs==0) Triggered = false;
  
  //check if trigger names are active
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
  //m_triggerNames.init( *iHLT.product() );
  
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if( iHLT->error(itrig) ) continue;
    string trigName = m_triggerNames.triggerName(itrig); 
    if( trigName.find(iTriggerName)==std::string::npos ) continue;
    if( !iHLT->accept(itrig) ) continue; 
    Triggered = true;
  }
  
  return Triggered;
  
}

void TriggerStudies::printFiredHLT(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> iHLT){
  
  int ntrigs = iHLT->size();
  
  const edm::TriggerNames &m_triggerNames = iEvent.triggerNames(*iHLT);
   
  for (int itrig = 0; itrig != ntrigs; ++itrig) 
  {
    if( !iHLT->wasrun(itrig) ) continue;
    if(  iHLT->error(itrig) )  continue;
    
    string trigName = m_triggerNames.triggerName(itrig); 
    
    if( !iHLT->accept(itrig) )        continue;
    
    if(trigName.find("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v")      !=std::string::npos){cHLT["HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v"]++; }
    if(trigName.find("HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v")  !=std::string::npos){cHLT["HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v"]++; }
    if(trigName.find("HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v")     !=std::string::npos){cHLT["HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v"]++;}
    if(trigName.find("HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v")           !=std::string::npos){cHLT["HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v"]++;      }
    if(trigName.find("HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v")           !=std::string::npos){cHLT["HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v"]++;      }
    if(trigName.find("HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v")           !=std::string::npos){cHLT["HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v"]++;      }
    if(trigName.find("HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v")           !=std::string::npos){cHLT["HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"]++;      }

  }
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerStudies::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerStudies::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TriggerStudies::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup){
  
}

// ------------ method called when ending the processing of a run  ------------
void 
TriggerStudies::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TriggerStudies::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TriggerStudies::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerStudies);
