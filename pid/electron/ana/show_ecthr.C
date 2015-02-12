void show_ecthr()
{
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.02);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	for(int s=0; s<7; s++)
	{
		for(int c=0; c<4; c++)
		{
			H.ecthr[c][s]->GetXaxis()->SetTitleSize(0.054);
			H.ecthr[c][s]->GetXaxis()->SetTitleOffset(1.1);
			H.ecthr[c][s]->GetXaxis()->SetLabelSize(0.044);
			H.ecthr[c][s]->GetYaxis()->SetLabelSize(0.044);
			if(s == 6)
			{
				H.ecthr[c][s]->GetXaxis()->SetTitleOffset(1.1);
			}
			H.ecthr[0][s]->GetYaxis()->SetRangeUser(1, H.ecthr[0][s]->GetMaximum()*3);
		}
	}

	TLine *p_cut[7];	
	for(int s=0; s<7; s++)
	{
		p_cut[s] = new TLine(Pars.p_ec_threshold, 0, Pars.p_ec_threshold, H.ecthr[0][s]->GetMaximum());
		p_cut[s]->SetLineStyle(2);
	}
	
	TCanvas *Cecthr  = new TCanvas("Cecthr", "Cecthr", 1200, 800);
	TPad    *Pecthr  = new TPad("Pecthr", "Pecthr", 0.02, 0.00,  0.98, 0.92);
   Pecthr->Divide(3, 2);
	Pecthr->Draw();

	
	for(int s=0; s<6; s++)
	{
		Pecthr->cd(s+1);
		H.ecthr[0][s]->Draw();
		H.ecthr[1][s]->Draw("same");
		H.ecthr[2][s]->Draw("same");
		H.ecthr[3][s]->Draw("same");
		p_cut[s]->Draw();
		gPad->SetLogy();
		lab.SetTextColor(colors[0]);
		lab.SetTextFont(42);
		lab.SetTextSize(0.048);
		lab.DrawLatex(0.606, 0.92,  Form("ec / no ec:  %3.1f%%",                                    100.0*hit_ec[s] / no_cc_or_ec[s]));
		lab.DrawLatex(0.500, 0.86,  Form("ecthr #geq %3.2f / ec: %3.1f%%", Pars.p_ec_threshold,     100.0*H.monitor[0][s]->GetBinContent(3)  / H.monitor[0][s]->GetBinContent(1)));
		lab.SetTextColor(colors[1]);
		lab.DrawLatex(0.589, 0.80,  Form("others / ec:  %3.1f%%",                                   100.0*H.ecthr[1][s]->GetEntries() / H.ecthr[0][s]->GetEntries()));
		lab.SetTextColor(colors[3]);
		lab.DrawLatex(0.425, 0.74,  Form("ecthr #geq %3.2f / others: %3.1f%%", Pars.p_ec_threshold, 100.0*H.ecthr[3][s]->GetEntries() / H.ecthr[1][s]->GetEntries()));
		lab.DrawLatex(0.589, 0.68,  Form("all cuts / ec: %3.1f%%",                                  100.0*H.monitor[1][s]->GetBinContent(10) / H.monitor[0][s]->GetBinContent(1)));
	}
	
	Cecthr->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.06, 0.94,  "EC Threshold cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.026);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.50, 0.97,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.50, 0.93,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.70, 0.97,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.70, 0.93,  "#rightarrow all cuts applied");
	
   // All sectors
	TCanvas *CAecthr  = new TCanvas("CAecthr", "CAecthr", 800, 600);
	TPad    *PAecthr  = new TPad("PAecthr", "PAecthr", 0.02, 0.02,  0.98, 0.88);
	PAecthr->Draw();
	PAecthr->cd();
	gPad->SetLogy();
	H.ecthr[0][6]->Draw();
	H.ecthr[1][6]->Draw("same");
	H.ecthr[2][6]->Draw("same");
	H.ecthr[3][6]->Draw("same");
	p_cut[6]->Draw();
	
	CAecthr->cd(0);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.34, 0.93,  "EC Threshold cut");
	
	PAecthr->cd();
	lab.SetTextFont(42);
	lab.SetTextSize(0.038);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.390, 0.94,  Form("ec / no ec:  %3.1f%%",                                    100.0*hit_ec[6] / no_cc_or_ec[6] ));
	lab.DrawLatex(0.332, 0.89,  Form("ecthr #geq %3.2f / ec: %3.1f%%", Pars.p_ec_threshold,     100.0*H.monitor[0][6]->GetBinContent(3)  / H.monitor[0][6]->GetBinContent(1)));
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.382, 0.84,  Form("others / ec:  %3.1f%%",                                   100.0*H.ecthr[1][6]->GetEntries() / H.ecthr[0][6]->GetEntries()));
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.294, 0.79,  Form("ecthr #geq %3.2f / others: %3.1f%%", Pars.p_ec_threshold, 100.0*H.ecthr[3][6]->GetEntries() / H.ecthr[1][6]->GetEntries()));
	lab.DrawLatex(0.374, 0.74,  Form("all cuts / ec:  %3.1f%%",                                 100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.63, 0.94,  "#rightarrow no cuts applied");
	lab.SetTextColor(colors[1]);
	lab.DrawLatex(0.63, 0.89,  "#rightarrow all other cuts applied");
	lab.SetTextColor(colors[2]);
	lab.DrawLatex(0.63, 0.84,  "#rightarrow all negative other cuts applied");
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.63, 0.79,  "#rightarrow all cuts applied");
	
	if(PRINT != "") 
	{
		Cecthr->Print(  Form("ecthr_each_sector.%s", PRINT.c_str()) );
		CAecthr->Print( Form("ecthr_all_sectors.%s", PRINT.c_str()) );
	}
	
}






