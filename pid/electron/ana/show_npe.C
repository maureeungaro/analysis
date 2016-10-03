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
	
	TCanvas *Cnpe  = new TCanvas("Cnpe", "Cnpe", 1000, 1000);
	TPad    *Pnpe  = new TPad("Pnpe", "Pnpe", 0.02, 0.00,  0.98, 0.92);
   Pnpe->Divide(3, 2);
	Pnpe->Draw();

	
	for(int s=0; s<6; s++)
	{
		Pnpe->cd(s+1);
		H.nphe[0][s]->Draw();
		H.nphe[1][s]->Draw("same");
		H.nphe[2][s]->Draw("same");
		H.nphe[3][s]->Draw("same");
		H.enphe[s]->Draw("same");
		npe_cut[s]->Draw();
		gPad->SetLogy();
		lab.SetTextColor(colors[0]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.05);
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.38, 0.91,  Form("calorimeter / no cut:  %3.1f%%",                            100.0*H.theta_vs_segm[1][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries() ));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.28, 0.85,  Form("neg calorimeter / no cut:  %3.1f%%",                        100.0*H.theta_vs_segm[2][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries() ));
		lab.SetTextColor(colors[0]);
		lab.DrawLatex(0.3, 0.79,  Form("nphe #geq %2.0f / calorimeter:  %3.1f%%", Pars.min_nphe[s],  100.0*H.nphe[3][s]->GetEntries() / H.nphe[1][s]->GetEntries() ));
		lab.SetTextColor(colors[1]);
	}
	
	Cnpe->cd(0);

	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.2, 0.97,  "#rightarrow no cuts");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.2, 0.93,  "#rightarrow calorimeter cuts");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.6, 0.97,  "#rightarrow calorimeter negative cuts");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.6, 0.93,  "#rightarrow all cuts applied");
	

	if(PRINT != "") 
	{
		Cnpe->Print(  Form("img/cut-12nphe_sector-all.%s", PRINT.c_str()) );
	}

	cout << " Done showing NPE." << endl;
}

void show_npeSingle()
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

	int s = SECTOR - 1;

	for(int c=0; c<4; c++)
	{
		H.nphe[c][s]->GetXaxis()->SetTitleSize(0.04);
		H.nphe[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.nphe[c][s]->GetXaxis()->SetLabelSize(0.035);
		H.nphe[c][s]->GetYaxis()->SetLabelSize(0.035);
	}

	TLine *npe_cut = new TLine(Pars.min_nphe[s], 0, Pars.min_nphe[s], H.nphe[1][s]->GetMaximum());
	npe_cut->SetLineStyle(2);


	TCanvas *Cnpe  = new TCanvas("Cnpe", "Cnpe", 1000, 1000);
	TPad    *Pnpe  = new TPad("Pnpe", "Pnpe", 0.02, 0.00,  0.98, 0.92);
	Pnpe->Draw();

	H.nphe[0][s]->Draw();
	H.nphe[1][s]->Draw("same");
	H.nphe[2][s]->Draw("same");
	H.nphe[3][s]->Draw("same");
	H.enphe[s]->Draw("same");
	npe_cut->Draw();
	gPad->SetLogy();
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.48, 0.85,  Form("calorimeter / no cut:  %3.1f%%",                            100.0*H.theta_vs_segm[1][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries() ));
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.41, 0.79,  Form("neg calorimeter / no cut:  %3.1f%%",                        100.0*H.theta_vs_segm[2][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries() ));
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.42, 0.73,  Form("nphe #geq %2.0f / calorimeter:  %3.1f%%", Pars.min_nphe[s], 100.0*H.nphe[3][s]->GetEntries() / H.nphe[1][s]->GetEntries() ));

	Cnpe->cd(0);
	lab.SetTextFont(102);

	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.3, 0.97,  "#rightarrow no cuts");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.3, 0.93,  "#rightarrow calorimeter cuts");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.6, 0.97,  "#rightarrow calorimeter negative cuts");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.6, 0.93,  "#rightarrow all cuts applied");


	if(PRINT != "")
	{
		Cnpe->Print(  Form("img/cut-12nphe_sector-%d.%s", SECTOR, PRINT.c_str()) );
	}

	cout << " Done showing NPE." << endl;
}







