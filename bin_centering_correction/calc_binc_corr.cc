#include "bin.h"
#include "binc_histos.h"

// This calculates the binciative correction as average of the models
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
	
	binc_histos BH("systematic");
	BH.define_histos();

	const int NMODELS = 6;
	string model[NMODELS] = {"dmt2001", "maid2002", "maid2003", "maid2003woroper", "maid2007", "said2008"};
	
	binc_histos BH_models[NMODELS];

	for(int m=0; m<NMODELS; m++)
		BH_models[m] = binc_histos(model[m]);

	for(int m=0; m<NMODELS; m++)
		BH_models[m].init_histos(Form("/arena1/analysis_data/bin_correction/%s_binc_cor.root", model[m].c_str()));

	// calculating the binciative correction and systematic error
	cout << " Calculating bin correction and systematic error from the models: " << endl << endl;
	for(int m=0; m<NMODELS; m++)
		cout << "    > " <<  model[m] << endl;
	cout << endl;
	
	double mean, sigma;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(unsigned int c=0; c<Bin.CTBIN; c++)
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					mean = sigma = 0;
					for(int m=0; m<NMODELS; m++)
						mean  = mean  + BH_models[m].pht_binc_cor[w][q]->GetBinContent(c+1, p+1);
					mean = mean / NMODELS;

					for(int m=0; m<NMODELS; m++)
						sigma = sigma + pow(BH_models[m].pht_binc_cor[w][q]->GetBinContent(c+1, p+1) - mean, 2);

					sigma = sqrt(sigma/NMODELS);
					
					BH.pht_binc_cor[w][q]->SetBinContent(c+1, p+1, mean);
					BH.pht_binc_cor[w][q]->SetBinError(  c+1, p+1, sigma);
				}
				
 	BH.write_histos("/arena1/analysis_data/bin_correction.root");
	cout << " done." << endl << endl;
	
}











