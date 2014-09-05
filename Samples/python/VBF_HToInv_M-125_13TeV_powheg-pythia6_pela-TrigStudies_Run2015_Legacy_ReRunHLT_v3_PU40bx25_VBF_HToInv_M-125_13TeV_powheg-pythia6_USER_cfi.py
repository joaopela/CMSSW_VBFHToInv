import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_10_1_rLl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_11_1_bEG.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_12_1_8vf.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_13_1_pB1.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_14_1_BXq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_15_1_jME.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_16_1_L9a.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_17_1_Vfl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_18_1_DJl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_19_1_2Gq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_1_1_U3G.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_20_1_9Kc.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_21_1_TFJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_22_1_e0o.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_23_1_0Sr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_24_1_3NY.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_25_1_IgJ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_26_1_HBI.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_27_1_Ss8.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_28_1_ZF6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_29_1_M7H.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_2_1_zl5.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_30_1_ASl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_31_1_KtB.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_32_1_Kgc.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_33_1_VkY.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_34_2_W3n.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_35_1_cJq.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_36_1_uvz.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_37_1_AgE.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_38_1_uJM.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_39_1_Yzl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_3_1_Jxa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_40_1_nDO.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_41_1_HMx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_42_1_j6r.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_4_1_DI6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_5_1_d3F.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_6_1_M8M.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_7_1_gij.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_8_1_yLx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_9_1_Jk2.root' ] );


secFiles.extend( [
               ] )

