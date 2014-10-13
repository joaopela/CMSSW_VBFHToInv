import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_10_1_1Em.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_11_1_Pqu.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_12_1_APx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_13_1_VYa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_14_1_UiK.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_15_1_tcz.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_16_1_RCN.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_17_1_OFS.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_18_1_229.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_19_1_HCF.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_1_1_79t.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_20_1_4PJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_21_1_aeM.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_22_1_dWb.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_23_1_DMQ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_24_1_i4r.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_25_1_K2y.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_26_1_gNE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_27_1_epd.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_28_1_yAG.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_29_1_IWD.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_2_1_rFE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_30_1_3mc.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_31_1_WIQ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_32_1_ko7.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_33_1_0YX.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_34_1_JCA.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_35_1_Pb5.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_36_1_uqw.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_37_1_A1Y.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_38_1_UFF.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_39_1_iMr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_3_1_R7Y.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_4_1_WHq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_5_1_wFl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_6_1_L7r.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_7_1_uHs.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_8_1_6M7.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_9_1_hml.root' ] );


secFiles.extend( [
               ] )
