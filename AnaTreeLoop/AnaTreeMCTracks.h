
#ifndef AnaTreeMCTracks_h
#define AnaTreeMCTracks_h

#include <TROOT.h>
#include <TChain.h>

constexpr int kMaxMCTracks = 1000;

class AnaTreeMCTracks {

   public:

      /// Constructor
      AnaTreeMCTracks(TTree *fChain);

      Short_t NMCTracks() {return fNMCTracks;}
     
      // Track variables
      Int_t ID(int i){ return fID[i];}
      Int_t Origin(int i){ return fOrigin[i];}
      Float_t LengthDrifted(int i){ return fLengthDrifted[i];}
      Int_t PDGTruth(int i){ return fPDGTruth[i];}

   private:

      Int_t                     fNMCTracks;
      Int_t                     fOrigin[kMaxMCTracks];
      Int_t                     fPDGTruth[kMaxMCTracks];
      Int_t                     fID[kMaxMCTracks];
      Float_t                   fLengthDrifted[kMaxMCTracks];

};


#endif // #ifdef AnaTreeMCTracks_cxx
