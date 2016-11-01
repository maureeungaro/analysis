void show_cs_WQ()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.02);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	gStyle->SetPadGridX(0);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();

	TCanvas *TH = new TCanvas("TH","W dependence of CS", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.04,.92, Form("%s Cross Sections for  #phi^{*}=%3.2f  Q^{2}=%3.2f", what[WHAT].c_str(), Bin.ph_center[PH], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.42,.03, Form("#leftarrow    W   #rightarrow") );

	TPad *TTH   = new TPad("TTH","W dependence of CS", 0.01, 0.06, 0.99, 0.86);
	TTH->Draw();
	TTH->Divide(2, 5);

	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<4; m++)
		tmodels->AddEntry(tH[m]->pi0_cs_W_model[QQ][0][PH], tH[m]->model.c_str(), "L");

	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		TTH->cd(i+1);
		ANA_H->pi0_cs_W[QQ][i][PH]->GetXaxis()->SetRangeUser(1.0, 1.7);
		ANA_H->pi0_cs_W[QQ][i][PH]->Draw("E1");
		
		for(int m=0; m<4; m++)
			tH[m]->pi0_cs_W_model[QQ][i][PH]->Draw("LCsame");
		

		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.35,.86, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	
	if(PRINT != "")
		TH->Print(Form("%s_W_cs_PH_%3.2f_Q2_%3.2f%s", swhat[WHAT].c_str(), Bin.ph_center[PH], Bin.q2_center[QQ], PRINT.c_str()));
}
 






