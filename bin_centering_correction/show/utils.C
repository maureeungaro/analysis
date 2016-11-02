void change_q2()
{
	bins Bin;
	QQ++;
	if(QQ==Bin.Q2BIN) QQ=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}


void change_w()
{
	bins Bin;
	WW++;
	if(WW==Bin.WMBIN) WW=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}

void change_model()
{
	Model++;
	if(Model==NMODELS) Model=0;
	cout << endl << " Model set to " << models[Model] << endl << endl;
}

void show_theta()
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

	
	TCanvas *TH = new TCanvas("TH","Theta dependence of correction", 1000, 1000);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("Bin Correction  W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.36,.03, Form("#leftarrow    cos(#theta*)   #rightarrow") );

	TPad *TTH   = new TPad("TTH","Theta dependence of Bin Correction", 0.01, 0.06, 0.99, 0.86);
	TTH->Draw();
	TTH->Divide(4, 6);

	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<6; m++)
		tmodels->AddEntry(BH[m]->the_binc_cor[WW][QQ][m], BH[m]->model.c_str(), "L");

	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	for(int i=0; i<Bin.PHBIN; i++)
	{
		TTH->cd(i+1);
		double max = 0;
		for(int m=0; m<NMODELS; m++)
			if(BH[m]->the_binc_cor[WW][QQ][i]->GetMaximum() > max)
				BH[m]->the_binc_cor[WW][QQ][i]->Draw("C");

		for(int m=0; m<NMODELS; m++)
			BH[m]->the_binc_cor[WW][QQ][i]->Draw("Csame");

		lab.SetTextFont(42);
		lab.SetTextSize(0.2);
		lab.SetTextColor(kBlack);
		if(i<7) lab.DrawLatex(.30,.85, Form("#phi: %3.0f#divide%2.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
		 else   lab.DrawLatex(.28,.85, Form("#phi: %3.0f#divide%3.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
	}
	if(PRINT != "")
		TH->Print(Form("img/wbin-%3.2f_q2bin-%3.2f_plot-thetas%s", Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}
 
void show_phi()
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
	
	TCanvas *PH = new TCanvas("PH","Phi dependence of correction", 1000,1000);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.95, Form("Bin Correction   W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.44,.03, Form("#leftarrow   #phi*  #rightarrow") );

	TPad *PPH   = new TPad("PPH","Phi dependence of correction", 0.01, 0.06, 0.99, 0.86);
	PPH->Draw();
	PPH->Divide(2, 5);
	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<6; m++)
		tmodels->AddEntry(BH[m]->phi_binc_cor[WW][QQ][m], BH[m]->model.c_str(), "L");

	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();

	for(int i=0; i<Bin.CTBIN; i++)
	{
		PPH->cd(i+1);
		double max = 0;
		for(int m=0; m<NMODELS; m++)
			if(BH[m]->phi_binc_cor[WW][QQ][i]->GetMaximum() > max)
				BH[m]->phi_binc_cor[WW][QQ][i]->Draw("C");
		
		for(int m=0; m<NMODELS; m++)
			BH[m]->phi_binc_cor[WW][QQ][i]->Draw("Csame");


		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.38,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "")
		PH->Print(Form("img/wbin-%3.2f_q2bin-%3.2f_plot-phis%s", Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));

}


void show_thetaphi()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetFrameFillColor(kYellow-10);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *TPH = new TCanvas("TPH","Theta Phi dependence of correction", 1000, 1000);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.94, Form("Bin Correction W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );

	TPad *PTPH   = new TPad("PPH","Theta dependence of correction", 0.01, 0.06, 0.99, 0.92);
	PTPH->Draw();
	PTPH->Divide(2, 3);


	for(int m=0; m<NMODELS; m++)
	{
		PTPH->cd(m+1);
		gPad->SetTheta(45);
		gPad->SetPhi(50);
		BH[m]->pht_binc_cor[WW][QQ]->SetMinimum(0.6);
		BH[m]->pht_binc_cor[WW][QQ]->SetMaximum(1.2);
		BH[m]->pht_binc_cor[WW][QQ]->GetXaxis()->SetNdivisions(505);
		BH[m]->pht_binc_cor[WW][QQ]->GetYaxis()->SetNdivisions(505);
		BH[m]->pht_binc_cor[WW][QQ]->GetZaxis()->SetNdivisions(505);
		BH[m]->pht_binc_cor[WW][QQ]->GetXaxis()->SetLabelSize(0.07);
		BH[m]->pht_binc_cor[WW][QQ]->GetYaxis()->SetLabelSize(0.07);
		BH[m]->pht_binc_cor[WW][QQ]->GetZaxis()->SetLabelSize(0.07);
		BH[m]->pht_binc_cor[WW][QQ]->GetXaxis()->SetLabelOffset(0.02);
		BH[m]->pht_binc_cor[WW][QQ]->GetYaxis()->SetLabelOffset(0.03);
		BH[m]->pht_binc_cor[WW][QQ]->GetZaxis()->SetLabelOffset(0.02);
		BH[m]->pht_binc_cor[WW][QQ]->Draw("surf1FB");
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.10);
		lab.SetTextColor(kRed+2);
		lab.SetTextAngle(22);
		if(m!=3) lab.DrawLatex(.20,.72, Form("%s", models[m].c_str()) );
		else lab.DrawLatex(.10,.68, Form("%s", models[m].c_str()) );
	}
	if(PRINT != "")
		TPH->Print(Form("img/wbin-%3.2f_q2bin-%3.2f_plot-thetaphis%s", Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}

void show_thetaphi_single()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetFrameFillColor(kYellow-10);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *TPHS = new TCanvas("TPH","Theta Phi dependence of correction", 600, 600);

	TPad *PTPHS   = new TPad("PPH","Theta dependence of correction", 0.01, 0.06, 0.99, 0.92);
	PTPHS->Draw();


	gPad->SetTheta(45);
	gPad->SetPhi(50);
	BH[Model]->pht_binc_cor[WW][QQ]->SetMinimum(0.6);
	BH[Model]->pht_binc_cor[WW][QQ]->SetMaximum(1.2);
	BH[Model]->pht_binc_cor[WW][QQ]->GetXaxis()->SetNdivisions(505);
	BH[Model]->pht_binc_cor[WW][QQ]->GetYaxis()->SetNdivisions(505);
	BH[Model]->pht_binc_cor[WW][QQ]->GetZaxis()->SetNdivisions(505);
	BH[Model]->pht_binc_cor[WW][QQ]->GetXaxis()->SetLabelSize(0.04);
	BH[Model]->pht_binc_cor[WW][QQ]->GetYaxis()->SetLabelSize(0.04);
	BH[Model]->pht_binc_cor[WW][QQ]->GetZaxis()->SetLabelSize(0.04);
	BH[Model]->pht_binc_cor[WW][QQ]->GetXaxis()->SetLabelOffset(0.005);
	BH[Model]->pht_binc_cor[WW][QQ]->GetYaxis()->SetLabelOffset(0.01);
	BH[Model]->pht_binc_cor[WW][QQ]->GetZaxis()->SetLabelOffset(0.02);
	BH[Model]->pht_binc_cor[WW][QQ]->Draw("surf1FB");
		
	lab.SetTextSize(0.032);
	lab.DrawLatex(.06,.94, Form("Bin Correction  W = %3.2f  Q^{2} = %3.2f", Bin.wm_center[WW], Bin.q2_center[QQ]) );
	lab.SetTextSize(0.05);
	lab.SetTextColor(colors[Model]);
	lab.DrawLatex(.05,.05, Form("%s", models[Model].c_str()) );
	
	if(PRINT != "")
		TPHS->Print(Form("binc_cor_thetaphi_W_%3.2f_Q2_%3.2f%s%s", Bin.wm_center[WW], Bin.q2_center[QQ], models[Model].c_str(), PRINT.c_str()));
}

void print_all()
{
	bins Bin;
	PRINT=".png";
 	for(int w=0; w<Bin.WMBIN; w++)
	{
		WW=w;
		for(int q=5; q<Bin.Q2BIN; q++)
		{
			QQ=q;
			show_phi();
			show_theta();
			show_thetaphi();
		}
	}
}












