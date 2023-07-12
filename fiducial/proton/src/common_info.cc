// MU includes
#include "common_info.h"
#include "utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>
#include <cmath>

// Histograms
chistos::chistos(string filename, int READ)
{
	string cut[4]    = {"no_cuts_on", "all_other_cuts_on", "all_other_cuts_neg", "all_cuts_on"};
	
	minp   = 0.2;
	maxp   = 5.0;

	dp = (maxp-minp)/NDIV_P;
	for(int m=0; m<NDIV_P; m++)
	{
		mom[m]  = minp + (m + 0.5)*dp;
		mom2[m] = minp + (m + 1.0)*dp;
	}
	
	double x_min[5]  = {-40,  -100,  -150, -200,  -240};
	double x_max[5]  = { 40,   100,   150,  200,   240};
	double y_min[5]  = { 10,    30,    60,  100,   100};
	double y_max[5]  = { 60,   180,   280,  420,   480};
	double limxf[5]  = { 3.5, 10.0,  15.0, 19.0,  19.0};
	double limyf1[5] = { 1.0,  2.2,   0.5, -1.5,  -1.5};
	double limyf2[5] = { 3.0, 10.0,  16.0, 28.0,  28.0};
	
	// Default: filename is output file
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
			for(int c=0; c<4; c++)
			{
				for(int p=0; p<5; p++)
				{
					x_y_tot[c][s][p] = new TH2F(Form("x_y_tot_plane%d_%s_sect%d",       p+1, cut[c].c_str(), s+1),
														 Form("x vs y, plane %d, %s, sector %d", p+1, cut[c].c_str(), s+1),
																400, x_min[p], x_max[p],
					  										400, y_min[p], y_max[p]);
				}
				
				
				for(int m=0; m<NDIV_P; m++)
				{
					phi_theta[c][s][m] = new TH2F(Form("phi_theta_mom%d_%s_sect%d",                 m+1, cut[c].c_str(), s+1),
															Form("phi vs theta, mom=%2.1f, %s, sector %d", mom[m], cut[c].c_str(), s+1),
																	280, 4.0, 72.0 - m*4.5, 240, -32+m/2.5, 32-m/2.5);
				
					for(int p=0; p<5; p++)
					{
						x_y[c][s][p][m] = new TH2F(Form("x_y_mom%d_plane%d_%s_sect%d",                   m+1, p+1, cut[c].c_str(), s+1),
															Form("x vs y, mom=%2.1f, plane %d, %s, sector %d", mom[m], p+1, cut[c].c_str(), s+1),
																	200, x_min[p]+m*limxf[p],  x_max[p]-m*limxf[p],
																	200, y_min[p]-m*limyf1[p], y_max[p]-m*limyf2[p]);
					}
				}
			}
			
			// 1: All events
			// 2: after vzcuts
			monitor[s]  = new TH1F(Form("monitor_sect%d", s+1), Form("Vtx monitor, sector %d", s+1), 2, 0, 2);
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
			{
				for(int c=0; c<4; c++)
				{
					for(int p=0; p<5; p++)
					{
						x_y_tot[c][s][p] = (TH2F*)f.Get(Form("x_y_tot_plane%d_%s_sect%d", p+1, cut[c].c_str(), s+1));
						x_y_tot[c][s][p]->SetDirectory(0);
						
						x_y_tot[c][s][p]->GetXaxis()->SetTitle("Y pos                 [cm]");
						x_y_tot[c][s][p]->GetYaxis()->SetTitle("X pos                 [cm]"); 
						x_y_tot[c][s][p]->GetXaxis()->SetTitleSize(0.040);
						x_y_tot[c][s][p]->GetYaxis()->SetTitleSize(0.040);
						x_y_tot[c][s][p]->GetXaxis()->SetTitleOffset(1.0);
						x_y_tot[c][s][p]->GetYaxis()->SetTitleOffset(1.2);
						x_y_tot[c][s][p]->GetXaxis()->SetLabelSize(0.030);
						x_y_tot[c][s][p]->GetYaxis()->SetLabelSize(0.030);
						x_y_tot[c][s][p]->GetZaxis()->SetLabelSize(0.030);
						x_y_tot[c][s][p]->GetXaxis()->SetNdivisions(8);
						x_y_tot[c][s][p]->GetYaxis()->SetNdivisions(8);
						x_y_tot[c][s][p]->GetZaxis()->SetNdivisions(8);
						x_y_tot[c][s][p]->SetMinimum(1);
					}
					for(int m=0; m<NDIV_P; m++)
					{
						phi_theta[c][s][m] = (TH2F*)f.Get(Form("phi_theta_mom%d_%s_sect%d", m+1, cut[c].c_str(), s+1));
						phi_theta[c][s][m]->SetDirectory(0);
						for(int p=0; p<5; p++)
						{
							x_y[c][s][p][m] = (TH2F*)f.Get(Form("x_y_mom%d_plane%d_%s_sect%d", m+1, p+1, cut[c].c_str(), s+1));
							x_y[c][s][p][m]->SetDirectory(0);
							
							x_y[c][s][p][m]->GetXaxis()->SetTitle("Y pos [cm]");
							x_y[c][s][p][m]->GetYaxis()->SetTitle("X pos [cm]");
							x_y[c][s][p][m]->GetXaxis()->SetTitleSize(0.08);
							x_y[c][s][p][m]->GetYaxis()->SetTitleSize(0.08);
							x_y[c][s][p][m]->GetXaxis()->SetTitleOffset(1.0);
							x_y[c][s][p][m]->GetYaxis()->SetTitleOffset(0.6);
							x_y[c][s][p][m]->GetXaxis()->SetLabelSize(0.07);
							x_y[c][s][p][m]->GetYaxis()->SetLabelSize(0.07);
							x_y[c][s][p][m]->GetZaxis()->SetLabelSize(0.07);
							x_y[c][s][p][m]->GetXaxis()->SetNdivisions(8);
							x_y[c][s][p][m]->GetYaxis()->SetNdivisions(8);
							x_y[c][s][p][m]->GetZaxis()->SetNdivisions(8);
							x_y[c][s][p][m]->SetMinimum(1);
						}
					}
				}
				monitor[s] = (TH1F*)f.Get(Form("monitor_sect%d", s+1));
				monitor[s]->SetDirectory(0);
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
    parameter_file = filename;

	// DC are at 6 degrees, but projected slope is somehow less than tan(6) = 0.1051
	stereo_angle_slope = 0.064;
	
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
	
	// these values are found empirically by looking at the XY plot
	XMIN[0] = 13.0;
	XMIN[1] = 44.0;
	XMIN[2] = 82.0;
	XMIN[3] = 90.0;
	XMIN[4] = 135.0;
	
	YMIN[0][0] = -0.4;
	YMIN[0][1] = 0.2;
	YMIN[0][2] = 0.2;
	YMIN[0][3] = 0.6;
	YMIN[0][4] = 1.1;
	YMIN[0][5] = 0.1;

	YMIN[1][0] = 0.1;
	YMIN[1][1] = 0.4;
	YMIN[1][2] = 0.2;
	YMIN[1][3] = 0.3;
	YMIN[1][4] = 1.8;
	YMIN[1][5] = 0.5;

	YMIN[2][0] = 0.0;
	YMIN[2][1] = 0.5;
	YMIN[2][2] = 0.0;
	YMIN[2][3] = 1.5;
	YMIN[2][4] = 2.5;
	YMIN[2][5] = 1.7;

	YMIN[4][0] = 0.5;
	YMIN[4][1] = 0.5;
	YMIN[4][2] = 0.0;
	YMIN[4][3] = 0.8;
	YMIN[4][4] = 4.0;
	YMIN[4][5] = 0.0;
	
	
	while(getline( parfile, line))
	{
		istringstream cuts(line);
		while(!cuts.eof())
		{
			string al;
			cuts >> al;
			if(al == "R1_A_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_a_left[s];
			}
			if(al == "R1_A_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_a_rite[s];
			}
			if(al == "R2_A_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_a_left[s];
			}
			if(al == "R2_A_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_a_rite[s];
			}
			if(al == "R3_A_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_a_left[s];
			}
			if(al == "R3_A_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_a_rite[s];
			}
			if(al == "SC_A_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_a_left[s];
			}
			if(al == "SC_A_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_a_rite[s];
			}
			
			if(al == "R1_B_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_b_left[s];
			}
			if(al == "R1_B_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_b_rite[s];
			}
			if(al == "R2_B_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_b_left[s];
			}
			if(al == "R2_B_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_b_rite[s];
			}
			if(al == "R3_B_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_b_left[s];
			}
			if(al == "R3_B_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_b_rite[s];
			}
			if(al == "SC_B_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_b_left[s];
			}
			if(al == "SC_B_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_b_rite[s];
			}
			if(al == "R1_C_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_c_left[s];
			}
			if(al == "R1_C_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r1_c_rite[s];
			}
			if(al == "R2_C_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_c_left[s];
			}
			if(al == "R2_C_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_c_rite[s];
			}
			if(al == "R3_C_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_c_left[s];
			}
			if(al == "R3_C_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_c_rite[s];
			}
			if(al == "SC_C_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_c_left[s];
			}
			if(al == "SC_C_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> sc_c_rite[s];
			}

			if(al == "R2_D_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_d_left[s];
			}
			if(al == "R2_D_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r2_d_rite[s];
			}
			if(al == "R3_D_LEFT:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_d_left[s];
			}
			if(al == "R3_D_RITE:")
			{
				for(unsigned int s=0; s<6; s++) cuts >> r3_d_rite[s];
			}

			if(al == "R1_AXIAL_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r1_axial_limits.push_back(tmp);
				addinfo = " > R1 Axial Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r1_axial_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r1_axial_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "R2_AXIAL_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r2_axial_limits.push_back(tmp);
				addinfo = " > R2 Axial Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r2_axial_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r2_axial_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "R3_AXIAL_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r3_axial_limits.push_back(tmp);
				addinfo = " > R3 Axial Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r3_axial_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r3_axial_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "SC_AXIAL_LIMITS:")
			{
				double tmp;
				cuts >> tmp; sc_axial_limits.push_back(tmp);
				addinfo = " > SC Axial Hole in Sector: " + stringify(tmp);
				cuts >> tmp; sc_axial_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; sc_axial_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			
			if(al == "R1_STEREO_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r1_stereo_limits.push_back(tmp);
				addinfo = " > R1 Stereo Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r1_stereo_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r1_stereo_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "R2_STEREO_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r2_stereo_limits.push_back(tmp);
				addinfo = " > R2 Stereo Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r2_stereo_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r2_stereo_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "R3_STEREO_LIMITS:")
			{
				double tmp;
				cuts >> tmp; r3_stereo_limits.push_back(tmp);
				addinfo = " > R3 Stereo Hole in Sector: " + stringify(tmp);
				cuts >> tmp; r3_stereo_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; r3_stereo_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
			if(al == "SC_STEREO_LIMITS:")
			{
				double tmp;
				cuts >> tmp; sc_stereo_limits.push_back(tmp);
				addinfo = " > SC Stereo Hole in Sector: " + stringify(tmp);
				cuts >> tmp; sc_stereo_limits.push_back(tmp);
				addinfo += "  Min: ";
				addinfo += stringify(tmp);
				addinfo += "  Max: ";
				cuts >> tmp; sc_stereo_limits.push_back(tmp);
				addinfo += stringify(tmp);
				addInfos.push_back(addinfo);
			}
		}
	}
	
	addInfos.push_back(" > XY XMIN positions: ");
	addinfo  = "";
	for(int p=0; p<5; p++)
	{
		addinfo += "   P" + stringify(p+1);
		addinfo += ": "  + stringify(XMIN[p]);
	}
	addInfos.push_back(addinfo);
	
	// left:  x = a + b_left*y + c_left*y2
	// left:  x = a + b_left*y + c_left*y2
	addInfos.push_back(" > XY parameters cuts: ");
	addInfos.push_back("   left:   x = a + b_left*y + c_left*y2");
	addInfos.push_back("   right:  x = a + b_rite*y + c_rite*y2");
	for(int ss=0; ss<6; ss++)
	{
		addinfo  = "   > S" + stringify(ss+1);
		addinfo += "  R1 A left: "  + stringify(r1_a_left[ss]);
		addinfo += "  R1 A rite: "  + stringify(r1_a_rite[ss]);
		addinfo += "  R2 A left: "  + stringify(r2_a_left[ss]);
		addinfo += "  R2 A rite: "  + stringify(r2_a_rite[ss]);
		addinfo += "  R3 A left: "  + stringify(r3_a_left[ss]);
		addinfo += "  R3 A rite: "  + stringify(r3_a_rite[ss]);
		addinfo += "  SC A left: "  + stringify(sc_a_left[ss]);
		addinfo += "  SC A rite: "  + stringify(sc_a_rite[ss]);
		addInfos.push_back(addinfo);
		addinfo  = "   > S" + stringify(ss+1);
		addinfo += "  R1 B left: "  + stringify(r1_b_left[ss]);
		addinfo += "  R1 B rite: "  + stringify(r1_b_rite[ss]);
		addinfo += "  R2 B left: "  + stringify(r2_b_left[ss]);
		addinfo += "  R2 B rite: "  + stringify(r2_b_rite[ss]);
		addinfo += "  R3 B left: "  + stringify(r3_b_left[ss]);
		addinfo += "  R3 B rite: "  + stringify(r3_b_rite[ss]);
		addinfo += "  SC B left: "  + stringify(sc_b_left[ss]);
		addinfo += "  SC B rite: "  + stringify(sc_b_rite[ss]);
		addInfos.push_back(addinfo);
		addinfo  = "   > S" + stringify(ss+1);
		addinfo += "  R1 C left: "  + stringify(r1_c_left[ss]);
		addinfo += "  R1 C rite: "  + stringify(r1_c_rite[ss]);
		addinfo += "  R2 C left: "  + stringify(r2_c_left[ss]);
		addinfo += "  R2 C rite: "  + stringify(r2_c_rite[ss]);
		addinfo += "  R3 C left: "  + stringify(r3_c_left[ss]);
		addinfo += "  R3 C rite: "  + stringify(r3_c_rite[ss]);
		addinfo += "  SC C left: "  + stringify(sc_c_left[ss]);
		addinfo += "  SC C rite: "  + stringify(sc_c_rite[ss]);
		addInfos.push_back(addinfo);
		addinfo  = "   > S" + stringify(ss+1);
		addinfo += "  R2 D left: "  + stringify(r2_d_left[ss]);
		addinfo += "  R2 D rite: "  + stringify(r2_d_rite[ss]);
		addinfo += "  R3 D left: "  + stringify(r3_d_left[ss]);
		addinfo += "  R3 D rite: "  + stringify(r3_d_rite[ss]);
		addInfos.push_back(addinfo);
	}
	
	for(unsigned int s=0; s<addInfos.size(); s++)
		cout << addInfos[s] << endl;
}

void cpars::write_vars()
{
	ofstream parfile(parameter_file.c_str());
	cout << endl << " Opening output parameter file " << parameter_file << endl;
	
	parfile << "R1_A_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_a_left[s] << " ";}
	parfile << "   # XY parameters cuts for R1 A LEFT" << endl;
	
	parfile << "R1_A_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_a_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R1 A RITE" << endl;
	
	parfile << "R2_A_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_a_left[s] << " ";}
	parfile << "   # XY parameters cuts for R2 A LEFT" << endl;
	
	parfile << "R2_A_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_a_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R2 A RITE" << endl;
	
	parfile << "R3_A_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_a_left[s] << " ";}
	parfile << "   # XY parameters cuts for R3 A LEFT" << endl;
	
	parfile << "R3_A_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_a_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R3 A RITE" << endl;
	
	parfile << "SC_A_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_a_left[s] << " ";}
	parfile << "   # XY parameters cuts for SC A LEFT" << endl;
	
	parfile << "SC_A_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_a_rite[s] << " ";}
	parfile << "   # XY parameters cuts for SC A RITE" << endl;
	
	
	parfile << "R1_B_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_b_left[s] << " ";}
	parfile << "   # XY parameters cuts for R1 B LEFT" << endl;
	
	parfile << "R1_B_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_b_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R1 B RITE" << endl;
	
	parfile << "R2_B_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_b_left[s] << " ";}
	parfile << "   # XY parameters cuts for R2 B LEFT" << endl;
	
	parfile << "R2_B_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_b_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R2 B RITE" << endl;
	
	parfile << "R3_B_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_b_left[s] << " ";}
	parfile << "   # XY parameters cuts for R3 B LEFT" << endl;
	
	parfile << "R3_B_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_b_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R3 B RITE" << endl;
	
	parfile << "SC_B_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_b_left[s] << " ";}
	parfile << "   # XY parameters cuts for SC B LEFT" << endl;
	
	parfile << "SC_B_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_b_rite[s] << " ";}
	parfile << "   # XY parameters cuts for SC B RITE" << endl;
	
	parfile << "R1_C_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_c_left[s] << " ";}
	parfile << "   # XY parameters cuts for R1 C LEFT" << endl;
	
	parfile << "R1_C_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r1_c_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R1 C RITE" << endl;
	
	parfile << "R2_C_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_c_left[s] << " ";}
	parfile << "   # XY parameters cuts for R2 C LEFT" << endl;
	
	parfile << "R2_C_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_c_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R2 C RITE" << endl;
	
	parfile << "R3_C_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_c_left[s] << " ";}
	parfile << "   # XY parameters cuts for R3 C LEFT" << endl;
	
	parfile << "R3_C_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_c_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R3 C RITE" << endl;
	
	parfile << "SC_C_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_c_left[s] << " ";}
	parfile << "   # XY parameters cuts for SC C LEFT" << endl;
	
	parfile << "SC_C_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << sc_c_rite[s] << " ";}
	parfile << "   # XY parameters cuts for SC C RITE" << endl;

	parfile << "R2_D_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_d_left[s] << " ";}
	parfile << "   # XY parameters cuts for R2 D LEFT" << endl;
	
	parfile << "R2_D_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r2_d_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R2 D RITE" << endl;
	
	parfile << "R3_D_LEFT: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_d_left[s] << " ";}
	parfile << "   # XY parameters cuts for R3 D LEFT" << endl;
	
	parfile << "R3_D_RITE: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << r3_d_rite[s] << " ";}
	parfile << "   # XY parameters cuts for R3 D RITE" << endl;
	
	

	for(unsigned int c=0; c<r1_axial_limits.size()/3; c++)
	{
		parfile << "R1_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r1_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r1_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r1_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R1 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<r2_axial_limits.size()/3; c++)
	{
		parfile << "R2_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r2_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r2_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r2_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R2 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<r3_axial_limits.size()/3; c++)
	{
		parfile << "R3_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r3_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r3_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r3_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R3 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<sc_axial_limits.size()/3; c++)
	{
		parfile << "SC_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << sc_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << sc_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << sc_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of SC Axial Limits" << endl;
	}

	for(unsigned int c=0; c<r1_stereo_limits.size()/3; c++)
	{
		parfile << "R1_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r1_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r1_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r1_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R1 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<r2_stereo_limits.size()/3; c++)
	{
		parfile << "R2_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r2_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r2_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r2_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R2 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<r3_stereo_limits.size()/3; c++)
	{
		parfile << "R3_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r3_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r3_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r3_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R3 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<sc_stereo_limits.size()/3; c++)
	{
		parfile << "SC_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << sc_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << sc_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << sc_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of SC Stereo Limits" << endl;
	}

}


double cpars::xycut(int sector, int plane, double x, double y)
{
	int s  = sector - 1;
	
	if(plane == 1)
	{
		if(y<=0)
			if(x > r1_a_left[s] + r1_b_left[s]*y + r1_c_left[s]*y*y)
				return 1;
		if(y>0)
			if(x > r1_a_rite[s] + r1_b_rite[s]*y + r1_c_rite[s]*y*y)
				return 1;
	}
	if(plane == 2)
	{
		if(y<=0)
			if(x > r2_a_left[s] + r2_b_left[s]*y + r2_c_left[s]*y*y + r2_d_left[s]*y*y*y)
				return 1;
		if(y>0)
			if(x > r2_a_rite[s] + r2_b_rite[s]*y + r2_c_rite[s]*y*y + r2_d_rite[s]*y*y*y)
				return 1;
	}
	if(plane == 3)
	{
		if(y<=0)
			if(x > r3_a_left[s] + r3_b_left[s]*y + r3_c_left[s]*y*y + r3_d_left[s]*y*y*y)
				return 1;
		if(y>0)
			if(x > r3_a_rite[s] + r3_b_rite[s]*y + r3_c_rite[s]*y*y + r3_d_rite[s]*y*y*y)
				return 1;
	}
	if(plane == 5)
	{
		if(y<=0)
			if(x > sc_a_left[s] + sc_b_left[s]*y + sc_c_left[s]*y*y)
				return 1;
		if(y>0)
			if(x > sc_a_rite[s] + sc_b_rite[s]*y + sc_c_rite[s]*y*y)
				return 1;
	}
   return 0;
}

double cpars::xyholes(int sector, int plane, double x, double y)
{
	
	if(plane == 1)
	{
		for(unsigned int c=0; c<r1_axial_limits.size()/3; c++)
		{
			if(sector == r1_axial_limits[c*3])
			{
				double min_x = r1_axial_limits[c*3+1];
				double max_x = r1_axial_limits[c*3+2];
				if(x > min_x && x < max_x)
					return 0;
			}
		}
		for(unsigned int c=0; c<r1_stereo_limits.size()/3; c++)
		{
			if(sector == r1_stereo_limits[c*3])
			{
				double min_x = r1_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r1_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x)
					return 0;
			}
		}
	}
	if(plane == 2)
	{
		for(unsigned int c=0; c<r2_axial_limits.size()/3; c++)
		{
			if(sector == r2_axial_limits[c*3])
			{
				double min_x = r2_axial_limits[c*3+1];
				double max_x = r2_axial_limits[c*3+2];
				if(x > min_x && x < max_x)
					return 0;
			}
		}
		for(unsigned int c=0; c<r2_stereo_limits.size()/3; c++)
		{
			if(sector == r2_stereo_limits[c*3])
			{
				double min_x = r2_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r2_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x)
					return 0;
			}
		}
	}
	if(plane == 3)
	{
		for(unsigned int c=0; c<r3_axial_limits.size()/3; c++)
		{
			if(sector == r3_axial_limits[c*3])
			{
				double min_x = r3_axial_limits[c*3+1];
				double max_x = r3_axial_limits[c*3+2];
				if(x > min_x && x < max_x)
					return 0;
			}
		}
		for(unsigned int c=0; c<r3_stereo_limits.size()/3; c++)
		{
			if(sector == r3_stereo_limits[c*3])
			{
				double min_x = r3_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r3_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x)
					return 0;
			}
		}
	}
	if(plane == 5)
	{
		for(unsigned int c=0; c<sc_axial_limits.size()/3; c++)
		{
			if(sector == sc_axial_limits[c*3])
			{
				double min_x = sc_axial_limits[c*3+1];
				double max_x = sc_axial_limits[c*3+2];
				if(x > min_x && x < max_x)
					return 0;
			}
		}
		for(unsigned int c=0; c<sc_stereo_limits.size()/3; c++)
		{
			if(sector == sc_stereo_limits[c*3])
			{
				double min_x = sc_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = sc_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x)
					return 0;
			}
		}
	}

	return 1;
}
