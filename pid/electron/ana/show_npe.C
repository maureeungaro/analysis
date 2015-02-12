void show_npe()
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	
	for(int s=0; s<7; s++)
		for(int c=0; c<4; c++)
		{
			H.nphe[c][s]->GetXaxis()->SetTitleSize(0.054);
			H.nphe[c][s]->GetXaxis()->SetTitleOffset(1.14);
			H.nphe[c][s]->GetXaxis()->SetLabelSize(0.044);
			H.nphe[c][s]->GetYaxis()->SetLabelSize(0.044);
			if(s == 6)
			{
				H.nphe[c][s]->GetXaxis()->SetTitleOffset(1.1);
			}
		}

	TLine *npe_cut[6];	
	for(int s=0; s<6; s++)
	{
		npe_cut[s] = new TLine(Pars.min_nphe[s], 0, Pars.min_nphe[s], H.nphe[1][s]->GetMaximum());
		npe_cut[s]->SetLineStyle(2);
	}
	
	TCanvas *Cnpe  = new TCanvas("Cnpe", "Cnpe", 1200, 800);
	TPad    *Pnpe  = new TPad("Pnpe", "Pnpe", 0.02, 0.00,  0.98, 0.92);
   Pnpe->Divide(3, 2);
	Pnpe->Draw();

	
	for(int s=0; s<6; s++)
	{
		Pnpe->cd(s+1);
		H.nphe[0][s]->SetMinimum(10000);
		H.nphe[0][s]->Draw();
		H.nphe[1][s]->Draw("same");
		H.nphe[2][s]->Draw("same");
		H.nphe[3][s]->Draw("same");
		H.enphe[s]->Draw("same");
		npe_cut[s]->Draw();
		gPad->SetLogy();
		lab.SetTextColor(colors[0]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.048);
		lab.DrawLatex(0.610, 0.91,  Form("cc / no cc:  %3.1f%%",                              100.0*hit_cc[s] / no_cc_or_ec[s]));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.504, 0.85,  Form("calorimeter / cc:  %3.1f%%",                        100.0*H.nphe[1][s]->GetEntries() / H.nphe[0][s]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.415, 0.79,  Form("all cuts / calorimeter:  %3.1f%%",                  100.0*H.nphe[3][s]->GetEntries() / H.nphe[1][s]->GetEntries()));
		lab.SetTextColor(colors[0]);
		lab.DrawLatex(0.525, 0.73,  Form("nphe #geq %2.0f / cc:  %3.1f%%", Pars.min_nphe[s],  100.0*H.monitor[0][s]->GetBinContent(2) / H.monitor[0][s]->GetBinContent(1)));
	}
	
	Cnpe->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.044);
	lab.DrawLatex(0.05, 0.94,  "10 #times Number of photo-electrons");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.58, 0.97,  "#rightarrow no cuts");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.58, 0.93,  "#rightarrow calorimeter cuts");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.74, 0.97,  "#rightarrow calorimeter negative cuts");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.74, 0.93,  "#rightarrow all cuts applied");
	
	
   // All sectors
	TCanvas *CAnpe  = new TCanvas("CAnpe", "CAnpe", 800, 600);
	TPad    *PAnpe  = new TPad("PAnpe", "PAnpe", 0.02, 0.02,  0.98, 0.88);
	PAnpe->Draw();
	PAnpe->cd();
	
	gPad->SetLogy();
	H.nphe[0][6]->SetMinimum(10000);
	H.nphe[0][6]->Draw();
	H.nphe[1][6]->Draw("same");
	H.nphe[2][6]->Draw("same");
	H.nphe[3][6]->Draw("same");
	H.enphe[6]->Draw("same");
	
	CAnpe->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.21, 0.93,  "10 #times Number of photo-electrons");
	
	PAnpe->cd();
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.SetTextColor(colors[0]);
	
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.66, 0.92,  "#rightarrow no cuts");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.66, 0.86,  "#rightarrow calorimeter cuts");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.66, 0.80,  "#rightarrow all other negative cuts");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.66, 0.74,  "#rightarrow all cuts applied");
	
	if(PRINT != "") 
	{
		Cnpe->Print(  Form("npe_each_sector.%s", PRINT.c_str()) );
		CAnpe->Print( Form("npe_all_sectors.%s", PRINT.c_str()) );
	}

	cout << " Done showing NPE." << endl;
}






