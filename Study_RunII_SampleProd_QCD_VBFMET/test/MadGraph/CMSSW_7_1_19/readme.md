Sequence of thing to to obtain results
======================================

Produce LHE files using MadGraph
================================

Hadronize them using Pythia8
============================

Studies #1 - Parton to Generator Matching
=========================================

Studies #2 - Generator Filter Studies
=====================================

To run the filter analysis over a set of input files:

```bash
cmsRun run_ANALYSISFILTER_overGEN_cfg.py print inputFiles=[inFile0.root,inFile1.root,...]  outputFile=[outFile0.root] maxEvents=[numberOfEvents]
```

To test the implemented filter:

```bash
cmsRun testFilter_cfg.py inputFiles=[inFile0.root,inFile1.root,...] maxEvents=-1
```