#include "tof_match.h"


Double_t TOF_Match::dt_mom_mean(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    return Pars->dt_mom_mean_a[s] +
           Pars->dt_mom_mean_b[s]*x[0] +
           Pars->dt_mom_mean_c[s]*x[0]*x[0] +
           Pars->dt_mom_mean_d[s]*x[0]*x[0]*x[0] +
           Pars->dt_mom_mean_e[s]*x[0]*x[0]*x[0]*x[0] +
           Pars->dt_mom_mean_f[s]*x[0]*x[0]*x[0]*x[0]*x[0];
}

Double_t TOF_Match::dt_mom_sigma(double *x, double *par)
{
    // par[0] is sector
    int s = (int) par[0] - 1;

    return Pars->dt_mom_sigm_a[s] +
           Pars->dt_mom_sigm_b[s]*x[0] +
           Pars->dt_mom_sigm_c[s]*x[0]*x[0] +
           Pars->dt_mom_sigm_d[s]*x[0]*x[0]*x[0] +
           Pars->dt_mom_sigm_e[s]*x[0]*x[0]*x[0]*x[0] +
           Pars->dt_mom_sigm_f[s]*x[0]*x[0]*x[0]*x[0]*x[0];
}

Double_t TOF_Match::dt_mom_limit(double *x, double *par)
{
    // par[1] is # of sigmas
    double nsigmas = par[1];

    // par[2] is which limit (upper or lower)
    if(par[2] >= 0) return dt_mom_mean(x, par) + nsigmas*dt_mom_sigma(x, par);
    else            return dt_mom_mean(x, par) - nsigmas*dt_mom_sigma(x, par);
}


// constructor using chisto and cpars
TOF_Match::TOF_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t c[4], bool is_sim) {

    H = common_histo;
    Pars = common_pars;
    PRINT = P;
    is_simulation = is_sim;

    for(int cc=0; cc<4; cc++) {
        colors[cc] = c[cc];
    }

    dt_me = new TF1("mass_me", [&](double*x, double *p){ return dt_mom_mean(x, p)  ; }, 0.2, 5.0, 1);
    dt_up = new TF1("mass_up", [&](double*x, double *p){ return dt_mom_limit(x, p) ; }, 0.2, 5.0, 3);
    dt_dn = new TF1("mass_dn", [&](double*x, double *p){ return dt_mom_limit(x, p) ; }, 0.2, 5.0, 3);

}
