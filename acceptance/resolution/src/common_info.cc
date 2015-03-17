// MU includes
#include "common_info.h"
#include "bin.h"


// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
reso_chistos::reso_chistos(string filename, int READ)
{

	string part[2] = {"ele", "pro"};
	
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
			for(int p=0; p<2; p++)
			{
				mom[s][p] = new TH1D(Form("mom_s%d_%s", s+1, part[p].c_str()),
											Form("mom_s%d_%s", s+1, part[p].c_str()),
											200, -100, 100);
				phi[s][p] = new TH1D(Form("phi_s%d_%s", s+1, part[p].c_str()),
											Form("phi_s%d_%s", s+1, part[p].c_str()),
											200, -2, 2);
				the[s][p] = new TH1D(Form("the_s%d_%s", s+1, part[p].c_str()),
											Form("the_s%d_%s", s+1, part[p].c_str()),
											200, -0.4, 0.4);

				double minPhi = -30;
				double maxPhi = 30;
				if(s==6)
				{
					minPhi = 0;
					maxPhi = 360;
				}
			
				momPhi[s][p] = new TH2D(Form("momPhi_s%d_%s", s+1, part[p].c_str()),
											   Form("momPhi_s%d_%s", s+1, part[p].c_str()),
											   200, minPhi, maxPhi, 200, -100, 100);
				
				thePhi[s][p] = new TH2D(Form("thePhi_s%d_%s", s+1, part[p].c_str()),
											   Form("thePhi_s%d_%s", s+1, part[p].c_str()),
											   200, minPhi, maxPhi,  200, -0.4, 0.4);
				phiPhi[s][p] = new TH2D(Form("phiPhi_s%d_%s", s+1, part[p].c_str()),
												Form("phiPhi_s%d_%s", s+1, part[p].c_str()),
												200, minPhi, maxPhi,  200, -2, 2);

			
			}
	}
	// Reading from Input file
	else
	{
		// loading gen/rec histos
		if(filename!= "none") 
		{
			TFile f(filename.c_str());
			cout << " Loading resolution histos from: " << filename << "...";
			for(int s=0; s<7; s++)
				for(int p=0; p<2; p++)
				{
					mom[s][p] = (TH1D*) f.Get(Form("mom_s%d_%s", s+1, part[p].c_str()));
					phi[s][p] = (TH1D*) f.Get(Form("phi_s%d_%s", s+1, part[p].c_str()));
					the[s][p] = (TH1D*) f.Get(Form("the_s%d_%s", s+1, part[p].c_str()));
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












