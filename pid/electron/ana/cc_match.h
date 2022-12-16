#ifndef CCMATCH_PARAMETERS_LOADED
#define CCMATCH_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

#include "TGraphErrors.h"

class CC_Match {

public:

    CC_Match();
    ~CC_Match();

    // constructor using chisto and cpars
    CC_Match(chistos *common_histo, cpars *common_pars);

    // 2 gaussians + parabole
    double parabole(double *x, double *par)     { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] ; }
    double gaussian(double *x, double *par)     { return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2)); }
    double gauss2_para(double *x, double *par)  { return parabole(x, par) + gaussian(x, &par[3]) + gaussian(x, &par[6]); }

private:

    chistos *H;
    cpars *Pars;

    // CC theta match histos, variables, functions
    TH1F *cc_match1d[6][18];      // 1 dimensional projections, fitted with GAUS+PARABOLE
    double cc_matchmean[6][18];
    double cc_matchsigm[6][18];
    double cc_matchmeane[6][18];
    double cc_matchsigme[6][18];
    TGraphErrors *cc_match_mean[6];
    TGraphErrors *cc_match_sigm[6];


    // adds the functions defined in cc_match.cc
    double cc_match_Mean(double *x, double *par);
    double cc_match_Mean2(double *x, double *par);
    double cc_match_Sigma(double *x, double *par);
    double cc_match_limit(double *x, double *par);
    void calc_cc_match(int sector);
    void calc_all_cc_match();




};



#endif