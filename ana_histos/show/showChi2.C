void show_chi2(int whichFunction)
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetFrameFillColor(kWhite);

	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);

	bins Bin;

	TLatex lab;
	lab.SetTextFont(102);
	lab.SetTextColor(kBlue+2);
	lab.SetNDC();

	TCanvas *TH = new TCanvas("CH","Chi2", 1000, 1000);


	lab.SetTextColor(kBlack);
	lab.DrawLatex(.35,.03, Form("#chi^2 distributions") );

	TPad *TTH   = new TPad("TTH","W dependence of SF", 0.01, 0.06, 0.99, 0.86);
	TTH->Draw();
	TTH->Divide(2, 3);


	for(int q=0; q<Bin.Q2BIN; q++)
	{
		TTH->cd(q+1);

		ANA_H->chi2s_ctr[q]->Draw("");
		
		ANA_H->chi2s_ctr[q]->GetXaxis()->SetNdivisions(508);
		ANA_H->chi2s_ctr[q]->GetYaxis()->SetNdivisions(805);
		ANA_H->chi2s_ctr[q]->GetXaxis()->SetLabelSize(0.12);
		ANA_H->chi2s_ctr[q]->GetYaxis()->SetLabelSize(0.12);
		ANA_H->chi2s_ctr[q]->GetXaxis()->SetLabelOffset(0.03);
		ANA_H->chi2s_ctr[q]->GetYaxis()->SetLabelOffset(0.04);

		lab.SetTextFont(42);
		lab.SetTextSize(0.2);
		lab.SetTextColor(kBlack);
	//	lab.DrawLatex(.35,.85, Form("cos(#theta*): %2.1f#divide%2.1f", Bin.ct_center[c] - Bin.dct[c]/2.0 , Bin.ct_center[c] + Bin.dct[c]/2.0) );
	}
	
	if(PRINT != "")
		TH->Print(Form("imgsf/q2-%3.2f_sf-%s_runningvar-wmass%s", Bin.q2_center[QQ],  ssigma[which].c_str(), PRINT.c_str()));
}








 
