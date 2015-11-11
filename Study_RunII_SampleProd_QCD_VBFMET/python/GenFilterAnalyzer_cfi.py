import FWCore.ParameterSet.Config as cms

genFilterAnalyzer = cms.EDAnalyzer("GenFilterAnalyzer",
  
  inputTag_GenJetCollection = cms.untracked.InputTag('ak5GenJetsNoNu'),
  outFile                   = cms.untracked.string  ('GenFilterAnalyzer.root'),
  
  workingPoints = cms.VPSet(
    
    # Same as Run I samples without Delta(phi) cut
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt20_Eta5p0_DEta3p2_Mjj700"),
      jetMinPt                = cms.untracked.double(20.0),
      jetMaxEta               = cms.untracked.double(5.0),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.2),
      dijetMinMjj             = cms.untracked.double(700)
    ),

    cms.PSet(
      name                    = cms.untracked.string("Pt20_Eta5p0_DEta3p2_Mjj700"),
      jetMinPt                = cms.untracked.double(20.0),
      jetMaxEta               = cms.untracked.double(5.0),
      dijetOppositeHemisphere = cms.untracked.bool  (False),
      dijetMinDeltaEta        = cms.untracked.double(3.2),
      dijetMinMjj             = cms.untracked.double(700)
    ),

    # Same cuts as the current VBF Higgs to invisible (2015/04/27) HLT Path
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p5_Mjj600"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMinMjj             = cms.untracked.double(600)
    ), 

    # Same cuts as the current VBF Higgs to invisible (2015/04/27) HLT Path + Delta(phi)<1.5 cut
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p5_Dphi1p5_Mjj600"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(600)
    ),

    # Current lowest CPU runtime working point (WP_A)
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(1000)
    ),

    ######################################################
    # Lowering Dijet pT                                  #
    ######################################################
    # WP_A: With Dijet pT>45 (lower by 10) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt45_Eta4p8_DEta3p5_Dphi1p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(45.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(1000.0)
    ),

    # WP_A: With Dijet pT>40 (lower by 10) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p5_Dphi1p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(1000.0)
    ),

    ######################################################
    # Lowering Dijet Delta(Eta)                          #
    ######################################################
    # WP_A: With Dijet Delta(Eta)>3.25 (lower by 0.25)
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p25_Dphi1p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.25),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(1000.0)
    ),

    # WP_A: With Dijet Delta(Eta)>3.00 (lower by 0.5)
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p0_Dphi1p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(1000.0)
    ),


    ######################################################
    # Lowering Dijet Mjj                                 #
    ######################################################
    # WP_A: With Dijet Mjj>900 (lower by 100) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj900"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(900)
    ),

    # WP_A: With Dijet Mjj>800 (lower by 200) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj800"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(800)
    ),


    # WP_A: With Dijet Mjj>700 (lower by 300) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj700"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(700)
    ),


    # WP_A: With Dijet Mjj>600 (lower by 400) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj600"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(600)
    ),

    # WP_A: With Dijet Mjj>500 (lower by 500) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj500"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(500)
    ),
    
    # WP_A: With Dijet Mjj>400 (lower by 600) GeV
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p5_Mjj400"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.5),
      dijetMinMjj             = cms.untracked.double(400)
    ),

    ######################################################
    # Increasing Delta(phi)                              #
    ######################################################
    # WP_A: With Dijet Delta(phi)<1.75 (increased by 0.25) 
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi1p75_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(1.75),
      dijetMinMjj             = cms.untracked.double(1000.)
    ),

    # WP_A: With Dijet Delta(phi)<2.0 (increased by 0.5) 
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi2p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(2.0),
      dijetMinMjj             = cms.untracked.double(1000.)
    ),

    # WP_A: With Dijet Delta(phi)<2.25 (increased by 0.75) 
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi2p25_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(2.25),
      dijetMinMjj             = cms.untracked.double(1000.)
    ),

    # WP_A: With Dijet Delta(phi)<2.5 (increased by 1.0) 
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi2p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(2.5),
      dijetMinMjj             = cms.untracked.double(1000.)
    ),

    # WP_A: With Dijet Delta(phi)<2.5 (increased by 1.25) 
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Dphi2p75_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMaxDeltaPhi        = cms.untracked.double(2.55),
      dijetMinMjj             = cms.untracked.double(1000.)
    ),

    # WP_A: Without Dijet Delta(phi) cut
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p5_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.5),
      dijetMinMjj             = cms.untracked.double(1000)
    ),

    ######################################################
    # Second working point                               #
    ######################################################
    # WP_B
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt50_Eta4p8_DEta3p0_Dphi2p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.0),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt45_Eta4p8_DEta3p0_Dphi2p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(45.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.0),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p0_Dphi2p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.0),
      dijetMinMjj             = cms.untracked.double(1000)
    ),

     cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.15),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    
     cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (False),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.15),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    #cms.PSet(
      #name                    = cms.untracked.string("Pt50_Eta4p8_DEta3p0_Mjj1000"),
      #jetMinPt                = cms.untracked.double(50.),
      #jetMaxEta               = cms.untracked.double(4.8),
      #dijetOppositeHemisphere = cms.untracked.double(True),
      #dijetMinDeltaEta        = cms.untracked.double(3.0),
      #dijetMinMjj             = cms.untracked.double(1000)
    #),

    #cms.PSet(
      #name                    = cms.untracked.string("Pt45_Eta4p8_DEta3p0_Mjj1000"),
      #jetMinPt                = cms.untracked.double(45.),
      #jetMaxEta               = cms.untracked.double(4.8),
      #dijetOppositeHemisphere = cms.untracked.double(True),
      #dijetMinDeltaEta        = cms.untracked.double(3.0),
      #dijetMinMjj             = cms.untracked.double(1000)
    #),
    
    cms.PSet(
      name                    = cms.untracked.string("OppSides_Pt40_Eta4p8_DEta3p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (False),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMinMjj             = cms.untracked.double(1000)
    ),
    
    cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj900"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.15),
      dijetMinMjj             = cms.untracked.double(900)
    ),

    cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj800"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.15),
      dijetMinMjj             = cms.untracked.double(800)
    ),
    
    cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj700"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMaxDeltaPhi        = cms.untracked.double(2.15),
      dijetMinMjj             = cms.untracked.double(700)
    ),

    cms.PSet(
      name                    = cms.untracked.string("Pt40_Eta4p8_DEta3p0_Dphi2p15_Mjj600"),
      jetMinPt                = cms.untracked.double(40.),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.0),
      dijetMinMjj             = cms.untracked.double(600)
    ),

     cms.PSet(
      name                    = cms.untracked.string("Pt50_Eta4p8_DEta3p25_Dphi2p0_Mjj1000"),
      jetMinPt                = cms.untracked.double(50.0),
      jetMaxEta               = cms.untracked.double(4.8),
      dijetOppositeHemisphere = cms.untracked.bool  (True),
      dijetMinDeltaEta        = cms.untracked.double(3.25),
      dijetMaxDeltaPhi        = cms.untracked.double(2.0),
      dijetMinMjj             = cms.untracked.double(1000)
    )
  ),
)
