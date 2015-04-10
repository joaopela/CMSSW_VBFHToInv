import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_10_1_3uh.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_11_1_EnF.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_12_1_IRa.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_13_1_A7f.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_14_1_NCB.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_15_1_yh7.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_16_1_eV8.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_17_1_VoI.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_18_1_3Kz.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_19_1_UmC.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_1_1_k3A.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_20_1_OIn.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_21_1_VCS.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_22_1_UfX.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_23_1_Y4O.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_24_1_IDH.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_25_1_4lg.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_26_1_Yni.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_27_1_oJo.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_2_1_aiU.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_3_1_pqd.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_4_1_zLC.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_5_1_XTT.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_6_1_ZvS.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_7_1_Eil.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_8_1_TMP.root',
       '/store/user/chayanit/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_VBF_HToInv_M-125_13TeV/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_9_1_fy5.root' ] );


secFiles.extend( [
               ] )

