#ifndef MOD_HISTOS_H
#define MOD_HISTOS_H

#include "bin.h"

// %%%%%%%%%%%%%
// ROOT includes
// %%%%%%%%%%%%%
#include "TFile.h"
#include "TH2.h"
#include "TF1.h"

class mod_histos
{
	public:
		 mod_histos(string mod);
	  ~mod_histos(){;}

	string  model;
	Color_t col;   // line color
	int     lsty;  // line style
	
	// unfortunately need to hardcode the dimensions here
	public:
		TH2D *pht_model[45][7];           // cross section as a function of cos(theta), phi
		TH1D *phi_model[45][7][10];       // cross section as a function of phi
		TH1D *the_model[45][7][24];       // cross section as a function of cos(theta)
		TH1D *pi0_cs_W_model[7][10][24];  // cross section as a function of W
		TH1D *pi0_sf_model[45][7][3];     // structure function [cos(theta)] 0 = L+T ; 1 = TT; 2 = LT
		TH1D *pi0_sf_W_model[7][10][3];   // structure function [W] 0 = L+T ; 1 = TT; 2 = LT
		TH1D *chi2s_ctr[7];               // reduced chi2 distribution for Cross section fits (for each Q2)
		
	public:
		void define_histos(string filename="");
		void write_histos(string);
		void slice_histos();

		void fill_WQ2_histos();
		void fill_WQ2_sfhistos();
		
		void fit_phis();
		TF1 *phifit;
};
#endif
