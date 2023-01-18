// MU includes
#include "common_info.h"
#include "/opt/projects/muEvent/src/utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <sstream>


// Histograms
chistos::chistos(string filename, int READ)
{
	string cut[4]     = {"no_cuts_on", "all_other_cuts_on", "all_other_cuts_neg", "all_cuts_on"};
	Color_t colors[4] = {   kBlack   ,        kBlue       ,        kRed         ,     kGreen+3};
	
	// Default: filename is output file
	if(READ == 0)
	{
		output = NULL;
		if( filename != "none" ) {
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}

		for(int s=0; s<7; s++) {
			for(int c=0; c<4; c++) {
				nphe[c][s]          = new TH1F(Form("nphe_%s_sect%d",                         cut[c].c_str(), s+1),
                                               Form("10*photoelectrons in cc: %s, sector %d", cut[c].c_str(), s+1), 240, -20, 220);
				theta_vs_segm[c][s] = new TH2F(Form("theta_vs_segm_%s_sect%d",                cut[c].c_str(), s+1),
                                               Form("CC Theta vs segment: %s, sector %d",     cut[c].c_str(), s+1), 20, 0, 20, 900, -5, 60);
				phi_match[c][s]     = new TH1F(Form("phi_match_%s_sect%d",                    cut[c].c_str(), s+1),
                                               Form("CC phi match: %s, sector %d",            cut[c].c_str(), s+1), 7, -3, 3);
				cc_timing[c][s]     = new TH2F(Form("cc_timing_%s_sect%d",                    cut[c].c_str(), s+1),
                                               Form("CC Timing vs segment %s, sector %d",     cut[c].c_str(), s+1), 38, 0, 38, 400, -20, 20);
				ecthr[c][s]         = new TH1F(Form("ecthr_%s_sect%d",                        cut[c].c_str(), s+1),
                                               Form("EC Threshold: %s, sector %d",            cut[c].c_str(), s+1), 285, -0.3, 6.0);
				ecp[c][s]           = new TH2F(Form("ecp_%s_sect%d",                          cut[c].c_str(), s+1),
                                               Form("E_ec/P vs P: %s, sector %d",             cut[c].c_str(), s+1), 250, 0, 5, 250, 0.0, 0.5);
				ECu[c][s]           = new TH1F(Form("ECu_%s_sect%d",                          cut[c].c_str(), s+1),
                                               Form("EC U coordinate: %s, sector %d",         cut[c].c_str(), s+1), 235, -10, 460);
				ECv[c][s]           = new TH1F(Form("ECv_%s_sect%d",                          cut[c].c_str(), s+1),
                                               Form("EC V coordinate: %s, sector %d",         cut[c].c_str(), s+1), 235, -10, 420);
				ECw[c][s]           = new TH1F(Form("ECw_%s_sect%d",                          cut[c].c_str(), s+1),
                                               Form("EC W coordinate: %s, sector %d",         cut[c].c_str(), s+1), 235, -10, 460);
				EoutEin[c][s]       = new TH2F(Form("EoutEin_%s_sect%d",                      cut[c].c_str(), s+1),
                                               Form("Eout/P vs Ein/P: %s, sector %d",         cut[c].c_str(), s+1), 300, 0.0, 0.3, 300, 0.0, 0.3);
				EinEtot[c][s]       = new TH2F(Form("EinEtot_%s_sect%d",                      cut[c].c_str(), s+1),
                                               Form("Ein/E total vs P: %s, sector %d",        cut[c].c_str(), s+1), 225, 0.0, 4.5, 200, 0.0, 1.2);
			}
		}
		// utility histos
		nphe_phi = new TH2F("nphe_phi", "nphe vs phi", 240, -20, 220, 380, -40, 340);
		for(int s=0; s<7; s++) {
			//  1: no cuts
			//  2: npe
			//  3: p min
			//  4: sampling fraction
			//  5: U
			//  6: V
			//  7: W
			//  8: UVW
			//  9: Eo/Ei
			// 10: Ei/Etot
			// 11: cc match
			monitor[0][s]  = new TH1F(Form("monitor1_sect%d", s+1), Form("Individual cuts pass rate, sector %d", s+1), 11, 0, 11);

			// cumulative:
			monitor[1][s]  = new TH1F(Form("monitor2_sect%d", s+1), Form("Collective cuts pass rate, sector %d", s+1), 11, 0, 11);

			// 1: All events
			// 2: hit in CC
			// 3: hit in EC
			// 4: hit in both CC and EC
			monitor[2][s]  = new TH1F(Form("monitor3_sect%d", s+1), Form("Counter for hits in CC, EC, sector %d", s+1), 4, 0, 4);
		}

		for(int c=0; c<4; c++) {
			ECpos[c] = new TH2F(Form("ECpos_%s", cut[c].c_str()),
									  Form("Y versus X in EC plane: %s", cut[c].c_str()), 500, -500, 500, 500, -500, 500);
		}
		ECpos[4]    = new TH2F("ECpos_UVW_cut",
									  "Y versus X in EC plane: UVW Cut Applied", 500, -500, 500, 500, -500, 500);
	} else { // Reading from Input file
		if( filename != "none" ) {
			TFile f(filename.c_str());
			cout << "\n > Loading histos from: " << filename << endl;

			for(int s=0; s<7; s++) {
				for(int c=0; c<4; c++) {

                    theta_vs_segm[c][s] = (TH2F*)f.Get(Form("theta_vs_segm_%s_sect%d", cut[c].c_str(), s+1));
                    phi_match[c][s]     = (TH1F*)f.Get(Form("phi_match_%s_sect%d",     cut[c].c_str(), s+1));


					cc_timing[c][s]     = (TH2F*)f.Get(Form("cc_timing_%s_sect%d",     cut[c].c_str(), s+1));


                    // set dir
					cc_timing[c][s]    ->SetDirectory(0);
					theta_vs_segm[c][s]->SetDirectory(0);
                    phi_match[c][s]    ->SetDirectory(0);

                    // colors
                    phi_match[c][s]    ->SetLineColor(colors[c]);


                    // titles
                    theta_vs_segm[c][s]->GetXaxis()->SetTitle(Form("Sector %d             [segment]", s+1));
					theta_vs_segm[c][s]->GetYaxis()->SetTitle(Form("#theta on CC plane    [degrees]"));


//					nphe[c][s]          = (TH1F*)f.Get(Form("nphe_%s_sect%d",          cut[c].c_str(), s+1));
//					ecthr[c][s]         = (TH1F*)f.Get(Form("ecthr_%s_sect%d",         cut[c].c_str(), s+1));
//					ecp[c][s]           = (TH2F*)f.Get(Form("ecp_%s_sect%d",           cut[c].c_str(), s+1));
//					ECu[c][s]           = (TH1F*)f.Get(Form("ECu_%s_sect%d",           cut[c].c_str(), s+1));
//					ECv[c][s]           = (TH1F*)f.Get(Form("ECv_%s_sect%d",           cut[c].c_str(), s+1));
//					ECw[c][s]           = (TH1F*)f.Get(Form("ECw_%s_sect%d",           cut[c].c_str(), s+1));
//					EoutEin[c][s]       = (TH2F*)f.Get(Form("EoutEin_%s_sect%d",       cut[c].c_str(), s+1));
//					EinEtot[c][s]       = (TH2F*)f.Get(Form("EinEtot_%s_sect%d",       cut[c].c_str(), s+1));
//					nphe[c][s]         ->SetDirectory(0);
//					ecthr[c][s]        ->SetDirectory(0);
//					ecp[c][s]          ->SetDirectory(0);
//					ECu[c][s]          ->SetDirectory(0);
//					ECv[c][s]          ->SetDirectory(0);
//					ECw[c][s]          ->SetDirectory(0);
//					EoutEin[c][s]      ->SetDirectory(0);
//					EinEtot[c][s]      ->SetDirectory(0);
//					nphe[c][s]         ->SetLineColor(colors[c]);
//					ecthr[c][s]        ->SetLineColor(colors[c]);
//					ECu[c][s]          ->SetLineColor(colors[c]);
//					ECv[c][s]          ->SetLineColor(colors[c]);
//					ECw[c][s]          ->SetLineColor(colors[c]);
//
//					ecp[c][s]          ->GetXaxis()->SetTitle(Form("p  [GeV]"));
//					ecp[c][s]          ->GetYaxis()->SetTitle(Form("E_{EC} / p"));
//					cc_timing[c][s]    ->GetXaxis()->SetTitle(Form("Sector %d              pmt", s+1));
//					cc_timing[c][s]    ->GetYaxis()->SetTitle(Form("#Delta T    [ns]"));
//					EoutEin[c][s]      ->GetXaxis()->SetTitle(Form("E_{in} / p"));
//					EoutEin[c][s]      ->GetYaxis()->SetTitle(Form("E_{out} / P"));
//					EinEtot[c][s]      ->GetXaxis()->SetTitle(Form("p  [GeV]"));
//					EinEtot[c][s]      ->GetYaxis()->SetTitle(Form("E_{in} / E_{TOT}"));
				}
				// X title
				if(s < 6) {
//					nphe[0][s]      ->GetXaxis()->SetTitle(Form("Sector %d          [nphe#times10]", s+1));
					phi_match[0][s] ->GetXaxis()->SetTitle(Form("Sector %d                [match index]",  s+1));
//					ecthr[0][s]     ->GetXaxis()->SetTitle(Form("Sector %d              p [GeV]", s+1));
//					ECu[1][s]       ->GetXaxis()->SetTitle(Form("Sector %d              U [cm]",  s+1));
//					ECv[1][s]       ->GetXaxis()->SetTitle(Form("Sector %d              V [cm]",  s+1));
//					ECw[1][s]       ->GetXaxis()->SetTitle(Form("Sector %d              W [cm]",  s+1));
				} else {
					theta_vs_segm[0][s]->GetXaxis()->SetTitle("All Sectors      Segment ");
					phi_match[0][s]    ->GetXaxis()->SetTitle("All Sectors");
//					nphe[0][s]         ->GetXaxis()->SetTitle("All Sectors                         [nphe#times10]");
//					cc_timing[0][s]    ->GetXaxis()->SetTitle("All Sectors      Segment ");
//					ecthr[0][s]        ->GetXaxis()->SetTitle("All Sectors                          p [GeV]");
//					ecp[0][s]          ->GetXaxis()->SetTitle("All Sectors");
//					ECu[1][s]          ->GetXaxis()->SetTitle("All Sectors                              U [cm]");
//					ECv[1][s]          ->GetXaxis()->SetTitle("All Sectors                              V [cm]");
//					ECw[1][s]          ->GetXaxis()->SetTitle("All Sectors                              W [cm]");
				}
//				enphe[s] = (TH1F*) nphe[0][s]->Clone();
//				enphe[s]->SetDirectory(0);
//				for(int b=0; b<enphe[s]->GetNbinsX(); b++) {
//					enphe[s]->SetBinContent(b, 0);
//				}
			}
			
			// utility histos
//			nphe_phi = (TH2F*)f.Get("nphe_phi");
//			nphe_phi ->SetDirectory(0);

			for(int s=0; s<7; s++) {
//				monitor[0][s] = (TH1F*)f.Get(Form("monitor1_sect%d", s+1));
//				monitor[1][s] = (TH1F*)f.Get(Form("monitor2_sect%d", s+1));
//				monitor[2][s] = (TH1F*)f.Get(Form("monitor3_sect%d", s+1));
//				monitor[0][s] ->SetDirectory(0);
//				monitor[1][s] ->SetDirectory(0);
//				monitor[2][s] ->SetDirectory(0);
			}

			for(int c=0; c<4; c++) {
//				ECpos[c] = (TH2F*)f.Get(Form("ECpos_%s", cut[c].c_str()));
//				ECpos[c] ->SetDirectory(0);
//				ECpos[c] ->GetXaxis()->SetTitle("EC Track x Position                 [cm]");
//				ECpos[c] ->GetYaxis()->SetTitle("EC Track y Position         [cm]");
			}
//			ECpos[4] = (TH2F*)f.Get("ECpos_UVW_cut");
//			ECpos[4] ->SetDirectory(0);

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
	cout << endl << " > Opening parameter file " << filename << endl << endl;
	if(!parfile) {
		cout << " File " <<  filename << " could not be opened. " << endl;
		cout << " Specify parameters file with -PARS_FILE=filename. Exiting. " << endl;
		exit(0);
	}
	
	string line;
	string addinfo;
	for(int s=0; s<6; s++) {
		ecp_mean_a[s] = 0;
		ecp_mean_b[s] = 0;
		ecp_mean_c[s] = 0;
		ecp_mean_d[s] = 0;
		ecp_sigm_a[s] = 0;
		ecp_sigm_b[s] = 0;
		ecp_sigm_c[s] = 0;
		ecp_sigm_d[s] = 0;

		for(int p=0; p<18; p++) {
			cc_match_low[s][p] = 0;
		}

		for(int p=0; p<36; p++) {
			cc_timing_low[s][p] = 0;
		}
	}
	
	while(getline( parfile, line)) {
		istringstream cuts(line);

		while(!cuts.eof()) {
			string al;
			cuts >> al;
			if(al == "MINP:") {
				cuts >> p_ec_threshold;
				addinfo = " > Min momentum as given by the EC Threshold in mV: " + stringify(p_ec_threshold) +  " GeV.";
				addInfos.push_back(addinfo);
			} else if(al == "NPHE:") {
				addInfos.push_back(" > Min Number of photoelectrons in CC: ");
				addinfo  = "" ;
				for(int s=0; s<6; s++)
				{
					cuts >> min_nphe[s];
					addinfo += "   S" +  stringify(s+1);
					addinfo += ": "     + stringify(min_nphe[s]);
				}
				addInfos.push_back(addinfo);
			} else if(al == "ECIT:") {
				for(int s=0; s<6; s++) cuts >> ecop_vs_ecip_a[s];
			} else if(al == "ECSL:") {
				for(int s=0; s<6; s++) cuts >> ecop_vs_ecip_b[s];
			} else if(al == "UVWC:") {
				cuts >> umin >> umax >> vmax >> wmax;
				addinfo  =  " > UVW Positions (cm): ";
				addInfos.push_back(addinfo);
				addinfo  = "   Umin=" + stringify(umin);
				addinfo += ",  Umax=" + stringify(umax);
				addinfo += ",  Vmax=" + stringify(vmax);
				addinfo += ",  Wmax=" + stringify(wmax);
				addInfos.push_back(addinfo);
			} else if(al == "INTO:") {
				addInfos.push_back(" > Ein/Etot: ");
				addinfo  = "" ;
				for(int s=0; s<6; s++)
				{
					cuts >> min_ecit[s];
					addinfo += "   S" +  stringify(s+1);
					addinfo += ": " + stringify(min_ecit[s]);
				}
				addInfos.push_back(addinfo);
			} else if(al == "SFMA:") { // Sampling Fraction
				for(int s=0; s<6; s++) cuts >> ecp_mean_a[s];
			} else if(al == "SFMB:") {
				for(int s=0; s<6; s++) cuts >> ecp_mean_b[s];
			} else if(al == "SFMC:") {
				for(int s=0; s<6; s++) cuts >> ecp_mean_c[s];
			} else if(al == "SFMD:") {
				for(int s=0; s<6; s++) cuts >> ecp_mean_d[s];
			} else if(al == "SFSA:") {
				for(int s=0; s<6; s++) cuts >> ecp_sigm_a[s];
			} else if(al == "SFSB:") {
				for(int s=0; s<6; s++) cuts >> ecp_sigm_b[s];
			} else if(al == "SFSC:") {
				for(int s=0; s<6; s++) cuts >> ecp_sigm_c[s];
			} else if(al == "SFSD:") {
				for(int s=0; s<6; s++) cuts >> ecp_sigm_d[s];
			} else if(al == "SFNS:") {
				cuts >> NSIGMAS[0] >> NSIGMAS[1];
			} else if(al == "CCMA:") { // CC Matching
				for(int s=0; s<6; s++) cuts >> cc_match_mean_a[s];
			} else if(al == "CCMB:") {
				for(int s=0; s<6; s++) cuts >> cc_match_mean_b[s];
			} else if(al == "CCMC:") {
				for(int s=0; s<6; s++) cuts >> cc_match_mean_c[s];
			} else if(al == "CCMS1:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[0][p];
			} else if(al == "CCMS2:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[1][p];
			} else if(al == "CCMS3:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[2][p];
			} else if(al == "CCMS4:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[3][p];
			} else if(al == "CCMS5:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[4][p];
			} else if(al == "CCMS6:") {
				for(int p=0; p<18; p++) cuts >> cc_match_low[5][p];
			} else if(al == "CCNS:") {
				cuts >> CC_NSIGMAS[0] >> CC_NSIGMAS[1];
			} else if(al == "CCTS1:") { // CC Timing
				for(int p=0; p<36; p++) cuts >> cc_timing_low[0][p];
			} else if(al == "CCTS2:") {
				for(int p=0; p<36; p++) cuts >> cc_timing_low[1][p];
			} else if(al == "CCTS3:") {
				for(int p=0; p<36; p++) cuts >> cc_timing_low[2][p];
			} else if(al == "CCTS4:") {
				for(int p=0; p<36; p++) cuts >> cc_timing_low[3][p];
			} else if(al == "CCTS5:") {
				for(int p=0; p<36; p++) cuts >> cc_timing_low[4][p];
			} else if(al == "CCTS6:") {
				for(int p=0; p<36; p++) cuts >> cc_timing_low[5][p];
			} else if(al == "CCTNS:") {
				cuts >> CC_T_NSIGMAS;
			}
		}
	}
	
	addInfos.push_back(" > ec_o/p vs ec_i/p curve: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  a: "  + stringify(ecop_vs_ecip_a[s]);
		addinfo += "  b: "  + stringify(ecop_vs_ecip_b[s]);
		addInfos.push_back(addinfo);
	}
	
	addInfos.push_back(" > Sampling Fraction MEAN pars: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  a: "  + stringify(ecp_mean_a[s]);
		addinfo += "  b: "  + stringify(ecp_mean_b[s]);
		addinfo += "  c: "  + stringify(ecp_mean_c[s]);
		addinfo += "  d: "  + stringify(ecp_mean_d[s]);
		addInfos.push_back(addinfo);
	}
	addInfos.push_back(" > Sampling Fraction SIGMA pars: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  a: "  + stringify(ecp_sigm_a[s]);
		addinfo += "  b: "  + stringify(ecp_sigm_b[s]);
		addinfo += "  c: "  + stringify(ecp_sigm_c[s]);
		addinfo += "  d: "  + stringify(ecp_sigm_d[s]);
		addInfos.push_back(addinfo);
	}
	addInfos.push_back(" > Number of Sigmas for upper Sampling Fraction Curve: " + stringify(NSIGMAS[0]));
	addInfos.push_back(" > Number of Sigmas for lower Sampling Fraction Curve: " + stringify(NSIGMAS[1]));

	addInfos.push_back(" > CC Theta Matching MEAN pars: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  a: "  + stringify(cc_match_mean_a[s]);
		addinfo += "  b: "  + stringify(cc_match_mean_b[s]);
		addinfo += "  c: "  + stringify(cc_match_mean_c[s]);
		addInfos.push_back(addinfo);
	}
	addInfos.push_back(" > CC Theta Matching SIGMA lower limits: ");
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  ";
		for(int p=0; p<18; p++)
			addinfo += "  " + stringify(cc_match_low[s][p]);
		addInfos.push_back(addinfo);
	}
	addInfos.push_back(" > Number of Sigmas for upper CC Theta Matching Curve: " + stringify(CC_NSIGMAS[0]));
	addInfos.push_back(" > Number of Sigmas for lower CC Theta Matching Curve: " + stringify(CC_NSIGMAS[1]));
	addInfos.push_back(" > CC Time Matching Lowe Limits: ");
	addInfos.push_back(" > Number of Sigmas for Time Matching Lower Limit: " + stringify(CC_T_NSIGMAS));
	for(int s=0; s<6; s++) {
		addinfo  = "   S" + stringify(s+1);
		addinfo += "  ";
		for(int p=0; p<36; p++)
			addinfo += "  " + stringify(cc_timing_low[s][p]);
		addInfos.push_back(addinfo);
	}

	//	for(unsigned int si=0; si<addInfos.size(); si++)
	//		cout << addInfos[si] << endl;
}

void cpars::write_vars()
{
	ofstream parfile(parameter_file.c_str());
	cout << endl << " Opening output parameter file " << parameter_file << endl;

    parfile << "NPHE: " ;
    for(int s=0; s<6; s++) parfile << min_nphe[s] << " ";
    parfile << "                     # Number of Photoelectrons"  << endl;

    parfile << "CCNS: " ;
    parfile << CC_NSIGMAS[0] << " " << CC_NSIGMAS[1] ;
    parfile << "                                    # CC Theta Matching number of sigmas for upper/lower curve" << endl;

    parfile << "CCMA: " ;
    for(int s=0; s<6; s++) {parfile.width(12) ; parfile << cc_match_mean_a[s] << " ";}
    parfile << "         # CC Matching mean A: a + bx + cx2" << endl;

    parfile << "CCMB: " ;
    for(int s=0; s<6; s++) {parfile.width(12) ; parfile << cc_match_mean_b[s] << " ";}
    parfile << "         # CC Matching mean B: a + bx + cx2" << endl;

    parfile << "CCMC: " ;
    for(int s=0; s<6; s++) {parfile.width(12) ; parfile << cc_match_mean_c[s] << " ";}
    parfile << "         # CC Matching mean C: a + bx + cx2" << endl;

    parfile << "CCMS1: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[0][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 1" << endl;

    parfile << "CCMS2: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[1][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 2" << endl;

    parfile << "CCMS3: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[2][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 3" << endl;

    parfile << "CCMS4: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[3][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 4" << endl;

    parfile << "CCMS5: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[4][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 5" << endl;

    parfile << "CCMS6: " ;
    for(int p=0; p<18; p++) {parfile.width(9) ; parfile << cc_match_low[5][p] << " ";}
    parfile << "     # CC Theta Matching Lower Limits for Sector 6" << endl;

    parfile << "CCTNS: " ;
    parfile << CC_T_NSIGMAS;
    parfile << "                                     # CC Timing number of sigmas for lower limit" << endl;

    parfile << "CCTS1: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[0][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 1" << endl;

    parfile << "CCTS2: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[1][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 2" << endl;

    parfile << "CCTS3: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[2][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 3" << endl;

    parfile << "CCTS4: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[3][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 4" << endl;

    parfile << "CCTS5: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[4][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 5" << endl;

    parfile << "CCTS6: " ;
    for(int p=0; p<36; p++) {parfile.width(9) ; parfile << cc_timing_low[5][p] << " ";}
    parfile << "     # CC Timing Lower Limits for Sector 6" << endl;





	parfile << "MINP: " ;
	parfile << p_ec_threshold;
	parfile << "                                # Min momentum as given by the EC Threshold in mV" << endl;
	

	parfile << "ECIT: " ;
	for(int s=0; s<6; s++) {parfile.width(5) ; parfile << ecop_vs_ecip_a[s] << " ";}
	parfile << "   # intercept on the curve ecop_vs_ecip" << endl;
	
	parfile << "ECSL: " ;
	for(int s=0; s<6; s++) {parfile.width(5) ; parfile << ecop_vs_ecip_b[s] << " ";}
	parfile << "   # slope on the curve ecop_vs_ecip" << endl;
	
	parfile << "UVWC: " ;
	parfile << umin << " " << umax << " " << vmax << " " << wmax << " ";
	parfile << "                        # Umin, Umax, Vmax, Wmax" << endl;

	parfile << "INTO: " ;
	for(int s=0; s<6; s++) parfile << min_ecit[s] << " ";
	parfile << "         # EC inner/total cut" << endl;

	parfile << "SFNS: " ;
	parfile << NSIGMAS[0] << " " << NSIGMAS[1] ;
	parfile << "                                  # sampling fraction number of sigmas for upper/lower curve" << endl;
	


	parfile << "SFMA: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_mean_a[s] << " ";}
	parfile << "         # sampling fraction mean A: a + bx + cx2 + dx3" << endl;

	parfile << "SFMB: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_mean_b[s] << " ";}
	parfile << "         # sampling fraction mean B: a + bx + cx2 + dx3" << endl;

	parfile << "SFMC: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_mean_c[s] << " ";}
	parfile << "         # sampling fraction mean C: a + bx + cx2 + dx3" << endl;

	parfile << "SFMD: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_mean_d[s] << " ";}
	parfile << "         # sampling fraction mean D: a + bx + cx2 + dx3" << endl;

	parfile << "SFSA: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_sigm_a[s] << " ";}
	parfile << "         # sampling fraction sigma A: a + bx + cx2 + dx3" << endl;

	parfile << "SFSB: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_sigm_b[s] << " ";}
	parfile << "         # sampling fraction sigma B: a + bx + cx2 + dx3" << endl;

	parfile << "SFSC: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_sigm_c[s] << " ";}
	parfile << "         # sampling fraction sigma C: a + bx + cx2 + dx3" << endl;

	parfile << "SFSD: " ;
	for(int s=0; s<6; s++) {parfile.width(12) ; parfile << ecp_sigm_d[s] << " ";}
	parfile << "         # sampling fraction sigma D: a + bx + cx2 + dx3" << endl;

	



}

double cpars::Mean(double p, int sector)
{
	int s = sector - 1;
	
	return ecp_mean_a[s] +
	ecp_mean_b[s]*p +
	ecp_mean_c[s]*p*p +
	ecp_mean_d[s]*p*p*p;
}

double cpars::Sigma(double p, int sector)
{
	int s = sector - 1;

	return ecp_sigm_a[s] +
	ecp_sigm_b[s]*p +
	ecp_sigm_c[s]*p*p +
	ecp_sigm_d[s]*p*p*p;
}

double cpars::ecp_limit(double p, int sector, int which)
{
	if(which >= 0) return Mean(p, sector) + NSIGMAS[0]*Sigma(p, sector);
	else           return Mean(p, sector) - NSIGMAS[1]*Sigma(p, sector);
}

double cpars::CC_Mean(double segm, int sector)
{
	int s = sector - 1;
	
	return cc_match_mean_a[s] +
	cc_match_mean_b[s]*segm +
	cc_match_mean_c[s]*segm*segm;
}

double cpars::CC_Sigma(double segm, int sector)
{
	int s = sector - 1;

	int iseg = (int) segm - 1;
	return cc_match_low[s][iseg];
	
}

double cpars::CC_limit(double segm, int sector, int which)
{
	if(which >= 0) return CC_Mean(floor(segm), sector) + CC_NSIGMAS[0]*CC_Sigma(segm, sector);
	else           return CC_Mean(floor(segm), sector) - CC_NSIGMAS[1]*CC_Sigma(segm, sector);
}

















