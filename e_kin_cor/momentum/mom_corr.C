{
	
	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_vertex.C");
	gROOT->LoadMacro("ana/show_2D_vertex.C");
	
	string PRINT   = "";
	int SECTOR     = 1;
		
	chistos H("a.root", 1);
	cpars   Pars("vertex_par.txt");
	
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











