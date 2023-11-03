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

    TH2F *deltavz_vz[7][3];    // for electron/proton. sector -- before, after corr, after cut --
    TH2F *phi_vz[7][3][2];     // phi versus z         sector -- before, after corr, after cut -- el/pro
    TH1F *vz[7][3][2];         //                      sector -- before, after corr, after cut -- el/pro

    TH1F *monitor[7];           // utility monitor

    void write_and_close();    // Write out histos and close ROOT file
};

// Parameters and functions
class cpars {
public:
    cpars(string filename);
    ~cpars() { ; }

    string parameter_file;

    // additional infos in the file: cuts information
    vector <string> addInfos;

    // all cuts are stored in the file specified in the constructor
    double beam_pos[2];         // BEAMD: Beam Displacement from (0,0), cm
    double vz_limits[2];        // ZLIM: VZ min and Max
    double delta_z;             // DLTZ: vz_e - vz_p cut

    void write_vars();
};

#endif
