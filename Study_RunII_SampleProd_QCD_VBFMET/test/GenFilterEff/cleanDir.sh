#!/bin/bash

# Clean job directories after hadd of ROOT files

# Cleaning ROOT
rm QCD_Pt-*/*.root

# Removing LSF directories
rm -fR QCD_Pt-*/LSFJOB_*

