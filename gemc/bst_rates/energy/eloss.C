{

	
//	const int pnum  = 3;
//	string  fname[pnum] = { "pions"   , "electrons"  ,  "protons"  };  // particles names - to be used in H names
//	string  pname[pnum] = { "pi-"     ,  "e-"        ,  "p"  };        // particles names - to be used in H names
//	string  pnaml[pnum] = {" #pi^{-}" ,  " e^{-}"    ,  "p"  };        // particles names - for labels
//	int       pid[pnum] = {  -211     ,   11         ,  2212 };        // particle IDs


	const int pnum  = 1;
	string  fname[pnum] = { "electrons"    };  // particles names - to be used in H names
	string  pname[pnum] = {  "e-"      };        // particles names - to be used in H names
	string  pnaml[pnum] = {  " e^{-}"   };        // particles names - for labels
	int       pid[pnum] = {    11      };        // particle IDs

	const int nbstl = 5; 
	string  lname[nbstl]   = { "0", "1", "2", "3", "4"};


	TH2F *phitheta[nbstl][pnum];
	TH2F *eloss[nbstl][pnum];

	for(int p=0; p<pnum; p++)
	{
		string ifile = Form("%s.root", fname[p]);
		cout << " Opening file " << ifile << endl;
		TFile f(ifile.c_str());
		
	
		f.Close();
	}


}