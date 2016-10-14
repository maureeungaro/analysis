{
	gStyle->SetPalette(1);
	gStyle->SetOptTitle(kWhite);
	gStyle->SetOptStat(kWhite);
	gStyle->SetOptFit(kWhite);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);
	
	gStyle->SetNumberContours(80);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadBorderMode(0);

	bool recalc = 1; // 1 will refill all histos - 0 will open the outputf file as input
	int NHITS; // number of events
	
	
	const int NCONF      = 12;
	string sconf[NCONF]  = {
		"field000",
		"field005",
		"field010",
		"field020",
		"field030",
		"field040",
		"field050",
		"field060",
		"field070",
		"field080",
		"field090",
		"field100"};


	double factor[NCONF] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};  // additional factor to scale the different configurations

	int CONF             = 0;
	// nphe cut
	const int NNPHE     = 2;
	string NPHE[NNPHE]  = {"nphe > 0", "nphe > 10"} ;
	string SNPHE[NNPHE] = {"nphegt0",  "nphegt10"} ;
	int IPHE            = 0;


	string PRINT = "";   // Print on Image File
	
	// 1D nphe histo
	TH1F *npheRates[NNPHE][NCONF];

	
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("init.C");
	gROOT->LoadMacro("show.C");
	
	for(int c=0; c<NCONF; c++)
		init_nphe_histos(Form("/opt/root/%s.root", sconf[c].c_str()), c);
		
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("HTCC Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show NPHE rates",       "showNpheRates()");
	bar->AddButton("","");

	bar->Show();
		
}


