#ifndef GLOBAL_PARAMETERS_LOADED
#define GLOBAL_PARAMETERS_LOADED


//#include "TGraphErrors.h"
//#include "TF1.h"


Color_t colors[4] = { kBlack, kBlue, kRed, kGreen+3 };

std::string PRINT     = ".png";
int SECTOR       = 1;

std::string data_pars_file = "electron_id_par.txt";
std::string gsim_pars_file = "electron_id_par_gsim.txt";
std::string data_root_file = "data_epid.root";
std::string gsim_root_file = "gsim_epid.root";
std::string data_label     = "data";




//const int NDIV = 15;       // divisions of sampling fraction
//
//double no_cc_or_ec[7];
//double hit_cc[7];
//double hit_ec[7];
//double hit_cc_and_ec[7];
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


//#include "common_info.h"
//#include "histos.h"

//TF1 *sf_me = new TF1("sf_me", Mean,      0.2, 5, 1);
//TF1 *sf_up = new TF1("sf_up", ecp_limit, 0.2, 5, 3);
//TF1 *sf_dn = new TF1("sf_dn", ecp_limit, 0.2, 5, 3);
//
//// CC theta match histos, variables, functions
//TH1F *cc_match1d[6][18];      // 1 dimensional projections, fitted with GAUS+PARABOLE
//double cc_matchmean[6][18];
//double cc_matchsigm[6][18];
//double cc_matchmeane[6][18];
//double cc_matchsigme[6][18];
//TGraphErrors *cc_match_mean[6];
//TGraphErrors *cc_match_sigm[6];
//TF1 *cc_match_me = new TF1("cc_match_me", cc_match_Mean,  1, 19, 1);
//TF1 *cc_match_up = new TF1("cc_match_up", cc_match_limit, 1, 19, 3);
//TF1 *cc_match_dn = new TF1("cc_match_dn", cc_match_limit, 1, 19, 3);
//
//// CC timing histos, variables, functions
//TH1F *cc_timing1d[6][36];      // 1 dimensional projections, fitted with GAUS
//TGraphErrors *cc_timing_low[6];



#endif

