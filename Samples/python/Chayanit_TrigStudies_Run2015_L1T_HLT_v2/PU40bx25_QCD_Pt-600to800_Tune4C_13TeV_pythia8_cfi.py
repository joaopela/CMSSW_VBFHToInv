import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_100_1_z16.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_101_1_NDe.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_102_1_oXZ.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_103_1_vDK.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_104_1_q3P.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_105_1_kqk.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_106_1_hUS.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_107_1_Yxt.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_108_1_YeR.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_109_1_ecb.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_10_1_ZKD.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_110_1_MU4.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_111_1_S59.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_112_1_jTP.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_113_1_7Wp.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_114_1_sM7.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_115_1_wEa.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_116_1_kRU.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_117_1_NKW.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_118_1_oXu.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_119_1_VT2.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_120_1_khO.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_121_1_BhA.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_122_1_M1E.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_123_1_S3Q.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_124_1_4wr.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_126_1_eh8.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_127_1_RkI.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_128_1_6Kz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_129_1_ftv.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_12_1_v03.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_130_1_c0Z.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_132_1_HOm.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_133_1_uiB.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_134_1_5dz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_135_1_Stp.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_136_1_xeu.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_138_1_cBe.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_139_1_Pfk.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_13_1_N3x.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_140_1_h3E.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_141_1_Gut.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_142_1_lRN.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_143_1_vxY.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_144_1_vYo.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_145_1_Xye.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_146_1_NWz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_148_1_JHd.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_149_1_1du.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_14_1_DSA.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_151_1_N21.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_152_1_HqF.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_153_1_Hxl.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_154_1_yTJ.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_155_1_dvg.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_156_1_M2t.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_159_1_uCa.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_15_1_odo.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_160_1_Bk0.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_161_1_vVB.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_162_1_YpY.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_163_1_gD9.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_164_1_IvT.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_165_1_nz8.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_166_1_vhl.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_167_1_AwP.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_168_1_yWh.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_16_1_ZR8.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_170_1_RaC.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_171_1_hgY.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_172_1_wZD.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_173_1_vtc.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_174_1_JWi.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_175_1_Q1C.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_176_1_FE7.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_177_1_Xvt.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_178_1_fQ4.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_179_1_Cxf.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_17_1_0Yc.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_180_1_R5W.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_181_1_MCz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_182_1_5oG.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_183_1_vhf.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_184_1_kPF.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_185_1_QIl.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_186_1_1ED.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_187_1_iz8.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_188_1_ooN.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_189_1_kMt.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_18_1_lqM.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_190_1_yun.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_192_1_bot.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_193_1_nFK.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_194_1_03a.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_19_1_DoT.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_20_1_Mgb.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_21_1_oC5.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_22_1_FOT.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_23_1_AdK.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_24_1_7t7.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_25_1_Mzp.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_26_1_Gto.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_27_1_SHo.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_28_1_B4G.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_29_1_muz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_2_1_32y.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_30_1_YWe.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_31_1_i89.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_32_1_rUm.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_33_1_m0c.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_34_1_EAW.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_35_1_Wcr.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_36_1_7N3.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_37_1_Llt.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_39_1_Qbd.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_40_1_8fp.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_41_1_rxg.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_42_1_gTk.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_43_1_y9k.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_44_1_fZ3.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_45_1_g6g.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_46_1_Ur9.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_47_1_e13.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_48_1_ZC5.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_49_1_vIr.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_50_1_z5b.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_51_1_8I6.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_52_1_SXF.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_53_1_pTW.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_54_1_mvM.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_55_1_Q4r.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_56_1_Voz.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_57_1_hW0.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_58_1_9Jw.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_59_1_2xL.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_60_1_z0V.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_61_1_piN.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_62_1_Qef.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_63_1_73s.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_64_1_B2y.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_65_1_9qT.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_66_1_49S.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_67_1_3hF.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_68_1_MkD.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_69_1_ziP.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_6_1_v6z.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_70_1_2EE.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_71_1_cwv.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_72_1_DfD.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_73_1_C1y.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_74_1_U4v.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_75_1_5ti.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_77_1_X6h.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_78_1_8qa.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_7_1_2ru.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_80_1_Poe.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_83_1_hrn.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_84_1_6kt.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_85_1_APO.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_86_1_QFg.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_87_1_5J3.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_88_1_e3f.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_89_1_V3y.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_8_1_Ar5.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_90_1_MJP.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_91_1_LHE.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_92_1_4CL.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_93_1_hob.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_94_1_VrW.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_95_1_DGG.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_96_1_BXy.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_97_1_7Do.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_98_1_Fgb.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_99_1_MOD.root',
       '/store/user/chayanit/QCD_Pt-600to800_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-600to800/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_9_1_J2O.root' ] );


secFiles.extend( [
               ] )

