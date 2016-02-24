#define AnaTreeClusters_cxx
#include "AnaTreeClusters.h"

AnaTreeClusters::AnaTreeClusters(TTree *fChain) {

   fChain->SetBranchStatus("nclusters",1);
   fChain->SetBranchStatus("cluster_NHits",1);
   fChain->SetBranchStatus("cluster_StartWire",1);
   fChain->SetBranchStatus("cluster_EndWire",1);
   fChain->SetBranchStatus("cluster_StartTick",1);
   fChain->SetBranchStatus("cluster_EndTick",1);
   fChain->SetBranchStatus("clusterView",1);
   
   fChain->SetBranchAddress("nclusters",&fNClusters);
   fChain->SetBranchAddress("cluster_NHits",&fNClusterHits);
   fChain->SetBranchAddress("cluster_StartWire",&fStartWire);
   fChain->SetBranchAddress("cluster_EndWire",&fEndWire);
   fChain->SetBranchAddress("cluster_StartTick",&fStartTick);
   fChain->SetBranchAddress("cluster_EndTick",&fEndTick);
   fChain->SetBranchAddress("clusterView",&fClusterView);
   
}


