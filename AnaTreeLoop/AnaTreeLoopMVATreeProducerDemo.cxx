#define AnaTreeLoopMVATreeProducerDemo_cxx
#include "AnaTreeLoopMVATreeProducerDemo.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>



void AnaTreeLoopMVATreeProducerDemo::Loop()
{

   TFile fTMVATrees(fOutputTreeFileName,"recreate");

   TTree tAll("tAll","Tree containing all track data");
   Float_t trackLengthAll, trackPerpDistXBoundAll, trackPerpDistYBoundAll, trackPerpDistZBoundAll,
            trackPerpDistToABoundAll, trackPIDAAll, trackRangeAll, trackKEAll, trackPhiAll, trackThetaAll, trackThetaXZAll,
            trackThetaYZAll, weightAll;
   Int_t trackTaggedCosAllGT;
   Int_t trackTaggedCosAllGTFM;
   Int_t trackOriginAll;
   tAll.Branch("trackLength",&trackLengthAll,"trackLength/F");
   tAll.Branch("trackPerpDistXBound",&trackPerpDistXBoundAll,"trackPerpDistXBound/F");
   tAll.Branch("trackPerpDistYBound",&trackPerpDistYBoundAll,"trackPerpDistYBound/F");
   tAll.Branch("trackPerpDistZBound",&trackPerpDistZBoundAll,"trackPerpDistZBound/F");
   tAll.Branch("trackPerpDistToABound",&trackPerpDistToABoundAll,"trackPerpDistToABound/F");
   tAll.Branch("trackPIDA",&trackPIDAAll,"trackPIDA/F");
   tAll.Branch("trackRange",&trackRangeAll,"trackRange/F");
   tAll.Branch("trackKE",&trackKEAll,"trackKE/F");
   tAll.Branch("trackPhi",&trackPhiAll,"trackPhi/F");
   tAll.Branch("trackTheta",&trackThetaAll,"trackTheta/F");
   tAll.Branch("trackThetaXZ",&trackThetaXZAll,"trackThetaXZ/F");
   tAll.Branch("trackThetaYZ",&trackThetaYZAll,"trackThetaYZ/F");
   tAll.Branch("trackOrigin",&trackOriginAll,"trackOrigin/I");
   tAll.Branch("trackTaggedCosGT",&trackTaggedCosAllGT,"trackTaggedCosGT/I");
   tAll.Branch("trackTaggedCosGTFM",&trackTaggedCosAllGTFM,"trackTaggedCosGTFM/I");
   tAll.Branch("weight",&weightAll,"weight/F");


   TTree tTrueNu("tTrueNu","Tree containing true neutrino track data");
   TTree tTrueCos("tTrueCos","Tree containing true cosmic track data");
   Float_t trackLengthTrueNu, trackPerpDistXBoundTrueNu, trackPerpDistYBoundTrueNu, trackPerpDistZBoundTrueNu,
            trackPerpDistToABoundTrueNu, trackPIDATrueNu, trackRangeTrueNu, trackKETrueNu, trackPhiTrueNu, trackThetaTrueNu, trackThetaXZTrueNu, trackThetaYZTrueNu;
   Float_t trackLengthTrueCos, trackPerpDistXBoundTrueCos, trackPerpDistYBoundTrueCos, trackPerpDistZBoundTrueCos,
            trackPerpDistToABoundTrueCos, trackPIDATrueCos, trackRangeTrueCos, trackKETrueCos, trackPhiTrueCos, trackThetaTrueCos, trackThetaXZTrueCos, trackThetaYZTrueCos, weightTrueCos;
   tTrueNu.Branch("trackLength",&trackLengthTrueNu,"trackLength/F");
   tTrueNu.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNu,"trackPerpDistXBound/F");
   tTrueNu.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNu,"trackPerpDistYBound/F");
   tTrueNu.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNu,"trackPerpDistZBound/F");
   tTrueNu.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNu,"trackPerpDistToABound/F");
   tTrueNu.Branch("trackPIDA",&trackPIDATrueNu,"trackPIDA/F");
   tTrueNu.Branch("trackRange",&trackRangeTrueNu,"trackRange/F");
   tTrueNu.Branch("trackKE",&trackKETrueNu,"trackKE/F");
   tTrueNu.Branch("trackPhi",&trackPhiTrueNu,"trackPhi/F");
   tTrueNu.Branch("trackTheta",&trackThetaTrueNu,"trackTheta/F");
   tTrueNu.Branch("trackThetaXZ",&trackThetaXZTrueNu,"trackThetaXZ/F");
   tTrueNu.Branch("trackThetaYZ",&trackThetaYZTrueNu,"trackThetaYZ/F");

   tTrueCos.Branch("trackLength",&trackLengthTrueCos,"trackLength/F");
   tTrueCos.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCos,"trackPerpDistXBound/F");
   tTrueCos.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCos,"trackPerpDistYBound/F");
   tTrueCos.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCos,"trackPerpDistZBound/F");
   tTrueCos.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCos,"trackPerpDistToABound/F");
   tTrueCos.Branch("trackPIDA",&trackPIDATrueCos,"trackPIDA/F");
   tTrueCos.Branch("trackRange",&trackRangeTrueCos,"trackRange/F");
   tTrueCos.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCos.Branch("trackPhi",&trackPhiTrueCos,"trackPhi/F");
   tTrueCos.Branch("trackTheta",&trackThetaTrueCos,"trackTheta/F");
   tTrueCos.Branch("trackThetaXZ",&trackThetaXZTrueCos,"trackThetaXZ/F");
   tTrueCos.Branch("trackThetaYZ",&trackThetaYZTrueCos,"trackThetaYZ/F");
   tTrueCos.Branch("weight",&weightTrueCos,"weight/F");


   TTree tTrueNuGT("tTrueNuGT","Tree containing true neutrino track data");
   TTree tTrueCosGT("tTrueCosGT","Tree containing true cosmic track data");
   Float_t trackLengthTrueNuGT, trackPerpDistXBoundTrueNuGT, trackPerpDistYBoundTrueNuGT, 
           trackPerpDistZBoundTrueNuGT, trackPerpDistToABoundTrueNuGT, trackPIDATrueNuGT, trackRangeTrueNuGT, trackKETrueNuGT,
           trackPhiTrueNuGT, trackThetaTrueNuGT, trackThetaXZTrueNuGT,
           trackThetaYZTrueNuGT, trackNearestDistUntaggedTrueNuToTaggedCosGT;
   Float_t trackLengthTrueCosGT, trackPerpDistXBoundTrueCosGT, trackPerpDistYBoundTrueCosGT, 
           trackPerpDistZBoundTrueCosGT, trackPerpDistToABoundTrueCosGT, trackPIDATrueCosGT, trackRangeTrueCosGT, trackKETrueCosGT,
           trackPhiTrueCosGT, trackThetaTrueCosGT, trackThetaXZTrueCosGT,
           trackThetaYZTrueCosGT, trackNearestDistUntaggedTrueCosToTaggedCosGT, weightTrueCosGT;
   tTrueNuGT.Branch("trackLength",&trackLengthTrueNuGT,"trackLength/F");
   tTrueNuGT.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuGT,"trackPerpDistXBound/F");
   tTrueNuGT.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuGT,"trackPerpDistYBound/F");
   tTrueNuGT.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuGT,"trackPerpDistZBound/F");
   tTrueNuGT.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuGT,"trackPerpDistToABound/F");
   tTrueNuGT.Branch("trackPIDA",&trackPIDATrueNuGT,"trackPIDA/F");
   tTrueNuGT.Branch("trackRange",&trackRangeTrueNuGT,"trackRange/F");
   tTrueNuGT.Branch("trackKE",&trackKETrueNuGT,"trackKE/F");
   tTrueNuGT.Branch("trackPhi",&trackPhiTrueNuGT,"trackPhi/F");
   tTrueNuGT.Branch("trackTheta",&trackThetaTrueNuGT,"trackTheta/F");
   tTrueNuGT.Branch("trackThetaXZ",&trackThetaXZTrueNuGT,"trackThetaXZ/F");
   tTrueNuGT.Branch("trackThetaYZ",&trackThetaYZTrueNuGT,"trackThetaYZ/F");
   tTrueNuGT.Branch("trackNearestDistUntaggedToTaggedCosGT",&trackNearestDistUntaggedTrueNuToTaggedCosGT,"trackNearestDistUntaggedToTaggedCosGT/F");

   tTrueCosGT.Branch("trackLength",&trackLengthTrueCosGT,"trackLength/F");
   tTrueCosGT.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCosGT,"trackPerpDistXBound/F");
   tTrueCosGT.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCosGT,"trackPerpDistYBound/F");
   tTrueCosGT.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCosGT,"trackPerpDistZBound/F");
   tTrueCosGT.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCosGT,"trackPerpDistToABound/F");
   tTrueCosGT.Branch("trackPIDA",&trackPIDATrueCosGT,"trackPIDA/F");
   tTrueCosGT.Branch("trackRange",&trackRangeTrueCos,"trackRange/F");
   tTrueCosGT.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCosGT.Branch("trackPhi",&trackPhiTrueCosGT,"trackPhi/F");
   tTrueCosGT.Branch("trackTheta",&trackThetaTrueCosGT,"trackTheta/F");
   tTrueCosGT.Branch("trackThetaXZ",&trackThetaXZTrueCosGT,"trackThetaXZ/F");
   tTrueCosGT.Branch("trackThetaYZ",&trackThetaYZTrueCosGT,"trackThetaYZ/F");
   tTrueCosGT.Branch("trackNearestDistUntaggedToTaggedCosGT",&trackNearestDistUntaggedTrueCosToTaggedCosGT,"trackNearestDistUntaggedToTaggedCosGT/F");
   tTrueCosGT.Branch("weight",&weightTrueCosGT,"weight/F");





   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the tracks blocks the name of the track module
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);
   ana_tree_truth = new AnaTreeTruth(fChain);

   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1060.};

   size_t nEvtsProcessed = 0;
   size_t nEvtsFiredPMTTrigger = 0;

   if (fChain == 0) return;

   size_t nEvtsLongestTrackNu = 0;
   size_t nEvtsLongestTrackCos = 0;

   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   if(fNEvts == 0 && fEvtToStart == 0){
      fNEvts = nentries;
      std::cout << "No number of events to process specified, running over all " << nentries << " of them." << std::endl;
   }
   if(fNEvts == 0 && fEvtToStart != 0){
      fNEvts = nentries;
      std::cout << "No number of events to process specified, starting at event " << fEvtToStart 
      << ", running over " << nentries - fEvtToStart << " events." << std::endl;
   }
   if(fNEvts != 0 && fEvtToStart != 0){
      fNEvts = nentries;
      std::cout << "Starting at event " << fEvtToStart 
      << ", running over " << nentries - fEvtToStart << " events starting there." << std::endl;
   }
   if(fNEvts != 0 && fEvtToStart == 0){
      std::cout << "Running over " << fNEvts << " events." << std::endl;
   }


   // Loop over events
   for (Long64_t jentry = fEvtToStart; jentry<fNEvts;jentry++) {

      if(jentry >= (signed)fNEvts)
         break;

      if(jentry%1000 == 0 && jentry !=0 )
         std::cout << "Processed: " << jentry-fEvtToStart << " events." << std::endl;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      nEvtsProcessed++;

      // Check if this event has a flash match consistent with a neutrino on any track (< 0.5 or 0.0)
      // If it does, the event had a track which fired the PMT trigger
      bool firedPMTTrigger = false;
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){
         if(ana_tree_tracks->CosmicScoreFlashMatch(i) < 0.5){
            firedPMTTrigger = true;
            nEvtsFiredPMTTrigger++;
            break;
         }
      }




      // Loop over tracks
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){

         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(i));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(i))) min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(i));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(i))) min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(i));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(i))) min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(i));

         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(i));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(i))) min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(i));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(i))) min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(i));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(i))) min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(i));

         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(i));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(i))) min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(i));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(i))) min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(i));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(i))) min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(i));
        
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));
                  
         trackLengthAll = ana_tree_tracks->Length(i);
         trackPerpDistXBoundAll = min_x_dist;
         trackPerpDistYBoundAll = min_y_dist;
         trackPerpDistZBoundAll = min_z_dist;
         trackPerpDistToABoundAll = min_to_a_boundary_dist;
         trackPIDAAll = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
         trackRangeAll = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
         trackKEAll = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
         trackPhiAll = ana_tree_tracks->Phi(i);
         if(trackPhiAll < 0)
            trackPhiAll = -trackPhiAll;
         trackThetaAll = ana_tree_tracks->Theta(i);
         trackThetaXZAll = ana_tree_tracks->ThetaXZ(i);
         trackThetaYZAll = ana_tree_tracks->ThetaYZ(i);
         if(trackThetaYZAll < 0)
            trackThetaYZAll = -trackThetaYZAll;
         if(trackThetaYZAll > TMath::Pi()/2)
            trackThetaYZAll = -(trackThetaYZAll-TMath::Pi());
         trackOriginAll = ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i));
         trackTaggedCosAllGT = 1;
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4){
            trackTaggedCosAllGT = 0;
         }
         trackTaggedCosAllGTFM = 1;
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4
              and ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            trackTaggedCosAllGTFM = 0;
         }

         weightAll=1;
         tAll.Fill();


         // Was the track a true neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
            if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                  && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                  && min_x_dist < 128){
               trackLengthTrueNu = ana_tree_tracks->Length(i);
               trackPerpDistXBoundTrueNu = min_x_dist;
               trackPerpDistYBoundTrueNu = min_y_dist;
               trackPerpDistZBoundTrueNu = min_z_dist;
               trackPerpDistToABoundTrueNu = min_to_a_boundary_dist;
               trackPIDATrueNu = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
               trackRangeTrueNu = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
               trackKETrueNu = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
               trackPhiTrueNu = ana_tree_tracks->Phi(i);
               if(trackPhiTrueNu < 0)
                  trackPhiTrueNu = -trackPhiTrueNu;
               trackThetaTrueNu = ana_tree_tracks->Theta(i);
               trackThetaXZTrueNu = ana_tree_tracks->ThetaXZ(i);
               trackThetaYZTrueNu = ana_tree_tracks->ThetaYZ(i);
               if(trackThetaYZTrueNu < 0)
                  trackThetaYZTrueNu = -trackThetaYZTrueNu;
               if(trackThetaYZTrueNu > TMath::Pi()/2)
                  trackThetaYZTrueNu = -(trackThetaYZTrueNu-TMath::Pi());
               tTrueNu.Fill();
            }
         }

         // Was the track a true cosmic?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
            
            if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                  && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                  && min_x_dist < 128){
               trackLengthTrueCos = ana_tree_tracks->Length(i);
               trackPerpDistXBoundTrueCos = min_x_dist;
               trackPerpDistYBoundTrueCos = min_y_dist;
               trackPerpDistZBoundTrueCos = min_z_dist;
               trackPerpDistToABoundTrueCos = min_to_a_boundary_dist;
               trackPIDATrueCos = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
               trackRangeTrueCos = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
               trackKETrueCos = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
               trackPhiTrueCos = ana_tree_tracks->Phi(i);
               if(trackPhiTrueCos < 0)
                  trackPhiTrueCos = -trackPhiTrueCos;
               trackThetaTrueCos = ana_tree_tracks->Theta(i);
               trackThetaXZTrueCos = ana_tree_tracks->ThetaXZ(i);
               trackThetaYZTrueCos = ana_tree_tracks->ThetaYZ(i);
               if(trackThetaYZTrueCos < 0)
                  trackThetaYZTrueCos = -trackThetaYZTrueCos;
               if(trackThetaYZTrueCos > TMath::Pi()/2)
                  trackThetaYZTrueCos = -(trackThetaYZTrueCos-TMath::Pi());
               weightTrueCos=1;
               tTrueCos.Fill();
            }
         }



         // Does the track flunk the geometric tagger cut?
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4){
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueCosGT = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueCosGT = min_x_dist;
                  trackPerpDistYBoundTrueCosGT = min_y_dist;
                  trackPerpDistZBoundTrueCosGT = min_z_dist;
                  trackPerpDistToABoundTrueCosGT = min_to_a_boundary_dist;
                  trackPIDATrueCosGT = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueCosGT = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueCosGT = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueCosGT = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueCosGT < 0)
                     trackPhiTrueCosGT  = -trackPhiTrueCosGT ;
                  trackThetaTrueCosGT = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueCosGT = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueCosGT = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueCosGT < 0)
                     trackThetaYZTrueCosGT = -trackThetaYZTrueCosGT;
                  if(trackThetaYZTrueCosGT > TMath::Pi()/2)
                     trackThetaYZTrueCosGT = -(trackThetaYZTrueCosGT-TMath::Pi());
                  trackNearestDistUntaggedTrueCosToTaggedCosGT=shortestTrackDistance;
                  weightTrueCosGT=1;
                  tTrueCosGT.Fill();
               }


            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueNuGT = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueNuGT = min_x_dist;
                  trackPerpDistYBoundTrueNuGT = min_y_dist;
                  trackPerpDistZBoundTrueNuGT = min_z_dist;
                  trackPerpDistToABoundTrueNuGT = min_to_a_boundary_dist;
                  trackPIDATrueNuGT = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueNuGT = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueNuGT = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueNuGT = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueNuGT < 0)
                     trackPhiTrueNuGT  = -trackPhiTrueNuGT ;
                  trackThetaTrueNuGT = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueNuGT = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueNuGT = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueNuGT < 0)
                     trackThetaYZTrueNuGT = -trackThetaYZTrueNuGT;
                  if(trackThetaYZTrueNuGT > TMath::Pi()/2)
                     trackThetaYZTrueNuGT = -(trackThetaYZTrueNuGT-TMath::Pi());
                  trackNearestDistUntaggedTrueNuToTaggedCosGT=shortestTrackDistance;
                  tTrueNuGT.Fill();
               }
            }
         }


      }
   }

   std::cout << "Done, processed " << nEvtsProcessed << " events." << std::endl;
   std::cout << "Of those events " << nEvtsFiredPMTTrigger << " fired the PMT trigger." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackNu  << " of the longest tracks in each event came from a neutrino." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackCos  << " of the longest tracks in each event came from a cosmic." << std::endl;



   tAll.Write();
   tTrueNu.Write();
   tTrueCos.Write();
   tTrueNuGT.Write();
   tTrueCosGT.Write();

}






