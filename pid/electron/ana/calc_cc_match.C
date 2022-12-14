



double cc_match_Mean(double *x, double *par)
{ 
	// par[0] is sector
	int s = (int) par[0] - 1;
	
	return Pars.cc_match_mean_a[s] +
			 Pars.cc_match_mean_b[s]*x[0] +
			 Pars.cc_match_mean_c[s]*x[0]*x[0];
}

double cc_match_Mean2(double *x, double *par)
{
	// par[0] is sector
	int s = (int) par[0] - 1;
	
	// we want lower limit to be constant in each segment 
	double segment = floor(x[0]);
	
	return Pars.cc_match_mean_a[s] +
			Pars.cc_match_mean_b[s]*segment +
			Pars.cc_match_mean_c[s]*segment*segment;
}

double cc_match_Sigma(double *x, double *par)
{
	// par[0] is sector
	int s = (int) par[0] - 1;
	
	// segment index
	int segment = (int) floor(x[0]) - 1;
	
	return Pars.cc_match_low[s][segment];
}

double cc_match_limit(double *x, double *par)
{ 
	// par[0] is sector
	int s = (int) par[0] - 1;
	
	// par[1] is # of sigmas
	double nsigmas = par[1];
	
	// par[2] is which limit (upper or lower)
	if(par[2] >= 0) return cc_match_Mean2(x, par) + nsigmas*cc_match_Sigma(x, par);
	else            return cc_match_Mean2(x, par) - nsigmas*cc_match_Sigma(x, par);
}


void calc_cc_match()
{
	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.14);
		
	TLatex lab;
	lab.SetNDC();
	
	TCanvas *Ccc_match  = new TCanvas("Ccc_match", "Ccc_match", 800, 800);
	
	TF1 *MyFit = new TF1("MyFit", gauss2_para, -100, 800, 6);
	MyFit->SetLineColor(kRed+2);
	MyFit->SetLineWidth(1);
	
	int s = SECTOR - 1;
	double xb[18], xbe[18];
	for(int b=0; b<18; b++)
	{
		xb[b]  = b+1.5;
		xbe[b] = 0;
	}
	
	// Slicing + fitting
	cout << " Fitting sector " << s+1 << endl;
	for(int b=0; b<18; b++)
	{
		cout << " Fitting pmt " << b+1 << endl;
		H.theta_vs_segm[1][s]->ProjectionY(Form("cc_match1d_s%d_pmt%d", s+1, b+1), b+2, b+3);
		cc_match1d[s][b] = (TH1F*)gROOT->Get(Form("cc_match1d_s%d_pmt%d", s+1, b+1));
		
		// Gaussian fit
		cc_match1d[s][b]->Fit("gaus", "QEM");
		
		double max   = cc_match1d[s][b]->GetBinCenter( cc_match1d[s][b]->GetMaximumBin() );
		double sigma = cc_match1d[s][b]->GetFunction("gaus")->GetParameter(2);
		if(sigma > 2) sigma = 2;
		double xmin =  max - 4*sigma;
		double xmax =  max + 4*sigma;

		if(b == 16)
		{
			xmin = 40;
			xmax = 50;
		}
		if(b == 17)
		{
			xmin = 43;
			xmax = 50;
		}
		
		MyFit->SetParameter(3, cc_match1d[s][b]->GetFunction("gaus")->GetParameter(0));
		MyFit->SetParameter(4, max);
		MyFit->SetParLimits(4, max-5, max+10);
		MyFit->SetParameter(5, 3);
		MyFit->SetParLimits(5, 0.6, 10);
		
		// cc_match1d[s][b]->Fit("MyFit", "QEM");
		cc_match1d[s][b]->Fit("MyFit", "QREM", "", xmin, xmax);
		cc_matchmean[s][b]  = MyFit->GetParameter(4);
		cc_matchsigm[s][b]  = MyFit->GetParameter(5);
		cc_matchmeane[s][b] = MyFit->GetParError(4);
		cc_matchsigme[s][b] = MyFit->GetParError(5);
		Pars.cc_match_low[s][b]  = cc_matchsigm[s][b];
	}
	cout << " done " << endl;
	// Now creating / fitting the graphs
	cc_match_mean[s] = new TGraphErrors(18, xb, cc_matchmean[s], xbe, cc_matchmeane[s]);
	cc_match_sigm[s] = new TGraphErrors(18, xb, cc_matchsigm[s], xbe, cc_matchsigme[s]);
		
	
	// will miss the first and last 2 pmts.
	cc_match_mean[s]->Fit("pol2", "REM", "", 1, 20);
		
	Pars.cc_match_mean_a[s] = cc_match_mean[s]->GetFunction("pol2")->GetParameter(0);
	Pars.cc_match_mean_b[s] = cc_match_mean[s]->GetFunction("pol2")->GetParameter(1);
	Pars.cc_match_mean_c[s] = cc_match_mean[s]->GetFunction("pol2")->GetParameter(2);
	
	cc_match_mean[s]->GetFunction("pol2")->SetLineColor(kRed+2);
	cc_match_mean[s]->GetFunction("pol2")->SetLineWidth(2);
	cc_match_mean[s]->GetFunction("pol2")->SetLineStyle(2);
	cc_match_mean[s]->SetMarkerStyle(20);
	cc_match_mean[s]->SetMarkerSize(0.9);


	cc_match_mean[s]->GetXaxis()->SetTitle("Segment");
	cc_match_mean[s]->GetYaxis()->SetTitle("#theta on CC plane");
	cc_match_sigm[s]->GetXaxis()->SetTitle("Segment");
	cc_match_sigm[s]->GetYaxis()->SetTitle("#Delta#theta on CC plane");
	
	cc_match_mean[s]->GetXaxis()->SetLabelSize(0.05);
	cc_match_mean[s]->GetYaxis()->SetLabelSize(0.05);
	cc_match_sigm[s]->GetXaxis()->SetLabelSize(0.05);
	cc_match_sigm[s]->GetYaxis()->SetLabelSize(0.05);

	cc_match_mean[s]->GetXaxis()->SetTitleSize(0.06);
	cc_match_mean[s]->GetYaxis()->SetTitleSize(0.06);
	cc_match_mean[s]->GetXaxis()->SetTitleOffset(1.1);
	cc_match_mean[s]->GetYaxis()->SetTitleOffset(0.7);
	cc_match_sigm[s]->GetXaxis()->SetTitleSize(0.06);
	cc_match_sigm[s]->GetYaxis()->SetTitleSize(0.06);
	cc_match_sigm[s]->GetXaxis()->SetTitleOffset(1.1);
	cc_match_sigm[s]->GetYaxis()->SetTitleOffset(0.7);

	TCanvas *Csum  = new TCanvas("Csum", "Csum", 800, 800);
	TPad    *Psum  = new TPad("Psum", "Psum", 0.02, 0.02,  0.98, 0.92);
	Psum->Divide(1, 2);
	Psum->Draw();

	lab.SetTextFont(42);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.07);
	Psum->cd(1);
	cc_match_mean[s]->Draw("AP");
	
	lab.DrawLatex(0.20, 0.75,  "Mean:");
	lab.DrawLatex(0.20, 0.65,  "#mu = a + bx + cx^{2}");
	lab.DrawLatex(0.70, 0.45,  Form("a = %3.2f", Pars.cc_match_mean_a[s]));
	lab.DrawLatex(0.70, 0.35,  Form("b = %3.2f", Pars.cc_match_mean_b[s]));
	lab.DrawLatex(0.70, 0.25,  Form("c = %3.2f", Pars.cc_match_mean_c[s]));

	Psum->cd(2);
	cc_match_sigm[s]->SetFillColor(kPink-2);
	cc_match_sigm[s]->Draw("AB");
	lab.DrawLatex(0.20, 0.75,  "Sigma:");
	lab.DrawLatex(0.20, 0.65,  "#sigma = #sigma(segment)");

	Csum->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.038);
	lab.DrawLatex(0.18, 0.94,  Form("CC #theta Matching Pars  -  Sector %d", SECTOR));


	if(PRINT != "")
	{
		Csum->Print( Form("img/cut-01cctmpars_sector-%d.%s", s+1, PRINT.c_str()) );
	}
	
	cout << " done " << endl;
	Ccc_match->Close();
}


void calc_all_cc_match()
{
	for(int s=0; s<6; s++)
	{
		SECTOR = s+1;
		calc_cc_match();
	}
	SECTOR = 1;
}


















