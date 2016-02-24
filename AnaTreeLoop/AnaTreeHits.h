
#ifndef AnaTreeHits_h
#define AnaTreeHits_h

#include <TROOT.h>
#include <TChain.h>

constexpr int kMaxHits = 40000;

class AnaTreeHits {

   public:

      /// Constructor
      AnaTreeHits(TTree *fChain);

      Int_t NHits() {return fNHits;}

      // Hit variables
      Short_t HitPlane(int i){ return fHitPlane[i];}
      Short_t HitWire(int i){ return fHitWire[i];}
      Short_t HitChannel(int i){ return fHitChannel[i];}
      Float_t HitStartTick(int i){ return fHitStartTick[i];}
      Float_t HitEndTick(int i){ return fHitEndTick[i];}
      Short_t HitTrackKey(int i){ return fHitTrackKey[i];}
      Short_t HitClusterKey(int i){ return fHitClusterKey[i];}
      Float_t HitCharge(int i){ return fHitCharge[i];}
      Float_t HitPeakCharge(int i){ return fHitPeakCharge[i];}
      Short_t HitMultiplicity(int i){ return fHitMultiplicity[i];}

   private:

      Int_t   fNHits;
      Short_t fHitPlane[kMaxHits];
      Short_t fHitWire[kMaxHits];
      Short_t fHitChannel[kMaxHits];
      Float_t fHitStartTick[kMaxHits];
      Float_t fHitEndTick[kMaxHits];
      Short_t fHitTrackKey[kMaxHits];
      Short_t fHitClusterKey[kMaxHits];
      Float_t fHitCharge[kMaxHits];
      Float_t fHitPeakCharge[kMaxHits];
      Short_t fHitMultiplicity[kMaxHits];

};


#endif // #ifdef AnaTreeHits_cxx
