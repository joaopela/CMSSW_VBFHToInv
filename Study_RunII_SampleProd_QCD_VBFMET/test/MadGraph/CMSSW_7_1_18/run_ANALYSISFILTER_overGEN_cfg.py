import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'analysis'  options
options = VarParsing.VarParsing ('analysis')

# setup any defaults you want
options.inputFiles = 'mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.lhe'
options.outputFile = 'CMSSW_7_1_18_Hadronizer_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root'
options.maxEvents  = -1

# get and parse the command line arguments
options.parseArguments()

#print os.path.splitext(inputLHE)[0]
#sys.exit()

import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYSIS')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.source = cms.Source ("PoolSource",
  fileNames  = cms.untracked.vstring (options.inputFiles),
)

from CMSSW_VBFHToInv.Study_RunII_SampleProd_QCD_VBFMET.GenFilterAnalyzer_cfi import *
process.genFilterAnalyzer                           = genFilterAnalyzer
process.genFilterAnalyzer.outFile                   = cms.untracked.string(options.outputFile)
process.genFilterAnalyzer.inputTag_GenJetCollection = cms.untracked.InputTag('ak4GenJetsNoNu')

# Path and EndPath definitions
process.analysis = cms.Path(
  process.genFilterAnalyzer
)