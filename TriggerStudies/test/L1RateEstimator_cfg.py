import FWCore.ParameterSet.Config as cms

process = cms.Process("TrgEff")

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
###############################################################

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( 'POSTLS162_V2::All' )
process.load("Configuration.StandardSequences.MagneticField_cff")

# standard unpacking sequence
process.load("Configuration.StandardSequences.RawToDigi_cff")                                                                                                                                                                                                                  

# For producing L1 Extra objects 
process.load("L1Trigger.L1ExtraFromDigis.l1extraParticles_cff")

process.RawToDigi.remove(process.csctfDigis)                                                                                                                                                                                                                                   
process.RawToDigi.remove(process.dttfDigis)                                                                                                                                                                                                                                    
#process.RawToDigi.remove(process.gctDigis)                                                                                                                                                                                                                                     
#process.RawToDigi.remove(process.gtDigis)                                                                                                                                                                                                                                     
process.RawToDigi.remove(process.gtEvmDigis)                                                                                                                                                                                                                                   
process.RawToDigi.remove(process.siPixelDigis)                                                                                                                                                                                                                                 
process.RawToDigi.remove(process.siStripDigis)                                                                                                                                                                                                                                 
process.RawToDigi.remove(process.ecalDigis)                                                                                                                                                                                                                                    
process.RawToDigi.remove(process.ecalPreshowerDigis)                                                                                                                                                                                                                           
process.RawToDigi.remove(process.hcalDigis)                                                                                                                                                                                                                                    
process.RawToDigi.remove(process.muonCSCDigis)                                                                                                                                                                                                                                 
process.RawToDigi.remove(process.muonDTDigis)                                                                                                                                                                                                                                  
process.RawToDigi.remove(process.muonRPCDigis)                                                                                                                                                                                                                                 
process.RawToDigi.remove(process.castorDigis)                                                                                                                                                                                                                                  
process.RawToDigi.remove(process.scalersRawToDigi)  

process.load("VBFHiggsToInvisible.TriggerStudies.samples_L1T_Neutrino_Pt-2to20_gun_Fall13dr-tsg_PU40bx50_POSTLS162_V1-v1_GEN-SIM-RAW_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.trgEff = cms.EDAnalyzer('L1RateEstimator',
                              
  verbose                    = cms.untracked.bool(True),
  doL1TAnalysis              = cms.untracked.bool(True),
  inputTag_L1GTReadoutRecord = cms.InputTag("gtDigis"),
  selL1Trigger               = cms.vstring("L1_ETM40",
                                           "L1_ETM50",
                                           "L1_HTT150",
                                           "L1_HTT175",
                                           "L1_HTT200"),
    
)

process.p = cms.Path(process.RawToDigi+process.l1extraParticles+process.trgEff)

