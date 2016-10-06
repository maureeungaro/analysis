void show_2D_vertex()
{
	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.12);
	gStyle->SetPadTopMargin(0.08);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
	lab.SetTextFont(32);
	lab.SetTextSize(0.052);
	lab.SetNDC();

	TLine *min_cut = new TLine(Pars.vz_limits[0], -10, Pars.vz_limits[0], 360);
	TLine *max_cut = new TLine(Pars.vz_limits[1], -10, Pars.vz_limits[1], 360);
	min_cut->SetLineStyle(7);
	max_cut->SetLineStyle(7);
	min_cut->SetLineColor(kRed+2);
	max_cut->SetLineColor(kRed+2);
	min_cut->SetLineWidth(2);
	max_cut->SetLineWidth(2);
	
	
	TLine *min_cut2 = new TLine(Pars.vz_limits[0], -3.2, Pars.vz_limits[0], 3.2);
	TLine *max_cut2 = new TLine(Pars.vz_limits[1], -3.2, Pars.vz_limits[1], 3.2);
	min_cut2->SetLineStyle(7);
	max_cut2->SetLineStyle(7);
	min_cut2->SetLineColor(kRed+2);
	max_cut2->SetLineColor(kRed+2);
	min_cut2->SetLineWidth(2);
	max_cut2->SetLineWidth(2);
	
	
	
	TLine *dmin_cut = new TLine(-10, -Pars.delta_z, 3, -Pars.delta_z);
	TLine *dmax_cut = new TLine(-10,  Pars.delta_z, 3,  Pars.delta_z);
	dmin_cut->SetLineStyle(7);
	dmax_cut->SetLineStyle(7);
	dmin_cut->SetLineColor(kRed+2);
	dmax_cut->SetLineColor(kRed+2);
	dmin_cut->SetLineWidth(2);
	dmax_cut->SetLineWidth(2);
	
	TCanvas *Cvtx  = new TCanvas("Cvtx", "Cvtx", 1100, 1100);
	TPad    *Pvtx  = new TPad("Pvtx", "Pvtx", 0.02, 0.00,  0.98, 0.92);
	Pvtx->Divide(2, 2);
	Pvtx->Draw();
	Pvtx->cd();

	lab.SetTextFont(42);
	lab.SetTextSize(0.047);
	lab.SetTextColor(kBlue+3);
	TPaletteAxis *palette;
	
	Pvtx->cd(1);
	gPad->SetLogz();
	H.phi_vz[6][0][0]->Draw("colz");
	Cvtx->Update();
	palette = (TPaletteAxis*)H.phi_vz[6][0][0]->FindObject("palette");
	palette->SetLabelSize(0.038);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.89);
	palette->SetX2NDC(0.92);
	min_cut->Draw();
	max_cut->Draw();
	lab.DrawLatex(0.44, 0.94,  "a: electron, not corrected");
	
	Pvtx->cd(3);
	gPad->SetLogz();
	H.phi_vz[6][2][0]->Draw("colz");
	Cvtx->Update();
	palette = (TPaletteAxis*)H.phi_vz[6][2][0]->FindObject("palette");
	palette->SetLabelSize(0.038);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.89);
	palette->SetX2NDC(0.92);
	min_cut->Draw();
	max_cut->Draw();
	lab.DrawLatex(0.3, 0.94,  "c: electron, corrected, after cut");
	
	Pvtx->cd(2);
	//gPad->SetLogz();
	H.deltavz_vz[6][0]->Draw("colz");
	Cvtx->Update();
	palette = (TPaletteAxis*)H.deltavz_vz[6][0]->FindObject("palette");
	palette->SetLabelSize(0.038);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.89);
	palette->SetX2NDC(0.92);
	min_cut2->Draw();
	max_cut2->Draw();
	dmin_cut->Draw();
	dmax_cut->Draw();
	lab.DrawLatex(0.49, 0.94,  "b: #Delta VZ, not corrected");
	
	Pvtx->cd(4);
	//gPad->SetLogz();
	H.deltavz_vz[6][2]->Draw("colz");
	Cvtx->Update();
	palette = (TPaletteAxis*)H.deltavz_vz[6][2]->FindObject("palette");
	palette->SetLabelSize(0.038);
	palette->SetLabelOffset(0.01);
	palette->SetX1NDC(0.89);
	palette->SetX2NDC(0.92);
	min_cut2->Draw();
	max_cut2->Draw();
	dmin_cut->Draw();
	dmax_cut->Draw();
	lab.DrawLatex(0.45, 0.94,  "d: #Delta VZ, corrected, after cut");
	lab.SetTextColor(kBlack+3);
	lab.DrawLatex(0.35, 0.87,  Form("events kept: %3.1f%%", 100*H.deltavz_vz[6][2]->GetEntries() /  H.deltavz_vz[6][1]->GetEntries() ));

	
	Cvtx->cd();
	lab.SetTextFont(102);
	lab.SetTextSize(0.043);
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.04, 0.94,  "Vertex Correction, Cut");
	
	lab.SetTextFont(42);
	lab.SetTextSize(0.024);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.82, 0.94,  Form("#Delta vz #leq %3.1f", Pars.delta_z));
		
	lab.DrawLatex(0.62, 0.93,  Form("%3.1f #leq vz #leq %3.1f", Pars.vz_limits[0], Pars.vz_limits[1]));
	lab.DrawLatex(0.66, 0.96,  "VZ Cut:");
	
	
	
	
	if(PRINT != "") 
	{
		Cvtx->Print(Form("vtx_2D_all_sector%s", PRINT.c_str()) );
	}
	
}






