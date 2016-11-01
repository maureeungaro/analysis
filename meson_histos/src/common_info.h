#ifndef MESON_INFO_H
#define MESON_INFO_H

// %%%%%%%%%%%%%
// ROOT includes
// %%%%%%%%%%%%%
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <string>
#include <iostream>
using namespace std;

// Common Classes with ROOT analysis macro

class meson_chistos
{
	public:
		meson_chistos(string filename, int READ = 0);
		~meson_chistos(){;}
		
		TFile *output;
		
		TH2F *Q2_W[3], *W_epXmm2[3];   // 0 = all; 1 = pi0 ; 2 = eta

		// pi0 histos from W=1.11 : bin 0
		// eta histos from W=1.47 : bin 18
		unsigned int MEB; // Minimum Eta Bin
		
		TH2D *pi0[45][7][3];   // last index is number of bins
		TH2D *eta[45][7][3];
		
		TH1D *pi0_phi[45][7][10][3];
		TH1D *eta_phi[45][7][10][3];
		
		TH1D *pi0_the[45][7][96][3];
		TH1D *eta_the[45][7][96][3];
		
		void write_and_close();                         // Write out histos and close ROOT file
		void slice();                                   // calculate the acceptance and slice the histos in phi, theta
		double find_max_phi(int w, int q, int b, int which);   // calculate the maximum of the pio_phi array for all CT in a given W,Q2 bin
		double find_max_the(int w, int q, int b, int which);   // calculate the maximum of the pio_the array for all PH in a given W,Q2 bin
};
#endif



#ifndef UTILS_H
#define UTILS_H

#include <sstream>
inline string stringify(double x)
{
	ostringstream o;
	o << x;
	return o.str();
}

inline string stringify(int x)
{
	ostringstream o;
	o << x;
	return o.str();
}

#endif






