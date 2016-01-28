#define AnaTreeAlgs_cxx
#include "AnaTreeAlgs.h"
#include <TVector3.h>

#define SMALL_NUM 0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
/* #define norm(v)    sqrt(dot(v,v))  // norm = length of  vector */
/* #define d(u,v)     norm(u-v)        // distance = norm of difference */
/* #define abs(x)     ((x) >= 0 ? (x) : -(x))   //  absolute value */

bool AnaTreeAlgs::IsFiducial(double x, double y, double z){

   // Setup an array for the TPC boundary 
   double fTPC[6] = {0.,-116.5, 0.,256.35,116.5,1036.8};
   double border = 5.;

   if(x < (fTPC[3] - border)
         and x > (fTPC[0] + border)
         and y < (fTPC[4] - border)
         and y > (fTPC[1] + border)
         and z < (fTPC[5] - border)
         and z > (fTPC[2] + border)) return true;
   else return false;

}

double AnaTreeAlgs::DistanceBetweenTracks(AnaTreeTracks *tracks, short i, short j){

   TVector3 u = TVector3(tracks->EndX(i)-tracks->StartX(i),tracks->EndY(i)-tracks->StartY(i),tracks->EndZ(i)-tracks->StartZ(i));
   TVector3 v = TVector3(tracks->EndX(j)-tracks->StartX(j),tracks->EndY(j)-tracks->StartY(j),tracks->EndZ(j)-tracks->StartZ(j));
   TVector3 w = TVector3(tracks->StartX(i)-tracks->StartX(j),tracks->StartY(i)-tracks->StartY(j),tracks->StartZ(i)-tracks->StartZ(j));

   double a = u.Dot(u);
   double b = u.Dot(v);
   double c = v.Dot(v);
   double d = u.Dot(w);
   double e = v.Dot(w);
   double D = a*c - b*b;
   double sc, sN, sD = D;
   double tc, tN, tD = D;

    // compute the line parameters of the two closest points
    if (D < SMALL_NUM) { // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                 // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d +  b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (std::abs(sN) < SMALL_NUM ? 0.0 : sN / sD);
    tc = (std::abs(tN) < SMALL_NUM ? 0.0 : tN / tD);

    // get the difference of the two closest points
    TVector3  dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

    return dP.Mag();   // return the closest distance

}



