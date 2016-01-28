//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 29 14:12:47 2015 by ROOT version 5.34/25
// from TTree anatree/analysis tree
// found on file: /Users/bcarls/MCC5_AnaTree/v03_07_00/prodcosmics/ana_hist.root
//////////////////////////////////////////////////////////

#ifndef AnaTreeLoop_h
#define AnaTreeLoop_h

#include <root/TROOT.h>
#include <root/TChain.h>
#include <root/TFile.h>
#include <root/TH1F.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

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



class AnaTreeLoop {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain


   // Declare histograms
   TH1F *hMCEvtsTruth;
   TH1F *hNuPDGTruth;
   TH1F *hCCNCTruth;
   TH1F *hRecoTruthVtxDist;
   TH1F *hRecoTruthVtxXDist;
   TH1F *hRecoTruthVtxYDist;
   TH1F *hRecoTruthVtxZDist;
   TH1F *hCCNCLongestTrackNuMu;
   TH1F *hCCNCLongestTrackNuMuBar;
   TH1F *hCCNCLongestTrackNuE;
   TH1F *hCCNCLongestTrackNuEBar;

   TH1F *hTrackPhi;
   TH1F *hLongestTrackPhi;
   TH1F *hTrackLength;
   TH1F *hLongestTrackLength;
   TH1F *hLongestTrackLengthTrueNuCC;
   TH1F *hLongestTrackLengthTrueNuNC;
   TH1F *hPerpDistXBound;
   TH1F *hPerpDistYBound;
   TH1F *hPerpDistZBound;
   TH1F *hPerpDistToABound;
   TH1F *hNearestDistUntaggedTrueCosToTaggedCosFM;
   TH1F *hNearestDistUntaggedTrueCosToTaggedCosGT;
   TH1F *hNearestDistUntaggedTrueCosToTaggedCosGTFM;
   TH1F *hNearestDistUntaggedTrueNuToTaggedCosFM;
   TH1F *hNearestDistUntaggedTrueNuToTaggedCosGT;
   TH1F *hNearestDistUntaggedTrueNuToTaggedCosGTFM;

   TH1F *hPerpDistXBoundTrueNuNoCosRem;
   TH1F *hPerpDistXBoundTrueNuFM;
   TH1F *hPerpDistXBoundTrueNuGT;
   TH1F *hPerpDistXBoundTrueNuGTFM;
   TH1F *hPerpDistYBoundTrueNuNoCosRem;
   TH1F *hPerpDistYBoundTrueNuFM;
   TH1F *hPerpDistYBoundTrueNuGT;
   TH1F *hPerpDistYBoundTrueNuGTFM;
   TH1F *hPerpDistZBoundTrueNuNoCosRem;
   TH1F *hPerpDistZBoundTrueNuFM;
   TH1F *hPerpDistZBoundTrueNuGT;
   TH1F *hPerpDistZBoundTrueNuGTFM;
   TH1F *hPerpDistToABoundTrueNuNoCosRem;
   TH1F *hPerpDistToABoundTrueNuFM;
   TH1F *hPerpDistToABoundTrueNuGT;
   TH1F *hPerpDistToABoundTrueNuGTFM;

   TH1F *hPerpDistXBoundTrueCosNoCosRem;
   TH1F *hPerpDistXBoundTrueCosFM;
   TH1F *hPerpDistXBoundTrueCosGT;
   TH1F *hPerpDistXBoundTrueCosGTFM;
   TH1F *hPerpDistYBoundTrueCosNoCosRem;
   TH1F *hPerpDistYBoundTrueCosFM;
   TH1F *hPerpDistYBoundTrueCosGT;
   TH1F *hPerpDistYBoundTrueCosGTFM;
   TH1F *hPerpDistZBoundTrueCosNoCosRem;
   TH1F *hPerpDistZBoundTrueCosFM;
   TH1F *hPerpDistZBoundTrueCosGT;
   TH1F *hPerpDistZBoundTrueCosGTFM;
   TH1F *hPerpDistToABoundTrueCosNoCosRem;
   TH1F *hPerpDistToABoundTrueCosFM;
   TH1F *hPerpDistToABoundTrueCosGT;
   TH1F *hPerpDistToABoundTrueCosGTFM;

   TH1F *hTrackPIDATrueCosNoCosRem;
   TH1F *hTrackPIDATrueNuNoCosRem;

   TH1F *hTrackThetaTrueNuNoCosRem;
   TH1F *hTrackThetaTrueCosNoCosRem;
   TH1F *hTrackThetaXZTrueNuNoCosRem;
   TH1F *hTrackThetaXZTrueCosNoCosRem;
   TH1F *hTrackThetaYZTrueNuNoCosRem;
   TH1F *hTrackThetaYZTrueCosNoCosRem;

   TH1F *hTrackPhiTrueNuNoCosRem;
   TH1F *hTrackPhiTrueCosNoCosRem;

   TH1F *hNTracks;
   TH1F *hTrueMuonPIDA;
   TH1F *hTruePionPIDA;
   TH1F *hTrueProtonPIDA;
   TH1F *hLongestTrackPIDA;
   TH1F *hLongestTrackPIDATrueNuCCMu;
   TH1F *hLongestTrackPIDATrueNuNCMu;
   TH1F *hLongestTrackPIDATrueNuCCPi;
   TH1F *hLongestTrackPIDATrueNuNCPi;
   TH1F *hTrackOrigin;
   TH1F *hLongestTrackOrigin;
   TH1F *hLepMomTruth;
   TH1F *hTrackOriginFM;
   TH1F *hTrackOriginNoCosRem;
   TH1F *hTrackOriginGT;
   TH1F *hTrackOriginGTFM;
   TH1F *hLongestTrackLengthTrueNu;
   TH1F *hLongestTrackLengthTrueCos;
   TH1F *hLongestTrackLengthTrueUnknown;
   TH1F *hTrackLengthNoCosRem;
   TH1F *hTrackLengthFM;
   TH1F *hTrackLengthGT;
   TH1F *hTrackLengthGTFM;
   TH1F *hTrackLengthTrueCosNoCosRem;
   TH1F *hTrackLengthTrueCosFM;
   TH1F *hTrackLengthTrueCosGT;
   TH1F *hTrackLengthTrueCosGTFM;
   TH1F *hTrackLengthTrueNuNoCosRem;
   TH1F *hTrackLengthTrueNuFM;
   TH1F *hTrackLengthTrueNuGT;
   TH1F *hTrackLengthTrueNuGTFM;
   TH1F *hTrackLengthTrueNuCCNoCosRem;
   TH1F *hTrackLengthTrueNuCCFM;
   TH1F *hTrackLengthTrueNuCCGT;
   TH1F *hTrackLengthTrueNuCCGTFM;
   TH1F *hTrackLengthTrueNuNCNoCosRem;
   TH1F *hTrackLengthTrueNuNCFM;
   TH1F *hTrackLengthTrueNuNCGT;
   TH1F *hTrackLengthTrueNuNCGTFM;
   TH1F *hTrackRangeTrueCosNoCosRem;
   TH1F *hTrackRangeTrueCosFM;
   TH1F *hTrackRangeTrueCosGT;
   TH1F *hTrackRangeTrueCosGTFM;
   TH1F *hTrackRangeTrueNuNoCosRem;
   TH1F *hTrackRangeTrueNuFM;
   TH1F *hTrackRangeTrueNuGT;
   TH1F *hTrackRangeTrueNuGTFM;
   TH1F *hTrackKETrueCosNoCosRem;
   TH1F *hTrackKETrueCosFM;
   TH1F *hTrackKETrueCosGT;
   TH1F *hTrackKETrueCosGTFM;
   TH1F *hTrackKETrueNuNoCosRem;
   TH1F *hTrackKETrueNuFM;
   TH1F *hTrackKETrueNuGT;
   TH1F *hTrackKETrueNuGTFM;

   TH1F *hLongestTrackNearestVtxDistTrueNuCC;
   TH1F *hLongestTrackNearestVtxDistTrueNuNC;
   TH1F *hLongestTrackNearestVtxDistTrueCos;



   AnaTreeTracks  *ana_tree_tracks;
   AnaTreeVertex  *ana_tree_vtx;
   AnaTreeTruth   *ana_tree_truth;
   AnaTreeAlgs    *ana_tree_algs;

   // Parameters
   size_t          fNEvts;
   size_t          fNEvtsToReport;
   TString         fTrackModuleName;
   TString         fVertexModuleName;
   TString         fOutputFileName;

   std::vector<std::string>  *processname;

   AnaTreeLoop(TTree *tree=0);
   virtual ~AnaTreeLoop();
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

#ifdef AnaTreeLoop_cxx
AnaTreeLoop::AnaTreeLoop(TTree *tree) : fChain(0)
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

void AnaTreeLoop::SetTrackModule(TString trackModuleName){
   fTrackModuleName = trackModuleName;
   return;
}

void AnaTreeLoop::SetVertexModule(TString vertexModuleName){
   fVertexModuleName = vertexModuleName;
   return;
}

void AnaTreeLoop::SetOutputFile(TString outputFileName){
   fOutputFileName = outputFileName;
   return;
}

void AnaTreeLoop::SetNEventsToReport(size_t nEvtsToReport){
   fNEvtsToReport = nEvtsToReport;
   return;
}

void AnaTreeLoop::SetNEvents(size_t nevts){
   fNEvts = nevts;
   return;
}

AnaTreeLoop::~AnaTreeLoop()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnaTreeLoop::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnaTreeLoop::LoadTree(Long64_t entry)
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

void AnaTreeLoop::Init(TTree *tree)
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

Bool_t AnaTreeLoop::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnaTreeLoop::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
// Int_t AnaTreeLoop::Cut(Long64_t entry)
// {
// // This function may be called from Loop.
// // returns  1 if entry is accepted.
// // returns -1 otherwise.
//    return 1;
// }
#endif // #ifdef AnaTreeLoop_cxx
