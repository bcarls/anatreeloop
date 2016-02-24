#define AnaTreeTruth_cxx
#include "AnaTreeTruth.h"


AnaTreeTruth::AnaTreeTruth(TTree *fChain) {
   fChain->SetBranchStatus("mcevts_truth",1);
   fChain->SetBranchStatus("nuPDG_truth",1);
   fChain->SetBranchStatus("ccnc_truth",1);
   fChain->SetBranchStatus("nuvtxx_truth",1);
   fChain->SetBranchStatus("nuvtxy_truth",1);
   fChain->SetBranchStatus("nuvtxz_truth",1);
   fChain->SetBranchStatus("lep_mom_truth",1);

   fChain->SetBranchAddress("mcevts_truth",&fMCEvtsTruth);
   fChain->SetBranchAddress("nuPDG_truth",&fNuPDGTruth);
   fChain->SetBranchAddress("ccnc_truth",&fCCNCTruth);
   fChain->SetBranchAddress("nuvtxx_truth",&fNuVtxXTruth);
   fChain->SetBranchAddress("nuvtxy_truth",&fNuVtxYTruth);
   fChain->SetBranchAddress("nuvtxz_truth",&fNuVtxZTruth);
   fChain->SetBranchAddress("lep_mom_truth",&fLepMomTruth);

}


