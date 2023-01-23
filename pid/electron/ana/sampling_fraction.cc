#include "ec_match.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"

// Ugly: these functions have to be global to be used by TF1
// but compiling them here means we cannot use them in other files (e.g. ec_match.cc)
// thus we have to copy them in ec_match.cc with a different name otherwise the compiler will find
// about duplicate definitions
//
// gaussian + parabole
Double_t ecm_parabole(   Double_t *x, Double_t *par)  { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] ; }
Double_t ecm_gaussian(   Double_t *x, Double_t *par)  { return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2)); }
Double_t ecm_gauss_para( Double_t *x, Double_t *par)  { return ecm_parabole(x, par) + ecm_gaussian(x, &par[3]) ; }

void EC_Match::calc_sf(int sector)
{
	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TCanvas *Cecp  = new TCanvas("Cecp", "Cecp", csize, csize);
	
	TF1 *MyFit = new TF1("MyFit", ecm_gauss_para, 0.15, 0.45, 6);
	MyFit->SetLineColor(kRed+2);
	MyFit->SetLineWidth(1);
	
	int NBINS = H->ecp[1][0]->GetNbinsX();

    int db = NBINS/EC_Match::NDIV;
	int s = sector - 1;

    double xb[EC_Match::NDIV], xbe[EC_Match::NDIV];
	double dp = ( H->ecp[1][0]->GetXaxis()->GetXmax() - H->ecp[1][0]->GetXaxis()->GetXmin() ) / EC_Match::NDIV;

    for(int b=0; b<EC_Match::NDIV; b++) {
		xb[b]  = H->ecp[1][0]->GetXaxis()->GetXmin() + (b+0.5)*dp;
		xbe[b] = 0;
	}
	
	// Slicing + fitting
	cout << " Fitting sector " << s+1 << endl;

	for(int b=0; b<EC_Match::NDIV; b++) {

		H->ecp[1][s]->ProjectionY(Form("ecp1d_s%d_b%d", s+1, b+1), b*db, (b+1)*db);
		ecp1d[s][b] = (TH1F*)gROOT->Get(Form("ecp1d_s%d_b%d", s+1, b+1));

        cout << " Fitting slice " << b+1 << " that has " << ecp1d[s][b]->GetEntries() << " entries." << endl;

        if(ecp1d[s][b]->GetEntries() > 10) {
			ecp1d[s][b]->Fit("gaus", "Q");
			MyFit->SetParameter(3, ecp1d[s][b]->GetFunction("gaus")->GetParameter(0));
			MyFit->SetParameter(4, ecp1d[s][b]->GetFunction("gaus")->GetParameter(1));
			MyFit->SetParameter(5, ecp1d[s][b]->GetFunction("gaus")->GetParameter(2));
			ecp1d[s][b]->Fit("MyFit", "QREM");
			ecpmean[s][b]  = MyFit->GetParameter(4);
			ecpsigm[s][b]  = MyFit->GetParameter(5);
			ecpmeane[s][b] = MyFit->GetParError(4);
			ecpsigme[s][b] = MyFit->GetParError(5);
		} else {
			ecpmean[s][b]  = 0.27;
			ecpsigm[s][b]  = 0.0;
			ecpmeane[s][b] = 1.0;
			ecpsigme[s][b] = 1.0;
		}
	}
	
	// Now creating / fitting the graphs
	sf_mean[s] = new TGraphErrors(EC_Match::NDIV, xb, ecpmean[s], xbe, ecpmeane[s]);
	sf_sigm[s] = new TGraphErrors(EC_Match::NDIV, xb, ecpsigm[s], xbe, ecpsigme[s]);
		
	sf_mean[s]->Fit("pol3", "REM", "", min_limit_sf, max_limit_sf);
	sf_sigm[s]->Fit("pol3", "REM", "", min_limit_sf, max_limit_sf);
		
	Pars->ecp_mean_a[s] = sf_mean[s]->GetFunction("pol3")->GetParameter(0);
	Pars->ecp_mean_b[s] = sf_mean[s]->GetFunction("pol3")->GetParameter(1);
	Pars->ecp_mean_c[s] = sf_mean[s]->GetFunction("pol3")->GetParameter(2);
	Pars->ecp_mean_d[s] = sf_mean[s]->GetFunction("pol3")->GetParameter(3);
		
	Pars->ecp_sigm_a[s] = sf_sigm[s]->GetFunction("pol3")->GetParameter(0);
	Pars->ecp_sigm_b[s] = sf_sigm[s]->GetFunction("pol3")->GetParameter(1);
	Pars->ecp_sigm_c[s] = sf_sigm[s]->GetFunction("pol3")->GetParameter(2);
	Pars->ecp_sigm_d[s] = sf_sigm[s]->GetFunction("pol3")->GetParameter(3);

    Cecp->Close();

}


void EC_Match::calc_sf_all_sectors()
{
    for(int s=0; s<6; s++) {
        calc_sf(s+1);
    }
}


















