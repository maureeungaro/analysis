#include "cc_match.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"

void CC_Match::show_phi_match(int sector)
{
    int s = sector - 1;
    int hist_minimum = 5;

    gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	H->phi_match[1][s]->SetFillColor(colors[1]);
	H->phi_match[3][s]->SetFillColor(kGreen);

    H->phi_match[1][s]->SetFillStyle(3004);
	H->phi_match[3][s]->SetFillStyle(3001);

	for(int c=0; c<4; c++) {
		H->phi_match[c][s]->GetXaxis()->SetTitleSize(0.04);
		H->phi_match[c][s]->GetXaxis()->SetTitleOffset(1.1);
		H->phi_match[c][s]->GetXaxis()->SetLabelSize(0.034);
		H->phi_match[c][s]->GetYaxis()->SetLabelSize(0.034);
	}

	TCanvas *Cphi_match  = new TCanvas("Cphi_match", "Cphi_match", 1000, 1000);
	TPad    *Pphi_match  = new TPad("Pphi_match", "Pphi_match", 0.02, 0.00,  0.98, 0.92);
 	Pphi_match->Draw();

	H->phi_match[0][s]->SetMinimum(hist_minimum);
	H->phi_match[0][s]->Draw();
	H->phi_match[1][s]->Draw("same");
	//H->phi_match[2][s]->Draw("same");
	H->phi_match[3][s]->Draw("same");
	gPad->SetLogy();
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.DrawLatex(0.350, 0.32,  Form("#phi match / no cut:  %3.1f%%",       100.0*H->phi_match[3][s]->GetEntries() / H->phi_match[0][s]->GetEntries()  ));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.320, 0.26,  Form("#phi match / calorimeter:  %3.1f%%",  100.0*H->phi_match[3][s]->GetEntries() / H->phi_match[1][s]->GetEntries()  ));
//	lab.SetTextColor(kRed);
//	lab.DrawLatex(0.245, 0.32,  Form("All cuts   / no cut : %3.1f%%",       100.0*H->phi_match[3][s]->GetEntries() / H->phi_match[0][s]->GetEntries()  ));
//	lab.SetTextColor(kBlack);
//	lab.DrawLatex(0.32, 0.26,   Form("All cuts  / calorimeter: %3.1f%%",    100.0*H->phi_match[3][s]->GetEntries() / H->phi_match[1][s]->GetEntries()  ));


	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.05, 0.94,  "#phi matching cut:");
	lab.DrawLatex(0.05, 0.88,  "|match|<2 || #phi > 4");

	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.42, 0.95,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.42, 0.92,  "#rightarrow calorimeters cuts applied");
//	lab.SetTextColor(colors[2]);
//	lab.DrawLatex(0.45, 0.90,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.42, 0.89,  "#rightarrow all cuts applied");

	lab.SetTextColor(colors[0]);
	lab.SetTextSize(0.022);
	lab.DrawLatex(0.72, 0.95,  "0: both pmts fired");
	lab.DrawLatex(0.72, 0.92,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.72, 0.89,  "-2, 2: track/pmt opposite side");

	if(PRINT != "none") {
        Cphi_match->Print( Form("img/cut-02-cc-phi-match_sector-%d%s", sector, PRINT.c_str()) );
    }

}

void CC_Match::show_phi_match_all_sectors()
{

    gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.15);
	gStyle->SetPadBottomMargin(0.12);

	int hist_minimum = 5;

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	H->phi_match[1][6]->SetFillColor(colors[1]);
	H->phi_match[3][6]->SetFillColor(kGreen);
	H->phi_match[1][6]->SetFillStyle(3004);
	H->phi_match[3][6]->SetFillStyle(3001);

   // All sectors
	TCanvas *CAphi_match  = new TCanvas("CAphi_match", "CAphi_match", 1000, 1000);
	TPad    *PAphi_match  = new TPad("PAphi_match", "PAphi_match", 0.02, 0.02,  0.98, 0.88);
	PAphi_match->Draw();
	PAphi_match->cd();
	gPad->SetLogy();
	H->phi_match[0][6]->SetMinimum(hist_minimum);
	H->phi_match[0][6]->Draw();
	H->phi_match[1][6]->Draw("same");
	//H->phi_match[2][6]->Draw("same");
	H->phi_match[3][6]->Draw("same");
	
	CAphi_match->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.052);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.34, 0.93,  "#phi Matching cut");
	
	PAphi_match->cd();
    lab.SetTextFont(42);
    lab.SetTextSize(0.042);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.350, 0.44,  Form("#phi match / no cut:  %3.1f%%",         100.0*H->phi_match[3][6]->GetEntries() / H->phi_match[0][6]->GetEntries()   ));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.320, 0.38,  Form("#phi match / calorimeter:  %3.1f%%",    100.0*H->phi_match[3][6]->GetEntries() / H->phi_match[1][6]->GetEntries()   ));
//	lab.SetTextColor(kRed);
//	lab.DrawLatex(0.25, 0.32,  Form("neg calorimeter / no cut : %3.1f%%", 100.0*H->phi_match[2][6]->GetEntries() / H->phi_match[0][6]->GetEntries()   ));
//	lab.SetTextColor(kBlack);
//	lab.DrawLatex(0.28, 0.26,   Form("cc match  / calorimeter: %3.1f%%",  100.0*H->phi_match[3][6]->GetEntries() / H->phi_match[1][6]->GetEntries()  ));

	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "|match|<2 || #phi > 4");

	lab.SetTextFont(42);
	lab.SetTextSize(0.03);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.45, 0.98,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.45, 0.94,  "#rightarrow calorimeter cuts applied");
//	lab.SetTextColor(colors[2]);
//	lab.DrawLatex(0.45, 0.92,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.45, 0.90,  "#rightarrow all cuts applied");

	lab.SetTextColor(colors[0]);
	lab.SetTextSize(0.024);
	lab.DrawLatex(0.78, 0.98,  "0: both pmts fired");
	lab.DrawLatex(0.78, 0.94,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.78, 0.90,  "-2, 2: track/pmt opposite side");


	
	if(PRINT != "none") {
        CAphi_match->Print( Form("img/cut-02-cc-phi-match_sector-all%s", PRINT.c_str()) );
    }
	
}






