import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_10_1_By6.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_11_1_8EG.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_12_1_2wU.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_13_1_fqA.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_14_1_3ue.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_15_1_sYu.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_16_1_6Xl.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_17_1_HwF.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_18_1_zDt.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_19_1_M51.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_1_1_mxa.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_20_1_Z6G.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_21_1_BZe.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_22_1_J0s.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_2_1_VmW.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_3_1_fDK.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_4_1_pOU.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_5_1_f33.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_6_1_WGi.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_7_1_kfK.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_8_1_Ooh.root',
       '/store/user/pela/VBFQCD_Pt_300to470_MET40_step1_v1/TrackNtuplesWithPv_v2_QCD-Pt-300to470_VBF-MET40/2ead7a770cb7c4f30893d41a5e99003d/ntupleTracks_9_1_evH.root' ] );


secFiles.extend( [
               ] )
