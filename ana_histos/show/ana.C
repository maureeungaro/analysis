{

	gInterpreter->AddIncludePath("/opt/projects/analysis/binning");
	
	string  what[2]  = {"#pi^{0}", "#pi^{0} data and MC"};
	string  swhat[2] = {"pi0",      "pi0MC"             };

	
	#include "bin.cc"
	#include "/opt/projects/analysis/ana_histos/src/common_info.h"
	#include "/opt/projects/analysis/ana_histos/src/common_info.cc"
	#include "/opt/projects/analysis/acceptance/acc_histos/src/common_info.h"
	#include "/opt/projects/analysis/acceptance/acc_histos/src/common_info.cc"
	#include "/opt/projects/analysis/models/cross_sections_tables/create_histos/mod_histos.h"
	#include "/opt/projects/analysis/models/cross_sections_tables/create_histos/mod_histos.cc"
	
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("show_cs.C");
	gROOT->LoadMacro("show_cs_WQ.C");
	gROOT->LoadMacro("show_sf.C");
	gROOT->LoadMacro("show_sf_W.C");
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	int WW    = 0;
	int QQ    = 0;
	int PH    = 0;
	int WHAT  = 0;   // 0 = pi0 ; 2 = pi0 and MC
	string PRINT="";

	bins Bin;

	// cross sections
	ana_chistos *ANA_H = new ana_chistos("/arena/analysis/pi0/analysis_data/ana_histos.root");
	ANA_H->slice_and_style();
	ANA_H->fill_WQ2_histos();
	ANA_H->fill_WQ2_sfhistos();
	
	// models
	string models[4] = {"maid2003", "maid2003woroper", "maid2007", "said2008"};
	mod_histos  *tH[4];
	for(int m=0; m<4; m++)
	{
		tH[m] = new mod_histos(models[m]);
		tH[m]->define_histos(Form("/arena/analysis/pi0/analysis_data/models/theory_cross_sections/%s.root", models[m].c_str()));
		tH[m]->slice_histos();
		tH[m]->fill_WQ2_histos();
		tH[m]->fit_phis();
		tH[m]->fill_WQ2_sfhistos();
	}
	
	// writing SF table 
	ANA_H->write_sf_table();

	bar = new TControlBar("vertical", "Meson Histograms  by Maurizio Ungaro");
	bar->AddButton("","");
	bar->AddButton("Change Q2", "change_q2()");
	bar->AddButton("Change W",  "change_w()");
	bar->AddButton("Change PH", "change_ph()");
	bar->AddButton("","");
	bar->AddButton("Show cross sections as function of theta",   "show_theta_cs()");
	bar->AddButton("Show cross sections as function of phi",     "show_phi_cs()");
	bar->AddButton("","");
	bar->AddButton("Show cross sections as function of W",       "show_cs_WQ()");
	bar->AddButton("","");
	bar->AddButton("Show structure function LPT",                "show_sf(0)");
	bar->AddButton("Show structure function TT",                 "show_sf(1)");
	bar->AddButton("Show structure function LT",                 "show_sf(2)");
	bar->AddButton("","");
	bar->AddButton("Show structure function LPT vs W",           "show_sf_W(0)");
	bar->AddButton("Show structure function TT vs W",            "show_sf_W(1)");
	bar->AddButton("Show structure function LT vs W",            "show_sf_W(2)");
	bar->AddButton("","");
	bar->AddButton("Change Quantity",                            "change_what()");
	bar->AddButton("","");
	bar->AddButton("Print all CS",                               "print_all_cs()");
	bar->AddButton("Print all SF",                               "print_all_sf()");
	bar->AddButton("Print all CS vs W",                          "print_all_cs_W()");
	bar->AddButton("Print all SF vs W",                          "print_all_sf_W()");
	bar->AddButton("","");
	bar->AddButton("Change Quantity",                            "change_what()");
	bar->AddButton("","");
	bar->Show();



}
