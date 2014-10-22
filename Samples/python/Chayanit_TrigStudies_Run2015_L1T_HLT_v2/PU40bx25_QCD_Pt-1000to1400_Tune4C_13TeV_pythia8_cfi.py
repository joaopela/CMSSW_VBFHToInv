import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_104_1_p4b.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_10_1_eNv.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_111_1_F5J.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_113_1_SN8.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_114_1_baz.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_115_1_Xc0.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_118_1_gp8.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_138_1_ApA.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_160_1_zi0.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_17_1_CW3.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_196_1_MWv.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_19_1_I2F.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_23_1_05R.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_24_1_ik8.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_2_1_ASV.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_32_1_OYr.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_37_1_Azd.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_38_1_rmd.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_39_1_TZl.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_44_1_U7n.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_47_1_uFQ.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_52_1_OwU.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_55_1_8XB.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_62_1_dZw.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_67_1_qwy.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_69_1_hgk.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_75_1_8oC.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_76_1_oIL.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_82_1_I6l.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_86_1_e6P.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_87_1_Kse.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_88_1_n7l.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_8_1_2xE.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_99_1_SL5.root',
       '/store/user/chayanit/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/TrigStudies2015_720_L1plusHLT_v2_PU40bx25_QCD_Pt-1000to1400/d9ec0993de5dab2a1e7afeea7cd4800d/outputA_9_1_dkw.root' ] );


secFiles.extend( [
               ] )

