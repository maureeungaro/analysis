#ifndef TOFMATCH_PARAMETERS_LOADED
#define TOFMATCH_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"
#include "TF1.h"

class TOF_Match {

public:

    TOF_Match();

    ~TOF_Match();

    static const int NDIV = 9;       // divisions of DT and Mass vs momentum

    // constructor using chisto and cpars
    TOF_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4], bool is_sim);

    // set print
    void set_print(string P) { PRINT = P; }


    void fit_and_calculate_pars(TH2F *h, TH2F *h2, int sector);

    // dt vs momentum
    void show_dt_vs_mom(int sector);
    void DynamicExec(int sector);
    void DrawFit(int s, int hid);
    void show_dt_vs_mom_all_sectors();

    // beta vs momentum
    void show_mass_and_beta(int sector);
    void show_mass_and_beta_all_sectors();


private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    bool is_simulation = false;

    const int csize = 1200; // common canvas size
    Color_t colors[4];

    const double min_limit_dt = 0.2;   // Fit range x min
    const double max_limit_dt = 5.5;   // Fit range x max

    // functions based on parameters in Pars
    Double_t dt_mom_mean(Double_t *x, Double_t *par);

    Double_t dt_mom_sigma(Double_t *x, Double_t *par);

    Double_t dt_mom_limit(Double_t *x, Double_t *par);

    TF1 *dt_me = nullptr;
    TF1 *dt_up = nullptr;
    TF1 *dt_dn = nullptr;

    TH1F *dt_1d[6][TOF_Match::NDIV];        // 1 dimensional projections of DT vs momentum, fitted with GAUS + PARABOLE

    TF1 *MySignal[6][TOF_Match::NDIV];
    TF1 *MyBackground[6][TOF_Match::NDIV];

    double dtmean[6][TOF_Match::NDIV];
    double dtsigm[6][TOF_Match::NDIV];
    double dtmeane[6][TOF_Match::NDIV];
    double dtsigme[6][TOF_Match::NDIV];

    TGraphErrors *dt_mean[6];
    TGraphErrors *dt_sigm[6];

};

#endif