#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"

void p_pid() {
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


    // load utils.C
    gROOT->ProcessLine(".L ana/utils.C");




    // last arguments are the positions on screen
    TControlBar *bar = new TControlBar("vertical", data_label.c_str(), 1600, 30);
	bar->AddButton("Proton Particle ID", "");
	bar->AddButton("","");
	bar->AddButton("","");
	bar->AddButton("Calculate new DT cuts",         "calc_2d(H->dt_momz[SECTOR-1], H->dt_mom[SECTOR-1])");
	bar->AddButton("Show DT vs mom",                "show_dt_vs_mom()");
	bar->AddButton("Show DT all sectors",           "show_dt_vs_moms()");
	bar->AddButton("","");
	bar->AddButton("Show Beta and Mass vs p",       "show_mass_beta()");
	bar->AddButton("Show Beta vs p all sectors",    "show_betaAll()");


    bar->AddButton("", "");
    bar->AddButton("", "");
    bar->AddButton("Switch PRINT", "switch_print();");
    bar->AddButton("Change Sector", "change_sector();");
    bar->AddButton("", "");
    bar->AddButton("Print all electrond ID plots", "print_all();");
    bar->AddButton("Write Parameters", "Pars->write_vars();");
    bar->AddButton("", "");
    bar->Show();
    gROOT->SaveContext();
}











