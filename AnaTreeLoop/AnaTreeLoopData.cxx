#define AnaTreeLoopData_cxx
#include "AnaTreeLoopData.h"

#include <iostream>

// ROOT includes 
#include <root/TStyle.h>
#include <root/TCanvas.h>
#include <root/TMath.h>



void AnaTreeLoopData::Loop()
{

   //
   // Track Length histograms
   //
   hTrackLength          = new TH1F("hTrackLength","Track Length; Length [cm]; Tracks", 100, 0, 530);
   hLongestTrackLength   = new TH1F("hLongestTrackLength","Longest Track Length; Length [cm]; Tracks", 100, 0, 530);

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
   // Other histograms
   //
   hPerpDistToABoundTrackLength = new TH2F("hPerpDistToABoundTrackLength","Closest Perpendicular Distance to A TPC Boundary; Dist [cm]; Length [cm]", 100, 0, 116,100,0,530);


   // Give the blocks the names of the modules
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);
   ana_tree_vtx = new AnaTreeVertex(fChain,fVertexModuleName);

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

      
      double longestTrackLength = 0;
      double longestTrackIndex = -1;

      // Loop over tracks
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){

         // Look for the longest track 
         if(ana_tree_tracks->Length(i) > longestTrackLength){
            longestTrackLength = ana_tree_tracks->Length(i);
            longestTrackIndex = i;
         }

         // Print out track pitch
         // std::cout << ana_tree_tracks->Pitch(i,2) << std::endl;



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

   // Write the histograms
   TFile f(fOutputFileName,"recreate");

   hPerpDistToABoundTrackLength->Write();

   f.cd();
   f.mkdir("track_lengths");
   f.cd("track_lengths");
   hTrackLength->Write();
   hLongestTrackLength->Write();

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

   // Close the file
   f.Close();

}






