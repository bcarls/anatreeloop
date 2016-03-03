
#ifndef AnaTreeTruth_h
#define AnaTreeTruth_h

#include <TROOT.h>
#include <TChain.h>

static const Int_t kMaxTruth = 10;

class AnaTreeTruth {

   public:

      /// Constructor
      AnaTreeTruth(TTree *fChain);

      Int_t MCEvtsTruth(){return fMCEvtsTruth;}
      Int_t NuPDGTruth(short i){return fNuPDGTruth[i];}
      Int_t CCNCTruth(short i){return fCCNCTruth[i];}
      Float_t ENuTruth(short i){return fENuTruth[i];}
      Float_t NuVtxXTruth(short i){return fNuVtxXTruth[i];}
      Float_t NuVtxYTruth(short i){return fNuVtxYTruth[i];}
      Float_t NuVtxZTruth(short i){return fNuVtxZTruth[i];}
      Float_t LepMomTruth(short i){return fLepMomTruth[i];}

   private:

      Int_t   fMCEvtsTruth;
      Int_t   fNuPDGTruth[kMaxTruth];
      Int_t   fCCNCTruth[kMaxTruth];
      Float_t fENuTruth[kMaxTruth];
      Float_t fNuVtxXTruth[kMaxTruth];
      Float_t fNuVtxYTruth[kMaxTruth];
      Float_t fNuVtxZTruth[kMaxTruth];
      Float_t fLepMomTruth[kMaxTruth];

};


#endif // #ifdef AnaTreeTruth_cxx
