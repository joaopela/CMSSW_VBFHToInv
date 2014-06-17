import FWCore.ParameterSet.Config as cms

process = cms.Process("TrgEff")

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
###############################################################

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( 'POSTLS162_V2::All' )
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("VBFHiggsToInvisible.TriggerStudies.samples_L1T_Neutrino_Pt-2to20_gun_Fall13dr-tsg_PU20bx25_POSTLS162_V2-v1_AODSIM_cfi")

process.trgEff = cms.EDAnalyzer('L1RateEstimator',
                              
  verbose                    = cms.untracked.bool(True),
  doL1TAnalysis              = cms.untracked.bool(True),
  inputTag_L1GTReadoutRecord = cms.InputTag("gtDigis"),
  selL1Trigger               = cms.vstring("L1_ETM40",
                                           "L1_ETM50",
                                           "L1_HTT150",
                                           "L1_HTT175",
                                           "L1_HTT200"),
    
)


process.p = cms.Path(process.trgEff)
