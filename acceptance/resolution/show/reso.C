{
	gInterpreter->AddIncludePath("src");
	#include "common_info.cc"

	
	string  what[2] = {"electrons", "protons" };
	int WHAT        = 0;  // 0 = electrons; 1 = protons

	int SECTOR      = 1;
	
	string PRINT = "";

	
	gROOT->LoadMacro("utils.C");
	
	acc_chistos *AH = new acc_chistos("/opt/root/analysis_data/acc.root", 1);
	AH->calc_acc();
	AH->slice();
	AH->style();

	bar = new TControlBar("vertical", "Acceptance Correction  by Maurizio Ungaro");
	bar->AddButton("","");
	bar->AddButton("Change Q2","change_q2()");
	bar->AddButton("Change W", "change_w()");
	bar->AddButton("","");
	bar->AddButton("Show correction as function of phi",           "show_phi()");
	bar->AddButton("","");
	bar->AddButton("Change Quantity",                              "change_what()");
	bar->AddButton("Change Binning",                               "change_binning()");
	bar->AddButton("","");
	bar->AddButton("Print all",                                    "print_all()");
	bar->AddButton("","");
	bar->Show();
}
