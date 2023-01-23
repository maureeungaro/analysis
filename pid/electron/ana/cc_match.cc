#include "cc_match.h"


Double_t CC_Match::cc_match_Mean(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    return Pars->cc_match_mean_a[s] +
           Pars->cc_match_mean_b[s]*x[0] +
           Pars->cc_match_mean_c[s]*x[0]*x[0];
}

Double_t CC_Match::cc_match_Mean2(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    // we want lower limit to be constant in each segment
    double segment = floor(x[0]);

    return Pars->cc_match_mean_a[s] +
           Pars->cc_match_mean_b[s]*segment +
           Pars->cc_match_mean_c[s]*segment*segment;
}

Double_t CC_Match::cc_match_Sigma(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    // segment index
    int segment = (int) floor(x[0]) - 1;

    return Pars->cc_match_low[s][segment];
}

Double_t CC_Match::cc_match_limit(double *x, double *par)
{
    // par[1] is # of sigmas
    double nsigmas = par[1];

    // par[2] is which limit (upper or lower)
    if(par[2] >= 0) return cc_match_Mean2(x, par) + nsigmas*cc_match_Sigma(x, par);
    else            return cc_match_Mean2(x, par) - nsigmas*cc_match_Sigma(x, par);
}


// constructor using chisto and cpars
CC_Match::CC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t c[4]) {
    H = common_histo;
    Pars = common_pars;
    PRINT = P;
    for(int cc=0; cc<4; cc++) {
        colors[cc] = c[cc];
    }

    for(int s=0; s<6; s++) {
        cc_match_mean[s] = NULL;
        cc_timing_low[s] = NULL;
    }

    cc_match_me = new TF1("cc_match_me", [&](double*x, double *p){ return cc_match_Mean(x, p)  ; }, 1, 19, 1);
    cc_match_up = new TF1("cc_match_up", [&](double*x, double *p){ return cc_match_limit(x, p) ; }, 1, 19, 3);
    cc_match_dn = new TF1("cc_match_dn", [&](double*x, double *p){ return cc_match_limit(x, p) ; }, 1, 19, 3);
}

