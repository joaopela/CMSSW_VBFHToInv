import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_10_1_fgr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_11_1_sBJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_12_1_H96.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_13_1_pqq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_14_1_sKh.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_15_1_CZ5.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_16_1_W1d.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_17_1_JSw.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_18_1_Aka.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_19_1_FKq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_1_1_MS6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_20_1_jk6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_21_1_wTM.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_22_1_Cet.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_23_1_CvJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_24_1_sRI.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_25_2_vBV.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_26_1_U7o.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_27_1_VKe.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_28_1_H2R.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_29_2_31r.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_2_1_5Tl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_30_1_pop.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_31_1_Ya4.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_32_1_zNo.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_33_1_nE0.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_34_1_Gih.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_35_1_jMs.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_36_1_z4B.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_37_1_KAV.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_38_1_dsk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_39_1_vRd.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_3_1_oe3.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_40_1_kLC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_41_1_r34.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_42_2_0hp.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_4_1_SHX.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_5_1_XPR.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_6_1_QJ3.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_7_1_epm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_8_1_QF1.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_L1Emulator_Stage1_v1_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/657ce3a53d042b7adaca883baf22ba33/SimL1Emulator_Stage1_PP_9_1_sGm.root' ] );


secFiles.extend( [
               ] )
