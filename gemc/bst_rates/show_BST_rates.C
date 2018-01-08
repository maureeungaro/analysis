void show_bst_rates()
{
	int layer = LAYER - 1;
	
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);

	TCanvas *rates  = new TCanvas("rates", "rates", 900, 650);

	gPad->SetGridx();
	gPad->SetLogy();
	bst_pr[layer][ENERGY][TARGET]->SetBinContent(2, 0.0);

	bst_pr[layer][ENERGY][TARGET]->SetFillColor(kGreen-9);
	bst_pr[layer][ENERGY][TARGET]->SetBarWidth(0.7);
	bst_pr[layer][ENERGY][TARGET]->SetBarOffset(0.15);
	if(bst_pr[layer][ENERGY][TARGET]->GetMinimum() < 200) bst_pr[layer][ENERGY][TARGET]->SetMinimum(200);
	bst_pr[layer][ENERGY][TARGET]->Draw("bar1");
	
	if(LAYER>8)
		bst_pr[layer][ENERGY][TARGET]->SetBinContent(2, 0);
	
	TH1F *a = bst_pr[layer][ENERGY][TARGET]->Clone(); 
	TH1F *b = bst_pr[layer][ENERGY][TARGET]->Clone(); 
	for(int p=1; p<pnum; p++)
	{
		a->SetBinContent(p+2, 0);
		a->SetFillColor(kRed+1);
		a->SetBarWidth(0.7);
		a->SetBarOffset(0.15);
		a->Draw("bar1same");
				
		b->SetBinContent(p+1, 0);
		b->SetFillColor(kBlue-1);
		b->SetBarWidth(0.7);
		b->SetBarOffset(0.15);
		b->Draw("bar1same");
	}	
	
	float par_slope = 0.083;
	float rat_slope = 1.00;
	
	lab.SetTextColor(kBlack);
	
	int pmin = 0;
	if(LAYER>8)
		pmin = 1;
	
	for(int p=pmin; p<pnum; p++)
	{
		lab.SetTextSize(0.045);
		lab.SetNDC(1);
		
		lab.DrawLatex(0.17+p*par_slope, 0.05, Form("%s",      pnaml[p].c_str()  ));
		
		lab.SetNDC(0);
		lab.SetTextSize(0.032);
		if( bst_pr[layer][ENERGY][TARGET]->GetBinContent(p+2)/1000000.0 > 1)
			lab.DrawLatex(1.1+p*rat_slope, bst_pr[layer][ENERGY][TARGET]->GetBinContent(p+2)*1.2,
						       Form("%3.1f MHz", bst_pr[layer][ENERGY][TARGET]->GetBinContent(p+2)/1000000.0 ));
		else
			lab.DrawLatex(1.1+p*rat_slope, bst_pr[layer][ENERGY][TARGET]->GetBinContent(p+2)*1.2,
						       Form("%3.1f KHz", bst_pr[layer][ENERGY][TARGET]->GetBinContent(p+2)/1000.0 ));
	}
	
	lab.SetTextSize(0.05);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.086, 0.915,  Form("Rates in %s     Layer: %s     %s MeV", starget[TARGET].c_str(), lname[layer].c_str(), EDEP[ENERGY].c_str()) );
	
	if(PRINT != "")
		rates->Print(Form("html/img/%s_rates_layer_%s_%s.%s", starget[TARGET].c_str(), lname[layer].c_str(), SEDEP[ENERGY].c_str(), PRINT.c_str()));
}


void show_bst_event()
{
	int layer = LAYER - 1;
	
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);

	TCanvas *rates  = new TCanvas("rates", "rates", 900, 650);

	gPad->SetGridx();
	gPad->SetLogy();
	bst_pr[layer][ENERGY][TARGET]->SetFillColor(kGreen-9);
	
	if(LAYER>8)
		bst_pr[layer][ENERGY][TARGET]->SetBinContent(2, 0);
	
	
	TH1F *a = bst_pr[layer][ENERGY][TARGET]->Clone(); 
	TH1F *b = bst_pr[layer][ENERGY][TARGET]->Clone(); 
	TH1F *c = bst_pr[layer][ENERGY][TARGET]->Clone(); 
	a->Scale(TWINDOW);
	b->Scale(TWINDOW);
	c->Scale(TWINDOW);
	if(a->GetMinimum()<0.000001) a->SetMinimum(0.000001);
	a->Draw("bar1");


	for(int p=1; p<pnum; p++)
	{
	
		b->SetBinContent(p+2, 0);
		b->SetFillColor(kRed+1);
		b->SetBarWidth(0.7);
		b->SetBarOffset(0.15);
		b->Draw("bar1same");

		c->SetBinContent(p+1, 0);
		c->SetFillColor(kBlue-1);
		c->SetBarWidth(0.7);
		c->SetBarOffset(0.15);
		c->Draw("bar1same");
		
	}	
	
	float par_slope = 0.083;
	float rat_slope = 1.00;
	
	lab.SetTextColor(kBlack);
	
	int pmin = 0;
	if(LAYER>8)
		pmin = 1;
	
	for(int p=pmin; p<pnum; p++)
	{
		lab.SetTextSize(0.045);
		lab.SetNDC(1);
		lab.DrawLatex(0.17+p*par_slope, 0.05, Form("%s",      pnaml[p].c_str()  ));
		lab.SetNDC(0);
		lab.SetTextSize(0.032);
			lab.DrawLatex(1.1+p*rat_slope, a->GetBinContent(p+2)*1.2,
						       Form("%3.1e", a->GetBinContent(p+2) ));
	}
	
	lab.SetTextSize(0.04);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.086, 0.915,  Form("Background in One Event in %s    Layer: %s     %s MeV", starget[TARGET].c_str(), lname[layer].c_str(), EDEP[ENERGY].c_str()) );
	
	if(PRINT != "")
		rates->Print(Form("html/img/%s_event_layer_%s_%s.%s", starget[TARGET].c_str(), lname[layer].c_str(), SEDEP[ENERGY].c_str(), PRINT.c_str()));
}


void show_all_bst_rates()
{
	int layer = LAYER - 1;
	
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	
	TCanvas *rates  = new TCanvas("rates", "rates", 900, 650);
	
	gPad->SetGridx();
	gPad->SetLogy();

	for(int t=0; t<NTARGET; t++)
	{
		bst_pr[layer][ENERGY][t]->SetFillColor(colors[t]);
		bst_pr[layer][ENERGY][t]->SetFillStyle(1001);
		bst_pr[layer][ENERGY][t]->SetBarWidth(0.12);
		bst_pr[layer][ENERGY][t]->SetBarOffset(0.12+0.13*t);

		if(LAYER>8)
			bst_pr[layer][ENERGY][t]->SetBinContent(2, 0);


	}

	// finding max and minimum
	double min = 10000000000;
	double max = 0;
	for(int t=0; t<NTARGET; t++)
	{
		bst_pr[layer][ENERGY][t]->GetYaxis()->UnZoom();
		if(bst_pr[layer][ENERGY][t]->GetMinimum() < min && bst_pr[layer][ENERGY][t]->GetMinimum()!=0)
			min = bst_pr[layer][ENERGY][t]->GetMinimum()+1;
		if(bst_pr[layer][ENERGY][t]->GetMaximum() > max)
			max = bst_pr[layer][ENERGY][t]->GetMaximum()*4;
	}
// 	bst_pr[layer][ENERGY][0]->SetMinimum(min);
	bst_pr[layer][ENERGY][0]->SetMaximum(max);

	bst_pr[layer][ENERGY][0]->Draw("bar1");

	for(int t=0; t<NTARGET; t++)
		bst_pr[layer][ENERGY][t]->Draw("bar1same");


	TH1F *b = bst_pr[layer][ENERGY][0]->Clone(); 

	for(int p=1; p<pnum; p++)
	{
	
		b->SetBinContent(p+2, 0);
		b->SetFillColor(kRed+1);
		b->SetBarWidth(0.8);
		b->SetBarOffset(-0.1);
	}	
	
	b->Draw("bar1same");

	
	float par_slope = 0.083;
	float rat_slope = 1.01;
	
	lab.SetTextColor(kBlack);

	int pmin = 0;
	if(LAYER>8)
		pmin = 1;
	
	for(int p=pmin; p<pnum; p++)
	{
		lab.SetTextSize(0.045);
		lab.SetNDC(1);
		lab.DrawLatex(0.17+p*par_slope, 0.05, Form("%s",      pnaml[p].c_str()  ));
		lab.SetNDC(0);
		lab.SetTextSize(0.032);
		double max_bin = 0;
		for(int t=0; t<NTARGET; t++)
		{
			if(bst_pr[layer][ENERGY][t]->GetBinContent(p+2) > max_bin)
				max_bin = bst_pr[layer][ENERGY][t]->GetBinContent(p+2);
		}
		
		if(bst_pr[layer][ENERGY][0]->GetBinContent(p+2)/1000000.0 > 1)
			lab.DrawLatex(1.1+p*rat_slope, max_bin*1.5,
									  Form("%3.1f MHz", bst_pr[layer][ENERGY][0]->GetBinContent(p+2)/1000000.0 ));
		else
			lab.DrawLatex(0.7+p*rat_slope, max_bin*1.5,
									  Form("%3.1f KHz", bst_pr[layer][ENERGY][0]->GetBinContent(p+2)/1000.0 ));
		
	}

	TLegend *tmodels  = new TLegend(0.46, 0.5, 0.94, 0.92);
	for(int t=0; t<NTARGET; t++)
		tmodels->AddEntry(bst_pr[layer][ENERGY][t], Form("%s", starget[t]),     "F");
	
	
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	lab.SetTextSize(0.06);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.086, 0.915,  Form("Rates in Layer: %s    %s MeV", lname[layer].c_str(), EDEP[ENERGY].c_str()) );
	
	if(PRINT != "")
		rates->Print(Form("html/img/targets_rates_layer_%s_%s.%s", lname[layer].c_str(), SEDEP[ENERGY].c_str(), PRINT.c_str()));
}



void show_all_bst_event()
{
	int layer = LAYER - 1;
	
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	
	TCanvas *rates  = new TCanvas("rates", "rates", 900, 650);
	
	gPad->SetGridx();
	gPad->SetLogy();

	for(int t=0; t<NTARGET; t++)
	{
		bst_pr[layer][ENERGY][t]->SetFillColor(colors[t]);
		bst_pr[layer][ENERGY][t]->SetFillStyle(1001);
		bst_pr[layer][ENERGY][t]->SetBarWidth(0.12);
		bst_pr[layer][ENERGY][t]->SetBarOffset(0.12+0.13*t);
		
		if(LAYER>8)
			bst_pr[layer][ENERGY][t]->SetBinContent(2, 0);
		
	}


	TH1F *a[NTARGET];
	for(int t=0; t<NTARGET; t++)
	{
	 a[t] = (TH1F*) bst_pr[layer][ENERGY][t]->Clone();
	 a[t]->Scale(TWINDOW);
	} 
	
	TH1F *b = bst_pr[layer][ENERGY][0]->Clone(); 
	b->Scale(TWINDOW);

	for(int p=1; p<pnum; p++)
	{
	
		b->SetBinContent(p+2, 0);
		b->SetFillColor(kRed+1);
		b->SetBarWidth(0.8);
		b->SetBarOffset(-0.1);
	}	




	// finding max and minimum
	double min = 10000000000;
	double max = 0;
	for(int t=0; t<NTARGET; t++)
	{
		a[t]->GetYaxis()->UnZoom();
		if(a[t]->GetMinimum() < min)
			min = a[t]->GetMinimum();
		if(a[t]->GetMaximum() > max)
			max = a[t]->GetMaximum()*10;
	}
	if(min==0) min=0.000001;
	
	
  a[0]->SetMinimum(min);
	a[0]->SetMaximum(max);
	a[0]->Draw("bar1");

	for(int t=0; t<NTARGET; t++)
		a[t]->Draw("bar1same");

	b->Draw("bar1same");		

	
	float par_slope = 0.083;
	float rat_slope = 1.00;
	
	lab.SetTextColor(kBlack);

	int pmin = 0;
	if(LAYER>8)
		pmin = 1;
	
	for(int p=pmin; p<pnum; p++)
	{
		lab.SetTextSize(0.045);
		lab.SetNDC(1);
		lab.DrawLatex(0.17+p*par_slope, 0.05, Form("%s",      pnaml[p].c_str()  ));
		lab.SetNDC(0);
		lab.SetTextSize(0.032);
		double max_bin = 0;
		for(int t=0; t<NTARGET; t++)
		{
			if(bst_pr[layer][ENERGY][t]->GetBinContent(p+2) > max_bin)
				max_bin = a[t]->GetBinContent(p+2);
		}
		
		if(layer < nbstl -3)
			lab.DrawLatex(1.1+p*rat_slope, max_bin*1.5, Form("%4.3f", a[0]->GetBinContent(p+2) ));
		else
			lab.DrawLatex(1.1+p*rat_slope, max_bin*1.5, Form("%6.5f", a[0]->GetBinContent(p+2) ));
		
	}

	TLegend *tmodels  = new TLegend(0.86, 0.5, 1.04, 0.72);
	for(int t=0; t<NTARGET; t++)
		tmodels->AddEntry(a[t], Form("%s", starget[t]),     "F");
	
	
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.086, 0.915,  Form("Background in one event for Layer: %s    %s MeV", lname[layer].c_str(), EDEP[ENERGY].c_str()) );
	
	if(PRINT != "")
		rates->Print(Form("html/img/targets_event_layer_%s_%s.%s", lname[layer].c_str(), SEDEP[ENERGY].c_str(), PRINT.c_str()));

}











