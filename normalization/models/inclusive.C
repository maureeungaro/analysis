#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cstddef>
using namespace std;


#include "TFile.h"
#include "TH1.h"
#include "TH2.h"



extern  "C"
{
 float elas_(    float&, float& );
 float elasrad_( float&, float&, float&, float& ); 
 float brasse_(float&, float&, float&);
 void input_(int&);
 float tkeppel_(float&, float&, float&);

struct params
{
 float mp, w[300], a[300], b[300] ,c[300];
 float R,delw,alpha,pi;
 int   nsteps;
}params_ ; 


}

// extern struct params
// {
//  float mp, w[300], a[300], b[300] ,c[300];
//  float R,delw,alpha,pi;
//  int   nsteps;
// }params_ ; 


main(int argc, char **argv)    
{

 TFile f("inclusive.root", "RECREATE");
 int unitb=99;

 float TGTL = 0.0023;      // radiation lenght  --  target = 5 cm
 float WRES = 20;          // W resolution set to 20 MeV
 float WW   = 1.028;       // upper limit of W

 float E = 5.754;     // incident  electron energy
 float theta_e[100];  // scattered electron angle
 float Ws[118];       // W values   1.11 - 1.7 -- 0.005
 float Qs[100];       // Q2 values  2.0  - 7.0 -- 0.05


 for(int i=0; i<100; i++) theta_e[i] = 10+i*0.5;
 for(int w=0; w<118; w++) Ws[w]      = 1.11 + 0.005*w;
 for(int q=0; q<100; q++) Qs[q]      = 2.0  + 0.05*q; 

 TH1F *el  = new TH1F("el",  "elastic cross section",          100, 10, 60); 
 TH1F *elr = new TH1F("elr", "elastic radiativecross section", 100, 10, 60); 

 for(int i=0; i<100; i++)
 {
//  cout <<  theta_e[i] << " " << elas_(E, theta_e[i]) << " " << elasrad_(E, theta_e[i], TGTL, WW) << endl;
  el->SetBinContent( i+1, elas_(E, theta_e[i]));
  elr->SetBinContent(i+1, elasrad_(E, theta_e[i], TGTL, WW));
 }


 input_(unitb);
 cout <<  params_.b[3] <<  " " << params_.R << endl;

 for(int w=0; w<118; w++)
 {
  cout << Ws[w] << " " << tkeppel_(E, Qs[2], Ws[w]) << " " <<  brasse_(E, Qs[2], Ws[w]) << endl;

 }





 el->Write();
 elr->Write();
 


 return 0;
}                        





  


 
