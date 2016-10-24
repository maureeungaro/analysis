#ifndef BINC_HISTOS_H
#define BINC_HISTOS_H

#include "bin.h"

#include "TH2.h"

class binc_histos
{
	public:
		binc_histos(){;}
		binc_histos(string mod);
	  ~binc_histos(){;}

	// unfortunately need to hardcode the dimensions here
	public:
		TH2D *pht_binc_cor[45][7];
		TH1D *phi_binc_cor[45][7][10];
		TH1D *the_binc_cor[45][7][24];

		string model;
		Color_t col;   // line color
		int     lsty;  // line style
		
	public:
		void define_histos();
		void write_histos(string);
		void init_histos(string);
		void slice_histos();
		void style_histos(int m=0);
		
		double find_max_phi(int w, int q);    // calculate the maximum of the phi array for all CT in a given W,Q2 bin
		double find_max_the(int w, int q);    // calculate the maximum of the the array for all PH in a given W,Q2 bin
};
#endif
