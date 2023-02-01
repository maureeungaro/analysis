#ifndef INFO_H
#define INFO_H

// ROOT includes
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

// C++ includes
#include <string>
#include <iostream>

using namespace std;

// Common Classes with ROOT analysis macro

class chistos {
public:
    chistos(string filename, int READ = 0);

    ~chistos() { ; }

    TFile *output;

    TH2F *dt_mom[7];           // Delta T versus momentum
    TH2F *dt_momz[7];          // Delta T versus momentum

    // utility histos. First index: before/after the cut
    TH2F *mass_vs_mom[2][7];   // TOF mass vs momentum
    TH2F *beta_vs_mom[2][7];   // TOF beta vs momentum

    // Cut statistic
    TH1F *monitor[7];          // 0: all  1: hits in SC (before) 1: after the cut.

    void write_and_close();    // Write out histos and close ROOT file
};

// %%%%%%%%%%%%%%%%%%%%%%%%
// Parameters and functions
// %%%%%%%%%%%%%%%%%%%%%%%%
class cpars {

public:
    cpars(string filename);

    ~cpars() { ; }

    string parameter_file;


    // additional infos in the file: cuts informations
    vector <string> addInfos;

    // all cuts are stored in the file specified in the constructor
    double dt_mom_mean_a[6];    // DTMA: delta t  mean A: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_mean_b[6];    // DTMB: delta t  mean B: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_mean_c[6];    // DTMC: delta t  mean C: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_mean_d[6];    // DTMD: delta t  mean D: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_mean_e[6];    // DTMD: delta t  mean D: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_mean_f[6];    // DTMD: delta t  mean D: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_a[6];    // DTSA: delta t sigma A: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_b[6];    // DTSB: delta t sigma B: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_c[6];    // DTSC: delta t sigma C: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_d[6];    // DTSD: delta t sigma D: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_e[6];    // DTSD: delta t sigma D: a + bx + cx2 + dx3 + ex4 + fx5
    double dt_mom_sigm_f[6];    // DTSD: delta t sigma D: a + bx + cx2 + dx3 + ex4 + fx5
    double NSIGMAS[2];          // SFNS: delta t number of sigmas for upper/lower DT curve

    double Mean(double p, int sector);

    double Sigma(double p, int sector);

    double dt_mom_limit(double p, int sector, int nsigmas, int which);

    double rMean(double *x, double *par);

    double rSigma(double *x, double *par);

    double rdt_mom_limit(double *x, double *par);

    void write_vars();
};

#endif



