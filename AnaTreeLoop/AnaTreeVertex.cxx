#define AnaTreeVertex_cxx
#include "AnaTreeVertex.h"

AnaTreeVertex::AnaTreeVertex(TTree *fChain,TString fVertexModule) {
   
   fChain->SetBranchAddress("nvtx_"+fVertexModule,&fNVertex);
   fChain->SetBranchAddress("vtxx_"+fVertexModule,&fVtxX);
   fChain->SetBranchAddress("vtxy_"+fVertexModule,&fVtxY);
   fChain->SetBranchAddress("vtxz_"+fVertexModule,&fVtxZ);

}

