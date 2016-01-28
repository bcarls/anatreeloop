
#ifndef AnaTreeRunInfo_h
#define AnaTreeRunInfo_h

#include <root/TROOT.h>
#include <root/TChain.h>

class AnaTreeRunInfo {

   public:

      /// Constructor
      AnaTreeRunInfo(TTree *fChain);

      Int_t Run() {return fRun;}
      Int_t Subrun() {return fSubrun;}
      Int_t Event() {return fEvent;}

   private:

      Int_t fRun;
      Int_t fSubrun;
      Int_t fEvent;
};


#endif // #ifdef AnaTreeRunInfo_cxx
