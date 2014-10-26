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

################################################################
### Output files
################################################################
process.trgStudies = cms.EDAnalyzer('L1TAdditionalRateStudies',

  verbose                    = cms.untracked.bool(False),
  #inputTag_L1GTReadoutRecord = cms.untracked.InputTag("gtDigis"),
  #inputTag_L1EmParticle_Isolated    = cms.untracked.InputTag("l1ExtraLayer2","Isolated"   ),
  #inputTag_L1EmParticle_NonIsolated = cms.untracked.InputTag("l1ExtraLayer2","NonIsolated"),
  #inputTag_L1EtMissParticle_MET     = cms.untracked.InputTag("l1ExtraLayer2","MET"        ),
  #inputTag_L1EtMissParticle_MHT     = cms.untracked.InputTag("l1ExtraLayer2","MHT"        ),
  #inputTag_L1HFRings                = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  #inputTag_L1JetParticle_Central    = cms.untracked.InputTag("l1ExtraLayer2","Central"    ),
  #inputTag_L1JetParticle_Forward    = cms.untracked.InputTag("l1ExtraLayer2","Forward"    ),
  #inputTag_L1JetParticle_Tau        = cms.untracked.InputTag("l1ExtraLayer2","Tau"        ),
  #inputTag_L1MuonParticle           = cms.untracked.InputTag("l1ExtraLayer2",""           ),
  #inputTag_HLTResults               = cms.untracked.InputTag("TriggerResults::HLT"),

  inputTagL1GtDataDaq = cms.InputTag("simGtDigis"),

  outputFilename = cms.untracked.string("L1TAdditionalRateStudiesResults.root"),

)

process.p = cms.Path(
  process.trgStudies
)

