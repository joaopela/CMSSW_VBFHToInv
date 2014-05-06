import FWCore.ParameterSet.Config as cms

process = cms.Process("Tracks")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("VBFHiggsToInvisible.Samples.Summer12_DR53X_VBF_HToInvisible_M-125_8TeV-powheg-pythia6_AODSIM_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.tracksAnalyser = cms.EDAnalyzer('TracksAnalyser')

process.p = cms.Path(process.tracksAnalyser)
