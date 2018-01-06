void draw_next_event()
{

	//evni++;
	
	genT->GetEntry(evni);
	bstT->GetEntry(evni);
	bbstT->GetEntry(evni+1);
	
	double interlayer = 3.582;           // distance between 2 layers of a superlayer
	double radii[8] = { 65.117,
	                    65.117 + interlayer,
											92.681,
											92.681 + interlayer,
											119.961,
											119.961 + interlayer,
											160.660,
											160.660 + interlayer};
	double segmentation[8] = {360.0/10, 360.0/10, 360.0/14, 360.0/14, 360.0/18, 360.0/18, 360.0/24, 360.0/24 };
	double start_phi[8]    = {       0,        0,        0,        0, 360.0/36, 360.0/36,        0,        0 };										
	double nstrips = 268;
	double pitch   = 0.150;

	cout << "Event: " << evn << "    N. of BST Hits: " << nbsthit << "    N. Background Hits: " << bnbsthit <<  "   Position of first hit: (" << x[0] << ", " << y[0] << ")" << endl;

	
	double six[100] = { 1000 };
	double siy[100] = { 1000 };
	
	double snix[100] = { 1000 };
	double sniy[100] = { 1000 };

	double fix[10000] = { 1000 };
	double fiy[10000] = { 1000 };
	
	
	for(int h=0; h<nbsthit; h++)
	{
		if(Edep[h]>=EMIN && pid[h] != -99) 
		{
			six[h] = x[h];
			siy[h] = y[h];
		}
	}
	gen_XY = new TGraph(nbsthit, six, siy);
	gen_XY->SetMarkerStyle(21);
	gen_XY->SetMarkerSize(1);
	gen_XY->SetMarkerColor(kBlue);
	
	for(int h=0; h<nbsthit; h++)
	{
		if(Edep[h]>=EMIN && pid[h] == -99) 
		{
			// converting strip to position
			int l = layer[h] - 1;
			int s = sector[h] - 1;
			
			cout << " l: " << l +1 << "    s: " << s+1 <<  "   strip: " << strip[h] << endl;
			
			double xx = -pitch*nstrips/2 + strip[h]*pitch;
			double yy = radii[l];
			
			// rotate by 90 degrees + sector*segmentation
			double phirot = (90 + start_phi[l] + segmentation[l]*s)*3.141592/180.0;
			

			snix[h] = xx*cos(phirot) - yy*sin(phirot);
			sniy[h] = xx*sin(phirot) + yy*cos(phirot);
		}
	}
	genn_XY = new TGraph(nbsthit, snix, sniy);
	genn_XY->SetMarkerStyle(21);
	genn_XY->SetMarkerSize(1);
	genn_XY->SetMarkerColor(kRed+1);
	




	for(int h=0; h<bnbsthit; h++)
	{
		if(bEdep[h]>=EMIN) 
		{
			fix[h] = bax[h];
			fiy[h] = bay[h];
		}
	}
	
	bgen_XY = new TGraph(bnbsthit, fix, fiy);
	bgen_XY->SetMarkerStyle(21);
	bgen_XY->SetMarkerSize(1);
	bgen_XY->SetMarkerColor(kGreen+1);




	bstyx->Draw();
	bgen_XY->Draw("Psame");
	gen_XY->Draw("Psame");
	genn_XY->Draw("Psame");


	

	lab.SetTextSize(0.04);
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(42);
	lab.SetNDC(1);
	lab.DrawLatex(0.16, 0.915, Form("Event Number %d    Edep#geq%3.1f KeV    %s", evni, EMIN*1000, target));


	eventC->Print(Form("ev_n%d_Egt%dKeV_%s.gif", evni, ((int) (EMIN*1000)), target  ));
	
	cout << endl;
	
}





void draw_nevents(int N)
{

	for(int i=0; i<N; i++)
	{
		evni++;
		for(int e=2; e<11; e++)
		{
			EMIN = e*0.01;
			draw_next_event();
			cout << " EMIN: " << EMIN << " evn: " << i +1 << endl;
		}
	}
}



void build_histo()
{
	TFile f("bst.root");
	TTree *bstT = (TTree *) f.Get("bstT");
	TFile ff("bstxy.root", "RECREATE");

	TH2F *bstyx = new TH2F("bstyx", "bstyx", 2000, -200, 200, 2000, -200, 200);
	bstT->Draw("x:y>>bstyx", "Edep>0", "");
	bstyx->Write();
}




