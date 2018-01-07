void init_bst_histos(string filename, int tindex)
{
	// ROOT bug/feature:
	// if the filename is not declared and opened within the if statement, things won't work
	cout << " Initializing histos for configuration " << starget[tindex] <<endl;
	
	if(recalc == 1)
	{
		cout << " Opening file " << filename << endl << endl;
		TFile f(filename.c_str());
		
		// total number of entries
		HNHITS = new TH1F("nhits", "nhits", 1, 0, 1);
		NHITS  = genT->GetEntries();
		HNHITS->SetBinContent(1, NHITS);
		HNHITS->SetDirectory(0);

		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);
	
		cout << " Defining and Filling sensor and chip energy histos for particles"  << endl;
	
		// ################################################
		// Energy deposited for different particles, layers
		for(int p=0; p<pnum; p++)
			for(int l=0; l<nbstl; l++)
				for(int e=0; e<NENERGY; e++)
				{
					bst_edep[l][p][e][tindex] = new TH1F(Form("bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str()),
														 Form("bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str()), 
														 Nbins, 0, 20);
				}
	
		for(int p=1; p<pnum; p++)
		{
			cout << "  " << pname[p] << endl ;
			for(int l=0; l<nbstl; l++)
				for(int e=0; e<NENERGY; e++)
				{
					// sensors
					if(l<2*nreg)
					{
						string hit    = "strip>-1 && " + EDEP[e];
						string bstcut;
						bstcut = Form("layer == %d", l+1);
						string cut    = hit + " && " + pcut[p] + " && " + bstcut;
						string hist = Form("Edep >> bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str());
						bstT->Draw(hist.c_str(), cut.c_str());
					}
					
					// chip
					if(l>=2*nreg && l<3*nreg)
					{
						string hit    =  "ID==22 && " + EDEP[e];
						string bstcut;
						bstcut = Form("z > %4.3f && z < %4.3f", chip_minz[l-2*nreg], chip_maxz[l-2*nreg]);
						string cut    = hit + " && " + pcut[p] + " && " + bstcut;
						string hist = Form("Edep >> bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str());
						fluxT->Draw(hist.c_str(), cut.c_str());
					}
					
					// regulator
					if(l>=3*nreg)
					{
						string hit    =  "ID==23 && " + EDEP[e];
						string bstcut;
						bstcut = Form("z > %4.3f && z < %4.3f", reg_minz[l-3*nreg], reg_maxz[l-3*nreg]);
						string cut    = hit + " && " + pcut[p] + " && " + bstcut;
						string hist = Form("Edep >> bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str());
						fluxT->Draw(hist.c_str(), cut.c_str());
					}
					
					
					bst_edep[l][p][e][tindex]->SetDirectory(0);
					// saving the noise histos
					if(p==1) bst_edep[l][0][e][tindex]->SetDirectory(0);
				}
		}

		// #########################################################################
		// Energy deposited for e.m. , hadronc particles, integrated over all layers
		edep[0][tindex] = new TH1F(Form("edep_em_%s", starget[tindex].c_str()),
								   Form("edep_em_%s", starget[tindex].c_str()), Nbins, 0, 0.5);
		edep[1][tindex] = new TH1F(Form("edep_ha_%s", starget[tindex].c_str()),
								   Form("edep_ha_%s", starget[tindex].c_str()), Nbins, 0, 0.5);
		
		// electromagnetic energy (sensors only)
		string hist = Form("Edep >> edep_em_%s", starget[tindex].c_str());
		string cut  = "pid==11 || pid==22 || pid==-11";
		bstT->Draw(hist.c_str(), cut.c_str());
		
		// hadronic energy (sensors only)
		hist = Form("Edep >> edep_ha_%s", starget[tindex].c_str());
		cut  = "pid!=11 && pid!=22 && pid!=-11";
		bstT->Draw(hist.c_str(), cut.c_str());
		
		edep[0][tindex]->SetDirectory(0);
		edep[1][tindex]->SetDirectory(0);
		
		cout << " done. " << endl << endl;
    
    
		// ########################################
		// Kinetic Energy (Total Energy minus mass)
		cout <<  " Now defining and filling 1 MeV Newutron Equivalent doses and rates" ;
		for(int l=0; l<nbstl; l++)
			for(int fp=0; fp<4; fp++)
			{
				bst_E[l][fp][tindex] = new TH1F(Form("bst_E_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
												Form("bst_E_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
												NEbins, 0, 2000);
				
				
				string hist  = Form("E - %5.4f >> bst_E_l%d_%s_%s", fmass[fp], l+1, fpname[fp].c_str(), starget[tindex].c_str());
				
				// sensors
				if(l<2*nreg)
				{
					string layer = Form("layer == %d", l+1);
					string cut   = layer + " && " + pcut[fpid[fp]] + " && Edep > 0.0 " ;
					
					bstT->Draw(hist.c_str(), cut.c_str());
				}
				
				// chip
				if(l>=2*nreg && l<3*nreg)
				{
					string layer = Form(" && z > %4.3f && z < %4.3f", chip_minz[l-2*nreg], chip_maxz[l-2*nreg]);
					string cut   = "ID==22 && " + pcut[fpid[fp]] + " && Edep > 0.0 " + layer;
					fluxT->Draw(hist.c_str(), cut.c_str());
				}
				
				// regulator
				if(l>=3*nreg)
				{
					string layer = Form(" && z > %4.3f && z < %4.3f", reg_minz[l-3*nreg], reg_maxz[l-3*nreg]);
					string cut   = "ID==23 && " + pcut[fpid[fp]] + " && Edep > 0.0 " + layer;
					fluxT->Draw(hist.c_str(), cut.c_str());
				}
				
				bst_E[l][fp][tindex]->SetDirectory(0);
				
			}
		cout <<	 " done. " << endl << endl;
		c1->Close();
		f.Close();
	}
	else {
		string fname =  "rootfiles/" + starget[tindex] + ".root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());
		
		// total number of entries
		HNHITS = (TH1F*) f.Get("nhits");
		NHITS = HNHITS->GetBinContent(1);
		HNHITS->SetDirectory(0);
		
		// Energy deposited for different particles, layers
		cout << " Getting sensor and chip energy histos for particles"  << endl;
		for(int p=0; p<pnum; p++)
			for(int l=0; l<nbstl; l++)
				for(int e=0; e<NENERGY; e++)
				{
					bst_edep[l][p][e][tindex] = (TH1F*) f.Get(Form("bst_edep_l%d_%s_e%d_%s", l+1, pname[p].c_str(), e, starget[tindex].c_str()));
					bst_edep[l][p][e][tindex]->SetDirectory(0);
				}
		
		// Energy deposited for e.m. , hadronc particles, integrated over all layers
		edep[0][tindex] = (TH1F*) f.Get(Form("edep_em_%s", starget[tindex].c_str()));
		edep[1][tindex] = (TH1F*) f.Get(Form("edep_ha_%s", starget[tindex].c_str()));
		edep[0][tindex]->SetDirectory(0);
		edep[1][tindex]->SetDirectory(0);
		
		// Kinetic Energy (Total Energy minus mass)
		for(int l=0; l<nbstl; l++)
			for(int fp=0; fp<4; fp++)
			{
				bst_E[l][fp][tindex] =(TH1F*) f.Get(Form("bst_E_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()));
				bst_E[l][fp][tindex]->SetDirectory(0);
			}
		
		f.Close();
	}

	
	// from now on all calculations are the same
	double TOT_TIME = NHITS*TWINDOW;
	cout << " Histos initialized with " << NHITS << " entries in " << TOT_TIME << " seconds total time." << endl << endl;
	
	// Defining and filling rates histos based on energy histos
	cout << " Now defining and filling BST rates histos for target " << starget[tindex] << "..." << endl; ;
	for(int l=0; l<nbstl; l++)
		for(int e=0; e<NENERGY; e++)
		{
			bst_pr[l][e][tindex] = new TH1F(Form("bst_rates_l%d_e%d_%s", l+1, e, starget[tindex].c_str()),
											Form("bst_rates_l%d_e%d_%s", l+1, e, starget[tindex].c_str()), pnum+2, 0, pnum+2);
			bst_pr[l][e][tindex]->GetXaxis()->SetTickLength(0);
			bst_pr[l][e][tindex]->GetXaxis()->SetLabelSize(0);
			bst_pr[l][e][tindex]->SetFillStyle(2);
			bst_pr[l][e][tindex]->SetDirectory(0);
		}
	
	for(int l=0; l<nbstl; l++)
		for(int p=0; p<pnum; p++)
			for(int e=0; e<NENERGY; e++)
			{
				// fill the noise level according to the function:
				// An MIP releases 108 KeV - or 240000 electrons
				// That's 222.2 electrons / KeV
				// Qnoise is 2400 electrons
				double expo     = exp(-Qth[e]*Qth[e]/(2.0*Qn*Qn/4.0));  // factor of 2 each sigma cause sigma is 1/2 FWHM
				double noisrate = expo/(4.0*sqrt(3)*(TWINDOW));
				// cout << e + 1 << "  expo: " << expo << "  noisrate: " << noisrate << endl;
				
				if(p==0) bst_pr[l][e][tindex]->SetBinContent(p+2, noisrate*2680.0);
				else     bst_pr[l][e][tindex]->SetBinContent(p+2, bst_edep[l][p][e][tindex]->GetEntries()/TOT_TIME);
				if(e==0 && l==0 && p>0)
					cout << " Layer 1 number of " << pname[p] << " in " << TOT_TIME << " seconds: " << bst_edep[0][p][0][tindex]->GetEntries() << endl;
				if(e==0 && l==0 && p==0)
					cout << " Layer 1 number of " << pname[p] << " in " << TOT_TIME << " seconds: " << noisrate*TOT_TIME << endl;
				
			}
	
	
	// integrating electromagnetic and hadronic rates
	// attention: particles indexes are hardcoded
	for(int l=0; l<nbstl; l++)
		for(int e=0; e<NENERGY; e++)
		{
			// e.m. rates
			Hrate_bst[l][e][tindex][0] = bst_edep[l][2][e][tindex]->GetEntries()/TOT_TIME +   // e-
			bst_edep[l][3][e][tindex]->GetEntries()/TOT_TIME +   // gamma
			bst_edep[l][5][e][tindex]->GetEntries()/TOT_TIME ;   // e+
			
			// hadronic rates = all - e.m. - noise
			Hrate_bst[l][e][tindex][1] = bst_edep[l][pnum-1][e][tindex]->GetEntries()/TOT_TIME -
			Hrate_bst[l][e][tindex][0] - bst_edep[l][0][e][tindex]->GetEntries()/TOT_TIME;
			
		}
	
	cout << " done. " << endl << endl;
	
	
	cout << " Now filling BST fluence infos for target " << starget[tindex] << "..." ;
	for(int l=0; l<nbstl; l++)
	{
		// sensor
		double area   = nmodules[l]*sarea;
		double weight = nmodules[l]*sweight;
		
		// chip
		if(l>=2*nreg && l<3*nreg)
		{
			area   = nmodules[l]*chip_area;
			weight = nmodules[l]*chip_weight;
		}
		
		// regulators
		if(l>=3*nreg)
		{
			area   = nmodules[l]*reg_area;
			weight = nmodules[l]*reg_weight;
		}
		
		
		
		
		// total energy rate (in GeV)
		for(int p=0; p<pnum; p++)
		{
			erate_bst[p][l][tindex] = 0;
			for(int b=0; b<Nbins; b++)
			{
				// 1000 to have it in GeV
				erate_bst[p][l][tindex] += bst_edep[l][p][0][tindex]->GetBinContent(b+1)*bst_edep[l][p][0][tindex]->GetBinCenter(b+1)/TOT_TIME/1000;
			}
			enrat_bst[p][l][tindex] = erate_bst[p][l][tindex] / area;            // (GeV) / s cm2
			drate_bst[p][l][tindex] = erate_bst[p][l][tindex] / weight / mrad;   // mrad  / s
			dnrat_bst[p][l][tindex] = drate_bst[p][l][tindex] / area;            // mrad  / s cm2
			dryat_bst[p][l][tindex] = drate_bst[p][l][tindex]*one_year/1000;     // rad / year
			dnyra_bst[p][l][tindex] = dnrat_bst[p][l][tindex]*one_year/1000;     // rad / year cm2
		}
	}
	cout << " done. " << endl << endl;
	
	
	print_fluences(0, tindex);
	
	
	cout << " Now creating and filling BST 1 MeV neutron equivalent fluence histos, infos for target " << starget[tindex] << "..." ;
	// see http://sesam.desy.de/members/gunnar/Si-dfuncs.html
	for(int l=0; l<nbstl; l++)
		for(int fp=0; fp<4; fp++)
		{
			// number of particles NP binned according to the induced damage tables energy
			bst_NE[l][fp][tindex] = new TH1F(Form("bst_NE_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
											 Form("bst_NE_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
											 15, 0, 15);
			
			// neutron equivalent rates: it's NP*induced_damage(energy).
			bst_NNE[l][fp][tindex] = new TH1F(Form("bst_NNE_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
											  Form("bst_NNE_l%d_%s_%s", l+1, fpname[fp].c_str(), starget[tindex].c_str()),
											  15, 0, 15);
			
			bst_NE[l][fp][tindex]->SetDirectory(0);
			bst_NNE[l][fp][tindex]->SetDirectory(0);
		}
	

	
	// ######################################
	// Filling 1 MeV Neutron Equivalent rates
	for(int l=0; l<nbstl; l++)
		for(int e=0; e<15; e++)
			for(int fp=0; fp<4; fp++)
			{
				int min_bin = 0;
				int max_bin = NEbins;
				int i = 1;
				
				while(bst_E[l][fp][tindex]->GetBinCenter(i++) <= min_e_induced_damage[fp][e])
					min_bin = i-1;
				i=NEbins;
				while(bst_E[l][fp][tindex]->GetBinCenter(i--) >= max_e_induced_damage[fp][e])
					max_bin = i;
				
				if(min_bin != 0 || max_bin != NEbins)
					n_equivalent_e[l][fp][e] = bst_E[l][fp][tindex]->Integral(min_bin, max_bin)/TOT_TIME/1000000;
				bst_NE[l][fp][tindex]->SetBinContent(e+1,  n_equivalent_e[l][fp][e]);
				bst_NNE[l][fp][tindex]->SetBinContent(e+1, n_equivalent_e[l][fp][e]*induced_damage[fp][e]);
				
				
			}
	cout << " done. " << endl << endl;
	print_damage_rates(0, tindex);
	
	
	// ######################
	// Writing out all histos 
	if(recalc == 1)
	{
		string fname = Form("rootfiles/%s.root", starget[tindex].c_str());
		cout << endl << " Writing all histos in " << fname << " ";
		TFile of(fname.c_str(), "RECREATE");
		
		for(int p=0; p<pnum; p++)
			for(int l=0; l<nbstl; l++)
				for(int e=0; e<NENERGY; e++)
					bst_edep[l][p][e][tindex]->Write();
		
		edep[0][tindex]->Write();
		edep[1][tindex]->Write();
		
		for(int l=0; l<nbstl; l++)
			for(int fp=0; fp<4; fp++)
			{			
				bst_E[l][fp][tindex]->Write();	
			}
		
		
		// Number of events histos
		HNHITS->Write();
		
		of.Close();
	}
	cout << "done." << endl << endl;
	
}





