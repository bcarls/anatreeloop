
#ifndef AnaTreeFlash_h
#define AnaTreeFlash_h

#include <TROOT.h>
#include <TChain.h>

constexpr int kMaxFlashes = 1000;

class AnaTreeFlash {

   public:

      /// Constructor
      AnaTreeFlash(TTree *fChain);

      Int_t NFlashes() {return fNFlashes;}
      Float_t FlashTime(int i) {return fFlashTime[i];}
      Float_t FlashPE(int i) {return fFlashPE[i];}
      Float_t FlashYCenter(int i) {return fFlashYCenter[i];}
      Float_t FlashZCenter(int i) {return fFlashZCenter[i];}

   private:

      Int_t fNFlashes;
      Float_t fFlashTime[kMaxFlashes];
      Float_t fFlashPE[kMaxFlashes];
      Float_t fFlashYCenter[kMaxFlashes];
      Float_t fFlashZCenter[kMaxFlashes];

};


#endif // #ifdef AnaTreeFlash_cxx
