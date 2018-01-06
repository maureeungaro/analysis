void print_all()
{
	PRINT = ".jpg";
	
	for(int l=0; l<nbstl; l++)
	{
		LAYER = l+1;
		show_bst_rates();
	}
	PRINT = "";

}

void change_layer()
{
	LAYER++;
	if(LAYER > nbstl) LAYER=1;
	cout << " Layer changed to: " << LAYER << endl;
}

void change_energy()
{
	ENERGY++;
	if(ENERGY == NENERGY) ENERGY=0;
	cout << " Energy cut changed to: " << EDEP[ENERGY] << endl;
}

void change_target()
{
	TARGET++;
	if(TARGET == NTARGET) TARGET=0;
	cout << " Target changed to: " << starget[TARGET] << endl;
}

void show_rates_in_layer()
{
	int l = LAYER-1;
	cout << " ------ " << endl;
	cout << "   " << lname[l] << endl;
	cout << " ------ " << endl << endl;
	cout << " target " << "     GeV/s " << "  GeV/(s cm2) " << "    mrad/s " << "    mrad/(scm2) " << "  rad/year " << "  rad/(year cm2) " << endl << endl;
	cout.precision(6);
	for(int t=0; t<NTARGET; t++)
	{
		cout << setw(6) << starget[t] << "\t"
		<< setw(10) << (int) erate_bst[pnum-1][l][t]
		<< setw(12) << enrat_bst[pnum-1][l][t]
		<< setw(14) << drate_bst[pnum-1][l][t]
		<< setw(15) << dnrat_bst[pnum-1][l][t]
		<< setw(12) << (int) dryat_bst[pnum-1][l][t]
		<< setw(10) << (int) dnyra_bst[pnum-1][l][t] << endl ;
	}
	
	cout << endl;
	
}

void show_rates_in_all_layers()
{
	int t = TARGET;
	cout << " ------ " << endl;
	cout << " target " << "     GeV/s " << "  GeV/(s cm2) " << "    mrad/s " << "    mrad/(scm2) " << "  rad/year " << "  rad/(year cm2) " << endl << endl;
	cout.precision(6);
	for(int l=0; l<nbstl; l++)
	{
		cout << setw(6) << lname[l] << "\t"
		<< setw(10) << (int) erate_bst[pnum-1][l][t]
		<< setw(12) << enrat_bst[pnum-1][l][t]
		<< setw(14) << drate_bst[pnum-1][l][t]
		<< setw(15) << dnrat_bst[pnum-1][l][t]
		<< setw(12) << (int) dryat_bst[pnum-1][l][t]
		<< setw(10) << (int) dnyra_bst[pnum-1][l][t] << endl ;
	}
	
	cout << endl;
	
}




void show_rates_in_layers()
{
	
	int t = TARGET;
	int e = ENERGY;

	cout << " ------------------- " << endl;
	cout << " " << starget[t] << "   " <<  EDEP[ENERGY] << endl;
	cout << " ------------------- " << endl << endl;
	cout << " layer " << "        e.m.  " << "    hadronic" << endl << endl;
	cout.precision(5);
	for(int l=0; l<nbstl; l++)
	{
		cout << setw(6) << lname[l] << "\t"
		<< setw(12) << Hrate_bst[l][e][t][0] << "  " 
		<< setw(12) << Hrate_bst[l][e][t][1] << endl;
	}
	
	cout << endl;
	
}


void init_induced_damage()
{

	ifstream in("ElectronsMinMaxMeanDam.txt");
	for(int i=0; i<15; i++)
		in >> min_e_induced_damage[0][i] >> max_e_induced_damage[0][i] >> induced_damage[0][i];
	in.close();

	in.open("PionsMinMaxMeanDam.txt");
	for(int i=0; i<15; i++)
		in >> min_e_induced_damage[1][i] >> max_e_induced_damage[1][i] >> induced_damage[1][i];
	in.close();
	
	in.open("NeutronMinMaxMean.txt");
	for(int i=0; i<15; i++)
		in >> min_e_induced_damage[2][i] >> max_e_induced_damage[2][i] >> induced_damage[2][i];
	in.close();
	
	in.open("ProtonsMinMaxMeanDam.txt");
	for(int i=0; i<15; i++)
		in >> min_e_induced_damage[3][i] >> max_e_induced_damage[3][i] >> induced_damage[3][i];
	in.close();
}




void show_dist(int what)
{

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.2);
	gStyle->SetPadTopMargin(0.14);
	gStyle->SetPadBottomMargin(0.14);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);
	lab.SetNDC();

	TCanvas *dist  = new TCanvas("dist", "dist", 800, 500);

	int layer = LAYER-1;

	string wdist[4] = {"y_vs_z", "y_vs_th", "modules", "z"};
	int windex;
	if(what == 0)   windex = 0;
	if(what == 1)   windex = 1;
	if(what == 10)  windex = 2;
	if(what == 100) windex = 3;

	double fac[3];

	if(what==0)  
	{
		yz[layer][ENERGY]->Draw("colz");
	}
	
	if(what==1)  
	{
		yt[layer][ENERGY]->Draw("colz");
	}
	
	if(what==10) 
	{
		yzm[layer][ENERGY]->Draw("colz");
		for(int m=0; m<3; m++)
		{
		 fac[m] = yzm[layer][ENERGY]->GetBinContent(m+1, 1);
		}
		
		lab.DrawLatex(0.17, 0.5, Form("%4.2f MHz",  fac[0]/1000000 ));
		lab.DrawLatex(0.42, 0.5, Form("%4.2f MHz",  fac[1]/1000000 ));
		lab.DrawLatex(0.65, 0.5, Form("%4.2f MHz",  fac[2]/1000000 ));
	}
	
	if(what==20) 
	{
		ytm[layer][ENERGY][ENERGY]->Draw("colz");
		for(int m=0; m<3; m++)
		{
		 fac[m] = yzm[layer]->GetBinContent(m+1, 1)*100;
		}
		
		lab.DrawLatex(0.22, 0.5, Form("%4.2f %%",  fac[0] ));
		lab.DrawLatex(0.47, 0.5, Form("%4.2f %%",  fac[1] ));
		lab.DrawLatex(0.70, 0.5, Form("%4.2f %%",  fac[2] ));
	}	

	if(what==100)  
	{
		double zminnbin = zpos[layer][ENERGY]->GetBinCenter(zpos[layer][ENERGY]->GetMinimumBin());
		double zmaxnbin = zpos[layer][ENERGY]->GetBinCenter(zpos[layer][ENERGY]->GetMaximumBin());
		zpos[layer][ENERGY]->Fit("expo", "REM", "", zminnbin+20, zmaxnbin-40);
	
		lab.DrawLatex(0.85, 0.67, "y = e^{A+Bx}");
		lab.DrawLatex(0.85, 0.60, Form("A = %4.2f %", zpos[layer][ENERGY]->GetFunction("expo")->GetParameter(0)  ));
		lab.DrawLatex(0.85, 0.53, Form("B = %4.2f %", zpos[layer][ENERGY]->GetFunction("expo")->GetParameter(1)  ));
		
	}
																	


	lab.SetTextSize(0.07);
	lab.DrawLatex(0.35, 0.90, Form("Layer %d   E>%2.0f KeV",  layer + 1,  EVAL[ENERGY]*1000 ));

	lab.SetTextSize(0.05);
	lab.SetTextColor(kBlack);
	if(what == 0 || what == 10|| what == 100)
		lab.DrawLatex(0.72, 0.04, "z  [mm]");

	if(what == 1 || what == 20 )
		lab.DrawLatex(0.72, 0.03, "#theta  [mm]");

	if(what != 100 && what !=10)
	{
		lab.DrawLatex(0.86, 0.88, "Hz");
		lab.SetTextAngle(90);
		lab.DrawLatex(0.06, 0.7, "y    [mm]");
	}


	dist->Print(Form("%s_l%s_Egt%dKeV.gif", wdist[windex], lname[layer], ((int) (EVAL[ENERGY]*1000))));
}


void print_all_dist()
{

	for(int l=0; l<nbstl; l++)
		for(int e=0; e<NENERGY; e++)
		{
			LAYER = l+1;
			ENERGY = e;
			show_dist(0);
			show_dist(1);
			show_dist(10);
			show_dist(100);
		}

}


void show_energy(int rebin)
{

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.14);
	gStyle->SetPadBottomMargin(0.14);

	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetNDC();


	Color_t fcol[2] = { kBlue, kRed+2};
	TCanvas *dist  = new TCanvas("dist", "dist", 800, 500);

	int layer = LAYER-1;
	
	gPad->SetLogy();

	TH1F *flux[2];

	for(int f=0; f<2; f++)
	{
		flux[f] = (TH1F*) edep[f][TARGET]->Clone();

		if(rebin) flux[f]->Rebin(rebin);
		flux[f]->SetBinContent(1, 0);
		flux[f]->SetLineColor(fcol[f]);
		flux[f]->SetMinimum(0.1);
	}
	
	TH1F *SUM =  (TH1F*) flux[0]->Clone();
	SUM->Add(flux[1]);
	SUM->SetBinContent(1, 0);
	SUM->SetLineColor(kBlack);
	SUM->SetLineStyle(2);	
	
	
	flux[0]->Draw();
	flux[1]->Draw("same");


	SUM->Draw("same");



	TLegend *tmodels  = new TLegend(0.6, 0.65, 0.85, 0.85);
	tmodels->AddEntry(flux[0], "Electromagnetic",  "L");
	tmodels->AddEntry(flux[1], "Hadronic",         "L");
	tmodels->AddEntry(SUM,     "All",              "L");
	tmodels->Draw();


	lab.SetTextFont(32);
	lab.SetTextSize(0.09);
	lab.DrawLatex(0.2, 0.9, Form("Energy Deposited in Layer %d",  layer + 1 ));
	
	
	lab.SetTextSize(0.05);
	lab.DrawLatex(0.76, 0.035, "E  [MeV]");


}


void print_fluences(int l, int tindex)
{
	
	cout << " ------------" << endl;
	cout << " " << starget[tindex] << endl;
	cout << " Layer " <<  lname [l] << " Fluences: " << endl;
	cout << " ------------ " << endl << endl;
	cout << " particles " << "       GeV/s  " << "    mrad/s " <<  "     rad/year " << endl << endl;
	cout.precision(6);
	for(int p=1; p<pnum; p++)
	{
		cout << "  " << pname[p] << "\t"
		<< setw(13) << (int) erate_bst[p][l][tindex]
		<< setw(14) <<       drate_bst[p][l][tindex]
		<< setw(12) << (int) dryat_bst[p][l][tindex] << endl ;
	}
	cout << endl;
}

void print_all_fluences()
{
	for(int l=0; l<nbstl; l++)
	{
		for(int t=0; t<NTARGET; t++)
		{
			print_fluences(l, t);
		}
	}
}

void print_damage_rates(int l, int tindex)
{
	cout << " ------ " << endl;
	cout << "   " << starget[tindex] << endl;
	cout << " Layer " << lname[l] << " damage rates " << endl;
	cout << " ------ " << endl << endl;
	cout << " particle " << "       rate (MHz)" << "   1 MeV Neutron Damage Rate (MHz)" << endl << endl;
	cout.precision(6);
	
	cout << "      e-     \t"
	<< setw(10) <<  bst_NE[l][0][tindex]->Integral()
	<< setw(14) << bst_NNE[l][0][tindex]->Integral() << endl ;
	cout << "     pions   \t"
	<< setw(10) <<  bst_NE[l][1][tindex]->Integral()
	<< setw(14) << bst_NNE[l][1][tindex]->Integral() << endl ;
	cout << "    neutrons \t"
	<< setw(10) <<  bst_NE[l][2][tindex]->Integral()
	<< setw(14) << bst_NNE[l][2][tindex]->Integral() << endl ;
	cout << "    protons  \t"
	<< setw(10) <<  bst_NE[l][3][tindex]->Integral()
	<< setw(14) << bst_NNE[l][3][tindex]->Integral() << endl ;
	cout << "    Total:  \t"
	<< setw(10) << bst_NE[l][0][tindex]->Integral() +
	bst_NE[l][1][tindex]->Integral() +
	bst_NE[l][2][tindex]->Integral() +
	bst_NE[l][3][tindex]->Integral()
	<< setw(14) << bst_NNE[0][0][tindex]->Integral() +
	bst_NNE[l][1][tindex]->Integral() +
	bst_NNE[l][2][tindex]->Integral() +
	bst_NNE[l][3][tindex]->Integral()
	<< endl ;
	
}

void print_all_damage_rates()
{
	for(int l=0; l<nbstl; l++)
	{
		for(int t=0; t<NTARGET; t++)
		{
			print_damage_rates(l, t);
		}
	}
}

void print_all_rates()
{
	PRINT = "gif";
	for(int l=0; l<nbstl; l++)
	{
		LAYER = l+1;
		for(int e=0; e<NENERGY; e++)
		{
			ENERGY = e;
			for(int t=0; t<NTARGET; t++)
			{
				TARGET = t;
				show_bst_rates();
			}
		}
	}
}


void print_all_events()
{
	PRINT = "gif";
	for(int l=0; l<nbstl; l++)
	{
		LAYER = l+1;
		for(int e=0; e<NENERGY; e++)
		{
			ENERGY = e;
			for(int t=0; t<NTARGET; t++)
			{
				TARGET = t;
				show_bst_event();
			}
		}
	}
}



void print_all_targets_rates()
{
	PRINT = "gif";
	for(int l=0; l<nbstl; l++)
	{
		LAYER = l+1;
		for(int e=0; e<NENERGY; e++)
		{
			ENERGY = e;
			show_all_bst_rates();
		}
	}
}


void print_all_targets_events()
{
	PRINT = "gif";
	for(int l=0; l<nbstl; l++)
	{
		LAYER = l+1;
		for(int e=0; e<NENERGY; e++)
		{
			ENERGY = e;
			show_all_bst_event();
		}
	}
}









