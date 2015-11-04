#!/bin/bash

# Run over version 0 files
# mkdir v0/jj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v0/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   -d v0/jj/   | tee v0/jj/run.log
# mkdir v0/jjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v0/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  -d v0/jjj/  | tee v0/jjj/run.log
# mkdir v0/jjjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v0/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root -d v0/jjjj/ | tee v0/jjjj/run.log
# mkdir v0/all/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v0/PartonGenJetAnalyzer_QCD_VBFLike_all.root  -d v0/all/  | tee v0/all/run.log

# Run over version 1 files
# mkdir v1/jj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v1/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   -d v1/jj/   | tee v0/jj/run.log
# mkdir v1/jjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v1/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  -d v1/jjj/  | tee v0/jjj/run.log
# mkdir v1/jjjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v1/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root -d v1/jjjj/ | tee v0/jjjj/run.log
# mkdir v1/all/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v1/PartonGenJetAnalyzer_QCD_VBFLike_all.root  -d v1/all/  | tee v0/all/run.log

# Run over version 2 files
# mkdir v2/jj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v2/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   -d v2/jj/   | tee v0/jj/run.log
# mkdir v2/jjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v2/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  -d v2/jjj/  | tee v0/jjj/run.log
# mkdir v2/jjjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v2/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root -d v2/jjjj/ | tee v0/jjjj/run.log
# mkdir v2/all/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v2/PartonGenJetAnalyzer_QCD_VBFLike_all.root  -d v2/all/  | tee v0/all/run.log

# Run over version 3 files
# mkdir v3/jj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v3/PartonGenJetAnalyzer_QCD_VBFLike_jj.root   -d v3/jj/   | tee v0/jj/run.log
# mkdir v3/jjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v3/PartonGenJetAnalyzer_QCD_VBFLike_jjj.root  -d v3/jjj/  | tee v0/jjj/run.log
# mkdir v3/jjjj/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v3/PartonGenJetAnalyzer_QCD_VBFLike_jjjj.root -d v3/jjjj/ | tee v0/jjjj/run.log
# mkdir v3/all/
# vbfinv_qcdSamplesRunII_madgraph_hadronization -i v3/PartonGenJetAnalyzer_QCD_VBFLike_all.root  -d v3/all/  | tee v0/all/run.log

# Run over prod 0 files

mkdir prod_v0/all/
vbfinv_qcdSamplesRunII_madgraph_hadronization -i prod_v0/PartonGenJetAnalyzer_QCD_VBFLike_all.root  -d prod_v0/all/  | tee prod_v0/all/run.log