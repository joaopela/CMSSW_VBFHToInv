import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_10_1_IHC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_11_1_iNr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_12_1_DFK.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_13_1_GNN.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_14_1_5rr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_15_1_2iL.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_16_1_wiO.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_17_1_2Uf.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_18_1_BGQ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_19_1_dPn.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_1_2_bts.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_20_1_gNj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_21_1_6UP.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_22_1_2iF.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_23_1_OiM.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_24_1_UWi.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_25_1_XKI.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_26_1_kmj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_27_1_q0s.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_28_1_odT.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_29_1_mN0.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_2_1_qPG.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_30_1_JV9.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_31_1_JJa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_32_1_T87.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_33_1_L7H.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_34_2_5bT.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_35_1_vYG.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_36_1_35t.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_37_1_4xe.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_38_1_S51.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_39_1_1KH.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_3_1_JMa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_4_1_Cl9.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_5_1_oBT.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_6_1_lvD.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_7_1_b3C.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_8_1_6Sw.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU20bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_9_1_kgZ.root' ] );


secFiles.extend( [
               ] )

