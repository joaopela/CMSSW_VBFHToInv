# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/BTV-Fall13-00043-fragment.py --fileout file:QCD_Pt-50to80_step1.root --mc --eventcontent RAWSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1,Configuration/StandardSequences/SimWithCastor_cff.customise,Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --pileup_input dbs:/MinBias_TuneA2MB_13TeV-pythia8/Fall13-POSTLS162_V1-v1/GEN-SIM --pileup AVE_35_BX_50ns,{"N":30} --conditions PHYS14_ST_V1 --step GEN,SIM,DIGI,L1,DIGI2RAW,HLT:GRun --magField 38T_PostLS1 --geometry Extended2015 --python_filename QCD_Pt-50to80_step1_cfg.py --no_exec -n 100
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_POISSON_average_cfi')
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2015_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

###############################################################
# START: Extra block for job making
###############################################################
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

# Input source
process.source = cms.Source("EmptySource",
  firstRun            =cms.untracked.uint32(1),
  firstLuminosityBlock=cms.untracked.uint32(JOBNUMBER)
)


process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
  generator = cms.PSet(              # 900000000
    initialSeed = cms.untracked.uint32(JOBNUMBER),
    engineName = cms.untracked.string('HepJamesRandom')
  )
)
###############################################################
# END: Extra block for job making
###############################################################

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('\\$Revision: 1.1 $'),
    annotation = cms.untracked.string('Fall13 sample with PYTHIA8: QCD dijet production, pThat = 50 .. 80 GeV, Tune4C')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('file:QCD_Pt-50to80_step1.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.mix.input.nbPileupEvents.averageNumber = cms.double(30.000000)
process.mix.bunchspace = cms.int32(50)
process.mix.minBunch = cms.int32(-12)
process.mix.maxBunch = cms.int32(3)
process.mix.input.fileNames = cms.untracked.vstring(['/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/001CB469-A91E-E311-9BFE-0025907FD24A.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/009CB248-A81C-E311-ACD8-00259073E4F0.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/009F81D5-B21C-E311-966C-BCAEC50971D0.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/00B5BB8C-A91E-E311-816A-782BCB1F5E6B.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/00B8F676-BA1C-E311-BA87-0019B9CABFB6.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/00DD7446-B51D-E311-B714-001E6739CEB1.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/021E1B53-101D-E311-886F-00145EDD7569.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/022A782D-A51C-E311-9856-80000048FE80.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/026FE678-BA1C-E311-BEF5-00D0680BF90A.root', '/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/10000/02A10BDE-B21C-E311-AB59-00266CF327C0.root'])
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'PHYS14_ST_V1', '')

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(13000.0),
    crossSection = cms.untracked.double(175007.8),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
        processParameters = cms.vstring('Main:timesAllowErrors    = 10000', 
            'ParticleDecays:limitTau0 = on', 
            'ParticleDecays:tauMax = 10', 
            'HardQCD:all = on', 
            'PhaseSpace:pTHatMin = 50 ', 
            'PhaseSpace:pTHatMax = 80 ', 
            'Tune:pp 5', 
            'Tune:ee 3'),
        parameterSets = cms.vstring('processParameters')
    )
)

# Generator level event filter definition
from Study_RunII_SampleProd_QCD_VBFMET.SampleProduction.GenFilterAnalyzer_cfi import *
process.genFilterAnalyzer                           = genFilterAnalyzer
process.genFilterAnalyzer.outFile                   = cms.untracked.string('GenFilterAnalyzer_QCD_Pt-50to80_'+str(JOBNUMBER)+'.root')
process.genFilterAnalyzer.inputTag_GenJetCollection = cms.untracked.InputTag('ak4GenJetsNoNu')

# Path and EndPath definitions
#process.generation_step = cms.Path(process.pgen)
process.generation_step = cms.Path(
  process.generator*
  process.genParticles*
  process.genParticlesForJetsNoNu*
  process.ak4GenJetsNoNu*
  process.genFilterAnalyzer
)
process.simulation_step       = cms.Path(process.psim)
process.digitisation_step     = cms.Path(process.pdigi)
process.L1simulation_step     = cms.Path(process.SimL1Emulator)
process.digi2raw_step         = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step           = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step     = cms.EndPath(process.RAWSIMoutput)

# Schedule definition

# REMOVING FOR TESTING
#process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
#process.schedule.extend(process.HLTSchedule)

process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step)
#process.schedule.extend([process.endjob_step,process.RAWSIMoutput_step])
#process.schedule.extend([process.endjob_step])

# filter all path with the production filter sequence
#for path in process.paths:
        #getattr(process,path)._seq = process.generator *process.genParticles *process.genParticlesForJetsNoNu *process.ak5GenJetsNoNu *process.genFilterAnalyzer * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# Automatic addition of the customisation function from Configuration.StandardSequences.SimWithCastor_cff
from Configuration.StandardSequences.SimWithCastor_cff import customise 

#call to customisation function customise imported from Configuration.StandardSequences.SimWithCastor_cff
process = customise(process)

# End of customisation functions

process.generation_step.remove(process.randomEngineStateProducer)
process.generation_step.remove(process.VtxSmeared)
process.generation_step.remove(process.genParticlesForJets)
process.generation_step.remove(process.kt4GenJets)
process.generation_step.remove(process.kt6GenJets)
process.generation_step.remove(process.iterativeCone5GenJets)
process.generation_step.remove(process.ak4GenJets)
process.generation_step.remove(process.ak5GenJets)
process.generation_step.remove(process.ak8GenJets)
process.generation_step.remove(process.genCandidatesForMET)
process.generation_step.remove(process.genParticlesForMETAllVisible)
process.generation_step.remove(process.genMetCalo)
process.generation_step.remove(process.genMetCaloAndNonPrompt)
process.generation_step.remove(process.genMetTrue)
process.generation_step.remove(process.genMetIC5GenJets)
