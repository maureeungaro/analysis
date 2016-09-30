// /opt/projects/htmlImageBrowserCreator/pageCreator -addRowTableVariable=cut  -addColumnTableVariable=sector -defaultPlot=img/cut-cctm_sector-1.png -imagesSize="1000 1000"

{
/*	string pars_file = "electron_id_par_gsim.txt";
	string root_file = "electrons_gsim.root";
	int GSIM         = 1;*/
	string pars_file = "electron_id_par.txt";
	string root_file = "pass4.root";
	int GSIM         = 0;
	
	gInterpreter->AddIncludePath("/opt/projects/muEvent/src");
	#include "utilities.h"

	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/init.C");
	gROOT->LoadMacro("ana/show_npe.C");
	gROOT->LoadMacro("ana/calc_cc_match.C");
	gROOT->LoadMacro("ana/show_cc_match.C");
	gROOT->LoadMacro("ana/show_phi_matching.C");
	gROOT->LoadMacro("ana/calc_cc_timing.C");
	gROOT->LoadMacro("ana/show_cc_timing.C");
	gROOT->LoadMacro("ana/show_ecthr.C");
	gROOT->LoadMacro("ana/calc_ecp.C");
	gROOT->LoadMacro("ana/show_ecp.C");
	gROOT->LoadMacro("ana/show_uvw.C");
	gROOT->LoadMacro("ana/show_ecyx.C");
	gROOT->LoadMacro("ana/show_EoEi.C");
	gROOT->LoadMacro("ana/show_EinEtot.C");
	gROOT->LoadMacro("ana/show_summary.C");
	
	Color_t colors[4] = {   kBlack   ,        kBlue       ,        kRed         ,     kGreen+3};
	
	string PRINT   = "png";
	int SECTOR     = 1;
	const int NDIV = 15;       // divisions of sampling fraction	
	
	double no_cc_or_ec[7];
	double hit_cc[7];
	double hit_ec[7];
	double hit_cc_and_ec[7];
	
	chistos H(root_file, 1);
	cpars Pars(pars_file);
	

	// Sampling fraction histos, variables, functions
	TH1F *ecp1d[6][NDIV];      // 1 dimensional projections, fitted with GAUS+PARABOLE
	double ecpmean[6][NDIV];
	double ecpsigm[6][NDIV];
	double ecpmeane[6][NDIV];
	double ecpsigme[6][NDIV];
	TGraphErrors *sf_mean[6];
	TGraphErrors *sf_sigm[6];
	double min_limit_sf = 0.65;  // Fit range x min
	double max_limit_sf = 5.00;  // Fit range x max
	TF1 *sf_me = new TF1("sf_me", Mean,      0.2, 5, 1);
	TF1 *sf_up = new TF1("sf_up", ecp_limit, 0.2, 5, 3);
	TF1 *sf_dn = new TF1("sf_dn", ecp_limit, 0.2, 5, 3);
	
	// CC theta match histos, variables, functions
	TH1F *cc_match1d[6][18];      // 1 dimensional projections, fitted with GAUS+PARABOLE
	double cc_matchmean[6][18];
	double cc_matchsigm[6][18];
	double cc_matchmeane[6][18];
	double cc_matchsigme[6][18];
	TGraphErrors *cc_match_mean[6];
	TGraphErrors *cc_match_sigm[6];
	TF1 *cc_match_me = new TF1("cc_match_me", cc_match_Mean,  1, 19, 1);
	TF1 *cc_match_up = new TF1("cc_match_up", cc_match_limit, 1, 19, 3);
	TF1 *cc_match_dn = new TF1("cc_match_dn", cc_match_limit, 1, 19, 3);
	
	// CC timing histos, variables, functions
	TH1F *cc_timing1d[6][36];      // 1 dimensional projections, fitted with GAUS
	TGraphErrors *cc_timing_low[6];
	
	init();

	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Electron Particle ID", "");
	bar->AddButton("","");
	bar->AddButton("Show number of photoelectrons",            "show_npe();");
	bar->AddButton("Show number of photoelectrons in sector",  "show_npeSingle();");
	bar->AddButton("","");
	bar->AddButton("Calculate new CC theta matching cuts",     "calc_cc_match();");
	bar->AddButton("Show CC theta matching cuts",              "show_cc_match();");
	bar->AddButton("Show CC theta matching cuts each sector",  "show_theta_vs_segms();");
	bar->AddButton("Show CC theta matching cuts all sectors",  "show_theta_vs_segm_all_sectors();");
	bar->AddButton("","");
	bar->AddButton("Show CC phi matching cuts each sector",    "show_phi_match();");
	bar->AddButton("Show CC phi matching cuts all sector",     "show_phi_matchAll();");
	bar->AddButton("","");
	bar->AddButton("Calculate new CC timing cuts",             "calc_cc_timing();");
	bar->AddButton("Show CC timing",                           "show_cc_timing();");
	bar->AddButton("Show CC timing each sector",               "show_cc_timings();");
	bar->AddButton("","");
	bar->AddButton("","");
	bar->AddButton("Calculate new fraction cuts",              "calc_all_ecp();");
	bar->AddButton("Calculate new fraction cuts this sector",  "calc_ecp();");
	bar->AddButton("Show sampling fraction cuts",              "show_ecp();");
	bar->AddButton("Show sampling fraction sector by sector",  "show_ecps();");
	bar->AddButton("Show Sampling Fraction for all sectors",   "show_ecp_all_sectors();");
	bar->AddButton("","");
	bar->AddButton("Show minimum momentum cut",                "show_ecthr();");
	bar->AddButton("","");
	bar->AddButton("Show U",                                   "show_uvw(H.ECu);");
	bar->AddButton("Show V",                                   "show_uvw(H.ECv);");
	bar->AddButton("Show W",                                   "show_uvw(H.ECw);");
	bar->AddButton("Show EC Y vs X",                           "show_ecyx();");
	bar->AddButton("","");
	bar->AddButton("Show EC Eout/p vs Ein/p",                  "show_EoEi();");
	bar->AddButton("Show EC Eout/p vs Ein/p for all sectors",  "show_EoEi_all();");
	bar->AddButton("","");
	bar->AddButton("Show Ein/Etot vs p",                       "show_EinEtot();");
	bar->AddButton("","");
	bar->AddButton("Show Summary",                             "show_summary();");
	bar->AddButton("","");
	bar->AddButton("Change Sector",                            "change_sector();");
	bar->AddButton("Print all electrond ID plots",             "print_all();");
	bar->AddButton("Write Parameters",                         "Pars.write_vars(pars_file);");
	bar->AddButton("","");
	bar->AddButton("","");
	bar->Show();
}











