
#ifndef AnaTreeTracks_h
#define AnaTreeTracks_h

#include <TROOT.h>
#include <TChain.h>

constexpr int kMaxTracks = 500;
constexpr int kMaxTrackHits = 2000;

class AnaTreeTracks {

   public:

      /// Constructor
      AnaTreeTracks(TTree *fChain,TString fTrackModule);

      Short_t NTracks() {return fNTracks;}

      // Tagging variables
      Short_t NCosmicTagsTagger(short i){ return fNCosmicTagsTagger[i];}
      Float_t CosmicScoreTagger(short i){ return fCosmicScoreTagger[i];}
      Short_t CosmicTypeTagger(short i){ return fCosmicTypeTagger[i];}
      Short_t NCosmicTagsFlashMatch(short i){ return fNCosmicTagsFlashMatch[i];}
      Float_t CosmicScoreFlashMatch(short i){ return fCosmicScoreFlashMatch[i];}
      Short_t CosmicTypeFlashMatch(short i){ return fCosmicTypeFlashMatch[i];}
     
      // Track variables
      Short_t ID(short i){ return fID[i];}
      Float_t Length(short i){ return fLength[i];}
      Float_t Phi(short i){ return fPhi[i];}
      Float_t Theta(short i){ return fTheta[i];}
      Float_t ThetaXZ(short i){ return fThetaXZ[i];}
      Float_t ThetaYZ(short i){ return fThetaYZ[i];}
      Float_t StartX(short i){ return fStartX[i];}
      Float_t StartY(short i){ return fStartY[i];}
      Float_t StartZ(short i){ return fStartZ[i];}
      Float_t EndX(short i){ return fEndX[i];}
      Float_t EndY(short i){ return fEndY[i];}
      Float_t EndZ(short i){ return fEndZ[i];}
      Float_t Range(short i,short plane){ return fTrackRange[i][plane];}
      Float_t Pitch(short i,short plane){ return fTrackPitch[i][plane];}
      Float_t KE(short i,short plane){ return fTrackKE[i][plane];}
      Float_t PIDA(short i, short plane){ return fPIDA[i][plane];}
      Float_t Origin(short i,short plane){ return fOrigin[i][plane];}
      Int_t   PDGTruth(short i,short plane){ return fPDGTruth[i][plane];}
      Short_t PIDBestPlane(short i){ return fPIDBestPlane[i];}
      Short_t NTrackHits(short i, short plane){ return fNTrackHits[i][plane];}

      // Track "HitData" and "HitCoordData" variables
      Float_t TrackHitdEdx(short i, short plane, short j){return fTrackHitdEdx[i][plane][j];}
      Float_t TrackHitdQdx(short i, short plane, short j){return fTrackHitdQdx[i][plane][j];}
      Float_t TrackHitXYZ(short i, short plane, short j, short hitplane){return fTrackHitXYZ[i][plane][j][hitplane];}

   private:

      Short_t fID[kMaxTracks];
      Float_t fLength[kMaxTracks];
      Float_t fPhi[kMaxTracks];
      Float_t fTheta[kMaxTracks];
      Float_t fThetaXZ[kMaxTracks];
      Float_t fThetaYZ[kMaxTracks];
      Float_t fStartX[kMaxTracks];
      Float_t fStartY[kMaxTracks];
      Float_t fStartZ[kMaxTracks];
      Float_t fEndX[kMaxTracks];
      Float_t fEndY[kMaxTracks];
      Float_t fEndZ[kMaxTracks];
      Short_t fNCosmicTagsTagger[kMaxTracks];
      Float_t fCosmicScoreTagger[kMaxTracks];
      Short_t fCosmicTypeTagger[kMaxTracks];
      Short_t fNCosmicTagsFlashMatch[kMaxTracks];
      Float_t fCosmicScoreFlashMatch[kMaxTracks];
      Short_t fCosmicTypeFlashMatch[kMaxTracks];
      Float_t fTrackRange[kMaxTracks][3];
      Float_t fTrackPitch[kMaxTracks][3];
      Float_t fTrackKE[kMaxTracks][3];
      Short_t fOrigin[kMaxTracks][3];
      Float_t fPIDA[kMaxTracks][3];
      Int_t   fPDGTruth[kMaxTracks][3];
      Short_t fPIDBestPlane[kMaxTracks];
      Short_t fNTrackHits[kMaxTracks][3];
      Short_t fNTracks;
      Float_t fTrackHitdEdx[kMaxTracks][3][kMaxTrackHits];
      Float_t fTrackHitdQdx[kMaxTracks][3][kMaxTrackHits];
      Float_t fTrackHitXYZ[kMaxTracks][3][kMaxTrackHits][3];
};


#endif // #ifdef AnaTreeTracks_cxx
