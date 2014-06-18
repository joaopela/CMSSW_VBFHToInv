import FWCore.ParameterSet.Config as cms

process = cms.Process("TrgEff")

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
################################################################

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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.trgEff = cms.EDAnalyzer('L1RateEstimator',
                              
  verbose                    = cms.untracked.bool(True),
  inputTag_L1GTReadoutRecord = cms.InputTag("gtDigis"),
  
  inputTag_HLTResults        = cms.InputTag("TriggerResults::HLT"),
  selHLTrigger               = cms.vstring("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",
                                           "HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v",
                                           "HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"),
  
)

process.p = cms.Path(process.RawToDigi+process.l1extraParticles+process.trgEff)

