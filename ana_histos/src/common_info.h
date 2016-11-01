#ifndef ANA_INFO_H
#define ANA_INFO_H

// ROOT includes
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

// Common Classes with ROOT analysis macro

class ana_chistos
{
	public:
		 ana_chistos(TH2D *pi0[45][7][3]);
		 ana_chistos(string, int bin=2);
		~ana_chistos(){;}
		
		TFile *output;
		
		double min_acceptance; // minimum acceptance allowed on cross section
		                       // if acceptance is lower, bin is set to zero, and error set to 10M

		TH2D *pi0_l1[45][7][3]; // yields - 3 choices of binning
		TH2D *pi0_l2[45][7][3]; // yields divided by acceptance - 3 choices of binning
		TH2D *pi0_l3[45][7];    // l2 divided by rad. correction
		TH2D *pi0_cs[45][7];    // divided by bin correction
		
		TH1D *pi0_l2_phi[45][7][10][3];  // yields divided by acceptance - 3 choices of binning		

		TH1D *pi0_cs_phi[45][7][10];
		TH1D *pi0_cs_the[45][7][24];
		TH1D *pi0_cs_W[7][10][24];

		double epst[45][7];       // Transverse polarization of virtual photon
		double epsl[45][7];       // Longitudinal polarization of virtual photon


		// structure function histos - as a function of cos(theta)
		TH1D *pi0_sf[45][7][3];           // 0 = L+T ; 1 = TT; 2 = LT
		
		// structure function histos - as a function of W
		TH1D *pi0_sf_W[7][10][3];        

		// multipoles as a function of W
		TH1D *pi0_ml[7];

		void write(string);                             // Write out histos
		void slice_and_style(int also = 0);             // slice the histos in phi, theta and setting styles
		double find_max_phi(int w, int q, int which);   // calculate the maximum of the pio_phi array for all CT in a given W,Q2 bin
		double find_max_the(int w, int q, int which);   // calculate the maximum of the pio_the array for all PH in a given W,Q2 bin

		void divide_by_acc_cor(TH2D *pi0[45][7][3]);    // build the 3 version of corrected yields
		void divide_by_rad_cor(TH2D *pi0[45][7], int);  // divide by the chosen version of corrected yields
		void multiply_by_bin_cor(TH2D *pi0[45][7]);

		void quality_check(TH2D *pi0[45][7][3]);
		
		void normalize();
		void fill_WQ2_histos();

		void fill_WQ2_sfhistos();
		
		// fitting variables
		void fit_phis();
		TH1D *chi2s_ctr[7];    // reduced chi2 distribution for Cross to Response fits

		// rebin 2 bins according to acceptances
		double value_rebin( double data1, double data2, double acc1, double acc2);   
		double error_rebin(double data1, double data2, double edata1, double edata2, double acc1, double acc2, double eacc1, double eacc2);

		// sum 2 bins according to acceptances
		double value_srebin(double  data1, double  data2);                            
		double error_srebin(double edata1, double edata2);
		
		double error_quotient(double nomi, double enomi, double deno, double edeno);
		
		// Write tables
		void write_sf_table();
		
		
		// ROOT functions
		TF1 *phifit;
		
};
#endif













