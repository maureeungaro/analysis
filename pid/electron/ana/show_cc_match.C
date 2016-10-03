void show_cc_match()
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
		H.theta_vs_segm[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.theta_vs_segm[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.theta_vs_segm[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.theta_vs_segm[c][s]->GetYaxis()->SetTitleOffset(1.1);
		H.theta_vs_segm[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.theta_vs_segm[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.theta_vs_segm[c][s]->GetZaxis()->SetNdivisions(8);
		if(s == 6)
		{
			H.theta_vs_segm[c][s]->GetXaxis()->SetTitleOffset(1.1);
		}
	}
	
	TCanvas *Ctheta_vs_segmS;
	TPad    *Ptheta_vs_segmS;
	
	Ctheta_vs_segmS = new TCanvas(Form("Ctheta_vs_segmS%d", s+1), Form("Ctheta_vs_segmS%d", s+1), 1000, 1000);
	Ptheta_vs_segmS = new TPad(Form("Ptheta_vs_segmS%d", s+1), Form("Ptheta_vs_segmS%d", s+1), 0.02, 0.00,  0.98, 0.92);
	Ptheta_vs_segmS->Divide(2, 2);
	Ptheta_vs_segmS->Draw();

	cc_match_me->SetParameter(0, SECTOR);
	
	cc_match_up->SetParameter(0, SECTOR);
	cc_match_up->SetParameter(1, Pars.CC_NSIGMAS[0]);
	cc_match_up->SetParameter(2, 1);
	cc_match_dn->SetParameter(0, SECTOR);
	cc_match_dn->SetParameter(1, Pars.CC_NSIGMAS[1]);
	cc_match_dn->SetParameter(2, -1);
	
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++)
	{
		Ptheta_vs_segmS->cd(c+1);
		gPad->SetLogz();
		H.theta_vs_segm[c][s]->Draw("colz");
		Ctheta_vs_segmS->Update();
		if(H.theta_vs_segm[c][s]->GetMaximum()>1)
		{
			palette = (TPaletteAxis*)H.theta_vs_segm[c][s]->FindObject("palette");
			palette->SetLabelSize(0.035);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.92);
			palette->SetY2NDC(0.96);
		}
		cc_match_up->SetLineWidth(2);
		cc_match_dn->SetLineWidth(2);
		cc_match_up->Draw("same");
		cc_match_dn->Draw("same");
		cc_match_me->Draw("same");
		
		lab.SetTextColor(colors[c]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.050);
		if(c==0) 
		{
			lab.DrawLatex(0.48, 0.91,  "a. no cuts applied");
		}
		if(c==1)
		{
			lab.DrawLatex(0.35, 0.25,  "b. calorimeter cuts applied");
			lab.DrawLatex(0.43, 0.19,  Form("entries b. / a. : %3.1f%%", 100.0*H.theta_vs_segm[c][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries()));
		}
		if(c==2) 
		{
			lab.DrawLatex(0.18, 0.90,  "c. calorimeter negative cuts applied");
			lab.DrawLatex(0.39, 0.82,  Form("entries c. / a. : %3.1f%%", 100.0*H.theta_vs_segm[c][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries()));
		}
		if(c==3) 
		{
			lab.DrawLatex(0.43, 0.32,  "d. all cuts applied");
			lab.DrawLatex(0.36, 0.26,  Form("entries d. / a. : %3.1f%%", 100.0*H.theta_vs_segm[c][s]->GetEntries()/H.theta_vs_segm[0][s]->GetEntries()));
			lab.DrawLatex(0.36, 0.20,  Form("entries d. / b. : %3.1f%%", 100.0*H.theta_vs_segm[c][s]->GetEntries()/H.theta_vs_segm[1][s]->GetEntries()));
		}
	}
	
	Ctheta_vs_segmS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.26, 0.95,  Form("CC #theta Matching  -  Sector %d", SECTOR));

	if(PRINT != "") 
	{
		Ctheta_vs_segmS->Print( Form("img/cut-01ccthmd_sector-%d.%s", s+1, PRINT.c_str()) );
	}
}



void show_theta_vs_segms()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	
	int s = SECTOR - 1;
	int NBINS = H.theta_vs_segm[1][0]->GetNbinsX();
	int db = NBINS/NDIV;
	
	TCanvas *Ctheta_vs_segm  = new TCanvas("Ctheta_vs_segm", "Ctheta_vs_segm", 1000, 1000);
	gPad->SetLogz();
	
	// Changing titles
	H.theta_vs_segm[1][s]->GetXaxis()->CenterTitle(0);
	H.theta_vs_segm[1][s]->GetXaxis()->SetTitleSize(0.040);
	H.theta_vs_segm[1][s]->GetYaxis()->SetTitleSize(0.040);
	H.theta_vs_segm[1][s]->GetXaxis()->SetTitleOffset(1.2);
	H.theta_vs_segm[1][s]->GetYaxis()->SetTitleOffset(1.2);
	H.theta_vs_segm[1][s]->GetXaxis()->SetLabelSize(0.032);
	H.theta_vs_segm[1][s]->GetYaxis()->SetLabelSize(0.032);
	H.theta_vs_segm[1][s]->GetZaxis()->SetLabelSize(0.032);

	H.theta_vs_segm[1][s]->Draw("colz");
	
	Ctheta_vs_segm->Update();     // important, otherwise it won't find the palette
	TPaletteAxis *palette;
	if(H.theta_vs_segm[1][s]->GetMaximum()>1)
	{
		palette = (TPaletteAxis*)H.theta_vs_segm[1][s]->FindObject("palette");
		palette->SetLabelSize(0.032);
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.85);
		palette->SetX2NDC(0.89);
		palette->SetY2NDC(0.88);
	}
	if(cc_match_mean[s])
	{
		cc_match_mean[s]->Draw("P");
	}
	
	cc_match_me->SetParameter(0, SECTOR);
	
	cc_match_up->SetParameter(0, SECTOR);
	cc_match_up->SetParameter(1, Pars.CC_NSIGMAS[0]);
	cc_match_up->SetParameter(2, 1);
	cc_match_dn->SetParameter(0, SECTOR);
	cc_match_dn->SetParameter(1, Pars.CC_NSIGMAS[1]);
	cc_match_dn->SetParameter(2, -1);
	
	cc_match_up->SetLineWidth(3);
	cc_match_dn->SetLineWidth(3);
	cc_match_up->Draw("same");
	cc_match_dn->Draw("same");
	cc_match_me->Draw("same");
	
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.DrawLatex(0.13, 0.94,  "CC #theta Matching");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.028);
	lab.SetTextColor(kRed+2);
	lab.DrawLatex(0.65, 0.96,  Form("Upper Limit: #mu + %3.2f #sigma", Pars.CC_NSIGMAS[0]));
	lab.DrawLatex(0.65, 0.92,  Form("Lower Limit: #mu - %3.2f #sigma", Pars.CC_NSIGMAS[1]));
	
	
	if(PRINT != "") 
	{
		Ctheta_vs_segm->Print(Form("img/cut-01ccthm_sector-%d.%s", s+1, PRINT.c_str()));
	}
	
	if(cc_match_mean[s])
		Ctheta_vs_segm->AddExec("dynamic","CC_DynamicExec()");
	
}



void CC_DynamicExec()
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
	if((int)(x-1) < 18)
	CC_DrawFit(s, (int)(x-1));
}


void CC_DrawFit(int s, int hid)
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();

   // create or set the new canvas c2
	TVirtualPad *padsav = gPad;
	TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
	if(c2) delete c2->GetPrimitive("Projection");
	else   c2 = new TCanvas("c2","Projection Canvas",710,10,800,800);
	c2->cd();
	
	if(cc_match1d[s][hid])
	{
		cc_match1d[s][hid]->GetXaxis()->SetTitleOffset(1.3);
		cc_match1d[s][hid]->Draw();
		lab.SetTextFont(102);
		lab.SetTextSize(0.058);
		lab.DrawLatex(0.34, 0.92,  "#theta on CC plane");
		lab.SetTextFont(42);
		lab.SetTextSize(0.04);
		if(hid<11)
		{
			lab.DrawLatex(0.66, 0.82,  Form("Sector %d", SECTOR));
			lab.DrawLatex(0.64, 0.76,  Form("segment: %d", hid+1));
			lab.SetTextColor(kRed+2);
			lab.DrawLatex(0.59, 0.68,  Form("#mu = %4.3f #pm %2.1e",    cc_match1d[s][hid]->GetFunction("MyFit")->GetParameter(4), cc_match1d[s][hid]->GetFunction("MyFit")->GetParError(4)));
			lab.DrawLatex(0.59, 0.62,  Form("#sigma = %4.3f #pm %2.1e", cc_match1d[s][hid]->GetFunction("MyFit")->GetParameter(5), cc_match1d[s][hid]->GetFunction("MyFit")->GetParError(5)));
		}
		else
		{
			lab.DrawLatex(0.26, 0.82,  Form("Sector %d", SECTOR));
			lab.DrawLatex(0.24, 0.76,  Form("segment: %d", hid+1));
			lab.SetTextColor(kRed+2);
			lab.DrawLatex(0.19, 0.68,  Form("#mu = %4.3f #pm %2.1e",    cc_match1d[s][hid]->GetFunction("MyFit")->GetParameter(4), cc_match1d[s][hid]->GetFunction("MyFit")->GetParError(4)));
			lab.DrawLatex(0.19, 0.62,  Form("#sigma = %4.3f #pm %2.1e", cc_match1d[s][hid]->GetFunction("MyFit")->GetParameter(5), cc_match1d[s][hid]->GetFunction("MyFit")->GetParError(5)));
		}
	}

	c2->Update();
	padsav->cd();
	
	if(PRINT != "") 
	{
		if(hid>=9)
			c2->Print(Form("imgs/slice-%d_cut-01ccthm_sector-%d.%s", hid+1, s+1, PRINT.c_str()) );
		else
			c2->Print(Form("imgs/slice-0%d_cut-01ccthm_sector-%d.%s", hid+1, s+1, PRINT.c_str()) );
	}

}


void show_theta_vs_segm_all_sectors()
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

		H.theta_vs_segm[1][s]->GetXaxis()->CenterTitle(0);
		H.theta_vs_segm[1][s]->GetXaxis()->SetTitle(Form("Sector %d              segment", s+1));
		H.theta_vs_segm[1][s]->GetYaxis()->SetTitle(Form("\theta on CC plane    [degrees]"));
		H.theta_vs_segm[1][s]->GetXaxis()->SetTitleSize(0.046);
		H.theta_vs_segm[1][s]->GetYaxis()->SetTitleSize(0.046);
		H.theta_vs_segm[1][s]->GetXaxis()->SetTitleOffset(1.2);
		H.theta_vs_segm[1][s]->GetYaxis()->SetTitleOffset(1.5);
		H.theta_vs_segm[1][s]->GetXaxis()->SetLabelSize(0.036);
		H.theta_vs_segm[1][s]->GetYaxis()->SetLabelSize(0.036);
		H.theta_vs_segm[1][s]->GetZaxis()->SetLabelSize(0.036);
		H.theta_vs_segm[1][s]->GetYaxis()->SetRangeUser(1, 55);
	}
	
	TCanvas *Ctheta_vs_segmA  = new TCanvas("Ctheta_vs_segmA", "Ctheta_vs_segmA", 1000, 1000);
	TPad    *Ptheta_vs_segmA  = new TPad("Ptheta_vs_segmA", "Ptheta_vs_segmA", 0.02, 0.00,  0.98, 0.92);
	Ptheta_vs_segmA->Divide(3, 2);
	Ptheta_vs_segmA->Draw();

	TPaletteAxis *palette;
	
	for(int s=0; s<6; s++)
	{
		Ptheta_vs_segmA->cd(s+1);
		gPad->SetGridx();
		gPad->SetGridy();
		gPad->SetLogz();
		H.theta_vs_segm[1][s]->Draw("colz");
		Ctheta_vs_segmA->Update();

		if(H.theta_vs_segm[1][s]->GetMaximum()>1)
		{
			palette = (TPaletteAxis*)H.theta_vs_segm[1][s]->FindObject("palette");
			palette->SetLabelSize(0.032);
			palette->SetLabelOffset(0.01);
			palette->SetX1NDC(0.89);
		}
		
		cc_match_me->SetParameter(0, s+1);
		cc_match_up->SetParameter(0, s+1);
		cc_match_up->SetParameter(1, Pars.CC_NSIGMAS[0]);
		cc_match_up->SetParameter(2, 1);
		cc_match_dn->SetParameter(0, s+1);
		cc_match_dn->SetParameter(1, Pars.CC_NSIGMAS[1]);
		cc_match_dn->SetParameter(2, -1);
	
		cc_match_up->SetLineWidth(3);
		cc_match_dn->SetLineWidth(3);
		cc_match_up->Draw("same");
		cc_match_dn->Draw("same");
		cc_match_me->Draw("same");
		
		hor->Draw("same");
	}
	
	Ctheta_vs_segmA->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.036);
	lab.DrawLatex(0.04, 0.94,  "CC #theta matching - All Sectors");
	lab.SetTextSize(0.026);
	lab.SetTextColor(kBlue+2);
	lab.DrawLatex(0.62, 0.94,  "All Other Cuts Applied");
	
	
	if(PRINT != "") 
	{
		Ctheta_vs_segmA->Print(  Form("img/cut-01ccthm_sector-all.%s", PRINT.c_str()) );
	}
	
}











