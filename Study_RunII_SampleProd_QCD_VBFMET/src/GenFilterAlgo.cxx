#include "CMSSW_VBFHToInv/Study_RunII_SampleProd_QCD_VBFMET/interface/GenFilterAlgo.h"

using namespace std;

#include "TMath.h"
#include "DataFormats/Math/interface/deltaPhi.h"

struct greater_GenJet{
  bool operator() (const reco::GenJet* j1,const reco::GenJet* j2) {
    return (j1->pt() > j2->pt());
  }
};

GenFilterAlgo::GenFilterAlgo(){
  this->init();
}

GenFilterAlgo::GenFilterAlgo(edm::ParameterSet& pset){
  this->init();
  
  if(pset.exists("name"))     {m_name = pset.getUntrackedParameter<string>("name");}
  
  if(pset.exists("jetMinPt")) {m_doJetMinPt  = true; m_valJetMinPt  = pset.getUntrackedParameter<double>("jetMinPt");}
  if(pset.exists("jetMaxEta")){m_doJetMaxEta = true; m_valJetMaxEta = pset.getUntrackedParameter<double>("jetMaxEta");}
  
  if(pset.exists("dijetOppositeHemisphere")){m_doOppositeHemisphere = pset.getUntrackedParameter<bool>("dijetOppositeHemisphere");}
  if(pset.exists("dijetMinDeltaEta"))       {m_doDijetMinDeltaEta   = true; m_valDijetMinDeltaEta = pset.getUntrackedParameter<double>("dijetMinDeltaEta");}
  if(pset.exists("dijetMaxDeltaPhi"))       {m_doDijetMaxDeltaPhi   = true; m_valDijetMaxDeltaPhi = pset.getUntrackedParameter<double>("dijetMaxDeltaPhi");}
  if(pset.exists("dijetMinMjj"))            {m_doDijetMinMjj        = true; m_valDijetMinMjj      = pset.getUntrackedParameter<double>("dijetMinMjj");}
  
}

void GenFilterAlgo::init(){
  m_name                 = "Unnamed Algorithm";
  m_doJetMinPt           = false;
  m_doJetMaxEta          = false;
  m_doOppositeHemisphere = false;
  m_doDijetMinDeltaEta   = false;
  m_doDijetMaxDeltaPhi   = false;
  m_doDijetMinMjj        = false;
  
  // For plots
  m_doPlots             = false;
  m_Jets_Multiplicity   = 0;
  m_Jet0_maxPt          = 0;
  m_Jet1_maxPt          = 0;
  m_Dijet_minEtaProduct = 0;
  m_Dijet_MaxMjj        = 0;
  m_Dijet_MaxDEta       = 0;
  m_Dijet_MinDPhi       = 0;
  
  m_Dijet_MultiplicityPass = 0;
  m_LeadDijet_Jet0_Pt      = 0;
  m_LeadDijet_Jet1_Pt      = 0;
  m_LeadDijet_Jet0_Eta     = 0;
  m_LeadDijet_Jet1_Eta     = 0;
  m_LeadDijet_Mjj          = 0;
  m_LeadDijet_DEta         = 0;
  m_LeadDijet_DPhi         = 0;
  
}

void GenFilterAlgo::buildPlots(TDirectory* dir){
  
  m_doPlots = true;
  
  m_Jets_Multiplicity   = new TH1D("Jets_Multiplicity"  ,"Jets_Multiplicity"  ,  51,-0.5,       50.5); m_Jets_Multiplicity  ->SetDirectory(dir);
  m_Jet0_maxPt          = new TH1D("Jet0_maxPt"         ,"Jet0_maxPt"         ,1000,   0,       2000); m_Jet0_maxPt         ->SetDirectory(dir);
  m_Jet1_maxPt          = new TH1D("Jet1_maxPt"         ,"Jet1_maxPt"         ,1000,   0,       2000); m_Jet1_maxPt         ->SetDirectory(dir);
  m_Dijet_minEtaProduct = new TH1D("Dijet_minEtaProduct","Dijet_minEtaProduct",  50, -25,         25); m_Dijet_minEtaProduct->SetDirectory(dir);
  m_Dijet_MaxMjj        = new TH1D("Dijet_MaxMjj"       ,"Dijet_MaxMjj"       , 500,   0,       5000); m_Dijet_MaxMjj       ->SetDirectory(dir);
  m_Dijet_MaxDEta       = new TH1D("Dijet_MaxDEta"      ,"Dijet_MaxDEta"      , 200,   0,         10); m_Dijet_MaxDEta      ->SetDirectory(dir);
  m_Dijet_MinDPhi       = new TH1D("Dijet_MinDPhi"      ,"Dijet_MinDPhi"      , 128,   0,TMath::Pi()); m_Dijet_MinDPhi      ->SetDirectory(dir);
  
  m_Dijet_MultiplicityPass = new TH1D("Dijet_MultiplicityPass" ,"Dijet_MultiplicityPass" ,   51, -0.5,50.5); m_Dijet_MultiplicityPass ->SetDirectory(dir);
  
  // Distributions for leading dijet passing cuts
  // Here leading dijet is the dijet combination passing cuts with the highest lead jet pT
  // and if more than one, the one with the highest sub-leading jet pT
  m_LeadDijet_Jet0_Pt  = new TH1D("LeadDijet_Jet0_Pt" ,"LeadDijet_Jet0_Pt", 1000,   0,2000);        m_LeadDijet_Jet0_Pt ->SetDirectory(dir);
  m_LeadDijet_Jet1_Pt  = new TH1D("LeadDijet_Jet1_Pt" ,"LeadDijet_Jet1_Pt", 1000,   0,2000);        m_LeadDijet_Jet1_Pt ->SetDirectory(dir);
  m_LeadDijet_Jet0_Eta = new TH1D("LeadDijet_Jet0_Eta","LeadDijet_Jet0_Eta", 100,-5.0, 5.0);        m_LeadDijet_Jet0_Eta->SetDirectory(dir);
  m_LeadDijet_Jet1_Eta = new TH1D("LeadDijet_Jet1_Eta","LeadDijet_Jet1_Eta", 100,-5.0, 5.0);        m_LeadDijet_Jet1_Eta->SetDirectory(dir);
  m_LeadDijet_Mjj      = new TH1D("LeadDijet_Mjj"     ,"LeadDijet_Mjj",      500,   0,5000);        m_LeadDijet_Mjj     ->SetDirectory(dir);
  m_LeadDijet_DEta     = new TH1D("LeadDijet_DEta"    ,"LeadDijet_DEta",     200,   0,  10);        m_LeadDijet_DEta    ->SetDirectory(dir);
  m_LeadDijet_DPhi     = new TH1D("LeadDijet_DPhi"    ,"LeadDijet_DPhi",     128,   0,TMath::Pi()); m_LeadDijet_DPhi    ->SetDirectory(dir);
  
}

GenFilterAlgo::~GenFilterAlgo(){
  
  if(m_Jets_Multiplicity)  {delete m_Jets_Multiplicity;}
  if(m_Jet0_maxPt)         {delete m_Jet0_maxPt;}
  if(m_Jet1_maxPt)         {delete m_Jet1_maxPt;}
  if(m_Dijet_minEtaProduct){delete m_Dijet_minEtaProduct;}
  if(m_Dijet_MaxMjj)       {delete m_Dijet_MaxMjj;}
  if(m_Dijet_MaxDEta)      {delete m_Dijet_MaxDEta;}
  if(m_Dijet_MinDPhi)      {delete m_Dijet_MinDPhi;}
  
  if(m_Dijet_MultiplicityPass){delete m_Dijet_MultiplicityPass;}
  if(m_LeadDijet_Jet0_Pt     ){delete m_LeadDijet_Jet0_Pt     ;}
  if(m_LeadDijet_Jet1_Pt     ){delete m_LeadDijet_Jet1_Pt     ;}
  if(m_LeadDijet_Jet0_Eta    ){delete m_LeadDijet_Jet0_Eta    ;}
  if(m_LeadDijet_Jet1_Eta    ){delete m_LeadDijet_Jet1_Eta    ;}
  if(m_LeadDijet_Mjj         ){delete m_LeadDijet_Mjj         ;}
  if(m_LeadDijet_DEta        ){delete m_LeadDijet_DEta        ;}
  if(m_LeadDijet_DPhi        ){delete m_LeadDijet_DPhi        ;}
  
}
  
bool GenFilterAlgo::evaluate(const vector<reco::GenJet>* genJets){
  
  bool   eventPass             = false;
  double passDijetMultiplicity = 0;
  
  double maxJetPt0  = -1;
  double maxJetPt1  = -1;
  double minEtaProd = 1e99;
  double minDPhi    = 1e99;
  double maxDEta    = -1;
  double maxMjj     = -1;
  
  // Making sure genJets are sorted by pT
  vector<const reco::GenJet*> sorted_genJets;
  for(unsigned a=0; a<sorted_genJets.size(); a++){
    const reco::GenJet* j = &((*genJets)[a]);
    sorted_genJets.push_back(j);
  }
  sort(sorted_genJets.begin(),sorted_genJets.end(),greater_GenJet());
  
  
  vector<const reco::GenJet*> filGenJets = filterGenJets(genJets);
  
  for(unsigned a=0; a<filGenJets.size(); a++){
    for(unsigned b=a+1; b<filGenJets.size(); b++){
      
      const reco::GenJet* pA = filGenJets[a];
      const reco::GenJet* pB = filGenJets[b];
      
      double etaProd = 0;
      double dPhi    = 0;
      double dEta    = 0;
      double invMass = 0;
      

      // Dijet cut: Opposite hemispheres
      etaProd = pA->p4().eta()*pB->p4().eta();
      if(m_doOppositeHemisphere){
        if(etaProd>=0){continue;}
      }


      // Dijet cut: Max delta(phi)
      dPhi = fabs(reco::deltaPhi(pA->phi(),pB->phi()));
      if(m_doDijetMaxDeltaPhi){
        if(dPhi>=m_valDijetMaxDeltaPhi){continue;}
      }
      
      // Dijet cut: Max delta(eta)
      dEta = fabs(pA->p4().eta()-pB->p4().eta());
      if(m_doDijetMinDeltaEta){
        if(dEta<=m_valDijetMinDeltaEta){continue;}
      }

      // Getting the dijet vector
      math::XYZTLorentzVector diJet = pA->p4() + pB->p4();
      invMass = diJet.mass();
 
      // Dijet cut: Max delta(eta)
      if(m_doDijetMinMjj){
        if(invMass<=m_valDijetMinMjj){continue;}
      }
      
      eventPass = true;
      passDijetMultiplicity++;
      
      if(maxJetPt0  < pA->pt()){maxJetPt0  = pA->pt();}
      if(maxJetPt1  < pB->pt()){maxJetPt1  = pB->pt();}
      if(minEtaProd > etaProd) {minEtaProd = etaProd;}
      if(minDPhi    > dPhi)    {minDPhi    = dPhi;}
      if(maxDEta    < dEta)    {maxDEta    = dEta;}
      if(maxMjj     < invMass) {maxMjj     = invMass;}
      
      // For the leading combination
      if(passDijetMultiplicity==1){
        m_LeadDijet_Jet0_Pt ->Fill(pA->pt());
        m_LeadDijet_Jet1_Pt ->Fill(pB->pt());
        m_LeadDijet_Jet0_Eta->Fill(pA->p4().eta());
        m_LeadDijet_Jet1_Eta->Fill(pB->p4().eta());
        m_LeadDijet_Mjj     ->Fill(invMass);
        m_LeadDijet_DEta    ->Fill(dEta);
        m_LeadDijet_DPhi    ->Fill(dPhi);
      }
    }
  }
  
  if(eventPass){
    m_Jets_Multiplicity     ->Fill(filGenJets.size());
    m_Dijet_MultiplicityPass->Fill(passDijetMultiplicity);
    m_Jet0_maxPt            ->Fill(maxJetPt0);
    m_Jet1_maxPt            ->Fill(maxJetPt1);
    m_Dijet_minEtaProduct   ->Fill(minEtaProd);
    m_Dijet_MinDPhi         ->Fill(minDPhi);
    m_Dijet_MaxDEta         ->Fill(maxDEta);
    m_Dijet_MaxMjj          ->Fill(maxMjj);
  }
  
  
  return eventPass;
}

void GenFilterAlgo::print(){
  
  cout << "############################" << endl;
  cout << "###### GenFilterAlgo #######" << endl;
  cout << "############################" << endl;
  cout << "# Algo Name          : " << m_name << endl;
  if(m_doJetMinPt)          {cout << "# Jet Min Pt         : " << m_valJetMinPt << endl;}
  if(m_doJetMaxEta)         {cout << "# Jet Max Eta        : " << m_valJetMaxEta << endl;}
  if(m_doOppositeHemisphere){cout << "# Dijet Opp. Hem.    : True" << endl;}
  if(m_doDijetMinDeltaEta)  {cout << "# Dijet Min DeltaEta : " << m_valDijetMinDeltaEta << endl;}
  if(m_doDijetMaxDeltaPhi)  {cout << "# Dijet Max DeltaPhi : " << m_valDijetMaxDeltaPhi << endl;}
  if(m_doDijetMinMjj)       {cout << "# Dijet Min Mjj      : " << m_valDijetMinMjj << endl;}
  cout << "############################" << endl;
  cout << endl;
  
}

vector<const reco::GenJet*> GenFilterAlgo::filterGenJets(const vector<reco::GenJet>* jets){
  
  vector<const reco::GenJet*> out;
  
  for(unsigned i=0; i<jets->size(); i++){
    
    const reco::GenJet* j = &((*jets)[i]);
    
    if(m_doJetMinPt) {if(j->p4().pt()       <=m_valJetMinPt) {continue;}}
    if(m_doJetMaxEta){if(fabs(j->p4().eta())>=m_valJetMaxEta){continue;}}
    
    out.push_back(j);
  }
  
  return out;
}