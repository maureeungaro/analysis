void change_q2()
{
	bins Bin;
	QQ++;
	if(QQ==Bin.Q2BIN-1) QQ=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}

void change_w()
{
	bins Bin;
	WW++;
	if(WW==Bin.WMBIN) WW=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}


void change_binning()
{
	BIN++;
	if(BIN==3) BIN=0;
	cout << endl << " Binning set to " << bindex[BIN] << endl << endl;
}


void show_ctheta()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.20);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();

	TCanvas *TH = new TCanvas("TH","Theta dependence of yields", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.11,.95, Form("%s yields for W = %3.2f  Q^{2} = %3.2f", swhat.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.35,.03, Form("#leftarrow    cos(#theta*)   #rightarrow") );

	TPad *TTH   = new TPad("TTH","Theta dependence of yields", 0.01, 0.06, 0.99, 0.92);
	TTH->Draw();
	TTH->Divide(4, 6);

	for(int i=0; i<Bin.PHBIN; i++)
	{
		TTH->cd(i+1);
		MH->pi0_the[WW][QQ][i]->Draw("C");
		gPad->Update();
		double rightmax = 1.1*AH->pi0_the[WW][QQ][i][1]->GetMaximum();
		double scale = gPad->GetUymax()/rightmax;
		
		MH->pi0_the[WW][QQ][i]->Draw("C");
		MH->pi0_the[WW][QQ][i]->Draw("C");
		AH->pi0_the[WW][QQ][i][1]->Scale(scale);
		AH->pi0_the[WW][QQ][i][1]->Draw("Csame");
		
		
		//draw an axis on the right side
		TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
		axis->SetLineColor(kRed+2);
		axis->SetLabelSize(0.14);
		axis->SetNdivisions(805);
		axis->SetLabelOffset(0.03);
		axis->SetLabelColor(kRed+2);
		axis->Draw();
		
		
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.2);
		lab.SetTextColor(kBlack);
		if(i<7) lab.DrawLatex(.30,.85, Form("#phi: %3.0f#divide%2.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
		 else   lab.DrawLatex(.28,.85, Form("#phi: %3.0f#divide%3.0f", Bin.ph_center[i] - Bin.dph[i]/2.0 , Bin.ph_center[i] + Bin.dph[i]/2.0) );
	}
	
	if(PRINT != "")
		TH->Print(Form("%s_cthe_W_%3.2f_Q2_%3.2f%s", what.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}
 
void show_phi()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *PH = new TCanvas("PH","Phi dependence of yields", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.05,.95, Form("%s yields for W=%3.2f, Q^{2}=%3.2f, %s bins ", swhat.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], sbindex[BIN].c_str() ));
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.42,.03, Form("#leftarrow   #phi*  #rightarrow") );

	TPad *PPH   = new TPad("PPH","Phi dependence of yields", 0.01, 0.06, 0.99, 0.92);
	PPH->Draw();
	PPH->Divide(2, 5);

	TLegend *tbins  = new TLegend(0.77, 0.93, 1.00, 0.99);
	tbins->AddEntry(MH->pi0_phi[WW][QQ][0][BIN],    "data yields", "L");
	tbins->AddEntry(AH->pi0_phi[WW][QQ][0][1][BIN], "MC yields", "L");
	tbins->SetBorderSize(0);
	tbins->SetFillColor(0);
	tbins->Draw();
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		PPH->cd(i+1);
		MH->pi0_phi[WW][QQ][i][BIN]->Draw("C");
		gPad->Update();
		double rightmax = 1.1*AH->pi0_phi[WW][QQ][i][1][BIN]->GetMaximum();
		double scale = gPad->GetUymax()/rightmax;
		
		MH->pi0_phi[WW][QQ][i][BIN]->Draw("E1");
			
		AH->pi0_phi[WW][QQ][i][1][BIN]->Scale(scale);
		AH->pi0_phi[WW][QQ][i][1][BIN]->Draw("E1same");
		
		//draw an axis on the right side
		TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
		axis->SetLineColor(kRed+2);
		axis->SetLabelSize(0.14);
		axis->SetNdivisions(805);
		axis->SetLabelOffset(0.03);
		axis->SetLabelColor(kRed+2);
		axis->Draw();
		
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.33,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "")
		PH->Print(Form("%s_phi_%s_W_%3.2f_Q2_%3.2f%s",  what.c_str(), bindex[BIN].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}

void show_cphi()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.08);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;
	
	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *CPH = new TCanvas("CPH","Phi dependence of yields", 800, 800);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.05,.93, Form("%s corrected yields for W=%3.2f, Q^{2}=%3.2f   ", swhat.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ] ));
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.42,.03, Form("#leftarrow   #phi*  #rightarrow") );
	
	TPad *PCPH   = new TPad("PCPH","Phi dependence of yields", 0.01, 0.06, 0.99, 0.88);
	PCPH->Draw();
	PCPH->Divide(2, 5);
	TLegend *tbins  = new TLegend(0.75, 0.89, 1.00, 0.99);
	tbins->AddEntry(ANA_H->pi0_l2_phi[WW][QQ][0][0],    "24 bins", "L");
	tbins->AddEntry(ANA_H->pi0_l2_phi[WW][QQ][0][1],    "48 rebinned to 24", "L");
	tbins->AddEntry(ANA_H->pi0_l2_phi[WW][QQ][0][2],    "96 rebinned to 24", "L");
	tbins->SetBorderSize(0);
	tbins->SetFillColor(0);
	tbins->Draw();
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		PCPH->cd(i+1);
		ANA_H->pi0_l2_phi[WW][QQ][i][0]->GetYaxis()->UnZoom();
		
		ANA_H->pi0_l2_phi[WW][QQ][i][0]->Draw("E1");
		ANA_H->pi0_l2_phi[WW][QQ][i][1]->Draw("E1same");
		ANA_H->pi0_l2_phi[WW][QQ][i][2]->Draw("E1same");
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.35,.86, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "")
		CPH->Print(Form("%s_cphi_W_%3.2f_Q2_%3.2f%s",  what.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}


void show_thetaphi()
{
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.15);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetFrameFillColor(kYellow-10);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();
	
	TCanvas *TPHS = new TCanvas("TPH","Theta Phi dependence of yields", 600, 600);

	TPad *PTPHS   = new TPad("PPH","Theta dependence of yields", 0.01, 0.06, 0.99, 0.92);
	PTPHS->Draw();

	gPad->SetTheta(33);
	gPad->SetPhi(-56);

	MH->pi0[WW][QQ]->Draw("lego2FB");
	
	lab.SetTextSize(0.040);
	lab.DrawLatex(.15,.95, Form("%s yields for W = %3.2f  Q^{2} = %3.2f", swhat.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ]) );

	lab.SetTextColor(kBlack);
	lab.SetTextAngle(19);
	lab.DrawLatex(.62,.06, Form("#leftarrow   #phi*  #rightarrow") );
	lab.SetTextAngle(-38);
	lab.DrawLatex(.04,.26, Form("#leftarrow    cos(#theta*)   #rightarrow") );
	
	if(PRINT != "")
		TPHS->Print(Form("%s_thetaphi_W_%3.2f_Q2_%3.2f%s", what.c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}













void print_all_phi()
{
	bins Bin;
	PRINT=".gif";
	for(int w=0; w<Bin.WMBIN; w++)
	{
		WW=w;
		for(int q=0; q<Bin.Q2BIN-1; q++)
		{
			QQ=q;
			for(int b=0; b<3; b++)
			{
				BIN = b;
				show_phi();
			}
			show_cphi();
		}
	}
}












