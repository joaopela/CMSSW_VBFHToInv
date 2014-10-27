import FWCore.ParameterSet.Config as cms

process = cms.Process('PAT')

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
################################################################


# import of standard configurations
#process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.hltPathStudies = cms.EDAnalyzer('HLTPathStudies',

  verbose                    = cms.untracked.bool(False),  
  inputTag_HLTResults        = cms.untracked.InputTag("TriggerResults::TEST"),
  
  HLTPaths  = cms.vstring(
    "HLT_PFHT350_PFMET120_NoiseCleaned_v1",
    "HLT_PFHT900_v1",
    "HLT_PFMET170_NoiseCleaned_v1",
    "HLT_PFMET_PFVBF_Unseeded_v1",
    "HLT_L1ETM70_PFMET_PFVBF_v1",
    "HLT_CaloMET_CaloVBF_Unseeded_v1",
    "HLT_L1ETM70_CaloMET_CaloVBF_v1",
    #"HLT_CaloMET_CaloVBF_v1",
    #"HLT_PFMET_PFVBF_v1",
  ), 

  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("hltL1extraParticles","Isolated"   ),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("hltL1extraParticles","NonIsolated"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("hltL1extraParticles","MET"        ),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("hltL1extraParticles","MHT"        ),
  inputTag_L1HFRings                = cms.untracked.InputTag("hltL1extraParticles",""           ),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("hltL1extraParticles","Central"    ),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("hltL1extraParticles","Forward"    ),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("hltL1extraParticles","Tau"        ),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("hltL1extraParticles",""           ),

  outputFilename = cms.untracked.string("HLTPathStudiesResults.root"),

)


# Output module
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('file:patReRunResults.root'),
                               SelectEvents    = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),             
                               outputCommands  = cms.untracked.vstring('keep *')              
                              )

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'POSTLS162_V2::All', '')


#process.load( "PhysicsTools.PatAlgos.patSequences_cff" )
#from PhysicsTools.PatAlgos.patEventContent_cff import *

#from PhysicsTools.PatAlgos.patTemplate_cfg import *
process.p = cms.Path()

from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process, path = 'p', hltProcess = 'TEST',outputModule = 'out')
#switchOnTrigger( process, hltProcess = 'HLT2',outputModule = 'out')

process.p += process.hltPathStudies

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process )                       
#process.patTrigger.saveL1Refs = cms.bool( False )
#process.patTrigger.hltProcess = cms.untracked.string('HLT2')
#switchOnTrigger( process )                       
    
#process.e = cms.EndPath(process.out)