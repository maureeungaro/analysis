// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "CLAS_Event.h"
#include "definitions.h"
#include "generator.h"


#include <cstdlib>
#include <iostream>
using namespace std;

pi0_generator::pi0_generator(bins Bin, double E)
{
	WMMIN = Bin.wm_min[0];
	WMMAX = Bin.wm_max.back();
	BeamE = E;

	cout << " Beam Energy: " << BeamE << endl;
	cout << " W min: " << WMMIN << " W max: " << WMMAX << endl;

}



void pi0_generator::generate_event()
{
	V4 ki(0, 0, BeamE, BeamE);
	V4 kf, Pf, pi0f, Pfcm, pi0fcm, q, H;
	
	// generating variables
	WM      = WMMIN  + drand48()*(WMMAX - WMMIN);
	Q2      = Q2MIN  + drand48()*(Q2MAX - Q2MIN);
	PhiCM   = drand48()*360.0*degree;
	ThetaCM = drand48()*180.0*degree;
	PhiEL   = drand48()*360.0*degree;

   // setting inclusive 4-momenta
	q.t     = (WM*WM + Q2 - proton_mass/GeV*proton_mass/GeV)/(2*proton_mass/GeV);
	kf.t    = BeamE - q.t;
	ThetaEL = acos(1-Q2/(2*BeamE*kf.t));
	
	kf.set(kf.t, ThetaEL, PhiEL);
	q       = ki - kf;
	H       = q + P;
	
   // setting exclusive 4-momenta in the CM
	double pcm  = sqrt( ( WM*WM - (proton_mass/GeV + pi0_mass/GeV )*(proton_mass/GeV + pi0_mass/GeV ) ) *
				           ( WM*WM - (proton_mass/GeV - pi0_mass/GeV )*(proton_mass/GeV - pi0_mass/GeV ) ) ) / (2*WM);
	Pfcm.t   = sqrt(proton_mass/GeV *proton_mass/GeV + pcm*pcm);
	pi0fcm.t = sqrt(   pi0_mass/GeV *   pi0_mass/GeV + pcm*pcm);
  
	Pfcm.set  (-pcm, ThetaCM, PhiCM);
	pi0fcm.set( pcm, ThetaCM, PhiCM);
	
   // setting lab coordinates
	Pf   = res_to_lab(H, Pcm);
	pi0f = res_to_lab(H, pi0fcm);


   // Assigning class 4 vectors
	e     = kf;
	P     = Pf;
	pi0   = pi0f;
	Pcm   = Pfcm;
	pi0cm = pi0fcm;
	
	return;
}

















