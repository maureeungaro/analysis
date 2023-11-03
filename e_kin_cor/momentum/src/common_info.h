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

    TH1F *hH[7][2][4];   //  sector ## uncorr - corr ##  W mmePpi0 mmepip mmePeta
    TH2F *hHt[7][2][4];  //  sector ## uncorr - corr ##  W mmePpi0 mmepip mmePeta as function of theta
    TH2F *hHp[7][2][4];  //  sector ## uncorr - corr ##  W mmePpi0 mmepip mmePeta as function of phi

    void write_and_close();    // Write out histos and close ROOT file
};

// Parameters and functions
class cpars {
public:
    cpars(string filename);
    ~cpars() { ; }

    string parameter_file;

    // additional infos in the file
    long double par_par_phi[6][4][10];

    vector <string> addInfos;

};

#endif
