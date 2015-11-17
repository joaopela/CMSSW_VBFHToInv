import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'analysis'  options
options = VarParsing.VarParsing ('analysis')

options.inputFiles = ''
options.outputFile = ''
options.maxEvents  = -1

# get and parse the command line arguments
options.parseArguments()

#print os.path.splitext(inputLHE)[0]
#sys.exit()

import FWCore.ParameterSet.Config as cms

process = cms.Process('FILTER')
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.source = cms.Source ("PoolSource",
  fileNames  = cms.untracked.vstring (options.inputFiles),
)

process.load("CMSSW_VBFHToInv.GenFilters.VBFGenJetFilter_cff")

from CMSSW_VBFHToInv.Study_RunII_SampleProd_QCD_VBFMET.GenFilterAnalyzer_cfi import *
process.genFilterAnalyzer                           = genFilterAnalyzer
process.genFilterAnalyzer.outFile                   = cms.untracked.string('test2.root')
process.genFilterAnalyzer.inputTag_GenJetCollection = cms.untracked.InputTag('ak4GenJetsNoNu')

#This parts of the sequence are not necessary since they were already done in test files
process.vbfGenJetFilterASeq.remove(process.genParticlesForJetsNoNu)
process.vbfGenJetFilterASeq.remove(process.ak4GenJetsNoNu)
process.vbfGenJetFilterBSeq.remove(process.genParticlesForJetsNoNu)
process.vbfGenJetFilterBSeq.remove(process.ak4GenJetsNoNu)
process.vbfGenJetFilterCSeq.remove(process.genParticlesForJetsNoNu)
process.vbfGenJetFilterCSeq.remove(process.ak4GenJetsNoNu)

process.filterA = cms.Path(
  process.vbfGenJetFilterASeq
  #*process.genFilterAnalyzer
)

process.filterB = cms.Path(
  process.vbfGenJetFilterBSeq
  #*process.genFilterAnalyzer
)

process.filterC = cms.Path(
  process.vbfGenJetFilterCSeq
  #*process.genFilterAnalyzer
)

#process.output = cms.OutputModule("PoolOutputModule",
    #SelectEvents = cms.untracked.PSet(
        #SelectEvents = cms.vstring('p')
    #),
    #dataset = cms.untracked.PSet(
        #dataTier = cms.untracked.string('GEN-SIM-RAW'),
        #filterName = cms.untracked.string('')
    #),
    #eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    #fileName = cms.untracked.string(options.outputFile ),
    #splitLevel = cms.untracked.int32(0)
#)
    
#process.output_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(
  process.filterA,
  process.filterB,
  process.filterC,
  #process.output_step
)