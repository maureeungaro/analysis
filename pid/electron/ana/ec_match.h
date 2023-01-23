#ifndef ECMATCH_PARAMETERS_LOADED
#define ECMATCH_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"
#include "TF1.h"

class EC_Match {

public:

    EC_Match();
    ~EC_Match();

    static const int NDIV = 15;

    // constructor using chisto and cpars
    EC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4]);

    // set print
    void set_print(string P) { PRINT = P; }

    // threshold
    void show_ecthr(int sector);
    void show_ecthr_all_sectors();
    void show_ecthr_integral_over_sectors();

    // sampling fraction
    void calc_sf(int sector);
    void calc_sf_all_sectors();
    void show_sf_comparison(int sector);
    void show_sf(int sector);
    void show_sf_all_sectors();
    void DynamicExec(int sector);
    void DrawFit_SF(int sectorIndex, int hid);

    // uvw, which is 0, 1, 2 for u, v, w
    void show_uvw(int sector, int which);
    void show_uvw_all_sectors(int which);
    void show_uvw_integrated_sectors(int which);

    // Y vs X coordinates
    void show_ecyx();

private:

    chistos *H;
    cpars *Pars;
    string PRINT;

    const int csize = 1200; // common canvas size
    Color_t colors[4];

    const double min_limit_sf = 0.65;  // Fit range x min
    const double max_limit_sf = 5.00;  // Fit range x max


    // functions based on parameters in Pars
    Double_t ecsf_Mean( Double_t *x, Double_t *par);
    Double_t ecsf_Sigma(Double_t *x, Double_t *par);
    Double_t ecsf_limit(Double_t *x, Double_t *par);

    TF1 *sf_me = nullptr;
    TF1 *sf_up = nullptr;
    TF1 *sf_dn = nullptr;

    TH1F *ecp1d[6][EC_Match::NDIV];      // 1 dimensional projections, fitted with GAUS+PARABOLE

    double ecpmean[6][EC_Match::NDIV];
    double ecpsigm[6][EC_Match::NDIV];
    double ecpmeane[6][EC_Match::NDIV];
    double ecpsigme[6][EC_Match::NDIV];

    TGraphErrors *sf_mean[6];
    TGraphErrors *sf_sigm[6];
};

#endif