import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/42D9D6F7-3D80-E211-9AEC-00266CFFCCC8.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/48B1D17A-3280-E211-8603-00266CFFC76C.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/5842E7DE-3080-E211-8C71-1CC1DE051080.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/6AC01C9A-3C80-E211-9382-00266CFFBC38.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/B4135B4C-2780-E211-9872-00266CFFBFC0.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/C47C22C3-3880-E211-84B7-1CC1DE051038.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/C8C51D31-3780-E211-9C46-001F296B9576.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/CCBFD618-2F80-E211-88F5-1CC1DE1CEFE0.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/D43C4CB3-3080-E211-BC4F-00237DF345D6.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/D8B805CF-2B80-E211-B59C-1CC1DE04FF50.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/E6D398CF-3280-E211-87A8-AC162DACE1B8.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/F49A996F-3580-E211-A243-001F296B9576.root',
       '/store/mc/Summer12_DR53X/VBF_HToInvisible_M-125_8TeV-powheg-pythia6/AODSIM/PU_S10_START53_V7C-v1/20000/FA9F3F66-4C80-E211-B0CC-0017A4770420.root' ] );


secFiles.extend( [
               ] )
