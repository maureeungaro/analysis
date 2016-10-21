{
	
//	string pars_file = "vertex_par.txt";
//	string root_file = "pass4.root";
//	int GSIM         = 0;

	string pars_file = "vertex_par.txt";
	string root_file = "gsim.root";
	int GSIM         = 1;

	gInterpreter->AddIncludePath("/opt/projects/muEvent/src");
	#include "utilities.h"

	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_vertex.C");
	gROOT->LoadMacro("ana/show_2D_vertex.C");
	
	string PRINT   = "";
		
	chistos H(root_file, 1);
	cpars   Pars(pars_file);
	
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Vertex Correction, Selection", "");
	bar->AddButton("","");
	bar->AddButton("Show z vertex",            "show_vertex()");
	bar->AddButton("Show 2D vertex",           "show_2D_vertex()");
	bar->AddButton("","");
	bar->AddButton("Print all vertex plots",   "print_all()");
	bar->AddButton("","");
	bar->Show();
}











