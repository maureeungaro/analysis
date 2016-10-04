void show_mass_beta()
{
	int s = SECTOR - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.08);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<2; c++)
	{
		H.mass_vs_mom[c][s]->GetXaxis()->SetTitle("p  [GeV]");
		H.mass_vs_mom[c][s]->GetYaxis()->SetTitle("TOF Mass  [GeV]");
		
		H.mass_vs_mom[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.mass_vs_mom[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.mass_vs_mom[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.mass_vs_mom[c][s]->GetYaxis()->SetTitleOffset(1.12);
		H.mass_vs_mom[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.mass_vs_mom[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.mass_vs_mom[c][s]->GetZaxis()->SetNdivisions(8);
		H.mass_vs_mom[c][s]->GetXaxis()->SetRangeUser(0.0, 4.5);
		
		H.beta_vs_mom[c][s]->GetXaxis()->SetTitle("p  [GeV]");
		H.beta_vs_mom[c][s]->GetYaxis()->SetTitle("TOF Beta  [GeV]");
		
		H.beta_vs_mom[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.beta_vs_mom[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.beta_vs_mom[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.beta_vs_mom[c][s]->GetYaxis()->SetTitleOffset(1.12);
		H.beta_vs_mom[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.beta_vs_mom[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.beta_vs_mom[c][s]->GetZaxis()->SetNdivisions(8);
		H.beta_vs_mom[c][s]->GetXaxis()->SetRangeUser(0.0, 4.5);
	
	}
	
	TCanvas *CecpS;
	TPad    *PecpS;
	
	CecpS = new TCanvas(Form("CecpS%d", s+1), Form("CecpS%d", s+1), 1000, 1000);
	PecpS = new TPad(Form("PecpS%d", s+1), Form("PecpS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	PecpS->Divide(2, 2);
	PecpS->Draw();

	
	dt_me->SetParameter(0, SECTOR);
	dt_up->SetParameter(0, SECTOR);
	dt_up->SetParameter(1, Pars.NSIGMAS[0]);
	dt_up->SetParameter(2, 1);
	dt_dn->SetParameter(0, SECTOR);
	dt_dn->SetParameter(1, Pars.NSIGMAS[1]);
	dt_dn->SetParameter(2, -1);
	
	dt_me->SetLineWidth(2);
	dt_me->SetLineStyle(8);
	dt_me->SetLineColor(kRed+3);
		
	dt_up->SetLineWidth(2);
	dt_up->SetLineStyle(9);
	dt_up->SetLineColor(kRed+3);
		
	dt_dn->SetLineWidth(2);
	dt_dn->SetLineStyle(9);
	dt_dn->SetLineColor(kRed+3);
	
	
	TPaletteAxis *palette;
	
	lab.SetTextColor(kBlue+2);
	lab.SetTextFont(42);
	lab.SetTextSize(0.050);	
	
	PecpS->cd(1);
	gPad->SetLogz();
	H.mass_vs_mom[0][s]->Draw("colz");
	CecpS->Update();
	palette = (TPaletteAxis*)H.mass_vs_mom[0][s]->FindObject("palette");
	palette->SetLabelSize(0.035);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.88);
	palette->SetX2NDC(0.92);
	lab.DrawLatex(0.37, 0.95,  "no cuts applied");
	
	
	PecpS->cd(2);
	gPad->SetLogz();
	H.mass_vs_mom[1][s]->Draw("colz");
	CecpS->Update();
	palette = (TPaletteAxis*)H.mass_vs_mom[1][s]->FindObject("palette");
	palette->SetLabelSize(0.035);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.88);
	palette->SetX2NDC(0.92);
	lab.DrawLatex(0.36, 0.95,  "#Delta T cut applied");
	
	
	PecpS->cd(3);
	gPad->SetLogz();
	H.beta_vs_mom[0][s]->Draw("colz");
	CecpS->Update();
	palette = (TPaletteAxis*)H.beta_vs_mom[0][s]->FindObject("palette");
	palette->SetLabelSize(0.035);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.88);
	palette->SetX2NDC(0.92);
	lab.DrawLatex(0.37, 0.95,  "no cuts applied");
	
	
	PecpS->cd(4);
	gPad->SetLogz();
	H.beta_vs_mom[1][s]->Draw("colz");
	CecpS->Update();
	palette = (TPaletteAxis*)H.beta_vs_mom[1][s]->FindObject("palette");
	palette->SetLabelSize(0.035);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.88);
	palette->SetX2NDC(0.92);
	lab.DrawLatex(0.36, 0.95,  "#Delta T cut applied");
	
	
	CecpS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.14, 0.95,  Form("TOF Mass and Beta vs p  -   Sector %d", SECTOR));

	if(PRINT != "") 
	{
		CecpS->Print( Form("img/dist-massNbeta_sector-%d.%s", s+1, PRINT.c_str()) );
	}
}


void show_betaAll()
{
	int s = SECTOR - 1;

	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.08);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();

	for(int s=0; s<6; s++)
	{
		for(int c=0; c<2; c++)
		{

			H.beta_vs_mom[c][s]->GetXaxis()->SetTitle("p  [GeV]");
			H.beta_vs_mom[c][s]->GetYaxis()->SetTitle("TOF Beta  [GeV]");

			H.beta_vs_mom[c][s]->GetXaxis()->SetTitleSize(0.052);
			H.beta_vs_mom[c][s]->GetXaxis()->SetTitleOffset(1.14);
			H.beta_vs_mom[c][s]->GetYaxis()->SetTitleSize(0.054);
			H.beta_vs_mom[c][s]->GetYaxis()->SetTitleOffset(1.12);
			H.beta_vs_mom[c][s]->GetXaxis()->SetLabelSize(0.042);
			H.beta_vs_mom[c][s]->GetYaxis()->SetLabelSize(0.042);
			H.beta_vs_mom[c][s]->GetZaxis()->SetNdivisions(8);
			H.beta_vs_mom[c][s]->GetXaxis()->SetRangeUser(0.0, 4.5);
			
		}
	}

	TCanvas *CecpS;
	TPad    *PecpS;

	CecpS = new TCanvas("CecpS", "CecpS", 1000, 1000);
	PecpS = new TPad("PecpS", "PecpS", 0.02, 0.00,  0.98, 0.92);
	PecpS->Divide(3, 2);
	PecpS->Draw();

	TPaletteAxis *palette;
	for(int s=0; s<6; s++)
	{
		PecpS->cd(s+1);
		gPad->SetLogz();
		H.beta_vs_mom[1][s]->Draw("colz");
		CecpS->Update();

		palette = (TPaletteAxis*)H.beta_vs_mom[1][s]->FindObject("palette");
		palette->SetLabelSize(0.035);
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.88);
		palette->SetX2NDC(0.92);
		lab.DrawLatex(0.36, 0.95,  "#Delta T cut applied");

	}


	CecpS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.14, 0.95,  Form("Beta vs p"));

	if(PRINT != "")
	{
		CecpS->Print( Form("img/dist-massNbeta_sector-all.%s", PRINT.c_str()) );
	}
}








