void show_syst_theta()
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

	
	TCanvas *THC = new TCanvas("THC","Theta dependence of correction", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("Bin Correction W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.36,.03, Form("#leftarrow    cos(#theta*)   #rightarrow") );

	TPad *TTH   = new TPad("TTH","Theta dependence of Bin Correction", 0.01, 0.06, 0.99, 0.90);
	TTH->Draw();
	TTH->Divide(4, 6);
	
	for(int i=0; i<Bin.PHBIN; i++)
	{
		TTH->cd(i+1);
		BHC->the_binc_cor[WW][QQ][i]->Draw("E1");

		lab.SetTextFont(42);
		lab.SetTextSize(0.2);
		lab.SetTextColor(kBlack);
		if(i<7) lab.DrawLatex(.30,.85, Form("#phi: %3.0f#divide%2.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
		else    lab.DrawLatex(.28,.85, Form("#phi: %3.0f#divide%3.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
	}
	if(PRINT != "")
		THC->Print(Form("binc_cor_syst_theta_W_%3.2f_Q2_%3.2f%s", Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}
 
void show_syst_phi()
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
	
	TCanvas *PHC = new TCanvas("PHC","Phi dependence of correction", 800,800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("Bin Correction  W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.44,.03, Form("#leftarrow   #phi*  #rightarrow") );

	TPad *PPH   = new TPad("PPH","Phi dependence of correction", 0.01, 0.06, 0.99, 0.90);
	PPH->Draw();
	PPH->Divide(2, 5);
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		PPH->cd(i+1);
		BHC->phi_binc_cor[WW][QQ][i]->Draw("E1");

		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.38,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "")
		PHC->Print(Form("binc_cor_syst_phi_W_%3.2f_Q2_%3.2f%s", Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}


void print_all_syst()
{
	bins Bin;
	PRINT=".gif";
	for(int w=0; w<Bin.WMBIN; w++)
	{
		WW=w;
		for(int q=0; q<Bin.Q2BIN-1; q++)
		{
			QQ=q;
			show_syst_phi();
			show_syst_theta();
		}
	}
}




