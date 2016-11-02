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

void change_what()
{
	WHAT++;
	if(WHAT==2) WHAT=0;
	cout << endl << " WHAT set to " << what[WHAT] << endl << endl;
}

void change_binning()
{
	BIN++;
	if(BIN==3) BIN=0;
	cout << endl << " Binning set to " << bindex[BIN] << endl << endl;
}

void change_hoption()
{
	HOPT++;
	if(HOPT==3) HOPT=0;
	cout << endl << " Histo option set to " << oindex[HOPT] << endl << endl;
}

void show_phi()
{
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadRightMargin(0.04);
	if(WHAT == 1)
		gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC();
	
	TCanvas *PH = new TCanvas("PH","Phi dependence of correction", 1200, 1200);
	lab.SetTextSize(0.032);
	lab.DrawLatex(.04,.94, Form("%s   W=%3.2f  Q^{2}=%3.2f", what[WHAT].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.40,.03, Form("#leftarrow   #phi*  #rightarrow") );

	TPad *PPH   = new TPad("PPH","Phi dependence of correction", 0.01, 0.06, 0.99, 0.88);
	PPH->Draw();
	PPH->Divide(2, 5);

	TLegend *lbins  = new TLegend(0.76, 0.90, 1.00, 0.98);
	lbins->SetBorderSize(0);
	lbins->SetFillColor(0);
	if(WHAT==0)
	{
		lbins->AddEntry(AH->pi0_phi[WW][QQ][0][2][0], "24 bins", "L");
		lbins->AddEntry(AH->pi0_phi[WW][QQ][0][2][1], "48 bins", "L");
		lbins->AddEntry(AH->pi0_phi[WW][QQ][0][2][2], "96 bins", "L");
	}
	if(WHAT==1)
	{
		lbins->AddEntry(AH->pi0_phi[WW][QQ][0][0][BIN], "Generated", "L");
		lbins->AddEntry(AH->pi0_phi[WW][QQ][0][1][BIN], "Reconstructed", "L");
	}
	lbins->Draw();
	
	for(int i=0; i<Bin.CTBIN; i++)
	{
		PPH->cd(i+1);

		// need to update pud here... if I do it
		// withing the if statement it doesn't work.
		AH->pi0_phi[WW][QQ][i][0][BIN]->Draw("");
		gPad->Update();

		string hopt     = oindex[HOPT];
		string hoptsame = hopt + "same";

		if(WHAT ==0)
		{
			AH->pi0_phi[WW][QQ][i][2][2]->Draw(hopt.c_str());
			AH->pi0_phi[WW][QQ][i][2][1]->Draw(hoptsame.c_str());
			AH->pi0_phi[WW][QQ][i][2][0]->Draw(hoptsame.c_str());
		}
		
		if(WHAT == 1)
		{
			AH->pi0_phi[WW][QQ][i][0][BIN]->Draw("E ][");
			double rightmax = 1.1*AH->pi0_phi[WW][QQ][i][1][BIN]->GetMaximum();
			double scale = gPad->GetUymax()/rightmax;
			
			AH->pi0_phi[WW][QQ][i][1][BIN]->Scale(scale);
			AH->pi0_phi[WW][QQ][i][1][BIN]->Draw("Esame");

			//draw an axis on the right side
			TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
			axis->SetLineColor(kRed+2);
			axis->SetLabelSize(0.14);
			axis->SetNdivisions(805);
			axis->SetLabelOffset(0.03);
			axis->SetLabelColor(kRed+2);
			axis->Draw();
			
		}
		
		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.37,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );
	}
	if(PRINT != "" && WHAT==0) // acceptance
		PH->Print(Form("imga/wmass-%3.2f_q2-%3.2f_histo-%s%s", Bin.wm_center[WW], Bin.q2_center[QQ], sindex[HOPT].c_str(), PRINT.c_str()));

	if(PRINT != "" && WHAT==1) // gen/rec
		PH->Print(Form("imggr/wmass-%3.2f_q2-%3.2f_binning-%s%s", Bin.wm_center[WW], Bin.q2_center[QQ], bindex[BIN].c_str(), PRINT.c_str()));

}



void print_all()
{
	bins Bin;
	PRINT=".png";

	for(int w=0; w<Bin.WMBIN-43; w++)
	{
		WW=w;
		for(int q=0; q<Bin.Q2BIN; q++)
		{
			QQ=q;
			WHAT=1;

			// show gen/rec
			for(int b=0; b<3; b++) {
				BIN = b;
				show_phi();
			}

			// show acceptance
			WHAT=0;
			for(int b=0; b<3; b++) {
				HOPT = b;
				show_phi();
			}

		}
	}
	
}












