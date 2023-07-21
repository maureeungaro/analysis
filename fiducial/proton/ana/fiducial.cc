#include "fiducial.h"

// Ugly: these functions have to be global to be used by TF1
// but compiling them here means we cannot use them in other files
// thus we have to call them with a different name otherwise the compiler will detect
// duplicate definitions
//
// 2 gaussians + parabole
Double_t fid_parabole(   Double_t *x, Double_t *par)  { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] ; }
double thirdOrder(double *x, double *par)             { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] ; }


// constructor using chisto and cpars
FiducialCut::FiducialCut(chistos *common_histo, cpars *common_pars, string P, const Color_t c[4], bool logz ) {
    H = common_histo;
    Pars = common_pars;
    PRINT = P;
    LOGZ = logz;
    for (int cc = 0; cc < 4; cc++) {
        colors[cc] = c[cc];
    }

    for (int s = 0; s < 7; s++) {
        for (int pl = 0; pl < 5; pl++) {
            y_left[s][pl] = NULL;
            y_right[s][pl] = NULL;
        }
    }

    double x_lims[5] = { 40,   100,   150,  200,   200};

    for (int s = 0; s < 7; s++) {
        for (int pl = 0; pl < 5; pl++) {
            // don't consider EC
            if (pl == 3) continue;

            left_para[s][pl] = new TF1(Form("left_para_s%d_pl%d", s + 1, pl + 1), fid_parabole, -x_lims[pl],       Pars->YMIN[pl][s], 4);
            rite_para[s][pl] = new TF1(Form("rite_para_s%d_pl%d", s + 1, pl + 1), fid_parabole, Pars->YMIN[pl][s], x_lims[pl], 4);

            left_para[s][pl]->SetLineColor(kRed + 3);
            rite_para[s][pl]->SetLineColor(kRed + 3);
            left_para[s][pl]->SetLineStyle(1);
            rite_para[s][pl]->SetLineStyle(1);
            left_para[s][pl]->SetLineWidth(2);
            rite_para[s][pl]->SetLineWidth(2);

            //double a_left=0, a_rite=0;

            if(pl==0) {
                left_para[s][pl]->SetParameter( 0, Pars->r1_a_left[s]);
                rite_para[s][pl]->SetParameter( 0, Pars->r1_a_rite[s]);
                left_para[s][pl]->SetParameter( 1, Pars->r1_b_left[s]);
                rite_para[s][pl]->SetParameter( 1, Pars->r1_b_rite[s]);
                left_para[s][pl]->SetParameter( 2, Pars->r1_c_left[s]);
                rite_para[s][pl]->SetParameter( 2, Pars->r1_c_rite[s]);
            } else if(pl==1) {
                left_para[s][pl]->SetParameter(0, Pars->r2_a_left[s]);
                rite_para[s][pl]->SetParameter(0, Pars->r2_a_rite[s]);
                left_para[s][pl]->SetParameter(1, Pars->r2_b_left[s]);
                rite_para[s][pl]->SetParameter(1, Pars->r2_b_rite[s]);
                left_para[s][pl]->SetParameter(2, Pars->r2_c_left[s]);
                rite_para[s][pl]->SetParameter(2, Pars->r2_c_rite[s]);
                left_para[s][pl]->SetParameter(3, Pars->r2_d_left[s]);
                rite_para[s][pl]->SetParameter(3, Pars->r2_d_rite[s]);
            } else if(pl==2) {
                left_para[s][pl]->SetParameter( 0, Pars->r3_a_left[s]);
                rite_para[s][pl]->SetParameter( 0, Pars->r3_a_rite[s]);
                left_para[s][pl]->SetParameter( 1, Pars->r3_b_left[s]);
                rite_para[s][pl]->SetParameter( 1, Pars->r3_b_rite[s]);
                left_para[s][pl]->SetParameter( 2, Pars->r3_c_left[s]);
                rite_para[s][pl]->SetParameter( 2, Pars->r3_c_rite[s]);
                left_para[s][pl]->SetParameter( 3, Pars->r3_d_left[s]);
                rite_para[s][pl]->SetParameter( 3, Pars->r3_d_rite[s]);
            } else if(pl==4) {
                left_para[s][pl]->SetParameter( 0, Pars->sc_a_left[s]);
                rite_para[s][pl]->SetParameter( 0, Pars->sc_a_rite[s]);
                left_para[s][pl]->SetParameter( 1, Pars->sc_b_left[s]);
                rite_para[s][pl]->SetParameter( 1, Pars->sc_b_rite[s]);
                left_para[s][pl]->SetParameter( 2, Pars->sc_c_left[s]);
                rite_para[s][pl]->SetParameter( 2, Pars->sc_c_rite[s]);
            }

        }
    }

    for(int s=0; s<6; s++) {
        for (int c = 0; c < 10; c++) {
            for (int w = 0; w < 2; w++) {
                for (int pl = 0; pl < 2; pl++) {
                    wire_axial[s][pl][c][w] = NULL;
                    wire_stereo[s][pl][c][w] = NULL;
                }
            }
        }
    }

    for(int c=0; c<Pars->r1_axial_limits.size()/3; c++) {
        int s =  Pars->r1_axial_limits[c*3] - 1;
        wire_axial[s][0][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[0], x_lims[0]);
        wire_axial[s][0][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[0], x_lims[0]);
        wire_axial[s][0][c][0]->SetParameter(0, Pars->r1_axial_limits[c*3+1]);
        wire_axial[s][0][c][1]->SetParameter(0, Pars->r1_axial_limits[c*3+2]);
        wire_axial[s][0][c][0]->SetLineWidth(1);
        wire_axial[s][0][c][0]->SetLineStyle(9);
        wire_axial[s][0][c][1]->SetLineWidth(1);
        wire_axial[s][0][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->r2_axial_limits.size()/3; c++) {
        int s =  Pars->r2_axial_limits[c*3] - 1;
        wire_axial[s][1][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[1], x_lims[1]);
        wire_axial[s][1][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[1], x_lims[1]);
        wire_axial[s][1][c][0]->SetParameter(0, Pars->r2_axial_limits[c*3+1]);
        wire_axial[s][1][c][1]->SetParameter(0, Pars->r2_axial_limits[c*3+2]);
        wire_axial[s][1][c][0]->SetLineWidth(1);
        wire_axial[s][1][c][0]->SetLineStyle(9);
        wire_axial[s][1][c][1]->SetLineWidth(1);
        wire_axial[s][1][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->r3_axial_limits.size()/3; c++) {
        int s =  Pars->r3_axial_limits[c*3] - 1;
        wire_axial[s][2][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[2], x_lims[2]);
        wire_axial[s][2][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[2], x_lims[2]);
        wire_axial[s][2][c][0]->SetParameter(0, Pars->r3_axial_limits[c*3+1]);
        wire_axial[s][2][c][1]->SetParameter(0, Pars->r3_axial_limits[c*3+2]);
        wire_axial[s][2][c][0]->SetLineWidth(1);
        wire_axial[s][2][c][0]->SetLineStyle(9);
        wire_axial[s][2][c][1]->SetLineWidth(1);
        wire_axial[s][2][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->sc_axial_limits.size()/3; c++) {
        int s =  Pars->sc_axial_limits[c*3] - 1;
        wire_axial[s][3][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[3], x_lims[3]);
        wire_axial[s][3][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[3], x_lims[3]);
        wire_axial[s][3][c][0]->SetParameter(0, Pars->sc_axial_limits[c*3+1]);
        wire_axial[s][3][c][1]->SetParameter(0, Pars->sc_axial_limits[c*3+2]);
        wire_axial[s][3][c][0]->SetLineWidth(1);
        wire_axial[s][3][c][0]->SetLineStyle(9);
        wire_axial[s][3][c][1]->SetLineWidth(1);
        wire_axial[s][3][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->r1_stereo_limits.size()/3; c++) {
        int s =  Pars->r1_stereo_limits[c*3] - 1;
        wire_stereo[s][0][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[0], x_lims[0]);
        wire_stereo[s][0][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[0], x_lims[0]);
        wire_stereo[s][0][c][0]->SetParameter(0, Pars->r1_stereo_limits[c*3+1]);
        wire_stereo[s][0][c][1]->SetParameter(0, Pars->r1_stereo_limits[c*3+2]);
        wire_stereo[s][0][c][0]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][0][c][1]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][0][c][0]->SetLineWidth(1);
        wire_stereo[s][0][c][0]->SetLineStyle(9);
        wire_stereo[s][0][c][1]->SetLineWidth(1);
        wire_stereo[s][0][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->r2_stereo_limits.size()/3; c++) {
        int s =  Pars->r2_stereo_limits[c*3] - 1;
        wire_stereo[s][1][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[1], x_lims[1]);
        wire_stereo[s][1][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[1], x_lims[1]);
        wire_stereo[s][1][c][0]->SetParameter(0, Pars->r2_stereo_limits[c*3+1]);
        wire_stereo[s][1][c][1]->SetParameter(0, Pars->r2_stereo_limits[c*3+2]);
        wire_stereo[s][1][c][0]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][1][c][1]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][1][c][0]->SetLineWidth(1);
        wire_stereo[s][1][c][0]->SetLineStyle(9);
        wire_stereo[s][1][c][1]->SetLineWidth(1);
        wire_stereo[s][1][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->r3_stereo_limits.size()/3; c++) {
        int s =  Pars->r3_stereo_limits[c*3] - 1;
        wire_stereo[s][2][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[2], x_lims[2]);
        wire_stereo[s][2][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[2], x_lims[2]);
        wire_stereo[s][2][c][0]->SetParameter(0, Pars->r3_stereo_limits[c*3+1]);
        wire_stereo[s][2][c][1]->SetParameter(0, Pars->r3_stereo_limits[c*3+2]);
        wire_stereo[s][2][c][0]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][2][c][1]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][2][c][0]->SetLineWidth(1);
        wire_stereo[s][2][c][0]->SetLineStyle(9);
        wire_stereo[s][2][c][1]->SetLineWidth(1);
        wire_stereo[s][2][c][1]->SetLineStyle(9);
    }

    for(int c=0; c<Pars->sc_stereo_limits.size()/3; c++) {
        int s =  Pars->sc_stereo_limits[c*3] - 1;
        wire_stereo[s][3][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[3], x_lims[3]);
        wire_stereo[s][3][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[3], x_lims[3]);
        wire_stereo[s][3][c][0]->SetParameter(0, Pars->sc_stereo_limits[c*3+1]);
        wire_stereo[s][3][c][1]->SetParameter(0, Pars->sc_stereo_limits[c*3+2]);
        wire_stereo[s][3][c][0]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][3][c][1]->SetParameter(1, -Pars->stereo_angle_slope);
        wire_stereo[s][3][c][0]->SetLineWidth(1);
        wire_stereo[s][3][c][0]->SetLineStyle(9);
        wire_stereo[s][3][c][1]->SetLineWidth(1);
        wire_stereo[s][3][c][1]->SetLineStyle(9);
    }


}

//TGraph* FiducialCut::fidcut(int s, double p, int which)
//{
//	const int npoints = 160;
//	double x[npoints];
//	double y[npoints];
//	for(int i=0; i<npoints; i++) {
//		x[i] = 10 + i/3.0;
//
//		if(which ==  1 )  y[i] =  Pars->dphi(s, p, x[i]);
//		if(which == -1 )  y[i] = -Pars->dphi(s, p, x[i]);
//		if(y[i] == 0) x[i] = Pars->theta_cut(s, p);
//	}
//
//	TGraph *a = new TGraph(npoints, x, y);
//	a->SetLineWidth(2);
//	a->SetLineColor(kRed+3);
//	a->SetLineStyle(9);
//
//	return a;
//}



void FiducialCut::draw_limits(int sector, int plane)
{
    int s  = sector - 1;

    if(plane == 1) {
        for(int c=0; c<Pars->r1_axial_limits.size()/3; c++) {
            if(s == Pars->r1_axial_limits[c*3]-1) {
                wire_axial[s][0][c][0]->Draw("same");
                wire_axial[s][0][c][1]->Draw("same");
            }
        }
        for(int c=0; c<Pars->r1_stereo_limits.size()/3; c++) {
            if(s == Pars->r1_stereo_limits[c*3]-1) {
                wire_stereo[s][0][c][0]->Draw("same");
                wire_stereo[s][0][c][1]->Draw("same");
            }
        }
    } else if(plane == 2) {
        for(int c=0; c<Pars->r2_axial_limits.size()/3; c++) {
            if(s == Pars->r2_axial_limits[c*3]-1) {
                wire_axial[s][1][c][0]->Draw("same");
                wire_axial[s][1][c][1]->Draw("same");
            }
        }
        for(int c=0; c<Pars->r2_stereo_limits.size()/3; c++) {
            if(s == Pars->r2_stereo_limits[c*3]-1) {
                wire_stereo[s][1][c][0]->Draw("same");
                wire_stereo[s][1][c][1]->Draw("same");
            }
        }
    } else if(plane == 3) {
        for(int c=0; c<Pars->r3_axial_limits.size()/3; c++) {
            if(s == Pars->r3_axial_limits[c*3]-1) {
                wire_axial[s][2][c][0]->Draw("same");
                wire_axial[s][2][c][1]->Draw("same");
            }
        }
        for(int c=0; c<Pars->r3_stereo_limits.size()/3; c++) {
            if(s == Pars->r3_stereo_limits[c*3]-1) {
                wire_stereo[s][2][c][0]->Draw("same");
                wire_stereo[s][2][c][1]->Draw("same");
            }
        }
    } else if(plane == 5) {
        for(int c=0; c<Pars->sc_axial_limits.size()/3; c++) {
            if(s == Pars->sc_axial_limits[c*3]-1) {
                wire_axial[s][3][c][0]->Draw("same");
                wire_axial[s][3][c][1]->Draw("same");
            }
        }
        for(int c=0; c<Pars->sc_stereo_limits.size()/3; c++) {
            if(s == Pars->sc_stereo_limits[c*3]-1) {
                wire_stereo[s][3][c][0]->Draw("same");
                wire_stereo[s][3][c][1]->Draw("same");
            }
        }
    }

}



void FiducialCut::draw_fiducial(int sector, int plane)
{
    int s = sector - 1;
    int pl = plane - 1;

    double y_lims[5]  = { 30,   90,   150,  200,   200};

    TF1 *my_fit1 = new TF1("my_fit1",  thirdOrder, -y_lims[pl],   Pars->YMIN[pl][s], 4);
    TF1 *my_fit2 = new TF1("my_fit2",  thirdOrder,                Pars->YMIN[pl][s], y_lims[pl], 4);

    my_fit1->SetLineWidth(2);
    my_fit2->SetLineWidth(2);

    if(pl == 0) {
        my_fit1->SetParameter(0, Pars->r1_a_left[s]);
        my_fit1->SetParameter(1, Pars->r1_b_left[s]);
        my_fit1->SetParameter(2, Pars->r1_c_left[s]);

        my_fit2->SetParameter(0, Pars->r1_a_rite[s]);
        my_fit2->SetParameter(1, Pars->r1_b_rite[s]);
        my_fit2->SetParameter(2, Pars->r1_c_rite[s]);
    } else if(pl == 1) {
        my_fit1->SetParameter(0, Pars->r2_a_left[s]);
        my_fit1->SetParameter(1, Pars->r2_b_left[s]);
        my_fit1->SetParameter(2, Pars->r2_c_left[s]);
        my_fit1->SetParameter(3, Pars->r2_d_left[s]);

        my_fit2->SetParameter(0, Pars->r2_a_rite[s]);
        my_fit2->SetParameter(1, Pars->r2_b_rite[s]);
        my_fit2->SetParameter(2, Pars->r2_c_rite[s]);
        my_fit2->SetParameter(3, Pars->r2_d_rite[s]);
    } else if(pl == 2) {
        my_fit1->SetParameter(0, Pars->r3_a_left[s]);
        my_fit1->SetParameter(1, Pars->r3_b_left[s]);
        my_fit1->SetParameter(2, Pars->r3_c_left[s]);
        my_fit1->SetParameter(3, Pars->r3_d_left[s]);

        my_fit2->SetParameter(0, Pars->r3_a_rite[s]);
        my_fit2->SetParameter(1, Pars->r3_b_rite[s]);
        my_fit2->SetParameter(2, Pars->r3_c_rite[s]);
        my_fit2->SetParameter(3, Pars->r3_d_rite[s]);
    } else if(pl == 4) {
        my_fit1->SetParameter(0, Pars->sc_a_left[s]);
        my_fit1->SetParameter(1, Pars->sc_b_left[s]);
        my_fit1->SetParameter(2, Pars->sc_c_left[s]);

        my_fit2->SetParameter(0, Pars->sc_a_rite[s]);
        my_fit2->SetParameter(1, Pars->sc_b_rite[s]);
        my_fit2->SetParameter(2, Pars->sc_c_rite[s]);
    }
    my_fit1->Draw("same");
    my_fit2->Draw("same");
}
