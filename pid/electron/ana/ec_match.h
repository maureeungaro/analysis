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


    // constructor using chisto and cpars
    EC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4]);

    // set print
    void set_print(string P) { PRINT = P; }

    void show_ecthr(int sector);
    void show_ecthr_all_sectors();
    void show_ecthr_integral_over_sectors();

private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int NDIV = 15;
    const int csize = 1200; // common canvas size
    Color_t colors[4];

};

#endif