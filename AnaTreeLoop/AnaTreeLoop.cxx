#define AnaTreeLoop_cxx
#include "AnaTreeLoop.h"

#include <iostream>

// ROOT includes
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>



void AnaTreeLoop::Loop()
{

   // Book histograms
   hNearestDistUntaggedTrueCosToTaggedCosFM = 
      new TH1F("hNearestDistUntaggedTrueCosToTaggedCosFM","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);
   hNearestDistUntaggedTrueCosToTaggedCosGT = 
      new TH1F("hNearestDistUntaggedTrueCosToTaggedCosGT","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);
   hNearestDistUntaggedTrueCosToTaggedCosGTFM = 
      new TH1F("hNearestDistUntaggedTrueCosToTaggedCosGTFM","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);
   hNearestDistUntaggedTrueNuToTaggedCosFM = 
      new TH1F("hNearestDistUntaggedTrueNuToTaggedCosFM","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);
   hNearestDistUntaggedTrueNuToTaggedCosGT = 
      new TH1F("hNearestDistUntaggedTrueNuToTaggedCosGT","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);
   hNearestDistUntaggedTrueNuToTaggedCosGTFM = 
      new TH1F("hNearestDistUntaggedTrueNuToTaggedCosGTFM","Distance of untagged true track to tagged cosmic track; Dist [cm]; Tracks", 100, 0, 500);


   hNTracks = new TH1F("hNTracks","Number of tracks in event; Tracks; Events", 100, 0, 100);
   hLepMomTruth = new TH1F("hLepMomTruth","Track Momentum; Momentum [GeV]; Tracks", 100, 0, 10);


   //
   // MC Truth Information
   //
   hMCEvtsTruth = new TH1F("hMCEvtsTruth","Number of neutrino interactions in spill; Interactions; Neutrinos", 10, 0, 11);
   hNuPDGTruth = new TH1F("hNuPDGTruth","Nu PDG Truth; PDG; Neutrinos", 32, -17, 17);
   hCCNCTruth  = new TH1F("hCCNCTruth","CCNC Truth; PDG; Neutrinos", 2, 0, 2);
   hCCNCTruth->GetXaxis()->SetBinLabel(1,"CC");
   hCCNCTruth->GetXaxis()->SetBinLabel(2,"NC");
   hRecoTruthVtxDist = new TH1F("hRecoTruthVtxDist","Distance between the matched vtx and the true vtx; Dist [cm]; Neutrinos", 100, 0, 100);
   hRecoTruthVtxXDist = new TH1F("hRecoTruthVtxXDist","Distance between the matched vtx and the true vtx; Dist [cm]; Neutrinos", 100, -100, 100);
   hRecoTruthVtxYDist = new TH1F("hRecoTruthVtxYDist","Distance between the matched vtx and the true vtx; Dist [cm]; Neutrinos", 100, -100, 100);
   hRecoTruthVtxZDist = new TH1F("hRecoTruthVtxZDist","Distance between the matched vtx and the true vtx; Dist [cm]; Neutrinos", 100, -100, 100);
   hCCNCLongestTrackNuMu = new TH1F("hCCNCLongestTrackNuMu","CCNC NuMu Longest Track; PDG; Neutrinos", 2, 0, 2);
   hCCNCLongestTrackNuMu->GetXaxis()->SetBinLabel(1,"CC");
   hCCNCLongestTrackNuMu->GetXaxis()->SetBinLabel(2,"NC");
   hCCNCLongestTrackNuMuBar = new TH1F("hCCNCLongestTrackNuMuBar","CCNC NuMuBar Longest Track; PDG; Neutrinos", 2, 0, 2);
   hCCNCLongestTrackNuMuBar->GetXaxis()->SetBinLabel(1,"CC");
   hCCNCLongestTrackNuMuBar->GetXaxis()->SetBinLabel(2,"NC");
   hCCNCLongestTrackNuE = new TH1F("hCCNCLongestTrackNuE","CCNC NuE Longest Track; PDG; Neutrinos", 2, 0, 2);
   hCCNCLongestTrackNuE->GetXaxis()->SetBinLabel(1,"CC");
   hCCNCLongestTrackNuE->GetXaxis()->SetBinLabel(2,"NC");
   hCCNCLongestTrackNuEBar = new TH1F("hCCNCLongestTrackNuEBar","CCNC NuEBar Longest Track; PDG; Neutrinos", 2, 0, 2);
   hCCNCLongestTrackNuEBar->GetXaxis()->SetBinLabel(1,"CC");
   hCCNCLongestTrackNuEBar->GetXaxis()->SetBinLabel(2,"NC");

   
   //
   // Track origin histograms
   //
   hTrackOrigin                = new TH1F("hTrackOrigin","Track Origin; Origin; Tracks", 3, 0, 3);
   hLongestTrackOrigin         = new TH1F("hLongestTrackOrigin","Longest Track Origin; Origin; Tracks", 3, 0, 3);
   hTrackOriginNoCosRem = new TH1F("hTrackOriginNoCosRem","Origin for tracks before cosmic removal; Origin; Tracks", 3, 0, 3);
   hTrackOriginFM      = new TH1F("hTrackOriginFM","Origin for tracks not removed by flash match cut; Origin; Tracks", 3, 0, 3);
   hTrackOriginGT      = new TH1F("hTrackOriginGT","Origin for tracks not removed by geom tagger cut; Origin; Tracks", 3, 0, 3);
   hTrackOriginGTFM       = new TH1F("hTrackOriginGTFM","Origin for tracks not removed by geom tagger and flash match cut; Origin; Tracks", 3, 0, 3);
   hTrackOrigin->GetXaxis()->SetBinLabel(1,"Unknown");
   hTrackOrigin->GetXaxis()->SetBinLabel(2,"Nurino");
   hTrackOrigin->GetXaxis()->SetBinLabel(3,"Cosmic");
   hLongestTrackOrigin->GetXaxis()->SetBinLabel(1,"Unknown");
   hLongestTrackOrigin->GetXaxis()->SetBinLabel(2,"Nurino");
   hLongestTrackOrigin->GetXaxis()->SetBinLabel(3,"Cosmic");
   hTrackOriginNoCosRem->GetXaxis()->SetBinLabel(1,"Unknown");
   hTrackOriginNoCosRem->GetXaxis()->SetBinLabel(2,"Neutrino");
   hTrackOriginNoCosRem->GetXaxis()->SetBinLabel(3,"Cosmic");
   hTrackOriginFM->GetXaxis()->SetBinLabel(1,"Unknown");
   hTrackOriginFM->GetXaxis()->SetBinLabel(2,"Neutrino");
   hTrackOriginFM->GetXaxis()->SetBinLabel(3,"Cosmic");
   hTrackOriginGT->GetXaxis()->SetBinLabel(1,"Unknown");
   hTrackOriginGT->GetXaxis()->SetBinLabel(2,"Neutrino");
   hTrackOriginGT->GetXaxis()->SetBinLabel(3,"Cosmic");
   hTrackOriginGTFM->GetXaxis()->SetBinLabel(1,"Unknown");
   hTrackOriginGTFM->GetXaxis()->SetBinLabel(2,"Neutrino");
   hTrackOriginGTFM->GetXaxis()->SetBinLabel(3,"Cosmic");

   // Track Length histograms
   hTrackLength                           = new TH1F("hTrackLength","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hTrackLengthTrueCosNoCosRem  = new TH1F("hTrackLengthTrueCosNoCosRem","Track Length; Length; Tracks", 100, 0., 530);
   hTrackLengthNoCosRem            = new TH1F("hTrackLengthNoCosRem","Length for tracks before cosmic removal; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthFM                 = new TH1F("hTrackLengthFM","Length for tracks not removed by flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthGT                 = new TH1F("hTrackLengthGT","Length for tracks not removed by geom tagger cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthGTFM                  = new TH1F("hTrackLengthGTFM","Length for tracks not removed by geom tagger and flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueCosFM       = new TH1F("hTrackLengthTrueCosFM","Length for tracks not removed by flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueCosGT       = new TH1F("hTrackLengthTrueCosGT","Length for tracks not removed by geom tagger cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueCosGTFM        = new TH1F("hTrackLengthTrueCosGTFM","Length for tracks not removed by geom tagger and flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuNoCosRem    = new TH1F("hTrackLengthTrueNuNoCosRem","Length for tracks before cosmic removal; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuFM         = new TH1F("hTrackLengthTrueNuFM","Length for tracks not removed by flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuGT         = new TH1F("hTrackLengthTrueNuGT","Length for tracks not removed by geom tagger cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuGTFM          = new TH1F("hTrackLengthTrueNuGTFM","Length for tracks not removed by geom tagger and flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuCCNoCosRem    = new TH1F("hTrackLengthTrueNuCCNoCosRem","Length for tracks before cosmic removal; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuCCFM         = new TH1F("hTrackLengthTrueNuCCFM","Length for tracks not removed by flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuCCGT         = new TH1F("hTrackLengthTrueNuCCGT","Length for tracks not removed by geom tagger cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuCCGTFM          = new TH1F("hTrackLengthTrueNuCCGTFM","Length for tracks not removed by geom tagger and flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuNCNoCosRem    = new TH1F("hTrackLengthTrueNuNCNoCosRem","Length for tracks before cosmic removal; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuNCFM         = new TH1F("hTrackLengthTrueNuNCFM","Length for tracks not removed by flash match cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuNCGT         = new TH1F("hTrackLengthTrueNuNCGT","Length for tracks not removed by geom tagger cut; Length (cm); Tracks", 100, 0, 530);
   hTrackLengthTrueNuNCGTFM          = new TH1F("hTrackLengthTrueNuNCGTFM","Length for tracks not removed by geom tagger and flash match cut; Length (cm); Tracks", 100, 0, 530);
   hLongestTrackLengthTrueNu            = new TH1F("hLongestTrackLengthTrueNu","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hLongestTrackLengthTrueNuCC          = new TH1F("hLongestTrackLengthTrueNuCC","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hLongestTrackLengthTrueNuNC          = new TH1F("hLongestTrackLengthTrueNuNC","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hLongestTrackLengthTrueCos          = new TH1F("hLongestTrackLengthTrueCos","Track Length; Length [cm]; Tracks", 100, 0, 530);

   //
   // Track boundary histograms
   // 

   // All tracks
   hPerpDistXBound   = new TH1F("hPerpDistXBound ","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistYBound   = new TH1F("hPerpDistYBound ","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistZBound   = new TH1F("hPerpDistZBound ","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistToABound = new TH1F("hPerpDistToABound ","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 1060);
  
   // True neutrinos only
   hPerpDistXBoundTrueNuNoCosRem  =
      new TH1F("hPerpDistXBoundTrueNuNoCosRem","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueNuFM       =
      new TH1F("hPerpDistXBoundTrueNuFM","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueNuGT       =
      new TH1F("hPerpDistXBoundTrueNuGT","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueNuGTFM        =
      new TH1F("hPerpDistXBoundTrueNuGTFM","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistYBoundTrueNuNoCosRem   =
      new TH1F("hPerpDistYBoundTrueNuNoCosRem","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueNuFM        =
      new TH1F("hPerpDistYBoundTrueNuFM","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueNuGT        =
      new TH1F("hPerpDistYBoundTrueNuGT","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueNuGTFM         =
      new TH1F("hPerpDistYBoundTrueNuGTFM","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistZBoundTrueNuNoCosRem   =
      new TH1F("hPerpDistZBoundTrueNuNoCosRem","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueNuFM        =
      new TH1F("hPerpDistZBoundTrueNuFM","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueNuGT        =
      new TH1F("hPerpDistZBoundTrueNuGT","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueNuGTFM          = new TH1F("hPerpDistZBoundTrueNuGTFM","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistToABoundTrueNuNoCosRem  = new TH1F("hPerpDistToABoundTrueNuNoCosRem","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 1060);
   hPerpDistToABoundTrueNuFM       = new TH1F("hPerpDistToABoundTrueNuFM","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 1060);
   hPerpDistToABoundTrueNuGT       = new TH1F("hPerpDistToABoundTrueNuGT","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 1060);
   hPerpDistToABoundTrueNuGTFM        = new TH1F("hPerpDistToABoundTrueNuGTFM","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 1060);

   // True cosmics only
   hPerpDistXBoundTrueCosNoCosRem   = new TH1F("hPerpDistXBoundTrueCosNoCosRem","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueCosFM        = new TH1F("hPerpDistXBoundTrueCosFM","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueCosGT        = new TH1F("hPerpDistXBoundTrueCosGT","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistXBoundTrueCosGTFM         = new TH1F("hPerpDistXBoundTrueCosGTFM","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistYBoundTrueCosNoCosRem   = new TH1F("hPerpDistYBoundTrueCosNoCosRem","to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueCosFM        = new TH1F("hPerpDistYBoundTrueCosFM","to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueCosGT        = new TH1F("hPerpDistYBoundTrueCosGT","to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistYBoundTrueCosGTFM         = new TH1F("hPerpDistYBoundTrueCosGTFM","to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistZBoundTrueCosNoCosRem   = new TH1F("hPerpDistZBoundTrueCosNoCosRem","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueCosFM        = new TH1F("hPerpDistZBoundTrueCosFM","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueCosGT        = new TH1F("hPerpDistZBoundTrueCosGT","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistZBoundTrueCosGTFM         = new TH1F("hPerpDistZBoundTrueCosGTFM","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistToABoundTrueCosNoCosRem = new TH1F("hPerpDistToABoundTrueCosNoCosRem","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistToABoundTrueCosFM      = new TH1F("hPerpDistToABoundTrueCosFM","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistToABoundTrueCosGT      = new TH1F("hPerpDistToABoundTrueCosGT","tClosest Perpendicular Distance o A TPC Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistToABoundTrueCosGTFM       = new TH1F("hPerpDistToABoundTrueCosGTFM","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 116);

   //
   // Track calo and PID histograms
   //
   hTrackPIDATrueNuNoCosRem    = new TH1F("hTrackPIDATrueNuNoCosRem","Track PIDA; PIDA; Tracks", 100, 0, 30);
   hTrackPIDATrueCosNoCosRem  = new TH1F("hTrackPIDATrueCosNoCosRem","Track PIDA; PIDA; Tracks", 100, 0, 30);
   hTrueMuonPIDA                        = new TH1F("hTrueMuonPIDA","True Muon PIDA; PIDA; Tracks", 100, 0, 10);
   hTruePionPIDA                        = new TH1F("hTruePionPIDA","True Pion PIDA; PIDA; Tracks", 100, 0, 10);
   hTrueProtonPIDA                      = new TH1F("hTrueProtonPIDA","True Proton PIDA; PIDA; Tracks", 100, 0, 10);
   hLongestTrackPIDA          = new TH1F("hLongestTrackPIDA","Longest Track PIDA; PIDA; Tracks", 100, 0, 30);
   hLongestTrackPIDATrueNuCCMu       = new TH1F("hLongestTrackPIDATrueNuCCMu","Longest Track PIDA; PIDA; Tracks", 100, 0, 30);
   hLongestTrackPIDATrueNuNCMu       = new TH1F("hLongestTrackPIDATrueNuNCMu","Longest Track PIDA; PIDA; Tracks", 100, 0, 30);
   hLongestTrackPIDATrueNuCCPi       = new TH1F("hLongestTrackPIDATrueNuCCPi","Longest Track PIDA; PIDA; Tracks", 100, 0, 30);
   hLongestTrackPIDATrueNuNCPi       = new TH1F("hLongestTrackPIDATrueNuNCPi","Longest Track PIDA; PIDA; Tracks", 100, 0, 30);
   hTrackRangeTrueCosNoCosRem    = new TH1F("hTrackRangeTrueCosNoCosRem","Range for tracks before cosmic removal; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueCosFM         = new TH1F("hTrackRangeTrueCosFM","Range for tracks not removed by flash match cut; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueCosGT         = new TH1F("hTrackRangeTrueCosGT","Range for tracks not removed by geom tagger cut; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueCosGTFM          = new TH1F("hTrackRangeTrueCosGTFM","Range for tracks not removed by geom tagger and flash match cut; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueNuNoCosRem    = new TH1F("hTrackRangeTrueNuNoCosRem","Range for tracks before cosmic removal; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueNuFM         = new TH1F("hTrackRangeTrueNuFM","Range for tracks not removed by flash match cut; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueNuGT         = new TH1F("hTrackRangeTrueNuGT","Range for tracks not removed by geom tagger cut; Range (cm); Tracks", 100, 0, 530);
   hTrackRangeTrueNuGTFM          = new TH1F("hTrackRangeTrueNuGTFM","Range for tracks not removed by geom tagger and flash match cut; Range (cm); Tracks", 100, 0, 530);
   hTrackKETrueCosNoCosRem    = new TH1F("hTrackKETrueCosNoCosRem","KE for tracks before cosmic removal; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueCosFM         = new TH1F("hTrackKETrueCosFM","KE for tracks not removed by flash match cut; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueCosGT         = new TH1F("hTrackKETrueCosGT","KE for tracks not removed by geom tagger cut; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueCosGTFM          = new TH1F("hTrackKETrueCosGTFM","KE for tracks not removed by geom tagger and flash match cut; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueNuNoCosRem    = new TH1F("hTrackKETrueNuNoCosRem","KE for tracks before cosmic removal; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueNuFM         = new TH1F("hTrackKETrueNuFM","KE for tracks not removed by flash match cut; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueNuGT         = new TH1F("hTrackKETrueNuGT","KE for tracks not removed by geom tagger cut; KE (MeV); Tracks", 100, 0, 10000);
   hTrackKETrueNuGTFM          = new TH1F("hTrackKETrueNuGTFM","KE for tracks not removed by geom tagger and flash match cut; KE (MeV); Tracks", 100, 0, 10000);

   //
   // Track angle histograms
   //
   hTrackPhi                              = new TH1F("hTrackPhi","Track Phi; Phi; Tracks", 100, -3.14, 3.14);
   hTrackThetaTrueNuNoCosRem     = new TH1F("hTrackThetaTrueNuNoCosRem","Track Theta; Theta; Tracks", 100, 0., 3.14);
   hTrackThetaTrueCosNoCosRem   = new TH1F("hTrackThetaTrueCosNoCosRem","Track Theta; Theta; Tracks", 100, 0., 3.14);
   hTrackThetaXZTrueNuNoCosRem   = new TH1F("hTrackThetaXZTrueNuNoCosRem","Track Theta XZ; Theta; Tracks", 100, 0., 3.14);
   hTrackThetaXZTrueCosNoCosRem = new TH1F("hTrackThetaXZTrueCosNoCosRem","Track Theta XZ; Theta; Tracks", 100, 0., 3.14);
   hTrackThetaYZTrueNuNoCosRem   = new TH1F("hTrackThetaYZTrueNuNoCosRem","Track Theta YZ; Theta; Tracks", 100, 0., 3.14);
   hTrackThetaYZTrueCosNoCosRem = new TH1F("hTrackThetaYZTrueCosNoCosRem","Track Theta YZ; Theta; Tracks", 100, 0., 3.14);
   hTrackPhiTrueNuNoCosRem       = new TH1F("hTrackPhiTrueNuNoCosRem","Track Phi; Phi; Tracks", 100, -3.14, 3.14);
   hTrackPhiTrueCosNoCosRem     = new TH1F("hTrackPhiTrueCosNoCosRem","Track Phi; Phi; Tracks", 100, -3.14, 3.14);

   //
   // Track vertex histograms
   //
   hLongestTrackNearestVtxDistTrueNuCC = new TH1F("hLongestTrackNearestVtxDistTrueNuCC","Distance to nearest vertex; Distance [cm]; Tracks", 100, 0, 25);
   hLongestTrackNearestVtxDistTrueNuNC = new TH1F("hLongestTrackNearestVtxDistTrueNuNC","Distance to nearest vertex; Distance [cm]; Tracks", 100, 0, 25);
   hLongestTrackNearestVtxDistTrueCos = new TH1F("hLongestTrackNearestVtxDistTrueCos","Distance to nearest vertex; Distance [cm]; Tracks", 100, 0, 25);


   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the tracks blocks the name of the track module
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);
   ana_tree_truth = new AnaTreeTruth(fChain);
   ana_tree_vtx = new AnaTreeVertex(fChain,fVertexModuleName);


   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1060.};

   size_t nEvtsProcessed = 0;
   size_t nEvtsFiredPMTTrigger = 0;

   // Reality check
   size_t nRealityEvts0 = 0;
   // size_t nRealityEvts1 = 0;
   // size_t nRealityEvts2 = 0;
   // size_t nRealityEvts3 = 0;
   // size_t nTracksVertexMatched = 0;
   // size_t nTracksVertexLengthMatched = 0;

   if (fChain == 0) return;

   size_t nEvtsLongestTrackNu = 0;
   size_t nEvtsLongestTrackCos = 0;
   size_t nEvtsLongestTrackAll = 0;

   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   if(fNEvts == 0){
      fNEvts = nentries;
      std::cout << "No number of events to process specified, running over all " << nentries << " of them." << std::endl;
   }

   // Loop over events
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if(jentry >= (signed)fNEvts)
         break;

      if(jentry%1000 == 0 && jentry !=0 )
         std::cout << "Processed: " << jentry << " events." << std::endl;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      nEvtsProcessed++;



      // Get MC truth information
      hMCEvtsTruth->Fill(ana_tree_truth->MCEvtsTruth());
      for (short i = 0; i< ana_tree_truth->MCEvtsTruth(); i++){
         hNuPDGTruth->Fill(ana_tree_truth->NuPDGTruth(i));
         hCCNCTruth->Fill(ana_tree_truth->CCNCTruth(i));
      }
























      // Check if this event has a flash match consistent with a neutrino on any track (< 0.5 or 0.0)
      // If it does, the event had a track which fired the PMT trigger
      bool firedPMTTrigger = false;
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){
         if(ana_tree_tracks->CosmicScoreFlashMatch(i) < 0.5){
            firedPMTTrigger = true;
            nEvtsFiredPMTTrigger++;
            break;
         }
      }


      hNTracks->Fill(ana_tree_tracks->NTracks()); 

      double longestTrackLength = 0;
      double longestTrackOrigin = -1;
      double longestTrackIndex = -1;
      double longestTrackLengthNuGTFM = 0;
      double longestTrackLengthCosGTFM = 0;
      double longestTrackVertexDist = 999999;
      int longestTrackIndexNuGTFM = -1;
      int longestTrackIndexCosGTFM = -1;
      int longestTrackMatchedVtxIndex = -1;
      
      // Before even processing this event, is the longest track greater than 100 cm?
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){
         // Is it contained? I'm using the cosmic tagger to check.
         if(ana_tree_tracks->CosmicScoreTagger(i) > 0.4
              or ana_tree_tracks->CosmicScoreFlashMatch(i) > 0.5)
            continue;

         double minVertexTrackDist = 999999;
         int minVertexTrackDistIndex = -1;
         // Does the track match a vertex?
         for (short j= 0; j< ana_tree_vtx->NVertex(); j++){
            // Check at start point
            double startVertexDist = sqrt(pow(ana_tree_tracks->StartX(i)-ana_tree_vtx->VertexX(j),2) +
                                          pow(ana_tree_tracks->StartY(i)-ana_tree_vtx->VertexY(j),2) +
                                          pow(ana_tree_tracks->StartZ(i)-ana_tree_vtx->VertexZ(j),2));
            if(startVertexDist < minVertexTrackDist){
               minVertexTrackDist = startVertexDist;
               minVertexTrackDistIndex = j;
            }
            // Check at end point
            double endVertexDist = sqrt(pow(ana_tree_tracks->EndX(i)-ana_tree_vtx->VertexX(j),2) +
                                        pow(ana_tree_tracks->EndY(i)-ana_tree_vtx->VertexY(j),2) +
                                        pow(ana_tree_tracks->EndZ(i)-ana_tree_vtx->VertexZ(j),2));
            if(endVertexDist < minVertexTrackDist){
               minVertexTrackDist = endVertexDist;
               minVertexTrackDistIndex = j;
            }
         }
         // Only accept the vertex if it is within 1 cm of the longest track and is in the fiducial volume
         if(minVertexTrackDist > 5 or !(ana_tree_algs->IsFiducial(ana_tree_vtx->VertexX(minVertexTrackDistIndex),ana_tree_vtx->VertexY(minVertexTrackDistIndex),ana_tree_vtx->VertexZ(minVertexTrackDistIndex))))
            continue;

         // Only accept the vertex if it is in the fiducial volume
         // if(!(ana_tree_algs->IsFiducial(ana_tree_vtx->Vertex(minVertexTrackDistIndex,0),ana_tree_vtx->Vertex(minVertexTrackDistIndex,1),ana_tree_vtx->Vertex(minVertexTrackDistIndex,2))))
         //    continue;

         if(ana_tree_tracks->Length(i) > longestTrackLength){
            longestTrackLength = ana_tree_tracks->Length(i);
            longestTrackOrigin = ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i));
            longestTrackMatchedVtxIndex = minVertexTrackDistIndex;
            longestTrackVertexDist = minVertexTrackDist;
            longestTrackIndex = i;
         }
         
         if(ana_tree_tracks->Length(i) > longestTrackLengthNuGTFM && ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
            longestTrackLengthNuGTFM = ana_tree_tracks->Length(i);
            longestTrackIndexNuGTFM = i;
         }
         if(ana_tree_tracks->Length(i) > longestTrackLengthCosGTFM && ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
            longestTrackLengthCosGTFM = ana_tree_tracks->Length(i);
            longestTrackIndexCosGTFM = i;
         }

      }

      // Fill the longest track histograms before the length cut is applied
      if(longestTrackOrigin == 1){
         hLongestTrackLengthTrueNu->Fill(longestTrackLength);
         if(ana_tree_truth->CCNCTruth(0) == 0){
            hLongestTrackLengthTrueNuCC->Fill(longestTrackLength);
            hLongestTrackNearestVtxDistTrueNuCC->Fill(longestTrackVertexDist);
         }
         if(ana_tree_truth->CCNCTruth(0) == 1){
            hLongestTrackLengthTrueNuNC->Fill(longestTrackLength);
            hLongestTrackNearestVtxDistTrueNuNC->Fill(longestTrackVertexDist);
         }
      }
      if(longestTrackOrigin == 2){
         hLongestTrackLengthTrueCos->Fill(longestTrackLength);
         if(longestTrackVertexDist < 999999)
            hLongestTrackNearestVtxDistTrueCos->Fill(longestTrackVertexDist);
      }

      // Apply the cut on 100 cm
      if(longestTrackLength  > 100){
         nEvtsLongestTrackAll++;
         hLongestTrackOrigin->Fill(longestTrackOrigin);
         hLongestTrackPIDA->Fill(ana_tree_tracks->PIDA(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex)));
         if(longestTrackOrigin == 2)
            nEvtsLongestTrackCos++;
         if(longestTrackOrigin == 1){
            nEvtsLongestTrackNu++;

            if(ana_tree_truth->CCNCTruth(0) == 0 and abs(ana_tree_tracks->PDGTruth(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex))) == 13)
               hLongestTrackPIDATrueNuCCMu->Fill(ana_tree_tracks->PIDA(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex)));
            if(ana_tree_truth->CCNCTruth(0) == 1 and abs(ana_tree_tracks->PDGTruth(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex))) == 13)
               hLongestTrackPIDATrueNuNCMu->Fill(ana_tree_tracks->PIDA(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex)));
            if(ana_tree_truth->CCNCTruth(0) == 0 and abs(ana_tree_tracks->PDGTruth(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex))) == 211)
               hLongestTrackPIDATrueNuCCPi->Fill(ana_tree_tracks->PIDA(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex)));
            if(ana_tree_truth->CCNCTruth(0) == 1 and abs(ana_tree_tracks->PDGTruth(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex))) == 211)
               hLongestTrackPIDATrueNuNCPi->Fill(ana_tree_tracks->PIDA(longestTrackIndex,ana_tree_tracks->PIDBestPlane(longestTrackIndex)));

            // Can we match a true vertex to the longest track?
            for (short i = 0; i< ana_tree_truth->MCEvtsTruth(); i++){
               hRecoTruthVtxDist->Fill(sqrt(pow(ana_tree_vtx->VertexX(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxXTruth(i),2)
                        + pow(ana_tree_vtx->VertexY(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxYTruth(i),2)
                        + pow(ana_tree_vtx->VertexZ(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxZTruth(i),2)));
               hRecoTruthVtxXDist->Fill(ana_tree_vtx->VertexX(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxXTruth(i));
               hRecoTruthVtxYDist->Fill(ana_tree_vtx->VertexY(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxYTruth(i));
               hRecoTruthVtxZDist->Fill(ana_tree_vtx->VertexZ(longestTrackMatchedVtxIndex)-ana_tree_truth->NuVtxZTruth(i));
               if(ana_tree_truth->NuPDGTruth(i) == 14)
                  hCCNCLongestTrackNuMu->Fill(ana_tree_truth->CCNCTruth(i));
               if(ana_tree_truth->NuPDGTruth(i) == -14)
                  hCCNCLongestTrackNuMuBar->Fill(ana_tree_truth->CCNCTruth(i));
               if(ana_tree_truth->NuPDGTruth(i) == 12)
                  hCCNCLongestTrackNuE->Fill(ana_tree_truth->CCNCTruth(i));
               if(ana_tree_truth->NuPDGTruth(i) == -12)
                  hCCNCLongestTrackNuEBar->Fill(ana_tree_truth->CCNCTruth(i));
            }
         }
      }








      // Fill the longest track trees
      // The GTFM cut has already been applied
      if(longestTrackLengthNuGTFM > 100 
            && ana_tree_tracks->PIDA(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 100
            && ana_tree_tracks->KE(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 100000
            && ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 1060.
            && ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) > 0.){
         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM));
         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM));
         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM));
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));
         // get distance to closest tagged cosmic track 
         double shortestTrackDistance = 999999;
         for (short j=0; j< ana_tree_tracks->NTracks(); j++){
            if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                  or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
               double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,longestTrackIndexNuGTFM,j);
               if(trackDistance < shortestTrackDistance)
                  shortestTrackDistance = trackDistance;
            }
         }
      }
      if(longestTrackLengthCosGTFM > 100
            and ana_tree_tracks->PIDA(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 100
            and ana_tree_tracks->KE(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 100000
            and ana_tree_tracks->Range(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 1060.
            and ana_tree_tracks->Range(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) > 0.){
         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM));
         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM));
         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM));
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));
         // get distance to closest tagged cosmic track 
         double shortestTrackDistance = 999999;
         for (short j=0; j< ana_tree_tracks->NTracks(); j++){
            if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                  or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
               double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,longestTrackIndexNuGTFM,j);
               if(trackDistance < shortestTrackDistance)
                  shortestTrackDistance = trackDistance;
            }
         }
      }


















      // Loop over tracks
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){

         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(i));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(i))) min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(i));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(i))) min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(i));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(i))) min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(i));

         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(i));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(i))) min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(i));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(i))) min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(i));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(i))) min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(i));

         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(i));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(i))) min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(i));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(i))) min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(i));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(i))) min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(i));
        
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));


         hTrackOriginNoCosRem->Fill(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i))); 
         hTrackLengthNoCosRem->Fill(ana_tree_tracks->Length(i));
                  

         // Was the track a true neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
            hTrackLengthTrueNuNoCosRem->Fill(ana_tree_tracks->Length(i));
            hPerpDistXBoundTrueNuNoCosRem->Fill(min_x_dist);
            hPerpDistYBoundTrueNuNoCosRem->Fill(min_y_dist);
            hPerpDistZBoundTrueNuNoCosRem->Fill(min_z_dist);
            hPerpDistToABoundTrueNuNoCosRem->Fill(min_to_a_boundary_dist);
            hTrackPIDATrueNuNoCosRem->Fill(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackPhiTrueNuNoCosRem->Fill(ana_tree_tracks->Phi(i));
            hTrackThetaTrueNuNoCosRem->Fill(ana_tree_tracks->Theta(i));
            hTrackThetaXZTrueNuNoCosRem->Fill(ana_tree_tracks->ThetaXZ(i));
            hTrackThetaYZTrueNuNoCosRem->Fill(ana_tree_tracks->ThetaYZ(i));
            hTrackRangeTrueNuNoCosRem->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackKETrueNuNoCosRem->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));
         }

         // Was the track a true cosmic?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
            hTrackLengthTrueCosNoCosRem->Fill(ana_tree_tracks->Length(i));
            hPerpDistXBoundTrueCosNoCosRem->Fill(min_x_dist);
            hPerpDistYBoundTrueCosNoCosRem->Fill(min_y_dist);
            hPerpDistZBoundTrueCosNoCosRem->Fill(min_z_dist);
            hPerpDistToABoundTrueCosNoCosRem->Fill(min_to_a_boundary_dist);
            hTrackPIDATrueCosNoCosRem->Fill(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackPhiTrueCosNoCosRem->Fill(ana_tree_tracks->Phi(i));
            hTrackThetaTrueCosNoCosRem->Fill(ana_tree_tracks->Theta(i));
            hTrackThetaXZTrueCosNoCosRem->Fill(ana_tree_tracks->ThetaXZ(i));
            hTrackThetaYZTrueCosNoCosRem->Fill(ana_tree_tracks->ThetaYZ(i));
            hTrackRangeTrueCosNoCosRem->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackKETrueCosNoCosRem->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));
         }
         







         // Does the track flunk the flash match cut?
         if(ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            hTrackOriginFM->Fill(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackLengthFM->Fill(ana_tree_tracks->Length(i));
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
               hTrackLengthTrueCosFM->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueCosFM->Fill(min_x_dist);
               hPerpDistYBoundTrueCosFM->Fill(min_y_dist);
               hPerpDistZBoundTrueCosFM->Fill(min_z_dist);
               hPerpDistToABoundTrueCosFM->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueCosFM->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueCosFM->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));


               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){

                  if(ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                     shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueCosToTaggedCosFM->Fill(shortestTrackDistance);


            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               hTrackLengthTrueNuFM->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueNuFM->Fill(min_x_dist);
               hPerpDistYBoundTrueNuFM->Fill(min_y_dist);
               hPerpDistZBoundTrueNuFM->Fill(min_z_dist);
               hPerpDistToABoundTrueNuFM->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueNuFM->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueNuFM->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){

                  if(ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                     shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueNuToTaggedCosFM->Fill(shortestTrackDistance);

            }
         }

         // Does the track flunk the geometric tagger cut?
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4){
           hTrackOriginGT->Fill(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)));
           hTrackLengthGT->Fill(ana_tree_tracks->Length(i));
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
               hTrackLengthTrueCosGT->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueCosGT->Fill(min_x_dist);
               hPerpDistYBoundTrueCosGT->Fill(min_y_dist);
               hPerpDistZBoundTrueCosGT->Fill(min_z_dist);
               hPerpDistToABoundTrueCosGT->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueCosGT->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueCosGT->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueCosToTaggedCosGT->Fill(shortestTrackDistance);



            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               hTrackLengthTrueNuGT->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueNuGT->Fill(min_x_dist);
               hPerpDistYBoundTrueNuGT->Fill(min_y_dist);
               hPerpDistZBoundTrueNuGT->Fill(min_z_dist);
               hPerpDistToABoundTrueNuGT->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueNuGT->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueNuGT->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueNuToTaggedCosGT->Fill(shortestTrackDistance);

            }
         }

         // Does the track flunk the geometric tagger and flash match cuts?
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4
              and ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            hTrackOriginGTFM->Fill(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)));
            hTrackLengthGTFM->Fill(ana_tree_tracks->Length(i));
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
               hTrackLengthTrueCosGTFM->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueCosGTFM->Fill(min_x_dist);
               hPerpDistYBoundTrueCosGTFM->Fill(min_y_dist);
               hPerpDistZBoundTrueCosGTFM->Fill(min_z_dist);
               hPerpDistToABoundTrueCosGTFM->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueCosGTFM->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueCosGTFM->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));
               
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                        or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueCosToTaggedCosGTFM->Fill(shortestTrackDistance);

            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               hTrackLengthTrueNuGTFM->Fill(ana_tree_tracks->Length(i));
               hPerpDistXBoundTrueNuGTFM->Fill(min_x_dist);
               hPerpDistYBoundTrueNuGTFM->Fill(min_y_dist);
               hPerpDistZBoundTrueNuGTFM->Fill(min_z_dist);
               hPerpDistToABoundTrueNuGTFM->Fill(min_to_a_boundary_dist);
               hTrackRangeTrueNuGTFM->Fill(ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i)));
               hTrackKETrueNuGTFM->Fill(ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)));
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                        or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }
               hNearestDistUntaggedTrueNuToTaggedCosGTFM->Fill(shortestTrackDistance);
            }
            // Was the track a true CC neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1 and 
                  ana_tree_truth->CCNCTruth(0) == 0
                  ){
               hTrackLengthTrueNuCCGTFM->Fill(ana_tree_tracks->Length(i));
            }
            // Was the track a true NC neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1 and 
                  ana_tree_truth->CCNCTruth(0) == 1
                  ){
               hTrackLengthTrueNuNCGTFM->Fill(ana_tree_tracks->Length(i));
            }
         }


         hTrackOrigin->Fill(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)));
         hTrackLength->Fill(ana_tree_tracks->Length(i));
         hTrackPhi->Fill(ana_tree_tracks->Phi(i));
         hPerpDistZBound->Fill(min_z_dist);
         hPerpDistYBound->Fill(min_y_dist);
         hPerpDistXBound->Fill(min_x_dist);
         hPerpDistToABound->Fill(min_to_a_boundary_dist);

         // Was this a muon from the neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1 and std::abs(ana_tree_tracks->PDGTruth(i,2)) == 13)
            hTrueMuonPIDA->Fill(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)));

         // Was this a pion from the neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1 and std::abs(ana_tree_tracks->PDGTruth(i,2)) == 211)
            hTruePionPIDA->Fill(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)));

         // Was this a proton from the neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1 and std::abs(ana_tree_tracks->PDGTruth(i,2)) == 2212)
            hTrueProtonPIDA->Fill(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)));


      }

   }

   std::cout << "Done, processed " << nEvtsProcessed << " events." << std::endl;
   std::cout << "Of those events " << nEvtsFiredPMTTrigger << " fired the PMT trigger." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackNu  << " of the longest tracks in each event came from a neutrino." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackCos  << " of the longest tracks in each event came from a cosmic." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackAll << " of the longest tracks in each event passed the cuts." << std::endl;

   // std::cout << "Reality check" << std::endl;
   // std::cout << "nRealityEvts0: " << nRealityEvts0 << std::endl;
   // std::cout << "nRealityEvts1: " << nRealityEvts1 << std::endl;
   // std::cout << "nRealityEvts2: " << nRealityEvts2 << std::endl;
   // std::cout << "nRealityEvts3: " << nRealityEvts3 << std::endl;
   // std::cout << "nTracksVertexMatched : " << nTracksVertexMatched <<  std::endl;
   // std::cout << "nTracksVertexLengthMatched: " << nTracksVertexLengthMatched << std::endl;


   // Write the histograms
   TFile f(fOutputFileName,"recreate");
   hNearestDistUntaggedTrueCosToTaggedCosFM->Write();
   hNearestDistUntaggedTrueCosToTaggedCosGT->Write();
   hNearestDistUntaggedTrueCosToTaggedCosGTFM->Write();
   hNearestDistUntaggedTrueNuToTaggedCosFM->Write();
   hNearestDistUntaggedTrueNuToTaggedCosGT->Write();
   hNearestDistUntaggedTrueNuToTaggedCosGTFM->Write();
   hNTracks->Write();




   f.cd();
   f.mkdir("mc_truth");
   f.cd("mc_truth");
   hMCEvtsTruth->Write();
   hNuPDGTruth->Write();
   hCCNCTruth->Write(); 
   hRecoTruthVtxDist->Write();
   hRecoTruthVtxXDist->Write();
   hRecoTruthVtxYDist->Write();
   hRecoTruthVtxZDist->Write();
   hCCNCLongestTrackNuMu->Write();
   hCCNCLongestTrackNuMuBar->Write();
   hCCNCLongestTrackNuE->Write();
   hCCNCLongestTrackNuEBar->Write();

   f.cd();
   f.mkdir("track_origins");
   f.cd("track_origins");
   
   hTrackOrigin->Write();
   hLongestTrackOrigin->Write();
   hLepMomTruth->Write();
   hTrackOriginNoCosRem->Write();
   hTrackOriginFM->Write();
   hTrackOriginGT->Write();
   hTrackOriginGTFM->Write();



   f.cd();
   f.mkdir("track_lengths");
   f.cd("track_lengths");

   hTrackLength->Write();
   hTrackLengthNoCosRem->Write();
   hTrackLengthFM->Write();
   hTrackLengthGT->Write();
   hTrackLengthGTFM->Write();
   hTrackLengthTrueCosNoCosRem->Write();
   hTrackLengthTrueCosFM->Write();
   hTrackLengthTrueCosGT->Write();
   hTrackLengthTrueCosGTFM->Write();
   hTrackLengthTrueNuNoCosRem->Write();
   hTrackLengthTrueNuFM->Write();
   hTrackLengthTrueNuGT->Write();
   hTrackLengthTrueNuGTFM->Write();
   hTrackLengthTrueNuCCNoCosRem->Write();
   hTrackLengthTrueNuCCFM->Write();
   hTrackLengthTrueNuCCGT->Write();
   hTrackLengthTrueNuCCGTFM->Write();
   hTrackLengthTrueNuNCNoCosRem->Write();
   hTrackLengthTrueNuNCFM->Write();
   hTrackLengthTrueNuNCGT->Write();
   hTrackLengthTrueNuNCGTFM->Write();
   hLongestTrackLengthTrueNu->Write();
   hLongestTrackLengthTrueNuCC->Write();
   hLongestTrackLengthTrueNuNC->Write();
   hLongestTrackLengthTrueCos->Write();

   f.cd();
   f.mkdir("track_boundaries");
   f.cd("track_boundaries");

   hPerpDistXBound->Write();
   hPerpDistYBound->Write();
   hPerpDistZBound->Write();
   hPerpDistToABound->Write();

   hPerpDistXBoundTrueNuNoCosRem->Write();
   hPerpDistXBoundTrueNuFM->Write();
   hPerpDistXBoundTrueNuGT->Write();
   hPerpDistXBoundTrueNuGTFM->Write();
   hPerpDistYBoundTrueNuNoCosRem->Write();
   hPerpDistYBoundTrueNuFM->Write();
   hPerpDistYBoundTrueNuGT->Write();
   hPerpDistYBoundTrueNuGTFM->Write();
   hPerpDistZBoundTrueNuNoCosRem->Write();
   hPerpDistZBoundTrueNuFM->Write();
   hPerpDistZBoundTrueNuGT->Write();
   hPerpDistZBoundTrueNuGTFM->Write();
   hPerpDistToABoundTrueNuNoCosRem->Write();
   hPerpDistToABoundTrueNuFM->Write();
   hPerpDistToABoundTrueNuGT->Write();
   hPerpDistToABoundTrueNuGTFM->Write();

   hPerpDistXBoundTrueCosNoCosRem->Write();
   hPerpDistXBoundTrueCosFM->Write();
   hPerpDistXBoundTrueCosGT->Write();
   hPerpDistXBoundTrueCosGTFM->Write();
   hPerpDistYBoundTrueCosNoCosRem->Write();
   hPerpDistYBoundTrueCosFM->Write();
   hPerpDistYBoundTrueCosGT->Write();
   hPerpDistYBoundTrueCosGTFM->Write();
   hPerpDistZBoundTrueCosNoCosRem->Write();
   hPerpDistZBoundTrueCosFM->Write();
   hPerpDistZBoundTrueCosGT->Write();
   hPerpDistZBoundTrueCosGTFM->Write();
   hPerpDistToABoundTrueCosNoCosRem->Write();
   hPerpDistToABoundTrueCosFM->Write();
   hPerpDistToABoundTrueCosGT->Write();
   hPerpDistToABoundTrueCosGTFM->Write();


   f.cd();
   f.mkdir("track_calo_pid");
   f.cd("track_calo_pid");

   hTrackPIDATrueNuNoCosRem->Write();
   hTrackPIDATrueCosNoCosRem->Write();
   hTrueMuonPIDA->Write();
   hTruePionPIDA->Write();
   hTrueProtonPIDA->Write();
   hLongestTrackPIDA->Write();
   hLongestTrackPIDATrueNuCCMu->Write();
   hLongestTrackPIDATrueNuNCMu->Write();
   hLongestTrackPIDATrueNuCCPi->Write();
   hLongestTrackPIDATrueNuNCPi->Write();
   hTrackRangeTrueCosNoCosRem->Write();
   hTrackRangeTrueCosFM->Write();
   hTrackRangeTrueCosGT->Write();
   hTrackRangeTrueCosGTFM->Write();
   hTrackRangeTrueNuNoCosRem->Write();
   hTrackRangeTrueNuFM->Write();
   hTrackRangeTrueNuGT->Write();
   hTrackRangeTrueNuGTFM->Write();
   hTrackKETrueCosNoCosRem->Write();
   hTrackKETrueCosFM->Write();
   hTrackKETrueCosGT->Write();
   hTrackKETrueCosGTFM->Write();
   hTrackKETrueNuNoCosRem->Write();
   hTrackKETrueNuFM->Write();
   hTrackKETrueNuGT->Write();
   hTrackKETrueNuGTFM->Write();

   f.cd();
   f.mkdir("track_angles");
   f.cd("track_angles");

   hTrackPhi->Write();
   hTrackThetaTrueNuNoCosRem->Write();
   hTrackThetaTrueCosNoCosRem->Write();
   hTrackThetaXZTrueNuNoCosRem->Write();
   hTrackThetaXZTrueCosNoCosRem->Write();
   hTrackThetaYZTrueNuNoCosRem->Write();
   hTrackThetaYZTrueCosNoCosRem->Write();
   hTrackPhiTrueNuNoCosRem->Write();
   hTrackPhiTrueCosNoCosRem->Write();

   f.cd();
   f.mkdir("track_vertices");
   f.cd("track_vertices");

   hLongestTrackNearestVtxDistTrueNuCC->Write();
   hLongestTrackNearestVtxDistTrueNuNC->Write();
   hLongestTrackNearestVtxDistTrueCos->Write();

   // Close the file
   f.Close();


}






