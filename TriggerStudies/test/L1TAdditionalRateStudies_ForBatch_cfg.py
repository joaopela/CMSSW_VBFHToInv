import FWCore.ParameterSet.Config as cms

process = cms.Process("L1TAdditionalRateStudies")

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
process.GlobalTag.globaltag = cms.string( 'MCRUN2_72_V1A::All' )

process.load('L1TriggerConfig.L1GtConfigProducers.l1GtTriggerMenuXml_cfi')
process.l1GtTriggerMenuXml.TriggerMenuLuminosity = cms.string("startup")
process.l1GtTriggerMenuXml.DefXmlFile = cms.string("L1Menu_Collisions2015_25ns_v1_L1T_Scales_20101224_Imp0_0x102f.xml")
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMenuConfig_cff')
process.es_prefer_l1GtParameters = cms.ESPrefer('L1GtTriggerMenuXmlProducer','l1GtTriggerMenuXml')

################################################################
### Output files
################################################################
process.trgStudies = cms.EDAnalyzer('L1TAdditionalRateStudies',

  verbose                    = cms.untracked.bool(False),
  #inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("hltL1extraParticles","Isolated"   ),
  inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("hltL1extraParticles","NonIsolated"),
  inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("hltL1extraParticles","MET"        ),
  inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("hltL1extraParticles","MHT"        ),
  inputTag_L1HFRings                = cms.untracked.InputTag("hltL1extraParticles",""           ),
  inputTag_L1JetParticle_Central    = cms.untracked.InputTag("hltL1extraParticles","Central"    ),
  inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("hltL1extraParticles","Forward"    ),
  inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("hltL1extraParticles","Tau"        ),
  inputTag_L1MuonParticle           = cms.untracked.InputTag("hltL1extraParticles",""           ),

  inputTagL1GtDataDaq = cms.InputTag("simGtDigis"),

  outputFilename = cms.untracked.string("L1TAdditionalRateStudiesResults.root"),

)

process.p = cms.Path(
  process.trgStudies
)

