{

	const double  proton_mass     = 938.27203;
	const double  neutron_mass    = 939.56536;
	const double  electron_mass   = 0.54857990;
	const double  pi0_mass        = 134.9766;
	const double  pi_mass         = 139.57018;
	const double  eta_mass        = 547.853;
	const double  kaon_mass       = 493.67;
    const double  k0_mass         = 497.614;
    const double  muon_mass       = 105.65;

	// light nuclei
	const double  a_u_mass        = 0.931494;
	const double  He3_mass        = 3.016*a_u_mass;  // two protons, one neutron
	const double  H3_mass         = 3.016*a_u_mass;  // triton, tritium: one proton, two neutrons, radioactive into He3
	const double  He4_mass        = 4.002*a_u_mass;  // two protons, two neutrons.
	const double  deuteron_mass   = 2.014*a_u_mass;  // deuteron: one protons, one neutron

	TFile    f(Form("out.root"));
	TFile fout(Form("out_acc.root"), "RECREATE");
	
	// generated particles
    TTree *genT = (TTree*)f.Get("genT");
	int evn;        // input evn
 	int evn2;       // output evn, same as input but it needs a different address
	
    int   ngen;
    vector<double> *id = 0;
	vector<double> *px = 0;   // momentum and energy of generated particle
	vector<double> *py = 0;
	vector<double> *pz = 0;
	vector<double> *gE = 0;
	vector<double> *dc = 0;     // = 1 if dc accepted

    genT->SetBranchAddress("evn",  &evn);
    genT->SetBranchAddress("ngen", &ngen);
    genT->SetBranchAddress("id",   id);
    genT->SetBranchAddress("px",   px);
    genT->SetBranchAddress("py",   py);
    genT->SetBranchAddress("pz",   pz);

    
    // DC Hits
	int   ndchit;
    vector<double> *dcTotE = 0;
	vector<double> *dcS    = 0;
	vector<double> *dcSL   = 0;
	vector<double> *dcL    = 0;
	vector<double> *dcpid  = 0;
	vector<double> *dcmpid = 0;
	vector<double> *dctE   = 0;


	TTree *dcT  = (TTree*)f.Get("dcT");
    dcT->SetBranchAddress("totEdep",     &dcTotE);
    dcT->SetBranchAddress("sector",      &dcS);
    dcT->SetBranchAddress("superlayer",  &dcSL);
    dcT->SetBranchAddress("layer",       &dcL);
    dcT->SetBranchAddress("pid",         &dcpid);
    dcT->SetBranchAddress("mpid",        &dcmpid);
	dcT->SetBranchAddress("trackE",      &dctE);


    // output
    vector<double> pid;     // pid of accepted particle
    vector<double> mom;     // momentum
    vector<double> theta;   // theta
    vector<double> dc;      // dc acceptance

	TTree *out = new TTree("out", "accepted particles");
	out->Branch("evn",  &evn2, "evn/I");
	out->Branch("id",   id,    "id[20]/I");
	out->Branch("px",   px,    "px[20]/F");
	out->Branch("py",   py,    "py[20]/F");
	out->Branch("pz",   pz,    "pz[20]/F");
	out->Branch("dc",   dc,    "dc[20]/I");

	for(int i=0; i<genT->GetEntries(); i++)
	{
		genT->GetEntry(i);
		dcT->GetEntry(i);
		evn2 = evn ;
		if(evn%100 == 0)
			cout << " evn: " << evn << " ndchits: " << ndchit
                 << endl;

		for(int in=0; in<20; in++)
		{
			dc[in] = 0;
		}
		
		for(int p=0; p<ngen; p++)
		{
			double mass = -1;
			if(id[p] == 22)         mass = 0;
			if(id[p] == 11)         mass = electron_mass;
			if(id[p] == -11)        mass = electron_mass;
			if(id[p] == 111)        mass = pi0_mass;
			if(id[p] ==  211)       mass = pi_mass;
			if(id[p] == -211)       mass = pi_mass;
			if(id[p] ==  130)       mass = kaon_mass;
			if(id[p] ==  321)       mass = kaon_mass;
			if(id[p] == -321)       mass = kaon_mass;
			if(id[p] == 2212)       mass = proton_mass;
			if(id[p] == -2212)      mass = proton_mass;
			if(id[p] == 2112)       mass = neutron_mass;
			if(id[p] == -2112)      mass = neutron_mass;
			if(id[p] == 1000010030) mass = H3_mass;
			if(mass == -1) cout << " Unknown mass for id " << id[p] << endl;

			gE[p] = sqrt(px[p]*px[p] + py[p]*py[p] + pz[p]*pz[p] + mass*mass);

			// %%%%%%%%%%%%%
			// DC acceptance
			// %%%%%%%%%%%%%
			int dc_la[6][6];
			for(int l=0; l<6; l++)
				for(int sl=0; sl<6; sl++)
					dc_la[l][sl] = 0;
	
			for(int d=0; d<ndchit; d++)
			{
				// if same pid of generated, it's a hit in that layer, superlayer
				if(dcpid[d]==id[p] && dcmpid[d] ==0 && dcTotE[d] > 0.0001)
				{
					if(fabs(dcgE[d] - gE[p]) < 200)
						dc_la[dcL[d]-1][dcSL[d]-1] = 1;
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
			dc[p] = 0;
			int dcacc  = 0;
			for(int sl=0; sl<6; sl++)
				if(seg[sl]==1) dcacc++;
			if(dcacc > 4)
				dc[p] = 1;


			
		}
		fout.cd();
		out->Fill();
	}
 
	f.Close();
	fout.Write();
	fout.Close();

}
