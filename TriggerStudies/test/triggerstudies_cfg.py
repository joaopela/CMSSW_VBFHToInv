import FWCore.ParameterSet.Config as cms

process = cms.Process("TrgEff")

################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
################################################################

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/output5.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_1.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_10.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_11.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_12.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_13.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_14.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_15.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_16.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_17.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_18.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_19.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_2.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_20.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_21.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_22.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_23.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_24.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_25.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_3.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_4.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_5.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_6.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_7.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_8.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/HLT3_output_9.root'
    ),
    
    #secondaryFileNames=cms.untracked.vstring(
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/0E249394-AB7A-E211-A6EC-00237DA1ED1C.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/1AD6FA5A-DD7A-E211-9DE3-0025901D1668.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/24FBA0DF-DD7A-E211-8EA9-0025901D08D6.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/262AE4F9-E07A-E211-BA48-003048F5B69C.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/284A39BB-A37A-E211-B5D3-0017A477100C.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/5A9BE0BE-D97A-E211-8056-90B11C2CC96F.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/5E541B39-E07A-E211-95A2-003048341A94.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/60F2B62F-F47A-E211-BE08-90B11C2ACF20.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/68227EAD-E07A-E211-9EC0-0025904AC2C6.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/6AF3AD35-E77A-E211-BCA2-003048344C14.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/6AFA2D9D-E47A-E211-B47A-90B11C27F5F0.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/6E684AFE-DB7A-E211-991A-003048F5ADF2.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/921B8731-EA7A-E211-BE73-00259048BBCA.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/945F944E-ED7A-E211-8891-0025900EAB5E.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/94AF05D0-F07A-E211-BF71-0025907254BC.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/96B129BD-E57A-E211-A3BF-0025904A8EC8.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/9EB6C0E9-F67A-E211-9573-90B11C27F5F0.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/A472FD48-2A7B-E211-A5C4-78E7D1E4B772.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/A811A238-A87A-E211-BD82-00266CFFCA1C.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/B013C3AB-D27A-E211-8C2F-003048344C68.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/B2D0413A-E37A-E211-8C94-0025904886E6.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/B4009C87-E17A-E211-80E1-0025904AC2C4.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/BCEEB605-DF7A-E211-9BE5-003048344A9A.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/D8907729-E27A-E211-A415-0025900E3506.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/EA72C17B-DE7A-E211-9CCE-003048344A9A.root',
      #'file:/afs/cern.ch/user/p/pela/go/ws/public/samples/VBF_HToInv_M-125_13TeV_powheg-pythia6/GEN-SIM/FE2C8C9A-D67A-E211-97F1-0025904A8ECE.root'
    #)
)

process.demo = cms.EDAnalyzer('TriggerStudies',
                              
  verbose                    = cms.untracked.bool(True),
  doL1TAnalysis              = cms.untracked.bool(True),
  inputTag_L1GTReadoutRecord = cms.InputTag("gtDigis"),
  selL1Trigger               = cms.vstring("L1_ETM40",
                                           "L1_ETM50",
                                           "L1_HTT150",
                                           "L1_HTT175",
                                           "L1_HTT200"),
  
  doHLTAnalysis              = cms.untracked.bool(True),
  inputTag_HLTResults        = cms.InputTag("TriggerResults::HLT2"),
  selHLTrigger               = cms.vstring("HLT_DiPFJet40_PFMETnoMu65_MJJ800VBF_AllJets_v",
                                           "HLT_DiPFJet40_PFMETnoMu65_MJJ600VBF_LeadingJets_v",
                                           "HLT_DiJet20_MJJ650_AllJets_DEta3p5_HT120_VBF_v",
                                           "HLT_DiJet30_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ650_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ700_AllJets_DEta3p5_VBF_v",
                                           "HLT_DiJet35_MJJ750_AllJets_DEta3p5_VBF_v"),
  
)


process.p = cms.Path(process.demo)
