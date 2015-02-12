void show_ecyx()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.18);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	
	TCanvas *CECpos  = new TCanvas("CECpos", "CECpos", 1000, 900);
	
	H.ECpos[0]->GetXaxis()->SetTitleSize(0.040);
	H.ECpos[0]->GetYaxis()->SetTitleSize(0.040);
	H.ECpos[0]->GetXaxis()->SetTitleOffset(1.2);
	H.ECpos[0]->GetYaxis()->SetTitleOffset(1.5);
	H.ECpos[0]->GetXaxis()->SetLabelSize(0.028);
	H.ECpos[0]->GetYaxis()->SetLabelSize(0.028);
	H.ECpos[0]->GetXaxis()->SetLabelOffset(0.007);
	H.ECpos[0]->GetZaxis()->SetMoreLogLabels();
	H.ECpos[0]->GetZaxis()->SetNdivisions(10);
	
	
	gPad->SetLogz();
	gPad->SetGridx();
	gPad->SetGridy();
	
	H.ECpos[0]->Draw("");
	H.ECpos[4]->Draw("colzsame");
	
	CECpos->Update();     // important, otherwise it won't find the palette
	TPaletteAxis *palette = (TPaletteAxis*)H.ECpos[4]->FindObject("palette");
	palette->SetLabelSize(0.028);
	palette->SetX1NDC(0.89);
	palette->Draw();
	
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(102);
	lab.SetTextSize(0.048);
	lab.DrawLatex(0.14, 0.91,  "EC Y vs X");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.028);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.46, 0.95,   Form("ec / no ec:  %3.1f%%",    100.0*hit_ec[6] / no_cc_or_ec[6]));
	lab.SetTextColor(kBlue+3);
	lab.DrawLatex(0.44, 0.91,  Form("UVW Cut / ec: %3.1f%%",    100.0*H.monitor[0][6]->GetBinContent(8)  / H.monitor[0][6]->GetBinContent(1)));
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.45, 0.87,   Form("all cuts / ec: %3.1f%%",  100.0*H.monitor[1][6]->GetBinContent(10) / H.monitor[0][6]->GetBinContent(1)));
	
	lab.SetTextSize(0.03);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.76, 0.94, "Black: no cuts");
	lab.SetTextColor(kBlue+2);
	lab.DrawLatex(0.75, 0.89, "Color: UVW cuts");

   for(int s=0; s<6; s++)
	{
		cout << "S" << s+1 << ": " << 100*H.monitor[0][s]->GetBinContent(8)  / H.monitor[0][s]->GetBinContent(1) << "%" << endl;
	}

	
	if(PRINT != "") 
	{
		CECpos->Print( Form("EC_yvsx.%s", PRINT.c_str()) );
	}
}












