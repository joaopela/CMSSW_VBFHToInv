# /dev/CMSSW_7_4_0/GRun/V79 (CMSSW_7_4_3)

import FWCore.ParameterSet.Config as cms

process = cms.Process( "RUN" )

###############################################################
# START: HLT Simple Analysis
###############################################################
process.hltAnalysis = cms.EDAnalyzer('HLTSimpleAnalyser',

  inputTag_HLTResults        = cms.untracked.InputTag("TriggerResults::TEST"),
  
  HLTPaths  = cms.vstring(
    "HLT_PFMET170_NoiseCleaned_v2",
    "HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_v2",
    "HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_v2",
    "HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu80_extra"
  ), 

  outputFilename = cms.untracked.string("HLTSimpleAnalysis.root"),

)
###############################################################
# END: HLT Simple Analysis
###############################################################

process.HLTanalysis = cms.Path(process.hltAnalysis)
process.HLTSchedule = cms.Schedule(process.HLTanalysis)


###############################################################
# BEGIN: Running over the signal sample with PU20bx25
###############################################################
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_1.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_10.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_11.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_12.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_13.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_14.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_15.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_16.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_17.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_18.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_19.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_2.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_20.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_3.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_4.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_5.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_6.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_7.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_8.root',
    '/store/user/pela/2015/Trigger_RunII_HLT_dev_CMSSW_7_4_0_GRun_V79/HCALMethod0/VBF_HToInv_M-125_13TeV_powheg-pythia6/crab_VBF_HToInv_M-125_PU20bx25/150624_114844/0000/hltReRunResults_9.root' 
  ),
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

###############################################################
# END: Running over the signal sample with PU20bx25
###############################################################

