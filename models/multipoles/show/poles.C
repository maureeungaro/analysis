{
	gROOT->LoadMacro("show.C");
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("../poles.cc");
	
	const int NMODELS = 9;
	string model[NMODELS] = {"dmt2001", "maid2002", "maid2003", "maid2003woroper", "maid2007", "said2008", "hlee", "janr", "etamaid2001"};
	poles_histos *P[NMODELS];
	string file = "../poles.root";
	
	for(int m=0; m<NMODELS; m++)
		P[m] = new poles_histos(model[m], file);
	
	int iMODEL = 0;
	int ANGMOM = 0;
	int PLUS_M = 1;
 
	int PRINT  = 0;
	
	bar = new TControlBar("vertical", "Models Multiples");
	bar->AddButton("","");
	bar->AddButton("Show S distributions", "show(1)");
	bar->AddButton("Show E distributions", "show(2)");
	bar->AddButton("Show M distributions", "show(3)");
	bar->AddButton("","");
	bar->AddButton("Switch Model",          "switch_model()");
	bar->AddButton("Switch L",              "switch_L()");
	bar->AddButton("Switch +/-",            "switch_plus_minus()");
	bar->AddButton("","");
	bar->AddButton("Print all",             "print_all()");
	bar->AddButton("","");
 
	bar->Show();

	
	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q poles.C
	print_all();

	
	return 0;
	
	
	
}
