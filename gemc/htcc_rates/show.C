void showNpheRates()
{
	
	gStyle->SetPadLeftMargin(0.2);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetNDC(1);
	
	TCanvas *rates  = new TCanvas("rates1", "HTCC Rates", 1000, 1000);
	npheRates[IPHE][CONF]->Draw("");
	
	lab.SetTextSize(0.05);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.DrawLatex(0.25, 0.915, Form("Hit Rates %s", sconf[CONF].c_str() ) );
	
	lab.SetTextSize(0.04);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.25, 0.03,   "Number of Photo-Electrons in HTCC" );

	lab.DrawLatex(0.45, 0.7,   Form("nphe > 10: %5.1f KHz", npheRates[IPHE][CONF]->Integral(20, 100) ) );
	lab.DrawLatex(0.45, 0.6,   Form("nphe > 30: %5.1f KHz", npheRates[IPHE][CONF]->Integral(60, 100) ) );



	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.7,   "Rates  [KHz]" );
	
	
	if(PRINT != "") {
			rates->Print(Form("img/conf-%s.%s", sconf[CONF].c_str(), PRINT.c_str() ) );
	}
}

