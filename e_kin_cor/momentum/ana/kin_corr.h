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
    void show_vertex();
    void show_2D_vertex();


private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int csize = 1200; // common canvas size

};

#endif
