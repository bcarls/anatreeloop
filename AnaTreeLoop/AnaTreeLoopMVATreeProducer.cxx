#define AnaTreeLoopMVATreeProducer_cxx
#include "AnaTreeLoopMVATreeProducer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>



void AnaTreeLoopMVATreeProducer::Loop()
{

   TFile fTMVATrees(fOutputTreeFileName,"recreate");

   TTree tAll("tAll","Tree containing all track data");
   Float_t trackLengthAll, trackPerpDistXBoundAll, trackPerpDistYBoundAll, trackPerpDistZBoundAll,
            trackPerpDistToABoundAll, trackPIDAAll, trackRangeAll, trackKEAll, trackPhiAll, trackThetaAll, trackThetaXZAll,
            trackThetaYZAll, weightAll;
   Int_t trackTaggedCosAllGT;
   Int_t trackTaggedCosAllGTFM;
   Int_t trackOriginAll;
   tAll.Branch("trackLength",&trackLengthAll,"trackLength/F");
   tAll.Branch("trackPerpDistXBound",&trackPerpDistXBoundAll,"trackPerpDistXBound/F");
   tAll.Branch("trackPerpDistYBound",&trackPerpDistYBoundAll,"trackPerpDistYBound/F");
   tAll.Branch("trackPerpDistZBound",&trackPerpDistZBoundAll,"trackPerpDistZBound/F");
   tAll.Branch("trackPerpDistToABound",&trackPerpDistToABoundAll,"trackPerpDistToABound/F");
   tAll.Branch("trackPIDA",&trackPIDAAll,"trackPIDA/F");
   tAll.Branch("trackRange",&trackRangeAll,"trackRange/F");
   tAll.Branch("trackKE",&trackKEAll,"trackKE/F");
   tAll.Branch("trackPhi",&trackPhiAll,"trackPhi/F");
   tAll.Branch("trackTheta",&trackThetaAll,"trackTheta/F");
   tAll.Branch("trackThetaXZ",&trackThetaXZAll,"trackThetaXZ/F");
   tAll.Branch("trackThetaYZ",&trackThetaYZAll,"trackThetaYZ/F");
   tAll.Branch("trackOrigin",&trackOriginAll,"trackOrigin/I");
   tAll.Branch("trackTaggedCosGT",&trackTaggedCosAllGT,"trackTaggedCosGT/I");
   tAll.Branch("trackTaggedCosGTFM",&trackTaggedCosAllGTFM,"trackTaggedCosGTFM/I");
   tAll.Branch("weight",&weightAll,"weight/F");


   TTree tTrueNu("tTrueNu","Tree containing true neutrino track data");
   TTree tTrueCos("tTrueCos","Tree containing true cosmic track data");
   Float_t trackLengthTrueNu, trackPerpDistXBoundTrueNu, trackPerpDistYBoundTrueNu, trackPerpDistZBoundTrueNu,
            trackPerpDistToABoundTrueNu, trackPIDATrueNu, trackRangeTrueNu, trackKETrueNu, trackPhiTrueNu, trackThetaTrueNu, trackThetaXZTrueNu, trackThetaYZTrueNu;
   Float_t trackLengthTrueCos, trackPerpDistXBoundTrueCos, trackPerpDistYBoundTrueCos, trackPerpDistZBoundTrueCos,
            trackPerpDistToABoundTrueCos, trackPIDATrueCos, trackRangeTrueCos, trackKETrueCos, trackPhiTrueCos, trackThetaTrueCos, trackThetaXZTrueCos, trackThetaYZTrueCos, weightTrueCos;
   tTrueNu.Branch("trackLength",&trackLengthTrueNu,"trackLength/F");
   tTrueNu.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNu,"trackPerpDistXBound/F");
   tTrueNu.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNu,"trackPerpDistYBound/F");
   tTrueNu.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNu,"trackPerpDistZBound/F");
   tTrueNu.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNu,"trackPerpDistToABound/F");
   tTrueNu.Branch("trackPIDA",&trackPIDATrueNu,"trackPIDA/F");
   tTrueNu.Branch("trackRange",&trackRangeTrueNu,"trackRange/F");
   tTrueNu.Branch("trackKE",&trackKETrueNu,"trackKE/F");
   tTrueNu.Branch("trackPhi",&trackPhiTrueNu,"trackPhi/F");
   tTrueNu.Branch("trackTheta",&trackThetaTrueNu,"trackTheta/F");
   tTrueNu.Branch("trackThetaXZ",&trackThetaXZTrueNu,"trackThetaXZ/F");
   tTrueNu.Branch("trackThetaYZ",&trackThetaYZTrueNu,"trackThetaYZ/F");

   tTrueCos.Branch("trackLength",&trackLengthTrueCos,"trackLength/F");
   tTrueCos.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCos,"trackPerpDistXBound/F");
   tTrueCos.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCos,"trackPerpDistYBound/F");
   tTrueCos.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCos,"trackPerpDistZBound/F");
   tTrueCos.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCos,"trackPerpDistToABound/F");
   tTrueCos.Branch("trackPIDA",&trackPIDATrueCos,"trackPIDA/F");
   tTrueCos.Branch("trackRange",&trackRangeTrueCos,"trackRange/F");
   tTrueCos.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCos.Branch("trackPhi",&trackPhiTrueCos,"trackPhi/F");
   tTrueCos.Branch("trackTheta",&trackThetaTrueCos,"trackTheta/F");
   tTrueCos.Branch("trackThetaXZ",&trackThetaXZTrueCos,"trackThetaXZ/F");
   tTrueCos.Branch("trackThetaYZ",&trackThetaYZTrueCos,"trackThetaYZ/F");
   tTrueCos.Branch("weight",&weightTrueCos,"weight/F");




   TTree tTrueNuGT("tTrueNuGT","Tree containing true neutrino track data");
   TTree tTrueCosGT("tTrueCosGT","Tree containing true cosmic track data");
   Float_t trackLengthTrueNuGT, trackPerpDistXBoundTrueNuGT, trackPerpDistYBoundTrueNuGT, 
           trackPerpDistZBoundTrueNuGT, trackPerpDistToABoundTrueNuGT, trackPIDATrueNuGT, trackRangeTrueNuGT, trackKETrueNuGT,
           trackPhiTrueNuGT, trackThetaTrueNuGT, trackThetaXZTrueNuGT,
           trackThetaYZTrueNuGT, trackNearestDistUntaggedTrueNuToTaggedCosGT, weightTrueNuGT;
   Float_t trackLengthTrueCosGT, trackPerpDistXBoundTrueCosGT, trackPerpDistYBoundTrueCosGT, 
           trackPerpDistZBoundTrueCosGT, trackPerpDistToABoundTrueCosGT, trackPIDATrueCosGT, trackRangeTrueCosGT, trackKETrueCosGT,
           trackPhiTrueCosGT, trackThetaTrueCosGT, trackThetaXZTrueCosGT,
           trackThetaYZTrueCosGT, trackNearestDistUntaggedTrueCosToTaggedCosGT, weightTrueCosGT;
   tTrueNuGT.Branch("trackLength",&trackLengthTrueNuGT,"trackLength/F");
   tTrueNuGT.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuGT,"trackPerpDistXBound/F");
   tTrueNuGT.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuGT,"trackPerpDistYBound/F");
   tTrueNuGT.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuGT,"trackPerpDistZBound/F");
   tTrueNuGT.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuGT,"trackPerpDistToABound/F");
   tTrueNuGT.Branch("trackPIDA",&trackPIDATrueNuGT,"trackPIDA/F");
   tTrueNuGT.Branch("trackRange",&trackRangeTrueNuGT,"trackRange/F");
   tTrueNuGT.Branch("trackKE",&trackKETrueNuGT,"trackKE/F");
   tTrueNuGT.Branch("trackPhi",&trackPhiTrueNuGT,"trackPhi/F");
   tTrueNuGT.Branch("trackTheta",&trackThetaTrueNuGT,"trackTheta/F");
   tTrueNuGT.Branch("trackThetaXZ",&trackThetaXZTrueNuGT,"trackThetaXZ/F");
   tTrueNuGT.Branch("trackThetaYZ",&trackThetaYZTrueNuGT,"trackThetaYZ/F");
   tTrueNuGT.Branch("trackNearestDistUntaggedToTaggedCosGT",&trackNearestDistUntaggedTrueNuToTaggedCosGT,"trackNearestDistUntaggedToTaggedCosGT/F");

   tTrueCosGT.Branch("trackLength",&trackLengthTrueCosGT,"trackLength/F");
   tTrueCosGT.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCosGT,"trackPerpDistXBound/F");
   tTrueCosGT.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCosGT,"trackPerpDistYBound/F");
   tTrueCosGT.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCosGT,"trackPerpDistZBound/F");
   tTrueCosGT.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCosGT,"trackPerpDistToABound/F");
   tTrueCosGT.Branch("trackPIDA",&trackPIDATrueCosGT,"trackPIDA/F");
   tTrueCosGT.Branch("trackRange",&trackRangeTrueCos,"trackRange/F");
   tTrueCosGT.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCosGT.Branch("trackPhi",&trackPhiTrueCosGT,"trackPhi/F");
   tTrueCosGT.Branch("trackTheta",&trackThetaTrueCosGT,"trackTheta/F");
   tTrueCosGT.Branch("trackThetaXZ",&trackThetaXZTrueCosGT,"trackThetaXZ/F");
   tTrueCosGT.Branch("trackThetaYZ",&trackThetaYZTrueCosGT,"trackThetaYZ/F");
   tTrueCosGT.Branch("weight",&weightTrueCosGT,"weight/F");
   tTrueCosGT.Branch("trackNearestDistUntaggedToTaggedCosGT",&trackNearestDistUntaggedTrueCosToTaggedCosGT,"trackNearestDistUntaggedToTaggedCosGT/F");
   tTrueCosGT.Branch("weight",&weightTrueCosGT,"weight/F");

   TTree tTrueNuGTFM("tTrueNuGTFM","Tree containing true neutrino track data");
   TTree tTrueCosGTFM("tTrueCosGTFM","Tree containing true cosmic track data");
   Float_t trackLengthTrueNuGTFM, trackPerpDistXBoundTrueNuGTFM, trackPerpDistYBoundTrueNuGTFM, trackPerpDistZBoundTrueNuGTFM,
            trackPerpDistToABoundTrueNuGTFM, trackPIDATrueNuGTFM, trackRangeTrueNuGTFM, trackKETrueNuGTFM, trackPhiTrueNuGTFM, trackThetaTrueNuGTFM, trackThetaXZTrueNuGTFM, trackThetaYZTrueNuGTFM, trackNearestDistUntaggedTrueNuToTaggedCosGTFM;
   Int_t trackTaggedCosTrueNuGTFM;

   Float_t trackLengthTrueCosGTFM, trackPerpDistXBoundTrueCosGTFM, trackPerpDistYBoundTrueCosGTFM, 
           trackPerpDistZBoundTrueCosGTFM, trackPerpDistToABoundTrueCosGTFM, trackPIDATrueCosGTFM, trackRangeTrueCosGTFM, trackKETrueCosGTFM, trackPhiTrueCosGTFM, trackThetaTrueCosGTFM, trackThetaXZTrueCosGTFM,
           trackThetaYZTrueCosGTFM, trackNearestDistUntaggedTrueCosToTaggedCosGTFM, weightTrueCosGTFM;
   Int_t trackTaggedCosTrueCosGTFM;
   
   tTrueNuGTFM.Branch("trackLength",&trackLengthTrueNuGTFM,"trackLength/F");
   tTrueNuGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuGTFM,"trackPerpDistXBound/F");
   tTrueNuGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuGTFM,"trackPerpDistYBound/F");
   tTrueNuGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuGTFM,"trackPerpDistZBound/F");
   tTrueNuGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuGTFM,"trackPerpDistToABound/F");
   tTrueNuGTFM.Branch("trackPIDA",&trackPIDATrueNuGTFM,"trackPIDA/F");
   tTrueNuGTFM.Branch("trackRange",&trackRangeTrueNuGTFM,"trackRange/F");
   tTrueNuGTFM.Branch("trackKE",&trackKETrueNuGTFM,"trackKE/F");
   tTrueNuGTFM.Branch("trackPhi",&trackPhiTrueNuGTFM,"trackPhi/F");
   tTrueNuGTFM.Branch("trackTheta",&trackThetaTrueNuGTFM,"trackTheta/F");
   tTrueNuGTFM.Branch("trackThetaXZ",&trackThetaXZTrueNuGTFM,"trackThetaXZ/F");
   tTrueNuGTFM.Branch("trackThetaYZ",&trackThetaYZTrueNuGTFM,"trackThetaYZ/F");
   tTrueNuGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueNuToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosGTFM/F");

   tTrueCosGTFM.Branch("trackLength",&trackLengthTrueCosGTFM,"trackLength/F");
   tTrueCosGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCosGTFM,"trackPerpDistXBound/F");
   tTrueCosGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCosGTFM,"trackPerpDisYBound/F");
   tTrueCosGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCosGTFM,"trackPerpDistZBound/F");
   tTrueCosGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCosGTFM,"trackPerpDistToABound/F");
   tTrueCosGTFM.Branch("trackPIDA",&trackPIDATrueCosGTFM,"trackPIDA/F");
   tTrueCosGTFM.Branch("trackRange",&trackRangeTrueCos,"trackRange/F");
   tTrueCosGTFM.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCosGTFM.Branch("trackPhi",&trackPhiTrueCosGTFM,"trackPhi/F");
   tTrueCosGTFM.Branch("trackTheta",&trackThetaTrueCosGTFM,"trackTheta/F");
   tTrueCosGTFM.Branch("trackThetaXZ",&trackThetaXZTrueCosGTFM,"trackThetaXZ/F");
   tTrueCosGTFM.Branch("trackThetaYZ",&trackThetaYZTrueCosGTFM,"trackThetaYZ/F");
   tTrueCosGTFM.Branch("weight",&weightTrueCosGTFM,"weight/F");
   tTrueCosGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueCosToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosGTFM/F");
   tTrueCosGTFM.Branch("weight",&weightTrueCosGTFM,"weight/F");


   TTree tTrueNuLongestGTFM("tTrueNuLongestGTFM","Tree containing true neutrino track data");
   TTree tTrueNuCCLongestGTFM("tTrueNuCCLongestGTFM","Tree containing true neutrino track data");
   TTree tTrueNuNCLongestGTFM("tTrueNuNCLongestGTFM","Tree containing true neutrino track data");
   TTree tTrueCosLongestGTFM("tTrueCosLongestGTFM","Tree containing true cosmic track data");
   Float_t trackLengthTrueNuLongestGTFM, trackPerpDistXBoundTrueNuLongestGTFM, trackPerpDistYBoundTrueNuLongestGTFM, 
           trackPerpDistZBoundTrueNuLongestGTFM,
            trackPerpDistToABoundTrueNuLongestGTFM, trackPIDATrueNuLongestGTFM, trackRangeTrueNuLongestGTFM, trackKETrueNuLongestGTFM, trackPhiTrueNuLongestGTFM, trackThetaTrueNuLongestGTFM, trackThetaXZTrueNuLongestGTFM, trackThetaYZTrueNuLongestGTFM, trackNearestDistUntaggedTrueNuLongestToTaggedCosGTFM, trackNearestVtxDistTrueNuLongestGTFM;
   Int_t trackTaggedCosTrueNuLongestGTFM;
   
   Float_t trackLengthTrueNuCCLongestGTFM, trackPerpDistXBoundTrueNuCCLongestGTFM, trackPerpDistYBoundTrueNuCCLongestGTFM, 
           trackPerpDistZBoundTrueNuCCLongestGTFM,
            trackPerpDistToABoundTrueNuCCLongestGTFM, trackPIDATrueNuCCLongestGTFM, trackRangeTrueNuCCLongestGTFM, trackKETrueNuCCLongestGTFM, trackPhiTrueNuCCLongestGTFM, trackThetaTrueNuCCLongestGTFM, trackThetaXZTrueNuCCLongestGTFM, trackThetaYZTrueNuCCLongestGTFM, trackNearestDistUntaggedTrueNuCCLongestToTaggedCosGTFM, trackNearestVtxDistTrueNuCCLongestGTFM;
   Int_t trackTaggedCosTrueNuCCLongestGTFM;

   Float_t trackLengthTrueNuNCLongestGTFM, trackPerpDistXBoundTrueNuNCLongestGTFM, trackPerpDistYBoundTrueNuNCLongestGTFM, 
           trackPerpDistZBoundTrueNuNCLongestGTFM,
            trackPerpDistToABoundTrueNuNCLongestGTFM, trackPIDATrueNuNCLongestGTFM, trackRangeTrueNuNCLongestGTFM, trackKETrueNuNCLongestGTFM, trackPhiTrueNuNCLongestGTFM, trackThetaTrueNuNCLongestGTFM, trackThetaXZTrueNuNCLongestGTFM, trackThetaYZTrueNuNCLongestGTFM, trackNearestDistUntaggedTrueNuNCLongestToTaggedCosGTFM, trackNearestVtxDistTrueNuNCLongestGTFM, weightTrueNuNCLongestGTFM;
   Int_t trackTaggedCosTrueNuNCLongestGTFM;

   Float_t trackLengthTrueCosLongestGTFM, trackPerpDistXBoundTrueCosLongestGTFM, trackPerpDistYBoundTrueCosLongestGTFM, 
           trackPerpDistZBoundTrueCosLongestGTFM, trackPerpDistToABoundTrueCosLongestGTFM, trackPIDATrueCosLongestGTFM, trackRangeTrueCosLongestGTFM, trackKETrueCosLongestGTFM, trackPhiTrueCosLongestGTFM, trackThetaTrueCosLongestGTFM, trackThetaXZTrueCosLongestGTFM,
           trackThetaYZTrueCosLongestGTFM, trackNearestDistUntaggedTrueCosLongestToTaggedCosGTFM, weightTrueCosLongestGTFM, trackNearestVtxDistTrueCosLongestGTFM;
   Int_t trackTaggedCosTrueCosLongestGTFM;

   tTrueNuLongestGTFM.Branch("trackLength",&trackLengthTrueNuLongestGTFM,"trackLength/F");
   tTrueNuLongestGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuLongestGTFM,"trackPerpDistXBound/F");
   tTrueNuLongestGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuLongestGTFM,"trackPerpDistYBound/F");
   tTrueNuLongestGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuLongestGTFM,"trackPerpDistZBound/F");
   tTrueNuLongestGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuLongestGTFM,"trackPerpDistToABound/F");
   tTrueNuLongestGTFM.Branch("trackPIDA",&trackPIDATrueNuLongestGTFM,"trackPIDA/F");
   tTrueNuLongestGTFM.Branch("trackRange",&trackRangeTrueNuLongestGTFM,"trackRange/F");
   tTrueNuLongestGTFM.Branch("trackKE",&trackKETrueNuLongestGTFM,"trackKE/F");
   tTrueNuLongestGTFM.Branch("trackPhi",&trackPhiTrueNuLongestGTFM,"trackPhi/F");
   tTrueNuLongestGTFM.Branch("trackTheta",&trackThetaTrueNuLongestGTFM,"trackTheta/F");
   tTrueNuLongestGTFM.Branch("trackThetaXZ",&trackThetaXZTrueNuLongestGTFM,"trackThetaXZ/F");
   tTrueNuLongestGTFM.Branch("trackThetaYZ",&trackThetaYZTrueNuLongestGTFM,"trackThetaYZ/F");
   tTrueNuLongestGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueNuLongestToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosGTFM/F");
   tTrueNuLongestGTFM.Branch("trackNearestVtxDist",&trackNearestVtxDistTrueNuLongestGTFM,"trackNearestVtxDist/F");

   tTrueNuCCLongestGTFM.Branch("trackLength",&trackLengthTrueNuCCLongestGTFM,"trackLength/F");
   tTrueNuCCLongestGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuCCLongestGTFM,"trackPerpDistXBound/F");
   tTrueNuCCLongestGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuCCLongestGTFM,"trackPerpDistYBound/F");
   tTrueNuCCLongestGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuCCLongestGTFM,"trackPerpDistZBound/F");
   tTrueNuCCLongestGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuCCLongestGTFM,"trackPerpDistToABound/F");
   tTrueNuCCLongestGTFM.Branch("trackPIDA",&trackPIDATrueNuCCLongestGTFM,"trackPIDA/F");
   tTrueNuCCLongestGTFM.Branch("trackRange",&trackRangeTrueNuCCLongestGTFM,"trackRange/F");
   tTrueNuCCLongestGTFM.Branch("trackKE",&trackKETrueNuCCLongestGTFM,"trackKE/F");
   tTrueNuCCLongestGTFM.Branch("trackPhi",&trackPhiTrueNuCCLongestGTFM,"trackPhi/F");
   tTrueNuCCLongestGTFM.Branch("trackTheta",&trackThetaTrueNuCCLongestGTFM,"trackTheta/F");
   tTrueNuCCLongestGTFM.Branch("trackThetaXZ",&trackThetaXZTrueNuCCLongestGTFM,"trackThetaXZ/F");
   tTrueNuCCLongestGTFM.Branch("trackThetaYZ",&trackThetaYZTrueNuCCLongestGTFM,"trackThetaYZ/F");
   tTrueNuCCLongestGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueNuCCLongestToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosGTFM/F");
   tTrueNuCCLongestGTFM.Branch("trackNearestVtxDist",&trackNearestVtxDistTrueNuCCLongestGTFM,"trackNearestVtxDist/F");

   tTrueNuNCLongestGTFM.Branch("trackLength",&trackLengthTrueNuNCLongestGTFM,"trackLength/F");
   tTrueNuNCLongestGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueNuNCLongestGTFM,"trackPerpDistXBound/F");
   tTrueNuNCLongestGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueNuNCLongestGTFM,"trackPerpDistYBound/F");
   tTrueNuNCLongestGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueNuNCLongestGTFM,"trackPerpDistZBound/F");
   tTrueNuNCLongestGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueNuNCLongestGTFM,"trackPerpDistToABound/F");
   tTrueNuNCLongestGTFM.Branch("trackPIDA",&trackPIDATrueNuNCLongestGTFM,"trackPIDA/F");
   tTrueNuNCLongestGTFM.Branch("trackRange",&trackRangeTrueNuNCLongestGTFM,"trackRange/F");
   tTrueNuNCLongestGTFM.Branch("trackKE",&trackKETrueNuNCLongestGTFM,"trackKE/F");
   tTrueNuNCLongestGTFM.Branch("trackPhi",&trackPhiTrueNuNCLongestGTFM,"trackPhi/F");
   tTrueNuNCLongestGTFM.Branch("trackTheta",&trackThetaTrueNuNCLongestGTFM,"trackTheta/F");
   tTrueNuNCLongestGTFM.Branch("trackThetaXZ",&trackThetaXZTrueNuNCLongestGTFM,"trackThetaXZ/F");
   tTrueNuNCLongestGTFM.Branch("trackThetaYZ",&trackThetaYZTrueNuNCLongestGTFM,"trackThetaYZ/F");
   tTrueNuNCLongestGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueNuNCLongestToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosGTFM/F");
   tTrueNuNCLongestGTFM.Branch("trackNearestVtxDist",&trackNearestVtxDistTrueNuNCLongestGTFM,"trackNearestVtxDist/F");
   tTrueNuNCLongestGTFM.Branch("weight",&weightTrueNuNCLongestGTFM,"weight/F");

   tTrueCosLongestGTFM.Branch("trackLength",&trackLengthTrueCosLongestGTFM,"trackLength/F");
   tTrueCosLongestGTFM.Branch("trackPerpDistXBound",&trackPerpDistXBoundTrueCosLongestGTFM,"trackPerpDistXBound/F");
   tTrueCosLongestGTFM.Branch("trackPerpDistYBound",&trackPerpDistYBoundTrueCosLongestGTFM,"trackPerpDisYBound/F");
   tTrueCosLongestGTFM.Branch("trackPerpDistZBound",&trackPerpDistZBoundTrueCosLongestGTFM,"trackPerpDistZBound/F");
   tTrueCosLongestGTFM.Branch("trackPerpDistToABound",&trackPerpDistToABoundTrueCosLongestGTFM,"trackPerpDistToABound/F");
   tTrueCosLongestGTFM.Branch("trackPIDA",&trackPIDATrueCosLongestGTFM,"trackPIDA/F");
   tTrueCosLongestGTFM.Branch("trackRange",&trackRangeTrueCosLongestGTFM,"trackRange/F");
   tTrueCosLongestGTFM.Branch("trackKE",&trackKETrueCos,"trackKE/F");
   tTrueCosLongestGTFM.Branch("trackPhi",&trackPhiTrueCosLongestGTFM,"trackPhi/F");
   tTrueCosLongestGTFM.Branch("trackTheta",&trackThetaTrueCosLongestGTFM,"trackTheta/F");
   tTrueCosLongestGTFM.Branch("trackThetaXZ",&trackThetaXZTrueCosLongestGTFM,"trackThetaXZ/F");
   tTrueCosLongestGTFM.Branch("trackThetaYZ",&trackThetaYZTrueCosLongestGTFM,"trackThetaYZ/F");
   tTrueCosLongestGTFM.Branch("weight",&weightTrueCosLongestGTFM,"weight/F");
   tTrueCosLongestGTFM.Branch("trackNearestDistUntaggedToTaggedCosGTFM",&trackNearestDistUntaggedTrueCosLongestToTaggedCosGTFM,"trackNearestDistUntaggedToTaggedCosLongestGTFM/F");
   tTrueCosLongestGTFM.Branch("trackNearestVtxDist",&trackNearestVtxDistTrueCosLongestGTFM,"trackNearestVtxDist/F");
   tTrueCosLongestGTFM.Branch("weight",&weightTrueCosLongestGTFM,"weight/F");



   // Turn off all branches, this speeds stuff up
   fChain->SetBranchStatus("*",0);
   // Give the tracks blocks the name of the track module
   ana_tree_tracks = new AnaTreeTracks(fChain,fTrackModuleName);
   ana_tree_truth = new AnaTreeTruth(fChain);
   ana_tree_vtx = new AnaTreeVertex(fChain,fVertexModuleName);


   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116., 0.,256.,116.,1060.};

   size_t nEvtsProcessed = 0;
   size_t nEvtsFiredPMTTrigger = 0;

   if (fChain == 0) return;

   size_t nEvtsLongestTrackNu = 0;
   size_t nEvtsLongestTrackCos = 0;

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

      // Check if this event has a flash match consistent with a neutrino on any track (< 0.5 or 0.0)
      // If it does, the event had a track which fired the PMT trigger
      bool firedPMTTrigger = false;
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){
         if(ana_tree_tracks->CosmicScoreFlashMatch(i) < 0.5){
            firedPMTTrigger = true;
            nEvtsFiredPMTTrigger++;
            break;
         }
      }

      double longestTrackLength = 0;
      double longestTrackOrigin = -1;
      double longestTrackLengthNuGTFM = 0;
      double longestTrackLengthCosGTFM = 0;
      int longestTrackMatchedVtxIndex = -1;
      int longestTrackMatchedVtxIndexNuGTFM = -1;
      int longestTrackMatchedVtxIndexCosGTFM = -1;
      int longestTrackMatchedVtxDistNuGTFM = -1;
      int longestTrackMatchedVtxDistCosGTFM = -1;
      int longestTrackIndexNuGTFM = -1;
      int longestTrackIndexCosGTFM = -1;
      
      // Find the longest track in the event   
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){
         // Is it contained? I'm using the cosmic tagger to check.
         if(ana_tree_tracks->CosmicScoreTagger(i) > 0.4
              or ana_tree_tracks->CosmicScoreFlashMatch(i) > 0.5)
            continue;

         double minVertexTrackDist = 999999;
         int minVertexTrackDistIndex = -1;
         // Does the track match a vertex?
         for (short j= 0; j< ana_tree_vtx->NVertex(); j++){
            // Check at start point
            double startVertexDist = sqrt(pow(ana_tree_tracks->StartX(i)-ana_tree_vtx->VertexX(j),2) +
                                          pow(ana_tree_tracks->StartY(i)-ana_tree_vtx->VertexY(j),2) +
                                          pow(ana_tree_tracks->StartZ(i)-ana_tree_vtx->VertexZ(j),2));
            if(startVertexDist < minVertexTrackDist){
               minVertexTrackDist = startVertexDist;
               minVertexTrackDistIndex = j;
            }
            // Check at end point
            double endVertexDist = sqrt(pow(ana_tree_tracks->EndX(i)-ana_tree_vtx->VertexX(j),2) +
                                        pow(ana_tree_tracks->EndY(i)-ana_tree_vtx->VertexY(j),2) +
                                        pow(ana_tree_tracks->EndZ(i)-ana_tree_vtx->VertexZ(j),2));
            if(endVertexDist < minVertexTrackDist){
               minVertexTrackDist = endVertexDist;
               minVertexTrackDistIndex = j;
            }
         }

         // Only accept the vertex and the track if it is in the fiducial volume
         if(!(ana_tree_algs->IsFiducial(ana_tree_vtx->VertexX(minVertexTrackDistIndex),ana_tree_vtx->VertexY(minVertexTrackDistIndex),ana_tree_vtx->VertexZ(minVertexTrackDistIndex))))
            continue;

         if(ana_tree_tracks->Length(i) > longestTrackLength){
            longestTrackLength = ana_tree_tracks->Length(i);
            longestTrackOrigin = ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i));
            longestTrackMatchedVtxIndex = minVertexTrackDistIndex;
         }

         
         if(ana_tree_tracks->Length(i) > longestTrackLengthNuGTFM && ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
            longestTrackLengthNuGTFM = ana_tree_tracks->Length(i);
            longestTrackIndexNuGTFM = i;
            longestTrackMatchedVtxIndexNuGTFM = minVertexTrackDistIndex;
            longestTrackMatchedVtxDistNuGTFM = minVertexTrackDist;
         }
         if(ana_tree_tracks->Length(i) > longestTrackLengthCosGTFM && ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
            longestTrackLengthCosGTFM = ana_tree_tracks->Length(i);
            longestTrackIndexCosGTFM = i;
            longestTrackMatchedVtxIndexCosGTFM = minVertexTrackDistIndex;
            longestTrackMatchedVtxDistCosGTFM = minVertexTrackDist;
         }

      }

      if(longestTrackOrigin == 2)
         nEvtsLongestTrackCos++;
      if(longestTrackOrigin == 1)
         nEvtsLongestTrackNu++;


      // Fill the longest track trees
      // The GTFM cut has already been applied
      if(longestTrackLengthNuGTFM > 0 and
         // longestTrackLengthNuGTFM > 100 and 
         ana_tree_tracks->PIDA(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 100 and
         ana_tree_tracks->KE(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 100000 and
         ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) < 1060. and
         ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM)) > 0.){
         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexNuGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexNuGTFM));
         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexNuGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexNuGTFM));
         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexNuGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexNuGTFM));
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));
         // get distance to closest tagged cosmic track 
         double shortestTrackDistance = 999999;
         for (short j=0; j< ana_tree_tracks->NTracks(); j++){
            if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                  or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
               double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,longestTrackIndexNuGTFM,j);
               if(trackDistance < shortestTrackDistance)
                  shortestTrackDistance = trackDistance;
            }
         }

         trackLengthTrueNuLongestGTFM = ana_tree_tracks->Length(longestTrackIndexNuGTFM);
         trackPerpDistXBoundTrueNuLongestGTFM = min_x_dist;
         trackPerpDistYBoundTrueNuLongestGTFM = min_y_dist;
         trackPerpDistZBoundTrueNuLongestGTFM = min_z_dist;
         trackPerpDistToABoundTrueNuLongestGTFM = min_to_a_boundary_dist;
         trackPIDATrueNuLongestGTFM = ana_tree_tracks->PIDA(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
         trackRangeTrueNuLongestGTFM = ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
         trackKETrueNuLongestGTFM = ana_tree_tracks->KE(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
         trackPhiTrueNuLongestGTFM = ana_tree_tracks->Phi(longestTrackIndexNuGTFM);
         if(trackPhiTrueNuLongestGTFM < 0)
            trackPhiTrueNuLongestGTFM  = -trackPhiTrueNuLongestGTFM;
         trackThetaTrueNuLongestGTFM = ana_tree_tracks->Theta(longestTrackIndexNuGTFM);
         trackThetaXZTrueNuLongestGTFM = ana_tree_tracks->ThetaXZ(longestTrackIndexNuGTFM);
         trackThetaYZTrueNuLongestGTFM = ana_tree_tracks->ThetaYZ(longestTrackIndexNuGTFM);
         if(trackThetaYZTrueNuLongestGTFM < 0)
            trackThetaYZTrueNuLongestGTFM = -trackThetaYZTrueNuLongestGTFM;
         if(trackThetaYZTrueNuLongestGTFM > TMath::Pi()/2)
            trackThetaYZTrueNuLongestGTFM = -(trackThetaYZTrueNuLongestGTFM-TMath::Pi());
         trackNearestDistUntaggedTrueNuLongestToTaggedCosGTFM=shortestTrackDistance;
         trackNearestVtxDistTrueNuLongestGTFM = longestTrackMatchedVtxDistNuGTFM;
         tTrueNuLongestGTFM.Fill();

         // Do we have a CC event?
         if(ana_tree_truth->CCNCTruth(0) == 0){
            trackLengthTrueNuCCLongestGTFM = ana_tree_tracks->Length(longestTrackIndexNuGTFM);
            trackPerpDistXBoundTrueNuCCLongestGTFM = min_x_dist;
            trackPerpDistYBoundTrueNuCCLongestGTFM = min_y_dist;
            trackPerpDistZBoundTrueNuCCLongestGTFM = min_z_dist;
            trackPerpDistToABoundTrueNuCCLongestGTFM = min_to_a_boundary_dist;
            trackPIDATrueNuCCLongestGTFM = ana_tree_tracks->PIDA(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackRangeTrueNuCCLongestGTFM = ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackKETrueNuCCLongestGTFM = ana_tree_tracks->KE(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackPhiTrueNuCCLongestGTFM = ana_tree_tracks->Phi(longestTrackIndexNuGTFM);
            if(trackPhiTrueNuCCLongestGTFM < 0)
               trackPhiTrueNuCCLongestGTFM  = -trackPhiTrueNuCCLongestGTFM;
            trackThetaTrueNuCCLongestGTFM = ana_tree_tracks->Theta(longestTrackIndexNuGTFM);
            trackThetaXZTrueNuCCLongestGTFM = ana_tree_tracks->ThetaXZ(longestTrackIndexNuGTFM);
            trackThetaYZTrueNuCCLongestGTFM = ana_tree_tracks->ThetaYZ(longestTrackIndexNuGTFM);
            if(trackThetaYZTrueNuCCLongestGTFM < 0)
               trackThetaYZTrueNuCCLongestGTFM = -trackThetaYZTrueNuCCLongestGTFM;
            if(trackThetaYZTrueNuCCLongestGTFM > TMath::Pi()/2)
               trackThetaYZTrueNuCCLongestGTFM = -(trackThetaYZTrueNuCCLongestGTFM-TMath::Pi());
            trackNearestDistUntaggedTrueNuCCLongestToTaggedCosGTFM=shortestTrackDistance;
            trackNearestVtxDistTrueNuCCLongestGTFM = longestTrackMatchedVtxDistNuGTFM;
            tTrueNuCCLongestGTFM.Fill();
         }

         // Do we have a NC event?
         if(ana_tree_truth->CCNCTruth(0) == 1){
            trackLengthTrueNuNCLongestGTFM = ana_tree_tracks->Length(longestTrackIndexNuGTFM);
            trackPerpDistXBoundTrueNuNCLongestGTFM = min_x_dist;
            trackPerpDistYBoundTrueNuNCLongestGTFM = min_y_dist;
            trackPerpDistZBoundTrueNuNCLongestGTFM = min_z_dist;
            trackPerpDistToABoundTrueNuNCLongestGTFM = min_to_a_boundary_dist;
            trackPIDATrueNuNCLongestGTFM = ana_tree_tracks->PIDA(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackRangeTrueNuNCLongestGTFM = ana_tree_tracks->Range(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackKETrueNuNCLongestGTFM = ana_tree_tracks->KE(longestTrackIndexNuGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexNuGTFM));
            trackPhiTrueNuNCLongestGTFM = ana_tree_tracks->Phi(longestTrackIndexNuGTFM);
            if(trackPhiTrueNuNCLongestGTFM < 0)
               trackPhiTrueNuNCLongestGTFM  = -trackPhiTrueNuNCLongestGTFM;
            trackThetaTrueNuNCLongestGTFM = ana_tree_tracks->Theta(longestTrackIndexNuGTFM);
            trackThetaXZTrueNuNCLongestGTFM = ana_tree_tracks->ThetaXZ(longestTrackIndexNuGTFM);
            trackThetaYZTrueNuNCLongestGTFM = ana_tree_tracks->ThetaYZ(longestTrackIndexNuGTFM);
            if(trackThetaYZTrueNuNCLongestGTFM < 0)
               trackThetaYZTrueNuNCLongestGTFM = -trackThetaYZTrueNuNCLongestGTFM;
            if(trackThetaYZTrueNuNCLongestGTFM > TMath::Pi()/2)
               trackThetaYZTrueNuNCLongestGTFM = -(trackThetaYZTrueNuNCLongestGTFM-TMath::Pi());
            trackNearestDistUntaggedTrueNuNCLongestToTaggedCosGTFM=shortestTrackDistance;
            trackNearestVtxDistTrueNuNCLongestGTFM = longestTrackMatchedVtxDistNuGTFM;
            weightTrueNuNCLongestGTFM = 1;
            tTrueNuNCLongestGTFM.Fill();
         }



      }
      if(longestTrackLengthCosGTFM > 0 and
         // longestTrackLengthCosGTFM > 100 and 
         ana_tree_tracks->PIDA(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 100 and
         ana_tree_tracks->KE(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 100000 and
         ana_tree_tracks->Range(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) < 1060. and
         ana_tree_tracks->Range(longestTrackIndexCosGTFM,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM)) > 0.){
         // Look at boundaries of TPC
         // Consider distance to Y boundary
         double min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[1]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->StartY(longestTrackIndexCosGTFM));
         if(min_y_dist > std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM))) 
            min_y_dist = std::abs(fTPC[4]-ana_tree_tracks->EndY(longestTrackIndexCosGTFM));
         // Consider distance to X boundary
         double min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[0]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->StartX(longestTrackIndexCosGTFM));
         if(min_x_dist > std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM))) 
            min_x_dist = std::abs(fTPC[3]-ana_tree_tracks->EndX(longestTrackIndexCosGTFM));
         // Consider distance to Z boundary
         double min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[2]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->StartZ(longestTrackIndexCosGTFM));
         if(min_z_dist > std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM))) 
            min_z_dist = std::abs(fTPC[5]-ana_tree_tracks->EndZ(longestTrackIndexCosGTFM));
         double min_to_a_boundary_dist = std::min(min_z_dist, std::min(min_y_dist,min_x_dist));
         // get distance to closest tagged cosmic track 
         double shortestTrackDistance = 999999;
         for (short j=0; j< ana_tree_tracks->NTracks(); j++){
            if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                  or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
               double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,longestTrackIndexNuGTFM,j);
               if(trackDistance < shortestTrackDistance)
                  shortestTrackDistance = trackDistance;
            }
         }
         trackLengthTrueCosLongestGTFM = ana_tree_tracks->Length(longestTrackIndexCosGTFM );
         trackPerpDistXBoundTrueCosLongestGTFM = min_x_dist;
         trackPerpDistYBoundTrueCosLongestGTFM = min_y_dist;
         trackPerpDistZBoundTrueCosLongestGTFM = min_z_dist;
         trackPerpDistToABoundTrueCosLongestGTFM = min_to_a_boundary_dist;
         trackPIDATrueCosLongestGTFM = ana_tree_tracks->PIDA(longestTrackIndexCosGTFM ,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM ));
         trackRangeTrueCosLongestGTFM = ana_tree_tracks->Range(longestTrackIndexCosGTFM ,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM ));
         trackKETrueCosLongestGTFM = ana_tree_tracks->KE(longestTrackIndexCosGTFM ,ana_tree_tracks->PIDBestPlane(longestTrackIndexCosGTFM ));
         trackPhiTrueCosLongestGTFM = ana_tree_tracks->Phi(longestTrackIndexCosGTFM );
         if(trackPhiTrueCosLongestGTFM < 0)
            trackPhiTrueCosLongestGTFM  = -trackPhiTrueCosLongestGTFM;
         trackThetaTrueCosLongestGTFM = ana_tree_tracks->Theta(longestTrackIndexCosGTFM );
         trackThetaXZTrueCosLongestGTFM = ana_tree_tracks->ThetaXZ(longestTrackIndexCosGTFM );
         trackThetaYZTrueCosLongestGTFM = ana_tree_tracks->ThetaYZ(longestTrackIndexCosGTFM );
         if(trackThetaYZTrueCosLongestGTFM < 0)
            trackThetaYZTrueCosLongestGTFM = -trackThetaYZTrueCosLongestGTFM;
         if(trackThetaYZTrueCosLongestGTFM > TMath::Pi()/2)
            trackThetaYZTrueCosLongestGTFM = -(trackThetaYZTrueCosLongestGTFM-TMath::Pi());
         trackNearestDistUntaggedTrueCosLongestToTaggedCosGTFM = shortestTrackDistance;
         trackNearestVtxDistTrueCosLongestGTFM = longestTrackMatchedVtxDistCosGTFM;
         weightTrueCosLongestGTFM = 1;
         tTrueCosLongestGTFM.Fill();
      }

















      // Loop over tracks
      for (short i= 0; i< ana_tree_tracks->NTracks(); i++){

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
                  
         trackLengthAll = ana_tree_tracks->Length(i);
         trackPerpDistXBoundAll = min_x_dist;
         trackPerpDistYBoundAll = min_y_dist;
         trackPerpDistZBoundAll = min_z_dist;
         trackPerpDistToABoundAll = min_to_a_boundary_dist;
         trackPIDAAll = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
         trackRangeAll = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
         trackKEAll = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
         trackPhiAll = ana_tree_tracks->Phi(i);
         if(trackPhiAll < 0)
            trackPhiAll = -trackPhiAll;
         trackThetaAll = ana_tree_tracks->Theta(i);
         trackThetaXZAll = ana_tree_tracks->ThetaXZ(i);
         trackThetaYZAll = ana_tree_tracks->ThetaYZ(i);
         if(trackThetaYZAll < 0)
            trackThetaYZAll = -trackThetaYZAll;
         if(trackThetaYZAll > TMath::Pi()/2)
            trackThetaYZAll = -(trackThetaYZAll-TMath::Pi());
         trackOriginAll = ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i));
         trackTaggedCosAllGT = 1;
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4){
            trackTaggedCosAllGT = 0;
         }
         trackTaggedCosAllGTFM = 1;
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4
              and ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            trackTaggedCosAllGTFM = 0;
         }

         weightAll=1;
         tAll.Fill();


         // Was the track a true neutrino?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
            if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                  && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                  && min_x_dist < 128){
               trackLengthTrueNu = ana_tree_tracks->Length(i);
               trackPerpDistXBoundTrueNu = min_x_dist;
               trackPerpDistYBoundTrueNu = min_y_dist;
               trackPerpDistZBoundTrueNu = min_z_dist;
               trackPerpDistToABoundTrueNu = min_to_a_boundary_dist;
               trackPIDATrueNu = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
               trackRangeTrueNu = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
               trackKETrueNu = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
               trackPhiTrueNu = ana_tree_tracks->Phi(i);
               if(trackPhiTrueNu < 0)
                  trackPhiTrueNu = -trackPhiTrueNu;
               trackThetaTrueNu = ana_tree_tracks->Theta(i);
               trackThetaXZTrueNu = ana_tree_tracks->ThetaXZ(i);
               trackThetaYZTrueNu = ana_tree_tracks->ThetaYZ(i);
               if(trackThetaYZTrueNu < 0)
                  trackThetaYZTrueNu = -trackThetaYZTrueNu;
               if(trackThetaYZTrueNu > TMath::Pi()/2)
                  trackThetaYZTrueNu = -(trackThetaYZTrueNu-TMath::Pi());
               tTrueNu.Fill();
            }
         }

         // Was the track a true cosmic?
         if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
            
            if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                  && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                  && min_x_dist < 128){
               trackLengthTrueCos = ana_tree_tracks->Length(i);
               trackPerpDistXBoundTrueCos = min_x_dist;
               trackPerpDistYBoundTrueCos = min_y_dist;
               trackPerpDistZBoundTrueCos = min_z_dist;
               trackPerpDistToABoundTrueCos = min_to_a_boundary_dist;
               trackPIDATrueCos = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
               trackRangeTrueCos = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
               trackKETrueCos = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
               trackPhiTrueCos = ana_tree_tracks->Phi(i);
               if(trackPhiTrueCos < 0)
                  trackPhiTrueCos = -trackPhiTrueCos;
               trackThetaTrueCos = ana_tree_tracks->Theta(i);
               trackThetaXZTrueCos = ana_tree_tracks->ThetaXZ(i);
               trackThetaYZTrueCos = ana_tree_tracks->ThetaYZ(i);
               if(trackThetaYZTrueCos < 0)
                  trackThetaYZTrueCos = -trackThetaYZTrueCos;
               if(trackThetaYZTrueCos > TMath::Pi()/2)
                  trackThetaYZTrueCos = -(trackThetaYZTrueCos-TMath::Pi());
               weightTrueCos=1;
               tTrueCos.Fill();
            }
         }
         







         // Does the track flunk the flash match cut?
         if(ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){

                  if(ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                     shortestTrackDistance = trackDistance;
                  }
               }


            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){

                  if(ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                     shortestTrackDistance = trackDistance;
                  }
               }

            }
         }

         // Does the track flunk the geometric tagger cut?
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4){
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){

               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueCosGT = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueCosGT = min_x_dist;
                  trackPerpDistYBoundTrueCosGT = min_y_dist;
                  trackPerpDistZBoundTrueCosGT = min_z_dist;
                  trackPerpDistToABoundTrueCosGT = min_to_a_boundary_dist;
                  trackPIDATrueCosGT = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueCosGT = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueCosGT = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueCosGT = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueCosGT < 0)
                     trackPhiTrueCosGT  = -trackPhiTrueCosGT ;
                  trackThetaTrueCosGT = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueCosGT = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueCosGT = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueCosGT < 0)
                     trackThetaYZTrueCosGT = -trackThetaYZTrueCosGT;
                  if(trackThetaYZTrueCosGT > TMath::Pi()/2)
                     trackThetaYZTrueCosGT = -(trackThetaYZTrueCosGT-TMath::Pi());
                  trackNearestDistUntaggedTrueCosToTaggedCosGT=shortestTrackDistance;
                  weightTrueCosGT=1;
                  tTrueCosGT.Fill();
               }


            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueNuGT = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueNuGT = min_x_dist;
                  trackPerpDistYBoundTrueNuGT = min_y_dist;
                  trackPerpDistZBoundTrueNuGT = min_z_dist;
                  trackPerpDistToABoundTrueNuGT = min_to_a_boundary_dist;
                  trackPIDATrueNuGT = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueNuGT = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueNuGT = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueNuGT = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueNuGT < 0)
                     trackPhiTrueNuGT  = -trackPhiTrueNuGT ;
                  trackThetaTrueNuGT = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueNuGT = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueNuGT = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueNuGT < 0)
                     trackThetaYZTrueNuGT = -trackThetaYZTrueNuGT;
                  if(trackThetaYZTrueNuGT > TMath::Pi()/2)
                     trackThetaYZTrueNuGT = -(trackThetaYZTrueNuGT-TMath::Pi());
                  trackNearestDistUntaggedTrueNuToTaggedCosGT=shortestTrackDistance;
                  tTrueNuGT.Fill();
               }
            }
         }

         // Does the track flunk the geometric tagger and flash match cuts?
         if(ana_tree_tracks->CosmicScoreTagger(i) <= 0.4
              and ana_tree_tracks->CosmicScoreFlashMatch(i) <= 0.5){
            // Was the track a true cosmic?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 2){
               
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                        or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueCosGTFM = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueCosGTFM = min_x_dist;
                  trackPerpDistYBoundTrueCosGTFM = min_y_dist;
                  trackPerpDistZBoundTrueCosGTFM = min_z_dist;
                  trackPerpDistToABoundTrueCosGTFM = min_to_a_boundary_dist;
                  trackPIDATrueCosGTFM = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueCosGTFM = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueCosGTFM = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueCosGTFM = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueCosGTFM < 0)
                     trackPhiTrueCosGTFM  = -trackPhiTrueCosGTFM ;
                  trackThetaTrueCosGTFM = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueCosGTFM = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueCosGTFM = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueCosGTFM < 0)
                     trackThetaYZTrueCosGTFM = -trackThetaYZTrueCosGTFM;
                  if(trackThetaYZTrueCosGTFM > TMath::Pi()/2)
                     trackThetaYZTrueCosGTFM = -(trackThetaYZTrueCosGTFM-TMath::Pi());
                  trackNearestDistUntaggedTrueCosToTaggedCosGTFM=shortestTrackDistance;
                  weightTrueCosGTFM=1;
                  tTrueCosGTFM.Fill();
               }


            }
            // Was the track a true neutrino?
            if(ana_tree_tracks->Origin(i,ana_tree_tracks->PIDBestPlane(i)) == 1){
               // get distance to closest tagged cosmic track 
               double shortestTrackDistance = 999999;
               for (short j=0; j< ana_tree_tracks->NTracks(); j++){
                  if(ana_tree_tracks->CosmicScoreTagger(j) > 0.4 
                        or ana_tree_tracks->CosmicScoreFlashMatch(j) > 0.5){
                     double trackDistance = ana_tree_algs->DistanceBetweenTracks(ana_tree_tracks,i,j);
                     if(trackDistance < shortestTrackDistance)
                        shortestTrackDistance = trackDistance;
                  }
               }

               if(ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i)) < 100
                     && ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i)) < 100000
                     && min_x_dist < 128){
                  trackLengthTrueNuGTFM = ana_tree_tracks->Length(i);
                  trackPerpDistXBoundTrueNuGTFM = min_x_dist;
                  trackPerpDistYBoundTrueNuGTFM = min_y_dist;
                  trackPerpDistZBoundTrueNuGTFM = min_z_dist;
                  trackPerpDistToABoundTrueNuGTFM = min_to_a_boundary_dist;
                  trackPIDATrueNuGTFM = ana_tree_tracks->PIDA(i,ana_tree_tracks->PIDBestPlane(i));
                  trackRangeTrueNuGTFM = ana_tree_tracks->Range(i,ana_tree_tracks->PIDBestPlane(i));
                  trackKETrueNuGTFM = ana_tree_tracks->KE(i,ana_tree_tracks->PIDBestPlane(i));
                  trackPhiTrueNuGTFM = ana_tree_tracks->Phi(i);
                  if(trackPhiTrueNuGTFM < 0)
                     trackPhiTrueNuGTFM  = -trackPhiTrueNuGTFM ;
                  trackThetaTrueNuGTFM = ana_tree_tracks->Theta(i);
                  trackThetaXZTrueNuGTFM = ana_tree_tracks->ThetaXZ(i);
                  trackThetaYZTrueNuGTFM = ana_tree_tracks->ThetaYZ(i);
                  if(trackThetaYZTrueNuGTFM < 0)
                     trackThetaYZTrueNuGTFM = -trackThetaYZTrueNuGTFM;
                  if(trackThetaYZTrueNuGTFM > TMath::Pi()/2)
                     trackThetaYZTrueNuGTFM = -(trackThetaYZTrueNuGTFM-TMath::Pi());
                  trackNearestDistUntaggedTrueNuToTaggedCosGTFM=shortestTrackDistance;
                  tTrueNuGTFM.Fill();
               }

            }
         }

      }

   }

   std::cout << "Done, processed " << nEvtsProcessed << " events." << std::endl;
   std::cout << "Of those events " << nEvtsFiredPMTTrigger << " fired the PMT trigger." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackNu  << " of the longest tracks in each event came from a neutrino." << std::endl;
   std::cout << "In those events, " << nEvtsLongestTrackCos  << " of the longest tracks in each event came from a cosmic." << std::endl;



   tAll.Write();
   tTrueNu.Write();
   tTrueCos.Write();
   tTrueNuGT.Write();
   tTrueCosGT.Write();
   tTrueNuGTFM.Write();
   tTrueCosGTFM.Write();
   tTrueNuLongestGTFM.Write();
   tTrueNuCCLongestGTFM.Write();
   tTrueNuNCLongestGTFM.Write();
   tTrueCosLongestGTFM.Write();

}






