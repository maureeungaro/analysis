#ifndef RAD_HISTOS_H
#define RAD_HISTOS_H

#include "bin.h"

#include "TH2.h"

class rad_histos
{
	public:
		rad_histos(){;}
	  ~rad_histos(){;}

	// unfortunately need to hardcode the dimensions here
	public:
		TH2D *pht_rad_cor[45][7];
		TH1D *phi_rad_cor[45][7][10];
		TH1D *the_rad_cor[45][7][24];

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
