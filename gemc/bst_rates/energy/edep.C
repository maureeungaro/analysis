{
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);


	bool recalc =0; // 1 will refill all histos - 0 will open the outputf file as input
	
	const int NPART     = 3;
	string SPART[NPART] = { "pions"   ,  "protons" , "kaons" };
	double fmass[NPART] = { 139.57018 ,  938.27203 , 493.677 };
	int fpid[NPART]     = { 211       ,     2212   ,    321  };
	double maxE[NPART]  = { 0.4       ,     0.7    ,    0.5  };
	double maxP[NPART]  = { 700       ,     2500   ,    1500 };
	
	
	// layers
	// last layer represents one chip in one layer
	const int nreg  = 4; 
	const int nbstl = 2*nreg;  // 2 layers of silicon for each region. Only one region considered for the chips 
	string  lname[nbstl]   = { "1a", "1b", "2a", "2b", "3a", "3b", "4a", "4b"};
	int nmodules[nbstl]    = {  10 ,  10 ,  14 ,  14 ,  18 ,  18 ,  24 ,  24 };
	int maxthe[nbstl]      = { 170 , 170 , 160 , 160 , 150 , 150 , 125 , 125 };
		
	const double TWINDOW = 130E-9;
	double TOT_TIME;
	TH1F *HNHITS;  // contains the number of hits - for the background
	int NHITS ;
	
		
	TH2F *edep_vs_mom[NPART][nbstl];      
	TH2F *edep_vs_the[NPART][nbstl];       
	TH2F *edep_vs_phi[NPART][nbstl];       
	
	TH2F *bedep_vs_mom[2][nbstl];      
	TH2F *bedep_vs_the[2][nbstl];       
	TH2F *bedep_vs_phi[2][nbstl];       
	

	TFile f[NPART];

	if(recalc == 1)
	{
		
		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

		
		for(int p=0; p<NPART; p++)
		{		
			string fname = 	Form("/arena/BST/root/%s.root", SPART[p].c_str());
			f[p].Open(fname.c_str());
			cout << fname << " " << SPART[p] << endl;

			
			
			for(int l=0; l<nbstl; l++)
			{
				edep_vs_mom[p][l] = new TH2F(Form("edep_vs_mom_%s_l%d", SPART[p].c_str(), l+1),
						                         Form("edep_vs_mom_%s_l%d", SPART[p].c_str(), l+1),
																		 200, 0, maxP[p], 200, 0, maxE[p]);
				
				edep_vs_the[p][l] = new TH2F(Form("edep_vs_the_%s_l%d", SPART[p].c_str(), l+1),
																		 Form("edep_vs_the_%s_l%d", SPART[p].c_str(), l+1),
																		 200, 20, 140, 200, 0, maxE[p]);
				
				edep_vs_phi[p][l] = new TH2F(Form("edep_vs_phi_%s_l%d", SPART[p].c_str(), l+1),
																		 Form("edep_vs_phi_%s_l%d", SPART[p].c_str(), l+1),
																		 200, -190, 190, 200, 0, maxE[p]);				
				
				string hist, cut;
				
				cout << " Layer " << l + 1 << endl;
				
				// momentum
				hist = Form("Edep:sqrt(abs(%6.5f*%6.5f-E*E)) >> edep_vs_mom_%s_l%d", fmass[p], fmass[p], SPART[p].c_str(), l+1);
				cut  = Form("layer==%d && Edep>0 && pid == %d && mpid==0 && Edep < %4.3f && sqrt(abs(%6.5f*%6.5f-E*E))<%4.3f",  l+1, fpid[p], maxE[p], fmass[p], fmass[p], maxP[p]);
				cout << cut << endl;
				bstT->Draw(hist.c_str(), cut.c_str());
				edep_vs_mom[p][l]->SetDirectory(0);
				
				// theta
				hist = Form("Edep:acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> edep_vs_the_%s_l%d", SPART[p].c_str(), l+1);
				cut  = Form("layer==%d && Edep>0 && pid == %d && mpid==0 && Edep < %4.3f && acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 > 20 && acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 < 140",  l+1, fpid[p], maxE[p]);
				cout << cut << endl;
				bstT->Draw(hist.c_str(), cut.c_str());
				edep_vs_the[p][l]->SetDirectory(0);
				
				
				// phi
				hist = Form("Edep:(abs(y)/y)*acos(x/sqrt(x*x+y*y))*180/3.141592 >> edep_vs_phi_%s_l%d", SPART[p].c_str(), l+1);
				cut  = Form("layer==%d && Edep>0 && pid == %d && mpid==0 && Edep < %4.3f ",  l+1, fpid[p], maxE[p]);
				cout << cut << endl;
				bstT->Draw(hist.c_str(), cut.c_str());
				edep_vs_phi[p][l]->SetDirectory(0);
			}
			
			f[p].Close();	
		}
		
		f[0].Open("/arena/BST/root/lh2.root");
		for(int l=0; l<nbstl; l++)
		{
			// total number of entries
			HNHITS = new TH1F("nhits", "nhits", 1, 0, 1);
			NHITS  = genT->GetEntries();
			HNHITS->SetBinContent(1, NHITS);
			HNHITS->SetDirectory(0);
			TOT_TIME = NHITS*TWINDOW;
			bedep_vs_mom[0][l] = new TH2F(Form("bedep_vs_mom_em_l%d", l+1),
																    Form("bedep_vs_mom_em_l%d", l+1),
																    200, 0, 1, 200, 0, 1);
			
			bedep_vs_the[0][l] = new TH2F(Form("bedep_vs_the_em_l%d", l+1),
																		Form("bedep_vs_the_em_l%d", l+1),
																		200, 20, maxthe[l], 200, 0, 0.1);
			
			bedep_vs_phi[0][l] = new TH2F(Form("bedep_vs_phi_em_l%d", l+1),
																		Form("bedep_vs_phi_em_l%d", l+1),
																		200, -190, 190, 200, 0,  0.1);
						
			bedep_vs_mom[1][l] = new TH2F(Form("bedep_vs_mom_ha_l%d", l+1),
																    Form("bedep_vs_mom_ha_l%d", l+1),
																    200, 0, 2000, 200, 0,  2);
			
			bedep_vs_the[1][l] = new TH2F(Form("bedep_vs_the_ha_l%d", l+1),
																		Form("bedep_vs_the_ha_l%d", l+1),
																		200, 20, maxthe[l], 200, 0,  1);
			
			bedep_vs_phi[1][l] = new TH2F(Form("bedep_vs_phi_ha_l%d", l+1),
																		Form("bedep_vs_phi_ha_l%d", l+1),
																		200, -190, 190, 200, 0,  1);			

			string hist, cut;
			
			cout << " Layer " << l + 1 << endl;
			
			// momentum
			hist = Form("Edep:E >> bedep_vs_mom_em_l%d", l+1);
			cut  = Form("layer==%d && Edep>0 && (pid == 11 || pid==22 || pid==-11) && Edep>0.0 && E>0",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_mom[0][l]->SetDirectory(0);
			bedep_vs_mom[0][l]->Scale(1.0/(TOT_TIME));
			
			hist = Form("Edep:E >> bedep_vs_mom_ha_l%d", l+1);
			cut  = Form("layer==%d && Edep>0 && (pid != 11 && pid!=22 && pid!=-11) && Edep>0 && E>0 ",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_mom[1][l]->SetDirectory(0);
			bedep_vs_mom[1][l]->Scale(1.0/(TOT_TIME));
			
			// theta
			hist = Form("Edep:acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> bedep_vs_the_em_l%d", l+1);
			cut  = Form("layer==%d && Edep>0 && (pid == 11 || pid==22 || pid==-11) && Edep>0 && E>0",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_the[0][l]->SetDirectory(0);
			bedep_vs_the[0][l]->Scale(1.0/(TOT_TIME));
			
			hist = Form("Edep:acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> bedep_vs_the_ha_l%d", l+1);
			cut  = Form("layer==%d && Edep>0 &&  (pid != 11 && pid!=22 && pid!=-11) && Edep>0 && E>0",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_the[1][l]->SetDirectory(0);
			bedep_vs_the[1][l]->Scale(1.0/(TOT_TIME));
			
			
			
			// phi
			hist = Form("Edep:(abs(y)/y)*acos(x/sqrt(x*x+y*y))*180/3.141592 >> bedep_vs_phi_em_l%d",  l+1);
			cut  = Form("layer==%d && Edep>0 && (pid == 11 || pid==22 || pid==-11)   && Edep>0 && E>0",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_phi[0][l]->SetDirectory(0);
			bedep_vs_phi[0][l]->Scale(1.0/(TOT_TIME));
			
			hist = Form("Edep:(abs(y)/y)*acos(x/sqrt(x*x+y*y))*180/3.141592 >> bedep_vs_phi_ha_l%d",  l+1);
			cut  = Form("layer==%d && Edep>0 &&  (pid != 11 && pid!=22 && pid!=-11)    && Edep>0 && E>0",  l+1);
			cout << cut << endl;
			bstT->Draw(hist.c_str(), cut.c_str());
			bedep_vs_phi[1][l]->SetDirectory(0);
			bedep_vs_phi[1][l]->Scale(1.0/(TOT_TIME));
			
			
		}	
		
		
		c1->Close();
		
		// saving all histos
		cout << " Saving all histos " << endl;
		f[0].Open("../rootfiles/edep.root", "RECREATE");
		for(int p=0; p<NPART; p++)
			for(int l=0; l<nbstl; l++)
			{
				edep_vs_mom[p][l]->Write();
				edep_vs_the[p][l]->Write();
				edep_vs_phi[p][l]->Write();
			}				
		for(int l=0; l<nbstl; l++)
		{
			bedep_vs_mom[0][l]->Write();
			bedep_vs_the[0][l]->Write();
			bedep_vs_phi[0][l]->Write();
			bedep_vs_mom[1][l]->Write();
			bedep_vs_the[1][l]->Write();
			bedep_vs_phi[1][l]->Write();
		}				
		HNHITS->Write();
		
		
	}	
	else
	{
		TFile ff("../rootfiles/edep.root");
		for(int p=0; p<NPART; p++)
			for(int l=0; l<nbstl; l++)
			{
				edep_vs_mom[p][l] = (TH2F*) ff.Get(Form("edep_vs_mom_%s_l%d", SPART[p].c_str(), l+1));
				edep_vs_the[p][l] = (TH2F*) ff.Get(Form("edep_vs_the_%s_l%d", SPART[p].c_str(), l+1));
				edep_vs_phi[p][l] = (TH2F*) ff.Get(Form("edep_vs_phi_%s_l%d", SPART[p].c_str(), l+1));
				
				edep_vs_mom[p][l]->SetDirectory(0);
				edep_vs_the[p][l]->SetDirectory(0);
				edep_vs_phi[p][l]->SetDirectory(0);
			}
			
		for(int l=0; l<nbstl; l++)
		{
			bedep_vs_mom[0][l] = (TH2F*) ff.Get(Form("bedep_vs_mom_em_l%d", l+1));
			bedep_vs_the[0][l] = (TH2F*) ff.Get(Form("bedep_vs_the_em_l%d", l+1));
			bedep_vs_phi[0][l] = (TH2F*) ff.Get(Form("bedep_vs_phi_em_l%d", l+1));
			bedep_vs_mom[1][l] = (TH2F*) ff.Get(Form("bedep_vs_mom_ha_l%d", l+1));
			bedep_vs_the[1][l] = (TH2F*) ff.Get(Form("bedep_vs_the_ha_l%d", l+1));
			bedep_vs_phi[1][l] = (TH2F*) ff.Get(Form("bedep_vs_phi_ha_l%d", l+1));
			
			bedep_vs_mom[0][l]->SetDirectory(0);
			bedep_vs_the[0][l]->SetDirectory(0);
			bedep_vs_phi[0][l]->SetDirectory(0);
			bedep_vs_mom[1][l]->SetDirectory(0);
			bedep_vs_the[1][l]->SetDirectory(0);
			bedep_vs_phi[1][l]->SetDirectory(0);
		}
					
									
		ff.Close();
	}




	gStyle->SetPadLeftMargin(0.14);
	gStyle->SetPadRightMargin(0.18);
	gStyle->SetPadTopMargin(0.15);
	gStyle->SetPadBottomMargin(0.14);
	gStyle->SetCanvasColor(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadBorderMode(0);
	
	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);
	
	
	// ENERGY
	TCanvas *energy  = new TCanvas("energy", "energy", 800, 700);


	for(int l=0; l<nbstl; l++)
	{
		
		bedep_vs_mom[0][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.1, 0.915, Form("dE/dx versus Energy, e.m. Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.5, 0.04, "Energy of the particle [MeV]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.8, "Hz");
		energy->Print(Form("Edep_vs_mom_em_l%s.gif", lname[l]));
		
		bedep_vs_mom[1][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.08, 0.915, Form("dE/dx versus Energy, hadronic Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.5, 0.04, "Energy of the particle [MeV]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.8, "Hz");
		energy->Print(Form("Edep_vs_mom_ha_l%s.gif", lname[l]));
		
	
		bedep_vs_the[0][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.2, 0.915, Form("Energy Versus Theta, e.m. Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.7, 0.04, "#theta [degrees]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.8, "Hz");
		energy->Print(Form("Edep_vs_the_em_l%s.gif", lname[l]));
		
		bedep_vs_the[1][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.2, 0.915, Form("Energy Versus Theta, hadronic Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.7, 0.04, "#theta [degrees]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.8, "Hz");
		energy->Print(Form("Edep_vs_the_ha_l%s.gif", lname[l]));
		

		bedep_vs_phi[0][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.17, 0.915, Form("Energy Versus Phi, e.m. Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.7, 0.04, "#phi [degrees]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.8, "Hz");
		energy->Print(Form("Edep_vs_phi_em_l%s.gif", lname[l]));
		
		bedep_vs_phi[1][l]->Draw("colz");
		lab.SetTextSize(0.04);
		lab.DrawLatex(0.17, 0.915, Form("Energy Versus Phi, hadronic Background - Layer %s", lname[l]));
		lab.SetTextSize(0.036);
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.7, 0.04, "#phi [degrees]");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
		lab.SetTextAngle(0);
		lab.DrawLatex(0.92, 0.88, "Hz");
		energy->Print(Form("Edep_vs_phi_ha_l%s.gif", lname[l]));
		
	
	
		for(int p=0; p<NPART; p++)
		{
			edep_vs_mom[p][l]->Draw("colz");
			lab.SetTextSize(0.04);
			lab.DrawLatex(0.18, 0.915, Form("dE/dx Versus Momentum, %s - Layer %s", SPART[p], lname[l]));
			lab.SetTextSize(0.036);
			lab.SetTextColor(kBlack);
			lab.DrawLatex(0.6, 0.04, "momentum [MeV]");
			lab.SetTextAngle(90);
			lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
			lab.SetTextAngle(0);
			lab.DrawLatex(0.92, 0.8, "Hz");
			edep_vs_mom[p][l]->GetXaxis()->SetNdivisions(5);
			energy->Print(Form("Edep_vs_mom_%s_l%s.gif", SPART[p], lname[l]));
			
			
			edep_vs_the[p][l]->Draw("colz");
			lab.SetTextSize(0.04);
			lab.DrawLatex(0.26, 0.915, Form("Energy Versus Theta, %s - Layer %s", SPART[p], lname[l]));
			lab.SetTextSize(0.036);
			lab.SetTextColor(kBlack);
			lab.DrawLatex(0.7, 0.04, "#theta [degrees]");
			lab.SetTextAngle(90);
			lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
			lab.SetTextAngle(0);
			lab.DrawLatex(0.92, 0.8, "Hz");
			energy->Print(Form("Edep_vs_the_%s_l%s.gif", SPART[p], lname[l]));
			
			edep_vs_phi[p][l]->Draw("colz");
			lab.SetTextSize(0.04);
			lab.DrawLatex(0.27, 0.915, Form("Energy Versus Phi, %s - Layer %s", SPART[p], lname[l]));
			lab.SetTextSize(0.036);
			lab.SetTextColor(kBlack);
			lab.DrawLatex(0.7, 0.04, "#phi [degrees]");
			lab.SetTextAngle(90);
			lab.DrawLatex(0.05, 0.5, "Energy deposited [MeV]");
			lab.SetTextAngle(0);
			lab.DrawLatex(0.92, 0.8, "Hz");
			energy->Print(Form("Edep_vs_phi_%s_l%s.gif", SPART[p], lname[l]));
		}
	
	
	
	}
	

}


















































