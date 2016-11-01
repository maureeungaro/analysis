{

	gInterpreter->AddIncludePath("/opt/projects/analysis/binning");
	gInterpreter->AddIncludePath("/opt/projects/analysis/meson_histos/src");
	gInterpreter->AddIncludePath("/opt/projects/analysis/acceptance/acc_histos/src");
	gInterpreter->AddIncludePath("/opt/projects/analysis/ana_histos/src");

	string  what = "pi0";
	string swhat = "#pi^{0}";
	
	#include "bin.cc"
	#include "/opt/projects/analysis/meson_histos/src/common_info.h"
	#include "/opt/projects/analysis/meson_histos/src/common_info.cc"
	#include "/opt/projects/analysis/acceptance/acc_histos/src/common_info.h"
	#include "/opt/projects/analysis/acceptance/acc_histos/src/common_info.cc"
	#include "/opt/projects/analysis/ana_histos/src/common_info.cc"
	#include "/opt/projects/analysis/ana_histos/src/rebin.cc"
	
	gROOT->LoadMacro("utils.C");
	
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	string bindex[3]  = {"b24", "b48", "b96"};
	string sbindex[3] = { "24",  "48",  "96"};
	int BIN          = 0;
	
	int WW       = 0;
	int QQ       = 0;
	string PRINT = "";
	
	
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	
	meson_chistos *MH = new meson_chistos("/arena1/analysis_data/meson_histos.root", 1);
	MH->slice();
	
	acc_chistos *AH = new acc_chistos("/arena1/analysis_data/acceptance.root", 1);
	AH->calc_acc();
	AH->slice();
	AH->style();
	
	ana_chistos *ANA_H = new ana_chistos("/arena1/analysis_data/ana_histos.root", 2);
	ANA_H->divide_by_acc_cor(AH->pi0_acc);
	ANA_H->slice_and_style(1);
	
	bar = new TControlBar("vertical", "Meson Histograms  by Maurizio Ungaro");
	bar->AddButton("","");
	bar->AddButton("Change Q2","change_q2()");
	bar->AddButton("Change W", "change_w()");
	bar->AddButton("","");
	bar->AddButton("Show yields as function of theta",          "show_theta()");
	bar->AddButton("Show yields as function of phi",            "show_phi()");
	bar->AddButton("Show yields as function of thetaphi",       "show_thetaphi()");
	bar->AddButton("","");
	bar->AddButton("Change Quantity",                           "change_what()");
	bar->AddButton("Change Binning",                            "change_binning()");
	bar->AddButton("","");
	bar->AddButton("Show corrected yields as function of phi",  "show_cphi()");
	bar->AddButton("","");
	bar->AddButton("Print all phi",                             "print_all_phi()");
	bar->AddButton("","");
	bar->Show();



}
