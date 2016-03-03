#define AnaTreeMCTracks_cxx
#include "AnaTreeMCTracks.h"

#include <TVector3.h>

AnaTreeMCTracks::AnaTreeMCTracks(TTree *fChain) {

   fChain->SetBranchStatus("no_mctracks",1);
   fChain->SetBranchStatus("mctrk_origin",1);
   fChain->SetBranchStatus("mctrk_pdg",1);
   fChain->SetBranchStatus("mctrk_TrackId",1);
   fChain->SetBranchStatus("mctrk_len_drifted",1);
   fChain->SetBranchStatus("mctrk_px_drifted",1);
   fChain->SetBranchStatus("mctrk_py_drifted",1);
   fChain->SetBranchStatus("mctrk_pz_drifted",1);

   fChain->SetBranchAddress("no_mctracks",&fNMCTracks);
   fChain->SetBranchAddress("mctrk_origin",&fOrigin);
   fChain->SetBranchAddress("mctrk_pdg",&fPDGTruth);
   fChain->SetBranchAddress("mctrk_TrackId",&fID);
   fChain->SetBranchAddress("mctrk_len_drifted",&fLengthDrifted);
   fChain->SetBranchAddress("mctrk_px_drifted",&fPxDrifted);
   fChain->SetBranchAddress("mctrk_py_drifted",&fPyDrifted);
   fChain->SetBranchAddress("mctrk_pz_drifted",&fPzDrifted);
   
}


Double_t AnaTreeMCTracks::Phi(int i){
   TVector3 dir = TVector3(fEndX[i]-fStartX[i],fEndY[i]-fStartY[i],fEndZ[i]-fStartZ[i]);
   return dir.Phi();
}

Double_t AnaTreeMCTracks::Theta(int i){
   TVector3 dir = TVector3(fEndX[i]-fStartX[i],fEndY[i]-fStartY[i],fEndZ[i]-fStartZ[i]);
   return dir.Theta();
}



