{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetPalette(1);
	
	const double TWINDOW = 130E-9;
	int NHITS ;


	string target = "lh2";
	const int nbstl = 8; 
	string  lname[nbstl]   = { "1a", "1b", "2a", "2b", "3a", "3b", "4a", "4b"};
	int LAYER  = 1;

	const int NBINS = 100;
	
	const int NENERGY    = 4;
	string EDEP[NENERGY] = {"Edep >= 0.00", "Edep > 0.02", "Edep > 0.04","Edep > 0.06"} ;
	double EVAL[NENERGY] = {         0.00 ,         0.02 ,         0.04 ,        0.06 } ;
	int ENERGY           = 0; 


	TFile f(Form("/arena/BST/root/%s.root", target));
	TCanvas *c1 = new TCanvas("c1", "c1", 100,100);
	
	
	NHITS  = genT->GetEntries();

	double TOT_TIME = NHITS*TWINDOW;
	
	// these histos are for sector 1 only
	double minz[nbstl],  maxz[nbstl];
	double minzm[nbstl], maxzm[nbstl];
	minz[0] = -250; maxz[0] = 140; 
	minz[1] = -250; maxz[1] = 140; 
	minz[2] = -200; maxz[2] = 170; 
	minz[3] = -200; maxz[3] = 170; 
	minz[4] = -160; maxz[4] = 210; 
	minz[5] = -160; maxz[5] = 210; 
	minz[6] = -100; maxz[6] = 260; 
	minz[7] = -100; maxz[7] = 260; 
	minzm[0] = -220; maxzm[0] = 115; 
	minzm[1] = -220; maxzm[1] = 115; 
	minzm[2] = -180; maxzm[2] = 155; 
	minzm[3] = -180; maxzm[3] = 155; 
	minzm[4] = -142; maxzm[4] = 195; 
	minzm[5] = -142; maxzm[5] = 195; 
	minzm[6] = -85;  maxzm[6] = 251; 
	minzm[7] = -85;  maxzm[7] = 251; 
	
	double mint[nbstl],  maxt[nbstl];
	double mintm[nbstl], maxtm[nbstl];
	mint[0] = 20; maxt[0] = 170; 
	mint[1] = 20; maxt[1] = 170; 
	mint[2] = 20; maxt[2] = 160; 
	mint[3] = 20; maxt[3] = 160; 
	mint[4] = 20; maxt[4] = 150; 
	mint[5] = 20; maxt[5] = 150; 
	mint[6] = 20; maxt[6] = 130; 
	mint[7] = 20; maxt[7] = 130; 
	mintm[0] = 30; maxtm[0] = 164; 
	mintm[1] = 30; maxtm[1] = 164; 
	mintm[2] = 31; maxtm[2] = 152; 
	mintm[3] = 31; maxtm[3] = 152; 
	mintm[4] = 31; maxtm[4] = 140; 
	mintm[5] = 31; maxtm[5] = 140; 
	mintm[6] = 32; maxtm[6] = 117; 
	mintm[7] = 32; maxtm[7] = 117; 
	
	TH2F *yz[nbstl][NENERGY];
	TH2F *yt[nbstl][NENERGY];
	TH2F *yzm[nbstl][NENERGY];
	TH2F *ytm[nbstl][NENERGY];
	TH1F *zpos[nbstl][NENERGY];
	
	
	for(int l=0; l<nbstl; l++)
		for(int e=0; e<NENERGY; e++)
		{
			string titlez  = Form("yx_layer%s_Egt%3.2f",     lname[l], EVAL[e]);
			string titlet  = Form("th_layer%s_Egt%3.2f",     lname[l], EVAL[e]);
			string titlezm = Form("yxm_layer%s_Egt%3.2f",    lname[l], EVAL[e]);
			string titletm = Form("thm_layer%s_Egt%3.2f",    lname[l], EVAL[e]);
			string titlezp = Form("zpos_layer%s_Egt%3.2f",   lname[l], EVAL[e]);
			yz[l][e]    = new TH2F(titlez.c_str(),  titlez.c_str(),  NBINS, minz[l], maxz[l], NBINS, -22, 22);
			yt[l][e]    = new TH2F(titlet.c_str(),  titlet.c_str(),  NBINS, mint[l], maxt[l], NBINS, -22, 22);
			yzm[l][e]   = new TH2F(titlezm.c_str(), titlezm.c_str(),     3, minz[l], maxz[l],     1, -22, 22);
			ytm[l][e]   = new TH2F(titletm.c_str(), titletm.c_str(),     3, mint[l], maxt[l],     1, -22, 22);
			zpos[l][e]  = new TH1F(titlezp.c_str(), titlezp.c_str(), NBINS, minz[l], maxz[l]);
			
			string lcut = Form("layer == %d", l+1);
			string cut  = lcut + " && " + " sector == 1 && " + EDEP[e];
			
			string whatz  = "y:z >> "                                      + titlez;
			string whatt  = "y:acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> " + titlet;
			string whatzm = "y:z >> "                                      + titlezm;
			string whattm = "y:acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> " + titletm;
			string whatzp = "z  >> " + titlezp;
			
			cout << cut << endl;
			
			if(l==4 || l==5)
			{
				whatz  = "(y-21):z >> "                                      + titlez;
				whatt  = "(y-21):acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> " + titlet;
				whatzm = "(y-21):z >> "                                      + titlezm;
				whattm = "(y-21):acos(z/sqrt(x*x+y*y+z*z))*180/3.141592 >> " + titletm;
			}
			
			bstT->Draw(whatz.c_str(),  cut.c_str());
			bstT->Draw(whatt.c_str(),  cut.c_str());
			bstT->Draw(whatzm.c_str(), cut.c_str());
			bstT->Draw(whattm.c_str(), cut.c_str());
			bstT->Draw(whatzp.c_str(), cut.c_str());
			
			
			yz[l][e]->SetDirectory(0);
			yt[l][e]->SetDirectory(0);
			yzm[l][e]->SetDirectory(0);
			ytm[l][e]->SetDirectory(0);
			zpos[l][e]->SetDirectory(0);
			
			yz[l][e]-> Scale(1.0/TOT_TIME);
			yt[l][e]-> Scale(1.0/TOT_TIME);
			yzm[l][e]->Scale(1.0/TOT_TIME);
			ytm[l][e]->Scale(1.0/TOT_TIME);
			zpos[l][e]->Scale(1.0/TOT_TIME);			
	}
	
	c1->Close();
	f.Close();

	gROOT->LoadMacro("utils.C");

	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("SVT Distribution",  "");
	bar->AddButton("","");
	bar->AddButton("Show YZ dist",      "show_dist(0)");
	bar->AddButton("Show YT dist",      "show_dist(1)");
	bar->AddButton("Show YZ m dist",    "show_dist(10)");
	bar->AddButton("Show YT m dist",    "show_dist(20)");
	bar->AddButton("Show Theta dist",   "show_dist(100)");
	bar->AddButton("","");
	bar->AddButton("Change Layer",      "change_layer()");
	bar->AddButton("","");
	bar->Show();

}






