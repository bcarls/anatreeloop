
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
      Float_t PxDrifted(int i){ return fPxDrifted[i];}
      Float_t PyDrifted(int i){ return fPyDrifted[i];}
      Float_t PzDrifted(int i){ return fPzDrifted[i];}
      Int_t PDGTruth(int i){ return fPDGTruth[i];}
      Float_t StartX(int i){ return fStartX[i];}
      Float_t StartY(int i){ return fStartY[i];}
      Float_t StartZ(int i){ return fStartZ[i];}
      Float_t EndX(int i){ return fEndX[i];}
      Float_t EndY(int i){ return fEndY[i];}
      Float_t EndZ(int i){ return fEndZ[i];}
      Double_t Phi(int i); 
      Double_t Theta(int i); 

   private:

      Int_t                     fNMCTracks;
      Int_t                     fOrigin[kMaxMCTracks];
      Int_t                     fPDGTruth[kMaxMCTracks];
      Int_t                     fID[kMaxMCTracks];
      Float_t                   fLengthDrifted[kMaxMCTracks];
      Float_t                   fPxDrifted[kMaxMCTracks];
      Float_t                   fPyDrifted[kMaxMCTracks];
      Float_t                   fPzDrifted[kMaxMCTracks];
      Float_t                   fStartX[kMaxMCTracks];
      Float_t                   fStartY[kMaxMCTracks];
      Float_t                   fStartZ[kMaxMCTracks];
      Float_t                   fEndX[kMaxMCTracks];
      Float_t                   fEndY[kMaxMCTracks];
      Float_t                   fEndZ[kMaxMCTracks];

};

#endif // #ifdef AnaTreeMCTracks_cxx
