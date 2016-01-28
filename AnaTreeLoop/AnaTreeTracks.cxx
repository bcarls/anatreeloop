#define AnaTreeTracks_cxx
#include "AnaTreeTracks.h"


AnaTreeTracks::AnaTreeTracks(TTree *fChain,TString fTrackModule) {
   fChain->SetBranchAddress("ntracks_"+fTrackModule,&fNTracks);
   fChain->SetBranchAddress("trkId_"+fTrackModule,&fID);
   fChain->SetBranchAddress("trkphi_"+fTrackModule,&fPhi);
   fChain->SetBranchAddress("trktheta_"+fTrackModule,&fTheta);
   fChain->SetBranchAddress("trkthetaxz_"+fTrackModule,&fThetaXZ);
   fChain->SetBranchAddress("trkthetayz_"+fTrackModule,&fThetaYZ);
   fChain->SetBranchAddress("trklen_"+fTrackModule,&fLength);
   fChain->SetBranchAddress("trkstartx_"+fTrackModule,&fStartX);
   fChain->SetBranchAddress("trkstarty_"+fTrackModule,&fStartY);
   fChain->SetBranchAddress("trkstartz_"+fTrackModule,&fStartZ);
   fChain->SetBranchAddress("trkendx_"+fTrackModule,&fEndX);
   fChain->SetBranchAddress("trkendy_"+fTrackModule,&fEndY);
   fChain->SetBranchAddress("trkendz_"+fTrackModule,&fEndZ);
   fChain->SetBranchAddress("trkncosmictags_tagger_"+fTrackModule,&fNCosmicTagsTagger);
   fChain->SetBranchAddress("trkcosmicscore_tagger_"+fTrackModule,&fCosmicScoreTagger);
   fChain->SetBranchAddress("trkcosmictype_tagger_"+fTrackModule,&fCosmicTypeTagger);
   fChain->SetBranchAddress("trkncosmictags_flashmatch_"+fTrackModule,&fNCosmicTagsFlashMatch);
   fChain->SetBranchAddress("trkcosmicscore_flashmatch_"+fTrackModule,&fCosmicScoreFlashMatch);
   fChain->SetBranchAddress("trkcosmictype_flashmatch_"+fTrackModule,&fCosmicTypeFlashMatch);
   fChain->SetBranchAddress("trkrange_"+fTrackModule,&fTrackRange);
   fChain->SetBranchAddress("trkpitchc_"+fTrackModule,&fTrackPitch);
   fChain->SetBranchAddress("trkke_"+fTrackModule,&fTrackKE);
   fChain->SetBranchAddress("trkpidpida_"+fTrackModule,&fPIDA);
   fChain->SetBranchAddress("trkpdgtruth_"+fTrackModule,&fPDGTruth);
   fChain->SetBranchAddress("trkorigin_"+fTrackModule,&fOrigin);
   fChain->SetBranchAddress("trkpidbestplane_"+fTrackModule,&fPIDBestPlane);
   fChain->SetBranchAddress("ntrkhits_"+fTrackModule,&fNTrackHits);
   fChain->SetBranchAddress("trkdedx_"+fTrackModule,&fTrackHitdEdx);
   fChain->SetBranchAddress("trkdqdx_"+fTrackModule,&fTrackHitdQdx);
   fChain->SetBranchAddress("trkxyz_"+fTrackModule,&fTrackHitXYZ);
   
}


