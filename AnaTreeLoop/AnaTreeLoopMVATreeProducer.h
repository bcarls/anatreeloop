//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 29 14:12:47 2015 by ROOT version 5.34/25
// from TTree anatree/analysis tree
// found on file: /Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root
//////////////////////////////////////////////////////////

#ifndef AnaTreeLoopMVATreeProducer_h
#define AnaTreeLoopMVATreeProducer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TVector3.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

#include <iostream>

#include "AnaTreeTracks.h"
#include "AnaTreeVertex.h"
#include "AnaTreeTruth.h"
#include "AnaTreeAlgs.h"

// Fixed size dimensions of array or collections stored in the TTree if any.


// class AnaTreeTracks {

//    public:

//       /// Constructor
//       AnaTreeTracks(TTree *fChain,TString fTrackModule);

//       Short_t NTracks() {return fNTracks;}
//       void    GetTrack(Short_t i){itrack = i;}

//       Float_t Length(){ return fLength[itrack];}

//    private:

//       Float_t fLength[100];
//       Short_t fNTracks;
//       Short_t itrack;
// };



class AnaTreeLoopMVATreeProducer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain



   AnaTreeTracks  *ana_tree_tracks;
   AnaTreeVertex  *ana_tree_vtx;
   AnaTreeTruth   *ana_tree_truth;
   AnaTreeAlgs    *ana_tree_algs;

   // Parameters
   size_t          fNEvts;
   size_t          fNEvtsToReport;
   TString         fTrackModuleName;
   TString         fOutputFileName;
   TString         fOutputTreeFileName;

   std::vector<std::string>  *processname;

   AnaTreeLoopMVATreeProducer(TTree *tree=0);
   virtual ~AnaTreeLoopMVATreeProducer();
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
   void SetOutputFile(TString outputFileName);
   void SetOutputTreeFile(TString outputTreeFileName);


};

#endif

#ifdef AnaTreeLoopMVATreeProducer_cxx
AnaTreeLoopMVATreeProducer::AnaTreeLoopMVATreeProducer(TTree *tree) : fChain(0)
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

void AnaTreeLoopMVATreeProducer::SetTrackModule(TString trackModuleName){
   fTrackModuleName = trackModuleName;
   return;
}

void AnaTreeLoopMVATreeProducer::SetVertexModule(TString vertexModuleName){
   fVertexModuleName = vertexModuleName;
   return;
}

void AnaTreeLoopMVATreeProducer::SetOutputFile(TString outputFileName){
   fOutputFileName = outputFileName;
   return;
}

void AnaTreeLoopMVATreeProducer::SetOutputTreeFile(TString outputTreeFileName){
   fOutputTreeFileName = outputTreeFileName;
   return;
}

void AnaTreeLoopMVATreeProducer::SetNEventsToReport(size_t nEvtsToReport){
   fNEvtsToReport = nEvtsToReport;
   return;
}

void AnaTreeLoopMVATreeProducer::SetNEvents(size_t nevts){
   fNEvts = nevts;
   return;
}

AnaTreeLoopMVATreeProducer::~AnaTreeLoopMVATreeProducer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnaTreeLoopMVATreeProducer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnaTreeLoopMVATreeProducer::LoadTree(Long64_t entry)
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

void AnaTreeLoopMVATreeProducer::Init(TTree *tree)
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

Bool_t AnaTreeLoopMVATreeProducer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnaTreeLoopMVATreeProducer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
// Int_t AnaTreeLoopMVATreeProducer::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
#endif // #ifdef AnaTreeLoopMVATreeProducer_cxx
