void show_uvwAll(TH1F* UVW[4][7])
{
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();
	
	for(int c=0; c<4; c++)
	{
		UVW[c][6]->SetBinContent(6, 0);
		UVW[c][6]->GetXaxis()->SetTitleSize(0.04);
		UVW[c][6]->GetXaxis()->SetTitleOffset(1.1);
		UVW[c][6]->GetXaxis()->SetLabelSize(0.034);
		UVW[c][6]->GetYaxis()->SetLabelSize(0.034);
	}

	// need sector by sector cause of vertical MAX of the line
	TLine *UVW_cut1;
	TLine *UVW_cut2;
	string hname = UVW[0][0]->GetName();

	if(hname.find("ECu") == 0)
	{
		UVW_cut1 = new TLine(Pars.umin, 0, Pars.umin, UVW[1][6]->GetMaximum());
		UVW_cut2 = new TLine(Pars.umax, 0, Pars.umax, UVW[1][6]->GetMaximum()/5);
		UVW_cut1->SetLineStyle(9);
		UVW_cut2->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2->SetLineWidth(2);
	}
	if(hname.find("ECv") == 0)
	{
		UVW_cut1 = new TLine(Pars.vmax, 0, Pars.vmax, UVW[1][6]->GetMaximum());
		UVW_cut1->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2 = NULL;
	}
	if(hname.find("ECw")  == 0)
	{
		UVW_cut1 = new TLine(Pars.wmax, 0, Pars.wmax, UVW[1][6]->GetMaximum());
		UVW_cut1->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2 = NULL;
	}


	TCanvas *Cuvw  = new TCanvas(Form("Cuvw%s", hname.c_str()), "Cuvw", csize, csize);
	TPad    *Puvw  = new TPad(   Form("Puvw%s", hname.c_str()), "Puvw", 0.02, 0.00,  0.98, 0.92);
	Puvw->Draw();

	
	UVW[1][6]->Draw("");
	UVW[2][6]->Draw("same");
	UVW[3][6]->Draw("same");
	UVW_cut1->Draw();
	if(UVW_cut2){
		UVW_cut2->Draw();
	}
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlue);
	if(hname.find("ECu") == 0)
	{
		lab.DrawLatex(0.5, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()) );
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.5, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][6]->GetEntries() / UVW[0][6]->GetEntries()) );
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.5, 0.73,  Form("U cut / all others:  %3.1f%%",         100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()) );
	}
	if(hname.find("ECv") == 0)
	{
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("V cut / all others:  %3.1f%%",         100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()));
	}
	if(hname.find("ECw") == 0)
	{
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][6]->GetEntries() / UVW[0][6]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("W cut / all others:  %3.1f%%",         100.0*UVW[3][6]->GetEntries() / UVW[1][6]->GetEntries()));
	}

	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.04);
	if(hname.find("ECu") == 0)
		lab.DrawLatex(0.1, 0.94,  "U coordinate in EC");
	if(hname.find("ECv") == 0)
		lab.DrawLatex(0.1, 0.94,  "V coordinate in EC");
	if(hname.find("ECw") == 0)
		lab.DrawLatex(0.1, 0.94,  "W coordinate in EC");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.025);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.65, 0.97,  "#rightarrow all other cuts applied");
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.65, 0.93,  "#rightarrow negative cuts applied");
	lab.SetTextColor(kGreen+3);
	lab.DrawLatex(0.65, 0.89,  "#rightarrow all cuts applied");
	
	if(PRINT != "") 
	{
		if(hname.find("ECu") == 0) {
			Cuvw->Print(Form("img/cut-06ECU_sector-all.%s", PRINT.c_str() ));
		}
		if(hname.find("ECv") == 0) {
			Cuvw->Print(Form("img/cut-07ECV_sector-all.%s", PRINT.c_str() ));
		}
		if(hname.find("ECw") == 0) {
			Cuvw->Print(Form("img/cut-08ECW_sector-all.%s", PRINT.c_str() ));
		}
	}

}

void show_uvw(TH1F* UVW[4][7])
{
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	int s = SECTOR -1;
	for(int c=0; c<4; c++)
	{
		UVW[c][s]->SetBinContent(6, 0);
		UVW[c][s]->GetXaxis()->SetTitleSize(0.04);
		UVW[c][s]->GetXaxis()->SetTitleOffset(1.1);
		UVW[c][s]->GetXaxis()->SetLabelSize(0.034);
		UVW[c][s]->GetYaxis()->SetLabelSize(0.034);
	}

	// need sector by sector cause of vertical MAX of the line
	TLine *UVW_cut1;
	TLine *UVW_cut2;
	string hname = UVW[0][0]->GetName();

	if(hname.find("ECu") == 0)
	{
		UVW_cut1 = new TLine(Pars.umin, 0, Pars.umin, UVW[1][s]->GetMaximum());
		UVW_cut2 = new TLine(Pars.umax, 0, Pars.umax, UVW[1][s]->GetMaximum()/5);
		UVW_cut1->SetLineStyle(9);
		UVW_cut2->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2->SetLineWidth(2);
	}
	if(hname.find("ECv") == 0)
	{
		UVW_cut1 = new TLine(Pars.vmax, 0, Pars.vmax, UVW[1][s]->GetMaximum());
		UVW_cut1->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2 = NULL;
	}
	if(hname.find("ECw")  == 0)
	{
		UVW_cut1 = new TLine(Pars.wmax, 0, Pars.wmax, UVW[1][s]->GetMaximum());
		UVW_cut1->SetLineStyle(9);
		UVW_cut1->SetLineWidth(2);
		UVW_cut2 = NULL;
	}


	TCanvas *Cuvw  = new TCanvas(Form("Cuvw%s", hname.c_str()), "Cuvw", csize, csize);
	TPad    *Puvw  = new TPad(   Form("Puvw%s", hname.c_str()), "Puvw", 0.02, 0.00,  0.98, 0.92);
	Puvw->Draw();


	UVW[1][s]->Draw("");
	UVW[2][s]->Draw("same");
	UVW[3][s]->Draw("same");
	UVW_cut1->Draw();
	if(UVW_cut2){
		UVW_cut2->Draw();
	}
	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlue);
	if(hname.find("ECu") == 0)
	{
		lab.DrawLatex(0.5, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.5, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.5, 0.73,  Form("U cut / all others:  %3.1f%%",         100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
	}
	if(hname.find("ECv") == 0)
	{
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("V cut / all others:  %3.1f%%",         100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
	}
	if(hname.find("ECw") == 0)
	{
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UVW[1][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UVW[2][s]->GetEntries() / UVW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("W cut / all others:  %3.1f%%",         100.0*UVW[3][s]->GetEntries() / UVW[1][s]->GetEntries()));
	}

	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.04);
	if(hname.find("ECu") == 0)
	lab.DrawLatex(0.1, 0.94,  "U coordinate in EC");
	if(hname.find("ECv") == 0)
	lab.DrawLatex(0.1, 0.94,  "V coordinate in EC");
	if(hname.find("ECw") == 0)
	lab.DrawLatex(0.1, 0.94,  "W coordinate in EC");

	lab.SetTextFont(42);
	lab.SetTextSize(0.025);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.65, 0.97,  "#rightarrow all other cuts applied");
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.65, 0.93,  "#rightarrow negative cuts applied");
	lab.SetTextColor(kGreen+3);
	lab.DrawLatex(0.65, 0.89,  "#rightarrow all cuts applied");

	if(PRINT != "")
	{
		if(hname.find("ECu") == 0) {
			Cuvw->Print(Form("img/cut-06ECU_sector-%d.%s", SECTOR, PRINT.c_str() ));
		}
		if(hname.find("ECv") == 0) {
			Cuvw->Print(Form("img/cut-07ECV_sector-%d.%s", SECTOR, PRINT.c_str() ));
		}
		if(hname.find("ECw") == 0) {
			Cuvw->Print(Form("img/cut-08ECW_sector-%d.%s", SECTOR, PRINT.c_str() ));
		}
	}
	
}
