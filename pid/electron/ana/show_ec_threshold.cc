#include "ec_match.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TLine.h"

void EC_Match::show_ecthr(int sector)
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	int s = sector - 1;

	for(int c=0; c<4; c++) {
		H->ecthr[c][s]->GetXaxis()->SetTitleSize(0.04);
		H->ecthr[c][s]->GetXaxis()->SetTitleOffset(1.1);
		H->ecthr[c][s]->GetXaxis()->SetLabelSize(0.034);
		H->ecthr[c][s]->GetYaxis()->SetLabelSize(0.034);
		H->ecthr[0][s]->GetYaxis()->SetRangeUser(1, H->ecthr[0][s]->GetMaximum()*1.5);
	}

	TLine *p_cut = new TLine(Pars->p_ec_threshold, 0, Pars->p_ec_threshold, H->ecthr[0][s]->GetMaximum());
	p_cut->SetLineStyle(2);
	
	
	TCanvas *Cecthr  = new TCanvas("Cecthr", "Cecthr", 1000, 1000);
	TPad    *Pecthr  = new TPad("Pecthr", "Pecthr", 0.02, 0.00,  0.98, 0.92);
	Pecthr->Draw();
	
	H->ecthr[0][s]->Draw();
	H->ecthr[1][s]->Draw("same");
	H->ecthr[2][s]->Draw("same");
	H->ecthr[3][s]->Draw("same");
	p_cut->Draw();
	gPad->SetLogy();
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.48, 0.85,  Form("all others / no cut:  %3.1f%%",                             100.0*H->ecthr[1][s]->GetEntries() / H->ecthr[0][s]->GetEntries() ));
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.45, 0.79,  Form("neg others / no cut:  %3.1f%%",                             100.0*H->ecthr[2][s]->GetEntries() / H->ecthr[0][s]->GetEntries() ));
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.45, 0.73,  Form("p  #geq %3.2f / all other :  %3.1f%%", Pars->p_ec_threshold, 100.0*H->ecthr[3][s]->GetEntries() / H->ecthr[1][s]->GetEntries() ));

	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "EC Threshold cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.40, 0.97,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.40, 0.93,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.65, 0.97,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.65, 0.93,  "#rightarrow all cuts applied");


    if(PRINT != "none") {
		Cecthr->Print(  Form("img/cut-04-ec-threshold_sector-%d%s", sector, PRINT.c_str()) );
    }
	
}




void EC_Match::show_ecthr_all_sectors()
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();
	
	for(int c=0; c<4; c++) {
		H->ecthr[c][6]->GetXaxis()->SetTitleSize(0.04);
		H->ecthr[c][6]->GetXaxis()->SetTitleOffset(1.1);
		H->ecthr[c][6]->GetXaxis()->SetLabelSize(0.034);
		H->ecthr[c][6]->GetYaxis()->SetLabelSize(0.034);
		H->ecthr[0][6]->GetYaxis()->SetRangeUser(1, H->ecthr[0][6]->GetMaximum()*1.5);
	}

	TLine *p_cut = new TLine(Pars->p_ec_threshold, 0, Pars->p_ec_threshold, H->ecthr[0][6]->GetMaximum());
	p_cut->SetLineStyle(2);

	TCanvas *Cecthr  = new TCanvas("Cecthr", "Cecthr", 1000, 1000);
	TPad    *Pecthr  = new TPad("Pecthr", "Pecthr", 0.02, 0.00,  0.98, 0.92);
	Pecthr->Draw();
	
	
	H->ecthr[0][6]->Draw();
	H->ecthr[1][6]->Draw("same");
	H->ecthr[2][6]->Draw("same");
	H->ecthr[3][6]->Draw("same");
	p_cut->Draw();
	gPad->SetLogy();
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.48, 0.85,  Form("all others / no cut:  %3.1f%%",                             100.0*H->ecthr[1][6]->GetEntries() / H->ecthr[0][6]->GetEntries() ));
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.45, 0.79,  Form("neg others / no cut:  %3.1f%%",                             100.0*H->ecthr[2][6]->GetEntries() / H->ecthr[0][6]->GetEntries() ));
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.45, 0.73,  Form("p  #geq %3.2f / all other :  %3.1f%%", Pars->p_ec_threshold, 100.0*H->ecthr[3][6]->GetEntries() / H->ecthr[1][6]->GetEntries() ));
	
	
	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "EC Threshold cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.40, 0.97,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.40, 0.93,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.65, 0.97,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.65, 0.93,  "#rightarrow all cuts applied");

    if(PRINT != "none") {
		Cecthr->Print(  Form("img/cut-04-ec-threshold_sector-all%s", PRINT.c_str()) );
	}
	
}






