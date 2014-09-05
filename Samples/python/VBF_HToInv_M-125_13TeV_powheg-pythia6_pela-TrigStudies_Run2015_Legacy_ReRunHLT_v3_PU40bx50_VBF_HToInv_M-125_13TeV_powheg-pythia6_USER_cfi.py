import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_10_1_eCZ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_11_1_TlL.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_12_1_dtm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_13_1_YLX.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_14_1_Rjd.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_15_1_OZC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_16_2_GRj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_17_1_Dgj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_18_1_EH4.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_19_1_FNo.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_1_1_AQl.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_20_1_vda.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_21_1_WRL.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_22_1_xst.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_23_1_obr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_24_1_PC0.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_25_1_NVg.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_26_1_LQd.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_27_1_he7.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_28_1_aKQ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_29_1_6Zr.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_2_1_q6m.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_30_1_YWC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_31_1_72M.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_32_1_UA6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_33_1_HND.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_34_1_vw8.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_35_1_2AC.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_36_2_4dx.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_37_2_lmO.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_38_1_dr6.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_39_1_mev.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_3_1_Ox2.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_40_1_Yzj.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_4_1_tDa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_5_1_PLe.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_6_1_gUu.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_7_1_K0j.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_8_2_Dxa.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies_Run2015_Legacy_ReRunHLT_v3_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/b711fcbbcd48b139822e91d84ed45ea9/hltReRunResults_9_1_3rI.root' ] );


secFiles.extend( [
               ] )

