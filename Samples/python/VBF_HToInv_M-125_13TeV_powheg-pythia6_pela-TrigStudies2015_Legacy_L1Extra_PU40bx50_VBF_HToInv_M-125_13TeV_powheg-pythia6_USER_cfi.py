import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_1_2_Cpk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_2_1_suk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_3_1_yA9.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_4_2_VQk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_5_1_Yzm.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_6_1_jzs.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx50_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_7_1_BVP.root' ] );


secFiles.extend( [
               ] )

 
