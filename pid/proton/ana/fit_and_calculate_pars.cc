#include "tof_match.h"

// root
#include "TROOT.h"
#include "TCanvas.h"

// Ugly: these functions have to be global to be used by TF1
// but compiling them here means we cannot use them in other files (e.g. ec_match.cc)
// thus we have to copy them in ec_match.cc with a different name otherwise the compiler will find
// about duplicate definitions
//
// 2 gaussians + parabole
Double_t ftof_parabole(   Double_t *x, Double_t *par)  { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] ; }
Double_t ftof_gaussian(   Double_t *x, Double_t *par)  { return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2)); }
Double_t ftof_gauss_para(Double_t *x, Double_t *par)   { return ftof_parabole(x, par) + ftof_gaussian(x, &par[3]) ; }
Double_t ftof_gauss2_para(Double_t *x, Double_t *par)  { return ftof_parabole(x, par) + ftof_gaussian(x, &par[3]) + ftof_gaussian(x, &par[6]); }

void TOF_Match::fit_and_calculate_pars(TH2F *h, TH2F *h2, int sector)
{
	string hname = h->GetName();
	string projname;
	
	TCanvas *C2D  = new TCanvas("C2D", "C2D", csize, csize);
    C2D->cd();
	
	TF1 *MyFit = new TF1("MyFit", ftof_gauss2_para, -10.0, 30.0, 9);
	MyFit->SetLineColor(kGreen+3);
	MyFit->SetLineWidth(2);
	
	int s = sector -1;

	int NBINS = h->GetNbinsX();
    int NDIV = TOF_Match::NDIV;
	int db = NBINS/NDIV;
	double xb[NDIV], xbe[NDIV];
	double dp = ( h->GetXaxis()->GetXmax() - h->GetXaxis()->GetXmin() ) / NDIV;

	for(int b=0; b<NDIV; b++) {

        xb[b]  = h->GetXaxis()->GetXmin() + (b+0.5)*dp;
		xbe[b] = 0;

		MySignal[s][b] = new TF1(Form("MySignal_sect%d_slice%d", s+1, b+1), ftof_gaussian, -4.0, 4.0, 3);
		MySignal[s][b]->SetLineColor(kBlue+2);
		MySignal[s][b]->SetLineWidth(2);
	
		MyBackground[s][b] = new TF1(Form("MyBackground_sect%d_slice%d", s+1, b+1), ftof_gauss_para, -4.0, 4.0, 6);
		MyBackground[s][b]->SetLineColor(kRed+2);
		MyBackground[s][b]->SetLineWidth(2);
	}

    // don't fit last 2 slices in GSIM
	for(int b=0; b< NDIV - is_simulation*2; b++) {

		projname = hname + "_";
		projname += to_string(b+1);
		cout << " Fitting slice " << b+1 << " to histo: " << projname << ", mom = " << xb[b] << endl;

        // h2 is the zoomed version of h
        // this condition never happens?
        if(b > 1) {
            h->ProjectionY( projname.c_str(), b * db, (b + 1) * db);
        } else {
            h2->ProjectionY(projname.c_str(), b * db, (b + 1) * db);
        }
		
		if(hname.find("dt") != string::npos) {

            dt_1d[s][b] = (TH1F*)gROOT->Get(projname.c_str());
			dt_1d[s][b]->SetLineStyle(1);
			dt_1d[s][b]->SetLineColor(7);
			dt_1d[s][b]->SetFillColor(kGreen-9);
			dt_1d[s][b]->SetFillStyle(3002);
			
			dt_1d[s][b]->Fit("gaus", "q0");
			dt_1d[s][b]->GetFunction("gaus")->SetParLimits(0, 0, dt_1d[s][b]->GetEntries());
			dt_1d[s][b]->Fit("gaus", "q0");

            MyFit->SetParameter(3, dt_1d[s][b]->GetFunction("gaus")->GetParameter(0));
			MyFit->SetParameter(5, dt_1d[s][b]->GetFunction("gaus")->GetParameter(2));
			MyFit->SetParameter(8, dt_1d[s][b]->GetFunction("gaus")->GetParameter(2)/2);
			
			// limits on the first gaussian
			MyFit->SetParameter(4, 0);
			MyFit->SetParLimits(4, -1.5, 0.2);

            if ( b >= 4 && b < 7 ) {
                MyFit->SetParLimits(4, -0.5, 0.5);
                MyFit->SetParLimits(5,  0.0, 0.2);
            } else if ( b >= 7 ) {
                MyFit->SetParLimits(4, -1.5, 0.5);
                MyFit->SetParLimits(5,  0.0, 0.5);
            }

			// limits on the second gaussian
            // depending on momentum (slice value)
            // can check with TOFMatch->DrawFit(0, 3)
			if(b == 0) {
				MyFit->SetParameter(7, 10.5);
				MyFit->SetParLimits(7, 5.0, 30);
			} else if(b > 0 && b <= 2) {
				MyFit->SetParameter(7, 2.5);
				MyFit->SetParLimits(7, 2, 30);
			} else if(b > 2 && b <= 4) {
                MyFit->SetParameter(7, 1.5);
                MyFit->SetParLimits(7, 0.5, 2.5);
                MyFit->SetParLimits(8, 0.0, 0.5);
            } else if(b > 4) {
				MyFit->SetParameter(7, 1);
				MyFit->SetParLimits(7, 0.0, 2);
                MyFit->SetParLimits(8, 0.0, 0.2);
			}

			MyFit->SetParameter(6,    dt_1d[s][b]->GetFunction("gaus")->GetParameter(0)/2);
			MyFit->SetParLimits(6, 0, dt_1d[s][b]->GetFunction("gaus")->GetParameter(0));

			dt_1d[s][b]->Fit("MyFit", "QREM");


            double first_gauss_mean   = MyFit->GetParameter(4);
            double first_gauss_sigma  = fabs(MyFit->GetParameter(5));
            double second_gauss_mean  = MyFit->GetParameter(7);
            double second_gauss_sigma = fabs(MyFit->GetParameter(8));

            dtmean[s][b] = first_gauss_mean;
            dtsigm[s][b] = first_gauss_sigma;

            double NSGIMA0 = Pars->NSIGMAS[0];
            double pion_lower_limit   = second_gauss_mean - NSGIMA0 * second_gauss_sigma;
            double proton_upper_limit = first_gauss_mean  + NSGIMA0 * first_gauss_sigma;

			if( b > 0 && pion_lower_limit > proton_upper_limit ) {
				dtsigm[s][b] = ( pion_lower_limit - proton_upper_limit ) + first_gauss_sigma;
				cout << " proton upper limit is enlarged from " << proton_upper_limit << "  to " << dtsigm[s][b] << endl;
			} else {
                dtsigm[s][b] = first_gauss_sigma;
            }

            cout << b << " first_gauss_mean " << first_gauss_mean << " first_gauss_sigma " << first_gauss_sigma ;
            cout << " second_gauss_mean " << second_gauss_mean << " second_gauss_sigma " << second_gauss_sigma ;
            cout << " dtsigm[s][b] " << dtsigm[s][b] << endl;


			// manually changing some values to make the fit look better


			dtmeane[s][b] = MyFit->GetParError(4);
			dtsigme[s][b] = MyFit->GetParError(5);
		}
	}

    // special cases for simulation
	if(is_simulation) {
		dtmean[s][NDIV-2]  = dtmean[s][NDIV-3];
		dtsigm[s][NDIV-2]  = dtsigm[s][NDIV-3]*2;
		dtmeane[s][NDIV-2] = dtmeane[s][NDIV-3];
		dtsigme[s][NDIV-2] = dtsigme[s][NDIV-3]*2;
		dtmean[s][NDIV-1]  = dtmean[s][NDIV-2];
		dtsigm[s][NDIV-1]  = dtsigm[s][NDIV-2];
		dtmeane[s][NDIV-1] = dtmeane[s][NDIV-2];
		dtsigme[s][NDIV-1] = dtsigme[s][NDIV-2];
	}

    TCanvas *C2DFitsC  = new TCanvas("C2DFitsC", "C2DFitsC", csize, csize);
    TPad    *C2DFitsP  = new TPad("C2DFitsP", "C2DFitsP", 0.02, 0.00,  0.98, 0.98);
    C2DFitsP->Divide(1, 2);
    C2DFitsP->Draw();


    dt_mean[s] = new TGraphErrors(NDIV, xb, dtmean[s], xbe, dtmeane[s]);
	dt_sigm[s] = new TGraphErrors(NDIV, xb, dtsigm[s], xbe, dtsigme[s]);

    dt_mean[s]->SetMarkerStyle(20);
    dt_mean[s]->SetMarkerSize(3.0);

    dt_sigm[s]->SetMarkerStyle(22);
    dt_sigm[s]->SetMarkerSize(3.0);

    C2DFitsP->cd(1);
    dt_mean[s]->Draw("AP");
    dt_mean[s]->Fit("pol5", "QREM", "", min_limit_dt, max_limit_dt);
    C2DFitsP->cd(2);
    dt_sigm[s]->Draw("AP");
	dt_sigm[s]->Fit("pol2", "QREM", "", min_limit_dt, max_limit_dt);

    C2DFitsC->Update();
		
	Pars->dt_mom_mean_a[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(0);
	Pars->dt_mom_mean_b[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(1);
	Pars->dt_mom_mean_c[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(2);
	Pars->dt_mom_mean_d[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(3);
	Pars->dt_mom_mean_e[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(4);
	Pars->dt_mom_mean_f[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(5);
		
//	Pars->dt_mom_sigm_a[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(0);
//	Pars->dt_mom_sigm_b[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(1);
//	Pars->dt_mom_sigm_c[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(2);
//	Pars->dt_mom_sigm_d[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(3);
//	Pars->dt_mom_sigm_e[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(4);
//	Pars->dt_mom_sigm_f[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(5);

    Pars->dt_mom_sigm_a[s] = dt_sigm[s]->GetFunction("pol2")->GetParameter(0);
    Pars->dt_mom_sigm_b[s] = dt_sigm[s]->GetFunction("pol2")->GetParameter(1);
    Pars->dt_mom_sigm_c[s] = dt_sigm[s]->GetFunction("pol2")->GetParameter(2);
    Pars->dt_mom_sigm_d[s] = 0;
    Pars->dt_mom_sigm_e[s] = 0;
    Pars->dt_mom_sigm_f[s] = 0;


    // sector 5 fits do not work. Using sector 6 sigmas for sector 6
    // this doesn't seem to be true anymore. Using sector 5 fits for sector 5
//	if(s==5) {
//		Pars->dt_mom_sigm_a[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(0);
//		Pars->dt_mom_sigm_b[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(1);
//		Pars->dt_mom_sigm_c[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(2);
//		Pars->dt_mom_sigm_d[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(3);
//		Pars->dt_mom_sigm_e[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(4);
//		Pars->dt_mom_sigm_f[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(5);
//	}



}
















