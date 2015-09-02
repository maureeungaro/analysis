{
	
	
	TFile finp(Form("muons.root"));
	TFile fout(Form("muons_acc.root"), "RECREATE");
	
	// header
	vector<double> *evn = 0;        // input evn
	
	TTree *headerT  = (TTree*)finp.Get("header");
	headerT->SetBranchAddress("evn",  &evn);

	
	// generated particles
	TTree *genT = (TTree*)finp.Get("generated");
	vector<double> *gid = 0;
	vector<double> *gpx = 0;   // momentum and energy of generated particle
	vector<double> *gpy = 0;
	vector<double> *gpz = 0;
	
	genT->SetBranchAddress("pid",  &gid);
	genT->SetBranchAddress("px",   &gpx);
	genT->SetBranchAddress("py",   &gpy);
	genT->SetBranchAddress("pz",   &gpz);
	
	
	// DC Hits
	vector<double> *dcTotE = 0;
	vector<double> *dcS    = 0;
	vector<double> *dcSL   = 0;
	vector<double> *dcL    = 0;
	vector<double> *dcpid  = 0;
	vector<double> *dcmpid = 0;
	vector<double> *dctE   = 0;
	vector<double> *dcpx   = 0;    // mom x
	vector<double> *dcpy   = 0;    // mom y
	vector<double> *dcpz   = 0;    // mom z

	
	TTree *dcT  = (TTree*)finp.Get("dc");
	dcT->SetBranchAddress("totEdep",     &dcTotE);
	dcT->SetBranchAddress("sector",      &dcS);
	dcT->SetBranchAddress("superlayer",  &dcSL);
	dcT->SetBranchAddress("layer",       &dcL);
	dcT->SetBranchAddress("pid",         &dcpid);
	dcT->SetBranchAddress("mpid",        &dcmpid);
	dcT->SetBranchAddress("trackE",      &dctE);
	dcT->SetBranchAddress("px",          &dcpx);
	dcT->SetBranchAddress("py",          &dcpy);
	dcT->SetBranchAddress("pz",          &dcpz);

	
	// output
	int evn2;       // output evn, same as input but it needs a different address
	vector<double> pid;     // pid of accepted particle
	vector<double> mom;     // momentum
	vector<double> theta;   // theta
	vector<double> dc;      // dc acceptance
	
	TTree *out = new TTree("out", "accepted particles");
	out->Branch("evn",    &evn2);
	out->Branch("pid",    &pid);
	out->Branch("mom",    &mom);
	out->Branch("theta",  &theta);
	out->Branch("dc",     &dc);
	
	for(int i=0; i<genT->GetEntries(); i++)
	{
		genT->GetEntry(i);
		dcT->GetEntry(i);
		headerT->GetEntry(i);

		if(evn->size() ==1) evn2 = (*evn)[0];
		
		
		pid.clear();
		mom.clear();
		theta.clear();
		dc.clear();

		int ngen = gid.size();
		
		if(evn2%100 == 0)
			cout << " evn: " << evn2 << "... number of gen: " << ngen << endl;
		
		for(int p=0; p<ngen; p++)
		{
			double thisID  = (*gid)[p];
			double genMom  = sqrt((*gpx)[p]*(*gpx)[p] + (*gpy)[p]*(*gpy)[p] + (*gpz)[p]*(*gpz)[p]);
			double theMom  = acos((*gpz)[p]/genMom)*180.0/3.141592;

			
			// DC acceptance
			int dc_la[6][6];
			for(int l=0; l<6; l++)
				for(int sl=0; sl<6; sl++)
					dc_la[l][sl] = 0;
			
			for(unsigned d=0; d<(*dcpid).size(); d++)
			{
				double thisMom = sqrt((*dcpx)[d]*(*dcpx)[d] + (*dcpy)[d]*(*dcpy)[d] + (*dcpz)[d]*(*dcpz)[d]);
				int thisLayer      = (*dcL)[d];
				int thisSuperLayer = (*dcSL)[d];

				// cout << genMom << " " << thisMom << endl;
				
				// if same pid of generated, it's a hit in that layer, superlayer
				if((*dcpid)[d] == thisID && (*dcmpid)[d] == 0 && (*dcTotE)[d] > 0.0001)
				{
					//	if(fabs(dcgE[d] - gE[p]) < 200)
						dc_la[thisLayer-1][thisSuperLayer-1] = 1;
					// cout << dcpid[d] << " " << dcL[d] << " " << dcS[d] << " " << dcSL[d] << " " << dcTotE[d] << endl;
				}
			}
			
			// if at least 5 hit in each superlayer, it's a segment
			int seg[6] = {0, 0, 0, 0, 0, 0};
			for(int sl=0; sl<6; sl++)
			{
				int nhit = 0;
				for(int l=0; l<6; l++)
					if(dc_la[l][sl] == 1) nhit++;
				if(nhit>4) seg[sl] = 1;
			}
			
			// if at least 5 segments, it's accepted
			int dcacc  = 0;
			for(int sl=0; sl<6; sl++)
				if(seg[sl]==1) dcacc++;
			
			mom.push_back(genMom);
			theta.push_back(theMom);
			pid.push_back(thisID);
			
			if(dcacc > 4)
			{
				dc.push_back(1);
			}
			else
			{
				dc.push_back(0);
			}
			
			
		}
		fout.cd();
		out->Fill();
	}
 
	finp.Close();
	fout.Write();
	fout.Close();
	
}
