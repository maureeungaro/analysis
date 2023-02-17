#include "fiducial.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"
#include "TVirtualX.h"

void FiducialCut::show_plane(int sector, int mom, int plane)
{
	int s  = sector - 1;
	int m  = mom - 1;
	int pl = plane - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++) {
		H->x_y[c][s][pl][m]->GetXaxis()->SetTitleSize(0.052);
		H->x_y[c][s][pl][m]->GetXaxis()->SetTitleOffset(1.14);
		H->x_y[c][s][pl][m]->GetYaxis()->SetTitleSize(0.054);
		H->x_y[c][s][pl][m]->GetYaxis()->SetTitleOffset(1.32);
		H->x_y[c][s][pl][m]->GetXaxis()->SetLabelSize(0.042);
		H->x_y[c][s][pl][m]->GetYaxis()->SetLabelSize(0.042);
		H->x_y[c][s][pl][m]->GetZaxis()->SetNdivisions(8);
		if(s == 6) {
			H->x_y[c][s][pl][m]->GetXaxis()->SetTitleOffset(1.1);
		}
	}
	
	
	TCanvas *Cx_yS = new TCanvas(Form("Cx_yS%d", s+1), Form("Cx_yS%d", s+1), 940, 900);
	TPad    *Px_yS = new TPad(Form("Px_yS%d", s+1), Form("Px_yS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Px_yS->Divide(2, 2);
	Px_yS->Draw();
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++) {
		Px_yS->cd(c+1);
		H->x_y[c][s][pl][m]->Draw("colz");
        draw_limits(sector, plane);
        Cx_yS->Update();
		palette = (TPaletteAxis*)H->x_y[c][s][pl][m]->FindObject("palette");
		if(palette) {
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		left_para[s][pl]->Draw("same");
		rite_para[s][pl]->Draw("same");

		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.050);
		if(c==0) {
			lab.DrawLatex(0.16, 0.91,  "a. no cuts applied");
		} else if(c==1) {
			lab.DrawLatex(0.16, 0.91,  "b. #phi vs #theta cuts applied");
			lab.DrawLatex(0.59, 0.18,  Form("b. / a. : %3.1f%%",  100.0*H->x_y[c][s][pl][m]->GetEntries()/H->x_y[0][s][pl][m]->GetEntries()));
		} else if(c==2) {
			lab.DrawLatex(0.16, 0.91,  "c. #phi vs #theta negative cuts applied");
			lab.DrawLatex(0.59, 0.18,  Form("c. / a. : %3.1f%%",  100.0*H->x_y[c][s][pl][m]->GetEntries()/H->x_y[0][s][pl][m]->GetEntries()));
		} else if(c==3) {
			lab.DrawLatex(0.16, 0.91,  "d. plane cuts applied");
			lab.DrawLatex(0.59, 0.22,  Form("d. / a. : %3.1f%%",  100.0*H->x_y[c][s][pl][m]->GetEntries()/H->x_y[0][s][pl][m]->GetEntries()));
			lab.DrawLatex(0.575, 0.17,  Form("d. / b. : %3.1f%%", 100.0*H->x_y[c][s][pl][m]->GetEntries()/H->x_y[1][s][pl][m]->GetEntries()));
		}
	}
	
	string planes[5]  = {"DC1 Plane", "DC2 Plane", "DC3 Plane", "EC Plane", "SC Plane"};
	string planes2[5] = {"DC1_Plane", "DC2_Plane", "DC3_Plane", "EC_Plane", "SC_Plane"};
	Cx_yS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	lab.DrawLatex(0.04, 0.95,  Form("Fiducial Cut - Sector %d - %s -  p:%3.1f#pm%3.2f GeV", sector, planes[pl].c_str(), H->mom[m], H->dp/2));

	if(PRINT != "none") {
		Cx_yS->Print( Form("img/X_vs_Y_cuts_m%d_sector%d_plane%s%s", m+1, s+1, planes2[pl].c_str(), PRINT.c_str()) );
	}
}

void FiducialCut::show_planes(int sector, int plane)
{
	int s  = sector - 1;
	int pl = plane - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.18);

	TLatex lab;
	lab.SetNDC();
	
	TCanvas *Cx_ysS = new TCanvas(Form("Cx_ysS%d", s+1), Form("Cx_ysS%d", s+1), 940, 1100);
	TPad    *Px_yS = new TPad(Form("Px_yS%d", s+1), Form("Px_yS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Px_yS->Divide(2, 5);
	Px_yS->Draw();

	lab.SetTextSize(0.08);
	lab.SetTextColor(kBlue+3);
	TPaletteAxis *palette;
	for(int m=0; m<chistos::NDIV_P; m++) {
		Px_yS->cd(m+1);
		if(LOGZ) Px_yS->SetLogz();
		H->x_y[0][s][pl][m]->SetMinimum(1);
		H->x_y[0][s][pl][m]->Draw("colz");
		Cx_ysS->Update();
		palette = (TPaletteAxis*)H->x_y[0][s][pl][m]->FindObject("palette");
		if(palette) {
			palette->SetLabelSize(0.08);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		lab.DrawLatex(0.28, 0.94,  Form("momentum: %3.2f #leq p #leq %3.2f GeV", H->mom[m]-H->dp/2, H->mom[m]+H->dp/2 ) );

		if(plane != 4) {
			left_para[s][pl]->Draw("same");
			rite_para[s][pl]->Draw("same");
		}
        draw_limits(sector, plane);
	}
	
	string planes[5]  = {"DC1 Plane", "DC2 Plane", "DC3 Plane", "EC Plane", "SC Plane"};
	string planes2[5] = {"DC1_Plane", "DC2_Plane", "DC3_Plane", "EC_Plane", "SC_Plane"};
	Cx_ysS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	lab.DrawLatex(0.1, 0.95,  Form("X vs Y Sector %d, Coordinates in %s ", sector, planes[pl].c_str()));

	if(PRINT != "none") {
		Cx_ysS->Print( Form("img/X_vs_Y_sect%d_plane%s%s", s+1, planes2[pl].c_str(), PRINT.c_str()) );
	}
}


void FiducialCut::show_integrated_plane(int sector, int plane)
{
    int s  = sector - 1;
    int pl = plane - 1;

	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);
	
	TLatex lab;
	lab.SetNDC();

    TCanvas *Cx_yIS = new TCanvas(Form("Cx_yIS%d", s+1), Form("Cx_yIS%d", s+1), 700, 700);
	TPad    *Px_yIS = new TPad(Form("Px_yIS%d", s+1), Form("Px_yIS%d", s+1), 0.02, 0.00,  0.98, 0.90);
	Px_yIS->Draw();

	if(LOGZ) gPad->SetLogz();
	TPaletteAxis *palette;
	H->x_y_tot[0][s][pl]->Draw("colz");
	Cx_yIS->Update();
	palette = (TPaletteAxis*)H->x_y_tot[0][s][pl]->FindObject("palette");
	if(palette) {
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.87);
		palette->SetX2NDC(0.91);
	}
	if(y_left[s][pl] && plane != 4) {
		y_left[s][pl]->Draw("P");
		y_right[s][pl]->Draw("P");
	}
	
	if(plane != 4) {
		left_para[s][pl]->Draw("same");
		rite_para[s][pl]->Draw("same");
	}

    draw_limits(sector, plane);

	string planes[5]  = {"DC1 Plane", "DC2 Plane", "DC3 Plane", "EC Plane", "SC Plane"};
	string planes2[5] = {"DC1_Plane", "DC2_Plane", "DC3_Plane", "EC_Plane", "SC_Plane"};
	Cx_yIS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.04);
	lab.DrawLatex(0.08, 0.94,  Form("X vs Y Sector %d, Coordinates in %s ", sector, planes[pl].c_str()));

	if(PRINT != "none") {
		Cx_yIS->Print( Form("img/X_vs_Y_integrated_sect%d_plane%s%s", s+1, planes2[pl].c_str(), PRINT.c_str()) );
	}


//	if(y_left[s][pl] && PLANE != 4) { Cx_yIS->AddExec("dynamic", "DynamicExec()"); }

	
}

void FiducialCut::DynamicExec(int sector, int plane)
{
	int s = sector - 1;
	int pl = plane - 1;

	TObject *select = gPad->GetSelected();
	if(!select) return;
	if (!select->InheritsFrom("TH2")) {gPad->SetUniqueID(0); return;}
	//TH2 *h = (TH2*)select;
	gPad->GetCanvas()->FeedbackMode(kTRUE);

   // erase old position and draw a line at current position
	int pyold = gPad->GetUniqueID();
	//int px    = gPad->GetEventX();
	int py    = gPad->GetEventY();

	float uxmin = gPad->GetUxmin();
	float uxmax = gPad->GetUxmax();

	int pxmin = gPad->XtoAbsPixel(uxmin);
	int pxmax = gPad->XtoAbsPixel(uxmax);
	if(pyold) gVirtualX->DrawLine(pxmin,  pyold, pxmax, pyold);
	gVirtualX->DrawLine(pxmin, py, pxmax, py);
	gPad->SetUniqueID(py);
	float upy = gPad->AbsPixeltoY(py);
	float y = gPad->PadtoY(upy);

	// draw slice corresponding to mouse position
	double dy = ( H->x_y_tot[0][s][pl]->GetYaxis()->GetXmax() - H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin() ) / NDIV_XY;
	int hid  = floor((y - H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin())/dy);

//	cout << " y: " << y << " dy: " << dy << "  hid: " << hid << endl;

	// need to match the slices
	if(hid > 1 && hid < 13) DrawFit(s, pl, hid);
}



void FiducialCut::DrawFit(int s, int pl, int hid)
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);

	TLatex lab;
	lab.SetNDC();
	double dy = ( H->x_y_tot[0][s][pl]->GetYaxis()->GetXmax() - H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin() ) / NDIV_XY;

   // create or set the new canvas c2
	TVirtualPad *padsav = gPad;
	TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
	if(c2) delete c2->GetPrimitive("Projection");
	else   c2 = new TCanvas("c2","Projection Canvas",710,10,700,500);
	c2->cd();
	
	string planes[5]  = {"DC1 Plane", "DC2 Plane", "DC3 Plane", "EC Plane", "SC Plane"};
	string planes2[5] = {"DC1_Plane", "DC2_Plane", "DC3_Plane", "EC_Plane", "SC_Plane"};

   double factor;
	if(pl == 0) factor = 2.0;
	if(pl == 1) factor = 5;
	if(pl == 2) factor = 8;
	if(pl == 4) factor = 10;
	
	double min_range = y_slice[s][pl][hid]->GetXaxis()->GetXmin() + factor*(18-hid);
	double max_range = y_slice[s][pl][hid]->GetXaxis()->GetXmax() - factor*(18-hid);
	y_slice[s][pl][hid]->GetXaxis()->SetRangeUser(min_range, max_range);
	
	if(y_slice[s][pl][hid])
	{
		
		y_slice[s][pl][hid]->Draw();

		y_slice[s][pl][hid]->GetXaxis()->SetTitleOffset(1.3);
		double pmin = H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin() + hid*dy;
		double pmax = H->x_y_tot[0][s][pl]->GetYaxis()->GetXmin() + (hid+1)*dy;

		lab.SetTextFont(102);
		lab.SetTextSize(0.058);
		lab.DrawLatex(0.22, 0.92,  Form("Y coordinates on %s", planes[pl].c_str()));
		lab.SetTextFont(42);
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.66, 0.82,  Form("Sector %d", s+1));
		lab.DrawLatex(0.60, 0.76,  Form("x = %3.1f - %3.1f cm", pmin, pmax ));
		lab.SetTextColor(kRed+2);
		lab.DrawLatex(0.59, 0.68,  Form("Y min = %3.1f #pm %3.2f", ymin[s][pl][hid], ymine[s][pl][hid]));
		lab.DrawLatex(0.59, 0.62,  Form("Y max = %3.1f #pm %3.2f", ymax[s][pl][hid], ymaxe[s][pl][hid]));

		TLine x_min_l(ymin[s][pl][hid], 0, ymin[s][pl][hid], y_slice[s][pl][hid]->GetMaximum()/2);
		TLine x_max_l(ymax[s][pl][hid], 0, ymax[s][pl][hid], y_slice[s][pl][hid]->GetMaximum()/2);

		x_min_l.SetLineColor(kRed+3);
		x_max_l.SetLineColor(kRed+3);
		x_min_l.SetLineWidth(2);
		x_max_l.SetLineWidth(2);
		x_min_l.SetLineStyle(9);
		x_max_l.SetLineStyle(9);
		
		x_min_l.Draw();
		x_max_l.Draw();

	}

	c2->Update();
	padsav->cd();

	if(PRINT != "none") {
		c2->Print(Form("slice%d_%s_sect%d%s", hid+1, planes2[pl].c_str(), s+1, PRINT.c_str()) );
	}

}













