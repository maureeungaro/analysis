#include "TControlBar.h"
#include "TApplication.h"

// common parameters, analysis classes
#include"ana/parameters.h"


void mom_corr(bool printa = false) {

    string pars_file = data_pars_file;
    string root_file = data_root_file;

    // load common histos and parameters
    // second parameters instructs to read the root file
    H = new chistos(root_file, 1);
    Pars = new cpars(pars_file);

    // Vertex Corrections and Selection
    EKinnCorrCS = new EKinnCorr_CS(H, Pars, PRINT);

    // load utils.C
    gROOT->ProcessLine(".L ana/utils.C");

    TControlBar *bar = new TControlBar("vertical", data_label.c_str(), 1800, 30);
    bar->AddButton("Momentum Correction, Selection", "");
    bar->AddButton("","");
    bar->AddButton("Show W before / after",            "EKinnCorrCS->show_1D_each_sector(SECTOR, 0)");
    bar->AddButton("Show mmePpi0 before / after",      "EKinnCorrCS->show_1D_each_sector(SECTOR, 1)");
    bar->AddButton("Show mmepip before / after",       "EKinnCorrCS->show_1D_each_sector(SECTOR, 2)");
    bar->AddButton("Show mmePeta before / after",      "EKinnCorrCS->show_1D_each_sector(SECTOR, 3)");
    bar->AddButton("","");
    bar->AddButton("Switch PRINT",                     "switch_print();");
    bar->AddButton("Change Sector",                    "change_sector();");
    bar->AddButton("","");
    bar->AddButton("Print all mom correction plots",   "print_all_message()");
    bar->AddButton("","");
    bar->Show();
    gROOT->SaveContext();


    if (printa) {
        gROOT->ProcessLine("print_all();");
    }
}
