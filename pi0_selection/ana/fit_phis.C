void fit_phis(TH1F *h[4][18], double xmin, double xmax)
{
	TF1 *MyFit = new TF1("MyFit", Gauss_Para, xmin, xmax, 6);
	MyFit->SetLineColor(kRed+2);
	MyFit->SetLineWidth(2);

	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.04);
	gStyle->SetPadBottomMargin(0.15);


	TLatex lab;
	lab.SetNDC();

	TCanvas *Cdists = new TCanvas("Cdists", "Cdists", 100, 100);

	double xw[NWBINS];
	double xwe[NWBINS];
	double means[NWBINS];
	double meanse[NWBINS];
	double sigmas[NWBINS];
	double sigmase[NWBINS];

	for(int w=0; w<NWBINS; w++)
	{
		xw[w] = 1.1 + dw*w + 0.5*dw;
		xwe[w] = 0;
		cout << " Fitting w slice " << w+1 << endl;
		h[STAGE][w]->Fit("gaus", "QREM", "", xmin, xmax);
		MyFit->SetParameter(3, h[STAGE][w]->GetFunction("gaus")->GetParameter(0));
		MyFit->SetParameter(4, h[STAGE][w]->GetFunction("gaus")->GetParameter(1));
		MyFit->SetParameter(5, h[STAGE][w]->GetFunction("gaus")->GetParameter(2));
		h[STAGE][w]->Fit("MyFit", "QREM");
		means[w]   = MyFit->GetParameter(4);
		meanse[w]  = MyFit->GetParError(4);
		sigmas[w]  = fabs(MyFit->GetParameter(5));
		sigmase[w] = MyFit->GetParError(5);
	}

	Cdists->Close();
	
	string title = h[STAGE][w]->GetTitle();
	if(title.find("dphiz_") != string::npos)
	{
		dphi_means_g  = new TGraphErrors(NWBINS, xw, means,  xwe, meanse);
		dphi_sigmas_g = new TGraphErrors(NWBINS, xw, sigmas, xwe, sigmase);
	}
	if(title.find("dth1z_") != string::npos)
	{
		dth1_means_g  = new TGraphErrors(NWBINS, xw, means,  xwe, meanse);
		dth1_sigmas_g = new TGraphErrors(NWBINS, xw, sigmas, xwe, sigmase);
	}
	if(title.find("dth2z_") != string::npos)
	{
		dth2_means_g  = new TGraphErrors(NWBINS, xw, means,  xwe, meanse);
		dth2_sigmas_g = new TGraphErrors(NWBINS, xw, sigmas, xwe, sigmase);
	}
	
}











