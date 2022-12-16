#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED


//#include "TGraphErrors.h"
//#include "TF1.h"


Color_t colors[4] = { kBlack, kBlue, kRed, kGreen+3 };

std::string PRINT = ".png";
int SECTOR        = 1;

const std::string data_pars_file = "electron_id_par.txt";
const std::string gsim_pars_file = "electron_id_par_gsim.txt";
const std::string data_root_file = "data_epid.root";
const std::string gsim_root_file = "gsim_epid.root";
std::string data_label     = "data";


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


//TF1 *cc_match_me = new TF1("cc_match_me", cc_match_Mean,  1, 19, 1);
//TF1 *cc_match_up = new TF1("cc_match_up", cc_match_limit, 1, 19, 3);
//TF1 *cc_match_dn = new TF1("cc_match_dn", cc_match_limit, 1, 19, 3);
//
//// CC timing histos, variables, functions
//TH1F *cc_timing1d[6][36];      // 1 dimensional projections, fitted with GAUS
//TGraphErrors *cc_timing_low[6];



#endif

