import FWCore.ParameterSet.Config as cms

offlineFilterAnalyzer = cms.EDAnalyzer('OfflineFilterAnalyzer',

  verbose                   = cms.untracked.bool(False),
  inputTag_HepMCProduct     = cms.untracked.InputTag("generator"),
  inputTag_GenJetCollection = cms.untracked.InputTag("ak5GenJetsNoNu"),
  inputTag_L1Extra_mets     = cms.untracked.InputTag("hltL1extraParticles","MET"),
  inputTag_HLTResults       = cms.untracked.InputTag("TriggerResults::HLT"),
  outputFilename            = cms.untracked.string('OfflineFilterAnalyzer_Results.root'),
)
