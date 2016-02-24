#define AnaTreeLoopClusterLinearity_cxx
#include "AnaTreeLoopClusterLinearity.h"

#include <iostream>

// ROOT includes 
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TPrincipal.h>
#include <TGraph.h>
#include <TF1.h>



void AnaTreeLoopClusterLinearity::Loop()
{


   TCanvas *c1 = new TCanvas("c1","Tree test");

   gStyle->SetOptFit(1111);
  

   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the blocks the names of the modules
   ana_tree_hits = new AnaTreeHits(fChain);
   ana_tree_clusters = new AnaTreeClusters(fChain);

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

      // Look at a fit to a line via a TGraph
      for (int i_c = 0; i_c < ana_tree_clusters->NClusters(); i_c++){
         if(ana_tree_clusters->NClusterHits(i_c) > 100){
            std::vector<Float_t> wireVector;
            std::vector<Float_t> tickVector;
            for (int i_h = 0; i_h < ana_tree_hits->NHits(); i_h++){
               if(ana_tree_hits->HitClusterKey(i_h) == i_c){
                  // hClusterHitsVsWires->SetBinContent(ana_tree_hits->HitWire(i_h)+1,0.5*(ana_tree_hits->HitEndTick(i_h)+ana_tree_hits->HitEndTick(i_h)));
                  wireVector.push_back((Float_t)ana_tree_hits->HitWire(i_h));
                  tickVector.push_back(0.5*(ana_tree_hits->HitEndTick(i_h)+ana_tree_hits->HitEndTick(i_h)));
               }
            }
            TGraph *gClusterHitsVsWires = new TGraph(wireVector.size(),&wireVector[0],&tickVector[0]);
            // Fit and print the histogram
            gClusterHitsVsWires->Draw();
            TF1 *fLinear = new TF1("fLinear","pol1");
            gClusterHitsVsWires->Fit("fLinear");
            std::cout <<  fLinear->GetChisquare()/fLinear->GetNDF() << std::endl;
            c1->Print("gClusterHitsVsWires_"+(TString)Form("%lld",jentry)+"_"+(TString)Form("%d",+ana_tree_clusters->ClusterView(i_c))+"_"+(TString)Form("%d",i_c)+".png");
            c1->Clear();
            delete gClusterHitsVsWires;
         }
      }


      // Look at a fit to a line via a histogram
      // for (int i_c = 0; i_c < ana_tree_clusters->NClusters(); i_c++){
      //    if(ana_tree_clusters->NClusterHits(i_c) > 10){
      //       TH1F *hClusterHitsVsWires;
      //       if(ana_tree_clusters->ClusterView(i_c) == 0)
      //          hClusterHitsVsWires = new TH1F("hClusterHitsVsWires","Tick Versus Wire; Wire; Ticks", kUWires, 0,kUWires);
      //       if(ana_tree_clusters->ClusterView(i_c) == 1)
      //          hClusterHitsVsWires = new TH1F("hClusterHitsVsWires","Tick Versus Wire; Wire; Ticks", kVWires, 0,kVWires);
      //       if(ana_tree_clusters->ClusterView(i_c) == 2)
      //          hClusterHitsVsWires = new TH1F("hClusterHitsVsWires","Tick Versus Wire; Wire; Ticks", kYWires, 0,kYWires);
      //       for (int i_h = 0; i_h < ana_tree_hits->NHits(); i_h++){
      //          if(ana_tree_hits->HitClusterKey(i_h) == i_c){
      //             hClusterHitsVsWires->SetBinContent(ana_tree_hits->HitWire(i_h)+1,0.5*(ana_tree_hits->HitEndTick(i_h)+ana_tree_hits->HitEndTick(i_h)));
      //          }
      //       }
      //       // Fit and print the histogram
      //       hClusterHitsVsWires->Fit("pol1");
      //       c1->Print("hClusterHitsVsWires_"+(TString)Form("%lld",jentry)+"_"+(TString)Form("%d",+ana_tree_clusters->ClusterView(i_c))+"_"+(TString)Form("%d",i_c)+".png");
      //       delete hClusterHitsVsWires;
      //    }
      // }


      // Perform a PCA
      // std::cout << "New event" << std::endl;
      // for (int i_c = 0; i_c < ana_tree_clusters->NClusters(); i_c++){
      //    if(ana_tree_clusters->NClusterHits(i_c) > 10){
      //       TPrincipal* principal = new TPrincipal(2,"ND");
      //       Double_t* data = new Double_t[2];
      //       for (int i_h = 0; i_h < ana_tree_hits->NHits(); i_h++){
      //          if(ana_tree_hits->HitClusterKey(i_h) == i_c){
      //             data[0] = ana_tree_hits->HitWire(i_h);
      //             data[1] = 0.5*(ana_tree_hits->HitEndTick(i_h)+ana_tree_hits->HitEndTick(i_h));
      //             principal->AddRow(data);
      //          }
      //       }
      //       delete [] data;
      //       principal->MakePrincipals();
      //       principal->Test();
      //       principal->Print();
      //       for(int i_e = 0; i_e < principal->GetEigenValues()->GetNrows(); i_e++){
      //          std::cout << (*principal->GetEigenValues())[i_e] << std::endl;
      //       }
      //       // principal->MakeHistograms();
      //       delete principal; 
      //    }
      // }








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
   }

   // Write the histograms
   TFile f(fOutputFileName,"recreate");

   // Close the file
   f.Close();

}






