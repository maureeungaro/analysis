#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"


void vertex(bool printa = false) {

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

    // Vertex Corrections and Selection
    VertexCS = new Vertex_CS(H, Pars, PRINT, is_simulation);

    // load utils.C
    gROOT->ProcessLine(".L ana/utils.C");

    TControlBar *bar = new TControlBar("vertical", data_label.c_str(), 1800, 30);
	bar->AddButton("Vertex Correction, Selection", "");
	bar->AddButton("","");
	bar->AddButton("Show z vertex",            "VertexCS->show_vertex()");
	bar->AddButton("Show 2D vertex",           "VertexCS->show_2D_vertex()");
	bar->AddButton("","");
    bar->AddButton("Switch PRINT",             "switch_print();");
    bar->AddButton("","");
	bar->AddButton("Print all vertex plots",   "print_all_message()");
    bar->AddButton("Write Parameters",         "Pars->write_vars();");
    bar->AddButton("","");
    bar->Show();
    gROOT->SaveContext();


    if (printa) {
        gROOT->ProcessLine("print_all();");
    }}











