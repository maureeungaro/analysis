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

    // don't fit last slice in GSIM
	for(int b=0; b<NDIV-is_simulation*2; b++) {
		projname = hname + "_";
		projname += to_string(b+1);
		cout << " Fitting slice " << b+1 << " to histo: " << projname << ", mom = " << xb[b] << endl;
		if(xb[b] > 0.6) {
            h->ProjectionY(projname.c_str(), b * db, (b + 1) * db);
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
			MyFit->SetParLimits(4, -3, 0.2);

			// limits on the second gaussian: mean must be above 0.5ns
			if(xb[b] <= 0.7) {
				MyFit->SetParameter(7, 10.5);
				MyFit->SetParLimits(7, 5.0, 30);
			} else if(xb[b] > 0.7 && xb[b] <= 1.7) {
				MyFit->SetParameter(7, 2.5);
				MyFit->SetParLimits(7, 2.0, 30);
			} else if(xb[b] > 1.7) {
				MyFit->SetParameter(7, 1);
				MyFit->SetParLimits(7, 0.5, 5);
			}

			MyFit->SetParameter(6,    dt_1d[s][b]->GetFunction("gaus")->GetParameter(0)/2);
			MyFit->SetParLimits(6, 0, dt_1d[s][b]->GetFunction("gaus")->GetParameter(0));

			dt_1d[s][b]->Fit("MyFit", "REM");
			dtmean[s][b] = MyFit->GetParameter(4);
			dtsigm[s][b] = fabs(MyFit->GetParameter(5));
			
			if(MyFit->GetParameter(7) - 3*fabs(MyFit->GetParameter(8)) > MyFit->GetParameter(4) + 3*fabs(MyFit->GetParameter(5)) ) {
				dtsigm[s][b] = (MyFit->GetParameter(7) - 3*fabs(MyFit->GetParameter(8)) - MyFit->GetParameter(4))/3.0;
				cout << " Sigma is enlarged from " << fabs(MyFit->GetParameter(5)) << "  to " << dtsigm[s][b] << endl;
			}

			// putting lower limits on sigma for certain b

			if(dtsigm[s][b] < 0.4 && b>1 && b<4) dtsigm[s][b] = 0.4;

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

	dt_mean[s] = new TGraphErrors(NDIV, xb, dtmean[s], xbe, dtmeane[s]);
	dt_sigm[s] = new TGraphErrors(NDIV, xb, dtsigm[s], xbe, dtsigme[s]);
		
	dt_mean[s]->Fit("pol5", "REM", "", min_limit_dt, max_limit_dt);
	dt_sigm[s]->Fit("pol5", "REM", "", min_limit_dt, max_limit_dt);
		
	Pars->dt_mom_mean_a[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(0);
	Pars->dt_mom_mean_b[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(1);
	Pars->dt_mom_mean_c[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(2);
	Pars->dt_mom_mean_d[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(3);
	Pars->dt_mom_mean_e[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(4);
	Pars->dt_mom_mean_f[s] = dt_mean[s]->GetFunction("pol5")->GetParameter(5);
		
	Pars->dt_mom_sigm_a[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(0);
	Pars->dt_mom_sigm_b[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(1);
	Pars->dt_mom_sigm_c[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(2);
	Pars->dt_mom_sigm_d[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(3);
	Pars->dt_mom_sigm_e[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(4);
	Pars->dt_mom_sigm_f[s] = dt_sigm[s]->GetFunction("pol5")->GetParameter(5);

	// sector 5 fits do not work. Using sector 6 sigmas for sector 6.
	if(s==5) {
		Pars->dt_mom_sigm_a[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(0);
		Pars->dt_mom_sigm_b[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(1);
		Pars->dt_mom_sigm_c[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(2);
		Pars->dt_mom_sigm_d[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(3);
		Pars->dt_mom_sigm_e[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(4);
		Pars->dt_mom_sigm_f[4] = dt_sigm[s]->GetFunction("pol5")->GetParameter(5);
	}



}
















