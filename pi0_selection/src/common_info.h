#ifndef INFO_H
#define INFO_H
 
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

class chistos
{
	public:
		chistos(string filename, int READ = 0);
		~chistos(){;}
		
		TFile *output;

		// 4 cuts: phi, phi vs mm, dth1, dth2
		// 18 bins in W
		// 10 bins in CT
		
		TH1F *W[5],  *Q2[5], *epXmm2[5];
		TH2F *Q2_W[5], *epXmm2_W[5];
		
		TH1F *epXmm2s[5][18];
		TH1F *dth1[5][18],  *dth2[5][18],  *dphi[5][18];
		TH1F *dth1z[5][18], *dth2z[5][18], *dphiz[5][18];
		
		TH2F *dphi_epXmm2[5][18],  *dth1_epXmm2[5][18],  *dth2_epXmm2[5][18];
		TH2F *dphi_epXmm2z[5][18], *dth1_epXmm2z[5][18], *dth2_epXmm2z[5][18];
		
		TH2F *ct_dphi_epXmm2[5][10][18],  *ct_dth1_epXmm2[5][10][18],  *ct_dth2_epXmm2[5][10][18];
		
		
		void write_and_close();    // Write out histos and close ROOT file
};

// %%%%%%%%%%%%%%%%%%%%%%%%
// Parameters and functions
// %%%%%%%%%%%%%%%%%%%%%%%%
class cpars
{
	public:
		cpars(string filename);
		~cpars(){;}
		
		// additional infos in the file: cuts informations
		vector<string> addInfos;
	
		// all cuts are stored in the file specified in the constructor
		double phiMin, phiMax;
		double dth1Min, dth1Max;
		double dth2_mean_a, dth2_mean_b; 
		double dth2_sigma;
	
		void write_vars(string);
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






