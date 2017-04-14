#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"

anaOption::anaOption(bool recalc, vector<string> configurations) : confs(configurations)
{
	pIndex = 0;
	PRINT  = "";

	if(recalc == 1) {

		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

		summaryRate = new TH1F("summaryRate", "summaryRate", confs.size(), 0.5, confs.size() + 0.5);
		summaryRate->SetDirectory(0);

		int cIndex = 0;
		for(auto p: confs) {


			string filename = "/opt/root/" + p + ".root";

			TFile f(filename.c_str());
			f.GetObject("generated", generated);
			f.GetObject("flux",      flux);

			cout << " File " << filename << " opened. " << endl;

			int NHITS       = generated->GetEntries();
			double TWINDOW  = 250.0e-9;
			TOT_TIME.push_back(NHITS*TWINDOW);


			defineHistos(p);
			cout << " Initializing Flux histos with " << NHITS << " entries in " << TOT_TIME[cIndex] << " total time..." << endl;

			initLeafs();

			fillHistos(cIndex);
			setDirHistos(cIndex++);

			f.Close();

		}


		c1->Close();
		writeHistos();


	} else {
		string fname = "fluxHistos.root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());


		for(auto p: partTit) {
			pflux.push_back((TH2F*) f.Get(Form("pflux_%s", p.c_str())));

		}

		cout << " done. " << endl;
		f.Close();

	}

}

void anaOption::setParticles() {
	partTit.push_back("all");
	partiID.push_back(0);

	partTit.push_back("electrons");
	partiID.push_back(11);

	partTit.push_back("gammas");
	partiID.push_back(22);

	partTit.push_back("pi+");
	partiID.push_back(211);

	partTit.push_back("pi-");
	partiID.push_back(-211);

	partTit.push_back("pi0");
	partiID.push_back(111);

	partTit.push_back("protons");
	partiID.push_back(2212);
}

void anaOption::defineHistos(string c) {
	cout << " Defining " << c << " histo." << endl;
	pflux.push_back(new TH2F(Form("pflux_%s", c.c_str()),
							 Form("pflux_%s", c.c_str()),
							 200, -1100, 1100, 200, -1100, 1100));

	pzver.push_back(new TH1F(Form("pzver_%s", c.c_str()),
							 Form("pzver_%s", c.c_str()),
							 200, -100, 1100));

	pmom.push_back(new TH1F(Form("pmom_%s", c.c_str()),
							Form("pmom_%s", c.c_str()),
							200, 0, 10000));

	pprocID.push_back(new TH1F(Form("pprocID_%s", c.c_str()),
							   Form("pprocID_%s", c.c_str()),
							   200, 0.5, 200.5));
}

void anaOption::setDirHistos(int cIndex) {
	cout << " Setting dir to index " << cIndex << " histos." << endl;

	pflux[cIndex]->SetDirectory(0);
	pmom[cIndex]->SetDirectory(0);
	pprocID[cIndex]->SetDirectory(0);
	pzver[cIndex]->SetDirectory(0);

}

void anaOption::writeHistos() {

	string ofname = "fluxHistos.root";

	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");

	for(auto *h: pflux)    { h->Write(); }
	for(auto *h: pmom)     { h->Write(); }
	for(auto *h: pprocID)  { h->Write(); }
	for(auto *h: pzver)    { h->Write(); }

	summaryRate->Write();

	of.Close();
}

void anaOption::initLeafs() {

	cout << " Leafs Initialized " << endl;

	// resetting pointer - is it necessary?
	x       = nullptr;
	y       = nullptr;
	vz      = nullptr;
	pid     = nullptr;
	mpid    = nullptr;
	procID  = nullptr;
	px      = nullptr;
	py      = nullptr;
	pz      = nullptr;


	flux->SetBranchAddress("avg_x",  &x);
	flux->SetBranchAddress("avg_y",  &y);
	flux->SetBranchAddress("vz",     &vz);
	flux->SetBranchAddress("pid",    &pid);
	flux->SetBranchAddress("mpid",   &mpid);
	flux->SetBranchAddress("procID", &procID);
	flux->SetBranchAddress("px",     &px);
	flux->SetBranchAddress("py",     &py);
	flux->SetBranchAddress("pz",     &pz);

	cout << " x " << x << endl;

}

void anaOption::fillHistos(int cindex) {

	for(int i=0; i<flux->GetEntries(); i++){
//	for(int i=0; i<1000; i++){
		flux->GetEntry(i);

		if(i%10000 == 0) cout << " Entry number " << i << endl;

		int thisPID     = 0;
		int thismPID    = 0;
		int thisProcID  = 0;

		double thisX  = 0;
		double thisY  = 0;
		double thisVZ = 0;

		double thisPx = 0;
		double thisPy = 0;
		double thisPz = 0;

		double mom = 0;

		for(unsigned d=0; d<(*x).size(); d++) {

			thisPID     = (*pid)[d];
			thismPID    = (*mpid)[d];
			thisProcID  = (*procID)[d];

			thisX  = (*x)[d];
			thisY  = (*y)[d];
			thisVZ = (*vz)[d];

			thisPx = (*px)[d];
			thisPy = (*py)[d];
			thisPz = (*pz)[d];

			mom = sqrt( thisPx*thisPx + thisPy*thisPy + thisPz*thisPz);

			// filling all particles
			if(thisPID == 11 && mom > 500) {
				pflux[cindex]->Fill(thisX, thisY);
				pmom[cindex]->Fill(mom);
				pprocID[cindex]->Fill(thisProcID);
				pzver[cindex]->Fill(thisVZ);
			}
		}
	}
	
}

void anaOption::setSummaryHisto {

	for(int i=0; i<pmom.size(); i++) {
		summaryRate->SetBinContent(i+1, pmom[i]->GetEntries() / TOT_TIME[i]);
	}
}






