#define AnaTreeLoopDataStability_cxx
#include "AnaTreeLoopDataStability.h"

#include <iostream>

// ROOT includes 
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TStopwatch.h>



void AnaTreeLoopDataStability::Loop()
{

   // Setup stopwatch
   TStopwatch *stopwatch = new TStopwatch();

   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1036.8};


   Double_t EventTime = 0;
   Long64_t NTotalHitsInPlane = 0;
   Long64_t NTotalHitsNoPlane = 0;
   Long64_t NUHits = 0;
   Long64_t NVHits = 0;
   Long64_t NYHits = 0;
   Double_t NTotalHitsInPlaneAverage = 0;
   Double_t NTotalHitsNoPlaneAverage = 0;
   Double_t NUHitsAverage = 0;
   Double_t NVHitsAverage = 0;
   Double_t NYHitsAverage = 0;
   Double_t TotalHitChargeInPlane = 0;
   Double_t TotalHitChargeNoPlane = 0;
   Double_t UHitCharge = 0;
   Double_t VHitCharge = 0;
   Double_t YHitCharge = 0;
   Double_t TotalHitChargeInPlaneAverage = 0;
   Double_t TotalHitChargeNoPlaneAverage = 0;
   Double_t UHitChargeAverage = 0;
   Double_t VHitChargeAverage = 0;
   Double_t YHitChargeAverage = 0;
   Double_t TotalHitChargeInPlaneStanDev = 0;
   Double_t TotalHitChargeNoPlaneStanDev = 0;
   Double_t UHitChargeStanDev = 0;
   Double_t VHitChargeStanDev = 0;
   Double_t YHitChargeStanDev = 0;
   Double_t TotalHitPeakChargeInPlane = 0;
   Double_t TotalHitPeakChargeNoPlane = 0;
   Double_t UHitPeakCharge = 0;
   Double_t VHitPeakCharge = 0;
   Double_t YHitPeakCharge = 0;
   Double_t TotalHitPeakChargeInPlaneAverage = 0;
   Double_t TotalHitPeakChargeNoPlaneAverage = 0;
   Double_t UHitPeakChargeAverage = 0;
   Double_t VHitPeakChargeAverage = 0;
   Double_t YHitPeakChargeAverage = 0;
   Double_t TotalHitPeakChargeInPlaneStanDev = 0;
   Double_t TotalHitPeakChargeNoPlaneStanDev = 0;
   Double_t UHitPeakChargeStanDev = 0;
   Double_t VHitPeakChargeStanDev = 0;
   Double_t YHitPeakChargeStanDev = 0;
   Double_t NAllFlashes = 0;
   Double_t NFlashes50PE = 0;
   Double_t NAllFlashesAverage = 0;
   Double_t NFlashes50PEAverage = 0;

   Double_t FlashZCenter = 0;
   Double_t FlashZCenter50PE = 0;
   Double_t FlashZCenterAverage = 0;
   Double_t FlashZCenter50PEAverage = 0;
   
   int fCurrentRun = 0;  
   int fNEventsInRun = 0;  
   int fNRuns = 0;

   // Setup the TTree for storing hit information
   TTree *DetectorStabilityTree= new TTree("DetectorStabilityTree","Hit Stability Information");
   DetectorStabilityTree->Branch("Run",&fCurrentRun,"Run/I");
   DetectorStabilityTree->Branch("EventTime",&EventTime,"EventTime/D");
   DetectorStabilityTree->Branch("TotalHitChargeInPlaneAverage",&TotalHitChargeInPlaneAverage,"TotalHitChargeInPlaneAverage/D");
   DetectorStabilityTree->Branch("TotalHitChargeNoPlaneAverage",&TotalHitChargeNoPlaneAverage,"TotalHitChargeNoPlaneAverage/D");
   DetectorStabilityTree->Branch("UHitChargeAverage",&UHitChargeAverage,"UHitChargeAverage/D");
   DetectorStabilityTree->Branch("VHitChargeAverage",&VHitChargeAverage,"VHitChargeAverage/D");
   DetectorStabilityTree->Branch("YHitChargeAverage",&YHitChargeAverage,"YHitChargeAverage/D");

   DetectorStabilityTree->Branch("TotalHitChargeInPlaneStanDev",&TotalHitChargeInPlaneStanDev,"TotalHitChargeInPlaneStanDev/D");
   DetectorStabilityTree->Branch("TotalHitChargeNoPlaneStanDev",&TotalHitChargeNoPlaneStanDev,"TotalHitChargeNoPlaneStanDev/D");
   DetectorStabilityTree->Branch("UHitChargeStanDev",&UHitChargeStanDev,"UHitChargeStanDev/D");
   DetectorStabilityTree->Branch("VHitChargeStanDev",&VHitChargeStanDev,"VHitChargeStanDev/D");
   DetectorStabilityTree->Branch("YHitChargeStanDev",&YHitChargeStanDev,"YHitChargeStanDev/D");

   DetectorStabilityTree->Branch("TotalHitPeakChargeInPlaneAverage",&TotalHitPeakChargeInPlaneAverage,"TotalHitPeakChargeInPlaneAverage/D");
   DetectorStabilityTree->Branch("TotalHitPeakChargeNoPlaneAverage",&TotalHitPeakChargeNoPlaneAverage,"TotalHitPeakChargeNoPlaneAverage/D");
   DetectorStabilityTree->Branch("UHitPeakChargeAverage",&UHitPeakChargeAverage,"UHitPeakChargeAverage/D");
   DetectorStabilityTree->Branch("VHitPeakChargeAverage",&VHitPeakChargeAverage,"VHitPeakChargeAverage/D");
   DetectorStabilityTree->Branch("YHitPeakChargeAverage",&YHitPeakChargeAverage,"YHitPeakChargeAverage/D");

   DetectorStabilityTree->Branch("TotalHitPeakChargeInPlaneStanDev",&TotalHitPeakChargeInPlaneStanDev,"TotalHitPeakChargeInPlaneStanDev/D");
   DetectorStabilityTree->Branch("TotalHitPeakChargeNoPlaneStanDev",&TotalHitPeakChargeNoPlaneStanDev,"TotalHitPeakChargeNoPlaneStanDev/D");
   DetectorStabilityTree->Branch("UHitPeakChargeStanDev",&UHitPeakChargeStanDev,"UHitPeakChargeStanDev/D");
   DetectorStabilityTree->Branch("VHitPeakChargeStanDev",&VHitPeakChargeStanDev,"VHitPeakChargeStanDev/D");
   DetectorStabilityTree->Branch("YHitPeakChargeStanDev",&YHitPeakChargeStanDev,"YHitPeakChargeStanDev/D");

   DetectorStabilityTree->Branch("NTotalHitsInPlaneAverage",&NTotalHitsInPlaneAverage,"NTotalHitsInPlaneAverage/D");
   DetectorStabilityTree->Branch("NTotalHitsNoPlaneAverage",&NTotalHitsNoPlaneAverage,"NTotalHitsNoPlaneAverage/D");
   DetectorStabilityTree->Branch("NTotalHitsInPlaneAverage",&NTotalHitsInPlaneAverage,"NTotalHitsInPlaneAverage/D");
   DetectorStabilityTree->Branch("NTotalHitsNoPlaneAverage",&NTotalHitsNoPlaneAverage,"NTotalHitsNoPlaneAverage/D");
   DetectorStabilityTree->Branch("NUHitsAverage",&NUHitsAverage,"NUHitsAverage/D");
   DetectorStabilityTree->Branch("NVHitsAverage",&NVHitsAverage,"NVHitsAverage/D");
   DetectorStabilityTree->Branch("NYHitsAverage",&NYHitsAverage,"NYHitsAverage/D");

   DetectorStabilityTree->Branch("NAllFlashesAverage",&NAllFlashesAverage,"NAllFlashesAverage/D");
   DetectorStabilityTree->Branch("NFlashes50PEAverage",&NFlashes50PEAverage,"NFlashes50PEAverage/D");
   DetectorStabilityTree->Branch("FlashZCenterAverage",&FlashZCenterAverage,"FlashZCenterAverage/D");
   DetectorStabilityTree->Branch("FlashZCenter50PEAverage",&FlashZCenter50PEAverage,"FlashZCenter50PEAverage/D");
  
   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the blocks the names of the modules
   ana_tree_hits = new AnaTreeHits(fChain);
   ana_tree_flash = new AnaTreeFlash(fChain);
   ana_tree_run = new AnaTreeRunInfo(fChain);

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

      // Is this the first run?
      if(fCurrentRun == 0){
         fNRuns++;
         fCurrentRun = ana_tree_run->Run();
         EventTime = ana_tree_run->EventTime();
      }

      // Do we have a new run? 
      // If yes, fill the tree
      if(ana_tree_run->Run() != fCurrentRun && fCurrentRun != 0){
         fNRuns++;
         NUHitsAverage = (double)NUHits/(double)fNEventsInRun;
         NVHitsAverage = (double)NVHits/(double)fNEventsInRun;
         NYHitsAverage = (double)NYHits/(double)fNEventsInRun;
         NTotalHitsInPlaneAverage = (double)NTotalHitsInPlane/(double)fNEventsInRun;
         NTotalHitsNoPlaneAverage = (double)NTotalHitsNoPlane/(double)fNEventsInRun;
         
         UHitChargeAverage = (double)UHitCharge/(double)NUHits;
         VHitChargeAverage = (double)VHitCharge/(double)NVHits;
         YHitChargeAverage = (double)YHitCharge/(double)NYHits;
         TotalHitChargeInPlaneAverage = (double)TotalHitChargeInPlane/(double)NTotalHitsInPlane;
         TotalHitChargeNoPlaneAverage = (double)TotalHitChargeNoPlane/(double)NTotalHitsNoPlane;
         
         UHitPeakChargeAverage = (double)UHitPeakCharge/(double)NUHits;
         VHitPeakChargeAverage = (double)VHitPeakCharge/(double)NVHits;
         YHitPeakChargeAverage = (double)YHitPeakCharge/(double)NYHits;
         TotalHitPeakChargeInPlaneAverage = (double)TotalHitPeakChargeInPlane/(double)NTotalHitsInPlane;
         TotalHitPeakChargeNoPlaneAverage = (double)TotalHitPeakChargeNoPlane/(double)NTotalHitsNoPlane;
         
         NAllFlashesAverage = (double)NAllFlashes/(double)fNEventsInRun;
         NFlashes50PEAverage = (double)NFlashes50PE/(double)fNEventsInRun;
         FlashZCenterAverage = (double)FlashZCenter/(double)NAllFlashes;
         FlashZCenter50PEAverage = (double)FlashZCenter50PE/(double)NFlashes50PE;


         // Find the standard deviations 
         // Loop over hits
         for (int i = 0; i < ana_tree_hits->NHits(); i++){
            if(ana_tree_hits->HitPlane(i) == 0){ 
               UHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-UHitChargeAverage,2);
               UHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-UHitPeakChargeAverage,2);
               TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
               TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
               continue;
            }
            if(ana_tree_hits->HitPlane(i) == 1){
               VHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-VHitChargeAverage,2);
               VHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-VHitPeakChargeAverage,2);
               TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
               TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
               continue;
            }
            if(ana_tree_hits->HitPlane(i) == 2){
               YHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-YHitChargeAverage,2);
               YHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-YHitPeakChargeAverage,2);
               TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
               TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
               continue;
            }
            TotalHitChargeNoPlaneStanDev += pow((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage,2);
            TotalHitPeakChargeNoPlaneStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeNoPlaneAverage,2);
         }

         UHitChargeStanDev = sqrt(UHitChargeStanDev/(double)NUHits);
         VHitChargeStanDev = sqrt(VHitChargeStanDev/(double)NVHits);
         YHitChargeStanDev = sqrt(YHitChargeStanDev/(double)NYHits);
         UHitPeakChargeStanDev = sqrt(UHitPeakChargeStanDev/(double)NUHits);
         VHitPeakChargeStanDev = sqrt(VHitPeakChargeStanDev/(double)NVHits);
         YHitPeakChargeStanDev = sqrt(YHitPeakChargeStanDev/(double)NYHits);
         TotalHitChargeInPlaneStanDev = sqrt(TotalHitChargeInPlaneStanDev/(double)NTotalHitsInPlane);
         TotalHitChargeNoPlaneStanDev = sqrt(TotalHitChargeNoPlaneStanDev/(double)NTotalHitsNoPlane);
         TotalHitPeakChargeInPlaneStanDev = sqrt(TotalHitPeakChargeInPlaneStanDev/(double)NTotalHitsInPlane);
         TotalHitPeakChargeNoPlaneStanDev = sqrt(TotalHitPeakChargeNoPlaneStanDev/(double)NTotalHitsNoPlane);

         DetectorStabilityTree->Fill();
         fCurrentRun = ana_tree_run->Run();
         EventTime = ana_tree_run->EventTime();
         NTotalHitsInPlane = 0;
         NTotalHitsNoPlane = 0;
         NUHits = 0;
         NVHits = 0;
         NYHits = 0;
         TotalHitChargeInPlane = 0;
         TotalHitChargeNoPlane = 0;
         UHitCharge = 0;
         VHitCharge = 0;
         YHitCharge = 0;
         TotalHitPeakChargeInPlane = 0;
         TotalHitPeakChargeNoPlane = 0;
         UHitPeakCharge = 0;
         VHitPeakCharge = 0;
         YHitPeakCharge = 0;
         UHitChargeStanDev = 0;
         VHitChargeStanDev = 0;
         YHitChargeStanDev = 0;
         UHitPeakChargeStanDev = 0;
         VHitPeakChargeStanDev = 0;
         YHitPeakChargeStanDev = 0;
         TotalHitChargeInPlaneStanDev = 0;
         TotalHitChargeNoPlaneStanDev = 0;
         TotalHitPeakChargeInPlaneStanDev = 0;
         TotalHitPeakChargeNoPlaneStanDev = 0;
         NAllFlashes = 0;
         NFlashes50PE = 0;
         FlashZCenter = 0;
         FlashZCenter50PE = 0;
         fNEventsInRun = 0;

      }
      fNEventsInRun++;

      // Loop over hits
      for (int i = 0; i < ana_tree_hits->NHits(); i++){
         if(ana_tree_hits->HitPlane(i) == 0){ 
            NTotalHitsInPlane++;
            NUHits++;
            TotalHitChargeInPlane+=(double)ana_tree_hits->HitCharge(i);
            UHitCharge+=(long double)ana_tree_hits->HitCharge(i);
            TotalHitPeakChargeInPlane+=(double)ana_tree_hits->HitPeakCharge(i);
            UHitPeakCharge+=(long double)ana_tree_hits->HitPeakCharge(i);
            continue;
         }
         if(ana_tree_hits->HitPlane(i) == 1){
            NTotalHitsInPlane++;
            NVHits++;
            TotalHitChargeInPlane+=(double)ana_tree_hits->HitCharge(i);
            VHitCharge+=(double)ana_tree_hits->HitCharge(i);
            TotalHitPeakChargeInPlane+=(double)ana_tree_hits->HitPeakCharge(i);
            VHitPeakCharge+=(double)ana_tree_hits->HitPeakCharge(i);
            continue;
         }
         if(ana_tree_hits->HitPlane(i) == 2){
            NTotalHitsInPlane++;
            NYHits++;
            TotalHitChargeInPlane+=(double)ana_tree_hits->HitCharge(i);
            YHitCharge+=(double)ana_tree_hits->HitCharge(i);
            TotalHitPeakChargeInPlane+=(double)ana_tree_hits->HitPeakCharge(i);
            YHitPeakCharge+=(double)ana_tree_hits->HitPeakCharge(i);
            continue;
         }
         NTotalHitsNoPlane++;
         TotalHitChargeNoPlane+=(double)ana_tree_hits->HitCharge(i);
         TotalHitPeakChargeNoPlane+=(double)ana_tree_hits->HitPeakCharge(i);
      }

      // Loop over flashes 
      NAllFlashes += ana_tree_flash->NFlashes();
      for (int i = 0; i < ana_tree_flash->NFlashes(); i++){
         FlashZCenter+=ana_tree_flash->FlashZCenter(i);
         if(ana_tree_flash->FlashPE(i) > 50){
            NFlashes50PE++;
            FlashZCenter50PE+=ana_tree_flash->FlashZCenter(i);
         }
      }

   }

   
   stopwatch->Stop();
   std::cout << "Total CPU Time: " << stopwatch->CpuTime() << " Per Event: " << stopwatch->CpuTime()/nentries << std::endl;
   std::cout << "Total Real Time: " << stopwatch->RealTime() << " Per Event: " << stopwatch->RealTime()/nentries << std::endl;
   
   // std::cout << "Total hits in a plane: " << NTotalHitsInPlane << " " <<  (Double_t)NTotalHitsInPlane/(Double_t)nentries << std::endl;
   // std::cout << "Total hits not in a plane: " << NTotalHitsNoPlane << " " <<  (Double_t)NTotalHitsNoPlane/(Double_t)nentries << std::endl;
   // std::cout << "U hits: " << NUHits << " " <<  (Double_t)NUHits/(Double_t)nentries << std::endl;
   // std::cout << "V hits: " << NVHits << " " <<  (Double_t)NVHits/(Double_t)nentries << std::endl;
   // std::cout << "Y hits: " << NYHits << " " <<  (Double_t)NYHits/(Double_t)nentries << std::endl;
   // std::cout << "U hit charge average: " << (double)UHitCharge/(double)NUHits << std::endl;
   // std::cout << UHitCharge << std::endl;



   NUHitsAverage = (double)NUHits/(double)fNEventsInRun;
   NVHitsAverage = (double)NVHits/(double)fNEventsInRun;
   NYHitsAverage = (double)NYHits/(double)fNEventsInRun;
   NTotalHitsInPlaneAverage = (double)NTotalHitsInPlane/(double)fNEventsInRun;
   NTotalHitsNoPlaneAverage = (double)NTotalHitsNoPlane/(double)fNEventsInRun;
   
   UHitChargeAverage = (double)UHitCharge/(double)NUHits;
   VHitChargeAverage = (double)VHitCharge/(double)NVHits;
   YHitChargeAverage = (double)YHitCharge/(double)NYHits;
   TotalHitChargeInPlaneAverage = (double)TotalHitChargeInPlane/(double)NTotalHitsInPlane;
   TotalHitChargeNoPlaneAverage = (double)TotalHitChargeNoPlane/(double)NTotalHitsNoPlane;
   
   UHitPeakChargeAverage = (double)UHitPeakCharge/(double)NUHits;
   VHitPeakChargeAverage = (double)VHitPeakCharge/(double)NVHits;
   YHitPeakChargeAverage = (double)YHitPeakCharge/(double)NYHits;
   TotalHitPeakChargeInPlaneAverage = (double)TotalHitPeakChargeInPlane/(double)NTotalHitsInPlane;
   TotalHitPeakChargeNoPlaneAverage = (double)TotalHitPeakChargeNoPlane/(double)NTotalHitsNoPlane;

   NAllFlashesAverage = (double)NAllFlashes/(double)fNEventsInRun;
   NFlashes50PEAverage = (double)NFlashes50PE/(double)fNEventsInRun;
   FlashZCenterAverage = (double)FlashZCenter/(double)NAllFlashes;
   FlashZCenter50PEAverage = (double)FlashZCenter50PE/(double)NFlashes50PE;
   
   // Find the standard deviations 
   // Loop over hits
   for (int i = 0; i < ana_tree_hits->NHits(); i++){
      if(ana_tree_hits->HitPlane(i) == 0){ 
         UHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-UHitChargeAverage,2);
         UHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-UHitPeakChargeAverage,2);
         TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
         TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
         continue;
      }
      if(ana_tree_hits->HitPlane(i) == 1){
         VHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-VHitChargeAverage,2);
         VHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-VHitPeakChargeAverage,2);
         TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
         TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
         continue;
      }
      if(ana_tree_hits->HitPlane(i) == 2){
         YHitChargeStanDev += pow((double)ana_tree_hits->HitCharge(i)-YHitChargeAverage,2);
         YHitPeakChargeStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-YHitPeakChargeAverage,2);
         TotalHitChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitCharge(i)-TotalHitChargeInPlaneAverage ),2);
         TotalHitPeakChargeInPlaneStanDev += pow(((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeInPlaneAverage),2);
         continue;
      }
      TotalHitChargeNoPlaneStanDev += pow((double)ana_tree_hits->HitCharge(i)-TotalHitChargeNoPlaneAverage,2);
      TotalHitPeakChargeNoPlaneStanDev += pow((double)ana_tree_hits->HitPeakCharge(i)-TotalHitPeakChargeNoPlaneAverage,2);
   }

   UHitChargeStanDev = sqrt(UHitChargeStanDev/(double)NUHits);
   VHitChargeStanDev = sqrt(VHitChargeStanDev/(double)NVHits);
   YHitChargeStanDev = sqrt(YHitChargeStanDev/(double)NYHits);
   UHitPeakChargeStanDev = sqrt(UHitPeakChargeStanDev/(double)NUHits);
   VHitPeakChargeStanDev = sqrt(VHitPeakChargeStanDev/(double)NVHits);
   YHitPeakChargeStanDev = sqrt(YHitPeakChargeStanDev/(double)NYHits);
   TotalHitChargeInPlaneStanDev = sqrt(TotalHitChargeInPlaneStanDev/(double)NTotalHitsInPlane);
   TotalHitChargeNoPlaneStanDev = sqrt(TotalHitChargeNoPlaneStanDev/(double)NTotalHitsNoPlane);
   TotalHitPeakChargeInPlaneStanDev = sqrt(TotalHitPeakChargeInPlaneStanDev/(double)NTotalHitsInPlane);
   TotalHitPeakChargeNoPlaneStanDev = sqrt(TotalHitPeakChargeNoPlaneStanDev/(double)NTotalHitsNoPlane);
   
   
   DetectorStabilityTree->Fill();



   // Write the histograms
   TFile f(fOutputFileName,"recreate");

   DetectorStabilityTree->Write();

   // Close the file
   f.Close();

}






