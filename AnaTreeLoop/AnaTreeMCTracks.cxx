#define AnaTreeMCTracks_cxx
#include "AnaTreeMCTracks.h"


AnaTreeMCTracks::AnaTreeMCTracks(TTree *fChain) {

   fChain->SetBranchStatus("no_mctracks",1);
   fChain->SetBranchStatus("mctrk_origin",1);
   fChain->SetBranchStatus("mctrk_pdg",1);
   fChain->SetBranchStatus("mctrk_TrackId",1);
   fChain->SetBranchStatus("mctrk_len_drifted",1);

   fChain->SetBranchAddress("no_mctracks",&fNMCTracks);
   fChain->SetBranchAddress("mctrk_origin",&fOrigin);
   fChain->SetBranchAddress("mctrk_pdg",&fPDGTruth);
   fChain->SetBranchAddress("mctrk_TrackId",&fID);
   fChain->SetBranchAddress("mctrk_len_drifted",&fLengthDrifted);
   
}


