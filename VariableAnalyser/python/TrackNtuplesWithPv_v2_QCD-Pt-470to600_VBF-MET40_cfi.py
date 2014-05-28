import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_10_1_4Qy.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_11_1_jBJ.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_1_1_iHO.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_2_1_FWL.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_3_1_ztQ.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_4_1_oA9.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_5_1_tWG.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_6_1_J0H.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_7_1_8nQ.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_8_1_T7O.root',
       '/store/user/pela/VBFQCD_Pt_470to600_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-470to600_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_9_1_Qxe.root' ] );


secFiles.extend( [
               ] )
