#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"

void e_pid(bool printa = false) {

    string type = "data";

    string pars_file = data_pars_file;
    string root_file = data_root_file;

    // if the first argument is the string 'gsim' then:
    if (type == "gsim") {
        pars_file = gsim_pars_file;
        root_file = gsim_root_file;
        data_label = "gsim";
        is_simulation = true;
    }

    // load common histos and parameters
    // second parameters instructs to read the root file
    H = new chistos(root_file, 1);
    Pars = new cpars(pars_file);

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
	TGraphErrors *y_left[7][5];
	TGraphErrors *y_right[7][5];
	TF1 *left_para[7][5];
	TF1 *rite_para[7][5];

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
	bar->AddButton("Slice all Planes",              "slice_all_planes()");
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
	bar->AddButton("Print All",                     "print_all()");
	bar->AddButton("","");
	bar->Show();
}









