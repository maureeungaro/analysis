#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

#include "Clas_event.C"
#include "definition.h"
#include <utilities.C>


#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

int main(int argc, char **argv)
{
 double W    , Q2;
 double phi  , theta;   // cm pi0 angles in CM
 double phi_e, theta_e; // lab electron angles 
 double pcm;
 double E = 5.7542;
  
 V4  k, P;
 V4 kf, Pf;
 
 k.t = k.z = E;
 P.t = MP;
 P.x = P.y = P.z = 0;
 
 V4 q, H, x, Pcm, xcm;
 
 int N = atoi(argv[1]);
 cout << " Number of events to process: " << N << endl;

 for(int j=0; j<N; j++)
 {
  kf.t  = kf.x  = kf.y  = kf.z  = 0;
  Pf.t  = Pf.x  = Pf.y  = Pf.z  = 0; 
  Pcm.t = Pcm.x = Pcm.y = Pcm.z = 0;   
  xcm.t = xcm.x = xcm.y = xcm.z = 0;     
  
  W       = 1.1  + drand48()*0.3;
  Q2      = 1.8  + drand48()*5;
  phi     = drand48()*2*PI;
  theta   = drand48()*PI;
  phi_e   = drand48()*2*PI;
 
  q.t     = (W*W + Q2 - MP*MP)/(2*MP);
  kf.t    = k.t - q.t;
  theta_e = acos(1-Q2/(2*E*kf.t));
  
  kf.set(kf.t, theta_e, phi_e);

  pcm     = sqrt(pow( W*W - (MP+Mpi0)*(MP+Mpi0), 2)*pow( W*W - (MP-Mpi0)*(MP-Mpi0), 2)/2*W );
  Pcm.t   = sqrt(MP*MP     + pcm*pcm);
  xcm.t   = sqrt(Mpi0*Mpi0 + pcm*pcm);
  
  Pcm.set
  
  
 } 
 
 cout << " Done!" << endl;
}


















