
void rates()
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
	int NHITS;       // number of events
	
	// for z-vertex only: particle flavors
	const int NPART     = 6;
	string SPART[NPART] = {"all", "electrons",    "gammas",                     "pions",     "protons",                                                             "other"};
	string pcut[NPART]  = {  "1", "pid == 11", "pid == 22", "pid == 211 || pid == -211", "pid == 2212", "pid != 11 && pid != 1 && pid != 211 && pid != -211 && pid != 2212"};

	int PART = 0;
	
	string PRINT = "";   // Print on Image File
	
	// 2D flux histos:
	TH2F *pflux[NPART];
	
	// Vertex histos
	TH1F *pzver[NPART];
	
	
	gROOT->LoadMacro("init.C");
//	gROOT->LoadMacro("show.C");
	
	init_histos(Form("flux.root"));
		
	TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Flux Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show 2D Flux",       "show_flux()");
	bar->AddButton("","");
	bar->AddButton("Show Vertex",                "show_vertex()");
	bar->AddButton("","");
	bar->Show();

	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q rates.C
	// print_all();
}


