#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// analysis classes
#include "tof_match.h"

// global variables
std::string DATA_PRINT = ".png";
std::string SIM_PRINT  = "_gsim.png";
std::string PRINT  = "none";

bool is_simulation = false;
int SECTOR = 1;
const Color_t colors[4] = { kBlack, kBlue, kRed, kGreen+3 };

const std::string data_pars_file = "proton_id_par.txt";
const std::string gsim_pars_file = "proton_id_par_gsim.txt";
const std::string data_root_file = "data_ppid.root";
const std::string gsim_root_file = "gsim_ppid.root";
std::string data_label     = "data";

// common histogram
chistos *H    = nullptr;
cpars   *Pars = nullptr;

// analysis classes - cannot be local to p_pid.C
TOF_Match *TOFMatch = nullptr;

const int csize = 1200;   // common canvas size


#endif

