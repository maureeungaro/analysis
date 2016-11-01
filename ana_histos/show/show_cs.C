void show_theta_cs()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();

	TCanvas *TH = new TCanvas("TH","Theta dependence of CS", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("%s Cross Sections for W=%3.2f  Q^{2}=%3.2f", what[WHAT].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ]) );
	lab.DrawLatex(.07,.9, "as a function of cos(#theta^{*}), in #mub/srad" );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.35,.03, Form("#leftarrow   cos(#theta*)   #rightarrow") );

	TPad *TTH   = new TPad("TTH","Theta dependence of CS", 0.01, 0.06, 0.99, 0.86);
	TTH->Draw();
	TTH->Divide(4, 6);

	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<4; m++)
		tmodels->AddEntry(tH[m]->the_model[WW][QQ][m], tH[m]->model.c_str(), "L");
	
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	for(int i=0; i<Bin.PHBIN; i++)
	{
		TTH->cd(i+1);
		ANA_H->pi0_cs_the[WW][QQ][i]->GetYaxis()->UnZoom();
		ANA_H->pi0_cs_the[WW][QQ][i]->SetMinimum(0.0001);
		if(ANA_H->pi0_cs_the[WW][QQ][i]->GetMaximum()<=0)
			ANA_H->pi0_cs_the[WW][QQ][i]->SetMaximum(1);
		ANA_H->pi0_cs_the[WW][QQ][i]->Draw("E1");
		
		for(int m=0; m<4; m++)
			tH[m]->the_model[WW][QQ][i]->Draw("LCsame");

		lab.SetTextFont(42);
		lab.SetTextSize(0.2);
		lab.SetTextColor(kBlack);
		if(i<7) lab.DrawLatex(.30,.85, Form("#phi: %3.0f#divide%2.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
		 else   lab.DrawLatex(.28,.85, Form("#phi: %3.0f#divide%3.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
	}
	if(PRINT != "")
		TH->Print(Form("%s_the_cs_W_%3.2f_Q2_%3.2f%s", swhat[WHAT].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}
 
void show_phi_cs()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *PH = new TCanvas("PH","Phi dependence of CS", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("%s Cross Sections for W=%3.2f  Q^{2}=%3.2f", what[WHAT].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ]) );
	lab.DrawLatex(.1,.9, "as a function of #phi^{*}, in #mub/srad" );
	
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.44,.03, Form("#leftarrow   #phi*  #rightarrow") );

	TPad *PPH   = new TPad("PPH","Phi dependence of CS", 0.01, 0.06, 0.99, 0.86);
	PPH->Draw();
	PPH->Divide(2, 5);
	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<4; m++)
		tmodels->AddEntry(tH[m]->phi_model[WW][QQ][m], tH[m]->model.c_str(), "L");
	
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		PPH->cd(i+1);
		if(WHAT == 0)
		{
			ANA_H->pi0_cs_phi[WW][QQ][i]->GetYaxis()->UnZoom();
			ANA_H->pi0_cs_phi[WW][QQ][i]->SetMinimum(0.0001);
			ANA_H->pi0_cs_phi[WW][QQ][i]->Draw("E1");

			for(int m=0; m<4; m++)
				tH[m]->phi_model[WW][QQ][i]->Draw("LCsame");

			lab.SetTextFont(42);
			lab.SetTextSize(0.16);
			lab.SetTextColor(kBlue+3);
/*			double chi2 = 0;
			double  ndf = 1;
			if(ANA_H->pi0_cs_phi[WW][QQ][i]->GetFunction("phifit"))
			{
				chi2 = ANA_H->pi0_cs_phi[WW][QQ][i]->GetFunction("phifit")->GetChisquare();
				ndf  = ANA_H->pi0_cs_phi[WW][QQ][i]->GetFunction("phifit")->GetNumberFitPoints() - 3;
			}
			if(ndf==0) ndf=1;
			lab.DrawLatex(.65,.83, Form("#chi^{2}/ndf. = %3.2f", chi2/ndf ));*/
		}
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.15,.83, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "")
		PH->Print(Form("%s_phi_cs_W_%3.2f_Q2_%3.2f%s",  swhat[WHAT].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}










