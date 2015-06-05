#include "CMSSW_VBFHToInv/TriggerStudies/interface/HLTAlgo.h"

using namespace std;

HLTAlgo::HLTAlgo(){}

HLTAlgo::~HLTAlgo(){}

bool HLTAlgo::evaluate(HLTEventData *hltData){
  return false;
}

string HLTAlgo::getName(){
  return m_algoName;
}