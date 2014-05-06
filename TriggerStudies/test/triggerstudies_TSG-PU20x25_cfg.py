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

process.load("VBFHiggsToInvisible.TriggerStudies.samples_tsg_PU20bx25_cfi")

process.trgEff = cms.EDAnalyzer('TriggerStudies',
                              
  verbose                    = cms.untracked.bool(True),
  doL1TAnalysis              = cms.untracked.bool(True),
  inputTag_L1GTReadoutRecord = cms.InputTag("gtDigis"),
  selL1Trigger               = cms.vstring("L1_ETM40",
                                           "L1_ETM50",
                                           "L1_HTT150",
                                           "L1_HTT175",
                                           "L1_HTT200"),
  
  doHLTAnalysis              = cms.untracked.bool(True),
  inputTag_HLTResults        = cms.InputTag("TriggerResults::HLT"),
  selHLTrigger               = cms.vstring("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",
                                           "HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v",
                                           "HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"),
  
)


process.p = cms.Path(process.trgEff)
