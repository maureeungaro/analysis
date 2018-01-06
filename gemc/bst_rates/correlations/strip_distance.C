{

	double MIN_ENERGY = 0.02; 

	const int nreg  = 4; 
	const int nbstl = 2*nreg;  // 2 layers of silicon for each region. Only one region considered for the chips 
	const int ns_lay[nbstl] = {10, 10, 14, 14, 18, 18, 24, 24};
	const int max_nsect     = 24;
	
	int NSTRIP = 268;

	TH1F *r_cor[nreg];      // probability of having background hitting both layers (same sector) in a region - for different regions

	for(int r=0; r<nreg; r++)
	{
		r_cor[r] = new TH1F(Form("r%d", r+1),
											  Form("r%d", r+1),
												NSTRIP, -NSTRIP, NSTRIP);
	}
	
	double s_hits[nbstl][max_nsect];
	
	// BST Hits 
	int    nbsthit;
	int layer[10000];
	int sector[10000];
	int strip[10000];
	
	
	TFile *bfile = new TFile("/opt/projects/analysis/gemc_farm/targets/protons.root");
	//TFile *bfile = new TFile("/arena/BST/root/protons.root");
	TTree *bbstT = (TTree*)bfile->Get("bstT");
	bbstT->SetBranchAddress("nbsthit",   &nbsthit);
	bbstT->SetBranchAddress("layer",     layer);
	bbstT->SetBranchAddress("sector",    sector);
	bbstT->SetBranchAddress("strip",     strip);
		
			
	int NEVENTS = genT->GetEntries();
	cout << " Number of events " << NEVENTS << endl;
	int NCOUNTS = NEVENTS;
			
	for(int e=1; e<=NCOUNTS; e++)
	{
		bstT->GetEntry(e);
		if(e%1000 == 0) 
			cout << "  evn: " << e << endl;
						
		for(int l=0; l<nbstl; l++)
			for(int s=0; s<ns_lay[l]; s++)
			{
				s_hits[l][s] = 0;
				
				// averaging the strip number
				double strip_avg   = 0;
				double strip_count = 0;
				for(int h=0; h<nbsthit; h++)
				{
					if(layer[h] == l+1 && sector[h] == s+1 && strip[h]>0)
					{
						strip_avg += strip[h];
						strip_count++;
						 //cout << " layer: " << l+1 << "  sector: " << s+1 << " strip: " << strip[h] << endl;
					}
				}
				if(strip_count)
				{
					strip_avg = strip_avg/strip_count;
					// cout << " count: " << strip_count <<  " average strip: " << strip_avg << endl;
					s_hits[l][s] = strip_avg;	
				}
			}
			
		for(int r=0; r<nreg; r++)
			for(int s=0; s<ns_lay[2*r]; s++)
		{
			//shir_cor[r]->Fill(s_hits[2*r+1] - s_hits[2*r]);
			if(s_hits[2*r+1][s] && s_hits[2*r][s]) 
			{
				r_cor[r]->Fill(s_hits[2*r+1][s] + s_hits[2*r][s] - 268);
				//cout << " difference for r: " << r+1 << "  " << s_hits[2*r+1][s] << " - " << s_hits[2*r][s] << endl;
			}
		}	
			
	}				
			
	

}



