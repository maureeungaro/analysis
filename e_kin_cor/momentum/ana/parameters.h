#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// analysis classes
#include "kin_corr.h"

// global variables
std::string DATA_PRINT = ".png";
std::string PRINT  = "none";

int SECTOR = 1;

const std::string data_pars_file = "emom_corr_pars.txt";
const std::string data_root_file = "ekin_corr.root";
std::string data_label     = "data";

// common histogram
chistos *H    = nullptr;
cpars   *Pars = nullptr;

// analysis classes - cannot be local to vertex.C
EKinnCorr_CS *EKinnCorrCS = nullptr;

const int csize = 1200;   // common canvas size

#endif
