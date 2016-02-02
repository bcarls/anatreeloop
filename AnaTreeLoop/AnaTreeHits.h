
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
      Short_t HitPlane(short i){ return fHitPlane[i];}
      Short_t HitWire(short i){ return fHitWire[i];}
      Float_t HitStartTick(short i){ return fHitStartTick[i];}
      Float_t HitEndTick(short i){ return fHitEndTick[i];}
      Short_t HitTrackKey(short i){ return fHitTrackKey[i];}
      Short_t HitClusterKey(short i){ return fHitClusterKey[i];}
      Float_t HitCharge(short i){ return fHitCharge[i];}
      Short_t HitMultiplicity(short i){ return fHitMultiplicity[i];}

   private:

      Int_t   fNHits;
      Short_t fHitPlane[kMaxHits];
      Short_t fHitWire[kMaxHits];
      Float_t fHitStartTick[kMaxHits];
      Float_t fHitEndTick[kMaxHits];
      Short_t fHitTrackKey[kMaxHits];
      Short_t fHitClusterKey[kMaxHits];
      Float_t fHitCharge[kMaxHits];
      Short_t fHitMultiplicity[kMaxHits];

};


#endif // #ifdef AnaTreeHits_cxx
