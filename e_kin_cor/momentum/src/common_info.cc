// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "common_info.h"
#include "utilities.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <fstream>
#include <cstdlib>

// %%%%%%%%%%
// Histograms
// %%%%%%%%%%
chistos::chistos(string filename, int READ)
{
	string what[4] = {"W", "eP_mm_inpi0", "epip_mm", "eP_mm_ineta"};
	string corr[2] = {"no_corr", "corrected"};
	
	// Default: filename is output file
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none") 
		{
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
		
		double hlims[4][2];
		hlims[0][0] = 0.8;    // W
		hlims[0][1] = 1.2;
		hlims[1][0] = -0.02;  // mm eP
		hlims[1][1] =  0.05;
		hlims[2][0] = 0.8;    // mm epip
		hlims[2][1] = 1.2;
		hlims[3][0] = 0.2;    // mm eP - eta
		hlims[3][1] = 0.5;

		for(int s=0; s<7; s++)
			for(int w=0; w<4; w++)
			{
				for(int c=0; c<2; c++)
				{
					hH[s][c][w] = new TH1F(Form("s%d_%s_%s", s+1, corr[c].c_str(), what[w].c_str()),
																 Form("s%d_%s_%s", s+1, corr[c].c_str(), what[w].c_str()),
																 200, hlims[w][0], hlims[w][1]);
					
					hHt[s][c][w] = new TH2F(Form("s%d_%s_%s_vs_theta", s+1, corr[c].c_str(), what[w].c_str()),
																	Form("s%d_%s_%s_vs_theta", s+1, corr[c].c_str(), what[w].c_str()),
																	 200,  14, 46,  200, hlims[w][0], hlims[w][1]);
																										 
					hHp[s][c][w] = new TH2F(Form("s%d_%s_%s_vs_phi", s+1, corr[c].c_str(), what[w].c_str()),
																	Form("s%d_%s_%s_vs_phi", s+1, corr[c].c_str(), what[w].c_str()),
																	192, -24, 24, 200, hlims[w][0], hlims[w][1]);
				}
			}
			
	}
	// Reading from Input file
	else
	{
		if(filename!= "none") 
		{
			TFile f(filename.c_str());
			cout << " Loading histos from: " << filename << endl;
			for(int s=0; s<7; s++)
				for(int w=0; w<4; w++)
				{
					for(int c=0; c<2; c++)
					{
						hH[s][c][w]  = (TH1F*) f.Get(Form("s%d_%s_%s",          s+1, corr[c].c_str(), what[w].c_str()));
						hHt[s][c][w] = (TH2F*) f.Get(Form("s%d_%s_%s_vs_theta", s+1, corr[c].c_str(), what[w].c_str()));
						hHp[s][c][w] = (TH2F*) f.Get(Form("s%d_%s_%s_vs_phi",   s+1, corr[c].c_str(), what[w].c_str()));
						hH[s][c][w]->SetDirectory(0);
						hHt[s][c][w]->SetDirectory(0);
						hHp[s][c][w]->SetDirectory(0);
					}
				}
				
			f.Close();
		}
		else
		{	
			cout << " No Input File selected. Exiting constructor..." << endl;
			return;
		}
	}
}

void chistos::write_and_close()
{
	if(output)
	{
		cout << endl << " Writing ROOT file...  " << endl;
		output->Write();
		output->Close();
	}
}

// %%%%%%%%%%%%%%%%%%%%%%%%
// Reads Parameters and functions
// %%%%%%%%%%%%%%%%%%%%%%%%
cpars::cpars(string filename)
{
	ifstream parfile(filename.c_str(), ios::in);
	cout << endl << " Opening parameter file " << filename << endl;
	if(!parfile)
	{
		cout << " File " <<  filename << " could not be opened. " << endl;
		cout << " Specify parameters file with -PARS_FILE=filename. Exiting. " << endl;
		exit(0);
	}
	
	for(int s=0; s<6; s++)
		for(int P=0; P<4; P++)
			for(int p=0; p<10; p++) parfile >>  par_par_phi[s][P][p];

	addInfos.push_back("Original e1-6 Momentum Correction");
	for(unsigned int s=0; s<addInfos.size(); s++)
		cout << addInfos[s] << endl;
}

void cpars::write_vars(string filename)
{
}










