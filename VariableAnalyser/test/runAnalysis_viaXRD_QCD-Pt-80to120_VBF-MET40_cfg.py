import FWCore.ParameterSet.Config as cms

process = cms.Process("AnalysisTracks")

################################################################
### Messages
################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
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
# MC Signal
process.load("VBFHiggsToInvisible.VariableAnalyser.TrackNtuplesWithPv_v2_QCD-Pt-80to120_VBF-MET40_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

# MC VBF QCD pt 470 to 600 GeV ntupleTracks version 0 (with PV cut)
#process.load("VBFHiggsToInvisible.VariableAnalyser.VBFQCD_Pt_470to600_ntupleTracksV0_cfi")
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Local file
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://gfe02.grid.hep.ph.ic.ac.uk:1097//store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/ntupleTracksV0_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_11_1_oF3.root'))
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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
