#define AnaTreeVertex_cxx
#include "AnaTreeVertex.h"

AnaTreeVertex::AnaTreeVertex(TTree *fChain,TString fVertexModule) {
   fChain->SetBranchStatus("nvtx_"+fVertexModule,1);
   fChain->SetBranchStatus("vtxx_"+fVertexModule,1);
   fChain->SetBranchStatus("vtxy_"+fVertexModule,1);
   fChain->SetBranchStatus("vtxz_"+fVertexModule,1);
   
   fChain->SetBranchAddress("nvtx_"+fVertexModule,&fNVertex);
   fChain->SetBranchAddress("vtxx_"+fVertexModule,&fVtxX);
   fChain->SetBranchAddress("vtxy_"+fVertexModule,&fVtxY);
   fChain->SetBranchAddress("vtxz_"+fVertexModule,&fVtxZ);

}

