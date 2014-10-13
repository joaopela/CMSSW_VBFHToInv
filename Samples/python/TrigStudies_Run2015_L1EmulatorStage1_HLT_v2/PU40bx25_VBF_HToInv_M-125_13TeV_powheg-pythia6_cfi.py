import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_10_1_RPA.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_11_1_vr3.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_12_1_BSE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_13_1_JDw.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_14_1_40n.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_15_1_wNG.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_16_1_w2E.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_17_1_cjW.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_18_1_jiM.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_19_1_r1H.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_1_1_oJE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_20_1_C8w.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_21_1_1My.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_22_1_BF9.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_23_1_WW1.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_24_1_X8R.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_25_1_vIn.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_26_1_zJi.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_27_1_Lv3.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_28_1_Ue0.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_29_1_f6H.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_2_1_5qK.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_30_1_Z2O.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_31_1_bjk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_32_1_m7f.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_33_1_Nh0.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_34_1_J2P.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_35_1_TYg.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_36_1_XXW.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_37_1_tbl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_38_1_lBi.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_39_1_FAf.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_3_1_l7w.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_40_1_RCx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_41_1_aBU.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_42_1_OJR.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_4_1_j8g.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_5_1_upW.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_6_1_oIl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_7_1_IMc.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_8_1_Wqm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_9_1_s20.root' ] );


secFiles.extend( [
               ] )
