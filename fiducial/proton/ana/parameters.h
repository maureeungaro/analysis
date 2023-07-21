#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// analysis classes
#include "fiducial.h"

// global variables
std::string DATA_PRINT = ".png";
std::string SIM_PRINT  = "_gsim.png";
std::string PRINT  = "none";

bool is_simulation = false;
int SECTOR = 1;
int MOM = 1;
int PLANE = 1;
int LOGZ = 1;
const Color_t colors[4] = { kBlack, kBlue, kRed, kGreen+3 };

const std::string data_pars_file = "proton_fiducial_par.txt";
const std::string data_root_file = "data_pfid.root";
const std::string gsim_root_file = "gsim_pfid.root";
std::string data_label     = "data";

// common histogram
chistos *H    = nullptr;
cpars   *Pars = nullptr;

// analysis classes - cannot be local to e_pid.C
FiducialCut *Fiducial = nullptr;

const int csize = 1200; // common canvas size


#endif
