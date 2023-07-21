#include "fiducial.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"

void FiducialCut::show_phi_theta(int sector, int mom)
{
	int s = sector - 1;`
	int m = mom - 1;
    int PLANE;

	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++) {
		H->phi_theta[c][s][m]->GetXaxis()->SetTitleSize(0.052);
		H->phi_theta[c][s][m]->GetXaxis()->SetTitleOffset(1.14);
		H->phi_theta[c][s][m]->GetYaxis()->SetTitleSize(0.054);
		H->phi_theta[c][s][m]->GetYaxis()->SetTitleOffset(1.32);
		H->phi_theta[c][s][m]->GetXaxis()->SetLabelSize(0.042);
		H->phi_theta[c][s][m]->GetYaxis()->SetLabelSize(0.042);
		H->phi_theta[c][s][m]->GetZaxis()->SetNdivisions(8);
	}
	for(int c=0; c<2; c++) {
		H->x_y[3][s][c][m]->GetXaxis()->SetTitleSize(0.052);
		H->x_y[3][s][c][m]->GetXaxis()->SetTitleOffset(1.14);
		H->x_y[3][s][c][m]->GetYaxis()->SetTitleSize(0.054);
		H->x_y[3][s][c][m]->GetYaxis()->SetTitleOffset(1.32);
		H->x_y[3][s][c][m]->GetXaxis()->SetLabelSize(0.042);
		H->x_y[3][s][c][m]->GetYaxis()->SetLabelSize(0.042);
		H->x_y[3][s][c][m]->GetZaxis()->SetNdivisions(8);
		H->x_y[3][s][c][m]->GetZaxis()->SetLabelSize(0.042);
	}


	TCanvas *Cphi_thetaS;
	TPad    *Pphi_thetaS;
	
	Cphi_thetaS = new TCanvas(Form("Cphi_thetaS%d", s+1), Form("Cphi_thetaS%d", s+1), csize, csize);
	Pphi_thetaS = new TPad(Form("Pphi_thetaS%d", s+1), Form("Pphi_thetaS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Pphi_thetaS->Divide(2, 2);
	Pphi_thetaS->Draw();

	TGraph *g_phi_theta1 = fidcut(sector, H->mom2[m],  1 );
	TGraph *g_phi_theta2 = fidcut(sector, H->mom2[m], -1 );
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++) {
		Pphi_thetaS->cd(c+1);

		if(c==0) H->phi_theta[0][s][m]->Draw("colz");
		else if(c==1) H->phi_theta[3][s][m]->Draw("colz");
        else if(c==2) H->x_y[3][s][0][m]->Draw("colz");
        else if(c==3) H->x_y[3][s][1][m]->Draw("colz");

		Cphi_thetaS->Update();
		g_phi_theta1->Draw("L");
		g_phi_theta2->Draw("L");
		if(c==0) palette = (TPaletteAxis*)H->phi_theta[c][s][m]->FindObject("palette");
		if(c==1) palette = (TPaletteAxis*)H->phi_theta[3][s][m]->FindObject("palette");
		if(c==2) palette = (TPaletteAxis*)H->x_y[3][s][0][m]->FindObject("palette");
		if(c==3) palette = (TPaletteAxis*)H->x_y[3][s][1][m]->FindObject("palette");
		palette->SetLabelSize(0.035);
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.88);
		palette->SetX2NDC(0.92);
		palette->SetY2NDC(0.96);
		
		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.050);
		if(c==0) {
			lab.DrawLatex(0.16, 0.91,  "a. no cuts applied");
		} else if(c==1) {
			lab.DrawLatex(0.16, 0.91,  "b. after fiducial cuts");
			lab.DrawLatex(0.16, 0.18,  Form("entries b. / a. : %3.1f%%", 100.0*H->phi_theta[c][s][m]->GetEntries()/H->phi_theta[0][s][m]->GetEntries()));
		} else if(c==2) {
			lab.SetTextColor(kRed+2);
			PLANE = 1;
			draw_limits(sector, PLANE);
			lab.DrawLatex(0.16, 0.18,  "c. DC1 plane, after fiducial cuts");
		} else if(c==3) {
			lab.SetTextColor(kRed+2);
			PLANE = 2;
			draw_limits(sector, PLANE);
			lab.DrawLatex(0.16, 0.18,  "d. DC2 plane, after fiducial cuts");
		}
	}
	
	Cphi_thetaS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	lab.DrawLatex(0.04, 0.95,  Form("Fiducial Cut - Sector %d - Momentum: %3.1f#pm%3.2f GeV", sector, H->mom[m], H->dp/2));

    string mom_str[10] = {"0.4", "0.9", "1.4", "1.9", "2.4", "2.8", "3.3", "3.8", "4.3", "4.8"};

    if(PRINT != "none") {
        Cphi_thetaS->Print( Form("img/PnPvsTmom-%s_sector-%d_plot-phiVsTheta%s",  mom_str[m].c_str(), s+1, PRINT.c_str()) );
	}
}


void FiducialCut::show_phi_thetas(int sector, int which)
{
	int s  = sector - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.2);

	TLatex lab;
	lab.SetNDC();
	
	TCanvas *Cphi_thetaS = new TCanvas(Form("Cphi_thetaS%d", s+1), Form("Cphi_thetaS%d", s+1), csize, csize);
	TPad    *Pphi_thetaS = new TPad(Form("Pphi_thetaS%d", s+1), Form("Pphi_thetaS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Pphi_thetaS->Divide(2, 5);
	Pphi_thetaS->Draw();
	
	
	lab.SetTextSize(0.08);
	lab.SetTextColor(kBlue+3);


	TPaletteAxis *palette;
	for(int m=0; m<chistos::NDIV_P; m++) {
		Pphi_thetaS->cd(m+1);
		gPad->SetLogz();
		H->phi_theta[which][s][m]->SetMinimum(1);
		H->phi_theta[which][s][m]->GetXaxis()->SetTitleSize(0.1);
		H->phi_theta[which][s][m]->GetYaxis()->SetTitleSize(0.1);
		H->phi_theta[which][s][m]->GetXaxis()->SetTitleOffset(0.9);
		H->phi_theta[which][s][m]->GetYaxis()->SetTitleOffset(0.5);
		H->phi_theta[which][s][m]->GetXaxis()->SetLabelSize(0.07);
		H->phi_theta[which][s][m]->GetYaxis()->SetLabelSize(0.07);
		H->phi_theta[which][s][m]->GetZaxis()->SetNdivisions(10);
		H->phi_theta[which][s][m]->GetYaxis()->SetNdivisions(5);
		H->phi_theta[which][s][m]->GetXaxis()->SetTitle("#theta        [deg]");
		H->phi_theta[which][s][m]->GetYaxis()->SetTitle("#phi        [deg]");

		H->phi_theta[which][s][m]->Draw("colz");
		Cphi_thetaS->Update();
		palette = (TPaletteAxis*)H->phi_theta[which][s][m]->FindObject("palette");

		if(palette) {
			palette->SetLabelSize(0.08);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
		}

		lab.DrawLatex(0.28, 0.94,  Form("momentum: %3.2f #leq p #leq %3.2f GeV", H->mom[m]-H->dp/2, H->mom[m]+H->dp/2 ) );
	}
	
	Cphi_thetaS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	if(which == 0) lab.DrawLatex(0.04, 0.95,  Form("#phi versus #theta in Sector %d  -  No Cuts Applied",     sector));
	if(which == 3) lab.DrawLatex(0.04, 0.95,  Form("#phi versus #theta in Sector %d  -  Planes Cuts Applied", sector));

	if(PRINT != "none") {
        if (which == 0) { Cphi_thetaS->Print(Form("img/phiTheta-before_sector-%d%s", s + 1, PRINT.c_str())); }
        else            { Cphi_thetaS->Print(Form("img/phiTheta-after_sector-%d%s",  s + 1, PRINT.c_str())); }
	}
}
