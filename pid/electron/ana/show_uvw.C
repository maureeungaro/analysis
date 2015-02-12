void show_uvw(TH1F* UVW[4][7])
{
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();
	
	for(int s=0; s<7; s++)
		for(int c=0; c<4; c++)
		{
			UVW[c][s]->SetBinContent(6, 0);
			UVW[c][s]->GetXaxis()->SetTitleSize(0.054);
			UVW[c][s]->GetXaxis()->SetTitleOffset(1.1);
			UVW[c][s]->GetXaxis()->SetLabelSize(0.044);
			UVW[c][s]->GetYaxis()->SetLabelSize(0.044);
			if(s == 6)
			{
				UVW[c][s]->GetXaxis()->SetTitleOffset(1.1);
			}
		}

	// need sector by sector cause of vertical MAX of the line
	TLine *UVW_cut1[7];	
	TLine *UVW_cut2[7];	
	string hname = UVW[0][0]->GetName();
	for(int s=0; s<7; s++)
	{
		if(hname.find("ECu") == 0)
		{
			UVW_cut1[s] = new TLine(Pars.umin, 0, Pars.umin, UVW[1][s]->GetMaximum());
			UVW_cut2[s] = new TLine(Pars.umax, 0, Pars.umax, UVW[1][s]->GetMaximum()/5);
			UVW_cut1[s]->SetLineStyle(9);
			UVW_cut2[s]->SetLineStyle(9);
			UVW_cut1[s]->SetLineWidth(2);
			UVW_cut2[s]->SetLineWidth(2);
		}
		if(hname.find("ECv") == 0)
		{
			UVW_cut1[s] = new TLine(Pars.vmax, 0, Pars.vmax, UVW[1][s]->GetMaximum());
			UVW_cut1[s]->SetLineStyle(9);
			UVW_cut1[s]->SetLineWidth(2);
			UVW_cut2[s] = NULL;
		}
		if(hname.find("ECw")  == 0)
		{
			UVW_cut1[s] = new TLine(Pars.wmax, 0, Pars.wmax, UVW[1][s]->GetMaximum());
			UVW_cut1[s]->SetLineStyle(9);
			UVW_cut1[s]->SetLineWidth(2);
			UVW_cut2[s] = NULL;
		}
	}		
	
	TCanvas *Cuvw  = new TCanvas(Form("Cuvw%s", hname.c_str()), "Cuvw", 1200, 800);
	TPad    *Puvw  = new TPad(   Form("Puvw%s", hname.c_str()), "Puvw", 0.02, 0.00,  0.98, 0.92);
	Puvw->Divide(3, 2);
	Puvw->Draw();

	
	for(int s=0; s<6; s++)
	{
		Puvw->cd(s+1);
		UVW[1][s]->Draw("");
		UVW[2][s]->Draw("same");
		UVW[3][s]->Draw("same");
		UVW_cut1[s]->Draw();
		if(UVW_cut2[s])
			UVW_cut2[s]->Draw();
		lab.SetTextColor(colors[0]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.048);
		if(hname.find("ECu") == 0)
		{
			lab.DrawLatex(0.606, 0.92,  Form("ec / no ec:  %3.1f%%",                                                   100.0*hit_ec[s] / no_cc_or_ec[s]));
			lab.DrawLatex(0.486, 0.86,  Form("%d #leq U #leq %d / ec: %3.1f%%",      (int) Pars.umin, (int) Pars.umax, 100.0*H.monitor[0][s]->GetBinContent(5)  / H.monitor[0][s]->GetBinContent(1)));
			lab.SetTextColor(colors[1]);
			lab.DrawLatex(0.592, 0.80,  Form("others / ec:  %3.1f%%",                                                  100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
			lab.SetTextColor(colors[3]);
			lab.DrawLatex(0.404, 0.74,  Form("%d #leq U #leq %d / others:  %3.1f%%", (int) Pars.umin, (int) Pars.umax, 100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
			lab.DrawLatex(0.592, 0.68,  Form("all cuts / ec: %3.1f%%",                                                 100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
		}
		if(hname.find("ECv") == 0)
		{
			lab.DrawLatex(0.266, 0.92,  Form("ec / no ec:  %3.1f%%",                          100.0*hit_ec[s] / no_cc_or_ec[s]));
			lab.DrawLatex(0.234, 0.86,  Form("V #leq %d / ec: %3.1f%%",      (int) Pars.vmax, 100.0*H.monitor[0][s]->GetBinContent(6)  / H.monitor[0][s]->GetBinContent(1)));
			lab.SetTextColor(colors[1]);
			lab.DrawLatex(0.250, 0.80,  Form("others / ec:  %3.1f%%",                         100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
			lab.SetTextColor(colors[3]);
			lab.DrawLatex(0.155, 0.74,  Form("V #leq %d / others:  %3.1f%%", (int) Pars.vmax, 100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
			lab.DrawLatex(0.248, 0.68,  Form("all cuts / ec: %3.1f%%",                        100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
		}
		if(hname.find("ECw") == 0)
		{
			lab.DrawLatex(0.278, 0.92,  Form("ec / no ec:  %3.1f%%",                          100.0*hit_ec[s] / no_cc_or_ec[s]));
			lab.DrawLatex(0.242, 0.86,  Form("W #leq %d / ec: %3.1f%%",      (int) Pars.wmax, 100.0*H.monitor[0][s]->GetBinContent(7)  / H.monitor[0][s]->GetBinContent(1)));
			lab.SetTextColor(colors[1]);
			lab.DrawLatex(0.266, 0.80,  Form("others / ec:  %3.1f%%",                         100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
			lab.SetTextColor(colors[3]);
			lab.DrawLatex(0.160, 0.74,  Form("W #leq %d / others:  %3.1f%%", (int) Pars.wmax, 100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
			lab.DrawLatex(0.267, 0.68,  Form("all cuts / ec: %3.1f%%",                        100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
		}
	}
	
	Cuvw->cd(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.044);
	if(hname.find("ECu") == 0)
		lab.DrawLatex(0.06, 0.94,  "U coordinate in EC");
	if(hname.find("ECv") == 0)
		lab.DrawLatex(0.06, 0.94,  "V coordinate in EC");
	if(hname.find("ECw") == 0)
		lab.DrawLatex(0.06, 0.94,  "W coordinates in EC");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.025);
//	lab.SetTextColor(colors[0]);
//	lab.DrawLatex(0.58, 0.97,  "#rightarrow no cuts");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.57, 0.95,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.74, 0.97,  "#rightarrow all other negative cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.74, 0.93,  "#rightarrow all cuts applied");
	
	if(PRINT != "") 
	{
		Cuvw->Print(Form("%s_each_sector.%s", hname.c_str(), PRINT.c_str() ));
	}
	
   // All sectors
	TCanvas *CAuvw  = new TCanvas(Form("CAuvw%s", hname.c_str()), "CAuvw", 800, 600);
	TPad    *PAuvw  = new TPad(   Form("PAuvw%s", hname.c_str()), "PAuvw", 0.02, 0.02,  0.98, 0.86);
	PAuvw->Draw();
	PAuvw->cd();
	
//	UVW[0][6]->Draw();
	UVW[1][6]->Draw("");
	UVW[2][6]->Draw("same");
	UVW[3][6]->Draw("same");
	UVW_cut1[6]->Draw();
	if(UVW_cut2[6])
		UVW_cut2[6]->Draw();
	
	CAuvw->cd();
	lab.SetTextFont(102);
	lab.SetTextSize(0.06);
	lab.SetTextColor(kBlack);
	if(hname.find("ECu") == 0)
		lab.DrawLatex(0.12, 0.91,  "U coordinate in EC");
	if(hname.find("ECv") == 0)
		lab.DrawLatex(0.12, 0.91,  "V coordinate in EC");
	if(hname.find("ECw") == 0)
		lab.DrawLatex(0.12, 0.91,  "W coordinates in EC");
	
	lab.SetTextSize(0.034);
	lab.SetTextFont(42);
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.65, 0.96,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.65, 0.92,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.65, 0.88,  "#rightarrow all cuts applied");
	
	PAuvw->cd();
	lab.SetTextFont(42);
	lab.SetTextSize(0.04);
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.046);
	if(hname.find("ECu") == 0)
	{
		lab.DrawLatex(0.700, 0.92,  Form("ec / no ec:  %3.1f%%",                                                   100.0*hit_ec[6] / no_cc_or_ec[6]));
		lab.DrawLatex(0.613, 0.86,  Form("%d < U < %d / ec: %3.1f%%",            (int) Pars.umin, (int) Pars.umax, 100.0*H.monitor[0][6]->GetBinContent(5)  / H.monitor[0][6]->GetBinContent(1)));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.690, 0.80,  Form("others / ec:  %3.1f%%",                                                  100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.564, 0.74,  Form("%d #leq U #leq %d / others:  %3.1f%%", (int) Pars.umin, (int) Pars.umax, 100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()));
		lab.DrawLatex(0.688, 0.68,  Form("all cuts / ec: %3.1f%%",                                                 100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	}
	if(hname.find("ECv") == 0)
	{
		lab.DrawLatex(0.230, 0.92,  Form("ec / no ec:  %3.1f%%",                          100.0*hit_ec[6] / no_cc_or_ec[6]));
		lab.DrawLatex(0.210, 0.86,  Form("V < %d / ec: %3.1f%%",         (int) Pars.vmax, 100.0*H.monitor[0][6]->GetBinContent(6)  / H.monitor[0][6]->GetBinContent(1)));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.220, 0.80,  Form("others / ec:  %3.1f%%",                         100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.156, 0.74,  Form("V #leq %d / others:  %3.1f%%", (int) Pars.vmax, 100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()));
		lab.DrawLatex(0.220, 0.68,  Form("all cuts / ec: %3.1f%%",                        100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	}
	if(hname.find("ECw") == 0)
	{
		lab.DrawLatex(0.240, 0.92,  Form("ec / no ec:  %3.1f%%",                          100.0*hit_ec[6] / no_cc_or_ec[6]));
		lab.DrawLatex(0.210, 0.86,  Form("W < %d / ec: %3.1f%%",         (int) Pars.wmax, 100.0*H.monitor[0][6]->GetBinContent(7)  / H.monitor[0][6]->GetBinContent(1)));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.232, 0.80,  Form("others / ec:  %3.1f%%",                         100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.158, 0.74,  Form("W #leq %d / others:  %3.1f%%", (int) Pars.wmax, 100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()));
		lab.DrawLatex(0.230, 0.68,  Form("all cuts / ec: %3.1f%%",                        100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	}

	
	if(PRINT != "") 
	{
		CAuvw->Print(Form("%s_all_sectors.%s", hname.c_str(), PRINT.c_str() ));
	}



}






