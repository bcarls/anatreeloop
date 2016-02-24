
#ifndef AnaTreeRunInfo_h
#define AnaTreeRunInfo_h

#include <TROOT.h>
#include <TChain.h>

class AnaTreeRunInfo {

   public:

      /// Constructor
      AnaTreeRunInfo(TTree *fChain);

      Int_t Run() {return fRun;}
      Int_t Subrun() {return fSubrun;}
      Int_t Event() {return fEvent;}
      Double_t EventTime() {return fEventTime;}

   private:

      Int_t fRun;
      Int_t fSubrun;
      Int_t fEvent;
      Double_t fEventTime;
};


#endif // #ifdef AnaTreeRunInfo_cxx
