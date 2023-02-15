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
	for(int m=0; m<NDIV_P; m++) {
		mom[m]  = minp + (m + 0.5)*dp;
		mom2[m] = minp + (m + 1.0)*dp;
	}
	
	double x_min[5]  = {-40,  -100,  -150, -200,  -200};
	double x_max[5]  = { 40,   100,   150,  200,   200};
	double y_min[5]  = { 30,    70,    70,   50,    50};
	double y_max[5]  = { 55,   165,   250,  440,   370};
	double limxf[5]  = { 3.5, 10.0,  15.0, 19.0,  19.0};
	double limyf1[5] = { 1.0,  2.2,   0.5, -1.5,  -1.5};
	double limyf2[5] = { 3.0, 10.0,  16.0, 28.0,  28.0};
	
	// Default: filename is output file
	if(READ == 0) {
		output = NULL;
		if(filename!= "none") {
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
		
		for(int s=0; s<7; s++) {
			for(int c=0; c<4; c++) {
				for(int p=0; p<5; p++) {
					x_y_tot[c][s][p] = new TH2F(Form("x_y_tot_plane%d_%s_sect%d",       p+1, cut[c].c_str(), s+1),
														 Form("x vs y, plane %d, %s, sector %d", p+1, cut[c].c_str(), s+1),
																400, x_min[p],                  x_max[p],
					  										400, y_min[p]-NDIV_P*limyf1[p], y_max[p]);
				}
				
				
				for(int m=0; m<NDIV_P; m++) {
					phi_theta[c][s][m] = new TH2F(Form("phi_theta_mom%d_%s_sect%d",                 m+1, cut[c].c_str(), s+1),
															Form("phi vs theta, mom=%2.1f, %s, sector %d", mom[m], cut[c].c_str(), s+1),
																	280, 24.0 - m*1.8, 65.0 - m*4.5, 240, -32+m, 32-m);
				
					for(int p=0; p<5; p++) {
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
	} else {
        // Reading from Input file
		if(filename!= "none") {

            // check if filename exists
            std::filesystem::path p(filename);
            if( ! std::filesystem::exists(p) ) {
                cout << " File " << filename << " does not exist. Exiting..." << endl;
                exit(1);
            }

            TFile f(filename.c_str());
			cout << " Loading histos from: " << filename << endl;
			for(int s=0; s<7; s++) {
				for(int c=0; c<4; c++) {
					for(int p=0; p<5; p++) {
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
					for(int m=0; m<NDIV_P; m++) {
						phi_theta[c][s][m] = (TH2F*)f.Get(Form("phi_theta_mom%d_%s_sect%d", m+1, cut[c].c_str(), s+1));
						phi_theta[c][s][m]->SetDirectory(0);
						for(int p=0; p<5; p++) {
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
		} else {
			cout << " No Input File selected. Exiting constructor..." << endl;
			return;
		}
	}
}

void chistos::write_and_close()
{
	if(output) {
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
	
	ifstream parfile(parameter_file.c_str(), ios::in);
	cout << endl << " Opening parameter file " << parameter_file << endl;
	if(!parfile) {
		cout << " File " <<  parameter_file << " could not be opened. " << endl;
		cout << " Specify parameters file with -PARS_FILE=filename. Exiting. " << endl;
		exit(0);
	}
	
	string line;
	string addinfo;
	
	// these values are found empirically by looking at the XY plot
	XMIN[0] = 22.5;
	XMIN[1] = 58.5;
	XMIN[2] = 74.5;
	XMIN[3] = 90.0;
	XMIN[4] = 89.0;
	
	YMIN[0][0] = -0.5;
	YMIN[0][1] = -0.3;
	YMIN[0][2] = 0.1;
	YMIN[0][3] = -0.2;
	YMIN[0][4] = -0.3;
	YMIN[0][5] = -0.7;

	YMIN[1][0] = -1.0;
	YMIN[1][1] = -0.8;
	YMIN[1][2] = -0.1;
	YMIN[1][3] = -0.8;
	YMIN[1][4] = -0.8;
	YMIN[1][5] = -1.1;

	YMIN[2][0] = -0.8;
	YMIN[2][1] = -0.5;
	YMIN[2][2] = -0.7;
	YMIN[2][3] = -1.2;
	YMIN[2][4] = -1.2;
	YMIN[2][5] = -1.7;

	YMIN[4][0] = -1.5;
	YMIN[4][1] = -0.9;
	YMIN[4][2] = -1.9;
	YMIN[4][3] = -2.0;
	YMIN[4][4] = -1.8;
	YMIN[4][5] = -1.5;
	
	
	while(getline( parfile, line)) {
		istringstream cuts(line);
		while(!cuts.eof()) {
			string al;
			cuts >> al;
			if(al == "C1:") {
				for(int s=0; s<6; s++) cuts >> c1[s];
			} else if(al == "C2:") {
				for(int s=0; s<6; s++) cuts >> c2[s];
			} else if(al == "C3:") {
				for(int s=0; s<6; s++) cuts >> c3[s];
			} else if(al == "C4:") {
				for(int s=0; s<6; s++) cuts >> c4[s];
			} else if(al == "C5:") {
				for(int s=0; s<6; s++) cuts >> c5[s];
			} else if(al == "C6:") {
				for(int s=0; s<6; s++) cuts >> c6[s];
			} else if(al == "R1_B_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r1_b_left[s];
			} else if(al == "R1_B_RITE:") {
				for(int s=0; s<6; s++) cuts >> r1_b_rite[s];
			} else if(al == "R2_B_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r2_b_left[s];
			} else if(al == "R2_B_RITE:") {
				for(int s=0; s<6; s++) cuts >> r2_b_rite[s];
			} else if(al == "R3_B_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r3_b_left[s];
			} else if(al == "R3_B_RITE:") {
				for(int s=0; s<6; s++) cuts >> r3_b_rite[s];
			} else if(al == "SC_B_LEFT:") {
				for(int s=0; s<6; s++) cuts >> sc_b_left[s];
			} else if(al == "SC_B_RITE:") {
				for(int s=0; s<6; s++) cuts >> sc_b_rite[s];
			} else if(al == "R1_C_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r1_c_left[s];
			} else if(al == "R1_C_RITE:") {
				for(int s=0; s<6; s++) cuts >> r1_c_rite[s];
			} else if(al == "R2_C_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r2_c_left[s];
			} else if(al == "R2_C_RITE:") {
				for(int s=0; s<6; s++) cuts >> r2_c_rite[s];
			} else if(al == "R3_C_LEFT:") {
				for(int s=0; s<6; s++) cuts >> r3_c_left[s];
			} else if(al == "R3_C_RITE:") {
				for(int s=0; s<6; s++) cuts >> r3_c_rite[s];
			} else if(al == "SC_C_LEFT:") {
				for(int s=0; s<6; s++) cuts >> sc_c_left[s];
			} else if(al == "SC_C_RITE:") {
				for(int s=0; s<6; s++) cuts >> sc_c_rite[s];
			} else if(al == "R1_AXIAL_LIMITS:") {
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
			} else if(al == "R2_AXIAL_LIMITS:") {
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
			} else if(al == "R3_AXIAL_LIMITS:") {
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
			} else if(al == "SC_AXIAL_LIMITS:") {
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
			} else if(al == "R1_STEREO_LIMITS:") {
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
			} else if(al == "R2_STEREO_LIMITS:") {
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
			} else if(al == "R3_STEREO_LIMITS:") {
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
			} else if(al == "SC_STEREO_LIMITS:") {
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
	addInfos.push_back(" > Theta vs Phi Cut Pars: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   > S"  + stringify(s+1);
		addinfo += "  C1: "  + stringify(c1[s]);
		addinfo += "  C2: "  + stringify(c2[s]);
		addinfo += "  C3: "  + stringify(c3[s]);
		addinfo += "  C4: "  + stringify(c4[s]);
		addinfo += "  C5: "  + stringify(c5[s]);
		addinfo += "  C6: "  + stringify(c6[s]);
		addInfos.push_back(addinfo);
	}
	
	addInfos.push_back(" > XY XMIN positions: ");
	addinfo  = "";
	for(int p=0; p<5; p++) {
		addinfo += "   P" + stringify(p+1);
		addinfo += ": "  + stringify(XMIN[p]);
	}
	addInfos.push_back(addinfo);
	
	// left:  x = a + b_left*y + c_left*y2
	// left:  x = a + b_left*y + c_left*y2
	// a = XMIN - b YMIN - c YMIN*YMIN
	// XMIN is the vertex vertical position of each plane's bottom corner(same in all sectors)
	// YMIN is the vertex horizontal position of each plane's bottom corner
	addInfos.push_back(" > XY parameters cuts: ");
	addInfos.push_back("   left:   x = a + b_left*y + c_left*y2");
	addInfos.push_back("   right:  x = a + b_rite*y + c_rite*y2");
	addInfos.push_back("   with parameter 'a' fixed to: XMIN - b YMIN - c YMIN*YMIN");
	for(int s=0; s<6; s++) {
		addinfo  = "   > S" + stringify(s+1);
		addinfo += "  R1 B left: "  + stringify(r1_b_left[s]);
		addinfo += "  R1 B rite: "  + stringify(r1_b_rite[s]);
		addinfo += "  R2 B left: "  + stringify(r2_b_left[s]);
		addinfo += "  R2 B rite: "  + stringify(r2_b_rite[s]);
		addinfo += "  R3 B left: "  + stringify(r3_b_left[s]);
		addinfo += "  R3 B rite: "  + stringify(r3_b_rite[s]);
		addinfo += "  SC B left: "  + stringify(sc_b_left[s]);
		addinfo += "  SC B rite: "  + stringify(sc_b_rite[s]);
		addInfos.push_back(addinfo);
		addinfo  = "   > S" + stringify(s+1);
		addinfo += "  R1 C left: "  + stringify(r1_c_left[s]);
		addinfo += "  R1 C rite: "  + stringify(r1_c_rite[s]);
		addinfo += "  R2 C left: "  + stringify(r2_c_left[s]);
		addinfo += "  R2 C rite: "  + stringify(r2_c_rite[s]);
		addinfo += "  R3 C left: "  + stringify(r3_c_left[s]);
		addinfo += "  R3 C rite: "  + stringify(r3_c_rite[s]);
		addinfo += "  SC C left: "  + stringify(sc_c_left[s]);
		addinfo += "  SC C rite: "  + stringify(sc_c_rite[s]);
		addInfos.push_back(addinfo);
	}

	for(unsigned int ss=0; ss<addInfos.size(); ss++) { cout << addInfos[ss] << endl; }
}

void cpars::write_vars(string filename)
{
	ofstream parfile(filename.c_str());
	cout << endl << " Opening output parameter file " << filename << endl;
	
	parfile << "C1: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c1[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C1" << endl;
	
	parfile << "C2: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c2[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C2" << endl;
	
	parfile << "C3: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c3[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C3" << endl;
	
	parfile << "C4: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c4[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C4" << endl;
	
	parfile << "C5: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c5[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C5" << endl;
	
	parfile << "C6: " ;
	for(int s=0; s<6; s++) {parfile.width(8) ; parfile << c6[s] << " ";}
	parfile << "   # Theta vs Phi Cut Pars C6" << endl;
	
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

	for(unsigned int c=0; c<r1_axial_limits.size()/3; c++) {
		parfile << "R1_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r1_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r1_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r1_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R1 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<r2_axial_limits.size()/3; c++) {
		parfile << "R2_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r2_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r2_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r2_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R2 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<r3_axial_limits.size()/3; c++) {
		parfile << "R3_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << r3_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << r3_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r3_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R3 Axial Limits" << endl;
	}
	for(unsigned int c=0; c<sc_axial_limits.size()/3; c++) {
		parfile << "SC_AXIAL_LIMITS:  " ;
		parfile.width(3);
		parfile << sc_axial_limits[c*3] << " ";
		parfile.width(5);
		parfile << sc_axial_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << sc_axial_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of SC Axial Limits" << endl;
	}

	for(unsigned int c=0; c<r1_stereo_limits.size()/3; c++) {
		parfile << "R1_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r1_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r1_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r1_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R1 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<r2_stereo_limits.size()/3; c++) {
		parfile << "R2_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r2_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r2_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r2_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R2 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<r3_stereo_limits.size()/3; c++) {
		parfile << "R3_STEREO_LIMITS: " ;
		parfile.width(3);
		parfile << r3_stereo_limits[c*3] << " ";
		parfile.width(5);
		parfile << r3_stereo_limits[c*3+1] << " ";
		parfile.width(5);
		parfile << r3_stereo_limits[c*3+2] << " ";
		parfile << "   # Sector, Min and Max X of R3 Stereo Limits" << endl;
	}
	for(unsigned int c=0; c<sc_stereo_limits.size()/3; c++) {
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

// all angle units here are in degrees, momentum in GeV
double cpars::theta_cut(int sect, double p)
{
	int s = sect - 1;
	return ( c1[s] + c2[s]/(p + c6[s]) );
}

double cpars::expon(int sect, double p)
{
	int s = sect - 1;
	return c3[s] * pow(p, c5[s] ) ;
}

double cpars::dphi(int sect, double p, double t)
{
	double RD = 57.2957795131;
	int s = sect - 1;
	
	double thc  = theta_cut(sect, p);
	double expo = expon(sect, p);
	
	if(t>thc && t<thc + 180.0) return c4[s] * pow( sin(t/RD - thc/RD) , expo);
	
	else return 0;
}


double cpars::xycut(int sector, int plane, double x, double y)
{
	int s  = sector - 1;
	int pl = plane -1;
	
	double a_left;
	double a_rite;
	
	if(plane == 1) {
		a_left = XMIN[pl] - r1_b_left[s]*YMIN[pl][s] - r1_c_left[s]*YMIN[pl][s]*YMIN[pl][s];
		a_rite = XMIN[pl] - r1_b_rite[s]*YMIN[pl][s] - r1_c_rite[s]*YMIN[pl][s]*YMIN[pl][s];
		if(y<=0)
			if(x > a_left + r1_b_left[s]*y + r1_c_left[s]*y*y)
				return 1;
		if(y>0)
			if(x > a_rite + r1_b_rite[s]*y + r1_c_rite[s]*y*y)
				return 1;
	} else if(plane == 2) {
		a_left = XMIN[pl] - r2_b_left[s]*YMIN[pl][s] - r2_c_left[s]*YMIN[pl][s]*YMIN[pl][s];
		a_rite = XMIN[pl] - r2_b_rite[s]*YMIN[pl][s] - r2_c_rite[s]*YMIN[pl][s]*YMIN[pl][s];
		if(y<=0)
			if(x > a_left + r2_b_left[s]*y + r2_c_left[s]*y*y)
				return 1;
		if(y>0)
			if(x > a_rite + r2_b_rite[s]*y + r2_c_rite[s]*y*y)
				return 1;
	} else if(plane == 3) {
		a_left = XMIN[pl] - r3_b_left[s]*YMIN[pl][s] - r3_c_left[s]*YMIN[pl][s]*YMIN[pl][s];
		a_rite = XMIN[pl] - r3_b_rite[s]*YMIN[pl][s] - r3_c_rite[s]*YMIN[pl][s]*YMIN[pl][s];
		if(y<=0)
			if(x > a_left + r3_b_left[s]*y + r3_c_left[s]*y*y)
				return 1;
		if(y>0)
			if(x > a_rite + r3_b_rite[s]*y + r3_c_rite[s]*y*y)
				return 1;
	} else if(plane == 5) {
		a_left = XMIN[pl] - sc_b_left[s]*YMIN[pl][s] - sc_c_left[s]*YMIN[pl][s]*YMIN[pl][s];
		a_rite = XMIN[pl] - sc_b_rite[s]*YMIN[pl][s] - sc_c_rite[s]*YMIN[pl][s]*YMIN[pl][s];
		if(y<=0) {
            if (x > a_left + sc_b_left[s] * y + sc_c_left[s] * y * y) { return 1; }
        } else {
            if (x > a_rite + sc_b_rite[s] * y + sc_c_rite[s] * y * y) { return 1; }
        }
	}
   return 0;
}

double cpars::xyholes(int sector, int plane, double x, double y)
{
	if(plane == 1) {
		for(unsigned int c=0; c<r1_axial_limits.size()/3; c++) {
			if(sector == r1_axial_limits[c*3]) {
				double min_x = r1_axial_limits[c*3+1];
				double max_x = r1_axial_limits[c*3+2];
				if(x > min_x && x < max_x) { return 0; }
			}
		}
		for(unsigned int c=0; c<r1_stereo_limits.size()/3; c++) {
			if(sector == r1_stereo_limits[c*3]) {
				double min_x = r1_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r1_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x) { return 0; }
			}
		}
	} else if(plane == 2) {
		for(unsigned int c=0; c<r2_axial_limits.size()/3; c++) {
			if(sector == r2_axial_limits[c*3])
			{
				double min_x = r2_axial_limits[c*3+1];
				double max_x = r2_axial_limits[c*3+2];
				if(x > min_x && x < max_x) { return 0; }
			}
		}
		for(unsigned int c=0; c<r2_stereo_limits.size()/3; c++)
		{
			if(sector == r2_stereo_limits[c*3])
			{
				double min_x = r2_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r2_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x) { return 0; }
			}
		}
	} else if(plane == 3) {
		for(unsigned int c=0; c<r3_axial_limits.size()/3; c++) {
			if(sector == r3_axial_limits[c*3]) {
				double min_x = r3_axial_limits[c*3+1];
				double max_x = r3_axial_limits[c*3+2];
				if(x > min_x && x < max_x) { return 0; }
			}
		}
		for(unsigned int c=0; c<r3_stereo_limits.size()/3; c++) {
			if(sector == r3_stereo_limits[c*3]) {
				double min_x = r3_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = r3_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x) { return 0; }
			}
		}
	} else if(plane == 5) {
		for(unsigned int c=0; c<sc_axial_limits.size()/3; c++) {
			if(sector == sc_axial_limits[c*3]) {
				double min_x = sc_axial_limits[c*3+1];
				double max_x = sc_axial_limits[c*3+2];
				if(x > min_x && x < max_x) { return 0; }
			}
		}
		for(unsigned int c=0; c<sc_stereo_limits.size()/3; c++) {
			if(sector == sc_stereo_limits[c*3]) {
				double min_x = sc_stereo_limits[c*3+1] - y*stereo_angle_slope;
				double max_x = sc_stereo_limits[c*3+2] - y*stereo_angle_slope;
				if(x > min_x && x < max_x) { return 0; }
			}
		}
	}

	return 1;
}








