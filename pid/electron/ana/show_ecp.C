void show_ecp()
{
	int s = SECTOR - 1;
	
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++)
	{
		H.ecp[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.ecp[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.ecp[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.ecp[c][s]->GetYaxis()->SetTitleOffset(1.32);
		H.ecp[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.ecp[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.ecp[c][s]->GetZaxis()->SetNdivisions(8);
		if(s == 6)
		{
			H.ecp[c][s]->GetXaxis()->SetTitleOffset(1.1);
		}
	}
	
	TCanvas *CecpS;
	TPad    *PecpS;
	
	CecpS = new TCanvas(Form("CecpS%d", s+1), Form("CecpS%d", s+1), 1000, 1000);
	PecpS = new TPad(Form("PecpS%d", s+1), Form("PecpS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	PecpS->Divide(2, 2);
	PecpS->Draw();

	sf_me->SetParameter(0, SECTOR);
	sf_up->SetParameter(0, SECTOR);
	sf_up->SetParameter(1, Pars.NSIGMAS[0]);
	sf_up->SetParameter(2, 1);
	sf_dn->SetParameter(0, SECTOR);
	sf_dn->SetParameter(1, Pars.NSIGMAS[1]);
	sf_dn->SetParameter(2, -1);
	
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++)
	{
		PecpS->cd(c+1);
		H.ecp[c][s]->Draw("colz");
		CecpS->Update();
		if(H.ecp[c][s]->GetMaximum()>1)
		{
			palette = (TPaletteAxis*)H.ecp[c][s]->FindObject("palette");
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		sf_up->SetLineWidth(2);
		sf_dn->SetLineWidth(2);
		sf_up->Draw("same");
		sf_dn->Draw("same");
		sf_me->Draw("same");
		
		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.050);
		if(c==0) 
		{
			lab.DrawLatex(0.50, 0.90,  "a. no cuts applied");
		}
		if(c==1)
		{
			lab.DrawLatex(0.39, 0.30,  "b. all other cuts applied");
			lab.DrawLatex(0.43, 0.23,  Form("entries b. / a. : %3.1f%%", 100.0*H.ecp[c][s]->GetEntries()/H.ecp[0][s]->GetEntries()));
		}
		if(c==2) 
		{
			lab.DrawLatex(0.23, 0.90,  "c. all other negative cuts applied");
			lab.DrawLatex(0.46, 0.82,  Form("entries c. / a. : %3.1f%%", 100.0*H.ecp[c][s]->GetEntries()/H.ecp[0][s]->GetEntries()));
		}
		if(c==3) 
		{
			lab.DrawLatex(0.49, 0.38,  "d. all cuts applied");
			lab.DrawLatex(0.42, 0.31,  Form("entries d. / a. : %3.1f%%", 100.0*H.ecp[c][s]->GetEntries()/H.ecp[0][s]->GetEntries()));
			lab.DrawLatex(0.42, 0.24,  Form("entries d. / b. : %3.1f%%", 100.0*H.ecp[c][s]->GetEntries()/H.ecp[1][s]->GetEntries()));
			
			// summary of total events passed
			lab.DrawLatex(0.28, 0.90,  Form("Passed all cuts: %2.3e", H.ecp[c][s]->GetEntries()));
		}
	}
	
	CecpS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.18, 0.95,  Form("Sampling Fraction  -   Sector %d", SECTOR));

	if(PRINT != "") 
	{
		CecpS->Print( Form("img/epid5cut-sampfd_sector-%d.%s", s+1, PRINT.c_str()) );
	}
}



void show_ecps()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	
	int s = SECTOR - 1;
	int NBINS = H.ecp[1][0]->GetNbinsX();
	int db = NBINS/NDIV;
	
	TCanvas *Cecp  = new TCanvas("Cecp", "Cecp", 1000, 1000);
	
	// Changing titles
	H.ecp[1][s]->GetXaxis()->CenterTitle(0);
	H.ecp[1][s]->GetXaxis()->SetTitle(Form("Sector %d                   p [GeV]", SECTOR));
	H.ecp[1][s]->GetXaxis()->SetTitleSize(0.040);
	H.ecp[1][s]->GetYaxis()->SetTitleSize(0.040);
	H.ecp[1][s]->GetXaxis()->SetTitleOffset(1.2);
	H.ecp[1][s]->GetYaxis()->SetTitleOffset(1.5);
	H.ecp[1][s]->GetXaxis()->SetLabelSize(0.032);
	H.ecp[1][s]->GetYaxis()->SetLabelSize(0.032);
	H.ecp[1][s]->GetZaxis()->SetLabelSize(0.032);

	H.ecp[1][s]->Draw("colz");
	
	Cecp->Update();     // important, otherwise it won't find the palette
	TPaletteAxis *palette = (TPaletteAxis*)H.ecp[1][s]->FindObject("palette");
	palette->SetLabelSize(0.032);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.85);
	palette->SetX2NDC(0.89);
	palette->SetY2NDC(0.88);
	
	if(sf_mean[s])
	{
		sf_mean[s]->GetFunction("pol3")->SetLineColor(kRed+2);
		sf_mean[s]->GetFunction("pol3")->SetLineWidth(1);
		sf_mean[s]->GetFunction("pol3")->SetLineStyle(2);
		sf_mean[s]->SetMarkerStyle(20);
		sf_mean[s]->SetMarkerSize(0.8);
		sf_mean[s]->Draw("P");
	}
	
	
	sf_me->SetParameter(0, SECTOR);
	
	sf_up->SetParameter(0, SECTOR);
	sf_up->SetParameter(1, Pars.NSIGMAS[0]);
	sf_up->SetParameter(2, 1);
	sf_dn->SetParameter(0, SECTOR);
	sf_dn->SetParameter(1, Pars.NSIGMAS[1]);
	sf_dn->SetParameter(2, -1);
	
	sf_up->SetLineWidth(3);
	sf_dn->SetLineWidth(3);
	sf_up->Draw("same");
	sf_dn->Draw("same");
	sf_me->Draw("same");
	
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.DrawLatex(0.13, 0.94,  "Sampling Fraction");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.028);
	lab.SetTextColor(kRed+2);
	lab.DrawLatex(0.65, 0.96,  Form("Upper Limit: #mu + %3.2f #sigma", Pars.NSIGMAS[0]));
	lab.DrawLatex(0.65, 0.92,  Form("Lower Limit: #mu - %3.2f #sigma", Pars.NSIGMAS[1]));
	
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.61, 0.30,  Form("ec / no ec:  %3.1f%%",                 100.0*hit_ec[s] / no_cc_or_ec[s]));
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.424, 0.25,  Form("Sampling Fraction Cut / ec: %3.1f%%", 100.0*H.monitor[0][s]->GetBinContent(4)  / H.monitor[0][s]->GetBinContent(1)));
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.60, 0.20,   Form("all cuts / ec: %3.1f%%",              100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
	lab.SetTextColor(colors[1]);
	lab.SetTextFont(102);
	lab.DrawLatex(0.48, 0.84,  "All Other Cuts Applied");
	
	if(PRINT != "") 
	{
		Cecp->Print( Form("img/epid5cut-sampf_sector-%d.%s", s+1, PRINT.c_str()) );
	}
	
	if(sf_mean[s])
		Cecp->AddExec("dynamic","DynamicExec()");
	
}



void DynamicExec()
{
	
	int s = SECTOR - 1;
	
	TObject *select = gPad->GetSelected();
	if(!select) return;
	if (!select->InheritsFrom("TH2")) {gPad->SetUniqueID(0); return;}
	TH2 *h = (TH2*)select;
	gPad->GetCanvas()->FeedbackMode(kTRUE);

   // erase old position and draw a line at current position
	int pxold = gPad->GetUniqueID();
	int px = gPad->GetEventX();
	int py = gPad->GetEventY();
	float uymin = gPad->GetUymin();
	float uymax = gPad->GetUymax();
	int pymin = gPad->YtoAbsPixel(uymin);
	int pymax = gPad->YtoAbsPixel(uymax);
	if(pxold) gVirtualX->DrawLine(pxold, pymin, pxold ,pymax);
	gVirtualX->DrawLine(px, pymin, px, pymax);
	gPad->SetUniqueID(px);
	float upx = gPad->AbsPixeltoX(px);
	float x = gPad->PadtoX(upx);
	
	// draw slice corresponding to mouse position
	double dp   = (H.ecp[1][0]->GetXaxis()->GetXmax()  - H.ecp[1][0]->GetXaxis()->GetXmin())/NDIV;
	int hid  = floor((x - H.ecp[1][0]->GetXaxis()->GetXmin())/dp);
	
//	cout << " x: " << x << " dp: " << dp << "  hid: " << hid << endl;	
	
	DrawFit(s, hid);
}


void DrawFit(int s, int hid)
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	double dp   = (H.ecp[1][0]->GetXaxis()->GetXmax()  - H.ecp[1][0]->GetXaxis()->GetXmin())/NDIV;

   // create or set the new canvas c2
	TVirtualPad *padsav = gPad;
	TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
	if(c2) delete c2->GetPrimitive("Projection");
	else   c2 = new TCanvas("c2","Projection Canvas",710,10,800,800);
	c2->cd();
	
	if(ecp1d[s][hid])
	{
		double pmin = H.ecp[1][0]->GetXaxis()->GetXmin() + hid*dp;
		double pmax = H.ecp[1][0]->GetXaxis()->GetXmin() + (hid+1)*dp;
		ecp1d[s][hid]->GetXaxis()->SetRangeUser(0.1, 0.5);
		ecp1d[s][hid]->GetXaxis()->SetTitleOffset(1.3);
		ecp1d[s][hid]->Draw();
		lab.SetTextFont(102);
		lab.SetTextSize(0.058);
		lab.DrawLatex(0.3, 0.92,  "Sampling Fraction");
		lab.SetTextFont(42);
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.66, 0.82,  Form("Sector %d", SECTOR));
		lab.DrawLatex(0.60, 0.76,  Form("p = %3.1f - %3.1f GeV", pmin, pmax ));
		lab.SetTextColor(kRed+2);
		lab.DrawLatex(0.59, 0.68,  Form("#mu = %4.3f #pm %2.1e",    ecp1d[s][hid]->GetFunction("MyFit")->GetParameter(4), ecp1d[s][hid]->GetFunction("MyFit")->GetParError(4)));
		lab.DrawLatex(0.59, 0.62,  Form("#sigma = %4.3f #pm %2.1e", ecp1d[s][hid]->GetFunction("MyFit")->GetParameter(5), ecp1d[s][hid]->GetFunction("MyFit")->GetParError(5)));
	}

	c2->Update();
	padsav->cd();
	
	if(PRINT != "") 
	{
		if(hid>=9)
			c2->Print(Form("imgs/slice-%d_epid5cut-sampf_sector-%d.%s", hid+1, s+1, PRINT.c_str()) );
		else
			c2->Print(Form("imgs/slice-0%d_epid5cut-sampf_sector-%d.%s", hid+1, s+1, PRINT.c_str()) );
	}

}


void show_ecp_all_sectors()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.02);
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
		H.ecp[1][s]->GetXaxis()->CenterTitle(0);
		H.ecp[1][s]->GetXaxis()->SetTitle(Form("Sector %d              p [GeV]", s+1));
		H.ecp[1][s]->GetYaxis()->SetTitle(Form("E_{TOT} / p"));
		H.ecp[1][s]->GetXaxis()->SetTitleSize(0.046);
		H.ecp[1][s]->GetYaxis()->SetTitleSize(0.046);
		H.ecp[1][s]->GetXaxis()->SetTitleOffset(1.2);
		H.ecp[1][s]->GetYaxis()->SetTitleOffset(1.5);
		H.ecp[1][s]->GetXaxis()->SetLabelSize(0.036);
		H.ecp[1][s]->GetYaxis()->SetLabelSize(0.036);
		H.ecp[1][s]->GetZaxis()->SetLabelSize(0.036);
		H.ecp[1][s]->GetYaxis()->SetRangeUser(0.1, 0.45);
	}

	
	TCanvas *CecpA  = new TCanvas("CecpA", "CecpA", 1000, 1000);
	TPad    *PecpA  = new TPad("PecpA", "PecpA", 0.02, 0.00,  0.98, 0.92);
	PecpA->Divide(3, 2);
	PecpA->Draw();

	TPaletteAxis *palette;
	
	for(int s=0; s<6; s++)
	{
		PecpA->cd(s+1);
		gPad->SetGridx();
		gPad->SetGridy();
		H.ecp[1][s]->Draw("colz");
		CecpA->Update();
		
		palette = (TPaletteAxis*)H.ecp[1][s]->FindObject("palette");
		palette->SetLabelSize(0.032);
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.89);
		
		sf_me->SetParameter(0, s+1);
		sf_up->SetParameter(0, s+1);
		sf_up->SetParameter(1, Pars.NSIGMAS[0]);
		sf_up->SetParameter(2, 1);
		sf_dn->SetParameter(0, s+1);
		sf_dn->SetParameter(1, Pars.NSIGMAS[1]);
		sf_dn->SetParameter(2, -1);
	
		sf_up->SetLineWidth(3);
		sf_dn->SetLineWidth(3);
		sf_up->Draw("same");
		sf_dn->Draw("same");
		sf_me->Draw("same");
		
		hor->Draw("same");
	}
	
	CecpA->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.044);
	lab.DrawLatex(0.10, 0.94,  "Sampling Fraction - All Sectors");
	lab.SetTextSize(0.026);
	lab.SetTextColor(kBlue+2);
	lab.DrawLatex(0.72, 0.94,  "All Other Cuts Applied");
	
	
	
	
	if(PRINT != "") 
	{
		CecpA->Print(Form("img/epid5cut-sampf_sector-all.%s", PRINT.c_str()));

	}
	
}











