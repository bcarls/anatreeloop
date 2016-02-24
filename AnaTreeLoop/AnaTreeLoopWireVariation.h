//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 29 14:12:47 2015 by ROOT version 5.34/25
// from TTree anatree/analysis tree
// found on file: /Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root
//////////////////////////////////////////////////////////

#ifndef AnaTreeLoopWireVariation_h
#define AnaTreeLoopWireVariation_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

#include "AnaTreeRunInfo.h"
#include "AnaTreeTracks.h"
#include "AnaTreeHits.h"
#include "AnaTreeAlgs.h"


class AnaTreeLoopWireVariation {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   static const int kUWires = 2400;
   static const int kVWires = 2400;
   static const int kYWires = 3456;

   // Declare histograms
   TH1F *hTrackPhi;
   TH1F *hLongestTrackPhi;
   TH1F *hTrackThetaXZ;
   TH1F *hLongestTrackThetaXZ;
   TH1F *hTrackLength;
   TH1F *hLongestTrackLength;
   TH1F *hTrackLengthX;

   TH1F *hPerpDistXBound;
   TH1F *hPerpDistYBound;
   TH1F *hPerpDistZBound;
   TH1F *hPerpDistToABound;

   TH1F *hUPlanedQdx[kUWires];
   TH1F *hVPlanedQdx[kVWires];
   TH1F *hYPlanedQdx[kYWires];

   TH2F *hPerpDistToABoundTrackLength;
   TH2F *hYPlaneHitChargeVsAngle;

   // The module access objects
   AnaTreeRunInfo *ana_tree_runinfo;
   AnaTreeHits    *ana_tree_hits;
   AnaTreeTracks  *ana_tree_tracks;
   AnaTreeAlgs    *ana_tree_algs;

   // Parameters
   size_t          fNEvts;
   size_t          fNEvtsToReport;
   TString         fTrackModuleName;
   TString         fOutputFileName;

   std::vector<std::string>  *processname;

   AnaTreeLoopWireVariation(TTree *tree=0);
   virtual ~AnaTreeLoopWireVariation();
   // virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void SetNEvents(size_t nevts);
   void SetNEventsToReport(size_t nEvtsToReport);

   void SetTrackModule(TString trackModuleName);
   void SetVertexModule(TString trackVertexName);
   void SetOutputFile(TString outputFileName);


};

#endif

#ifdef AnaTreeLoopWireVariation_cxx
AnaTreeLoopWireVariation::AnaTreeLoopWireVariation(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root:/analysistree");
      dir->GetObject("anatree",tree);

   }
   Init(tree);

   fNEvts = 999999;
   fNEvtsToReport = 1000;
}

void AnaTreeLoopWireVariation::SetTrackModule(TString trackModuleName){
   fTrackModuleName = trackModuleName;
   return;
}

void AnaTreeLoopWireVariation::SetOutputFile(TString outputFileName){
   fOutputFileName = outputFileName;
   return;
}

void AnaTreeLoopWireVariation::SetNEventsToReport(size_t nEvtsToReport){
   fNEvtsToReport = nEvtsToReport;
   return;
}

void AnaTreeLoopWireVariation::SetNEvents(size_t nevts){
   fNEvts = nevts;
   return;
}

AnaTreeLoopWireVariation::~AnaTreeLoopWireVariation()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnaTreeLoopWireVariation::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnaTreeLoopWireVariation::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnaTreeLoopWireVariation::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   processname = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   Notify();
}

Bool_t AnaTreeLoopWireVariation::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnaTreeLoopWireVariation::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
// Int_t AnaTreeLoopWireVariation::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
#endif // #ifdef AnaTreeLoopWireVariation_cxx
