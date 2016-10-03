show_EoEi()
{
	int s = SECTOR - 1;
	
	static int init_max;
	
	TF2 *diag = new TF1("diag", "pol1", 0, 0.1); 
	diag->SetParameter(0, 0);
	diag->SetParameter(1, 5.0/3.0); 
	diag->SetLineStyle(7);
	diag->SetLineColor(kRed+2);
	diag->SetLineWidth(2); 

	TF1 *EoutEin_cut = new TF1("up", "pol1", 0, 1);
	EoutEin_cut->SetLineColor(kGreen+3);
	EoutEin_cut->SetLineWidth(2);

	EoutEin_cut->SetParameter(0, Pars.ecop_vs_ecip_a[s]);
	EoutEin_cut->SetParameter(1, Pars.ecop_vs_ecip_b[s]);

	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++)
	{
		H.EoutEin[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.EoutEin[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.EoutEin[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.EoutEin[c][s]->GetYaxis()->SetTitleOffset(1.32);
		H.EoutEin[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.EoutEin[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.EoutEin[c][s]->GetZaxis()->SetNdivisions(8);
		if(s == 6)
		{
			H.EoutEin[c][s]->GetXaxis()->SetTitleOffset(1.1);
		}
		// Max is at Eout=0
		// Renormalizing
		H.EoutEin[c][s]->GetYaxis()->SetRangeUser(0.005, 0.3);
		H.EoutEin[c][s]->GetXaxis()->SetRangeUser(0.005, 0.3);
		double hmax = H.EoutEin[c][s]->GetMaximum()/1.5;
		H.EoutEin[c][s]->SetMaximum(hmax);
		
	}
	
	TCanvas *CEoutEinS;
	TPad    *PEoutEinS;
	
	CEoutEinS = new TCanvas(Form("CEoutEinS%d", s+1), Form("CEoutEinS%d", s+1), 1000, 1000);
	PEoutEinS = new TPad(Form("PEoutEinS%d", s+1), Form("PEoutEinS%d", s+1), 0.02, 0.00,  0.98, 0.90);
	PEoutEinS->Divide(2, 2);
	PEoutEinS->Draw();
	
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++)
	{
		PEoutEinS->cd(c+1);
		if(c==2) gPad->SetLogz();
		H.EoutEin[c][s]->Draw("colz");
		diag->Draw("same");
		EoutEin_cut->Draw("same");
		CEoutEinS->Update();
		if(H.EoutEin[c][s]->GetMaximum()>2)
		{
			palette = (TPaletteAxis*)H.EoutEin[c][s]->FindObject("palette");
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.048);
		if(c==0) 
		{
			lab.DrawLatex(0.52, 0.90,  "a. no cuts applied");
		}
		if(c==1)
		{
			lab.DrawLatex(0.42, 0.90,  "b. all other cuts applied");
			lab.DrawLatex(0.46, 0.84,  Form("entries b. / a. : %3.1f%%", 100.0*H.EoutEin[c][s]->GetEntries()/H.EoutEin[0][s]->GetEntries()));
		}
		if(c==2) 
		{
			lab.DrawLatex(0.25, 0.90,  "c. all other negative cuts applied");
			lab.DrawLatex(0.47, 0.84,  Form("entries c. / a. : %3.1f%%", 100.0*H.EoutEin[c][s]->GetEntries()/H.EoutEin[0][s]->GetEntries()));
		}
		if(c==3) 
		{

			// since there is also a cut Eout > 0.001 (most events cut out)
			// getting integral past that otherwise it seems this cut is 88%
			lab.DrawLatex(0.515, 0.90,  "d. all cuts applied");
			lab.DrawLatex(0.450, 0.84,  Form("entries d. / a. : %3.1f%%", 100.0*H.EoutEin[c][s]->Integral(0, 300, 10, 300)/H.EoutEin[0][s]->Integral(0, 300, 10, 300) ));
			lab.DrawLatex(0.450, 0.78,  Form("entries d. / b. : %3.1f%%", 100.0*H.EoutEin[c][s]->Integral(0, 300, 10, 300)/H.EoutEin[1][s]->Integral(0, 300, 10, 300) ));
		}
		
	}
	
	CEoutEinS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.036);
	lab.DrawLatex(0.07, 0.95,  Form("Minimum Ionizing Cut  -  Sector %d", SECTOR));

	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(kRed+2);
	lab.DrawLatex(0.76, 0.96,  "MIP:  y = #frac{5}{3} x");
	lab.SetTextColor(kGreen+3);
	lab.DrawLatex(0.3, 0.9,  Form("CUT:  y > %3.2f %3.1f x, Eout > 0.001", Pars.ecop_vs_ecip_a[s], Pars.ecop_vs_ecip_b[s]));
	lab.SetTextColor(kBlue+2);
	
	
	if(PRINT != "") 
	{
		CEoutEinS->Print(Form("img/cut-10EoVsEi_sector-%d.%s", s+1, PRINT.c_str()));
	}
	
//	change_sector();
}



void show_EoEi_all()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.15);
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

	
	for(int s=0; s<6; s++)
	{
		// Changing titles
		H.EoutEin[1][s]->GetXaxis()->CenterTitle(0);
		H.EoutEin[1][s]->GetXaxis()->SetTitle(Form("Sector %d              E_{in} / p", s+1));
		H.EoutEin[1][s]->GetYaxis()->SetTitle("E_{out} / p");
		H.EoutEin[1][s]->GetXaxis()->SetTitleSize(0.046);
		H.EoutEin[1][s]->GetYaxis()->SetTitleSize(0.046);
		H.EoutEin[1][s]->GetXaxis()->SetTitleOffset(1.2);
		H.EoutEin[1][s]->GetYaxis()->SetTitleOffset(1.5);
		H.EoutEin[1][s]->GetXaxis()->SetLabelSize(0.036);
		H.EoutEin[1][s]->GetYaxis()->SetLabelSize(0.036);
		H.EoutEin[1][s]->GetZaxis()->SetLabelSize(0.036);
		H.EoutEin[1][s]->GetYaxis()->SetRangeUser(0.005, 0.3);
		H.EoutEin[1][s]->GetXaxis()->SetRangeUser(0.005, 0.3);
	}

	
	TCanvas *CEoutEinA  = new TCanvas("CEoutEinA", "CEoutEinA", 1000, 1000);
	TPad    *PEoutEinA  = new TPad("PEoutEinA", "PEoutEinA", 0.02, 0.00,  0.98, 0.92);
	PEoutEinA->Divide(3, 2);
	PEoutEinA->Draw();

	TF1 *EoutEin_cut[6];
	for(int s=0; s<6; s++)
	{
		EoutEin_cut[s] = new TF1("up", "pol1", 0, 1);
		EoutEin_cut[s]->SetLineColor(kGreen+3);
		EoutEin_cut[s]->SetParameter(0, Pars.ecop_vs_ecip_a[s]);
		EoutEin_cut[s]->SetParameter(1, Pars.ecop_vs_ecip_b[s]);
		EoutEin_cut[s]->SetLineWidth(2);
	}


	TPaletteAxis *palette;
	
	for(int s=0; s<6; s++)
	{
		PEoutEinA->cd(s+1);
		H.EoutEin[1][s]->Draw("colz");
		CEoutEinA->Update();

		if(H.EoutEin[1][s]->GetMaximum()>2)
		{
			palette = (TPaletteAxis*)H.EoutEin[1][s]->FindObject("palette");
			palette->SetLabelSize(0.032);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.90);
		}
		EoutEin_cut[s]->Draw("same");
		
		lab.SetTextSize(0.055);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.3, 0.95,  Form("MIP cut / no cut: %3.1f%%",     100.0*H.EoutEin[3][s]->Integral(0, 300, 10, 300)/H.EoutEin[0][s]->Integral(0, 300, 10, 300) ));
		lab.DrawLatex(0.3, 0.90,  Form("MIP cut / all others: %3.1f%%", 100.0*H.EoutEin[3][s]->Integral(0, 300, 10, 300)/H.EoutEin[1][s]->Integral(0, 300, 10, 300)  ));
		lab.SetTextSize(0.052);
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.69, 0.80,  Form("a = %3.2f", Pars.ecop_vs_ecip_a[s]));
		lab.DrawLatex(0.69, 0.75,  Form("b = %3.1f", Pars.ecop_vs_ecip_b[s]));
	}
	
	CEoutEinA->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.034);
	lab.DrawLatex(0.06, 0.945,  "Minimum Ionizing Cut");
	lab.SetTextSize(0.028);
	lab.SetTextColor(kBlue+2);
	lab.DrawLatex(0.65, 0.945,  "All Other Cuts Applied");

	if(PRINT != "") 
	{
		CEoutEinA->Print(  Form("img/cut-10EoVsEi_sector-all.%s", PRINT.c_str()) );
	}
	
}











