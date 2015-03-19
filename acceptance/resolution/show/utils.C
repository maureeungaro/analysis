void change_sector()
{
	SECTOR++;
	if(SECTOR == 7) SECTOR = 1;
		
	cout << " Sector set to: " << SECTOR << endl;
}

void change_particle()
{
	WHAT++;
	if(WHAT == 2) WHAT = 0;
	
	cout << " Sector set to: " << SECTOR << endl;
}


void show_momentum()
{
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.17);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetFrameFillColor(kWhite);
	
	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC();
	
	TCanvas *PH = new TCanvas("PH","Momentum Resolution", 800, 800);

	TPad *PPH   = new TPad("PPH","Momentum Resolution", 0.01, 0.06, 0.99, 0.88);
	PPH->Draw();
	PPH->Divide(2, 3);

	
	for(int s=0; s<6; s++)
	{
		PPH->cd(s+1);

		// need to update pud here... if I do it
		// withing the if statement it doesn't work.
		mom[s][0]->Draw("");

		
		lab.SetTextFont(42);
		lab.SetTextSize(0.17);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(.37,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[i] - Bin.dct[i]/2.0 , Bin.ct_center[i] + Bin.dct[i]/2.0) );

	
	}
	if(PRINT != "")
		PH->Print(Form("momentum",  swhat[WHAT].c_str(), bindex[BIN].c_str(), Bin.wm_center[WW], Bin.q2_center[QQ], PRINT.c_str()));
}



void print_all()
{
	PRINT=".png";
}












