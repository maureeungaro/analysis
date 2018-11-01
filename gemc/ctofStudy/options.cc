#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"

anaOption::anaOption(bool recalc, vector<string> configurations) : confs(configurations)
{
	PRINT  = "";

	if(recalc == 1) {

		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

		int cIndex = 0;
		for(auto p: confs) {

			string filename = "/opt/root/ctof/" + p + ".root";

			TFile f(filename.c_str());
			f.GetObject("generated", generated);
			f.GetObject("ctof",      ctof);

			cout << " File " << filename << " opened. " << endl;

			int NHITS = generated->GetEntries();


			defineHistos(p);
			cout << " Initializing ctof histos with " << NHITS << " entries..." << endl;

			initLeafs();

			fillHistos(cIndex);
			setDirHistos(cIndex++);

			f.Close();

		}

		c1->Close();
		writeHistos();


	} else {
		string fname = "ctofHistos.root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());

		cout << " done. " << endl;
		f.Close();
	}
	
}


void anaOption::defineHistos(string c) {

	cout << " Defining " << c << " histo." << endl;
	ctofRatesTotal.push_back(new TH1F(Form("ctofRatesTotal_%s", c),
												 Form("ctofRatesTotal_%s", c), 48, 0.5, 48.5));

}

void anaOption::setDirHistos(int cIndex) {
	cout << " Setting dir to index " << cIndex << " histos." << endl;

	ctofRatesTotal[cIndex]->SetDirectory(0);
}

void anaOption::writeHistos() {

	string ofname = "ctofHistos.root";

	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");

	for(auto *h: ctofRatesTotal) {
		h->Write();
	}

	of.Close();
}

void anaOption::initLeafs() {

	cout << " Leafs Initialized " << endl;

	// resetting pointer - is it necessary?
	paddle  = nullptr;
	x       = nullptr;
	y       = nullptr;
	z       = nullptr;
	pid     = nullptr;
	mpid    = nullptr;
	totEdep = nullptr;

	ctof->SetBranchAddress("paddle",  &paddle);
	ctof->SetBranchAddress("avg_x",   &x);
	ctof->SetBranchAddress("avg_y",   &y);
	ctof->SetBranchAddress("avg_z",   &z);
	ctof->SetBranchAddress("pid",     &pid);
	ctof->SetBranchAddress("mpid",    &mpid);
	ctof->SetBranchAddress("totEdep", &totEdep);

}

void anaOption::fillHistos(int cindex) {

	int scale = 0;
	int nevents = ctof->GetEntries();

	for(int i=0; i<ctof->GetEntries(); i++){

		ctof->GetEntry(i);
		generated->GetEntry(i);

		if(i%10 == 0) cout << " Entry number " << i << endl;

		int thisPaddle = 0;

		double thisX  = 0;
		double thisY  = 0;
		double thisX  = 0;

		int thisPID     = 0;
		int thismPID    = 0;

		double thisEdep  = 0;


		// looping over hits
		for(unsigned d=0; d<(*x).size(); d++) {

			thisPaddle = (*paddle)[d];

			thisX  = (*x)[d];
			thisY  = (*y)[d];
			thisZ  = (*z)[d];

			thisPID    = (*pid)[d];
			thismPID   = (*mpid)[d];

			thisEdep  = (*totEdep)[d];


			// filling all particles
			ctofRatesTotal[cindex]->Fill(thisPaddle);

		}
	}

}





