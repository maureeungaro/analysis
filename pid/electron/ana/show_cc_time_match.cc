#include "cc_match.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"
#include "TVirtualX.h"

void CC_Match::show_cc_timing(int sector)
{
	int s = sector - 1;

    gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++) {
		H->cc_timing[c][s]->GetXaxis()->SetTitleSize(0.052);
		H->cc_timing[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H->cc_timing[c][s]->GetYaxis()->SetTitleSize(0.054);
		H->cc_timing[c][s]->GetYaxis()->SetTitleOffset(1.1);
		H->cc_timing[c][s]->GetXaxis()->SetLabelSize(0.042);
		H->cc_timing[c][s]->GetYaxis()->SetLabelSize(0.042);
		H->cc_timing[c][s]->GetZaxis()->SetNdivisions(8);
		if(s == 6) {
			H->cc_timing[c][s]->GetXaxis()->SetTitleOffset(1.1);
		}
	}
	
	TCanvas *Ccc_timingS;
	TPad    *Pcc_timingS;
	
	Ccc_timingS = new TCanvas(Form("Ccc_timingS%d", s+1), Form("Ccc_timingS%d", s+1), csize, csize);
	Pcc_timingS = new TPad(Form("Pcc_timingS%d", s+1), Form("Pcc_timingS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Pcc_timingS->Divide(2, 2);
	Pcc_timingS->Draw();


	TPaletteAxis *palette;
	for(int c=0; c<4; c++) {

		Pcc_timingS->cd(c+1);
		gPad->SetLogz();

        H->cc_timing[c][s]->Draw("colz");
		Ccc_timingS->Update();

        if(cc_timing_low[s]) {
            cc_timing_low[s]->Draw("P");
        }

		if(H->cc_timing[c][s]->GetMaximum()>1) {
			palette = (TPaletteAxis*)H->cc_timing[c][s]->FindObject("palette");
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		
        lab.SetTextFont(40);
        lab.SetTextSize(0.050);
        if(c==0) {
            lab.DrawLatex(0.48, 0.91,  "a: no cuts applied");
        } else if(c==1) {
            lab.DrawLatex(0.31, 0.91,  "b: calorimeter cuts applied");
            lab.DrawLatex(0.37, 0.21,  Form("percentage of a : %3.1f%%", 100.0*H->cc_timing[c][s]->GetEntries()/H->cc_timing[0][s]->GetEntries()));
        } else if(c==2) {
            lab.DrawLatex(0.18, 0.91,  "c: calorimeter negative cuts applied");
            lab.DrawLatex(0.33, 0.85,  Form("percentage of a : %3.1f%%", 100.0*H->cc_timing[c][s]->GetEntries()/H->cc_timing[0][s]->GetEntries()));
        } else if(c==3) {
            lab.DrawLatex(0.35, 0.91,  "d: all e pid cuts applied");
            lab.DrawLatex(0.25, 0.26,  Form("percentage of a: %3.1f%%", 100.0*H->cc_timing[c][s]->GetEntries()/H->cc_timing[0][s]->GetEntries()));
            lab.DrawLatex(0.25, 0.20,  Form("percentage of b: %3.1f%%", 100.0*H->cc_timing[c][s]->GetEntries()/H->cc_timing[1][s]->GetEntries()));
        }

    }
	
	Ccc_timingS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.08, 0.95,  Form("CC Timing") );
	lab.SetTextSize(0.030);
	lab.DrawLatex(0.55, 0.95,  Form("#Delta T = T_{CC} + |#vec{R}_{SC}-#vec{R}_{CC}|/c - T_{SC}"));

	if(PRINT != "none") {
		Ccc_timingS->Print( Form("img/cut-03-timc_sector-%d%s", s+1, PRINT.c_str()) );
    }
}



void CC_Match::show_cc_timings(int sector) {

    gStyle->SetPadLeftMargin(0.14);
    gStyle->SetPadRightMargin(0.16);
    gStyle->SetPadTopMargin(0.12);
    gStyle->SetPadBottomMargin(0.14);

    TLatex lab;
    lab.SetNDC();

    int s = sector - 1;
    //int NBINS = H->cc_timing[1][0]->GetNbinsX();
    //int db = NBINS / NDIV;

    TCanvas *Ccc_timing = new TCanvas("Ccc_timing", "Ccc_timing", csize, csize);
    gPad->SetLogz();

    // Changing titles
    H->cc_timing[1][s]->GetXaxis()->CenterTitle(0);
    H->cc_timing[1][s]->GetXaxis()->SetTitleSize(0.040);
    H->cc_timing[1][s]->GetYaxis()->SetTitleSize(0.040);
    H->cc_timing[1][s]->GetXaxis()->SetTitleOffset(1.2);
    H->cc_timing[1][s]->GetYaxis()->SetTitleOffset(1.5);
    H->cc_timing[1][s]->GetXaxis()->SetLabelSize(0.032);
    H->cc_timing[1][s]->GetYaxis()->SetLabelSize(0.032);
    H->cc_timing[1][s]->GetZaxis()->SetLabelSize(0.032);

    H->cc_timing[1][s]->Draw("colz");

    if (cc_timing_low[s])
        cc_timing_low[s]->Draw("P");

    Ccc_timing->Update();     // important, otherwise it won't find the palette
    TPaletteAxis *palette;
    if (H->cc_timing[1][s]->GetMaximum() > 1) {
        palette = (TPaletteAxis *) H->cc_timing[1][s]->FindObject("palette");
        palette->SetLabelSize(0.032);
        palette->SetLabelOffset(0.01);
        palette->SetX1NDC(0.85);
        palette->SetX2NDC(0.89);
        palette->SetY1NDC(0.14);
        palette->SetY2NDC(0.88);
    }

    lab.SetTextColor(colors[0]);
    lab.SetTextFont(102);
    lab.SetTextSize(0.048);
    lab.DrawLatex(0.10, 0.94, Form("CC Timing") );
    lab.SetTextSize(0.034);
    lab.DrawLatex(0.50, 0.95, Form("#Delta T = T_{CC} + |#vec{R}_{SC}-#vec{R}_{CC}|/c - T_{SC}"));

    lab.SetTextFont(42);
    lab.SetTextSize(0.028);
    lab.SetTextColor(kRed + 2);
    lab.DrawLatex(0.65, 0.91, Form("Lower Limit: #mu - %3.2f #sigma", Pars->CC_T_NSIGMAS));


    if (PRINT != "none") {
        Ccc_timing->Print(Form("img/cut-03-tim_sector-%d%s", s + 1, PRINT.c_str()));
    }

    if (cc_timing_low[s]) {
       // Ccc_timing->AddExec("dynamic", "CCT_DynamicExec()");
    }
}



void CC_Match::CCT_DynamicExec(int sector)
{
	
	int s = sector - 1;
	
	TObject *select = gPad->GetSelected();
	if(!select) return;
	if (!select->InheritsFrom("TH2")) {gPad->SetUniqueID(0); return;}
	//TH2 *h = (TH2*)select;
	gPad->GetCanvas()->FeedbackMode(kTRUE);

   // erase old position and draw a line at current position
	int pxold = gPad->GetUniqueID();
	int px = gPad->GetEventX();
	//int py = gPad->GetEventY();
	float uymin = gPad->GetUymin();
	float uymax = gPad->GetUymax();
	int pymin = gPad->YtoAbsPixel(uymin);
	int pymax = gPad->YtoAbsPixel(uymax);
	if(pxold) gVirtualX->DrawLine(pxold, pymin, pxold ,pymax);
	gVirtualX->DrawLine(px, pymin, px, pymax);
	gPad->SetUniqueID(px);
	float upx = gPad->AbsPixeltoX(px);
	float x = gPad->PadtoX(upx);
	
	// draw slice corresponding to mouse position

    CCT_DrawFit_TimeSlice(s, (int)(x-1));
}


void CC_Match::CCT_DrawFit_TimeSlice(int s, int hid)
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.14);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetNDC();

    // create or set the new canvas c2
	TVirtualPad *padsav = gPad;
	TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
	if(c2) delete c2->GetPrimitive("Projection");
	else   c2 = new TCanvas("c2","Projection Canvas",710,10, csize, csize);
	c2->cd();
	
	if(cc_timing1d[s][hid]) {
		cc_timing1d[s][hid]->GetXaxis()->SetTitleOffset(1.3);
		cc_timing1d[s][hid]->Draw();
		lab.SetTextFont(102);
		lab.SetTextSize(0.045);
		lab.DrawLatex(0.16, 0.93,  "#Delta T = T_{CC} + |#vec{R}_{SC}-#vec{R}_{CC}|/c - T_{SC}");
		lab.SetTextFont(42);
		lab.SetTextSize(0.04);
        lab.DrawLatex(0.62, 0.82,  Form("Sector %d", s+1));
        lab.DrawLatex(0.60, 0.76,  Form("Pmt: %d", hid+1));
        lab.SetTextColor(kRed+2);
        lab.DrawLatex(0.50, 0.68,  Form("#mu = %4.3f #pm %2.1e",    cc_timing1d[s][hid]->GetFunction("gaus")->GetParameter(1), cc_timing1d[s][hid]->GetFunction("gaus")->GetParError(1)));
        lab.DrawLatex(0.50, 0.62,  Form("#sigma = %4.3f #pm %2.1e", cc_timing1d[s][hid]->GetFunction("gaus")->GetParameter(2), cc_timing1d[s][hid]->GetFunction("gaus")->GetParError(2)));
	}

	c2->Update();
	padsav->cd();
	
	if(PRINT != "none") {
		if(hid>=9) {
            c2->Print(Form("img_slices/slice-%d_cut-03-tim_sector-%d%s", hid + 1, s + 1, PRINT.c_str()));
        } else {
            c2->Print(Form("img_slices/slice-0%d_cut-03-tim_sector-%d%s", hid + 1, s + 1, PRINT.c_str()));
        }
	}

}


void CC_Match::show_cc_timing_all_sectors()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	TF1 *hor = new TF1("hor", "pol0", 0, 5);
	hor->SetLineColor(kBlack);
	hor->SetLineWidth(1);
	hor->SetLineStyle(1);
	hor->SetParameter(0, 0.3);
	
	for(int s=0; s<6; s++) {
		// Changing titles
		H->cc_timing[1][s]->GetXaxis()->CenterTitle(0);
		H->cc_timing[1][s]->GetXaxis()->SetTitleSize(0.05);
		H->cc_timing[1][s]->GetYaxis()->SetTitleSize(0.05);
		H->cc_timing[1][s]->GetXaxis()->SetTitleOffset(1.0);
		H->cc_timing[1][s]->GetYaxis()->SetTitleOffset(1.2);
		H->cc_timing[1][s]->GetXaxis()->SetLabelSize(0.04);
		H->cc_timing[1][s]->GetYaxis()->SetLabelSize(0.04);
		H->cc_timing[1][s]->GetZaxis()->SetLabelSize(0.04);
	}
	
	TCanvas *Ccc_timingA  = new TCanvas("Ccc_timingA", "Ccc_timingA", csize, csize);
	TPad    *Pcc_timingA  = new TPad("Pcc_timingA", "Pcc_timingA", 0.02, 0.00,  0.98, 0.92);
	Pcc_timingA->Divide(3, 2);
	Pcc_timingA->Draw();

	TPaletteAxis *palette;
	
	for(int s=0; s<6; s++) {
		Pcc_timingA->cd(s+1);
		gPad->SetGridx();
		gPad->SetGridy();
        gPad->SetLogz();

        H->cc_timing[1][s]->Draw("colz");
		Ccc_timingA->Update();

		if(H->cc_timing[1][s]->GetMaximum()>1) {
			palette = (TPaletteAxis*)H->cc_timing[1][s]->FindObject("palette");
			palette->SetLabelSize(0.032);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.89);
		}
		

		if(cc_timing_low[s]) {
            cc_timing_low[s]->Draw("P");
        }
	}
	
	Ccc_timingA->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.034);
	lab.DrawLatex(0.10, 0.94,  "CC Timing - All Sectors");
	lab.SetTextSize(0.026);
	lab.SetTextColor(kBlue+2);
	lab.DrawLatex(0.62, 0.94,  "Calorimeter Cuts Applied");
	
	
	if(PRINT != "none" ) {
		Ccc_timingA->Print(Form("img/cut-03-tim_sector-all%s", PRINT.c_str()));
	}
	
}













