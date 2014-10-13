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

################################################################
### Output files
################################################################
process.trgCount = cms.EDAnalyzer('TrigStudies',

  verbose                    = cms.untracked.bool(False),
  inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ),
  inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  inputTag_HLTResults               = cms.untracked.InputTag("TriggerResults::HLT"),

  outputFilename = cms.untracked.string("TrigStudiesResults.root"),

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
    "L1_DoubleJet30_Mjj400_ETM40"
  ),

)

process.trgEff = cms.EDAnalyzer('L1AlgoWPStudies',
                              
  verbose                    = cms.untracked.bool(False),
  inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ),
  inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ),


  outputFilename = cms.untracked.string("L1AlgoWPStudiesResults.root"),  
)

process.p = cms.Path(
  process.trgCount+
  process.trgEff
)

#process.e = cms.EndPath(process.out)