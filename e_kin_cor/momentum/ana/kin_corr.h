#ifndef EKINCORR_PARAMETERS_LOADED
#define EKINCORR_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"

class EKinnCorr_CS {

public:

    EKinnCorr_CS();
    ~EKinnCorr_CS();

    // constructor using chisto and cpars
    EKinnCorr_CS(chistos *common_histo, cpars *common_pars, string P) {

        H = common_histo;
        Pars = common_pars;
        PRINT = P;

    }

    // set print
    void set_print(string P) { PRINT = P; }

    // plots
    void show_1D_each_sector(int sector, int what);
    void show_2D_each_sector(int sector, int what, int phi_theta);


private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int csize = 1200; // common canvas size
    const double mm_line[4]  = { 0.938, 0.018219, 0.88, 0.299 };
    const double mm_width[4] = { 0.04, 0.008,     0.05, 0.025 };

    const double w_shifts[7]   = { 0.03, 0.0, 0.0, 0.03, 0.03, 0.02, 0.03 };
    const double pi0_shifts[7] = { 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    const double n_shifts[7]   = { 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    const double eta_shifts[7] = { 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    const string mm_name[4] = { "W (elastic)", "pi0 in #Delta", "pi+ mm", "eta mmx" };

};

#endif
