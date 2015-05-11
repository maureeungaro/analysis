{

	TFile    f(Form("in.root"));
	TFile fout(Form("out.root"), "RECREATE");

	int dc[20];     // = 1 if dc accepted
    
    int evn;        // input evn
    int evn2;       // output evn, same as input but it needs a different address

    // DC Hits
    int   hitn[1000];    // hit index
 	int   dcS[1000];     // sector
	int   dcSL[1000];    // superlayer
	int   dcL[1000];     // layer
	int   dcpid[1000];   // pid
	int   dcmpid[1000];  // mother pid
	float dcE[1000];     // track energy

	TTree *dcT  = (TTree*)f.Get("dc");
	dcT->SetBranchAddress("hitn",        hitn);
	dcT->SetBranchAddress("totEdep",     dcE);
	dcT->SetBranchAddress("sector",      dcS);
	dcT->SetBranchAddress("superlayer",  dcSL);
	dcT->SetBranchAddress("layer",       dcL);
	dcT->SetBranchAddress("pid",         dcpid);
	dcT->SetBranchAddress("mpid",        dcmpid);
	dcT->SetBranchAddress("trackE",      dcE);

    TTree *headerT  = (TTree*)f.Get("header");
    headerT->SetBranchAddress("evn",  &evn);


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
