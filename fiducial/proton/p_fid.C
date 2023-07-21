#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"

void p_fid(bool printa = false) {

    string type = "data";

    string pars_file = data_pars_file;
    string root_file = data_root_file;

    // if the first argument is the string 'gsim' then:
    if (type == "gsim") {
        root_file = gsim_root_file;
        data_label = "gsim";
        is_simulation = true;
    }

    // load common histos and parameters
    // second parameters instructs to read the root file
    H = new chistos(root_file, 1);
    Pars = new cpars(pars_file);

    // Fiducial Cut Class
    Fiducial = new FiducialCut(H, Pars, PRINT, colors, LOGZ);

    // load utils.C
    gROOT->ProcessLine(".L ana/utils.C");


    TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro", 2600, 150);
	bar->AddButton("Fiducial Cuts",  "");
	bar->AddButton("","");
	bar->AddButton("Show phi vs theta",                      "Fiducial->show_phi_theta(SECTOR, MOM)");
	bar->AddButton("Show phi vs theta in p bins - before",   "Fiducial->show_phi_thetas(SECTOR, 0)");
	bar->AddButton("Show phi vs theta in p bins - after",    "Fiducial->show_phi_thetas(SECTOR, 3)");
	bar->AddButton("Show phis"            ,                  "Fiducial->show_phis(SECTOR, MOM, PLANE)");
	bar->AddButton("","");
	bar->AddButton("Show y vs x in current plane",           "Fiducial->show_plane(SECTOR, MOM, PLANE)");
	bar->AddButton("Show y vs x in all planes",              "Fiducial->show_planes(SECTOR, PLANE)");
	bar->AddButton("Show y vs x for all momenta",            "Fiducial->show_integrated_plane(SECTOR, PLANE)");
	bar->AddButton("","");
	bar->AddButton("Slice this plane",                       "Fiducial->slice_plane(SECTOR, PLANE)");
	bar->AddButton("Slice all Planes this sector",           "Fiducial->slice_all_planes()");


    bar->AddButton("", "");
    bar->AddButton("", "");
    bar->AddButton("Switch PRINT",                       "switch_print();");
    bar->AddButton("Change Sector",                      "change_sector();");
    bar->AddButton("Change Momentum",                    "change_mom()");
    bar->AddButton("Change Plane",                       "change_plane()");
    bar->AddButton("Switch Logz in the 2D plots",        "switch_logz()");
    bar->AddButton("", "");
    bar->AddButton("Print all proton fiducial plots",    "print_all_message();");
    bar->AddButton("Write Parameters",                   "Pars->write_vars();");
    bar->AddButton("", "");
    bar->Show();
    gROOT->SaveContext();

    if (printa) {
        gROOT->ProcessLine("print_all();");
    }

}
