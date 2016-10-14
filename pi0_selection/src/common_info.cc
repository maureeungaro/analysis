// MU includes
#include "common_info.h"
#include "utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
chistos::chistos(string filename, int READ)
{
	const int STAGES = 5;
	string cut[STAGES]  = {"no_cut", "phi_cut", "th1_cut", "th2_cut", "all_cuts"};

	double NWBINS  = 18;
	double CTBINS  = 10;
	double dw = (2.0 - 1.1)/NWBINS;
	double dt = 0.2;
	
	// Default: filename is output file
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none") 
		{
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
		
		for(int c=0; c<STAGES; c++)
		{
			W[c] = new TH1F(Form("W_%s",   cut[c].c_str()),
											Form("W_%s",   cut[c].c_str()), 200, 0.8, 2.1);
			Q2[c] = new TH1F(Form("Q2_%s", cut[c].c_str()),
											 Form("Q2_%s", cut[c].c_str()), 200, 1.0, 7.0);
			epXmm2[c] = new TH1F(Form("epXmm2_%s", cut[c].c_str()),
													 Form("epXmm2_%s", cut[c].c_str()), 400, -0.08, 0.8);
			Q2_W[c] = new TH2F(Form("Q2_W_%s",   cut[c].c_str()),
												 Form("Q2_W_%s",   cut[c].c_str()), 200, 0.8, 2.1, 200, 1.0, 7.0);
			epXmm2_W[c] = new TH2F(Form("epXmm2_W_%s",   cut[c].c_str()),
														 Form("epXmm2_W_%s",   cut[c].c_str()), 200, 0.8, 2.1, 200, -0.08, 0.1);
			for(int w=0; w<NWBINS; w++)
			{
				double W = 1.1 + dw*w + 0.5*dw;
				epXmm2s[c][w] = new TH1F(Form("epXmm2s_%s_w%3.2f", cut[c].c_str(), W),
												 Form("epXmm2s_%s_w%3.2f", cut[c].c_str(), W), 100, -0.08, 0.12);
				dth1[c][w]  = new TH1F(Form("dth1_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dth1_%s_w%3.2f", cut[c].c_str(), W),  100, -5.0-w/1.5, 15.0+w*1.5);
				dth2[c][w]  = new TH1F(Form("dth2_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dth2_%s_w%3.2f", cut[c].c_str(), W),  100, -3.0, 15.0+w*2);
				dphi[c][w]  = new TH1F(Form("dphi_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dphi_%s_w%3.2f", cut[c].c_str(), W),  100, 160.0-9*w, 200.0+9*w);
				dth1z[c][w] = new TH1F(Form("dth1z_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dth1z_%s_w%3.2f", cut[c].c_str(), W), 100, -2, 2);
				dth2z[c][w] = new TH1F(Form("dth2z_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dth2z_%s_w%3.2f", cut[c].c_str(), W), 100, -3, 5);
				dphiz[c][w] = new TH1F(Form("dphiz_%s_w%3.2f", cut[c].c_str(), W),
											  Form("dphiz_%s_w%3.2f", cut[c].c_str(), W), 100, 174, 186);
				dth1_epXmm2[c][w] = new TH2F(Form("dth1_epXmm2_%s_w%3.2f", cut[c].c_str(), W),
												     Form("dth1_epXmm2_%s_w%3.2f", cut[c].c_str(), W),    100, -0.05, 0.1,  100, -5.0-w/1.5, 15.0+w*1.5  );
				dth2_epXmm2[c][w] = new TH2F(Form("dth2_epXmm2_%s_w%3.2f", cut[c].c_str(), W),
													  Form("dth2_epXmm2_%s_w%3.2f", cut[c].c_str(), W),    100, -0.05, 0.1,  100, -3.0,  15.0+w*2    );
				dphi_epXmm2[c][w] = new TH2F(Form("dphi_epXmm2_%s_w%3.2f", cut[c].c_str(), W),
													  Form("dphi_epXmm2_%s_w%3.2f", cut[c].c_str(), W),    100, -0.05, 0.1,  100, 160.0-9*w, 200.0+9*w );
				dth1_epXmm2z[c][w] = new TH2F(Form("dth1_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),
														Form("dth1_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),  100, -0.05, 0.1,  100, -2, 2   );
				dth2_epXmm2z[c][w] = new TH2F(Form("dth2_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),
														Form("dth2_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),  100, -0.05, 0.1,  100, -3, 5   );
				dphi_epXmm2z[c][w] = new TH2F(Form("dphi_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),
														Form("dphi_epXmm2z_%s_w%3.2f", cut[c].c_str(), W),  100, -0.05, 0.1,  100, 160.0, 200.0 );
				
				for(int t=0; t<CTBINS; t++)
				{
					double ct = 0.1 + t*dt;
					ct_dth1_epXmm2[c][t][w] = new TH2F(Form("ct_dth1_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),
																  Form("ct_dth1_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),    100, -0.05, 0.1,  100, -5.0-w/1.5, 15.0+w*1.5  );
					ct_dth2_epXmm2[c][t][w] = new TH2F(Form("ct_dth2_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),
																  Form("ct_dth2_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),    100, -0.05, 0.1,  100, -3.0,  15.0+w*2    );
					ct_dphi_epXmm2[c][t][w] = new TH2F(Form("ct_dphi_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),
																  Form("ct_dphi_epXmm2_%s_ct%2.1f_w%3.2f", cut[c].c_str(), ct, W),    100, -0.05, 0.1,  100, 160.0-9*w, 200.0+9*w );
				}														
																			
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
			for(int c=0; c<STAGES; c++)
			{
				W[c]        = (TH1F*)f.Get(Form("W_%s",          cut[c].c_str()));
				Q2[c]       = (TH1F*)f.Get(Form("Q2_%s",         cut[c].c_str()));
				epXmm2[c]   = (TH1F*)f.Get(Form("epXmm2_%s",     cut[c].c_str()));
				Q2_W[c]     = (TH2F*)f.Get(Form("Q2_W_%s",     cut[c].c_str()));
				epXmm2_W[c] = (TH2F*)f.Get(Form("epXmm2_W_%s", cut[c].c_str()));
				W[c]->SetDirectory(0);
				Q2[c]->SetDirectory(0);
				epXmm2[c]->SetDirectory(0);
				Q2_W[c]->SetDirectory(0);
				epXmm2_W[c]->SetDirectory(0);
				for(int w=0; w<NWBINS; w++)
				{
					double W = 1.1 + dw*w + 0.5*dw;
					epXmm2s[c][w] = (TH1F*)f.Get(Form("epXmm2s_%s_w%3.2f", cut[c].c_str(), W));
					dth1[c][w]    = (TH1F*)f.Get(Form("dth1_%s_w%3.2f",    cut[c].c_str(), W));
					dth2[c][w]    = (TH1F*)f.Get(Form("dth2_%s_w%3.2f",    cut[c].c_str(), W));
					dphi[c][w]    = (TH1F*)f.Get(Form("dphi_%s_w%3.2f",    cut[c].c_str(), W));
					dth1z[c][w]   = (TH1F*)f.Get(Form("dth1z_%s_w%3.2f",   cut[c].c_str(), W));
					dth2z[c][w]   = (TH1F*)f.Get(Form("dth2z_%s_w%3.2f",   cut[c].c_str(), W));
					dphiz[c][w]   = (TH1F*)f.Get(Form("dphiz_%s_w%3.2f",   cut[c].c_str(), W));
					epXmm2s[c][w]->SetDirectory(0);
					dth1[c][w]->SetDirectory(0);
					dth2[c][w]->SetDirectory(0);
					dphi[c][w]->SetDirectory(0);
					dth1z[c][w]->SetDirectory(0);
					dth2z[c][w]->SetDirectory(0);
					dphiz[c][w]->SetDirectory(0);
					dth1_epXmm2[c][w]  = (TH2F*)f.Get(Form("dth1_epXmm2_%s_w%3.2f",  cut[c].c_str(), W));
					dth2_epXmm2[c][w]  = (TH2F*)f.Get(Form("dth2_epXmm2_%s_w%3.2f",  cut[c].c_str(), W));
					dphi_epXmm2[c][w]  = (TH2F*)f.Get(Form("dphi_epXmm2_%s_w%3.2f",  cut[c].c_str(), W));
					dth1_epXmm2z[c][w] = (TH2F*)f.Get(Form("dth1_epXmm2z_%s_w%3.2f", cut[c].c_str(), W));
					dth2_epXmm2z[c][w] = (TH2F*)f.Get(Form("dth2_epXmm2z_%s_w%3.2f", cut[c].c_str(), W));
					dphi_epXmm2z[c][w] = (TH2F*)f.Get(Form("dphi_epXmm2z_%s_w%3.2f", cut[c].c_str(), W));
					dth1_epXmm2[c][w]->SetDirectory(0);
					dth2_epXmm2[c][w]->SetDirectory(0);
					dphi_epXmm2[c][w]->SetDirectory(0);
					dth1_epXmm2z[c][w]->SetDirectory(0);
					dth2_epXmm2z[c][w]->SetDirectory(0);
					dphi_epXmm2z[c][w]->SetDirectory(0);

					dth1_epXmm2[c][w]->SetMaximum(dth1_epXmm2[c][w]->GetMaximum()/2);
					dth2_epXmm2[c][w]->SetMaximum(dth2_epXmm2[c][w]->GetMaximum()/2);
					dphi_epXmm2[c][w]->SetMaximum(dphi_epXmm2[c][w]->GetMaximum()/2);
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

// Reads Parameters and functions
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
	
	string line;
	string addinfo;
	
	while(getline( parfile, line))
	{
		istringstream cuts(line);
	
		while(!cuts.eof())
		{
			string al;
			cuts >> al;
			if(al == "PHI_LIMITS:")
			{
				cuts >> phiMin >> phiMax;
				addinfo  = "   > Phi limits: " + stringify(phiMin);
				addinfo  += ", ";
				addinfo  += stringify(phiMax);
				addinfo  += " degrees";
				addInfos.push_back(addinfo);
			}
			else if(al == "DTH1_LIMITS:")
			{
				cuts >> dth1Min >> dth1Max;
				addinfo  = "   > Dth1 limits: " + stringify(dth1Min);
				addinfo  += ", ";
				addinfo  += stringify(dth1Max);
				addinfo  += " degrees";
				addInfos.push_back(addinfo);
			}
			else if(al == "DTH2_LIMITS:")
			{
				cuts >> dth2_mean_a >> dth2_mean_b >> dth2_sigma;
				addinfo  = "   > Dth2 pars: mean = a+bW. a=" + stringify(dth2_mean_a);
				addinfo  += ", b=";
				addinfo  += stringify(dth2_mean_b);
				addinfo  += " Sigma = ";
				addinfo  += stringify(dth2_sigma);
				addInfos.push_back(addinfo);
			}
		}
	}
	
	for(unsigned int s=0; s<addInfos.size(); s++)
		cout << addInfos[s] << endl;
}

void cpars::write_vars(string filename)
{
	ofstream parfile(filename.c_str());
	cout << endl << " Opening output parameter file " << filename << endl;
	
	parfile << "PHI_LIMITS: ";
	parfile << phiMin << " " <<  phiMax ;
	parfile << "                # Phi Limits (degrees)" << endl;
	
	parfile << "DTH1_LIMITS: ";
	parfile << dth1Min << " " <<  dth1Max ;
	parfile << "            # DTH1 Limits (degrees)" << endl;
	
	parfile << "DTH2_LIMITS: ";
	parfile << dth2_mean_a << " " <<  dth2_mean_b << " " <<  dth2_sigma;
	parfile << "  # DTH2 Limits parameters: mean = a+bW" << endl;
	
}










