#define AnaTreeClusters_cxx
#include "AnaTreeClusters.h"

AnaTreeClusters::AnaTreeClusters(TTree *fChain) {
   fChain->SetBranchAddress("nclusters",&fNClusters);
   fChain->SetBranchAddress("cluster_NHits",&fNClusterHits);
   fChain->SetBranchAddress("cluster_StartWire",&fStartWire);
   fChain->SetBranchAddress("cluster_EndWire",&fEndWire);
   fChain->SetBranchAddress("cluster_StartTick",&fStartTick);
   fChain->SetBranchAddress("cluster_EndTick",&fEndTick);
   fChain->SetBranchAddress("clusterView",&fClusterView);
   
}


