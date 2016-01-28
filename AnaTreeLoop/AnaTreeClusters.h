
#ifndef AnaTreeClusters_h
#define AnaTreeClusters_h

#include <root/TROOT.h>
#include <root/TChain.h>

constexpr int kMaxClusters = 500;

class AnaTreeClusters {

   public:

      /// Constructor
      AnaTreeClusters(TTree *fChain);

      Short_t NClusters() {return fNClusters;}

      // Cluster variables
      Short_t NClusterHits(short i){return fNClusterHits[i];}
      Short_t StartWire(short i){return fStartWire[i];}
      Short_t EndWire(short i){return fEndWire[i];}
      Short_t StartTick(short i){return fStartTick[i];}
      Short_t EndTick(short i){return fEndTick[i];}
      Short_t ClusterView(short i){return fClusterView[i];}

   private:

      Short_t fNClusters;
      Short_t fNClusterHits[kMaxClusters];
      Short_t fStartWire[kMaxClusters];
      Short_t fEndWire[kMaxClusters];
      Short_t fStartTick[kMaxClusters];
      Short_t fEndTick[kMaxClusters];
      Short_t fClusterView[kMaxClusters];

};


#endif // #ifdef AnaTreeClusters_cxx
