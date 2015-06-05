#include "CMSSW_VBFHToInv/TriggerStudies/interface/AlgoTester.h"

#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"

#include <stdio.h>

using namespace std;

AlgoTester::AlgoTester(const edm::ParameterSet &pset){

  vector<string> algoTesterAlgos = pset.getParameter<vector<string> >("algoTesterAlgos");
  
  for(unsigned i=0; i<algoTesterAlgos.size(); i++){

    string &algo = algoTesterAlgos[i];

    cout << "Going to test algorithm: " << algo << endl;

    if     (algo=="L1_ETM40"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM40);}
    else if(algo=="L1_ETM45"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM45);}
    else if(algo=="L1_ETM50"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM50);}
    else if(algo=="L1_ETM55"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM55);}
    else if(algo=="L1_ETM60"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM60);}
    else if(algo=="L1_ETM65"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM65);}
    else if(algo=="L1_ETM70"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM70);}
    else if(algo=="L1_ETM75"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM75);}
    else if(algo=="L1_ETM80"){m_algoNames.push_back(algo); m_algos.push_back(&AlgoTester::l1tAlgo_L1_ETM80);}
    else if(algo=="L1_DoubleJetC60_ETM60"){
      m_algoNames.push_back("L1_DoubleJetC60_ETM60");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJetC60_ETM60);
    }
    else if(algo=="L1_DoubleJet60_ETM60"){
      m_algoNames.push_back("L1_DoubleJet60_ETM60");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJet60_ETM60);
    }
    else if(algo=="L1_DoubleJet40_DEta3p0_ETM40"){
      m_algoNames.push_back("L1_DoubleJet40_DEta3p0_ETM40");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJet40_DEta3p0_ETM40);
    }
    else if(algo=="L1_DoubleJet30_Mjj400_ETM40"){
      m_algoNames.push_back("L1_DoubleJet30_Mjj400_ETM40");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJet30_Mjj400_ETM40);
    }
    else if(algo=="L1_DoubleVBFJet40_DEta3p0_ETM40"){
      m_algoNames.push_back("L1_DoubleVBFJet40_DEta3p0_ETM40");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleVBFJet40_DEta3p0_ETM40);
    }
    else{
      cout << "ERROR: The selected trigger name \"" << algo << "\" is not implemented!"  << endl;
    }
  }
}

//
AlgoTester::~AlgoTester(){}

//
bool AlgoTester::l1tAlgo_L1_DoubleJetC60_ETM60(L1ExtraPayload &l1Objs){
  
  if(  l1Objs.m_L1EtMissParticle_MET->begin()->et()<60){return false;}
  if(  l1Objs.m_L1JetParticle_Central->size()<2)       {return false;}
  if((*l1Objs.m_L1JetParticle_Central)[1].et()<60)     {return false;}  
  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_DoubleJet60_ETM60(L1ExtraPayload &l1Objs){
  
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<60){return false;}

  vector<double> l1JetEt;
  for(unsigned i=0; i<l1Objs.m_L1JetParticle_Central->size(); i++){l1JetEt.push_back((*l1Objs.m_L1JetParticle_Central)[i].et());}
  for(unsigned i=0; i<l1Objs.m_L1JetParticle_Forward->size(); i++){l1JetEt.push_back((*l1Objs.m_L1JetParticle_Forward)[i].et());}
  sort (l1JetEt.begin(), l1JetEt.end(),std::greater<double>());
  
  if(l1JetEt.size()<2){return false;}
  if(l1JetEt[1]<60)   {return false;}  
  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM40(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<40){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM45(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<45){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM50(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<50){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM55(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<55){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM60(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<60){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM65(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<65){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM70(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<70){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM75(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<75){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_ETM80(L1ExtraPayload &l1Objs){
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<80){return false;}  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_DoubleJet40_DEta3p0_ETM40(L1ExtraPayload &l1Objs){
  
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<40){return false;}
  
  l1extra::L1JetParticleCollection* l1tJets = l1Objs.getL1TAllJets();
  
  if(l1tJets->size()<2)    {return false;}
  if((*l1tJets)[1].pt()<40){return false;}
  
  if(abs((*l1tJets)[0].eta()-(*l1tJets)[1].eta())<3.0){return false;}
  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_DoubleVBFJet40_DEta3p0_ETM40(L1ExtraPayload &l1Objs){
  
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<40){return false;}
  
  l1extra::L1JetParticleCollection *l1tJets = l1Objs.getL1TAllJets();
  
  if((*l1tJets).size()<2)  {return false;}
  if((*l1tJets)[1].pt()<40){return false;}

  if((*l1tJets)[0].eta()*(*l1tJets)[1].eta()>  0)     {return false;}
  if(abs((*l1tJets)[0].eta()-(*l1tJets)[1].eta())<3.0){return false;}
  
  return true;
}

//
bool AlgoTester::l1tAlgo_L1_DoubleJet30_Mjj400_ETM40(L1ExtraPayload &l1Objs){
  
  if(l1Objs.m_L1EtMissParticle_MET->begin()->et()<40){return false;}
  
  l1extra::L1JetParticleCollection *l1tJets = l1Objs.getL1TAllJets();
  
  if((*l1tJets).size()<2)  {return false;}
  if((*l1tJets)[1].pt()<30){return false;}
  
  double px = (*l1tJets)[0].px() + (*l1tJets)[1].px(); 
  double py = (*l1tJets)[0].py() + (*l1tJets)[1].py(); 
  double pz = (*l1tJets)[0].pz() + (*l1tJets)[1].pz(); 
  double normaP = pow(px,2) + pow(py,2) + pow(pz,2);
  double mjj    = sqrt(pow((*l1tJets)[0].energy()+(*l1tJets)[1].energy(),2) - normaP);
  
  if(mjj<400){return false;}
  
  return true;
}


vector<string> AlgoTester::getAlgoNames(){
  return m_algoNames;
}

vector<bool> AlgoTester::runAlgos(L1ExtraPayload &l1Objs){
  
  vector<bool> results;
  
  if(!l1Objs.isValid()){
    cout << "[AlgoTester] ERROR: L1 Extra not valid!" << endl;
  }else{
  
    for(unsigned iAlgo=0; iAlgo<m_algos.size(); iAlgo++){
      results.push_back(m_algos[iAlgo](this,l1Objs));
    }
  }
  
  return results;
}