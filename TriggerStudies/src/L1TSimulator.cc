#include "CMSSW_VBFHToInv/TriggerStudies/interface/L1TSimulator.h"

// CMSSW includes
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/ESInputTag.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"

// C++ includes
#include <iostream>

using namespace std;

L1TSimulator::L1TSimulator(){
  
  // Moun seeds
  m_menuPrescales["L1_SingleMuOpen"] = 262139;
  m_menuPrescales["L1_SingleMu5"]    =  50000;
  m_menuPrescales["L1_SingleMu12"]   =   3000;
  m_menuPrescales["L1_SingleMu16"]   =   1000;
  m_menuPrescales["L1_SingleMu20"]   =    700;
  m_menuPrescales["L1_SingleMu25"]   =      1;
  m_menuPrescales["L1_SingleMu30"]   =      1;
  m_menuPrescales["L1_SingleMu14er"] =   1000;
  m_menuPrescales["L1_SingleMu16er"] =   1000;
  m_menuPrescales["L1_SingleMu18er"] =    700;
  m_menuPrescales["L1_SingleMu20er"] =      1;
  m_menuPrescales["L1_SingleMu25er"] =      1;
  m_menuPrescales["L1_SingleMu30er"] =      1;
  
  m_menuPrescales["L1_DoubleMu0_Eta1p6_HighQ_WdEta18_OS"] =    1;
  m_menuPrescales["L1_DoubleMu0_Eta1p6_HighQ_WdEta18"]    = 2000;
  m_menuPrescales["L1_DoubleMu_10_0_HighQ_WdEta18"]       =    1;
  m_menuPrescales["L1_DoubleMu_10_Open"]                  = 2000;
  m_menuPrescales["L1_DoubleMu_10_3p5"]                   = 1000;
  m_menuPrescales["L1_DoubleMu_12_5"]                     =    1;
  
  m_menuPrescales["L1_TripleMu0_HighQ"]      =  100;
  m_menuPrescales["L1_TripleMu_5_5_3_HighQ"] =    1;
  m_menuPrescales["L1_QuadMu0_HighQ"]        =    1;

  // EG seeds
  m_menuPrescales["L1_SingleEG5"]       = 262139;
  m_menuPrescales["L1_SingleEG10"]      =  20000;
  m_menuPrescales["L1_SingleEG20"]      =   4000;
  m_menuPrescales["L1_SingleEG25"]      =   1000;
  m_menuPrescales["L1_SingleEG30"]      =    700;
  m_menuPrescales["L1_SingleEG35"]      =    500;
  m_menuPrescales["L1_SingleEG35er"]    =      1;
  m_menuPrescales["L1_SingleIsoEG18"]   =   3000;
  m_menuPrescales["L1_SingleIsoEG25er"] =   1000;
  m_menuPrescales["L1_SingleIsoEG28er"] =   1000;
  m_menuPrescales["L1_SingleIsoEG30er"] =      1;

  m_menuPrescales["L1_DoubleEG_15_10"]         = 1000;
  m_menuPrescales["L1_DoubleEG_22_10"]         =    1;
  m_menuPrescales["L1_DoubleEG_20_10_1LegIso"] =    1;
  
  m_menuPrescales["L1_TripleEG10"]       = 1;
  m_menuPrescales["L1_TripleEG_14_10_8"] = 1;
  
  // Jet seeds
  m_menuPrescales["L1_SingleJet52"]  = 50000;
  m_menuPrescales["L1_SingleJet68"]  = 40000;
  m_menuPrescales["L1_SingleJet92"]  =  4000;
  m_menuPrescales["L1_SingleJet128"] =  1000;
  m_menuPrescales["L1_SingleJet176"] =   300;
  m_menuPrescales["L1_SingleJet200"] =     1;
  m_menuPrescales["L1_SingleJet240"] =     1;
  
  m_menuPrescales["L1_DoubleJetC52"]  = 10000;
  m_menuPrescales["L1_DoubleJetC84"]  =   700;
  m_menuPrescales["L1_DoubleJetC100"] =     1;
  m_menuPrescales["L1_DoubleJetC112"] =     1;
  m_menuPrescales["L1_DoubleJetC120"] =     1;
  
  m_menuPrescales["L1_DoubleTauJet36er"] = 1000;
  m_menuPrescales["L1_DoubleTauJet52er"] =  200;
  m_menuPrescales["L1_DoubleTauJet68er"] =    1;

  m_menuPrescales["L1_TripleJet_92_76_64_VBF"] = 1;
  
  m_menuPrescales["L1_QuadJetC40"] = 1000;
  m_menuPrescales["L1_QuadJetC60"] =    1;
  m_menuPrescales["L1_QuadJetC84"] =    1;

  // Sum seeds
  m_menuPrescales["L1_ETM30"]                = 40000;
  m_menuPrescales["L1_ETM40"]                =  8000;
  m_menuPrescales["L1_ETM50"]                =  1000;
  m_menuPrescales["L1_ETM60"]                =   900;
  m_menuPrescales["L1_ETM70"]                =     1;
  m_menuPrescales["L1_ETM100"]               =     1;
  m_menuPrescales["L1_ETM60_NotJet52WdPhi2"] =     1;
  m_menuPrescales["L1_ETM70_NotJet52WdPhi2"] =     1;
  
  m_menuPrescales["L1_HTT125"] = 1000;
  m_menuPrescales["L1_HTT150"] =  800;
  m_menuPrescales["L1_HTT175"] =    1;
  m_menuPrescales["L1_HTT200"] =    1;
  m_menuPrescales["L1_HTT250"] =    1;
  
  // Cross seeds
  m_menuPrescales["L1_Mu6_HTT150"]           =   1;
  m_menuPrescales["L1_Mu0er_ETM55"]          = 100;
  m_menuPrescales["L1_Mu14er_ETM30"]         =   1;
  m_menuPrescales["L1_Mu10er_ETM50"]         =   1;
  m_menuPrescales["L1_Mu16er_TauJet20er"]    =   1;
  m_menuPrescales["L1_IsoEG20er_TauJet20er"] =   1;
  
  m_menuPrescales["L1_Mu20_EG8"]       = 10000;
  m_menuPrescales["L1_Mu20_EG10"]      =     1;
  m_menuPrescales["L1_Mu4_EG18"]       = 10000;
  m_menuPrescales["L1_Mu5_EG20"]       =     1;
  m_menuPrescales["L1_Mu5_IsoEG18"]    =     1;
  m_menuPrescales["L1_DoubleMu6_EG6"]  = 10000;
  m_menuPrescales["L1_DoubleMu7_EG7"]  =     1;
  m_menuPrescales["L1_Mu5_DoubleEG5"]  = 10000;
  m_menuPrescales["L1_Mu6_DoubleEG10"] =     1;
  
  m_menuPrescales["L1_Mu0er_ETM55_HTT100"]  = 1;
  m_menuPrescales["L1_Mu0er_ETM55_JetC120"] = 1;
  
  m_menuPrescales["L1_Mu3_JetC16_WdEtaPhi2"] =   1000;
  m_menuPrescales["L1_Mu3_JetC52_WdEtaPhi2"] =    200;
  m_menuPrescales["L1_Mu3_JetC92_WdEtaPhi2"] = 262139;
  
  m_menuPrescales["L1_DoubJetC32_WdPhi7_HTT125"] = 100;
  m_menuPrescales["L1_DoubleJetC56_ETM60"]       =   1;
  m_menuPrescales["L1_DoubleJetC60_ETM60"]       =   1;
  
  m_menuPrescales["L1_QuadJetC36_TauJet52"] = 20;

  for(unsigned i=0; i<128; i++){
    m_prescales.     push_back(0);
    m_prescalesCount.push_back(0);
  }

}

L1TSimulator::~L1TSimulator(){}

void L1TSimulator::getMenu(const edm::EventSetup& iSetup){
  
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd);
  
  const L1GtTriggerMenu* m_l1GtMenu;
  m_l1GtMenu = menuRcd.product(); // Getting the menu
  
  cout << "Menu name: " << m_l1GtMenu->gtTriggerMenuName() << endl;
  
  const AlgorithmMap *theAlgoMap = &m_l1GtMenu->gtAlgorithmAliasMap();
  
  for (auto iAlgo = theAlgoMap->begin(); iAlgo!=theAlgoMap->end(); ++iAlgo){
    
    if(m_menuPrescales.find(iAlgo->first) == m_menuPrescales.end()){cout << "NOT!!!=> ";}
    else{
      cout << "FOUND => ";

      const L1GtAlgorithm *pAlgo = &(iAlgo->second);
      m_prescales[pAlgo->algoBitNumber()] = m_menuPrescales[iAlgo->first];
    }
    
    const L1GtAlgorithm *pAlgo = &(iAlgo->second);
    cout << "Algo: " << iAlgo->first << " bit: " << pAlgo->algoBitNumber() << endl;
  }
}

bool L1TSimulator::l1tResult(DecisionWord &dw){
  
  bool out = false;
  
  for(unsigned i=0; i<dw.size(); i++){
    
    if(dw[i]){
      m_prescalesCount[i]++;
      if(m_prescalesCount[i]==m_prescales[i]){
        m_prescalesCount[i]=0;
        out=true;
      }
    }
  }
  
  return out;
}
