
#ifndef AnaTreeVertex_h
#define AnaTreeVertex_h

constexpr int kMaxVertices = 500;

#include <TROOT.h>
#include <TChain.h>


class AnaTreeVertex {

   public:

      /// Constructor
      AnaTreeVertex(TTree *fChain,TString fVertexModule);
     
      // Vertex variables
      Float_t VertexX(short i){ return fVtxX[i];}
      Float_t VertexY(short i){ return fVtxY[i];}
      Float_t VertexZ(short i){ return fVtxZ[i];}
      Short_t NVertex() {return fNVertex;}

   private:
      
      Short_t fNVertex;
      Float_t fVtxX[kMaxVertices];
      Float_t fVtxY[kMaxVertices];
      Float_t fVtxZ[kMaxVertices];

};


#endif // #ifdef AnaTreeVertex_cxx
