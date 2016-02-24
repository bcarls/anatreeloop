#define AnaTreeFlash_cxx
#include "AnaTreeFlash.h"


AnaTreeFlash::AnaTreeFlash(TTree *fChain) {

   fChain->SetBranchStatus("no_flashes",1);
   fChain->SetBranchStatus("flash_time",1);
   fChain->SetBranchStatus("flash_pe",1);
   fChain->SetBranchStatus("flash_ycenter",1);
   fChain->SetBranchStatus("flash_zcenter",1);
   
   fChain->SetBranchAddress("no_flashes",&fNFlashes);
   fChain->SetBranchAddress("flash_time",&fFlashTime);
   fChain->SetBranchAddress("flash_pe",&fFlashPE);
   fChain->SetBranchAddress("flash_ycenter",&fFlashYCenter);
   fChain->SetBranchAddress("flash_zcenter",&fFlashZCenter);
}


