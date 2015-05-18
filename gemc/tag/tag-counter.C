{
	TFile finp(Form("in.root"));
	TFile fout(Form("out.root"), "RECREATE");
	

	// DC Hits
	vector<double>   *dcTotE  = 0;    // sector
	vector<double>   *dcS     = 0;    // sector
	vector<double>   *dcSL    = 0;    // superlayer
	vector<double>   *dcL     = 0;    // layer
	vector<double>   *dcpid   = 0;    // pid
	vector<double>   *dcmpid  = 0;    // mother pid
	vector<double>   *dcpx    = 0;    // mom x
	vector<double>   *dcpy    = 0;    // mom y
	vector<double>   *dcpz    = 0;    // mom z
	vector<double>   *dcvx    = 0;    // vertex x
	vector<double>   *dcvy    = 0;    // vertex y
	vector<double>   *dcvz    = 0;    // vertex z
	vector<double>   *avg_t   = 0;    // time
	
	TTree *dcT  = (TTree*)finp.Get("dc");
	dcT->SetBranchAddress("totEdep",     &dcTotE);
	dcT->SetBranchAddress("sector",      &dcS);
	dcT->SetBranchAddress("superlayer",  &dcSL);
	dcT->SetBranchAddress("layer",       &dcL);
	dcT->SetBranchAddress("pid",         &dcpid);
	dcT->SetBranchAddress("mpid",        &dcmpid);
	dcT->SetBranchAddress("px",          &dcpx);
	dcT->SetBranchAddress("py",          &dcpy);
	dcT->SetBranchAddress("pz",          &dcpz);
	dcT->SetBranchAddress("vx",          &dcvx);
	dcT->SetBranchAddress("vy",          &dcvy);
	dcT->SetBranchAddress("vz",          &dcvz);
	dcT->SetBranchAddress("avg_t",       &avg_t);
	
	
	
	// header
	vector<double> *evn = 0;        // input evn

	TTree *headerT  = (TTree*)finp.Get("header");
	headerT->SetBranchAddress("evn",  &evn);
	
	
	int evn2;               // output evn, same as input but it needs a different address
	vector<double> pid;     // pid of accepted particle
	vector<double> mom;     // momentum
	vector<double> theta;   // theta
	vector<double> coinc;   // 1 or 2 particles at the same time
	vector<double> vx;      // vertex x
	vector<double> vy;      // vertex y
	vector<double> vz;      // vertex z
	vector<double> time;    // time
	
	TTree *out = new TTree("out", "accepted particles");
	out->Branch("evn",    &evn2);
	out->Branch("pid",    &pid);
	out->Branch("mom",    &mom);
	out->Branch("theta",  &theta);
	out->Branch("coinc",  &coinc);
	out->Branch("vx",     &vx);
	out->Branch("vy",     &vy);
	out->Branch("vz",     &vz);
	out->Branch("time",   &time);
	
	
	int NPART  = 2;
	int PARTID[NPART] = {211, -211};
	
	for(int i=0; i<dcT->GetEntries(); i++)
	{
		headerT->GetEntry(i);
		dcT->GetEntry(i);
		
		if(evn->size() ==1) evn2 = (*evn)[0];
		
		pid.clear();
		mom.clear();
		theta.clear();
		coinc.clear();
		vx.clear();
		vy.clear();
		vz.clear();
		time.clear();
		double coincidence = 0;
		
		// when counting particles, we're assuming only 1 of a kind
		// in each event.
		// if we have hit in 5 out of 6 SL above the energy threshold
		// the we count that as 1.
		for(int p=0; p<NPART; p++)
		{
			double momentum   = 0;
			double thetaangle = 0;
			double vtx        = 0;
			double vty        = 0;
			double vtz        = 0;
			double dtime      = 0;
			
			// init DC count
			int dc_hits[6][6][6];       // layer superlayer sector
			for(int l=0; l<6; l++)
				for(int sl=0; sl<6; sl++)
					for(int ss=0; ss<6; ss++)
						dc_hits[l][sl][ss] = 0;

			// looping over dchits
			for(unsigned d=0; d<(*dcpid).size(); d++)
			{
				// DC count set to 1 for hit in that layer / sector
				if((*dcpid)[d] == PARTID[p] || (*dcmpid)[d] == PARTID[p])
				{
					int thisLayer      = (*dcL)[d];
					int thisSuperLayer = (*dcSL)[d];
					int thisSector     = (*dcS)[d];
					
					// getting momentum, vertex, time as it enters first region
					if(thisLayer == 1 && thisSuperLayer == 1 && dtime == 0)
					{
						momentum   = sqrt((*dcpx)[d]*(*dcpx)[d] + (*dcpy)[d]*(*dcpy)[d] + (*dcpz)[d]*(*dcpz)[d]);
						thetaangle = acos((*dcpz)[d] / momentum)*180/3.1415;
						vtx        = (*dcvx)[d];
						vty        = (*dcvy)[d];
						vtz        = (*dcvz)[d];
						dtime      = (*avg_t)[d];
					}
					
					dc_hits[thisLayer-1][thisSuperLayer-1][thisSector-1] = 1;
				}
			}
			
			
			// now making segments in each SL and sectors
			int dc_seg[6][6];       // superlayer sector
			for(int sl=0; sl<6; sl++)
				for(int ss=0; ss<6; ss++)
					dc_seg[sl][ss] = 0;
			
			for(int sl=0; sl<6; sl++)
				for(int ss=0; ss<6; ss++)
				{
					int nhitsL = 0;
					for(int l=0; l<6; l++)
						nhitsL += dc_hits[l][sl][ss];
					
					// if we have 5 hits the same layer it's a segment
					if(nhitsL > 4)
						dc_seg[sl][ss] = 1;
				}
			
			
			// now making tracks in each sectors - 5 segments at least
			int dc_track[6];       // sector
			for(int ss=0; ss<6; ss++)
				dc_track[ss] = 0;
			
			for(int ss=0; ss<6; ss++)
			{
				int ntrack = 0;
				for(int sl=0; sl<6; sl++)
					ntrack += dc_seg[sl][ss] ;

				if(ntrack > 4)
					dc_track[ss] = 1;
			}
			
			// now filling up track infos
			for(int ss=0; ss<6; ss++)
			{
				if(dc_track[ss])
				{
					pid.push_back(PARTID[p]);
					mom.push_back(momentum);
					theta.push_back(thetaangle);
					vx.push_back(vtx);
					vy.push_back(vty);
					vz.push_back(vtz);
					time.push_back(dtime);
					coincidence++;
					cout << evn2 << " " << coincidence << endl;
				}
			}
			
		}
		
		if(coincidence && pid.size())
		for(int p=0; p<NPART; p++)
			coinc.push_back(coincidence);

		fout.cd();
		out->Fill();
	}
	
	finp.Close();
	fout.Write();
	fout.Close();

	
}



