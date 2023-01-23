#include "ec_match.h"

Double_t EC_Match::ecsf_Mean(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    return Pars->ecp_mean_a[s] +
           Pars->ecp_mean_b[s]*x[0] +
           Pars->ecp_mean_c[s]*x[0]*x[0] +
           Pars->ecp_mean_d[s]*x[0]*x[0]*x[0];
}

Double_t EC_Match::ecsf_Sigma(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    return Pars->ecp_sigm_a[s] +
           Pars->ecp_sigm_b[s]*x[0] +
           Pars->ecp_sigm_c[s]*x[0]*x[0] +
           Pars->ecp_sigm_d[s]*x[0]*x[0]*x[0];
}

Double_t EC_Match::ecsf_limit(double *x, double *par)
{
    // par[1] is # of sigmas
    double nsigmas = par[1];

    // par[2] is which limit (upper or lower)
    if(par[2] >= 0) return ecsf_Mean(x, par) + nsigmas*ecsf_Sigma(x, par);
    else            return ecsf_Mean(x, par) - nsigmas*ecsf_Sigma(x, par);
}


// constructor using chisto and cpars
EC_Match::EC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t c[4]) {
    H = common_histo;
    Pars = common_pars;
    PRINT = P;
    for(int cc=0; cc<4; cc++) {
        colors[cc] = c[cc];
    }

    sf_me = new TF1("sf_me", [&](double*x, double *p){ return ecsf_Mean(x, p)  ; }, 0.2, 5, 1 ) ;
    sf_up = new TF1("sf_up", [&](double*x, double *p){ return ecsf_limit(x, p) ; }, 0.2, 5, 3 ) ;
    sf_dn = new TF1("sf_dn", [&](double*x, double *p){ return ecsf_limit(x, p) ; }, 0.2, 5, 3 ) ;

}
