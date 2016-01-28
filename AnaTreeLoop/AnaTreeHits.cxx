#define AnaTreeHits_cxx
#include "AnaTreeHits.h"


AnaTreeHits::AnaTreeHits(TTree *fChain) {
   fChain->SetBranchAddress("no_hits",&fNHits);
   fChain->SetBranchAddress("hit_plane",&fHitPlane);
   fChain->SetBranchAddress("hit_wire",&fHitWire);
   fChain->SetBranchAddress("hit_startT",&fHitStartTick);
   fChain->SetBranchAddress("hit_endT",&fHitEndTick);
   fChain->SetBranchAddress("hit_trkKey",&fHitTrackKey);
   fChain->SetBranchAddress("hit_clusterKey",&fHitClusterKey);
   fChain->SetBranchAddress("hit_charge",&fHitCharge);
   fChain->SetBranchAddress("hit_multiplicity",&fHitMultiplicity);
}


