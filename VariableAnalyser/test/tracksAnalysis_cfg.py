import FWCore.ParameterSet.Config as cms

process = cms.Process("Tracks")

################################################################
### Messages
################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
                                       
################################################################
### Aligment and condition
################################################################                                       
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.GlobalTag.globaltag = cms.string('START53_V27::All')

################################################################
### Input files
################################################################
# MC POWHEG Signal VBF Higgs to Invisible mH=125 GeV 
# process.load("VBFHiggsToInvisible.Samples.Summer12_DR53X_VBF_HToInvisible_M-125_8TeV-powheg-pythia6_AODSIM_cfi")

# Local tests
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:/afs/cern.ch/user/p/pela/go/ws/public/42D9D6F7-3D80-E211-9AEC-00266CFFCCC8.root'))

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

#PAT has a hissy fit if this OutputModule isn't defined before we try and "removeMCMatching"
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),             
                               outputCommands = cms.untracked.vstring('drop *') #,*patEventContent )
                               )


################################################################
### Vertex Modules
################################################################
from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector
process.goodOfflinePrimaryVertices = cms.EDFilter("PrimaryVertexObjectFilter",
  filterParams = pvSelector.clone( minNdof = cms.double(4.0), maxZ = cms.double(24.0) ),
  src=cms.InputTag('offlinePrimaryVertices')
)

################################################################
### Start settting up the PAT default sequence
################################################################
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *
from PhysicsTools.PatAlgos.tools.tauTools import *
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.trigTools import *
from PhysicsTools.PatAlgos.tools.metTools import *
switchOnTrigger(process, outputModule="")

################################################################
### Configure PAT Jets
################################################################
switchJetCollection(process,
  cms.InputTag('ak5PFJets'),
  doJTA=True,
  doBTagging=True,
  jetCorrLabel=('AK5PF',['L1FastJet','L2Relative', 'L3Absolute']),
  doType1MET=True,
  genJetCollection=cms.InputTag("ak5GenJetsNoNuBSM"),
  doJetID = True,
  jetIdLabel = "ak5"
  )
process.patJets.embedGenPartonMatch = cms.bool(False)
# process.patJetsAK5PF.embedGenPartonMatch = cms.bool(False)
# process.selectedPatJets.cut = cms.string("pt>10. && abs(eta)<5.")

################################################################
### Set up METs
################################################################
from PhysicsTools.PatAlgos.tools.metTools import addPfMET
addPfMET(process, 'PF')

process.load("JetMETCorrections.Type1MET.pfMETCorrectionType0_cfi")
process.pfType1CorrectedMet.applyType0Corrections = cms.bool(False) #set to false because this module does track based corrections
process.pfType1CorrectedMet.srcType1Corrections = cms.VInputTag( #this section does pf based type0 corrections as recommended by workbookmetanalysis
  cms.InputTag('pfMETcorrType0'),
  cms.InputTag('pfJetMETcorr', 'type1')
  )

# Get PFMET from runMEtUncertainties
from PhysicsTools.PatUtils.tools.metUncertaintyTools import runMEtUncertainties
process.load("JetMETCorrections.Type1MET.pfMETsysShiftCorrections_cfi")

runMEtUncertainties(process,
                    electronCollection = cms.InputTag('cleanPatElectrons'),
                    photonCollection = '',
                    muonCollection = 'cleanPatMuons',
                    tauCollection = '',
                    jetCollection = cms.InputTag('selectedPatJets'),
                    jetCorrLabel = 'L3Absolute',
                    doSmearJets = True,
                    makeType1corrPFMEt = True,
                    makeType1p2corrPFMEt = False,
                    makePFMEtByMVA = False,
                    makeNoPileUpPFMEt = False,
                    doApplyType0corr = True,
                    #sysShiftCorrParameter = process.pfMEtSysShiftCorrParameters_2012runAvsNvtx_mc,
                    doApplySysShiftCorr = False,
                    )
process.producePatPFMETCorrections.replace(process.patPFJetMETtype2Corr,process.patPFJetMETtype2Corr + process.type0PFMEtCorrectionPFCandToVertexAssociation + process.patPFMETtype0Corr)

# Fix Type0 correction module
process.patPFMETtype0Corr.correction.par3 = cms.double(0.909209)
process.patPFMETtype0Corr.correction.par2 = cms.double(0.0303531)
process.patPFMETtype0Corr.correction.par1 = cms.double(-0.703151)
process.patPFMETtype0Corr.correction.par0 = cms.double(0.0)

################################################################
### MET Filters-curretly from Sasha's code
#################################################################
## The iso-based HBHE noise filter
process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')

## The ECAL dead cell trigger primitive filter
process.load('RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi')
process.EcalDeadCellTriggerPrimitiveFilter.taggingMode  = cms.bool(True)

## The EE bad SuperCrystal filter
process.load('RecoMET.METFilters.eeBadScFilter_cfi')
process.eeBadScFilter.taggingMode  = cms.bool(True)

## The Good vertices collection needed by the tracking failure filter
process.goodVertices = cms.EDFilter(
 "VertexSelector",
 filter = cms.bool(False),
 src = cms.InputTag("offlinePrimaryVertices"),
 cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.rho < 2")
)

## The tracking failure filter
process.load('RecoMET.METFilters.trackingFailureFilter_cfi')
process.trackingFailureFilter.taggingMode  = cms.bool(True)

process.load('RecoMET.METFilters.trackingPOGFilters_cff')
## NOTE: to make tagging mode of the tracking POG filters (three of them), please do:
process.manystripclus53X.taggedMode = cms.untracked.bool(True)
process.manystripclus53X.forcedValue = cms.untracked.bool(False)
process.toomanystripclus53X.taggedMode = cms.untracked.bool(True)
process.toomanystripclus53X.forcedValue = cms.untracked.bool(False)
process.logErrorTooManyClusters.taggedMode = cms.untracked.bool(True)
process.logErrorTooManyClusters.forcedValue = cms.untracked.bool(False)

### total sequence
process.filterSequence = cms.Sequence(
# # process.primaryVertexFilter *
# # process.noscraping *
  process.HBHENoiseFilterResultProducer
#  process.CSCTightHaloFilter *
#  process.MyhcalLaserEventFilter *
  +process.EcalDeadCellTriggerPrimitiveFilter
  +process.goodVertices + process.trackingFailureFilter
  +process.eeBadScFilter
#  process.MyecalLaserCorrFilter
# # process.hcallasereventfilter2012 
  +process.trkPOGFilters 
) 

from RecoJets.JetProducers.PileupJetID_cfi import *
stdalgos = cms.VPSet(full_53x,cutbased,PhilV1)
process.puJetMva = cms.EDProducer('PileupJetIdProducer',
                         produceJetIds = cms.bool(True),
                         jetids = cms.InputTag(""),
                         runMvas = cms.bool(True),
                         jets = cms.InputTag("ak5PFJets"),
                         vertexes = cms.InputTag("offlinePrimaryVertices"),
                         algos = cms.VPSet(stdalgos),
                         rho     = cms.InputTag("kt6PFJets","rho"),
                         jec     = cms.string("AK5PF"),
                         applyJec = cms.bool(True),
                         inputIsCorrected = cms.bool(False),                                     
                         residualsFromTxt = cms.bool(False),
                         residualsTxt     = cms.FileInPath("RecoJets/JetProducers/data/dummy.txt"))

################################################################
### Analysis
################################################################
process.tracksAnalyser = cms.EDAnalyzer('TracksAnalyser')

################################################################
### Sequence
################################################################
process.p = cms.Path(process.goodOfflinePrimaryVertices
                    +process.type0PFMEtCorrection
                    +process.patDefaultSequence
                    +process.puJetMva
                    +process.filterSequence
                    +process.tracksAnalyser)
