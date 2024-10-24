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

    // histos for 1D theta divisions.
    static const int NDIV_T = 24;

    // histos for 1D XY divisions.
    static const int NDIV_XY = 15;

    // number of planes
    static const int MIN_PLANE = 2;
    static const int NPLANES = 12;

    // constructor using chisto and cpars
    FiducialCut(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4], bool logz);

    // set print
    void set_print(string P) { PRINT = P; }
    void set_logz(bool logz) { LOGZ = logz; }


    void show_phi_theta(int sector, int mom);
    void show_phi_thetas(int sector, int which);
    void show_phis(int sector, int mom, int plane);
    void show_plane(int sector, int mom, int plane);
    void show_planes(int sector, int plane);
    void show_integrated_plane(int sector, int plane);
    void DynamicExec(int sector, int plane);
    void DrawFit(int s, int pl, int hid);

    void slice_plane(int sector, int plane);
    void slice_all_planes();

private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    bool LOGZ;
    const int csize = 1200; // common canvas size
    Color_t colors[4];

    // slices in momentum, theta
    TH2F *phi_theta[4][7][chistos::NDIV_P];
    TH2F *y_x[4][7][3][chistos::NDIV_P];


    TH1F *y_slice[7][5][FiducialCut::NDIV_XY];
    double ymin[7][5][FiducialCut::NDIV_XY];
    double ymax[7][5][FiducialCut::NDIV_XY];
    double ymine[7][5][FiducialCut::NDIV_XY];
    double ymaxe[7][5][FiducialCut::NDIV_XY];

    TGraphErrors *y_left[7][5]; // current fits
    TGraphErrors *y_right[7][5];

    TF1 *left_para[7][5]; // new fits
    TF1 *rite_para[7][5];

    // sect - plane - n. of holes - lower/upper
    TF1 *wire_axial[6][4][10][2];
    TF1 *wire_stereo[6][4][10][2];

    TH1F *phis_befor[7][5][chistos::NDIV_P][FiducialCut::NDIV_T];
    TH1F *phis_after[7][5][chistos::NDIV_P][FiducialCut::NDIV_T];


    void draw_limits(int sector, int plane);

    TGraph *fidcut(int s, double p, int which);
};


#endif
