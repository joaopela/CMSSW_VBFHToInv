Sequence of thing to to obtain results
======================================

Produce LHE files using MadGraph
================================

Hadronize them using Pythia8
============================

Studies #1 - Parton to Generator Matching
=========================================

To run analysis over the hadronized event files:

```bash
cmsRun run_ANALYSIS_overGEN_cfg.py print inputFiles=[inFile0.root,inFile1.root,...] outputFile=[outFile0.root] maxEvents=[numberOfEvents] dijetPt=[DijetPtCut] dijetMjj=[DijetPtCut]
```

To extract the results and plots:

```bash
vbfinv_qcdSamplesRunII_madgraph_hadronization -i [inFile.root] -d [outputDirectory]
```

Studies #2 - Generator Filter Studies
=====================================

To run the filter analysis over a set of input files:

```bash
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=[inFile0.root,inFile1.root,...]  outputFile=[outFile0.root] maxEvents=[numberOfEvents]
```

To get the plots output:

```bash
vbfinv_qcdSamplesRunII_madgraph_genFilterAnalysis -i [inFile.root] -d [outputDirectory]
```

To test the implemented filter:

```bash
cmsRun testFilter_cfg.py inputFiles=[inFile0.root,inFile1.root,...] maxEvents=-1
```