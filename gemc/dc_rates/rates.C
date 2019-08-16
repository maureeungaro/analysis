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
	
	
	const int NCONF      = 2;
	string sconf[NCONF]  = { "clas12", "clas12VE", };
	double factor[NCONF] = {   1, 1};  // additional factor to scale the different configurations

      	

	int CONF             = 0;
	
	// deposited energy cut
	//	const int NENERGY     = 2;
	//	string EDEP[NENERGY]  = {"totEdep >= 0.0", "totEdep > 0.00005"} ;
	//	string SEDEP[NENERGY] = {"Any totEdep",    "totEdep > 50 eV"} ;
	//	int ENERGY            = 1;
	const int NENERGY     = 1;
	string EDEP[NENERGY]  = {"totEdep > 0.00005"} ;
	string SEDEP[NENERGY] = {"totEdep > 50 eV"} ;
	int ENERGY            = 0;
	
	// sectors
	const int NSECT = 6;
	int SECT        = 0;
		
	// vertex locations
	const int NZONES     = 4;
	string SZONE[NZONES] = {"target", "beampipe", "torus", "all"}
	double zlimits[3][2][NZONES];  // r,z  --  min,max  --  zone
	int ZONE = 0;
	
	
	// for z-vertex only: particle flavors
	const int NPART     = 6;
	string SPART[NPART] = {"all", "electrons",   "gammas" ,                     "pions",     "protons",                                                             "other"};
	string pcut[NPART]  = {  "1", "pid == 11", "pid == 22", "pid == 211 || pid == -211", "pid == 2212", "pid != 11 && pid != 1 && pid != 211 && pid != -211 && pid != 2212"};

	int PART = 0;
	
	
	// region for vertex locations
	const int NREG     = 3;
	string sreg[NREG] = {"reg1", "reg2", "reg3"}
	int REG = 0;
	
	// near target
	zlimits[0][0][0] = -10;    zlimits[0][1][0] =  150;
	zlimits[2][0][0] = -100;   zlimits[2][1][0] = 1000;
	
	// beampipe
	zlimits[0][0][1] = -100;   zlimits[0][1][1] = 1400;
	zlimits[2][0][1] = -100;   zlimits[2][1][1] = 1600;
	
	// torus
	zlimits[0][0][2] = -200;    zlimits[0][1][2] = 1500;
	zlimits[2][0][2] = 2500;   zlimits[2][1][2] = 6000;
	
	// all
	zlimits[0][0][3] = -100;   zlimits[0][1][3] = 2000;
	zlimits[2][0][3] = -100;   zlimits[2][1][3] = 3000;
	
	
	string PRINT = "";   // Print on Image File
	
	// 2D occupancy histos: 2D for each sector, wire vs layer
	TH2F *dc_pro[NSECT][NENERGY][NCONF];
	TH2F *dc_occ[NSECT][NENERGY][NCONF];
	
	// 1D summary occupancy histo for the 3 regions
	TH1F *dc_occ_summary[3][NENERGY][NCONF];

	TH1F *dc_procID[NCONF];             // process ID / region
	TH2F *dc_procIDvsLayer[NCONF];      // process ID vs Layer
	TH2F *dc_procIDvsZ[3][NCONF];       // process ID vs VZ - for each region
	TH2F *dc_procIDvspid[NCONF];        // process ID vs pid
	TH2F *dc_procIDvsEdep[NCONF];       // process ID vs Edep
	TH2F *dc_procIDvsTrackE[3][NCONF];  // process ID vs track energy - for 3 track energy ranges: < 4000, <300, <30, <1

	
	// Vertex histos
	TH2F *dc_ver[NENERGY][NCONF][NZONES][NREG];
	TH1F *dc_zver[NENERGY][NCONF][NREG][NPART];
	
	TH2F *twindscale;
	
	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("init.C");
	gROOT->LoadMacro("show.C");
	
	for(int c=0; c<NCONF; c++)
		init_dc_histos(Form("/volatile/clas12/ungaro/clas12/root/added/%s.root", sconf[c].c_str()), c);
		
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("DC Occupancy Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show DC 2D Occupancy",       "show_dc_occ()");
	bar->AddButton("Show Integrated Occupancy",  "show_dc_int_occ()");
	bar->AddButton("","");
	bar->AddButton("Show Vertex",                "show_vertex()");
	bar->AddButton("Show Z Vertex",              "show_zvertex()");
	bar->AddButton("","");
	bar->AddButton("Change Sector",              "change_sector()");
	bar->AddButton("Change Energy",              "change_energy()");
	bar->AddButton("Change Configuration",       "change_conf()");
	bar->AddButton("Change Zone",                "change_zone()");
	bar->AddButton("Change Region",              "change_region()");
	bar->AddButton("","");
	bar->AddButton("Show Process ID",             "show_procID()");
	bar->AddButton("Show Process ID vs SL",       "show_procvsL()");
	bar->AddButton("Show Process ID vs Z",        "show_procvsZ()");
	bar->AddButton("Show Process ID vs pid",      "show_procvspid()");
	bar->AddButton("Show Process ID vs Edep",     "show_procvsedep()");
	bar->AddButton("Show Process ID vs E",        "show_procvse()");
	bar->Show();

	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q rates.C
	print_all();


}


