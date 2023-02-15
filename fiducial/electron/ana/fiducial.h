#ifndef FIDUCIAL_PARAMETERS_LOADED
#define FIDUCIAL_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"
#include "TF1.h"


class FiducialCut {

public:

    FiducialCut();
    ~FiducialCut();

    // histos for 1D XY divisions.
    static const int NDIV_T = 24;

    // constructor using chisto and cpars
    FiducialCut(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4]);

    // set print
    void set_print(string P) { PRINT = P; }





private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int csize = 1200; // common canvas size
    Color_t colors[4];


 
};


#endif