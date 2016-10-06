{
	
	string pars_file = "vertex_par.txt";
	string root_file = "vertex_gsim.root";
	int GSIM         = 1;

	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_vertex.C");
	gROOT->LoadMacro("ana/show_2D_vertex.C");
	
	string PRINT   = "";
	int SECTOR     = 1;
		
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











