#include "fiducial.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"

void FiducialCut::show_phis(int sector, int mom, int plane)
{
    int s = sector - 1;
    int m = mom - 1;
    int pl = plane - 1;
	
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	lab.SetTextSize(0.16);
	lab.SetTextFont(42);
	
	
	TCanvas *CphisS = new TCanvas(Form("CphisS%d", s+1), Form("CphisS%d", s+1), csize, csize);
	TPad    *PphisS = new TPad(Form("PphisS%d", s+1), Form("PphisS%d", s+1), 0.02, 0.05,  0.98, 0.92);
	PphisS->Divide(3, 8);
	PphisS->Draw();
	
	// ndivisions in theta
	int NBINS        = H->phi_theta[0][s][m]->GetNbinsX();
	int DB =  NBINS/NDIV_T; 
	
//	double theta_min =  H->phi_theta[0][s][m]->GetXaxis()->GetXmin();
//	double theta_max =  H->phi_theta[0][s][m]->GetXaxis()->GetXmax();

	for(int t=0; t<NDIV_T; t++) {
		H->phi_theta[0][s][m]->ProjectionY(Form("theta_slice_theta%d_s%d_m%d_befor", t+1, s+1, m+1), t*DB, (t+1)*DB);
		H->phi_theta[3][s][m]->ProjectionY(Form("theta_slice_theta%d_s%d_m%d_after", t+1, s+1, m+1), t*DB, (t+1)*DB);

        phis_befor[s][pl][m][t] = (TH1F*)gROOT->Get(Form("theta_slice_theta%d_s%d_m%d_befor", t+1, s+1, m+1));
		phis_after[s][pl][m][t] = (TH1F*)gROOT->Get(Form("theta_slice_theta%d_s%d_m%d_after", t+1, s+1, m+1));
		
		phis_after[s][pl][m][t]->SetLineColor(2);

		phis_befor[s][pl][m][t]->GetXaxis()->SetTitleSize(0.052);
		phis_befor[s][pl][m][t]->GetXaxis()->SetTitleOffset(1.14);
		phis_befor[s][pl][m][t]->GetYaxis()->SetTitleSize(0.054);
		phis_befor[s][pl][m][t]->GetYaxis()->SetTitleOffset(1.32);
		phis_befor[s][pl][m][t]->GetXaxis()->SetLabelSize(0.12);
		phis_befor[s][pl][m][t]->GetYaxis()->SetLabelSize(0.12);
		phis_befor[s][pl][m][t]->GetXaxis()->SetLabelOffset(0.05);
		
		phis_befor[s][pl][m][t]->GetXaxis()->SetNdivisions(10);
		phis_befor[s][pl][m][t]->GetYaxis()->SetNdivisions(5);

		
		PphisS->cd(t+1);
		
		phis_befor[s][pl][m][t]->Draw();
		phis_after[s][pl][m][t]->Draw("same");

		double tmin = H->phi_theta[0][s][m]->GetXaxis()->GetBinCenter(t*DB);
		double tmax = H->phi_theta[0][s][m]->GetXaxis()->GetBinCenter((t+1)*DB);
		
		lab.DrawLatex(0.30, 0.88,  Form("%3.1f #leq #theta #leq %3.1f deg", tmin, tmax ) );
	}
	
	CphisS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	lab.DrawLatex(0.04, 0.95,  Form("Fiducial Cut - Sector %d - Momentum: %3.1f#pm%3.2f GeV", sector, H->mom[m], H->dp/2));

	lab.SetTextFont(42);
	lab.DrawLatex(0.1, 0.02, "                        #leftarrow          #phi  [degrees]           #rightarrow ");


    string mom_str[10] = {"0.4", "0.9", "1.4", "1.9", "2.4", "2.8", "3.3", "3.8", "4.3", "4.8"};

    if (PRINT != "none") {
        CphisS->Print(Form("img/PnPvsTmom-%s_sector-%d_plot-phi%s", mom_str[m].c_str(), s + 1, PRINT.c_str()));
    }
}
