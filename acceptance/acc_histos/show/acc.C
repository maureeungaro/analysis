{
	gInterpreter->AddIncludePath("/opt/projects/muEvent/binning");
	gInterpreter->AddIncludePath("/opt/projects/analysis/acceptance/acc_histos/src");
	gInterpreter->AddIncludePath("/opt/projects/muEvent/src");
	#include "bin.cc"
	#include "common_info.cc"

	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	
	string  what[2] = {"Acceptance Correction", "Gen / Rec Events" };
	string swhat[2] = {       "acc"           ,      "genrec"      };
	int WHAT        = 0;  // 0 = acceptance; 1 = gen and rec

	string bindex[3] = {"b24", "b48", "b96"};
	int BIN          = 0;  

	string oindex[3] = {     "E", "hist 9c", "hist"};
	string sindex[3] = {"errors",    "line", "hist"};
	int HOPT         = 0;

	int WW       = 0;
	int QQ       = 0;
	string PRINT = "";

	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	
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
	bar->AddButton("Change hist options",                          "change_hoption()");
	bar->AddButton("","");
	bar->AddButton("Print all",                                    "print_all()");
	bar->AddButton("","");
	bar->Show();

	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q acc.C


	print_all();
}
