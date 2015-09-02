{

	const double  proton_mass     = 938.27203;
	const double  neutron_mass    = 939.56536;
	const double  electron_mass   = 0.54857990;
	const double  pi0_mass        = 134.9766;
	const double  pi_mass         = 139.57018;
	const double  eta_mass        = 547.853;
	const double  kaon_mass       = 493.67;
	const double  k0_mass         = 497.614;

	// light nuclei
	const double  a_u_mass        = 0.931494;
	const double  He3_mass        = 3.016*a_u_mass;  // two protons, one neutron
	const double  H3_mass         = 3.016*a_u_mass;  // triton, tritium: one proton, two neutrons, radioactive into He3
	const double  He4_mass        = 4.002*a_u_mass;  // two protons, two neutrons.
	const double  deuteron_mass   = 2.014*a_u_mass;  // deuteron: one protons, one neutron

	TFile    f(Form("out.root"));
	TFile fout(Form("out_acc.root"), "RECREATE");

	
	// generated particles
	int evn;        // input evn
 	int evn2;       // output evn, same as input but it needs a different address
	int ngen;
	int id[20];
	float px[20];   // momentum and energy of generated particle
	float py[20];
	float pz[20];
	float gE[20];
	int dc[20];     // = 1 if dc accepted
	int ct[20];     // = 1 if ctof accepted
	int bs[20];     // = 1 if bst accepted
	int sc[20];     // = 1 if TOF accepted
	int bn[20];     // = 1 if bonus accepted

    // DC Hits
	int   ndchit;
	int   dcS[1000];
	int   dcSL[1000];
	int   dcL[1000];
	int   dcpid[1000];
	int   dcmpid[1000];
	float dcE[1000];
	float dcgE[1000];

	// Ctof Hits
	int   ncthit;
	int   ctpid[1000];
	int   ctmpid[1000];
	int   ctpaddle[1000];
	float ctE[1000];
	float ctgE[1000];

	// SC Hits
	int   nschit;
	int   scpid[1000];
	int   scmpid[1000];
	float scE[1000];
	float scgE[1000];
	
	// BST Hits
	int   nbsthit;
	int   bstS[1000];
	int   bstSL[1000];
	int   bstL[1000];
	int   bstpid[1000];
	int   bstmpid[1000];
	float bstE[1000];
	float bstgE[1000];

	// Bonus Hits
	int   nbnhit;
	int   bnpid[1000];
	int   bnmpid[1000];
	float bnE[1000];
	float bngE[1000];

	TTree *genT = (TTree*)f.Get("genT"); 
	TTree *dcT  = (TTree*)f.Get("dcT"); 
	TTree *ctT  = (TTree*)f.Get("ctofT"); 
	TTree *bstT = (TTree*)f.Get("bstT"); 
	TTree *scT  = (TTree*)f.Get("otofp1aT"); 
	TTree *bnT  = (TTree*)f.Get("bonusT"); 

	genT->SetBranchAddress("evn",  &evn);
	genT->SetBranchAddress("ngen", &ngen);
	genT->SetBranchAddress("id",   id);
	genT->SetBranchAddress("px",   px);
	genT->SetBranchAddress("py",   py);
	genT->SetBranchAddress("pz",   pz);

	dcT->SetBranchAddress("ndchit",      &ndchit);
	dcT->SetBranchAddress("Edep",        dcE);
	dcT->SetBranchAddress("sector",      dcS);
	dcT->SetBranchAddress("superlayer",  dcSL);
	dcT->SetBranchAddress("layer",       dcL);
	dcT->SetBranchAddress("pid",         dcpid);
	dcT->SetBranchAddress("mpid",        dcmpid);
	dcT->SetBranchAddress("E",           dcgE);

	ctT->SetBranchAddress("nctofhit",    &ncthit);
	ctT->SetBranchAddress("Edep",        ctE);
	ctT->SetBranchAddress("pid",         ctpid);
	ctT->SetBranchAddress("mpid",        ctmpid);
	ctT->SetBranchAddress("E",           ctgE);
	ctT->SetBranchAddress("paddle",      ctpaddle);
	
	bstT->SetBranchAddress("nbsthit",    &nbsthit);
	bstT->SetBranchAddress("layer",      bstL);
	bstT->SetBranchAddress("Edep",       bstE);
	bstT->SetBranchAddress("pid",        bstpid);
	bstT->SetBranchAddress("mpid",       bstmpid);
	bstT->SetBranchAddress("E",          bstgE);

	scT->SetBranchAddress("notofp1ahit", &nschit);
	scT->SetBranchAddress("Edep",        scE);
	scT->SetBranchAddress("pid",         scpid);
	scT->SetBranchAddress("mpid",        scmpid);
	scT->SetBranchAddress("E",           scgE);

	bnT->SetBranchAddress("nbonushit",   &nbnhit);
	bnT->SetBranchAddress("Edep",        bnE);
	bnT->SetBranchAddress("pid",         bnpid);
	bnT->SetBranchAddress("mpid",        bnmpid);
	bnT->SetBranchAddress("E",           bngE);

	TTree *out = new TTree("out", "accepted particles");
	out->Branch("evn",  &evn2, "evn/I");
	out->Branch("ngen", &ngen, "ngen/I");
	out->Branch("id",   id,    "id[20]/I");
	out->Branch("px",   px,    "px[20]/F");
	out->Branch("py",   py,    "py[20]/F");
	out->Branch("pz",   pz,    "pz[20]/F");
	out->Branch("dc",   dc,    "dc[20]/I");
	out->Branch("ct",   ct,    "ct[20]/I");
	out->Branch("bs",   bs,    "bs[20]/I");
	out->Branch("sc",   sc,    "sc[20]/I");
	out->Branch("bn",   bn,    "bn[20]/I");

	for(int i=0; i<genT->GetEntries(); i++)
	{
		genT->GetEntry(i);
		dcT->GetEntry(i);
		ctT->GetEntry(i);
		bstT->GetEntry(i);
		scT->GetEntry(i);
		bnT->GetEntry(i);
		evn2 = evn ;
		if(evn%100 == 0)
			cout << " evn: " << evn << " ndchits: " << ndchit
					<< " ncthits: "  << ncthit
					<< " nbsthits: " << nbsthit
					<< " nbnhits: "  << nbnhit
					<< " nschits: "  << nschit << endl;

		for(int in=0; in<20; in++)
		{
			dc[in] = 0;
			ct[in] = 0;
			bs[in] = 0;
			bn[in] = 0;
			sc[in] = 0;
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
			if(id[p] == -2112)       mass = neutron_mass;
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
				if(dcpid[d]==id[p] && dcmpid[d] ==0 && dcE[d] > 0.0001)
				{
					if(fabs(dcgE[d] - gE[p]) < 200)
						dc_la[dcL[d]-1][dcSL[d]-1] = 1;
				// cout << dcpid[d] << " " << dcL[d] << " " << dcS[d] << " " << dcSL[d] << " " << dcE[d] << endl;
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


			// %%%%%%%%%%%%%%%
			// CTOF acceptance
			// %%%%%%%%%%%%%%%
			ct[p] = 0;
			for(int c=0; c<ncthit; c++)
			{
//				cout << p+1 <<  " " << id[p] << " " << ctpid[c] << " " << ctmpid[c] << " " << ctE[c] <<  " " << fabs(ctgE[c] - gE[p]) << " " << ctpaddle[c] << endl;
				// if same pid of generated and if energy within 300 MeV of generated, it's a hit in ctof
				if(ctpid[c]==id[p] && ctmpid[c]==0 && ctE[c] > 1)
				{
					if(fabs(ctgE[c] - gE[p]) < 300)
					{
						ct[p] = 1;
						// cout << "yes " << endl;
					}
				}
			}

			// %%%%%%%%%%%%%%%
			// BST acceptance
			// %%%%%%%%%%%%%%%
			int bst_la[6];
			for(int l=0; l<6; l++)
				bst_la[l] = 0;
			
			// if same pid of generated and energy within 60 MeV of generated, it's a hit in that layer
			for(int b=0; b<nbsthit; b++)
			{
				// if energy within 300 MeV of generated, it's a hit in ctof
				if(bstmpid[b]==0 && bstE[b] > 0.0001)
				{	
					if(fabs(bstgE[c] - gE[p]) < 300)			
						bst_la[bstL[b]-1] = 1;
				}
			}
			
			// have to have a hit in each layer to be accepted
			bs[p] = 0;
			if(bst_la[0]*bst_la[1]*bst_la[2]*bst_la[3]*bst_la[4]*bst_la[5] > 0)
				bs[p] = 1;



			
			// %%%%%%%%%%%%%%%
			// OTOF acceptance
			// %%%%%%%%%%%%%%%
			sc[p] = 0;
			for(int s=0; s<nschit; s++)
			{
				// if same pid of generated, mpid=0 and energy within 60 MeV of generated, it's a hit in otof
				if(scpid[s]==id[p] && scmpid[s] ==0 && scE[s] > 0.1)
				{

					if(fabs(scgE[s] - gE[p]) < 60)
						sc[p] = 1;
				}
			}

			// %%%%%%%%%%%%%%%%
			// Bonus acceptance
			// %%%%%%%%%%%%%%%%
			bn[p] = 0;
			// if same pid of generated, mpid=0 and energy within 60 MeV of generated, it's a hit in otof
			for(int b=0; b<nbnhit; b++)
			{
				// if same pid of generated, mpid=0 and energy within 100 MeV of generated, it's a hit in otof
				//			cout << p+1 <<  " " << id[p] << " " << bnpid[b] << " " << bnmpid[b] << " " << bnE[b] <<  " " << fabs(bngE[b] - gE[p]) << " "  << endl;
				if(bnpid[b]==id[p] && bnmpid[b] ==0 && bnE[b] > 0.0001)
				{
					
					if(fabs(bngE[b] - gE[p]) < 10)
					// cout << "yes " << endl;
					bn[p] = 1;
				}
			}
			
		}
		fout.cd();
		out->Fill();
	}
 
	f.Close();
	fout.Write();
	fout.Close();

}
