#ifndef INFO_H
#define INFO_H

// ROOT includes
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

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
    static const int NDIV_P = 10;
    double minp, maxp, dp;
    double mom[NDIV_P], mom2[NDIV_P];  // for some reason the graph need the upper edge of the bin

    // 4 cuts, 6 sectors + all sectors
    TH2F *phi_theta[4][7][NDIV_P];
    TH2F *x_y[4][7][5][NDIV_P];     // 3 DC planes, 1 EC plane, 1 SC plane
    TH2F *x_y_tot[4][7][5];         // 3 DC planes, 1 EC plane, 1 SC plane - Integrated over all momenta

    TH1F *monitor[7];               // utility monitor

    void write_and_close();         // Write out histos and close ROOT file
};

// Parameters and functions
class cpars {
public:
    cpars(string filename);

    ~cpars() { ; }

    string parameter_file;

    // additional infos in the file: cuts informations
    vector <string> addInfos;

    // phi theta parameters
    double c1[6];
    double c2[6];
    double c3[6];
    double c4[6];
    double c5[6];
    double c6[6];

    // plane coordinates parameters
    // left:  x = a + b_left*y + c_left*y2
    // right: x = a + b_rite*y + c_rite*y2
    // a = XMIN - b YMIN - c YMIN*YMIN
    // XMIN is the vertex vertical position of each plane's bottom corner(same in all sectors)
    // YMIN is the vertex horizontal position of each plane's bottom corner
    double XMIN[5];
    double YMIN[5][6];

    double r1_b_left[6];
    double r1_b_rite[6];
    double r2_b_left[6];
    double r2_b_rite[6];
    double r3_b_left[6];
    double r3_b_rite[6];
    double sc_b_left[6];
    double sc_b_rite[6];

    double r1_c_left[6];
    double r1_c_rite[6];
    double r2_c_left[6];
    double r2_c_rite[6];
    double r3_c_left[6];
    double r3_c_rite[6];
    double sc_c_left[6];
    double sc_c_rite[6];

    double stereo_angle_slope;

    // information comes in triplets: sector, min, max
    vector<double> r1_axial_limits;
    vector<double> r1_stereo_limits;
    vector<double> r2_axial_limits;
    vector<double> r2_stereo_limits;
    vector<double> r3_axial_limits;
    vector<double> r3_stereo_limits;
    vector<double> sc_axial_limits;
    vector<double> sc_stereo_limits;

    void write_vars();

    double theta_cut(int sect, double p);

    double expon(int sect, double p);

    double dphi(int sect, double p, double t);

    double xycut(int sector, int plane, double x, double y);

    double xyholes(int sector, int plane, double x, double y);
};

#endif





