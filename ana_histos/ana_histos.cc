// C++ includes
#include <fstream>
using namespace std;

// histos includes
#include "common_info.h"
#include "meson_histos/src/common_info.h"
#include "meson_histos/src/common_info.cc"
#include "acceptance/acc_histos/src/common_info.h"
#include "acceptance/acc_histos/src/common_info.cc"
#include "radCorr/models/rad_histos.h"
#include "radCorr/models/rad_histos.cc"
#include "bin_centering_correction/binc_histos.h"
#include "bin_centering_correction/binc_histos.cc"
#include "models/cross_sections_tables/create_histos/mod_histos.h"
#include "models/cross_sections_tables/create_histos/mod_histos.cc"


// C++ includes
#include <iostream>
using namespace std;

// ./ana_histos

int main(int argc, char **argv)
{
	// output filename
	string filename = "ana_histos.root";

	// yields
	meson_chistos *MH = new meson_chistos("/opt/root/analysis_data/meson_histos.root", 1);

	// acceptance correction
	acc_chistos   *AH = new acc_chistos(  "/opt/root/analysis_data/acc.root", 1);
	AH->calc_acc();
	
	// radiative correction
	rad_histos    *RH = new rad_histos();
	RH->init_histos("/opt/root/analysis_data/radiative_correction.root");

	// bin correction
	binc_histos    *BH = new binc_histos("systematics");
	BH->init_histos("/opt/root/analysis_data/bin_correction.root");
	
	// performing the analysis
	ana_chistos *ANA_H = new ana_chistos(MH->pi0);
	ANA_H->divide_by_acc_cor(AH->pi0_acc);
	ANA_H->divide_by_rad_cor(RH->pht_rad_cor, 2);
	ANA_H->multiply_by_bin_cor(BH->pht_binc_cor);
	ANA_H->quality_check(AH->pi0_acc);
	ANA_H->normalize();
	
	// slices, style
	ANA_H->slice_and_style(1);
	ANA_H->fit_phis();
	
	ANA_H->write(filename);

	delete MH;
	delete AH;
	delete RH;
	
	cout << endl;
	return 1;
}














