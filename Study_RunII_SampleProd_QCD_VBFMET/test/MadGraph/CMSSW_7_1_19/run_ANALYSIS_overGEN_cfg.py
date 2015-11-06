# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/python/Hadronizer_TuneCUETP8M1_13TeV_MLM_5f_max4j_LHE_pythia8_cff.py --filein file:unweighted_events.lhe --fileout file:lheSIM.root --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/StandardSequences/SimWithCastor_cff.customise --datatier GEN-SIM --conditions MCRUN2_71_V1::All --step GEN,SIM --magField 38T_PostLS1 --geometry Extended2015 --python_filename processLHE_cfg.py --no_exec -n 10

import FWCore.ParameterSet.VarParsing as VarParsing

# setup 'analysis'  options
options = VarParsing.VarParsing ('analysis')

options.register ('dijetPt',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.float,          # string, int, or float
                  "Dijet minimum pT (default 0)")
options.register ('dijetEta',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.float,          # string, int, or float
                  "Dijet minimum eta (default 0)")
options.register ('dijetMjj',
                  0, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.float,          # string, int, or float
                  "Dijet minimum mjj (default 0)")


# setup any defaults you want
options.inputFiles = 'CMSSW_7_1_18_Hadronizer_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root'
options.outputFile = 'PartonGenJetAnalyzer_Results_mg5_pp_jj_etaj4p8_ptj1min30_ptj2min30_mmjj800_unweighted_events.root'
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
  fileNames          = cms.untracked.vstring (options.inputFiles),
  duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
)

process.analyzer = cms.EDAnalyzer('PartonGenJetAnalyzer',
  dijet_pt       = cms.untracked.double(options.dijetPt),
  dijet_eta      = cms.untracked.double(options.dijetEta),
  dijet_mjj      = cms.untracked.double(options.dijetMjj),
  outputFilename = cms.untracked.string(options.outputFile)
)

# Path and EndPath definitions
process.analysis = cms.Path(
  process.analyzer
)
