#include "TControlBar.h"
#include "TApplication.h"


// common parameters, analysis classes
#include"ana/parameters.h"

void calc_cc_match() {
    cout << 'asd ' << endl;
    //CCMatch->calc_cc_match(SECTOR);
}
int main(int argc, char **argv)
{
	string pars_file = data_pars_file;
	string root_file = data_root_file;

	// if the first argument is the string 'gsim' then
	// this is simulation
	if (argc > 1) {
		if (string(argv[1]) == "gsim") {
			pars_file = data_pars_file;
			root_file = data_root_file;
			data_label = "gsim";
            GSIM  = 1;
			PRINT = "_gsim.png";
		}
	}


	// load common histos and parameters
	// second parameters instructs to read the root file
	H       = new chistos(root_file, 1);
	Pars    = new cpars(pars_file);

    CCMatch = new CC_Match(H, Pars, PRINT);



	TApplication app("app", &argc, argv);

	TControlBar* bar = new TControlBar("vertical", data_label.c_str());
	bar->AddButton("Electron Particle ID", "");
	bar->AddButton("","");

    // add button to execute  calc_cc_match defined in parameters.h
    bar->AddButton("calc_cc_match", "calc_cc_match");

    bar->AddButton("How to run  ","calc_cc_match()","Instructions for running this macro");

	// bar->AddButton("Calculate new CC theta matching cuts",     "calc_cc_match()");
	////	bar->AddButton("Show CC theta matching cuts",              "show_cc_match();");
	////	bar->AddButton("Show CC theta matching cuts each sector",  "show_theta_vs_segms();");
	////	bar->AddButton("Show CC theta matching cuts all sectors",  "show_theta_vs_segm_all_sectors();");
	////	bar->AddButton("","");
	////	bar->AddButton("Show CC phi matching cuts each sector",    "show_phi_match();");
	////	bar->AddButton("Show CC phi matching cuts all sector",     "show_phi_matchAll();");
	////	bar->AddButton("","");
	////	bar->AddButton("Calculate new CC timing cuts",             "calc_cc_timing();");
	////	bar->AddButton("Show CC timing",                           "show_cc_timing();");
	////	bar->AddButton("Show CC timing each sector",               "show_cc_timings();");
	////	bar->AddButton("Show CC timing all sectors",               "show_cc_timing_all_sectors();");
	////	bar->AddButton("","");
	////	bar->AddButton("Show minimum momentum cut",                "show_ecthr();");
	////	bar->AddButton("Show minimum momentum cut all sectors",    "show_ecthrAll();");
	////	bar->AddButton("","");
	////	bar->AddButton("Calculate new fraction cuts",              "calc_all_ecp();");
	////	bar->AddButton("Calculate new fraction cuts this sector",  "calc_ecp();");
	////	bar->AddButton("Show sampling fraction cuts",              "show_ecp();");
	////	bar->AddButton("Show sampling fraction sector by sector",  "show_ecps();");
	////	bar->AddButton("Show Sampling Fraction for all sectors",   "show_ecp_all_sectors();");
	////	bar->AddButton("","");
	////	bar->AddButton("Show U (all sectors)",                     "show_uvwAll(H.ECu);");
	////	bar->AddButton("Show V (all sectors)",                     "show_uvwAll(H.ECv);");
	////	bar->AddButton("Show W (all sectors)",                     "show_uvwAll(H.ECw);");
	////	bar->AddButton("Show U (single)",                          "show_uvw(H.ECu);");
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
	//	bar->AddButton("Show number of photoelectrons",            "show_npe();");
	//	bar->AddButton("Show number of photoelectrons in sector",  "show_npeSingle();");
	//	bar->AddButton("","");
	//	bar->AddButton("Show Summary",                             "show_summary();");
	//	bar->AddButton("","");
	//	bar->AddButton("Change Sector",                            "change_sector();");
	//	bar->AddButton("Print all electrond ID plots",             "print_all();");
	//	bar->AddButton("Write Parameters",                         "Pars.write_vars(pars_file);");
	bar->AddButton("","");
	bar->Show();
    gROOT->SaveContext();

    app.Run();

	return 0;
}











