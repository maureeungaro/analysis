void plot_region()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.045);
	lab.SetNDC();

	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetCanvasColor(0);
	


	TCanvas *correlations  = new TCanvas("correlations", "correlations", 700, 600);
	
	
	r_cor[REGION][ENERGY][TARGET]->GetXaxis()->SetNdivisions(5);
	
	r_cor[REGION][ENERGY][TARGET]->SetMinimum(0);
	r_cor[REGION][ENERGY][TARGET]->Fit("pol0");
	
	
	lab.DrawLatex(0.18, 0.92,  Form("Double Hits in Region %d   E#\geq%s   Target: %s", REGION+1,  SEDEP[ENERGY], starget[TARGET] ));
	
	
	
	lab.DrawLatex(0.8, 0.04,  "sector");


	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.26,  "100 #times N Double Hits / NEVENTS");


	lab.SetTextAngle(0);

	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.6, 0.42,  Form("Mean: %3.1f%%", r_cor[REGION][ENERGY][TARGET]->GetFunction("pol0")->GetParameter(0)));



	correlations->Print(Form("r%d_%s_%s.gif", REGION+1, SEDEP[ENERGY], starget[TARGET]));
}

void plot_dh_region()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.042);
	lab.SetNDC();
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetCanvasColor(0);
	
	
	
	TCanvas *correlations  = new TCanvas("correlations", "correlations", 700, 600);
	
	
	d_cor[REGION][ENERGY][TARGET]->GetXaxis()->SetNdivisions(5);
	
	d_cor[REGION][ENERGY][TARGET]->SetMinimum(0);
	d_cor[REGION][ENERGY][TARGET]->Fit("pol0", "", "E");
	
	
	lab.DrawLatex(0.13, 0.92,  Form("Double Hits / Single Hits in Region %d   E#\geq%s   Target: %s", REGION+1,  SEDEP[ENERGY], starget[TARGET] ));
	
	
	
	lab.DrawLatex(0.8, 0.04,  "sector");
	
	
	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.25,  "100 #times N Double Hits / N Single Hits");
	
	
	lab.SetTextAngle(0);
	
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.6, 0.42,  Form("Mean: %3.1f%%", d_cor[REGION][ENERGY][TARGET]->GetFunction("pol0")->GetParameter(0)));
	
	
	
	correlations->Print(Form("dh_r%d_%s_%s.gif", REGION+1, SEDEP[ENERGY], starget[TARGET]));
}






void print_all()
{
	for(int c=0; c<NENERGY; c++)
		for(int r=0; r<nreg; r++)
			for(int t=0; t<NTARGET; t++)
			{
				ENERGY = c;
				REGION = r;
				TARGET = t;
				plot_region();
				plot_dh_region();
			}
}
