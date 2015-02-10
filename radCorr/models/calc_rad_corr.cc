#include "bin.h"
#include "rad_histos.h"

// This calculates the radiative correction as average of the models
// The error is set to be the RMS.
// The cut chose is 0.08 (hardcoded)
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char** argv)
{
	bins Bin;
	
	rad_histos RH;
	RH.define_histos();

	const int NMODELS = 5;
	string model[NMODELS] = {"dmt2001", "maid2002", "maid2003", "maid2003woroper", "maid2007"};
	
	rad_histos RH_models[NMODELS];

	for(int m=0; m<NMODELS; m++)
		RH_models[m].init_histos(Form("/arena1/analysis_data/exclurad_tables/%s_rad_cor_0.08.root", model[m].c_str()));

	// calculating the radiative correction and systematic error
	cout << " Calculating radiative correction and systematic error from the models: " << endl;
	for(int m=0; m<NMODELS; m++)
		cout << "     " <<  model[m] << endl;
	cout << endl;
	double mean, sigma;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(unsigned int c=0; c<Bin.CTBIN; c++)
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					mean = sigma = 0;
					for(int m=0; m<NMODELS; m++)
						mean  = mean  + RH_models[m].pht_rad_cor[w][q]->GetBinContent(c+1, p+1);
					mean = mean / NMODELS;

					for(int m=0; m<NMODELS; m++)
						sigma = sigma + pow(RH_models[m].pht_rad_cor[w][q]->GetBinContent(c+1, p+1) - mean, 2);

					sigma = sqrt(sigma/NMODELS);
					
					RH.pht_rad_cor[w][q]->SetBinContent(c+1, p+1, mean);
					RH.pht_rad_cor[w][q]->SetBinError(  c+1, p+1, sigma);
				}
				
 	RH.write_histos("/arena1/analysis_data/radiative_correction.root");
	cout << " done." << endl << endl;
	
}











