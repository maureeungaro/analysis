void show_phi_match()
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);

	int hist_minimum = 5;
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	int s = SECTOR-1;

	H.phi_match[1][s]->SetFillColor(colors[1]);
	H.phi_match[3][s]->SetFillColor(kGreen);
	H.phi_match[1][s]->SetFillStyle(3004);
	H.phi_match[3][s]->SetFillStyle(3001);

	for(int c=0; c<4; c++)
	{
		H.phi_match[c][s]->GetXaxis()->SetTitleSize(0.04);
		H.phi_match[c][s]->GetXaxis()->SetTitleOffset(1.1);
		H.phi_match[c][s]->GetXaxis()->SetLabelSize(0.034);
		H.phi_match[c][s]->GetYaxis()->SetLabelSize(0.034);
	}


	TCanvas *Cphi_match  = new TCanvas("Cphi_match", "Cphi_match", 1000, 1000);
	TPad    *Pphi_match  = new TPad("Pphi_match", "Pphi_match", 0.02, 0.00,  0.98, 0.92);
 	Pphi_match->Draw();

	H.phi_match[0][s]->SetMinimum(hist_minimum);
	H.phi_match[0][s]->Draw();
	H.phi_match[1][s]->Draw("same");
	H.phi_match[2][s]->Draw("same");
	H.phi_match[3][s]->Draw("same");
	gPad->SetLogy();
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.DrawLatex(0.350, 0.44,  Form("cc match / no cut:  %3.1f%%",        100.0*H.phi_match[3][s]->GetEntries()    / H.phi_match[0][s]->GetEntries()   ));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.320, 0.38,  Form("calorimeter / no cut:  %3.1f%%",     100.0*H.phi_match[1][s]->GetEntries()    / H.phi_match[0][s]->GetEntries()   ));
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.245, 0.32,  Form("neg calorimeter / no cut : %3.1f%%", 100.0*H.phi_match[2][s]->GetEntries()    / H.phi_match[0][s]->GetEntries()   ));
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.28, 0.26,   Form("cc match  / calorimeter: %3.1f%%",   100.0*H.phi_match[3][s]->GetEntries()    / H.phi_match[1][s]->GetEntries()  ));


	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "#phi matching cut:");
	lab.DrawLatex(0.06, 0.90,  "|match|<2 || #phi > 4");

	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.45, 0.96,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.45, 0.93,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.45, 0.90,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.45, 0.87,  "#rightarrow all cuts applied");
	
	lab.SetTextColor(colors[0]);
	lab.SetTextSize(0.016);
	lab.DrawLatex(0.78, 0.95,  "0: both pmts fired");
	lab.DrawLatex(0.78, 0.92,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.78, 0.89,  "-2, 2: track/pmt opposite side");

	if(PRINT != "")
	{
		Cphi_match->Print(  Form("img/cut-ccphi_sector-%d.%s", SECTOR, PRINT.c_str()) );
	}

}

void show_phi_matchAll()
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

	H.phi_match[1][6]->SetFillColor(colors[1]);
	H.phi_match[3][6]->SetFillColor(kGreen);
	H.phi_match[1][6]->SetFillStyle(3004);
	H.phi_match[3][6]->SetFillStyle(3001);

   // All sectors
	TCanvas *CAphi_match  = new TCanvas("CAphi_match", "CAphi_match", 1000, 1000);
	TPad    *PAphi_match  = new TPad("PAphi_match", "PAphi_match", 0.02, 0.02,  0.98, 0.88);
	PAphi_match->Draw();
	PAphi_match->cd();
	gPad->SetLogy();
	H.phi_match[0][6]->SetMinimum(hist_minimum);
	H.phi_match[0][6]->Draw();
	H.phi_match[1][6]->Draw("same");
	H.phi_match[2][6]->Draw("same");
	H.phi_match[3][6]->Draw("same");
	
	CAphi_match->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.34, 0.93,  "#phi Matching cut");
	
	PAphi_match->cd();
	lab.SetTextFont(42);
	lab.SetTextSize(0.038);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.350, 0.44,  Form("cc match / no cut:  %3.1f%%",        100.0*H.phi_match[3][6]->GetEntries()    / H.phi_match[0][6]->GetEntries()   ));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.320, 0.38,  Form("calorimeter / no cut:  %3.1f%%",     100.0*H.phi_match[1][6]->GetEntries()    / H.phi_match[0][6]->GetEntries()   ));
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.25, 0.32,  Form("neg calorimeter / no cut : %3.1f%%", 100.0*H.phi_match[2][6]->GetEntries()    / H.phi_match[0][6]->GetEntries()   ));
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.28, 0.26,   Form("cc match  / calorimeter: %3.1f%%",   100.0*H.phi_match[3][6]->GetEntries()    / H.phi_match[1][6]->GetEntries()  ));

	lab.SetTextFont(102);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "|match|<2 || #phi > 4");

	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.45, 0.98,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.45, 0.95,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.45, 0.92,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.45, 0.89,  "#rightarrow all cuts applied");

	lab.SetTextColor(colors[0]);
	lab.SetTextSize(0.02);
	lab.DrawLatex(0.78, 0.95,  "0: both pmts fired");
	lab.DrawLatex(0.78, 0.92,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.78, 0.89,  "-2, 2: track/pmt opposite side");


	
	if(PRINT != "") 
	{
		CAphi_match->Print( Form("img/cut-ccphi_sector-all.%s", PRINT.c_str()) );
	}
	
}






