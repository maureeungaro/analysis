void show(int which)
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetFrameFillColor(kYellow-9);

	string poles[3]   = {"S", "E", "M"};
	string real_im[2] = {"Real", "Imag"};
	string pm[2]      = {"plus", "minus"};
   int ipm = PLUS_M > 0 ? 0 : 1;
	
	TLatex lab;
	lab.SetNDC();

	CMult = new TCanvas("CMult", "CMult", 800, 1200);
	PMult = new TPad("PMult", "PMult", 0.02, 0.00,  0.98, 0.90);
	PMult->Divide(1, 2);
	PMult->Draw();


	lab.SetTextAngle(13);
	lab.SetTextSize(0.064);
	PMult->cd(1);
	gPad->SetTheta(31);
	gPad->SetPhi(-45);
	P[iMODEL]->get_pole(which, PLUS_M, ANGMOM, 0)->Draw("surf1FB");
	lab.DrawLatex(0.28, 0.82,  Form("%s (%s_{%d%s})", real_im[0].c_str(), poles[which-1].c_str(), ANGMOM,  pm[ipm].c_str()));

	
	PMult->cd(2);
	gPad->SetTheta(31);
	gPad->SetPhi(-45);
	P[iMODEL]->get_pole(which, PLUS_M, ANGMOM, 1)->Draw("surf1FB");
	lab.DrawLatex(0.28, 0.82,  Form("%s (%s_{%d%s})", real_im[1].c_str(), poles[which-1].c_str(), ANGMOM, pm[ipm].c_str()));
	
	
	CMult->cd(0);
	lab.SetTextAngle(0);
	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.07);
	lab.DrawLatex(0.36, 0.94,  Form("%s", model[iMODEL].c_str()));

	
	if(PRINT==1)
		CMult->Print(Form("img/angmom-%d_multipole-%s_pm-%s_model-%s.png",
								ANGMOM,
								poles[which-1].c_str(),
								pm[ipm].c_str(),
								model[iMODEL].c_str()
							  ));
}













