import FWCore.ParameterSet.Config as cms

process = cms.Process('PAT')

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10

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

# Input source
process.load("VBFHiggsToInvisible.Samples.VBF_HToInv_M-125_13TeV_powheg-pythia6_pela-TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6_USER_cfi")

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(5)
)

process.hltPathStudies = cms.EDAnalyzer('HLTPathStudies',
                              
  verbose                    = cms.untracked.bool(True),  
  inputTag_HLTResults        = cms.untracked.InputTag("TriggerResults::HLT2"),

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
switchOnTrigger( process, path = 'p', hltProcess = 'HLT2',outputModule = 'out')
#switchOnTrigger( process, hltProcess = 'HLT2',outputModule = 'out')

process.p += process.hltPathStudies

#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process )                       
#process.patTrigger.saveL1Refs = cms.bool( False )
#process.patTrigger.hltProcess = cms.untracked.string('HLT2')
#switchOnTrigger( process )                       
    
process.e = cms.EndPath(process.out)