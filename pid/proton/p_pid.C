{
	string pars_file = "proton_id_par_gsim.txt";
	string root_file = "gsim.root";
	int GSIM         = 1;

//	string pars_file = "proton_id_par.txt";
//	string root_file = "pass4.root";
//	int GSIM         = 0;

	gInterpreter->AddIncludePath("/opt/projects/muEvent/src");
	#include "utilities.h"

	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/calc_2d.C");
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_dt_vs_mom.C");
	gROOT->LoadMacro("ana/show_mass_beta.C");
	
	string PRINT   = "";
	int SECTOR     = 1;
	const int NDIV = 9;          // divisions of DT and Mass vs momentum
		
	chistos H(root_file, 1);
	cpars   Pars(pars_file);
	
	TH1F *dt_1d[6][NDIV];        // 1 dimensional projections of DT vs momentum, fitted with GAUS + PARABOLE
	double dtmean[6][NDIV];
	double dtsigm[6][NDIV];
	double dtmeane[6][NDIV];
	double dtsigme[6][NDIV];
	TF1 *MySignal[6][NDIV];
	TF1 *MyBackground[6][NDIV];
	TGraphErrors *dt_mean[6] = {0, 0, 0, 0, 0, 0};
	TGraphErrors *dt_sigm[6];
	
	double min_limit_dt = 0.2;   // Fit range x min 
	double max_limit_dt = 5.5;   // Fit range x max
	TF1 *dt_me = new TF1("mass_me", Mean,         0.2, 5.0, 1);
	TF1 *dt_up = new TF1("mass_up", dt_mom_limit, 0.2, 5.0, 3);
	TF1 *dt_dn = new TF1("mass_dn", dt_mom_limit, 0.2, 5.0, 3);
	
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Proton Particle ID", "");
	bar->AddButton("","");
	bar->AddButton("","");
	bar->AddButton("Calculate new DT cuts",         "calc_2d(H.dt_momz[SECTOR-1], H.dt_mom[SECTOR-1])");
	bar->AddButton("Show DT vs mom",                "show_dt_vs_mom()");
	bar->AddButton("Show DT all sectors",           "show_dt_vs_moms()");
	bar->AddButton("","");
	bar->AddButton("Show Beta and Mass vs p",       "show_mass_beta()");
	bar->AddButton("Show Beta vs p all sectors",    "show_betaAll()");
	bar->AddButton("","");
	bar->AddButton("Change Sector",                 "change_sector()");
	bar->AddButton("Print all proton ID plots",     "print_all()");
	bar->AddButton("Calculate all DT cuts",         "calc_all()");
	bar->AddButton("Print everything",              "print_all()");
	bar->AddButton("","");
	bar->AddButton("Write Parameters to File",      "Pars.write_vars(pars_file)");
	bar->AddButton("","");
	bar->Show();
}











