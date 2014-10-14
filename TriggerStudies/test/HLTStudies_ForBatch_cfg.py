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

  verbose                    = cms.untracked.bool(True),  
  inputTag_HLTResults        = cms.untracked.InputTag("TriggerResults::TEST"),

  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ),
  inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ),

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