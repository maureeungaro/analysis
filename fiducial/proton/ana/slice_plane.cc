#include "fiducial.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"

// Ugly: these functions have to be global to be used by TF1
// but compiling them here means we cannot use them in other files
// thus we have to call them with a different name otherwise the compiler will detect
// duplicate definitions

double tent(double *X, double *par) {
    double x = X[0];

    double p0 = par[0];
    double p1 = par[1];
    double p2 = par[2];
    double p3 = par[3];
    double p4 = par[4];
    double a = par[5];

    // parabole parameters
    // y = ax2 + bx + c
    // a = par[5]
    // with two constrains given by the two points at x,y = (p1, p4), (p2, p4):
    double b = -a * (p1 * p1 - p2 * p2) / (p1 - p2);
    double c = p4 - a * p1 * p1 - b * p1;

    if (x < p1 - p0) return 0;                      // no signal
    if (x >= p1 - p0 && x < p1) return (p4 / p0) * (x - p1 + p0);  // steep rise
    if (x >= p1 && x < p2) return a * x * x + b * x + c;         // parabole
    if (x >= p2 && x < p2 + p3) return (p4 / p3) * (-x + p2 + p3);  // steep descend
    if (x >= p2 + p3) return 0;                      // no signal

    return 0;
}

double thirdOrder_s(double *x, double *par) { return par[0] + par[1] * x[0] + par[2] * x[0] * x[0] + par[3] * x[0] * x[0] * x[0]; }


void FiducialCut::slice_plane(int sector, int plane) {

    int s = sector - 1;
    int pl = plane - 1;

    int skip_start_bin = 2;
    int skip_final_bin = 6;

    if (pl == 4) skip_start_bin = 1;
    if (pl == 4) skip_final_bin = 7;

    gStyle->SetPadLeftMargin(0.1);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetPadTopMargin(0.12);
    gStyle->SetPadBottomMargin(0.14);

    TCanvas *Cecp = new TCanvas("Cecp", "Cecp", csize, csize);

    int NBINS = H->x_y_tot[0][s][pl]->GetNbinsY();
    int db = NBINS / NDIV_XY;

    double yb[NDIV_XY], ybe[NDIV_XY];
    double dy = (H->x_y_tot[0][s][pl]->GetYaxis()->GetXmax() - H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin()) / NDIV_XY;

    for (int b = skip_start_bin; b < NDIV_XY - skip_final_bin; b++) {
        yb[b] = H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin() + (b + 0.5) * dy;
        ybe[b] = 0.001;
    }

    for (int b = 0; b < skip_start_bin; b++) {
        yb[b] = -999;
        ybe[b] = 0.001;
        ymin[s][pl][b] = -999;
        ymax[s][pl][b] = -999;
        ymine[s][pl][b] = -999;
        ymaxe[s][pl][b] = -999;
    }
    for (int b = NDIV_XY - skip_final_bin; b < NDIV_XY; b++) {
        yb[b] = -999;
        ybe[b] = 0.001;
        ymin[s][pl][b] = -999;
        ymax[s][pl][b] = -999;
        ymine[s][pl][b] = -999;
        ymaxe[s][pl][b] = -999;
    }


    double y_lims[5] = {30, 90, 150, 200, 200};

    TF1 Tent("Tent", tent, -y_lims[pl], y_lims[pl], 6);
    Tent.SetParameter(0, 2);
    Tent.SetParameter(1, -2.2);
    Tent.SetParameter(2, 2.1);
    Tent.SetParameter(3, 2);

    Tent.SetParLimits(1, -y_lims[pl], -0.1);
    Tent.SetParLimits(2, 0.1, y_lims[pl]);

    Tent.SetParLimits(0, 1, y_lims[pl]);
    Tent.SetParLimits(3, 1, y_lims[pl]);
    Tent.SetLineWidth(2);
    Tent.SetLineColor(kRed + 3);


    // Slicing + fitting
    cout << " Fitting Sector " << sector << ", Plane " << plane << endl;
    for (int b = skip_start_bin; b < NDIV_XY - skip_final_bin; b++) {
        cout << " Fitting slice " << b + 1 << endl;
        H->x_y_tot[0][s][pl]->ProjectionX(Form("y_slice_s%d_b%d_pl%d", s + 1, b + 1, pl + 1), b * db, (b + 1) * db);
        y_slice[s][pl][b] = (TH1F *) gROOT->Get(Form("y_slice_s%d_b%d_pl%d", s + 1, b + 1, pl + 1));

        Tent.SetParameter(4, y_slice[s][pl][b]->GetMaximum() / 1.4);
        Tent.SetParLimits(4, y_slice[s][pl][b]->GetMaximum() / 2.0, y_slice[s][pl][b]->GetMaximum());

        y_slice[s][pl][b]->Fit("Tent", "QEM");

        double factor[5] = {4, 2.5, 2.5, 1.8, 1.8};

        // there is a slight asymmetry on the right, compensating for it
        double r_asym_f[5] = {1.0, 1.15, 1.3, 1.0, 1.0};

        ymin[s][pl][b] = -Tent.GetParameter(0) / (factor[pl]) + Tent.GetParameter(1);
        ymax[s][pl][b] = Tent.GetParameter(3) / (factor[pl] * r_asym_f[pl]) + Tent.GetParameter(2);
        ymine[s][pl][b] = Tent.GetParError(1) + Tent.GetParError(0) / (factor[pl]);
        ymaxe[s][pl][b] = Tent.GetParError(2) + Tent.GetParError(3) / (factor[pl] * r_asym_f[pl]);
    }

    // Now creating / fitting the graphs
    y_left[s][pl]  = new TGraphErrors(NDIV_XY, ymin[s][pl], yb, ymine[s][pl], ybe);
    y_right[s][pl] = new TGraphErrors(NDIV_XY, ymax[s][pl], yb, ymaxe[s][pl], ybe);

    y_left[s][pl]->SetMarkerStyle(20);
    y_right[s][pl]->SetMarkerStyle(20);
    y_left[s][pl]->SetMarkerColor(kRed + 3);
    y_right[s][pl]->SetMarkerColor(kRed + 3);

    y_left[s][pl]->SetMarkerSize(0.8);
    y_right[s][pl]->SetMarkerSize(0.8);

    TF1 *my_fit1 = new TF1("my_fit1", thirdOrder_s, -y_lims[pl], 0, 4);
    TF1 *my_fit2 = new TF1("my_fit2", thirdOrder_s, 0, y_lims[pl], 4);
    my_fit1->SetLineWidth(4);
    my_fit2->SetLineWidth(4);
    my_fit1->SetLineColor(kRed + 3);
    my_fit2->SetLineColor(kRed + 3);


    double allowed_smear = 0.1;
    my_fit1->SetParLimits(0, Pars->XMIN[pl] - allowed_smear, Pars->XMIN[pl] + allowed_smear);
    my_fit2->SetParLimits(0, Pars->XMIN[pl] - allowed_smear, Pars->XMIN[pl] + allowed_smear);


    // slope limits. The right size needs a small adjustment
    double max_slope[5] = {1.9, 1.7, 1.65, 1.9, 1.9};
    double slope_tilt = 0.2;
    my_fit1->SetParLimits(1, -max_slope[pl], 0);
    my_fit2->SetParLimits(1,0, max_slope[pl] - slope_tilt);

    // particular sectors/plane combination
    if ( pl == 1 ) {
        my_fit1->SetParLimits(1, -max_slope[pl]-0.2, -1.65);
        if ( s == 4 ) {
            my_fit1->SetParLimits(1, -max_slope[pl]-0.2, -1.6);
        }
    }
    if ( pl == 2 ) {
        my_fit1->SetParLimits(1, -max_slope[pl]-0.2, -1.55);
    }

    // curvature limits
    double max_curvature[5] = {0.008, 0.0005, 0.001, 0.001, 0.02};
    my_fit1->SetParLimits(2, -max_curvature[pl], 0);
    my_fit2->SetParLimits(2,                  0, max_curvature[pl] );

    // particular sectors/plane combination
    if ( pl == 2 ) {
        my_fit1->SetParLimits(2,  0, max_curvature[pl] );
    }
    if ( pl == 4 ) {
        my_fit1->SetParLimits(2, 0, max_curvature[pl]);

        if (s >= 2) {
            my_fit1->SetParLimits(2, 0.1*max_curvature[pl], 2*max_curvature[pl]);
            my_fit2->SetParLimits(2, 0.1*max_curvature[pl], 2*max_curvature[pl]);
        }
        if (s == 4) {
            my_fit2->SetParLimits(2, 0.05*max_curvature[pl], 0.4*max_curvature[pl] );
        }
        if (s == 5) {
            my_fit2->SetParLimits(2, 0, 0.1*max_curvature[pl] );
        }
    }
    // third order term limits
    double max_third[5] = {0.0001, 0.00001, 0.00001, 0.0001, 0.0001};
    my_fit1->SetParLimits(3, -max_third[pl], 0);
    my_fit2->SetParLimits(3,              0, max_third[pl]);






    y_left[s][pl]->Fit("my_fit1", "REM", "", -y_lims[pl], 0);
    y_right[s][pl]->Fit("my_fit2", "REM", "", 0, y_lims[pl]);

    // Now limiting the left/right position
    // left:  x = a + b_left*y + c_left*y2
    // left:  x = a + b_left*y + c_left*y2
    // a = XMIN - b YMIN - c YMIN*YMIN
    // XMIN is the vertex vertical position of each plane's bottom corner(same in all sectors)
    // YMIN is the vertex horizontal position of each plane's bottom corner

    double a_left, a_rite;

    double b_left = my_fit1->GetParameter(1);
    double b_rite = my_fit2->GetParameter(1);
    double c_left = my_fit1->GetParameter(2);
    double c_rite = my_fit2->GetParameter(2);
    double d_left = my_fit1->GetParameter(3);
    double d_rite = my_fit2->GetParameter(3);

    a_left = Pars->XMIN[pl] - b_left * Pars->YMIN[pl][s] - c_left * Pars->YMIN[pl][s] * Pars->YMIN[pl][s] -
             d_left * Pars->YMIN[pl][s] * Pars->YMIN[pl][s] * Pars->YMIN[pl][s];
    a_rite = Pars->XMIN[pl] - b_rite * Pars->YMIN[pl][s] - c_rite * Pars->YMIN[pl][s] * Pars->YMIN[pl][s] -
             d_rite * Pars->YMIN[pl][s] * Pars->YMIN[pl][s] * Pars->YMIN[pl][s];

    my_fit1->SetParLimits(0, a_left - allowed_smear, a_left + allowed_smear);
    my_fit2->SetParLimits(0, a_rite - allowed_smear, a_rite + allowed_smear);



    y_left[s][pl]->Fit("my_fit1", "REM", "", -y_lims[pl], 0);
    y_right[s][pl]->Fit("my_fit2", "REM", "", 0, y_lims[pl]);

    if (plane == 1) {
        Pars->r1_a_left[s] = my_fit1->GetParameter(0);
        Pars->r1_a_rite[s] = my_fit2->GetParameter(0);
        Pars->r1_b_left[s] = my_fit1->GetParameter(1);
        Pars->r1_b_rite[s] = my_fit2->GetParameter(1);
        Pars->r1_c_left[s] = my_fit1->GetParameter(2);
        Pars->r1_c_rite[s] = my_fit2->GetParameter(2);
    } else if (plane == 2) {
        Pars->r2_a_left[s] = my_fit1->GetParameter(0);
        Pars->r2_a_rite[s] = my_fit2->GetParameter(0);
        Pars->r2_b_left[s] = my_fit1->GetParameter(1);
        Pars->r2_b_rite[s] = my_fit2->GetParameter(1);
        Pars->r2_c_left[s] = my_fit1->GetParameter(2);
        Pars->r2_c_rite[s] = my_fit2->GetParameter(2);
        Pars->r2_d_left[s] = my_fit1->GetParameter(3);
        Pars->r2_d_rite[s] = my_fit2->GetParameter(3);
    } else if (plane == 3) {
        Pars->r3_a_left[s] = my_fit1->GetParameter(0);
        Pars->r3_a_rite[s] = my_fit2->GetParameter(0);
        Pars->r3_b_left[s] = my_fit1->GetParameter(1);
        Pars->r3_b_rite[s] = my_fit2->GetParameter(1);
        Pars->r3_c_left[s] = my_fit1->GetParameter(2);
        Pars->r3_c_rite[s] = my_fit2->GetParameter(2);
        Pars->r3_d_left[s] = my_fit1->GetParameter(3);
        Pars->r3_d_rite[s] = my_fit2->GetParameter(3);
    } else if (plane == 5) {
        Pars->sc_a_left[s] = my_fit1->GetParameter(0);
        Pars->sc_a_rite[s] = my_fit2->GetParameter(0);
        Pars->sc_b_left[s] = my_fit1->GetParameter(1);
        Pars->sc_b_rite[s] = my_fit2->GetParameter(1);
        Pars->sc_c_left[s] = my_fit1->GetParameter(2);
        Pars->sc_c_rite[s] = my_fit2->GetParameter(2);
    }
    Cecp->Close();
}

void FiducialCut::slice_all_planes() {
    for (int s = 0; s < 6; s++) {
        // not slicing EC plane
        slice_plane(s + 1, 1);
        slice_plane(s + 1, 2);
        slice_plane(s + 1, 3);
        slice_plane(s + 1, 5);
    }
}
