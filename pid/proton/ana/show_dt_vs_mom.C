void show_dt_vs_mom()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.16);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	
	int s = SECTOR - 1;
	int NBINS = H.dt_momz[s]->GetNbinsX();
	int db = NBINS/NDIV;
	
	TCanvas *Cecp  = new TCanvas("Cecp", "Cecp", 1000, 1000);
	
	// Changing titles
	H.dt_momz[s]->GetXaxis()->CenterTitle(0);
	H.dt_momz[s]->GetXaxis()->SetTitle(Form("Sector %d                            p [GeV]", SECTOR));
	H.dt_momz[s]->GetYaxis()->SetTitle("#Delta T     [ns]");
	H.dt_momz[s]->GetXaxis()->SetTitleSize(0.042);
	H.dt_momz[s]->GetYaxis()->SetTitleSize(0.046);
	H.dt_momz[s]->GetXaxis()->SetTitleOffset(1.3);
	H.dt_momz[s]->GetYaxis()->SetTitleOffset(0.9);
	H.dt_momz[s]->GetXaxis()->SetLabelSize(0.034);
	H.dt_momz[s]->GetYaxis()->SetLabelSize(0.034);
	H.dt_momz[s]->GetZaxis()->SetLabelSize(0.034);
	H.dt_momz[s]->GetXaxis()->SetRangeUser(0.0, 4.5);

	gPad->SetLogz();
	H.dt_momz[s]->Draw("colz");
	
	Cecp->Update();     // important, otherwise it won't find the palette
	TPaletteAxis *palette = (TPaletteAxis*)H.dt_momz[s]->FindObject("palette");
	palette->SetLabelSize(0.032);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.85);
	palette->SetX2NDC(0.89);
	palette->SetY2NDC(0.88);
	
	if(dt_mean[s])
	{
		dt_mean[s]->GetFunction("pol5")->SetLineColor(kRed+2);
		dt_mean[s]->GetFunction("pol5")->SetLineWidth(1);
		dt_mean[s]->GetFunction("pol5")->SetLineStyle(2);
		dt_mean[s]->SetMarkerStyle(20);
		dt_mean[s]->SetMarkerSize(0.8);
		dt_mean[s]->Draw("P");
	}
	
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
	dt_up->Draw("same");
	dt_dn->Draw("same");
	dt_me->Draw("same");
	
	lab.SetTextColor(kBlack);
	lab.SetTextFont(102);
	lab.SetTextSize(0.052);
	lab.DrawLatex(0.19, 0.94,  "#Delta T vs p");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.029);
	lab.SetTextColor(kRed+2);
	lab.DrawLatex(0.5, 0.96,  Form("Upper Limit: larger between (#mu_{P}+ 3 #sigma) and (#mu_{#pi} - 3 #sigma)", Pars.NSIGMAS[0]));
	lab.DrawLatex(0.5, 0.91,  Form("Lower Limit: smaller #mu - %3.2f #sigma", Pars.NSIGMAS[1]));
	
	if(PRINT != "") 
	{
		Cecp->Print(Form("img/dist-dtfit_sector-%d.%s", s+1, PRINT.c_str()));
	}
	
	if(dt_mean[s])
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
	int px    = gPad->GetEventX();
	int py    = gPad->GetEventY();
	
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
	double dp   = (H.dt_momz[s]->GetXaxis()->GetXmax() - H.dt_momz[s]->GetXaxis()->GetXmin())/NDIV;
	int hid  = floor((x - H.dt_momz[s]->GetXaxis()->GetXmin())/dp);
	
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
	double dp   = (H.dt_momz[s]->GetXaxis()->GetXmax() - H.dt_momz[s]->GetXaxis()->GetXmin())/NDIV;

   // create or set the new canvas c2
	TVirtualPad *padsav = gPad;
	TCanvas *c2 = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("c2");
	if(c2) delete c2->GetPrimitive("Projection");
	else   c2 = new TCanvas("c2","Projection Canvas",710,10,800,800);
	c2->cd();
	
	if(dt_1d[s][hid])
	{
		double pmin = H.dt_momz[s]->GetXaxis()->GetXmin() + hid*dp;
		double pmax = H.dt_momz[s]->GetXaxis()->GetXmin() + (hid+1)*dp;
		dt_1d[s][hid]->GetXaxis()->SetTitleOffset(1.3);
		dt_1d[s][hid]->Draw();
		lab.SetTextFont(102);
		lab.SetTextSize(0.058);
		lab.DrawLatex(0.36, 0.92,  "Delta T");
		lab.SetTextFont(42);
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.66, 0.82,  Form("Sector %d", SECTOR));
		lab.DrawLatex(0.60, 0.76,  Form("p = %3.1f - %3.1f GeV", pmin, pmax ));
		lab.SetTextColor(kRed+2);
		lab.DrawLatex(0.59, 0.68,  Form("#mu = %4.3f #pm %2.1e",    dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(4), dt_1d[s][hid]->GetFunction("MyFit")->GetParError(4)));
		lab.DrawLatex(0.59, 0.62,  Form("#sigma = %4.3f #pm %2.1e", dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(5), dt_1d[s][hid]->GetFunction("MyFit")->GetParError(5)));
	
		// Drawing signal + background
		MySignal[s][hid]->SetParameter(0, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(3));
		MySignal[s][hid]->SetParameter(1, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(4));
		MySignal[s][hid]->SetParameter(2, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(5));
		MySignal[s][hid]->Draw("same");
			
		MyBackground[s][hid]->SetParameter(0, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(0));
		MyBackground[s][hid]->SetParameter(1, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(1));
		MyBackground[s][hid]->SetParameter(2, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(2));
		MyBackground[s][hid]->SetParameter(3, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(6));
		MyBackground[s][hid]->SetParameter(4, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(7));
		MyBackground[s][hid]->SetParameter(5, dt_1d[s][hid]->GetFunction("MyFit")->GetParameter(8));
		MyBackground[s][hid]->Draw("same");
	}

	c2->Update();
	padsav->cd();
	
	if(PRINT != "") 
	{
		c2->Print(Form("imgs/slice-%d_sector-%d.%s", hid+1, s+1, PRINT.c_str()) );
	}

}


void show_dt_vs_moms()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.04);
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
	hor->SetParameter(0, 0.0);

	
	for(int s=0; s<6; s++)
	{
		// Changing titles
		H.dt_momz[s]->GetXaxis()->CenterTitle(0);
		H.dt_momz[s]->GetXaxis()->SetTitle(Form("Sector %d             p [GeV]", s+1));
		H.dt_momz[s]->GetYaxis()->SetTitle("#Delta T     [ns]");
		H.dt_momz[s]->GetXaxis()->SetTitleSize(0.050);
		H.dt_momz[s]->GetYaxis()->SetTitleSize(0.050);
		H.dt_momz[s]->GetXaxis()->SetTitleOffset(1.1);
		H.dt_momz[s]->GetYaxis()->SetTitleOffset(1.2);
		H.dt_momz[s]->GetXaxis()->SetLabelSize(0.042);
		H.dt_momz[s]->GetXaxis()->SetLabelOffset(0.008);
		H.dt_momz[s]->GetYaxis()->SetLabelOffset(0.009);
		H.dt_momz[s]->GetYaxis()->SetLabelSize(0.042);
		H.dt_momz[s]->GetZaxis()->SetLabelSize(0.042);
		H.dt_momz[s]->GetXaxis()->SetRangeUser(0.0, 4.5);
	}

	
	TCanvas *CecpA  = new TCanvas("CecpA", "CecpA", 1000, 1000);
	TPad    *PecpA  = new TPad("PecpA", "PecpA", 0.02, 0.00,  0.98, 0.92);
	PecpA->Divide(3, 2);
	PecpA->Draw();

	TPaletteAxis *palette;
	dt_me->SetLineWidth(2);
	dt_me->SetLineStyle(8);
	dt_me->SetLineColor(kRed+3);
		
	dt_up->SetLineWidth(2);
	dt_up->SetLineStyle(9);
	dt_up->SetLineColor(kRed+3);
		
	dt_dn->SetLineWidth(2);
	dt_dn->SetLineStyle(9);
	dt_dn->SetLineColor(kRed+3);
	
	for(int s=0; s<6; s++)
	{
		PecpA->cd(s+1);
		gPad->SetGridx();
		gPad->SetGridy();
		gPad->SetLogz();
		H.dt_momz[s]->Draw("colz");
		CecpA->Update();
		
		palette = (TPaletteAxis*)H.dt_momz[s]->FindObject("palette");
		palette->SetLabelSize(0.042);
		palette->SetLabelOffset(0.01);
		palette->SetX1NDC(0.89);
		
	
		dt_up->SetParameter(0, s+1);
		dt_up->SetParameter(1, Pars.NSIGMAS[0]);
		dt_up->SetParameter(2, 1);
		dt_dn->SetParameter(0, s+1);
		dt_dn->SetParameter(1, Pars.NSIGMAS[1]);
		dt_dn->SetParameter(2, -1);
	
		dt_me->SetParameter(0, s+1);
		
		
		dt_up->Draw("same");
		dt_dn->Draw("same");
		dt_me->Draw("same");
		
		hor->Draw("same");
	}
	
	CecpA->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.044);
	lab.DrawLatex(0.32, 0.95,  "#Delta T vs p - All Sectors");
	
	if(PRINT != "") 
	{
		CecpA->Print(  Form("img/dist-dtfit_sector-all.%s", PRINT.c_str()) );
	}
}
















