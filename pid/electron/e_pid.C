#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"

void e_pid()
{
	string type = "data";
	
	string pars_file = data_pars_file;
	string root_file = data_root_file;
	
	// if the first argument is the string 'gsim' then:
	if ( type == "gsim" ) {
		pars_file = gsim_pars_file;
		root_file = gsim_root_file;
		data_label = "gsim";
		is_simulation = true;
	}

	// load common histos and parameters
	// second parameters instructs to read the root file
	H       = new chistos(root_file, 1);
	Pars    = new cpars(pars_file);

    // CC, EC matching classes
    CCMatch = new CC_Match(H, Pars, PRINT, colors);
    ECMatch = new EC_Match(H, Pars, PRINT, colors);

	// load utils.C
	gROOT->ProcessLine(".L ana/utils.C");

    // last arguments are the positions on screen
	TControlBar* bar = new TControlBar("vertical", data_label.c_str(), 1400, 30);
	bar->AddButton("Electron Particle ID", "");
	bar->AddButton("","");
    bar->AddButton("### Theta Matching ###","");
	bar->AddButton("Calculate new CC theta matching cuts ",   "CCMatch->calc_cc_match(SECTOR)", "Hint");
    bar->AddButton("Show CC theta matching cuts",             "CCMatch->show_cc_theta_match_all_cuts(SECTOR)");
    bar->AddButton("Show CC theta matching",                  "CCMatch->show_cc_theta_match(SECTOR);");
    bar->AddButton("Show CC theta matching cuts all sectors", "CCMatch->show_theta_vs_segm_all_sectors();");
    bar->AddButton("","");

    bar->AddButton("### Phi Matching ###","");
    bar->AddButton("Show CC phi matching",                     "CCMatch->show_phi_match(SECTOR);");
    bar->AddButton("Show CC phi matching cuts all sector",     "CCMatch->show_phi_match_all_sectors();");
    bar->AddButton("","");


    bar->AddButton("### Time Matching ###","");
    bar->AddButton("Calculate new CC timing cuts",             "CCMatch->calc_cc_time_match(SECTOR);");
    bar->AddButton("Show CC timing",                           "CCMatch->show_cc_timing(SECTOR);");
    bar->AddButton("Show CC timing each sector",               "CCMatch->show_cc_timings(SECTOR);");
    bar->AddButton("Show CC timing all sectors",               "CCMatch->show_cc_timing_all_sectors();");
    bar->AddButton("","");

    bar->AddButton("### Time Matching ###","");
    bar->AddButton("Show nphe in sector",                      "CCMatch->show_npe(SECTOR);");
    bar->AddButton("Show nphe all sectors",                    "CCMatch->show_npe_all_sectors();");
    bar->AddButton("","");

    bar->AddButton("### EC Threshold ###","");
    bar->AddButton("Show minimum momentum cut",                "ECMatch->show_ecthr(SECTOR);");
    bar->AddButton("Show minimum momentum cut all sectors",    "ECMatch->show_ecthr_all_sectors();");
    bar->AddButton("","");
    bar->AddButton("### EC Sampling Fraction ###","");
    bar->AddButton("Calculate new fraction cuts this sector",  "ECMatch->calc_sf();");
    bar->AddButton("Show sampling fraction cuts",              "ECMatch->show_sf();");
    bar->AddButton("Show sampling fraction sector by sector",  "ECMatch->show_sfs();");
    bar->AddButton("Show Sampling Fraction for all sectors",   "ECMatch->show_sf_all_sectors();");
    bar->AddButton("","");
	//	bar->AddButton("Show U (all sectors)",                     "show_uvwAll(H.ECu);");
	//	bar->AddButton("Show V (all sectors)",                     "show_uvwAll(H.ECv);");
	//	bar->AddButton("Show W (all sectors)",                     "show_uvwAll(H.ECw);");
	//	bar->AddButton("Show U (single)",                          "show_uvw(H.ECu);");
	//	bar->AddButton("Show V (single)",                          "show_uvw(H.ECv);");
	//	bar->AddButton("Show W (single)",                          "show_uvw(H.ECw);");
	//	bar->AddButton("Show EC Y vs X",                           "show_ecyx();");
	//	bar->AddButton("","");
	//	bar->AddButton("Show EC Eout/p vs Ein/p",                  "show_EoEi();");
	//	bar->AddButton("Show EC Eout/p vs Ein/p for all sectors",  "show_EoEi_all();");
	//	bar->AddButton("","");
	//	bar->AddButton("Show Ein/Etot vs p",                       "show_EinEtot();");
	//	bar->AddButton("Show Ein/Etot vs p all sectors",           "show_EinEtotAll();");
	//	bar->AddButton("","");
	//	bar->AddButton("","");
	//	bar->AddButton("Show Summary",                             "show_summary();");

    bar->AddButton("","");
    bar->AddButton("Switch PRINT",                             "switch_print();");
    bar->AddButton("Change Sector",                            "change_sector();");
    bar->AddButton("","");
	bar->AddButton("Print all electrond ID plots",             "print_all();");
    bar->AddButton("Write Parameters",                         "Pars->write_vars();");
	bar->AddButton("","");
	bar->Show();
	gROOT->SaveContext();

}









