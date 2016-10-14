void init_nphe_histos(string filename, int cindex)
{
	if(recalc == 1)
	{
		TFile f(filename.c_str());
		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

		NHITS           = generated->GetEntries();
		double TWINDOW  = 250.0e-9;
		double TOT_TIME = NHITS*TWINDOW;

		cout << " Initializing HTCC histos for configuration " << sconf[cindex] << " with " << NHITS << " entries in " << TOT_TIME << " total time...";
		for(int e=0; e<NNPHE; e++) {
			npheRates[e][cindex] = new TH1F(Form("nphe_%s_%s", SNPHE[e].c_str(), sconf[cindex].c_str()),
													  Form("nphe_%s_%s", SNPHE[e].c_str(), sconf[cindex].c_str()),
													  100, 0, 50);
		}
		cout << " done. " << endl;


		for(int e=0; e<NNPHE; e++) {
			cout << " Now making the histos for the nphe cut: " << SNPHE[e] << endl;

			string hitCut = NPHE[e];
			string hist   = Form("nphe >> nphe_%s_%s", SNPHE[e].c_str(), sconf[cindex].c_str());

			htcc->Draw(hist.c_str(), hitCut.c_str());
		}


		for(int e=0; e<NNPHE; e++) {
			npheRates[e][cindex]->Scale(0.001/TOT_TIME); // rate in KHz
			npheRates[e][cindex]->SetDirectory(0);
		}

		c1->Close();
		f.Close();
		
		
		// writing out to file
		string ofname =   sconf[cindex] + ".root";
		cout << " Opening file for writing: " << ofname << endl;
		TFile of(ofname.c_str(), "RECREATE");
		for(int e=0; e<NNPHE; e++) {
			npheRates[e][cindex]->Write();
		}

		of.Close();
		cout << " done. "  << endl;
	} else {
		string fname =   sconf[cindex] + ".root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());
		for(int e=0; e<NNPHE; e++) {

			npheRates[e][cindex] = (TH2F*) f.Get(Form("nphe_%s_%s", SNPHE[e].c_str(), sconf[cindex].c_str()));
			npheRates[e][cindex]->SetDirectory(0);

			cout << " done. " << endl;
			f.Close();

		}
	}
	
}









