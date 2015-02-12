void show_EinEtot()
{

	int s = SECTOR - 1;

	TF1 *EinEtot_cut = new TF1("up", "pol0", 0, 5);
	EinEtot_cut->SetLineColor(kGreen+3);
	EinEtot_cut->SetLineWidth(2);

	EinEtot_cut->SetParameter(0, Pars.min_ecit[s]);

	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);

	TLatex lab;
	lab.SetNDC();
	
	for(int c=0; c<4; c++)
	{
		H.EinEtot[c][s]->GetXaxis()->SetTitleSize(0.052);
		H.EinEtot[c][s]->GetXaxis()->SetTitleOffset(1.14);
		H.EinEtot[c][s]->GetYaxis()->SetTitleSize(0.054);
		H.EinEtot[c][s]->GetYaxis()->SetTitleOffset(1.32);
		H.EinEtot[c][s]->GetXaxis()->SetLabelSize(0.042);
		H.EinEtot[c][s]->GetYaxis()->SetLabelSize(0.042);
		H.EinEtot[c][s]->GetZaxis()->SetNdivisions(8);
		if(s == 6)
		{
			H.EinEtot[c][s]->GetXaxis()->SetTitleOffset(1.1);
		}
		// Max is at Eout=0
		// Renormalizing
		H.EinEtot[c][s]->GetYaxis()->SetRangeUser(0.01, 0.97);
		double hmax = H.EinEtot[c][s]->GetMaximum();
		H.EinEtot[c][s]->GetYaxis()->SetRangeUser(0.0, 1.2);
		H.EinEtot[c][s]->SetMaximum(hmax);
		
	}
	
	TCanvas *CEinEtotS;
	TPad    *PEinEtotS;
	
	CEinEtotS = new TCanvas(Form("CEinEtotS%d", s+1), Form("CEinEtotS%d", s+1), 940, 900);
	PEinEtotS = new TPad(Form("PEinEtotS%d", s+1), Form("PEinEtotS%d", s+1), 0.02, 0.00,  0.98, 0.90);
	PEinEtotS->Divide(2, 2);
	PEinEtotS->Draw();
	
	
	TPaletteAxis *palette;
	for(int c=0; c<4; c++)
	{
		PEinEtotS->cd(c+1);
		H.EinEtot[c][s]->Draw("colz");
		EinEtot_cut->Draw("same");
		CEinEtotS->Update();
		if(H.EinEtot[c][s]->GetMaximum()>2)
		{
			palette = (TPaletteAxis*)H.EinEtot[c][s]->FindObject("palette");
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
			lab.DrawLatex(0.51, 0.91,  "a. no cuts applied");
		}
		if(c==1)
		{
			lab.DrawLatex(0.41, 0.91,  "b. all other cuts applied");
			lab.DrawLatex(0.45, 0.85,  Form("entries b. / a. : %3.1f%%", 100.0*H.EinEtot[c][s]->GetEntries()/H.EinEtot[0][s]->GetEntries()));
		}
		if(c==2) 
		{
			lab.DrawLatex(0.24, 0.91,  "c. all other negative cuts applied");
			lab.DrawLatex(0.46, 0.85,  Form("entries c. / a. : %3.1f%%", 100.0*H.EinEtot[c][s]->GetEntries()/H.EinEtot[0][s]->GetEntries()));
		}
		if(c==3) 
		{
			lab.DrawLatex(0.52, 0.91,  "d. all cuts applied");
			lab.DrawLatex(0.46, 0.86,  Form("entries d. / a. : %3.1f%%", 100.0*H.EinEtot[c][s]->GetEntries()/H.EinEtot[0][s]->GetEntries()));
			lab.DrawLatex(0.46, 0.81,  Form("entries d. / b. : %3.1f%%", 100.0*H.EinEtot[c][s]->GetEntries()/H.EinEtot[1][s]->GetEntries()));
		}
		
	}
	
	CEinEtotS->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.034);
	lab.DrawLatex(0.08, 0.95,  Form("Shower Shape Cut  -  Sector %d", SECTOR));

	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(kGreen+3);
	lab.DrawLatex(0.70, 0.95,  Form("CUT:  E_{in} / E_{TOT} > %3.2f ", Pars.min_ecit[s]));
	
	
	if(PRINT != "") 
	{
		CEinEtotS->Print(Form("einetot_sect%d.%s", s+1, PRINT.c_str()));
	}








}





