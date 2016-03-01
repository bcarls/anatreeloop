#define AnaTreeLoopMCStudy_cxx
#include "AnaTreeLoopMCStudy.h"

#include <iostream>

// ROOT includes
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>



void AnaTreeLoopMCStudy::Loop()
{

   // Book histograms


   //
   // MC Truth Information
   //

   
   //
   // Track origin histograms
   //

   //
   // Track Length histograms
   //
   hTrackLengthRecoVsTrue = new TH2F("hTrackLengthRecoVsTrue","hTrackLengthRecoVsTrue",50,0,530,50,0,530);
   hEffTrueTrackLength = new TProfile("hEffTrueTrackLength","hEffTrueTrackLength",50,0,530);


   //
   // Track boundary histograms
   // 

   // All tracks
  
   // True neutrinos only

   // True cosmics only

   //
   // Track calo and PID histograms
   //

   //
   // Track angle histograms
   //

   //
   // Track vertex histograms
   //


   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the tracks blocks the name of the track module
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);
   ana_tree_mctracks = new AnaTreeMCTracks(fChain);
   ana_tree_truth = new AnaTreeTruth(fChain);


   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1060.};

   size_t nEvtsProcessed = 0;
   size_t nEvtsFiredPMTTrigger = 0;

   // Reality check
   size_t nRealityEvts0 = 0;
   // size_t nRealityEvts1 = 0;
   // size_t nRealityEvts2 = 0;
   // size_t nRealityEvts3 = 0;
   // size_t nTracksVertexMatched = 0;
   // size_t nTracksVertexLengthMatched = 0;

   if (fChain == 0) return;

   size_t nEvtsLongestTrackNu = 0;
   size_t nEvtsLongestTrackCos = 0;
   size_t nEvtsLongestTrackAll = 0;

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




      // Loop over tracks
      for (int i= 0; i< ana_tree_tracks->NTracks(); i++){

         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){

            // Loop over MC tracks 
            for (int j= 0; j< ana_tree_mctracks->NMCTracks(); j++){
               if(ana_tree_tracks->ID(i) == ana_tree_mctracks->ID(j)
                    &&  ana_tree_mctracks->PDGTruth(j) == 13
                     ){
                  hTrackLengthRecoVsTrue->Fill(ana_tree_mctracks->LengthDrifted(j), ana_tree_tracks->Length(i));
               }
            }
         }
      }
 

      // Loop over MC tracks 
      bool foundTrueMuon = false;
      for (int j= 0; j< ana_tree_mctracks->NMCTracks(); j++){
         if(ana_tree_mctracks->Origin(j) == 1
              &&  ana_tree_mctracks->PDGTruth(j) == 13
               ){
            // Loop over tracks
            for (int i= 0; i< ana_tree_tracks->NTracks(); i++){
               if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1
                  && ana_tree_tracks->ID(i) == ana_tree_mctracks->ID(j)        
                     ){
                  hEffTrueTrackLength->Fill(ana_tree_mctracks->LengthDrifted(j),1);
                  foundTrueMuon = true;
               }
            }
            if(foundTrueMuon == false){
               hEffTrueTrackLength->Fill(ana_tree_mctracks->LengthDrifted(j),0);
            }
         }
      }
   }

   // Write the histograms
   TFile f(fOutputFileName,"recreate");
   
   hTrackLengthRecoVsTrue->Write();
   hEffTrueTrackLength->Write();
   // Close the file
   f.Close();
}






