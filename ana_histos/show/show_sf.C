void show_sf(int which)
{

	string sigma[3]  = {"#sigma_{L}+#epsilon#sigma_{T}", "#sigma_{TT}", "#sigma_{LT}"};
	string ssigma[3] = {"LPT", "TT", "LT"};
	
	gStyle->SetPadLeftMargin(0.13);
	gStyle->SetPadRightMargin(0.0);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);

	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);

	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();

	TCanvas *TH = new TCanvas("TH","Theta dependence of SF", 1000, 1200);

	lab.SetTextSize(0.045);
	lab.DrawLatex(.1,.92, Form("%s %s for Q^{2} = %3.2f", what[WHAT].c_str(), sigma[which].c_str(), Bin.q2_center[QQ]) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(.30,.02, Form("#leftarrow    cos(#theta*)   #rightarrow") );

	TPad *TTH   = new TPad("TTH","Theta dependence of SF", 0.01, 0.06, 0.99, 0.86);
	TTH->Draw();
	TTH->Divide(5, 9);


	double min_limits[3][7];
	double max_limits[3][7];

	// LPT
	min_limits[0][0] = -0.1; max_limits[0][0] = 1.5;
	min_limits[0][1] = -0.1; max_limits[0][1] = 1.8;
	min_limits[0][2] = -0.1; max_limits[0][2] = 1.2;
	min_limits[0][3] = -0.1; max_limits[0][3] = 0.7;
	min_limits[0][4] = -0.1; max_limits[0][4] = 0.4;
	min_limits[0][5] = -0.1; max_limits[0][5] = 0.4;
	min_limits[0][6] = -0.1; max_limits[0][6] = 0.4;
	
	// TT
	min_limits[1][0] = -1.0; max_limits[1][0] = 1.0;
	min_limits[1][1] = -1.0; max_limits[1][1] = 1.0;
	min_limits[1][2] = -1.0; max_limits[1][2] = 1.0;
	min_limits[1][3] = -0.5; max_limits[1][3] = 0.5;
	min_limits[1][4] = -0.4; max_limits[1][4] = 0.4;
	min_limits[1][5] = -0.3; max_limits[1][5] = 0.3;
	min_limits[1][6] = -0.3; max_limits[1][6] = 0.3;


	// LT
	min_limits[2][0] = -0.5; max_limits[2][0] = 0.5;
	min_limits[2][1] = -0.5; max_limits[2][1] = 0.5;
	min_limits[2][2] = -0.5; max_limits[2][2] = 0.5;
	min_limits[2][3] = -0.3; max_limits[2][3] = 0.3;
	min_limits[2][4] = -0.3; max_limits[2][4] = 0.3;
	min_limits[2][5] = -0.2; max_limits[2][5] = 0.2;
	min_limits[2][6] = -0.3; max_limits[2][6] = 0.3;
	
	TLegend *tmodels  = new TLegend(0.74, 0.88, 1.00, 0.99);
	for(int m=0; m<4; m++)
		tmodels->AddEntry(tH[m]->pi0_sf_model[0][QQ][which], tH[m]->model.c_str(), "L");
	
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();


	for(int i=0; i<Bin.WMBIN; i++)
	{
		TTH->cd(i+1);
		if(WHAT == 0)
		{
			ANA_H->pi0_sf[i][QQ][which]->SetMinimum(min_limits[which][QQ]);
			ANA_H->pi0_sf[i][QQ][which]->SetMaximum(max_limits[which][QQ]);
			if(i==1 || i==2) ANA_H->pi0_sf[i][QQ][which]->SetMaximum(2*max_limits[which][QQ]);
			if(i==0) ANA_H->pi0_sf[i][QQ][which]->SetMaximum(3*max_limits[which][QQ]);
			ANA_H->pi0_sf[i][QQ][which]->Draw("E1");

			for(int m=0; m<4; m++)
				tH[m]->pi0_sf_model[i][QQ][which]->Draw("LCsame");
			
		}
			
		lab.SetTextFont(42);
		lab.SetTextSize(0.21);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.38,.8, Form("W: %3.2f", Bin.wm_center[i] ) );
	}
	if(PRINT != "")
		TH->Print(Form("imgsf/q2-%3.2f_sf-%s_runningvar-ctheta%s", Bin.q2_center[QQ],  ssigma[which].c_str(), PRINT.c_str()));
}
 
