void show_ecyx()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.18);
	gStyle->SetPadBottomMargin(0.14);
	
	TLatex lab;
	lab.SetNDC();
	
	TCanvas *CECpos  = new TCanvas("CECpos", "CECpos", csize, csize);
	
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
	lab.SetTextSize(0.04);
	lab.DrawLatex(0.14, 0.91,  "EC Y vs X");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(colors[0]);
	lab.DrawLatex(0.4, 0.95,   Form("all others / no cut:  %3.1f%%",        100.0*H.ECpos[1]->GetEntries() / H.ECpos[0]->GetEntries()) );
	lab.SetTextColor(kBlue+3);
	lab.DrawLatex(0.4, 0.91,   Form("negative others / no cut:  %3.1f%%",   100.0*H.ECpos[2]->GetEntries() / H.ECpos[0]->GetEntries())  );
	lab.SetTextColor(colors[3]);
	lab.DrawLatex(0.4, 0.87,   Form("U,V,W cuts / all others:  %3.1f%%",    100.0*H.ECpos[3]->GetEntries() / H.ECpos[1]->GetEntries())  );
	
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
		CECpos->Print( Form("img/cut-09uvw_sector-all.%s", PRINT.c_str()) );
	}
}












