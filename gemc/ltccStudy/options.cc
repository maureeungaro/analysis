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


			string filename = "/opt/root/" + p + ".root";

			TFile f(filename.c_str());
			f.GetObject("generated", generated);
			f.GetObject("ftof",      ftof);

			cout << " File " << filename << " opened. " << endl;

			int NHITS = generated->GetEntries();


			defineHistos(p);
			cout << " Initializing FTOF histos with " << NHITS << " entries..." << endl;

			initLeafs();

			fillHistos(cIndex);
			setDirHistos(cIndex++);

			f.Close();

		}

		c1->Close();
		writeHistos();


	} else {
		string fname = "ltccHistos.root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());

		cout << " done. " << endl;
		f.Close();
	}
	
}


void anaOption::defineHistos(string c) {
	cout << " Defining " << c << " histo." << endl;
	dmom.push_back(new TH2F(Form("dmom_%s", c.c_str()),
							Form("dmom_%s", c.c_str()),
							200, 250, 4250, 200, -2000, -2000));
	deMomTheta.push_back(new TH2F(Form("deMomTheta_%s", c.c_str()),
								  Form("deMomTheta_%s", c.c_str()),
								  200, 5, 45, 200, 0, 4000));
	deMom.push_back(new TH1F(Form("deMom_%s", c.c_str()),
							 Form("deMom_%s", c.c_str()),
							 200, 0, 4000));
	theta.push_back(new TH1F(Form("theta1_%s", c.c_str()),
							  Form("theta1_%s", c.c_str()),
							  200, 5, 40));
}

void anaOption::setDirHistos(int cIndex) {
	cout << " Setting dir to index " << cIndex << " histos." << endl;

	dmom[cIndex]->SetDirectory(0);
	deMom[cIndex]->SetDirectory(0);
	deMomTheta[cIndex]->SetDirectory(0);
	theta[cIndex]->SetDirectory(0);
}

void anaOption::writeHistos() {

	string ofname = "ltccHistos.root";

	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");

	for(auto *h: dmom)       { h->Write(); }
	for(auto *h: deMom)      { h->Write(); }
	for(auto *h: deMomTheta) { h->Write(); }
	for(auto *h: theta)     { h->Write(); }

	of.Close();
}

void anaOption::initLeafs() {

	cout << " Leafs Initialized " << endl;

	// resetting pointer - is it necessary?
	sector  = nullptr;
	layer   = nullptr;
	x       = nullptr;
	y       = nullptr;
	pid     = nullptr;
	mpid    = nullptr;
	px      = nullptr;
	py      = nullptr;
	pz      = nullptr;

	gpx     = nullptr;
	gpy     = nullptr;
	gpz     = nullptr;


	ftof->SetBranchAddress("sector", &sector);
	ftof->SetBranchAddress("layer",  &layer);
	ftof->SetBranchAddress("avg_x",  &x);
	ftof->SetBranchAddress("avg_y",  &y);
	ftof->SetBranchAddress("pid",    &pid);
	ftof->SetBranchAddress("mpid",   &mpid);
	ftof->SetBranchAddress("px",     &px);
	ftof->SetBranchAddress("py",     &py);
	ftof->SetBranchAddress("pz",     &pz);

	generated->SetBranchAddress("px",     &gpx);
	generated->SetBranchAddress("py",     &gpy);
	generated->SetBranchAddress("pz",     &gpz);

}

void anaOption::fillHistos(int cindex) {

	int scale = 0;
	int nevents = ftof->GetEntries();

	for(int i=0; i<ftof->GetEntries(); i++){
//	for(int i=0; i<4000; i++){
		ftof->GetEntry(i);
		generated->GetEntry(i);

		if(i%1000 == 0) cout << " Entry number " << i << endl;

		int thisSector = 0;
		int thisLayer  = 0;

		int thisPID     = 0;
		int thismPID    = 0;

		double thisX  = 0;
		double thisY  = 0;

		double thisPx = 0;
		double thisPy = 0;
		double thisPz = 0;

		double thisgPx = 0;
		double thisgPy = 0;
		double thisgPz = 0;

		thisgPx = (*gpx)[0];
		thisgPy = (*gpy)[0];
		thisgPz = (*gpz)[0];

		double gmom = sqrt( thisgPx*thisgPx + thisgPy*thisgPy + thisgPz*thisgPz);


		for(unsigned d=0; d<(*x).size(); d++) {

			thisSector = (*sector)[d];
			thisLayer  = (*layer)[d];

			thisPID    = (*pid)[d];
			thismPID   = (*mpid)[d];

			thisX  = (*x)[d];
			thisY  = (*y)[d];

			thisPx = (*px)[d];
			thisPy = (*py)[d];
			thisPz = (*pz)[d];

			double mom = sqrt( thisPx*thisPx + thisPy*thisPy + thisPz*thisPz);
			double thisTheta = acos(thisPz/mom)*180/3.141592;

			double deltaMom = fabs(gmom - mom);



			// filling all particles
			if(thisPID == 11 && thismPID == 0 && thisSector == 1 && thisLayer == 2) {
//				dmom[cindex]->Fill(thisX, thisY, deltaMom);
				dmom[cindex]->Fill(thisX, thisY);
				deMom[cindex]->Fill(deltaMom);
				deMomTheta[cindex]->Fill(thisTheta, deltaMom);

				if(deltaMom<10)  theta[cindex]->Fill(thisTheta);

//				cout << deltaMom << " " << mom << " " << gmom << endl;
				scale++;
			}
		}
	}
	cout << "scale " << scale << endl;
//	dmom[cindex]->Scale(1.0/scale);
//	deMom[cindex]->Scale(1.0/scale);
	dmom[cindex]->Scale(1.0/nevents);
	deMom[cindex]->Scale(1.0/nevents);
}





