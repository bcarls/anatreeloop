#define AnaTreeRunInfo_cxx
#include "AnaTreeRunInfo.h"


AnaTreeRunInfo::AnaTreeRunInfo(TTree *fChain) {

   fChain->SetBranchStatus("run",1);
   fChain->SetBranchStatus("subrun",1);
   fChain->SetBranchStatus("event",1);
   fChain->SetBranchStatus("evttime",1);
   
   fChain->SetBranchAddress("run",&fRun);
   fChain->SetBranchAddress("subrun",&fSubrun);
   fChain->SetBranchAddress("event",&fEvent);
   fChain->SetBranchAddress("evttime",&fEventTime);
}


