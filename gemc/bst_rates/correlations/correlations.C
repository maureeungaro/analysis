{


	const int NENERGY     = 4;
	double EDEP[NENERGY]  = {0, 0.02, 0.04, 0.06};
	string SEDEP[NENERGY] = {"0KeV", "20KeV", "40KeV", "60KeV"};
	int ENERGY           = 0; 

	const int nreg  = 4; 
	const int nbstl = 2*nreg;  // 2 layers of silicon for each region. Only one region considered for the chips 
	const int ns_reg[nreg]  = {    10,     14,     18,     24};
	const int ns_lay[nbstl] = {10, 10, 14, 14, 18, 18, 24, 24};
	const int max_nsect     = 24;
	int REGION = 0;

	const int NTARGET     = 5;
	string starget[NTARGET] = { "lh2"   ,  "ld2"  , "carbon"  , "iron"   , "lead"};
	Color_t colors[NTARGET] = { kBlue-7 ,  kRed+1 , kOrange+1 , kGreen-8 ,  kBlue};
	int TARGET = 0;
//	const int NTARGET     = 1;
//	string starget[NTARGET] = { "lh2"   };
//	Color_t colors[NTARGET] = { kBlue-7 };
//	int TARGET = 0;
	 

	TH1F *r_cor[nreg][NENERGY][NTARGET];  // probability of having background hitting both layers (same sector) in a region - for different regions
	TH1F *d_cor[nreg][NENERGY][NTARGET];  // ratio of double hits to total hits
	
	for(int t=0; t<NTARGET; t++)
	for(int c=0; c<NENERGY; c++)
		for(int r=0; r<nreg; r++)
		{
			r_cor[r][c][t] = new TH1F(Form("r%d_%s_%s", r+1, SEDEP[c], starget[t]),
			                          Form("r%d_%s_%s", r+1, SEDEP[c], starget[t]),
														    ns_reg[r], 0.5, ns_reg[r]+0.5);
			d_cor[r][c][t] = new TH1F(Form("d_r%d_%s_%s", r+1, SEDEP[c], starget[t]),
			                          Form("d_r%d_%s_%s", r+1, SEDEP[c], starget[t]),
														    ns_reg[r], 0.5, ns_reg[r]+0.5);
		}
	
	// BST Hits 
	int    nbsthit;
	int layer[10000];
	int sector[10000];
	float edep[10000];
	int strip[10000];
	float max_strip_diff = 100; // max strip difference to be considered a double hit

	int DEBUG  = 0;
	int REREAD = 1;
	
	if(REREAD)
	{
		for(int t=0; t<NTARGET; t++)
		{
			TFile *bfile = new TFile(Form("/arena/BST/root/%s.root", starget[t]));
			TTree *bbstT = (TTree*)bfile->Get("bstT");
			
			bbstT->SetBranchAddress("nbsthit",   &nbsthit);
			bbstT->SetBranchAddress("layer",     layer);
			bbstT->SetBranchAddress("sector",    sector);
			bbstT->SetBranchAddress("strip",     strip);
			bbstT->SetBranchAddress("Edep",      edep);
			
			
			int NEVENTS = genT->GetEntries();
			cout << " Number of events " << NEVENTS << endl;
			int NCOUNTS = NEVENTS;
			int tot_nhits[nbstl][NENERGY] = { 0 };  // total number of hits in a region
						
			for(int e=1; e<=NCOUNTS; e++)
			{
				bstT->GetEntry(e);
				
				if(e%100 == 0) cout << " Target: " << starget[t] << " evn: " << e << endl;
				double nh_lay[max_nsect][nbstl][NENERGY] = { 0 };
				double nh_reg[max_nsect][nreg][NENERGY]  = { 0 };
				double h_strip[max_nsect][nbstl]         = { 0 };
				
				for(int h=0; h<nbsthit; h++)
				{
					h_strip[sector[h]-1][layer[h]-1] = strip[h];
					
					// filling array when E >= EDEP
					for(int c=0; c<NENERGY; c++)
						if(edep[h] >= EDEP[c]) 
							nh_lay[sector[h]-1][layer[h]-1][c]++ ;
					
					
					// DEBUG ONLY
					if(DEBUG == 2) 
					{ 
						cout << " layer: " << layer[h] << "    sector: " << sector[h] << "  energy: " << edep[h] << endl;
						for(int c=0; c<NENERGY; c++)
							for(int s=0; s<ns_lay[layer[h]-1]; s++)
							{
								cout << " l: " << layer[h]-1 << "   s: " << s << " energy: " << EDEP[c] << "  nhits: " << nh_lay[s][layer[h]-1][c] << endl;
							}
					}
					
					// end of hits loop
				}
				
				// adding number of hits in each sector
				for(int c=0; c<NENERGY; c++)
					for(int r=0; r<nreg; r++)
						for(int s=0; s<ns_lay[r]; s++)
							{
								tot_nhits[r][c] += nh_lay[s][2*r][c];
								tot_nhits[r][c] += nh_lay[s][2*r+1][c];
							}
							
				// Print LAYER Summary
				if(DEBUG == 1) 
				{
					for(int c=0; c<NENERGY; c++)
						for(int l=0; l<nbstl; l++)
							for(int s=0; s<ns_lay[l]; s++)
								cout << " l: " << l << "   s: " << s << " energy: " << EDEP[c] << "  nhits: " << nh_lay[s][l][c] << endl;
				}
				
				
				// filling the histos if there are hits in both layers of a region
				for(int c=0; c<NENERGY; c++)
					for(int r=0; r<nreg; r++)
						for(int s=0; s<ns_reg[r]; s++)
						{
							if(nh_lay[s][2*r][c] > 0 && nh_lay[s][2*r+1][c]>0 && abs(h_strip[s][2*r] - h_strip[s][2*r+1]) < max_strip_diff)
								nh_reg[s][r][c]++;
						}		
				
				// Print REGION Summary
				if(DEBUG == 10) 
				{
					for(int c=0; c<NENERGY; c++)
						for(int r=0; r<nreg; r++)
							for(int s=0; s<ns_reg[r]; s++)
								cout << " r: " << r << "   s: " << s << " energy: " << EDEP[c] << "  nhits: " << nh_reg[s][r][c] << "  ntothits: " << tot_nhits[r][c] << endl;
					
				}
				
				// filling the histos if there's a double hit
				for(int c=0; c<NENERGY; c++)
					for(int r=0; r<nreg; r++)
						for(int s=0; s<ns_reg[r]; s++)
							for(int nh=0; nh<nh_reg[s][r][c]; nh++)
							{
								r_cor[r][c][t]->Fill(s+1);
								d_cor[r][c][t]->Fill(s+1);
							}
				
				
				// end of event loop
			}
			
			for(int c=0; c<NENERGY; c++)
				for(int r=0; r<nreg; r++)
				{	
					r_cor[r][c][t]->Sumw2();
					r_cor[r][c][t]->Scale(100.0/NCOUNTS);	
					r_cor[r][c][t]->SetMinimum(0);	
					r_cor[r][c][t]->SetDirectory(0);
					
					d_cor[r][c][t]->Sumw2();
					if(tot_nhits[r][c]) d_cor[r][c][t]->Scale(100.0/tot_nhits[r][c]);
					else 	              d_cor[r][c][t]->Scale(0);
					d_cor[r][c][t]->SetMinimum(0);	
					d_cor[r][c][t]->SetDirectory(0);
				}
			
			bfile->Close();	
		}
		
		// saving all histos
		TFile ff("../rootfiles/correlations.root", "RECREATE");
		for(int c=0; c<NENERGY; c++)
			for(int r=0; r<nreg; r++)
				for(int t=0; t<NTARGET; t++)
				{
					r_cor[r][c][t]->Write();
					d_cor[r][c][t]->Write();
				}
		ff.Close();
	}
	else
	{
		TFile f("../rootfiles/correlations.root");
		for(int c=0; c<NENERGY; c++)
			for(int r=0; r<nreg; r++)
				for(int t=0; t<NTARGET; t++)
				{
					r_cor[r][c][t] = (TH1F*) f.Get(Form("r%d_%s_%s", r+1, SEDEP[c], starget[t]));			
					r_cor[r][c][t]->SetDirectory(0);
					d_cor[r][c][t] = (TH1F*) f.Get(Form("d_r%d_%s_%s", r+1, SEDEP[c], starget[t]));			
					d_cor[r][c][t]->SetDirectory(0);
				}
		f.Close();
		
	}	
	
	
	
	
	gROOT->LoadMacro("correlation_util.C");

}



