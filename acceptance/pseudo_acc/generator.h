#ifndef GENERATOR_H
#define GENERATOR_H

#include "bin.h"
#include "V4.h"

class pi0_generator
{
	public:
		 pi0_generator(bins, double);
		~pi0_generator(){;}


	double WMMIN, WMMAX;	
	double Q2MIN, Q2MAX;

	double BeamE;
	
   double WM, Q2, ThetaCM, PhiCM, PhiEL, ThetaEL;
	V4 e, P, pi0;
	V4 Pcm, pi0cm;
	
	public:
		void generate_event();
};

#endif


