#define AnaTreeRunInfo_cxx
#include "AnaTreeRunInfo.h"


AnaTreeRunInfo::AnaTreeRunInfo(TTree *fChain) {
   fChain->SetBranchAddress("run",&fRun);
   fChain->SetBranchAddress("subrun",&fSubrun);
   fChain->SetBranchAddress("event",&fEvent);
   
}


