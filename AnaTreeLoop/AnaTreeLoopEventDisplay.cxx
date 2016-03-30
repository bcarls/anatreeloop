#define AnaTreeLoopEventDisplay_cxx
#include "AnaTreeLoopEventDisplay.h"

#include <iostream>
#include <limits>

// ROOT includes 
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TStopwatch.h>



void AnaTreeLoopEventDisplay::Loop()
{

   // Setup stopwatch
   TStopwatch *stopwatch = new TStopwatch();


   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the blocks the names of the modules
   ana_tree_runinfo = new AnaTreeRunInfo(fChain);
   ana_tree_hits = new AnaTreeHits(fChain);
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);

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


      TCanvas *c1 = new TCanvas("c1","Tree test",900,900);
      c1->Divide(0,3);

      std::vector<float> vectorHitsUPlaneWire;
      std::vector<float> vectorHitsVPlaneWire;
      std::vector<float> vectorHitsYPlaneWire;
      std::vector<float> vectorHitsUPlaneTicks;
      std::vector<float> vectorHitsVPlaneTicks;
      std::vector<float> vectorHitsYPlaneTicks;

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

      for (int j = 0; j < ana_tree_hits->NHits(); j++){
         if(ana_tree_hits->HitPlane(j) != 0 
               && ana_tree_hits->HitPlane(j) != 1
               && ana_tree_hits->HitPlane(j) != 2)
            continue;

         if(ana_tree_hits->HitPlane(j) == 0){
            vectorHitsUPlaneWire.push_back(ana_tree_hits->HitWire(j));
            vectorHitsUPlaneTicks.push_back(fWindowOffset+0.5*(ana_tree_hits->HitStartTick(j)+ana_tree_hits->HitEndTick(j)));
         } 
         if(ana_tree_hits->HitPlane(j) == 1){
            vectorHitsVPlaneWire.push_back(ana_tree_hits->HitWire(j));
            vectorHitsVPlaneTicks.push_back(fWindowOffset+0.5*(ana_tree_hits->HitStartTick(j)+ana_tree_hits->HitEndTick(j)));
         }
         if(ana_tree_hits->HitPlane(j) == 2){
            vectorHitsYPlaneWire.push_back(ana_tree_hits->HitWire(j));
            vectorHitsYPlaneTicks.push_back(fWindowOffset+0.5*(ana_tree_hits->HitStartTick(j)+ana_tree_hits->HitEndTick(j)));
         }

      }

      TGraph *gHitsUPlane = new TGraph (vectorHitsUPlaneWire.size(),&vectorHitsUPlaneWire[0],&vectorHitsUPlaneTicks[0]);
      gHitsUPlane->SetTitle("U Plane");
      gHitsUPlane->SetMinimum(0);
      gHitsUPlane->SetMaximum(9600);
      gHitsUPlane->GetXaxis()->SetLimits(0,2400);
      gHitsUPlane->SetLineWidth(0);
      gHitsUPlane->SetMarkerStyle(6);
      TGraph *gHitsVPlane = new TGraph (vectorHitsVPlaneWire.size(),&vectorHitsVPlaneWire[0],&vectorHitsVPlaneTicks[0]);
      gHitsVPlane->SetTitle("V Plane");
      gHitsVPlane->SetMinimum(0);
      gHitsVPlane->SetMaximum(9600);
      gHitsVPlane->GetXaxis()->SetLimits(0,2400);
      gHitsVPlane->SetLineWidth(0);
      gHitsVPlane->SetMarkerStyle(6);
      TGraph *gHitsYPlane = new TGraph (vectorHitsYPlaneWire.size(),&vectorHitsYPlaneWire[0],&vectorHitsYPlaneTicks[0]);
      gHitsYPlane->SetTitle("Y Plane");
      gHitsYPlane->SetMinimum(0);
      gHitsYPlane->SetMaximum(9600);
      gHitsYPlane->GetXaxis()->SetLimits(0,3456);
      gHitsYPlane->SetLineWidth(0);
      gHitsYPlane->SetMarkerStyle(6);

      // Try TGraph
      c1->cd(1);
      gHitsUPlane->Draw();
      c1->cd(2);
      gHitsVPlane->Draw();
      c1->cd(3);
      gHitsYPlane->Draw();

      c1->Update();

      std::cout << "Double-click the canvas or push any key while the canvas is selected to move to the next event." << std::endl;

      c1->WaitPrimitive();

      delete c1;
   }

   stopwatch->Stop();
   std::cout << "Total CPU Time: " << stopwatch->CpuTime() << " Per Event: " << stopwatch->CpuTime()/nentries << std::endl;
   std::cout << "Total Real Time: " << stopwatch->RealTime() << " Per Event: " << stopwatch->RealTime()/nentries << std::endl;

}






