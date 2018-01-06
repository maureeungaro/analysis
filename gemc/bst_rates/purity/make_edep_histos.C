{
	
	
	// binning from 200 MeV to 4.2 GeV
	const int NPBINS = 20;
	int plims[NPBINS+1];
	for(int b=0; b<NPBINS+1; b++)
		plims[b] = 200 + b*200;
		
			
	const int NPART     = 3;
	string SPART[NPART] = { "protons" ,   "pions"  ,   "kaons" };
	int      PID[NPART] = {     2212  ,    211     ,     321   };
	double fmass[NPART] = { 938.27203 , 139.57018  ,   493.677};
	TH1F *sign_edep[NPART][NPBINS];       // signals E deposited as a function of momentum


	TFile f[NPART];
	for(int p=0; p<NPART; p++)
	{		
		string fname = 	Form("/arena/BST/root/%s.root", SPART[p].c_str());
		f[p].Open(fname.c_str());
		cout << fname << " " << SPART[p] << endl;
		
		for(int b=0; b<NPBINS; b++)
		{
			cout << " pmin: " << plims[b] << "     pmax: " << plims[b+1] <<  endl;
			sign_edep[p][b] = new TH1F(Form("edep_p%d_%d_%s", plims[b], plims[b+1], SPART[p].c_str()),
																 Form("edep_p%d_%d_%s", plims[b], plims[b+1], SPART[p].c_str()),
															   2000, 0, 0.5);
			
			
			string hist = Form("Edep >>  edep_p%d_%d_%s", plims[b], plims[b+1], SPART[p].c_str());
			cout << hist << endl;
			
			string cut  = Form("pid == %d && mpid == 0 && sqrt(abs(%6.5f*%6.5f-E*E)) > %d && sqrt(abs(%6.5f*%6.5f-E*E)) < %d", 
			                        PID[p],                        fmass[p], fmass[p], plims[b],  fmass[p], fmass[p], plims[b+1]);
			
			bstT->Draw(hist.c_str(), cut.c_str());
			
			sign_edep[p][b]->Scale(40);
			sign_edep[p][b]->SetDirectory(0);
		}
		f[p].Close();
	}	


	TFile of("../rootfiles/hadrons.root", "RECREATE");
	for(int p=0; p<NPART; p++)
		for(int b=0; b<NPBINS; b++)
			sign_edep[p][b]->Write();	
	of.Close();
		

}

