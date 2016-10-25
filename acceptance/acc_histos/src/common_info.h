#ifndef ACC_INFO_H
#define ACC_INFO_H
 
// ROOT includes
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

// Common Classes with ROOT analysis macro

class acc_chistos
{
	public:
		// READ    =  0 will create the histos
		// READ    =  1 will read the histos
		// OnlyAcc = -1 will read all bins acceptance histos
		// OACC    >  0 will just read the acceptance histos from a particular binning
		acc_chistos(string filename, int READ=0, int OACC=-1);
	 ~acc_chistos(){;}
		
		TFile *output;

		// W, Q2, 3 binnings in phi*
		TH2D *pi0_gen[45][7][3];
		TH2D *pi0_rec[45][7][3];

		// histos below are calculated by slicing and dividing
		TH2D *pi0_acc[45][7][3];
		TH1D *pi0_phi[45][7][10][3][3];  //  0 = generated, 1 = reconstructed, 2 = acceptance

		
		void write_and_close();                 // Write out histos and close ROOT file
		void calc_acc();                        // calculate the acceptance
		void slice(int OACC=-1);                // slice the histos in phi, theta and style them
		void style(int OACC=-1);                // slice the histos in phi, theta and style them
		
		double find_max_phi(int w, int q, int b, int which);    // calculate the maximum of the phi array for all CT in a given W,Q2 bin
		double find_max_the(int w, int q, int b, int which);    // calculate the maximum of the the array for all PH in a given W,Q2 bin
};
#endif








