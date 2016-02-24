#define AnaTreeLoopWireVariation_cxx
#include "AnaTreeLoopWireVariation.h"

#include <iostream>

// ROOT includes 
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStopwatch.h>



void AnaTreeLoopWireVariation::Loop()
{

   // Setup stopwatch
   TStopwatch *stopwatch = new TStopwatch();

   //
   // Track Length histograms
   //
   hTrackLength          = new TH1F("hTrackLength","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hLongestTrackLength   = new TH1F("hLongestTrackLength","Longest Track Length; Length [cm]; Tracks", 100, 0, 530);
   hTrackLengthX         = new TH1F("hTrackLengthX","Track Length in X Direction; Length [cm]; Tracks", 100, 0, 530);

   //
   // Track angle histograms
   //
   hTrackPhi                              = new TH1F("hTrackPhi","Track Phi; Phi; Tracks", 100, -3.14, 3.14);
   hLongestTrackPhi                       = new TH1F("hLongestTrackPhi","Longest Track Phi; Phi; Tracks", 100, -3.14, 3.14);
   hTrackThetaXZ            = new TH1F("hTrackThetaXZ","Track Theta XZ; Theta; Tracks", 100, 0., 3.14);
   hLongestTrackThetaXZ     = new TH1F("hLongestTrackThetaXZ","Longest Track Theta XZ; Theta; Tracks", 100, 0., 3.14);

   //
   // Track boundary histograms
   // 
   hPerpDistXBound   = new TH1F("hPerpDistXBound ","Closest Perpendicular Distance to TPC X Boundary; Dist [cm]; Tracks", 100, 0, 128);
   hPerpDistYBound   = new TH1F("hPerpDistYBound ","Closest Perpendicular Distance to TPC Y Boundary; Dist [cm]; Tracks", 100, 0, 116);
   hPerpDistZBound   = new TH1F("hPerpDistZBound ","Closest Perpendicular Distance to TPC Z Boundary; Dist [cm]; Tracks", 100, 0, 530);
   hPerpDistToABound = new TH1F("hPerpDistToABound ","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Tracks", 100, 0, 116);

   //
   // dQdx for each wire, corrected for pitch
   //
   for(int i = 0; i < kUWires; i++){
       hUPlanedQdx[i] = new TH1F("hUPlanedQdx_"+(TString)Form("%d",i),"dQdx for U Plane;dQ/dx [ADC/cm];Hits",75,0,1000);
       hUPlanedQdx[i]->Sumw2();
   }
   for(int i = 0; i < kVWires; i++){
       hVPlanedQdx[i] = new TH1F("hVPlanedQdx_"+(TString)Form("%d",i),"dQdx for V Plane;dQ/dx [ADC/cm];Hits",75,0,1000); 
       hVPlanedQdx[i]->Sumw2();
   }
   for(int i = 0; i < kYWires; i++){
       hYPlanedQdx[i] = new TH1F("hYPlanedQdx_"+(TString)Form("%d",i),"dQdx for Y Plane;dQ/dx [ADC/cm];Hits",75,0,2000); 
       hYPlanedQdx[i]->Sumw2();
   }

   //
   // Other histograms
   //
   hPerpDistToABoundTrackLength = new TH2F("hPerpDistToABoundTrackLength","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Length [cm]", 100, 0, 116,100,0,530);
   hYPlaneHitChargeVsAngle = new TH2F("hYPlaneHitChargeVsAngle","Angle to Wire Plane in Plane Perp. to Wires; Track Angle [radians]; Hit Charge [ADC]", 100, 0, 3.14/2,100,0,1000);


   // Get gain histogram
   // TFile *fGain = new TFile("20160204_PulserGain_Run3048.root");
   // TH1F *hGainVsChan = (TH1F*)fGain->Get("hGainVsChan");


   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the blocks the names of the modules
   ana_tree_runinfo = new AnaTreeRunInfo(fChain);
   ana_tree_hits = new AnaTreeHits(fChain);
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);

   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1060.};

   size_t nEvtsProcessed = 0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   if(fNEvts == 0){
      fNEvts = nentries;
      std::cout << "No number of events to process specified, running over all " << nentries << " of them." << std::endl;
   }

   stopwatch->Start();

   // Loop over events
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if(jentry >= (signed)fNEvts)
         break;

      if(jentry%1000 == 0 && jentry !=0 )
         std::cout << "Processed: " << jentry << " events." << std::endl;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      nEvtsProcessed++;

      
      // We want to check how many hits are on a wire.
      // Create a three dimensional array of maps with 
      // wire number as a key and filled with a vector 
      // for the hit index
      std::map<Short_t, std::vector<int>> wireToHitMap[3];
      for (int j = 0; j < ana_tree_hits->NHits(); j++){
         if(ana_tree_hits->HitPlane(j) != 0 
               && ana_tree_hits->HitPlane(j) != 1
               && ana_tree_hits->HitPlane(j) != 2)
            continue;
         std::pair<std::map<Short_t, std::vector<int> >::iterator,bool> ret;
         ret = wireToHitMap[ana_tree_hits->HitPlane(j)].insert(std::pair<Short_t, std::vector<int> >(ana_tree_hits->HitWire(j), {j}));
         if(ret.second==false)
            wireToHitMap[ana_tree_hits->HitPlane(j)][ana_tree_hits->HitWire(j)].push_back(j);
      }

      // for(auto wireToHitMapItr = wireToHitMap[0].begin(); wireToHitMapItr != wireToHitMap[0].end(); wireToHitMapItr++){
      //    std::cout << "Wire: " << wireToHitMapItr->first << std::endl;
      //    for(auto wireToHitMapItrVecItr = wireToHitMapItr->second.begin(); wireToHitMapItrVecItr != wireToHitMapItr->second.end(); wireToHitMapItrVecItr++){
      //       std::cout << "Hit: " << *wireToHitMapItrVecItr << std::endl;
      //    }
      // }

      double longestTrackLength = 0;
      double longestTrackIndex = -1;

      // Loop over tracks
      for (int i= 0; i< ana_tree_tracks->NTracks(); i++){

         // Look for the longest track 
         if(ana_tree_tracks->Length(i) > longestTrackLength){
            longestTrackLength = ana_tree_tracks->Length(i);
            longestTrackIndex = i;
         }

         // Is this a crossing track?
         // if(std::abs(ana_tree_tracks->StartX(i)-ana_tree_tracks->EndX(i)) > 250 && std::abs(ana_tree_tracks->StartX(i)-ana_tree_tracks->EndX(i)) < 270){

         // Is this a track longer than 200 cm?
         if( ana_tree_tracks->Length(i) > 200
              // && ana_tree_tracks->ThetaXZ(i) > -0.5
              // && ana_tree_tracks->ThetaXZ(i) < 0.5
               ){


            // For each track hit, find its dQdx for each plane
            for (int j = 0; j < ana_tree_hits->NHits(); j++){

               if(ana_tree_hits->HitPlane(j) != 0 
                     && ana_tree_hits->HitPlane(j) != 1
                     && ana_tree_hits->HitPlane(j) != 2)
                  continue;

               // Does the hit have an association with this track?
               if(ana_tree_hits->HitTrackKey(j) == i){

                  // Is this hit the only hit associated with this track on its wire?
                  // Use the wire to hit map created above to find out!
                  int nHitsOnWire = 0;
                  for(auto wireToHitMapVecItr = wireToHitMap[ana_tree_hits->HitPlane(j)][ana_tree_hits->HitWire(j)].begin();
                     wireToHitMapVecItr != wireToHitMap[ana_tree_hits->HitPlane(j)][ana_tree_hits->HitWire(j)].end(); 
                     wireToHitMapVecItr++){
                     if(ana_tree_hits->HitTrackKey(j) == ana_tree_hits->HitTrackKey(*wireToHitMapVecItr))
                        nHitsOnWire++;
                  }

                  if(nHitsOnWire != 1)
                     continue;

                  // double fHitGain = hGainVsChan->GetBinContent(ana_tree_hits->HitChannel(j));
                  double fHitGain = 1;

                  // Is this a U plane hit?
                  if(ana_tree_hits->HitPlane(j) == 0){
                     hUPlanedQdx[ana_tree_hits->HitWire(j)]->Fill(fHitGain*ana_tree_hits->HitCharge(j)/ana_tree_tracks->Pitch(i,0));
                  }
                  // Is this a V plane hit?
                  if(ana_tree_hits->HitPlane(j) == 1){
                     hVPlanedQdx[ana_tree_hits->HitWire(j)]->Fill(fHitGain*ana_tree_hits->HitCharge(j)/ana_tree_tracks->Pitch(i,1));
                  }
                  // Is this a Y plane hit?
                  if(ana_tree_hits->HitPlane(j) == 2){
                     hYPlanedQdx[ana_tree_hits->HitWire(j)]->Fill(fHitGain*ana_tree_hits->HitCharge(j)/ana_tree_tracks->Pitch(i,2));
                     hYPlaneHitChargeVsAngle->Fill(ana_tree_tracks->ThetaXZ(i),ana_tree_hits->HitCharge(j));
                  }
               }
            }
         }


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



         hTrackLength->Fill(ana_tree_tracks->Length(i));
         hTrackLengthX->Fill(std::abs(ana_tree_tracks->StartX(i)-ana_tree_tracks->EndX(i)));
         hTrackPhi->Fill(ana_tree_tracks->Phi(i));
         hTrackThetaXZ->Fill(ana_tree_tracks->ThetaXZ(i));
         hPerpDistZBound->Fill(min_z_dist);
         hPerpDistYBound->Fill(min_y_dist);
         hPerpDistXBound->Fill(min_x_dist);
         hPerpDistToABound->Fill(min_to_a_boundary_dist);
         hPerpDistToABoundTrackLength->Fill(min_to_a_boundary_dist,ana_tree_tracks->Length(i));
      }

      // Fill the longest track histograms before the length cut is applied
      hLongestTrackLength->Fill(ana_tree_tracks->Length(longestTrackIndex));
      hLongestTrackPhi->Fill(ana_tree_tracks->Phi(longestTrackIndex));
      hLongestTrackThetaXZ->Fill(ana_tree_tracks->ThetaXZ(longestTrackIndex));

   }


   stopwatch->Stop();
   std::cout << "Total CPU Time: " << stopwatch->CpuTime() << " Per Event: " << stopwatch->CpuTime()/nentries << std::endl;
   std::cout << "Total Real Time: " << stopwatch->RealTime() << " Per Event: " << stopwatch->RealTime()/nentries << std::endl;


   // Write the histograms
   TFile f(fOutputFileName,"recreate");

   hPerpDistToABoundTrackLength->Write();
   hYPlaneHitChargeVsAngle->Write();

   f.cd();
   f.mkdir("track_lengths");
   f.cd("track_lengths");
   hTrackLength->Write();
   hLongestTrackLength->Write();
   hTrackLengthX->Write();

   f.cd();
   f.mkdir("track_angles");
   f.cd("track_angles");
   hTrackPhi->Write();
   hLongestTrackPhi->Write();
   hTrackThetaXZ->Write();
   hLongestTrackThetaXZ->Write();

   f.cd();
   f.mkdir("track_boundaries");
   f.cd("track_boundaries");

   hPerpDistXBound->Write();
   hPerpDistYBound->Write();
   hPerpDistZBound->Write();
   hPerpDistToABound->Write();

   f.cd();
   f.mkdir("hit_dqdx/u_plane");
   f.cd("hit_dqdx/u_plane");
   for(int i = 0; i < kUWires; i++){
       hUPlanedQdx[i]->Write(); 
   }
   f.cd();
   f.mkdir("hit_dqdx/v_plane");
   f.cd("hit_dqdx/v_plane");
   for(int i = 0; i < kVWires; i++){
       hVPlanedQdx[i]->Write(); 
   }
   f.cd();
   f.mkdir("hit_dqdx/y_plane");
   f.cd("hit_dqdx/y_plane");
   for(int i = 0; i < kYWires; i++){
       hYPlanedQdx[i]->Write(); 
   }


   // Close the file
   f.Close();

}






