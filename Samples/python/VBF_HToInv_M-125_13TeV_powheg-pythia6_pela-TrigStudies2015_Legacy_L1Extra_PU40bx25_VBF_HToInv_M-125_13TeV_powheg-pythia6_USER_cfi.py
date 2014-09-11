import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_1_1_h9Z.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_2_1_P14.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_3_1_AtB.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_4_1_jFk.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_5_1_fOo.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_6_1_egQ.root',
       '/store/user/pela/VBF_HToInv_M-125_13TeV_powheg-pythia6/TrigStudies2015_Legacy_L1Extra_PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6/84409f128110e8d3d995f79072c47aaa/L1Extra_7_1_uyU.root' ] );


secFiles.extend( [
               ] )

 
