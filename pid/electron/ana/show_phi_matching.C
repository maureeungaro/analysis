void show_phi_match()
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	int hist_minimum = 5;
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();
	for(int s=0; s<7; s++)
	{
		H.phi_match[1][s]->SetFillColor(colors[1]);
		H.phi_match[3][s]->SetFillColor(kGreen);
		H.phi_match[1][s]->SetFillStyle(3004);
		H.phi_match[3][s]->SetFillStyle(3001);
		
		for(int c=0; c<4; c++)
		{
			H.phi_match[c][s]->GetXaxis()->SetTitleSize(0.054);
			H.phi_match[c][s]->GetXaxis()->SetTitleOffset(1.1);
			H.phi_match[c][s]->GetXaxis()->SetLabelSize(0.044);
			H.phi_match[c][s]->GetYaxis()->SetLabelSize(0.044);
			if(s == 6)
			{
				H.phi_match[c][s]->GetXaxis()->SetTitleOffset(1.1);
			}
		}
	}

	TCanvas *Cphi_match  = new TCanvas("Cphi_match", "Cphi_match", 1200, 800);
	TPad    *Pphi_match  = new TPad("Pphi_match", "Pphi_match", 0.02, 0.00,  0.98, 0.92);
   Pphi_match->Divide(3, 2);
	Pphi_match->Draw();

	for(int s=0; s<6; s++)
	{
		Pphi_match->cd(s+1);
		H.phi_match[0][s]->SetMinimum(hist_minimum);
		H.phi_match[0][s]->Draw();
		H.phi_match[1][s]->Draw("same");
//		H.phi_match[2][s]->Draw("same");
		H.phi_match[3][s]->Draw("same");
		gPad->SetLogy();
		lab.SetTextColor(colors[0]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.048);
		lab.DrawLatex(0.340, 0.44,  Form("cc / no cc:  %3.1f%%",               100.0*hit_cc[s] / no_cc_or_ec[s]));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.300, 0.38,  Form("calorimeter / cc:  %3.1f%%",         100.0*H.phi_match[1][s]->GetEntries()    / H.phi_match[0][s]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.250, 0.32,  Form("#phi match / calorimeter : %3.1f%%", 100.0*H.phi_match[3][s]->GetEntries()    / H.phi_match[1][s]->GetEntries()));
		lab.DrawLatex(0.330, 0.26,  Form("all cuts / cc: %3.1f%%",             100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
	}
	
	Cphi_match->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "#phi matching cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.40, 0.96,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.40, 0.93,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
//	lab.DrawLatex(0.70, 0.97,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.60, 0.93,  "#rightarrow all cuts applied");
	
	lab.SetTextColor(colors[0]);
	lab.SetTextSize(0.02);
	lab.DrawLatex(0.818, 0.98,  "0: both pmts fired");
	lab.DrawLatex(0.800, 0.955,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.800, 0.93,  "-2, 2: track/pmt opposite side");



	
   // All sectors
	TCanvas *CAphi_match  = new TCanvas("CAphi_match", "CAphi_match", 800, 600);
	TPad    *PAphi_match  = new TPad("PAphi_match", "PAphi_match", 0.02, 0.02,  0.98, 0.88);
	PAphi_match->Draw();
	PAphi_match->cd();
	gPad->SetLogy();
	H.phi_match[0][6]->SetMinimum(hist_minimum);
	H.phi_match[0][6]->Draw();
	H.phi_match[1][6]->Draw("same");
//	H.phi_match[2][6]->Draw("same");
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
	lab.DrawLatex(0.220, 0.40,  Form("cc / no cc:  %3.1f%%",               100.0*hit_cc[6] / no_cc_or_ec[6] ));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.220, 0.35,  Form("calorimeter / cc:  %3.1f%%",         100.0*H.phi_match[1][6]->GetEntries() / H.phi_match[0][6]->GetEntries()));
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.220, 0.30,  Form("#phi match / calorimeter: %3.1f%%",  100.0*H.phi_match[3][6]->GetEntries() / H.phi_match[1][6]->GetEntries()));
	lab.DrawLatex(0.220, 0.25,  Form("all cuts / ec:  %3.1f%%",            100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.52, 0.40,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.52, 0.35,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
//	lab.DrawLatex(0.52, 0.30,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.52, 0.25,  "#rightarrow all cuts applied");
	
	CAphi_match->cd(0);
	lab.SetTextSize(0.03);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.730, 0.97,  "0: both pmts fired");
	lab.DrawLatex(0.700, 0.93,  "-1, 1: track/pmt same side");
	lab.DrawLatex(0.700, 0.89,  "-2, 2: track/pmt opposite side");


	
	if(PRINT != "") 
	{
		Cphi_match->Print(  Form("phi_match_each_sector.%s", PRINT.c_str()) );
		CAphi_match->Print( Form("phi_match_all_sectors.%s", PRINT.c_str()) );
	}
	
}






