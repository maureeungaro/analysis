#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// analysis classes
#include "cc_match.h"

// global variables
std::string DATA_PRINT = ".png";
std::string SIM_PRINT  = "_gsim.png";
std::string PRINT  = "none";
bool is_simulation = false;
int SECTOR = 1;

const std::string data_pars_file = "electron_id_par.txt";
const std::string gsim_pars_file = "electron_id_par_gsim.txt";
const std::string data_root_file = "data_epid.root";
const std::string gsim_root_file = "gsim_epid.root";
std::string data_label     = "data";


// common histogram
chistos *H    = nullptr;
cpars   *Pars = nullptr;

// analysis classes
CC_Match *CCMatch = nullptr;


//void change_sector();
//void print_all();



//const int NDIV = 15;       // divisions of sampling fraction
//

//
//
//// Sampling fraction histos, variables, functions
//TH1F *ecp1d[6][NDIV];      // 1 dimensional projections, fitted with GAUS+PARABOLE
//double ecpmean[6][NDIV];
//double ecpsigm[6][NDIV];
//double ecpmeane[6][NDIV];
//double ecpsigme[6][NDIV];
//TGraphErrors *sf_mean[6];
//TGraphErrors *sf_sigm[6];
//double min_limit_sf = 0.65;  // Fit range x min
//double max_limit_sf = 5.00;  // Fit range x max



//TF1 *sf_me = new TF1("sf_me", Mean,      0.2, 5, 1);
//TF1 *sf_up = new TF1("sf_up", ecp_limit, 0.2, 5, 3);
//TF1 *sf_dn = new TF1("sf_dn", ecp_limit, 0.2, 5, 3);
//

#endif

