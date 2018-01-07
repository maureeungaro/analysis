{
	#include <iomanip>
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	
	const double TWINDOW = 248E-9;
	TH1F *HNHITS;  // contains the number of hits
	int NHITS ;
					
	bool recalc = 1; // 1 will refill all histos - 0 will open the outputf file as input
				     // convention: filename is target.root
	
	const int NTARGET       = 7;
	string starget[NTARGET] = { "noShield", "thick50", "thick100", "thick150", "thick200", "thick300", "thick500" };
	Color_t colors[NTARGET] = {    kBlue-7,      kRed,      kBlue,     kGreen,     kRed+4,     kBlack, kGreen - 4 };
	int TARGET = 0;

	// deposited energy cut
	// An MIP releases 108 KeV - or 240000 electrons
	// That's 222.2 electrons / KeV
	// Qnoise is 4000 electrons
	const int NENERGY    = 3;
	string EDEP[NENERGY]  = {"totEdep >= 0.00", "totEdep > 0.015", "totEdep > 0.03"};
	string SEDEP[NENERGY] = {    "nocut"   ,    "15KeV"   ,   "30KeV"    };
	double  Qth[NENERGY] = {        0      ,     2220     ,     4440     };
	const double Qn      = 2400;
	int ENERGY           = 0;

	// layers
	// last layer represents one chip in one layer
	const int nreg  = 3; 
	const int nbstl = 2*nreg + nreg + nreg;  // 2 layers of silicon for each region. Only one region considered for the chips and the regulators 
	string  lname[nbstl]   = { "1a", "1b", "2a", "2b", "3a", "3b", "chip_r1", "chip_r2", "chip_r3", "reg_r1", "reg_r2", "reg_r3"};
	int nmodules[nbstl]    = {  10 ,  10 ,  14 ,  14 ,  18 ,  18 ,       20 ,       28 ,       36 ,      20 ,      28 ,      36};
	
	
	
	int LAYER  = 1;
	
	// CHIP NUMBERS:
	// weight = 2.33 g/cm^3 * 0.5 cm * 0.75 cm * 0.03 cm = 26 mg
	// area = 0.5 cm * 0.75 cm = 0.375 cm^2
	double chip_area   = 0.375;   // chip size in cm2
	double chip_weight = 0.026;   // chip weight in grams
	// these dimensions are used to identify the region for the chips
	double chip_minz[nreg] = {-240, -200, -160};
	double chip_maxz[nreg] = {-220, -180, -140};
	
	// Regulators NUMBERS:
	// weight = 2.33 g/cm^3 * 0.3 cm * 0.3 cm * 0.1 cm = 21 mg
	// area = 0.3 cm * 0.3 cm = 0.09 cm^2
	double reg_area   = 0.09;    // reg size in cm2
	double reg_weight = 0.021;   // reg weight in grams
	// these dimensions are used to identify the region for the regulators
	double reg_minz[nreg] = {-460, -420, -380};
	double reg_maxz[nreg] = {-450, -410, -370};


	// particles
	const int pnum  = 9;
	string  pname[pnum] = { "noise", "pi-"     , "e-"    , "gamma"  ,  "n"  ,   "e+"   ,   "pi+"   ,  "p" , "all" };  // particles names - to be used in H names
	string  pnaml[pnum] = { "noise", " #pi^{-}", " e^{-}", " #gamma",  "n"  ,  "e^{+}" , "#pi^{+}" ,  "p" , "all" };  // particles names - for labels
	int       pid[pnum] = {    0   ,   -211    ,   11    ,    22    , 2112  ,   -11    ,    211    , 2212 ,     0 };  // particle IDs

	// criteria for particle ID
	string pcut[pnum] = {"1",
	                     "(pid == -211  || mpid == -211)",
	                     "(pid == 11    || (mpid == 11  && mpid != 22))",
	                     "(pid == 22    || (mpid == 22  && mpid != 11))",
	                     "(pid == 2112  || mpid == 2112)",
	                     "(pid == -11   || mpid == -11)",
	                     "(pid == 211   || mpid == 211)",
	                     "(pid == 2212  || mpid == 2212)",
	                     "1"};

	string PRINT = "";   // Print on Image File

	double sweight  = 3.26;          // 1 sensor weight in grams
	double sarea    = 46.88;         // 1 sensor area, in cm^2
	double rad      = 6.24E7;        // MeV per Kg
	double mrad     = 6.24E1;        // GeV per gram
	double one_year = 60*60*24*365;  // one year in seconds
	
	// energy distributions
	const int Nbins = 4000;
	TH1F *bst_edep[nbstl][pnum][NENERGY][NTARGET];
	TH1F *edep[2][NTARGET];  // 0 = e.m. 1 = hadronic

	// rates histos
	TH1F *bst_pr[nbstl][NENERGY][NTARGET];

	// rate numbers
	double Hrate_bst[nbstl][NENERGY][NTARGET][2]; // 0 = e.m. rate, 1 = hadronic rate
	
	double erate_bst[pnum][nbstl][NTARGET];    // total energy deposited (GeV) / s
	double enrat_bst[pnum][nbstl][NTARGET];    // total energy flux (GeV) / s cm2
	double drate_bst[pnum][nbstl][NTARGET];    // total dose rate (mrad) / s
	double dnrat_bst[pnum][nbstl][NTARGET];    // total dose flux (mrad) / s cm2
	double dryat_bst[pnum][nbstl][NTARGET];    // total dose rate (rad) / year
	double dnyra_bst[pnum][nbstl][NTARGET];    // total dose flux (rad) / year cm2

	// kinetic energy ditributions. Index is layer, particle type fpname, target
	int  NEbins = 20000;
	TH1F *bst_E[nbstl][4][NTARGET];       //  e-, pion, neutron, proton
	TH1F *bst_NE[15][4][NTARGET];         //  normalized particle rates
	TH1F *bst_NNE[15][4][NTARGET];        //  normalized neutron equivalent plots
	
	// neutron equivalent rates tables
	string fpname[4] = {      "e-" ,      "pi" ,       "n" ,       "p" };
	double fmass[4]  = {0.54857990 , 139.57018 , 939.56536 , 938.27203 };
	int fpid[4]      = {         2 ,         1 ,         4 ,         7 };
	double min_e_induced_damage[4][15];   // first index: e-, pion, neutron, proton
	double max_e_induced_damage[4][15];   // second index: energy range
	double induced_damage[4][15];
	double n_equivalent_e[nbstl][4][15];  // equivalent neutron dose for each energy, per particle and layer

	gROOT->LoadMacro("utils.C");
	gROOT->LoadMacro("bst_rates.C");
	gROOT->LoadMacro("show_BST_rates.C");

	init_induced_damage();
	
	for(int t=0; t<NTARGET; t++)
		init_bst_histos(Form("/volatile/clas12/ungaro/clas12/root/%s.root", starget[t].c_str()), t);
	

	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("SVT Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show BST Rates",         "show_bst_rates()");
	bar->AddButton("Show BST Event",         "show_bst_event()");
	bar->AddButton("Show all Target Rates",  "show_all_bst_rates()");
	bar->AddButton("Show all Target Event",  "show_all_bst_event()");
	bar->AddButton("","");
	bar->AddButton("Change Layer",     "change_layer()");
	bar->AddButton("Change Energy",    "change_energy()");
	bar->AddButton("Change Target",    "change_target()");
	bar->AddButton("","");
	bar->AddButton("Show Energy Distribution",        "show_energy(0)");
	bar->AddButton("Show Energy Distribution Zoomed", "show_energy(10)");
	bar->AddButton("","");
	bar->AddButton("Log Rates in Layer",        "show_rates_in_layer()");
	bar->AddButton("Log Rates in all Layers",   "show_rates_in_layers()");
	bar->AddButton("","");
	bar->AddButton("Print all Rates",   "print_all_rates()");
	bar->AddButton("Print all Events",  "print_all_events()");
	bar->AddButton("","");
	bar->AddButton("Print all targets Rates",   "print_all_targets_rates()");
	bar->AddButton("Print all targets Events",  "print_all_targets_events()");
	bar->AddButton("","");
	bar->Show();
	
}


