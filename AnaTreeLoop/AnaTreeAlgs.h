
#ifndef AnaTreeAlgs_h
#define AnaTreeAlgs_h

#include "AnaTreeTracks.h"

class AnaTreeAlgs{

   public:
      double DistanceBetweenTracks(AnaTreeTracks *tracks, short i, short j);
      bool IsFiducial(double x, double y, double z);
};

#endif // #ifdef AnaTreeAlgs_cxx

