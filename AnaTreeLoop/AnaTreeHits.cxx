#define AnaTreeHits_cxx
#include "AnaTreeHits.h"


AnaTreeHits::AnaTreeHits(TTree *fChain) {

   fChain->SetBranchStatus("no_hits",1);
   fChain->SetBranchStatus("hit_plane",1);
   fChain->SetBranchStatus("hit_wire",1);
   fChain->SetBranchStatus("hit_channel",1);
   fChain->SetBranchStatus("hit_startT",1);
   fChain->SetBranchStatus("hit_endT",1);
   fChain->SetBranchStatus("hit_trkKey",1);
   fChain->SetBranchStatus("hit_clusterKey",1);
   fChain->SetBranchStatus("hit_charge",1);
   fChain->SetBranchStatus("hit_ph",1);
   fChain->SetBranchStatus("hit_multiplicity",1);
   
   fChain->SetBranchAddress("no_hits",&fNHits);
   fChain->SetBranchAddress("hit_plane",&fHitPlane);
   fChain->SetBranchAddress("hit_wire",&fHitWire);
   fChain->SetBranchAddress("hit_channel",&fHitChannel);
   fChain->SetBranchAddress("hit_startT",&fHitStartTick);
   fChain->SetBranchAddress("hit_endT",&fHitEndTick);
   fChain->SetBranchAddress("hit_trkKey",&fHitTrackKey);
   fChain->SetBranchAddress("hit_clusterKey",&fHitClusterKey);
   fChain->SetBranchAddress("hit_charge",&fHitCharge);
   fChain->SetBranchAddress("hit_ph",&fHitPeakCharge);
   fChain->SetBranchAddress("hit_multiplicity",&fHitMultiplicity);
}


