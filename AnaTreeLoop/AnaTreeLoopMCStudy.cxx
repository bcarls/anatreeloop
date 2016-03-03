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
   hTrackXEndPointDiff = new TH1F("hTrackXEndPointDiff","hTrackXEndPointDiff",100,0,100);
   hTrackYEndPointDiff = new TH1F("hTrackYEndPointDiff","hTrackYEndPointDiff",100,0,100);
   hTrackZEndPointDiff = new TH1F("hTrackZEndPointDiff","hTrackZEndPointDiff",100,0,100);
   hTrackXStartPointDiff = new TH1F("hTrackXStartPointDiff","hTrackXStartPointDiff",100,0,100);
   hTrackYStartPointDiff = new TH1F("hTrackYStartPointDiff","hTrackYStartPointDiff",100,0,100);
   hTrackZStartPointDiff = new TH1F("hTrackZStartPointDiff","hTrackZStartPointDiff",100,0,100);

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
               double TrueStartX = std::min(ana_tree_mctracks->StartX(i),ana_tree_mctracks->EndX(i));
               double TrueEndX = std::max(ana_tree_mctracks->StartX(i),ana_tree_mctracks->EndX(i));
               double TrueStartY = std::min(ana_tree_mctracks->StartY(i),ana_tree_mctracks->EndY(i));
               double TrueEndY = std::max(ana_tree_mctracks->StartY(i),ana_tree_mctracks->EndY(i));
               double TrueStartZ = std::min(ana_tree_mctracks->StartZ(i),ana_tree_mctracks->EndZ(i));
               double TrueEndZ = std::max(ana_tree_mctracks->StartZ(i),ana_tree_mctracks->EndZ(i));
               double RecoStartX = std::min(ana_tree_tracks->StartX(i),ana_tree_tracks->EndX(i));
               double RecoEndX = std::max(ana_tree_tracks->StartX(i),ana_tree_tracks->EndX(i));
               double RecoStartY = std::min(ana_tree_tracks->StartY(i),ana_tree_tracks->EndY(i));
               double RecoEndY = std::max(ana_tree_tracks->StartY(i),ana_tree_tracks->EndY(i));
               double RecoStartZ = std::min(ana_tree_tracks->StartZ(i),ana_tree_tracks->EndZ(i));
               double RecoEndZ = std::max(ana_tree_tracks->StartZ(i),ana_tree_tracks->EndZ(i));
               hTrackXEndPointDiff->Fill(std::abs(TrueStartX-RecoEndX));
               
               
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






