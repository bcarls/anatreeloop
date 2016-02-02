#define AnaTreeFlash_cxx
#include "AnaTreeFlash.h"


AnaTreeFlash::AnaTreeFlash(TTree *fChain) {
   fChain->SetBranchAddress("no_flashes",&fNFlashes);
   fChain->SetBranchAddress("flash_time",&fFlashTime);
   fChain->SetBranchAddress("flash_pe",&fFlashPE);
   fChain->SetBranchAddress("flash_ycenter",&fFlashYCenter);
   fChain->SetBranchAddress("flash_zcenter",&fFlashZCenter);
}


