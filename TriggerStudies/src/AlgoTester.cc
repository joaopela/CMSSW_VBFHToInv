#include "VBFHiggsToInvisible/TriggerStudies/interface/AlgoTester.h"

#include <stdio.h>

using namespace std;

AlgoTester::AlgoTester(const edm::ParameterSet &pset){

  vector<string> algoTesterAlgos = pset.getParameter<vector<string> >("algoTesterAlgos");
  
  for(unsigned i=0; i<algoTesterAlgos.size(); i++){
    
    string &algo = algoTesterAlgos[i];
    
    if(algo=="L1_DoubleJetC60_ETM60"){
      m_algoNames.push_back("L1_DoubleJetC60_ETM60");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJetC60_ETM60);
    }
    else if(algo=="L1_DoubleJet60_ETM60"){
      m_algoNames.push_back("L1_DoubleJet60_ETM60");
      m_algos.push_back(&AlgoTester::l1tAlgo_L1_DoubleJet60_ETM60);
    }
    else{
      cout << "ERROR: The selected trigger name \"" << algo << "\" is not implemented!"  << endl;
    }
  }
}

AlgoTester::~AlgoTester(){}

bool AlgoTester::l1tAlgo_L1_DoubleJetC60_ETM60(L1ExtraPayload &l1extra){
  
  if(  l1extra.m_L1EtMissParticle_MET->begin()->et()<60){return false;}
  if(  l1extra.m_L1JetParticle_Central->size()<2)       {return false;}
  if((*l1extra.m_L1JetParticle_Central)[1].et()<60)     {return false;}  
  
  return true;
}

bool AlgoTester::l1tAlgo_L1_DoubleJet60_ETM60(L1ExtraPayload &l1extra){
  
  if(l1extra.m_L1EtMissParticle_MET->begin()->et()<60){return false;}

  vector<double> l1JetEt;
  for(unsigned i=0; i<l1extra.m_L1JetParticle_Central->size(); i++){l1JetEt.push_back((*l1extra.m_L1JetParticle_Central)[i].et());}
  for(unsigned i=0; i<l1extra.m_L1JetParticle_Forward->size(); i++){l1JetEt.push_back((*l1extra.m_L1JetParticle_Forward)[i].et());}
  sort (l1JetEt.begin(), l1JetEt.begin(),std::greater<double>());
  
  if(l1JetEt.size()<2){return false;}
  if(l1JetEt[1]<60)   {return false;}  
  
  return true;
}

vector<string> AlgoTester::getAlgoNames(){
  return m_algoNames;
}

vector<bool> AlgoTester::runAlgos(L1ExtraPayload &l1extra){
  
  vector<bool> results;
  
  for(unsigned iAlgo=0; iAlgo<m_algos.size(); iAlgo++){
    
    results.push_back(m_algos[iAlgo](this,l1extra));
    
  }
  
  return results;
}