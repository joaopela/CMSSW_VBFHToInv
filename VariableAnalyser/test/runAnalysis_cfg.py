import FWCore.ParameterSet.Config as cms

process = cms.Process("AnalysisTracks")

################################################################
### Messages
################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

################################################################
### Aligment and condition
################################################################                                       
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.GlobalTag.globaltag = cms.string('START53_V27::All')

################################################################
### Input files
################################################################

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:/tmp/pela/ntupleTracksV0.root'))
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

################################################################
### Output files
################################################################
process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string("TracksAnalysis.root"),
                                   closeFileFast = cms.untracked.bool(True) # Needs to be disabled if there are multiple references to same object (ex: TCanvas to TH1D)
                                   )

################################################################
### Analysis
################################################################
process.tracksAnalyser = cms.EDAnalyzer('TracksAnalyser')

################################################################
### Sequence
################################################################
process.p = cms.Path(process.tracksAnalyser)