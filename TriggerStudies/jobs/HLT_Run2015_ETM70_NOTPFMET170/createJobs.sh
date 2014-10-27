#!/bin/bash

mkdir PU40bx25_VBFInv
cd PU40bx25_VBFInv
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_VBF_HToInv_M-125_13TeV_powheg-pythia6_cfi.py --inputConfigFile ../HLTStudies_Sig_ForBatch_cfg.py --numberOfJobs 5
cd ..

mkdir PU40bx25_NeutrinoGun
cd PU40bx25_NeutrinoGun
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_Neutrino_Pt-2to20_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 200    
cd ..

mkdir PU40bx25_QCD_Pt-1000to1400
cd PU40bx25_QCD_Pt-1000to1400/
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-1000to1400_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 20                                                                                                                                       
cd ..

mkdir PU40bx25_QCD_Pt-120to170
cd PU40bx25_QCD_Pt-120to170
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-120to170_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-1400to1800
cd PU40bx25_QCD_Pt-1400to1800
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-1400to1800_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-170to300
cd PU40bx25_QCD_Pt-170to300
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-170to300_Tune4C_13TeV_pythia_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-300to470
cd PU40bx25_QCD_Pt-300to470
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-300to470_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-30to50
cd PU40bx25_QCD_Pt-30to50
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-30to50_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-470to600
cd PU40bx25_QCD_Pt-470to600
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-470to600_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-50to80
cd PU40bx25_QCD_Pt-50to80
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-50to80_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-600to800
cd PU40bx25_QCD_Pt-600to800
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-600to800_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-800to1000
cd PU40bx25_QCD_Pt-800to1000
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-800to1000_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-80to120
cd PU40bx25_QCD_Pt-80to120
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-80to120_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..

mkdir PU40bx25_QCD_Pt-1800
cd PU40bx25_QCD_Pt-1800
python $HEPFWSYS/bin/hepfwMakeBatchJobs.py --inputFileList ../../../../Samples/python/Chayanit_TrigStudies_Run2015_L1T_HLT_v2/PU40bx25_QCD_Pt-1800_Tune4C_13TeV_pythia8_cfi.py --inputConfigFile ../HLTStudies_Bkg_ForBatch_cfg.py --numberOfJobs 40
cd ..