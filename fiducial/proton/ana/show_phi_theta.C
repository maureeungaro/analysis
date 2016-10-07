void show_phi_theta()
{
	int s = SECTOR - 1;
	int m = MOM - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++)
	{
		H.phi_theta[c][s][m]->GetXaxis()->SetTitleSize(0.052);
		H.phi_theta[c][s][m]->GetXaxis()->SetTitleOffset(1.14);
		H.phi_theta[c][s][m]->GetYaxis()->SetTitleSize(0.054);
		H.phi_theta[c][s][m]->GetYaxis()->SetTitleOffset(1.32);
		H.phi_theta[c][s][m]->GetXaxis()->SetLabelSize(0.042);
		H.phi_theta[c][s][m]->GetYaxis()->SetLabelSize(0.042);
		H.phi_theta[c][s][m]->GetZaxis()->SetNdivisions(8);
		if(s == 6)
		{
			H.phi_theta[c][s][m]->GetXaxis()->SetTitleOffset(1.1);
		}
	}
	
	TCanvas *Cphi_thetaS;
	TPad    *Pphi_thetaS;
	
	Cphi_thetaS = new TCanvas(Form("Cphi_thetaS%d", s+1), Form("Cphi_thetaS%d", s+1), 940, 900);
	Pphi_thetaS = new TPad(Form("Pphi_thetaS%d", s+1), Form("Pphi_thetaS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Pphi_thetaS->Divide(2, 2);
	Pphi_thetaS->Draw();
		
	TPaletteAxis *palette;
	for(int c=0; c<4; c++)
	{
		Pphi_thetaS->cd(c+1);
		H.phi_theta[c][s][m]->Draw("colz");
		Cphi_thetaS->Update();
		if(H.phi_theta[c][s][m]->GetMaximum() > 1)
		{
			palette = (TPaletteAxis*)H.phi_theta[c][s][m]->FindObject("palette");
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.050);
		if(c==0) 
		{
			lab.DrawLatex(0.16, 0.91,  "a. no cuts applied");
		}
		if(c==1)
		{
			lab.DrawLatex(0.16, 0.91,  "b. planes cuts applied");
			lab.DrawLatex(0.16, 0.18,  Form("entries b. / a. : %3.1f%%", 100.0*H.phi_theta[c][s][m]->GetEntries()/H.phi_theta[0][s][m]->GetEntries()));
		}
		if(c==2)
		{
			lab.DrawLatex(0.16, 0.91,  "c. planes negative cuts applied");
			lab.DrawLatex(0.16, 0.18,  Form("entries c. / a. : %3.1f%%", 100.0*H.phi_theta[c][s][m]->GetEntries()/H.phi_theta[0][s][m]->GetEntries()));
		}
		if(c==3)
		{
			lab.DrawLatex(0.16, 0.91,  "d. all cuts applied");
			lab.DrawLatex(0.16, 0.18,  Form("entries d. / c. : %3.1f%%", 100.0*H.phi_theta[c][s][m]->GetEntries()/H.phi_theta[1][s][m]->GetEntries()));
		}
	}
	
	Cphi_thetaS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	lab.DrawLatex(0.04, 0.95,  Form("Fiducial Cut - Sector %d - Momentum: %3.1f#pm%3.2f GeV", SECTOR, H.mom[m], H.dp/2));

	
	
	if(PRINT != "") 
	{
		Cphi_thetaS->Print( Form("phi_vs_theta_m%d_sect%d.%s", m+1, s+1, PRINT.c_str()) );
	}
}



void show_phi_thetas(int which)
{
	int s  = SECTOR - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.2);

	TLatex lab;
	lab.SetNDC();
	
	TCanvas *Cphi_thetaS = new TCanvas(Form("Cphi_thetaS%d", s+1), Form("Cphi_thetaS%d", s+1), 940, 1100);
	TPad    *Pphi_thetaS = new TPad(Form("Pphi_thetaS%d", s+1), Form("Pphi_thetaS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Pphi_thetaS->Divide(2, 5);
	Pphi_thetaS->Draw();
	
	lab.SetTextSize(0.08);
	lab.SetTextColor(kBlue+3);

	TPaletteAxis *palette;
	for(int m=0; m<H.NDIV_P; m++)
	{
		Pphi_thetaS->cd(m+1);
		if(H.phi_theta[which][s][m]->GetMaximum() > 1)
		{
			gPad->SetLogz();
			H.phi_theta[which][s][m]->SetMinimum(1);
			H.phi_theta[which][s][m]->GetXaxis()->SetTitleSize(0.1);
			H.phi_theta[which][s][m]->GetYaxis()->SetTitleSize(0.1);
			H.phi_theta[which][s][m]->GetXaxis()->SetTitleOffset(0.9);
			H.phi_theta[which][s][m]->GetYaxis()->SetTitleOffset(0.5);
			H.phi_theta[which][s][m]->GetXaxis()->SetLabelSize(0.07);
			H.phi_theta[which][s][m]->GetYaxis()->SetLabelSize(0.07);
			H.phi_theta[which][s][m]->GetZaxis()->SetNdivisions(10);
			H.phi_theta[which][s][m]->GetYaxis()->SetNdivisions(5);
			H.phi_theta[which][s][m]->GetXaxis()->SetTitle("#theta        [deg]");
			H.phi_theta[which][s][m]->GetYaxis()->SetTitle("#phi        [deg]");

			H.phi_theta[which][s][m]->Draw("colz");
			Cphi_thetaS->Update();
			palette = (TPaletteAxis*)H.phi_theta[which][s][m]->FindObject("palette");
			palette->SetLabelSize(0.08);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
		}
		lab.DrawLatex(0.28, 0.94,  Form("momentum: %3.2f #leq p #leq %3.2f GeV", H.mom[m]-H.dp/2, H.mom[m]+H.dp/2 ) );
		
	}
	
	Cphi_thetaS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.035);
	if(which == 0) lab.DrawLatex(0.04, 0.95,  Form("#phi versus #theta in Sector %d  -  No Cuts Applied", SECTOR));
	if(which == 1) lab.DrawLatex(0.04, 0.95,  Form("#phi versus #theta in Sector %d  -  Planes Cuts Applied", SECTOR));

	if(PRINT != "")
	{
		Cphi_thetaS->Print( Form("phi_vs_theta_%d_sect%d.%s", which, s+1, PRINT.c_str()) );
	}
}






