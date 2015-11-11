import FWCore.ParameterSet.Config as cms

vbfGenJetFilter = cms.EDFilter("VBFGenJetFilter",

  inputTag_GenJetCollection = cms.untracked.InputTag('ak4GenJetsNoNu'),

  minPt       = cms.untracked.double(    40),
  minEta      = cms.untracked.double(  -4.8),
  maxEta      = cms.untracked.double(   4.8),
  minInvMass  = cms.untracked.double( 1000.),
  maxInvMass  = cms.untracked.double(99999.),
  minDeltaPhi = cms.untracked.double(  -1.0),
  maxDeltaPhi = cms.untracked.double(  2.15),
  minDeltaEta = cms.untracked.double(   3.0),
  maxDeltaEta = cms.untracked.double(99999.)

)