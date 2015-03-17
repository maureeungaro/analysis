// MU includes
#include "common_info.h"
#include "bin.h"


// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
reso_chistos::reso_chistos(string filename, int READ)
{

	// recreate histos
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none") 
		{
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}

		for(int s=0; s<7; s++)
		{
			mom[s] = new TH1D(Form("mom_s%d", s+1),
									Form("mom_s%d", s+1),
									200, 1, 5);
			phi[s] = new TH1D(Form("phi_s%d", s+1),
									Form("phi_s%d", s+1),
									200, 1, 5);
			the[s] = new TH1D(Form("the_s%d", s+1),
									Form("the_s%d", s+1),
									200, 1, 5);
		}
	}
	// Reading from Input file
	else
	{
		// loading gen/rec histos
		if(filename!= "none" && OACC==-1) 
		{
			TFile f(filename.c_str());
			cout << " Loading resolution histos from: " << filename << "...";
			for(int s=0; s<7; s++)
			{
				mom[s] = (TH1D*) f.Get(Form("mom_s%d", s+1));
				phi[s] = (TH1D*) f.Get(Form("phi_s%d", s+1));
				the[s] = (TH1D*) f.Get(Form("the_s%d", s+1));
			}			
			cout << " done. " << endl ;
		}
		
		else
		{
			cout << " No Input File selected. Exiting constructor..." << endl;
			return;
		}
	}
}

// writing out
void reso_chistos::write_and_close()
{
	if(output)
	{
		cout << endl << " Writing ROOT file...  "  << endl;
		output->Write();
		output->Close();
	}
}












