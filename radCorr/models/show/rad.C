{

	gInterpreter->AddIncludePath("/opt/projects/muEvent/binning");
	gInterpreter->AddIncludePath("/opt/projects/analysis/radCorr/models");
	
	#include "bin.cc"
	#include "rad_histos.h"
	#include "rad_histos.cc"

	const int NMODELS = 5;

	string models[NMODELS]  = {"dmt2001", "maid2002", "maid2003", "maid2003woroper", "maid2007"};
	Color_t colors[NMODELS] = { kGreen+1,    kGray+3,      kBlue,              kRed,    kViolet};

	// maid2007 does not have 0.00 cut
	string vcut = "0.08";
	
	rad_histos *RH[NMODELS+1];

	bins Bin;
	for(int m=0; m<NMODELS; m++)
	{
		RH[m] = new rad_histos();
		RH[m]->init_histos(Form("/opt/root/analysis_data/radiative_correction/%s_rad_cor_%s.root", models[m].c_str(), vcut.c_str()));
		RH[m]->slice_histos();
		RH[m]->style_histos(m);
	}
	
	rad_histos *RHC = new rad_histos();
	RHC->init_histos("/opt/root/analysis_data/radiative_correction/radiative_correction.root");
	RHC->slice_histos();
	RHC->style_histos(5);
	
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("show_syst.C");
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	int WW    = 0;
	int QQ    = 0;
	int Model = 0;
	string PRINT="";

	bar = new TControlBar("vertical", "Radiative correction  by Maurizio Ungaro");
	bar->AddButton("","");
	bar->AddButton("Change Q2","change_q2()");
	bar->AddButton("Change W", "change_w()");
	bar->AddButton("","");
	bar->AddButton("Show correction as function of theta",         "show_theta()");
	bar->AddButton("Show correction as function of phi",           "show_phi()");
	bar->AddButton("Show correction as function of theta and phi", "show_thetaphi()");
	bar->AddButton("","");
	bar->AddButton("Change Model", "change_model()");
	bar->AddButton("Show single model as function of theta and phi", "show_thetaphi_single()");
	bar->AddButton("","");
	bar->AddButton("Show syst correction as function of theta",    "show_syst_theta()");
	bar->AddButton("Show syst correction as function of phi",      "show_syst_phi()");
	bar->AddButton("","");
	bar->AddButton("Print all radiative corrections plot",         "print_all()");
	bar->AddButton("Print all radiative corrections syst",         "print_all_syst()");
	bar->AddButton("","");
	bar->Show();


	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q rad.C
	print_all();
	print_all_syst();


}
