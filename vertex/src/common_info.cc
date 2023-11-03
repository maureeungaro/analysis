// MU includes
#include "common_info.h"
#include "utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
chistos::chistos(string filename, int READ)
{
	string par[2]  = {"electron", "proton"};
	string what[3] = {"no_corr", "corrected", "cut_applied"};
	
	// Default: filename is output file
	if(READ == 0) {
		output = NULL;
		if(filename!= "none") {
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
		
		for(int s=0; s<7; s++) {
			for(int w=0; w<3; w++) {
				deltavz_vz[s][w] = new TH2F(Form("deltavz_vz_%s_sector%d",    what[w].c_str(), s+1),
													 Form("delta vz vs vz%s_sector%d", what[w].c_str(), s+1), 260, -10, 3, 640, -3.8, 3.8);
				for(int p=0; p<2; p++) {
					phi_vz[s][w][p] =  new TH2F(Form("phi_vz_%s_%s_sector%d", par[p].c_str(), what[w].c_str(), s+1),
														 Form("phi_vz_%s_%s_sector%d", par[p].c_str(), what[w].c_str(), s+1),
																 260, -10, 3, 740, -10, 360);
					    vz[s][w][p] =  new TH1F(Form("vz_%s_%s_sector%d", par[p].c_str(), what[w].c_str(), s+1),
														 Form("vz_%s_%s_sector%d", par[p].c_str(), what[w].c_str(), s+1),
																 260, -10, 3);
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
				for(int w=0; w<3; w++) {
					deltavz_vz[s][w] = (TH2F*)f.Get(Form("deltavz_vz_%s_sector%d",    what[w].c_str(), s+1));
					deltavz_vz[s][w]->SetDirectory(0);
					
					deltavz_vz[s][w]->GetXaxis()->SetTitle(Form("vertex z               [cm]"));
					deltavz_vz[s][w]->GetXaxis()->SetTitleOffset(1.1);
					deltavz_vz[s][w]->GetXaxis()->SetTitleSize(0.054);
					deltavz_vz[s][w]->GetYaxis()->SetTitle(Form("VZ_{e}-VZ_{p} (#Delta VZ) [cm] "));
					deltavz_vz[s][w]->GetYaxis()->SetTitleOffset(1.00);
					deltavz_vz[s][w]->GetYaxis()->SetTitleSize(0.054);

					for(int p=0; p<2; p++) {
						phi_vz[s][w][p] = (TH2F*)f.Get(Form("phi_vz_%s_%s_sector%d", par[p].c_str(), what[w].c_str(), s+1));
						    vz[s][w][p] = (TH1F*)f.Get(Form("vz_%s_%s_sector%d",     par[p].c_str(), what[w].c_str(), s+1));
							 
						phi_vz[s][w][p]->SetDirectory(0);
						    vz[s][w][p]->SetDirectory(0);
							 
						phi_vz[s][w][p]->GetXaxis()->SetTitle(Form("vertex z               [cm]"));
						phi_vz[s][w][p]->GetXaxis()->SetTitleOffset(1.1);
						phi_vz[s][w][p]->GetXaxis()->SetTitleSize(0.054);
						phi_vz[s][w][p]->GetYaxis()->SetTitle(Form("#phi    [deg]"));
						phi_vz[s][w][p]->GetYaxis()->SetTitleOffset(1.2);
						phi_vz[s][w][p]->GetYaxis()->SetTitleSize(0.054);

						// Titles
						vz[s][w][p]->GetXaxis()->SetTitle(Form("vertex z                 [cm]"));
						vz[s][w][p]->GetXaxis()->SetTitleOffset(1.1);
						vz[s][w][p]->GetXaxis()->SetTitleSize(0.054);
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

    ifstream parfile(parameter_file.c_str(), ios::in);
	cout << endl << " Opening parameter file " << parameter_file << endl;
	if(!parfile) {
		cout << " File " <<  parameter_file << " could not be opened. " << endl;
		cout << " Specify parameters file with -PARS_FILE=filename. Exiting. " << endl;
		exit(0);
	}
	
	string line;
	string addinfo;
	
	while(getline( parfile, line)) {
		istringstream cuts(line);
	
		while(!cuts.eof()) {
			string al;
			cuts >> al;
			if(al == "BEAMD:") {
				cuts >> beam_pos[0] >> beam_pos[1];
				addinfo  = "   > Beam position set to: (" + stringify(beam_pos[0]);
				addinfo  += ", ";
				addinfo  += stringify(beam_pos[1]);
				addinfo  += ") cm";
				addInfos.push_back(addinfo);
			} else if(al == "ZLIM:") {
				cuts >> vz_limits[0] >> vz_limits[1];
				addinfo  = "   > Z-Vertex Cut: " + stringify(vz_limits[0]);
				addinfo  += " <= vz <= ";
				addinfo  += stringify(vz_limits[1]);
				addinfo  += " cm";
				addInfos.push_back(addinfo);
			} else if(al == "DLTZ:") {
				cuts >> delta_z;
				addinfo  = "   > Electron-Proton Z-Vertexes Cut: " + stringify(delta_z);
				addinfo  += " cm";
				addInfos.push_back(addinfo);
			}
		}
	}
	
	for(unsigned int s=0; s<addInfos.size(); s++) { cout << addInfos[s] << endl; }
}

void cpars::write_vars()
{
	ofstream parfile(parameter_file.c_str());
	cout << endl << " Opening output parameter file " << parameter_file << endl;
	
	parfile << "BEAMD: ";
	parfile << beam_pos[0] << " " <<  beam_pos[0] ;
	parfile << "  # Beam (x,y) position" << endl;
		
	parfile << "ZLIM: ";
	parfile << vz_limits[0] << " " <<  vz_limits[0] ;
	parfile << "  # Z-Vertex Cut Min, Max" << endl;
	
	parfile << "DLTZ: ";
	parfile << delta_z;
	parfile << "          # Electron - Proton Z-Vertexes Cut" << endl << endl;
}
