import FWCore.ParameterSet.Config as cms

process = cms.Process("TrgEffoverL1Extra")

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True )
)
################################################################

process.load("Configuration.Geometry.GeometryExtended2015Reco_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_PostLS1_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string( 'POSTLS162_V6::All' )
#process.GlobalTag.globaltag = cms.string( 'POSTLS162_V2::All' )

# In MC HCAL need to be re-run as there is no TPG information stored
#process.load("SimCalorimetry.HcalSimProducers.hcalUnsuppressedDigis_cfi")
#process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")

#from L1Trigger.RegionalCaloTrigger.rctDigis_cfi import rctDigis
#from L1Trigger.GlobalCaloTrigger.gctDigis_cfi import gctDigis

#process.hcalReEmulDigis = process.simHcalTriggerPrimitiveDigis.clone()
#process.rctReEmulDigis  = rctDigis.clone()
#process.gctReEmulDigis  = gctDigis.clone()

#process.hcalReEmulDigis.inputLabel = cms.VInputTag(cms.InputTag('hcalDigis'), cms.InputTag('hcalDigis'))
#process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(False)

#process.rctReEmulDigis.ecalDigis = cms.VInputTag( cms.InputTag( 'ecalDigis:EcalTriggerPrimitives' ) )
#process.rctReEmulDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'hcalReEmulDigis' ) )

#process.gctReEmulDigis.inputLabel  = cms.InputTag("rctReEmulDigis")


process.load("Configuration.StandardSequences.L1HwVal_cff")
#process.load("SLHCUpgradeSimulations.L1CaloTrigger.SLHCCaloTrigger_cff")

#process.load('L1TriggerConfig.GctConfigProducers.L1GctConfig_cff')
#process.L1GctConfigProducers.CalibrationStyle = cms.string('None')

process.load("VBFHiggsToInvisible.Samples.Neutrino_Pt-2to20_gun_pela-TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_Neutrino_Pt-2to20_gun_USER_cfi")

#process.source = cms.Source("PoolSource",
  #fileNames = cms.untracked.vstring(
    #'/store/mc/Fall13dr/VBF_HToBB_M-125_13TeV-powheg-pythia6/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/00000/004EE9D6-EF6C-E311-968E-848F69FD29D6.root',
    ##'/store/mc/Fall13dr/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM-RAW/tsg_PU20bx25_POSTLS162_V2-v1/00000/001A6D13-E16C-E311-BE56-00266CFAE7C4.root',
    ##"file:/afs/cern.ch/user/p/pela/go/ws/public/samples/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/00114E14-0877-E311-B33A-003048678F74.root",
  #),
#)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

################################################################
### Output files
################################################################
#process.out = cms.OutputModule("PoolOutputModule",
                               #fileName = cms.untracked.string('file:test.root'),
                               #SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),             
                               #outputCommands = cms.untracked.vstring('keep *')
                               #)

process.trgCount = cms.EDAnalyzer('TrigStudies',
                              
  verbose                    = cms.untracked.bool(False),
  inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ,"L1TEMULATION"),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated","L1TEMULATION"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ,"L1TEMULATION"),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ,"L1TEMULATION"),
  inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ,"L1TEMULATION"),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ,"L1TEMULATION"),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ,"L1TEMULATION"),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ,"L1TEMULATION"),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ,"L1TEMULATION"),
  inputTag_HLTResults        = cms.untracked.InputTag("TriggerResults::HLT"),


  outputFilename = cms.untracked.string("TrigStudiesResults_L1TEmuStage1_NeutrinoGun_PU40bx25.root"),

  selHLTrigger               = cms.vstring("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu75_MJJ800VBF_AllJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu75_MJJ600VBF_LeadingJets_v",                                          
                                           "HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v",
                                           "HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"),
  
  runAlgoTester   = cms.untracked.bool(True),
  algoTesterAlgos = cms.vstring(
    "L1_ETM40",
    "L1_ETM45",
    "L1_ETM50",
    "L1_ETM55",
    "L1_ETM60",
    "L1_ETM65",
    "L1_ETM70",
    "L1_ETM75",
    "L1_ETM80",
    "L1_DoubleJetC60_ETM60",
    "L1_DoubleJet60_ETM60",
    "L1_DoubleJet40_DEta3p0_ETM40",
    "L1_DoubleVBFJet40_DEta3p0_ETM40",
    "L1_DoubleJet30_Mjj400_ETM40"),

)

process.trgEff = cms.EDAnalyzer('L1AlgoWPStudies',
                              
  verbose                    = cms.untracked.bool(False),
  inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ,"L1TEMULATION"),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated","L1TEMULATION"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ,"L1TEMULATION"),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ,"L1TEMULATION"),
  inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ,"L1TEMULATION"),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ,"L1TEMULATION"),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ,"L1TEMULATION"),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ,"L1TEMULATION"),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ,"L1TEMULATION"),


  outputFilename = cms.untracked.string("L1AlgoWPStudiesResults_L1TEmuStage1_NeutrinoGun_PU40bx25.root"),  
)

process.p = cms.Path(
  process.trgCount+
  process.trgEff
)

#process.e = cms.EndPath(process.out)