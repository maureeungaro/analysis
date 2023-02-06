#include "vertex.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"

void Vertex_CS::show_vertex()
{
	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.08);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();


	TLine *zero_cut = new TLine(0, 0, 0, H->vz[0][0][0]->GetMaximum()/2);
	zero_cut->SetLineStyle(2);
	
	TLine *min_cut = new TLine(Pars->vz_limits[0], 0, Pars->vz_limits[0], H->vz[0][0][0]->GetMaximum());
	TLine *max_cut = new TLine(Pars->vz_limits[1], 0, Pars->vz_limits[1], H->vz[0][0][0]->GetMaximum());
	min_cut->SetLineStyle(7);
	max_cut->SetLineStyle(7);
	min_cut->SetLineColor(kRed+2);
	max_cut->SetLineColor(kRed+2);
	min_cut->SetLineWidth(2);
	max_cut->SetLineWidth(2);
	
	TCanvas *Cvtx  = new TCanvas("Cvtx", "Cvtx", 1100, 1100);
	TPad    *Pvtx  = new TPad("Pvtx", "Pvtx", 0.02, 0.00,  0.98, 0.92);
	Pvtx->Divide(2, 2);
	Pvtx->Draw();
	Pvtx->cd();

	H->vz[0][0][0]->SetLineColor(kBlue);
	H->vz[1][0][0]->SetLineColor(kRed);
	H->vz[2][0][0]->SetLineColor(kGreen);
	H->vz[3][0][0]->SetLineColor(kMagenta);
	H->vz[4][0][0]->SetLineColor(kCyan);
	H->vz[5][0][0]->SetLineColor(kYellow+1);
	
	H->vz[0][0][1]->SetLineColor(kBlue);
	H->vz[1][0][1]->SetLineColor(kRed);
	H->vz[2][0][1]->SetLineColor(kGreen);
	H->vz[3][0][1]->SetLineColor(kMagenta);
	H->vz[4][0][1]->SetLineColor(kCyan);
	H->vz[5][0][1]->SetLineColor(kYellow+1);
	
	H->vz[0][1][0]->SetLineColor(kBlue);
	H->vz[1][1][0]->SetLineColor(kRed);
	H->vz[2][1][0]->SetLineColor(kGreen);
	H->vz[3][1][0]->SetLineColor(kMagenta);
	H->vz[4][1][0]->SetLineColor(kCyan);
	H->vz[5][1][0]->SetLineColor(kYellow+1);
	
	H->vz[0][1][1]->SetLineColor(kBlue);
	H->vz[1][1][1]->SetLineColor(kRed);
	H->vz[2][1][1]->SetLineColor(kGreen);
	H->vz[3][1][1]->SetLineColor(kMagenta);
	H->vz[4][1][1]->SetLineColor(kCyan);
	H->vz[5][1][1]->SetLineColor(kYellow+1);
	
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlue+3);
	
	Pvtx->cd(1);
	H->vz[0][0][0]->SetMaximum(H->vz[0][0][0]->GetMaximum()*1.2);
	H->vz[0][0][0]->Draw();
	for(int s=0; s<6; s++) {
		H->vz[s][0][0]->Draw("same");
		zero_cut->Draw();
		min_cut->Draw();
		max_cut->Draw();
		lab.DrawLatex(0.49, 0.92,  "electron, not corrected");
	}

	Pvtx->cd(3);
	H->vz[0][1][0]->SetMaximum(H->vz[0][0][0]->GetMaximum());
	H->vz[0][1][0]->Draw();
	for(int s=0; s<6; s++) {
		H->vz[s][1][0]->Draw("same");
		zero_cut->Draw();
		min_cut->Draw();
		max_cut->Draw();
		lab.DrawLatex(0.55, 0.92,  "electron, corrected");
	}
	
	Pvtx->cd(2);
	H->vz[0][0][1]->SetMaximum(H->vz[0][0][0]->GetMaximum());
	H->vz[0][0][1]->Draw();
	for(int s=0; s<6; s++) {
		H->vz[s][0][1]->Draw("same");
		zero_cut->Draw();
		min_cut->Draw();
		max_cut->Draw();
		lab.DrawLatex(0.52, 0.92,  "proton, not corrected");
	}

	Pvtx->cd(4);
	H->vz[0][1][1]->SetMaximum(H->vz[0][0][0]->GetMaximum());
	H->vz[0][1][1]->Draw();
	for(int s=0; s<6; s++) {
		H->vz[s][1][1]->Draw("same");
		zero_cut->Draw();
		min_cut->Draw();
		max_cut->Draw();
		lab.DrawLatex(0.56, 0.92,  "proton, corrected");
	}
	
	
	Cvtx->cd();
	lab.SetTextFont(102);
	lab.SetTextSize(0.043);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.04, 0.94,  "Vertex Correction, Cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.60, 0.93,  Form("%3.1f #leq vz #leq %3.1f", Pars->vz_limits[0], Pars->vz_limits[1]));
	lab.DrawLatex(0.64, 0.96,  "VZ Cut:");
		
	
	lab.SetTextSize(0.018);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.80, 0.97, "Sector 1");
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.80, 0.95, "Sector 2");
	lab.SetTextColor(kGreen);
	lab.DrawLatex(0.80, 0.93, "Sector 3");
	lab.SetTextColor(kMagenta);
	lab.DrawLatex(0.88, 0.97, "Sector 4");
	lab.SetTextColor(kCyan);
	lab.DrawLatex(0.88, 0.95, "Sector 5");
	lab.SetTextColor(kYellow+1);
	lab.DrawLatex(0.88, 0.93, "Sector 6");
	
	if(PRINT != "none") {
		Cvtx->Print(Form("vtx_all_sector%s", PRINT.c_str()) );
	}
	
}






