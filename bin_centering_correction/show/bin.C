{

	gInterpreter->AddIncludePath("/opt/work/projects/analysis/binning");
	gInterpreter->AddIncludePath("/opt/work/projects/analysis/bin_centering_correction");
	
	#include "bin.cc"
	#include "binc_histos.h"
	#include "binc_histos.cc"

	const int NMODELS = 6;

	string models[NMODELS]  = {"dmt2001", "maid2002", "maid2003", "maid2003woroper", "maid2007", "said2008"};


	binc_histos *BH[NMODELS];

	bins Bin;
	for(int m=0; m<NMODELS; m++)
	{
		BH[m] = new binc_histos(models[m]);
		BH[m]->init_histos(Form("/arena1/analysis_data/bin_correction/%s_binc_cor.root", models[m].c_str()));
		BH[m]->slice_histos();
		BH[m]->style_histos();
	}
	
	binc_histos *BHC = new binc_histos("systematic");
	BHC->init_histos("/arena1/analysis_data/bin_correction.root");
	BHC->slice_histos();
	BHC->style_histos(5);
	
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("show_syst.C");
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	int WW    = 0;
	int QQ    = 0;
	int Model = 0;
	string PRINT="";

	bar = new TControlBar("vertical", "bin correction  by Maurizio Ungaro");
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
	bar->AddButton("Print all bin corrections plot",         "print_all()");
	bar->AddButton("Print all bin corrections syst",         "print_all_syst()");
	bar->AddButton("","");
	bar->Show();



}
