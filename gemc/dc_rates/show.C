void show_dc_occ()
{
	
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetNDC(1);
	
	TCanvas *rates1  = new TCanvas("rates1", "DC Occupancy", 1000, 1000);


	// TEMP SCALE TO 100 SO WE DO NOT HAVE TO RECALC
	dc_occ[SECT][ENERGY][CONF]->SetMaximum(24);

	dc_occ[SECT][ENERGY][CONF]->Draw("colz");
	
	lab.SetTextSize(0.05);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.DrawLatex(0.15, 0.915, Form("Hit Probability for Sector %d for %s", SECT+1, sconf[CONF].c_str() ) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.78, 0.02,   "Wire" );
	
	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.7,   "Layer" );
	
	
	if(PRINT != "") {
		for(int z=0; z<NZONES; z++){
			rates1->Print(Form("img/conf-%s_zone-%s_plot-occ_region-1.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
			rates1->Print(Form("img/conf-%s_zone-%s_plot-occ_region-2.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
			rates1->Print(Form("img/conf-%s_zone-%s_plot-occ_region-3.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
		}
	}
}


void show_dc_int_occ()
{
	gStyle->SetPadLeftMargin(0.16);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	
	TCanvas *rates  = new TCanvas("rates2", "DC Occupancy Summary", 1000, 1000);
	TPad *prates    = new TPad("prates","prates", 0.01, 0.06, 0.99, 0.88);
	prates->Draw();
	
	// get max
	int whicmax = 0;
	double max  = 1;
	for(int r=0; r<3; r++)
	{
		dc_occ_summary[r][ENERGY][CONF]->SetMarkerStyle(20 + r);
		dc_occ_summary[r][ENERGY][CONF]->SetMarkerSize(1.5);
		dc_occ_summary[r][ENERGY][CONF]->SetMinimum(0);
		if(dc_occ_summary[r][ENERGY][CONF]->GetMaximum()*1.5>max)
		{
			whicmax = r;
			max = dc_occ_summary[r][ENERGY][CONF]->GetMaximum()*1.5;
			if(max >100) max = 110;
		}

		// manually setting max
		dc_occ_summary[r][ENERGY][CONF]->SetMaximum(max);
		dc_occ_summary[r][ENERGY][CONF]->SetMaximum(45.0);

//		if(CONF==2)
//			dc_occ_summary[r][ENERGY][CONF]->SetMaximum(2);

	}
	
	dc_occ_summary[0][ENERGY][CONF]->SetMarkerColor(kBlue+2);
	dc_occ_summary[1][ENERGY][CONF]->SetMarkerColor(kRed+2);
	dc_occ_summary[2][ENERGY][CONF]->SetMarkerColor(kGreen+1);
	dc_occ_summary[0][ENERGY][CONF]->SetFillColor(kBlue+2);
	dc_occ_summary[1][ENERGY][CONF]->SetFillColor(kRed+2);
	dc_occ_summary[2][ENERGY][CONF]->SetFillColor(kGreen+1);
	
	
	double intocc[3];
	for(int r=0; r<3; r++)
	{
		
		dc_occ_summary[r][ENERGY][CONF]->Fit("pol0");
		intocc[r] = dc_occ_summary[r][ENERGY][CONF]->GetFunction("pol0")->GetParameter(0);
	}
	intocc[0] = dc_occ_summary[0][ENERGY][CONF]->GetFunction("pol0")->SetLineColor(kBlue+2);
	intocc[1] = dc_occ_summary[1][ENERGY][CONF]->GetFunction("pol0")->SetLineColor(kRed+2);
	intocc[2] = dc_occ_summary[2][ENERGY][CONF]->GetFunction("pol0")->SetLineColor(kGreen+1);

			
	dc_occ_summary[whicmax][ENERGY][CONF]->Draw("P");
	for(int r=0; r<3; r++)
	{
		dc_occ_summary[r][ENERGY][CONF]->Draw("sameP");
	}
	
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.1, 0.915, Form("Drift Chamber Occupancy for %s", sconf[CONF].c_str() ) );
	
	lab.SetTextColor(kBlack);
	lab.DrawLatex(0.45, 0.02,   "Sector" );
	
	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.4,   "Occupancy     [%]" );
	
	char r1label[100];
	char r2label[100];
	char r3label[100];


	double r1Occ = intocc[0];
	double r2Occ = intocc[1];
	double r3Occ = intocc[2];

	//if(r1Occ > 100) r1Occ = 100;


	sprintf(r1label, "Region1: %3.2f%% * %d = %3.2f", intocc[0]/factor[CONF],  factor[CONF], r1Occ);
	sprintf(r2label, "Region2: %3.2f%% * %d = %3.2f", intocc[1]/factor[CONF],  factor[CONF], r2Occ);
	sprintf(r3label, "Region3: %3.2f%% * %d = %3.2f", intocc[2]/factor[CONF],  factor[CONF], r3Occ);

	TLegend *tmodels  = new TLegend(0.3, 0.6, 0.8,  0.73);
	tmodels->AddEntry(dc_occ_summary[0][ENERGY][CONF], r1label,  "P");
	tmodels->AddEntry(dc_occ_summary[1][ENERGY][CONF], r2label,  "P");
	tmodels->AddEntry(dc_occ_summary[2][ENERGY][CONF], r3label,  "P");
	tmodels->SetBorderSize(0);
	tmodels->SetFillColor(0);
	tmodels->Draw();
	
	if(PRINT != "") {
		for(int z=0; z<NZONES; z++){
			rates->Print(Form("img/conf-%s_zone-%s_plot-intocc_region-1.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
			rates->Print(Form("img/conf-%s_zone-%s_plot-intocc_region-2.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
			rates->Print(Form("img/conf-%s_zone-%s_plot-intocc_region-3.%s", sconf[CONF].c_str(), SZONE[z].c_str(), PRINT.c_str() ) );
		}
	}
}




void show_vertex()
{
	
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetNDC(1);
	
	TCanvas *rates1  = new TCanvas("rates1", "Z vertex", 1000, 1000);
	gPad->SetLogz();

	dc_ver[ENERGY][CONF][ZONE][REG]->SetMinimum(0.001);

	if(REG==0) {
		if(ZONE==3) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(8);
		if(ZONE==0) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(2);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(5);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(1);

	}
	if(REG==1) {
		if(ZONE==3) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(3);
		if(ZONE==0) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(2);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(2);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(0.02);

	}
	if(REG==2) {
		if(ZONE==3) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(8);
		if(ZONE==0) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(2);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(5);
		if(ZONE==1) dc_ver[ENERGY][CONF][ZONE][REG]->SetMaximum(0.02);

	}

	dc_ver[ENERGY][CONF][ZONE][REG]->Draw("colz");
	
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.DrawLatex(0.11, 0.915, Form("R vs Z vertex of tracks in region %d for %s", REG+1, sconf[CONF].c_str()) );
	
	lab.DrawLatex(0.8, 0.04,   "Z [mm]" );
	
	lab.SetTextAngle(90);
	lab.DrawLatex(0.06, 0.4,   "R [mm]" );


	// labeling positions
	lab.SetTextAngle(0);
	lab.SetTextSize(0.024);
	lab.SetNDC(0);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.0,  3*zlimits[0][0][ZONE],  "Target" );
	lab.DrawLatex(325,  3*zlimits[0][0][ZONE],  "FMT" );
	lab.DrawLatex(2750, 3*zlimits[0][0][ZONE],  "Torus Start" );
	lab.DrawLatex(4912.2, 3*zlimits[0][0][ZONE],  "Torus End" );

	
	// hacking arrows
	Double_t x[4]  = {0, 325, 2750, 4912.2};
	Double_t y[4]  = {zlimits[0][0][ZONE], zlimits[0][0][ZONE], zlimits[0][0][ZONE], zlimits[0][0][ZONE]};
	Double_t ex[4] = {0.5, 0.5, 0.5, 0.5};
	TGraphErrors * ulGraph = new TGraphErrors(4, x, y, ex, 0);
	ulGraph->SetMarkerStyle(22);
	ulGraph->SetMarkerColor(kRed+3);
	ulGraph->Draw("Psame");

	
	if(PRINT != "")
		rates1->Print(Form("img/conf-%s_zone-%s_plot-vertex_region-%d.%s", sconf[CONF].c_str(),  SZONE[ZONE].c_str(), REG+1, PRINT.c_str() ) );

}





void show_procID()
{
   
   gStyle->SetPadLeftMargin(0.12);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.32);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);
   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   dc_procID[CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   lab.DrawLatex(8.0, 20,   "Process ID" );
   
   lab.SetTextAngle(90);
   lab.SetTextSize(0.028);

   lab.DrawLatex(1,  -12,   "e ionization" );
   lab.DrawLatex(2,  -12,   "compton scattering" );
   lab.DrawLatex(3,  -12,   "bremsstrahlung" );
   lab.DrawLatex(4,  -12,   "Photo Electric" );
   lab.DrawLatex(5,  -12,   "Gamma Conversion" );
   lab.DrawLatex(6,  -12,   "e+ Annihilation" );
   lab.DrawLatex(7,  -12,   "photon-Nuclear" );
   lab.DrawLatex(8,  -12,   "electron-Nuclear" );
   lab.DrawLatex(9,  -12,   "Hadronic Elastic" );
   lab.DrawLatex(10, -12,   "Proton Inelastic" );
   lab.DrawLatex(11, -12,   "Neutron Inelastic" );
   lab.DrawLatex(12, -12,   "pi- Inelastic" );
   lab.DrawLatex(13, -12,   "pi+ Inelastic" );
   lab.DrawLatex(14, -12,   "hadron ionization" );
   lab.DrawLatex(15, -12,   "neutron capture" );
   lab.DrawLatex(16, -12,   "decay" );
   lab.DrawLatex(17, -12,   "muon ionization" );
   lab.DrawLatex(18, -12,   "Coulomb Scattering" );
   lab.DrawLatex(19, -12,   "Cherenkov" );
   lab.DrawLatex(20, -12,   "deuteron Inelastic" );

   
   if(PRINT != "")
      rates1->Print(Form("img/procID_%s.%s", sconf[CONF].c_str(), PRINT.c_str() ) );
   
}


void show_procvsL()
{
   
   gStyle->SetPadLeftMargin(0.32);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.12);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);
   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   gPad->SetLogz();

   dc_procIDvsLayer[CONF]->GetYaxis()->SetNdivisions(520);
   dc_procIDvsLayer[CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   lab.DrawLatex(2.0, 19,   "Process ID vs SL" );
   
   lab.SetTextSize(0.028);
   
   lab.DrawLatex(-2, 1-0.2,     "e ionization" );
   lab.DrawLatex(-2, 2-0.2,     "compton scattering" );
   lab.DrawLatex(-2, 3-0.2,     "bremsstrahlung" );
   lab.DrawLatex(-2, 4-0.2,     "Photo Electric" );
   lab.DrawLatex(-2, 5-0.2,     "Gamma Conversion" );
   lab.DrawLatex(-2, 6-0.2,     "e+ Annihilation" );
   lab.DrawLatex(-2, 7-0.2,     "photon-Nuclear" );
   lab.DrawLatex(-2, 8-0.2,     "electron-Nuclear" );
   lab.DrawLatex(-2, 9-0.2,     "Hadronic Elastic" );
   lab.DrawLatex(-2, 10-0.2,    "Proton Inelastic" );
   lab.DrawLatex(-2, 11-0.2,    "Neutron Inelastic" );
   lab.DrawLatex(-2, 12-0.2,    "pi- Inelastic" );
   lab.DrawLatex(-2, 13-0.2,    "pi+ Inelastic" );
   lab.DrawLatex(-2, 14-0.2,    "hadron ionization" );
   lab.DrawLatex(-2, 15-0.2,    "neutron capture" );
   lab.DrawLatex(-2, 16-0.2,    "decay" );
   lab.DrawLatex(-2, 17-0.2,    "muon ionization" );
   lab.DrawLatex(-2, 18-0.2,    "Coulomb Scattering" );
   lab.DrawLatex(-2, 19-0.2,    "Cherenkov" );
   lab.DrawLatex(-2, 20-0.2,    "deuteron Inelastic" );
   
   
   if(PRINT != "")
      rates1->Print(Form("img/procIDvsSL_%s.%s", sconf[CONF].c_str(), PRINT.c_str() ) );
   
}



void show_procvspid()
{
   
   gStyle->SetPadLeftMargin(0.32);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.12);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);
   

   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   gPad->SetLogz();

   dc_procIDvspid[CONF]->GetYaxis()->SetNdivisions(520);
   dc_procIDvspid[CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   lab.DrawLatex(-100, 19,   "Process ID vs PID" );
   
   lab.SetTextSize(0.028);
   
   lab.DrawLatex(-430, 1-0.2,     "e ionization" );
   lab.DrawLatex(-430, 2-0.2,     "compton scattering" );
   lab.DrawLatex(-430, 3-0.2,     "bremsstrahlung" );
   lab.DrawLatex(-430, 4-0.2,     "Photo Electric" );
   lab.DrawLatex(-430, 5-0.2,     "Gamma Conversion" );
   lab.DrawLatex(-430, 6-0.2,     "e+ Annihilation" );
   lab.DrawLatex(-430, 7-0.2,     "photon-Nuclear" );
   lab.DrawLatex(-430, 8-0.2,     "electron-Nuclear" );
   lab.DrawLatex(-430, 9-0.2,     "Hadronic Elastic" );
   lab.DrawLatex(-430, 10-0.2,    "Proton Inelastic" );
   lab.DrawLatex(-430, 11-0.2,    "Neutron Inelastic" );
   lab.DrawLatex(-430, 12-0.2,    "pi- Inelastic" );
   lab.DrawLatex(-430, 13-0.2,    "pi+ Inelastic" );
   lab.DrawLatex(-430, 14-0.2,    "hadron ionization" );
   lab.DrawLatex(-430, 15-0.2,    "neutron capture" );
   lab.DrawLatex(-430, 16-0.2,    "decay" );
   lab.DrawLatex(-430, 17-0.2,    "muon ionization" );
   lab.DrawLatex(-430, 18-0.2,    "Coulomb Scattering" );
   lab.DrawLatex(-430, 19-0.2,    "Cherenkov" );
   lab.DrawLatex(-430, 20-0.2,    "deuteron Inelastic" );
   
   
   if(PRINT != "")
      rates1->Print(Form("img/procIDvspid_%s.%s", sconf[CONF].c_str(), PRINT.c_str() ) );
   
}


void show_procvsedep()
{
   
   gStyle->SetPadLeftMargin(0.32);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.12);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);
   
   
   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   gPad->SetLogz();
   
   dc_procIDvsEdep[CONF]->GetYaxis()->SetNdivisions(520);
   dc_procIDvsEdep[CONF]->GetXaxis()->SetNdivisions(505);
   dc_procIDvsEdep[CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   lab.DrawLatex(0.001, 19,  "Process ID vs Energy deposited");
   lab.DrawLatex(0.009, -1.5,   "MeV" );

   lab.SetTextSize(0.028);
   
   lab.DrawLatex(-0.0037, 1-0.2,     "e ionization" );
   lab.DrawLatex(-0.0037, 2-0.2,     "compton scattering" );
   lab.DrawLatex(-0.0037, 3-0.2,     "bremsstrahlung" );
   lab.DrawLatex(-0.0037, 4-0.2,     "Photo Electric" );
   lab.DrawLatex(-0.0037, 5-0.2,     "Gamma Conversion" );
   lab.DrawLatex(-0.0037, 6-0.2,     "e+ Annihilation" );
   lab.DrawLatex(-0.0037, 7-0.2,     "photon-Nuclear" );
   lab.DrawLatex(-0.0037, 8-0.2,     "electron-Nuclear" );
   lab.DrawLatex(-0.0037, 9-0.2,     "Hadronic Elastic" );
   lab.DrawLatex(-0.0037, 10-0.2,    "Proton Inelastic" );
   lab.DrawLatex(-0.0037, 11-0.2,    "Neutron Inelastic" );
   lab.DrawLatex(-0.0037, 12-0.2,    "pi- Inelastic" );
   lab.DrawLatex(-0.0037, 13-0.2,    "pi+ Inelastic" );
   lab.DrawLatex(-0.0037, 14-0.2,    "hadron ionization" );
   lab.DrawLatex(-0.0037, 15-0.2,    "neutron capture" );
   lab.DrawLatex(-0.0037, 16-0.2,    "decay" );
   lab.DrawLatex(-0.0037, 17-0.2,    "muon ionization" );
   lab.DrawLatex(-0.0037, 18-0.2,    "Coulomb Scattering" );
   lab.DrawLatex(-0.0037, 19-0.2,    "Cherenkov" );
   lab.DrawLatex(-0.0037, 20-0.2,    "deuteron Inelastic" );
   
   
   if(PRINT != "")
      rates1->Print(Form("img/procIDvseDep_%s.%s", sconf[CONF].c_str(), PRINT.c_str() ) );
   
}

void show_procvse()
{
   if(SECT>3) return;
   
   gStyle->SetPadLeftMargin(0.32);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.12);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);

   
   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   gPad->SetLogz();
   
   dc_procIDvsTrackE[REG][CONF]->GetYaxis()->SetNdivisions(520);
   dc_procIDvsTrackE[REG][CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   double startT = 500;
   if(REG==1) startT = 2.6;
   if(REG==2) startT = 0.15;

   lab.DrawLatex(startT, 19,   Form("Process ID vs Track Energy (%d)", REG+1) );
   lab.DrawLatex(2500, -1.5,   "MeV" );

   lab.SetTextSize(0.028);
   
   double startL = -1300;
   if(REG==1) startL = -12;
   if(REG==2) startL = -0.4;
   
   lab.DrawLatex(startL, 1-0.2,     "e ionization" );
   lab.DrawLatex(startL, 2-0.2,     "compton scattering" );
   lab.DrawLatex(startL, 3-0.2,     "bremsstrahlung" );
   lab.DrawLatex(startL, 4-0.2,     "Photo Electric" );
   lab.DrawLatex(startL, 5-0.2,     "Gamma Conversion" );
   lab.DrawLatex(startL, 6-0.2,     "e+ Annihilation" );
   lab.DrawLatex(startL, 7-0.2,     "photon-Nuclear" );
   lab.DrawLatex(startL, 8-0.2,     "electron-Nuclear" );
   lab.DrawLatex(startL, 9-0.2,     "Hadronic Elastic" );
   lab.DrawLatex(startL, 10-0.2,    "Proton Inelastic" );
   lab.DrawLatex(startL, 11-0.2,    "Neutron Inelastic" );
   lab.DrawLatex(startL, 12-0.2,    "pi- Inelastic" );
   lab.DrawLatex(startL, 13-0.2,    "pi+ Inelastic" );
   lab.DrawLatex(startL, 14-0.2,    "hadron ionization" );
   lab.DrawLatex(startL, 15-0.2,    "neutron capture" );
   lab.DrawLatex(startL, 16-0.2,    "decay" );
   lab.DrawLatex(startL, 17-0.2,    "muon ionization" );
   lab.DrawLatex(startL, 18-0.2,    "Coulomb Scattering" );
   lab.DrawLatex(startL, 19-0.2,    "Cherenkov" );
   lab.DrawLatex(startL, 20-0.2,    "deuteron Inelastic" );
   
   
   if(PRINT != "")
      rates1->Print(Form("img/procIDvsE_%d_%s.%s", REG+1, sconf[CONF].c_str(), PRINT.c_str() ) );
   
}



void show_procvsZ()
{
   
   gStyle->SetPadLeftMargin(0.32);
   gStyle->SetPadRightMargin(0.14);
   gStyle->SetPadTopMargin(0.06);
   gStyle->SetPadBottomMargin(0.12);
   
   TLatex lab;
   lab.SetTextColor(kBlue+3);
   lab.SetTextFont(32);
   
   
   
   TCanvas *rates1  = new TCanvas("rates1", "Process ID", 1000, 800);
   gPad->SetLogz();
   
   dc_procIDvsZ[REG][CONF]->GetYaxis()->SetNdivisions(520);
   dc_procIDvsZ[REG][CONF]->Draw("colz");
   
   
   lab.SetTextColor(kBlack);
   lab.DrawLatex(1000, 19,   Form("Process ID vs Vertex Z for R%d", REG+1) );

   lab.DrawLatex(9000, -1.5,   "mm" );
   
   lab.SetTextSize(0.028);
   
   lab.DrawLatex(-4000, 1-0.2,     "e ionization" );
   lab.DrawLatex(-4000, 2-0.2,     "compton scattering" );
   lab.DrawLatex(-4000, 3-0.2,     "bremsstrahlung" );
   lab.DrawLatex(-4000, 4-0.2,     "Photo Electric" );
   lab.DrawLatex(-4000, 5-0.2,     "Gamma Conversion" );
   lab.DrawLatex(-4000, 6-0.2,     "e+ Annihilation" );
   lab.DrawLatex(-4000, 7-0.2,     "photon-Nuclear" );
   lab.DrawLatex(-4000, 8-0.2,     "electron-Nuclear" );
   lab.DrawLatex(-4000, 9-0.2,     "Hadronic Elastic" );
   lab.DrawLatex(-4000, 10-0.2,    "Proton Inelastic" );
   lab.DrawLatex(-4000, 11-0.2,    "Neutron Inelastic" );
   lab.DrawLatex(-4000, 12-0.2,    "pi- Inelastic" );
   lab.DrawLatex(-4000, 13-0.2,    "pi+ Inelastic" );
   lab.DrawLatex(-4000, 14-0.2,    "hadron ionization" );
   lab.DrawLatex(-4000, 15-0.2,    "neutron capture" );
   lab.DrawLatex(-4000, 16-0.2,    "decay" );
   lab.DrawLatex(-4000, 17-0.2,    "muon ionization" );
   lab.DrawLatex(-4000, 18-0.2,    "Coulomb Scattering" );
   lab.DrawLatex(-4000, 19-0.2,    "Cherenkov" );
   lab.DrawLatex(-4000, 20-0.2,    "deuteron Inelastic" );
   
   
   if(PRINT != "")
      rates1->Print(Form("img/procIDvsZ_r%d_%s.%s", REG+1, sconf[CONF].c_str(), PRINT.c_str() ) );
   
}
