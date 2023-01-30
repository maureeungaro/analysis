// MU includes
#include "common_info.h"
#include "utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
chistos::chistos(string filename, int READ)
{
	// Default: filename is output file
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none") {
            // check if filename exists
            if( file_exists(filename) ) {
                cout << " File " << filename << " already exists. Exiting..." << endl;
                exit(1);
            }

            output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
	
		for(int s=0; s<7; s++) {
			dt_mom[s]   = new TH2F(Form("dt_momsect%d",        s+1), 
										  Form("DT vs P, sector %d",  s+1), 550, 0.0, 5.5, 600, -30.0, 30.0);
			dt_momz[s]  = new TH2F(Form("dt_mom_z_sect%d",     s+1), 
										  Form("DT vs P, sector %d",  s+1), 550, 0.0, 5.5, 600, -8.0, 8.0);
		}
		
		// utility histos
		//  1: all
		//  2: before (hits in SC)
		//  3: after
		//  4: recovered
		//  5: thrown away
		for(int s=0; s<7; s++) {
			monitor[s] = new TH1F(Form("monitor_sect%d", s+1), Form("Individual cuts pass rate, sector %d", s+1), 5, 0, 5);
        }

		string what[2] = {"before", "after"};
		for(int s=0; s<7; s++) {
            for (int w = 0; w < 2; w++) {
                beta_vs_mom[w][s] = new TH2F(Form("beta_vs_mom_%s_sect%d", what[w].c_str(), s + 1),
                                             Form("Beta versus momentum, %s, sector %d", what[w].c_str(), s + 1), 550,
                                             0.0, 5.5, 500, 0.0, 1.2);
                mass_vs_mom[w][s] = new TH2F(Form("mass_vs_mom_%s_sect%d", what[w].c_str(), s + 1),
                                             Form("Mass versus momentum, %s, sector %d", what[w].c_str(), s + 1), 550,
                                             0.0, 5.5, 500, -0.4, 2.3);
            }
        }
	} else {
        // Reading from Input file

        if(filename!= "none") {
			TFile f(filename.c_str());
			cout << " Loading histos from: " << filename << endl;
		
			for(int s=0; s<7; s++)
			{
				dt_mom[s]   = (TH2F*)f.Get(Form("dt_momsect%d",    s+1));
				dt_momz[s]  = (TH2F*)f.Get(Form("dt_mom_z_sect%d", s+1));
				dt_mom[s]->SetDirectory(0);
				dt_momz[s]->SetDirectory(0);
				
				monitor[s] = (TH1F*)f.Get(Form("monitor_sect%d", s+1));
				monitor[s]->SetDirectory(0);
			}
		
	
			string what[2] = {"before", "after"};
			for(int s=0; s<7; s++)
				for(int w=0; w<2; w++)
			{
				beta_vs_mom[w][s] = (TH2F*)f.Get(Form("beta_vs_mom_%s_sect%d", what[w].c_str(), s+1));
				mass_vs_mom[w][s] = (TH2F*)f.Get(Form("mass_vs_mom_%s_sect%d", what[w].c_str(), s+1));
				beta_vs_mom[w][s]->SetDirectory(0);
				mass_vs_mom[w][s]->SetDirectory(0);
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
	
	for(int s=0; s<6; s++) 
	{
		dt_mom_mean_a[s] = 0;
		dt_mom_mean_b[s] = 0;
		dt_mom_mean_c[s] = 0;
		dt_mom_mean_d[s] = 0;
		dt_mom_mean_e[s] = 0;
		dt_mom_mean_f[s] = 0;
		dt_mom_sigm_a[s] = 0;
		dt_mom_sigm_b[s] = 0;
		dt_mom_sigm_c[s] = 0;
		dt_mom_sigm_d[s] = 0;
		dt_mom_sigm_e[s] = 0;
		dt_mom_sigm_f[s] = 0;
	}
	
	
	while(getline( parfile, line))
	{
		istringstream cuts(line);
	
		while(!cuts.eof())
		{
			string al;
			cuts >> al;
			if(al == "DTMA:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_a[s];
			}
			else if(al == "DTMB:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_b[s];
			}
			else if(al == "DTMC:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_c[s];
			}
			else if(al == "DTMD:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_d[s];
			}
			else if(al == "DTME:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_e[s];
			}
			else if(al == "DTMF:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_mean_f[s];
			}
			else if(al == "DTSA:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_a[s];
			}
			else if(al == "DTSB:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_b[s];
			}
			else if(al == "DTSC:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_c[s];
			}
			else if(al == "DTSD:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_d[s];
			}
			else if(al == "DTSE:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_e[s];
			}
			else if(al == "DTSF:")
			{
				for(int s=0; s<6; s++) cuts >> dt_mom_sigm_f[s];
			}
			else if(al == "DTNS:")
			{
				cuts >> NSIGMAS[0] >> NSIGMAS[1];
			}
		
		}
	}
	addInfos.push_back(" > Delta T MEAN pars: ");
	for(int s=0; s<6; s++)
	{
		addinfo  = "   > S" + stringify(s+1); 
		addinfo += "  a: "  + stringify(dt_mom_mean_a[s]);
		addinfo += "  b: "  + stringify(dt_mom_mean_b[s]);
		addinfo += "  c: "  + stringify(dt_mom_mean_c[s]);
		addinfo += "  d: "  + stringify(dt_mom_mean_d[s]);
		addinfo += "  e: "  + stringify(dt_mom_mean_e[s]);
		addinfo += "  f: "  + stringify(dt_mom_mean_f[s]);
		addInfos.push_back(addinfo);
	}
	addInfos.push_back(" > Delta T SIGMA pars: ");
	for(int s=0; s<6; s++)
	{
		addinfo  = "   > S" + stringify(s+1); 
		addinfo += "  a: "  + stringify(dt_mom_sigm_a[s]);
		addinfo += "  b: "  + stringify(dt_mom_sigm_b[s]);
		addinfo += "  c: "  + stringify(dt_mom_sigm_c[s]);
		addinfo += "  d: "  + stringify(dt_mom_sigm_d[s]);
		addinfo += "  e: "  + stringify(dt_mom_sigm_e[s]);
		addinfo += "  f: "  + stringify(dt_mom_sigm_f[s]);
		addInfos.push_back(addinfo);
	}
	
	addInfos.push_back(" > Number of Sigmas for upper Delta T Curve: " + stringify(NSIGMAS[0]));
	addInfos.push_back(" > Number of Sigmas for lower Delta T Curve: " + stringify(NSIGMAS[1]));
		
	for(unsigned int si=0; si<addInfos.size(); si++)
		cout << addInfos[si] << endl;
	
}

void cpars::write_vars(string filename)
{
	// NOTE: for gsim, can write just one sector.
	
	ofstream parfile(filename.c_str());
	cout << endl << " Opening output parameter file " << filename << endl;
	
	parfile << "DTMA: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_a[s] << " ";}
	parfile << "  # Delta T mean A: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTMB: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_b[s] << " ";}
	parfile << "  # Delta T mean B: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTMC: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_c[s] << " ";}
	parfile << "  # Delta T mean C: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTMD: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_d[s] << " ";}
	parfile << "  # Delta T mean D: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTME: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_e[s] << " ";}
	parfile << "  # Delta T mean E: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTMF: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_mean_f[s] << " ";}
	parfile << "  # Delta T mean F: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSA: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_a[s] << " ";}
	parfile << "  # Delta T sigma A: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSB: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_b[s] << " ";}
	parfile << "  # Delta T sigma B: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSC: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_c[s] << " ";}
	parfile << "  # Delta T sigma C: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSD: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_d[s] << " ";}
	parfile << "  # Delta T sigma D: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSE: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_e[s] << " ";}
	parfile << "  # Delta T sigma E: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTSF: ";
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << dt_mom_sigm_f[s] << " ";}
	parfile << "  # Delta T sigma F: a + bx + cx2 + dx3 + ex4 + fx5" << endl;

	parfile << "DTNS: ";
	parfile << NSIGMAS[0] << " " <<  NSIGMAS[1];
	parfile << "                                                                             # Delta T number of sigmas for upper/lower curve" << endl;
	
}



double cpars::Mean(double p, int sector)
{
	int s = sector - 1;
	
	return dt_mom_mean_a[s] +
			dt_mom_mean_b[s]*p +
			dt_mom_mean_c[s]*p*p +
			dt_mom_mean_d[s]*p*p*p +
			dt_mom_mean_e[s]*p*p*p*p +
			dt_mom_mean_f[s]*p*p*p*p*p;
}
double cpars::rMean(double *x, double *par)
{
	// par[0] is sector
	return Mean(x[0], (int) par[0]);
}

double cpars::Sigma(double p, int sector)
{
	int s = sector - 1;

	return dt_mom_sigm_a[s] +
			dt_mom_sigm_b[s]*p +
			dt_mom_sigm_c[s]*p*p +
			dt_mom_sigm_d[s]*p*p*p +
			dt_mom_sigm_e[s]*p*p*p*p +
			dt_mom_sigm_f[s]*p*p*p*p*p;
}
double cpars::rSigma(double *x, double *par)
{
	// par[0] is sector
	return Sigma(x[0], (int) par[0]);
}


double cpars::dt_mom_limit(double p, int sector, int nsigmas, int which)
{
	if(which >= 0) return Mean(p, sector) + nsigmas*Sigma(p, sector);
	else           return Mean(p, sector) - nsigmas*Sigma(p, sector);
	return 0;
}

double cpars::rdt_mom_limit(double *x, double *par)
{
	// par[0] is sector
	// par[1] is # of sigmas
	// par[2] is which limit (upper or lower)
	return  dt_mom_limit(x[0], (int) par[0], par[1], par[2]);
}






















