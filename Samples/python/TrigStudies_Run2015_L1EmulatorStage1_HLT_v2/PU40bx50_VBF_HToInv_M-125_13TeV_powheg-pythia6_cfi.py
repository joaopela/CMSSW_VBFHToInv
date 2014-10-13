import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_10_1_PRb.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_11_1_0Mm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_12_1_AeC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_13_1_9s4.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_14_1_v9U.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_15_2_2Kv.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_16_1_RaX.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_17_1_BYE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_18_1_tMl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_19_2_gVj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_1_1_Ed1.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_20_1_1hz.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_21_1_XiF.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_22_1_vsk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_23_1_wlf.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_24_1_BYb.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_25_1_nPT.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_26_1_DVo.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_27_1_R8U.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_28_1_j2O.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_29_1_l73.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_2_1_BYT.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_30_1_chg.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_31_1_lZr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_32_1_sRK.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_33_1_qnE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_34_1_Wbv.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_35_1_ozR.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_36_1_teR.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_37_1_deJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_38_1_1gx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_39_1_gXl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_3_1_83S.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_40_1_3Cy.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_4_1_qXk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_5_1_XTS.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_6_1_Rap.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_7_1_2fm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_8_1_84F.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1EmulatorStage1_HLT_v2_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/740729526d0c0f1eb16eda620a6cff9a/outputA_9_1_sBQ.root' ] );


secFiles.extend( [
               ] )
