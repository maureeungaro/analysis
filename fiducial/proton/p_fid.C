{
	string pars_file = "fiducial_par.txt";
	string root_file = "gsim.root";
	int GSIM         = 1;

//	string pars_file = "fiducial_par.txt";
//	string root_file = "pass4.root";
//	int GSIM         = 0;

	gInterpreter->AddIncludePath("/opt/projects/muEvent/src");
	#include "utilities.h"

	gROOT->LoadMacro("src/common_info.cc");
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_phi_theta.C");
	gROOT->LoadMacro("ana/show_phis.C");
	gROOT->LoadMacro("ana/show_plane.C");
	gROOT->LoadMacro("ana/slice_plane.C");

	string PRINT     = "";
	int SECTOR       = 1;
	int MOM          = 1;
	int PLANE        = 1;
	int LOGZ         = 0;
	Color_t colors[4] = {   kBlack   ,        kBlue       ,        kRed         ,     kGreen+3};
	
	chistos H(root_file, 1);
	cpars   Pars(pars_file);
	

	// slices in momentum, theta
	TH2F *phi_theta[4][7][H.NDIV_P];
	TH2F *y_x[4][7][3][H.NDIV_P];
	
	// histos for 1D XY divisions.
	const int NDIV_XY = 15;
	TH1F *y_slice[7][5][NDIV_XY];
	double ymin[7][5][NDIV_XY];
	double ymax[7][5][NDIV_XY];
	double ymine[7][5][NDIV_XY];
	double ymaxe[7][5][NDIV_XY];
	TGraphErrors *y_left[7][5];  // current fits
	TGraphErrors *y_right[7][5];
	TF1 *left_para[7][5];  // new fits
	TF1 *rite_para[7][5];
	// histos for 1D XY divisions.
	const int NDIV_T = 24;
	TH1F *phis_befor[7][5][H.NDIV_P][NDIV_T];
	TH1F *phis_after[7][5][H.NDIV_P][NDIV_T];

	// sect - plane - n. of holes - lower/upper
	TF1 *wire_axial[6][4][10][2];
	TF1 *wire_stereo[6][4][10][2];
	
	init();
	
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Fiducial Cuts",  "");
	bar->AddButton("","");
	bar->AddButton("Show phi vs theta",                      "show_phi_theta()");
	bar->AddButton("Show phi vs theta in p bins - before",   "show_phi_thetas(0)");
	bar->AddButton("Show phi vs theta in p bins - after",    "show_phi_thetas(3)");
	bar->AddButton("Show phis"            ,                  "show_phis()");
	bar->AddButton("","");
	bar->AddButton("Show y vs x in current plane",  "show_plane()");
	bar->AddButton("Show y vs x in current planes", "show_planes()");
	bar->AddButton("Show y vs x for all momenta",   "show_integrated_plane()");
	bar->AddButton("","");
	bar->AddButton("Slice this plane",              "slice_plane()");
	bar->AddButton("Re-fit this plane",             "slice_plane(1)");
	bar->AddButton("Slice all Planes",              "slice_all_planes()");
	bar->AddButton("Slice all Sectors",             "slice_all_sectors()");
	bar->AddButton("","");
	bar->AddButton("Switch Logz in the 2D plots",   "switch_logz()");
	bar->AddButton("Print all fiducial plots",      "print_all()");
	bar->AddButton("","");
	bar->AddButton("Change Sector",                 "change_sector()");
	bar->AddButton("Change Momentum",               "change_mom()");
	bar->AddButton("Change Plane",                  "change_plane()");
	bar->AddButton("","");
	bar->AddButton("Write Parameters",              "Pars.write_vars(pars_file)");
	bar->AddButton("","");
	bar->Show();
}









