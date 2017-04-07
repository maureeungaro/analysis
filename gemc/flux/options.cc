#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"

anaOption::anaOption(bool r) : recalc(r)
{
	pIndex     = 0;

	PRINT = "";

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

	partTit.push_back("protons");
	partiID.push_back(2212);


	if(recalc == 1) {
		string filename = "flux.root";
		TFile f(filename.c_str());

		TTree *generated, *flux;
		f.GetObject("generated", generated);
		f.GetObject("flux",      flux);


		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);


		vector<double> *x      = 0;
		vector<double> *y      = 0;
		vector<double> *pid    = 0;
		vector<double> *mpid   = 0;
		vector<double> *procID = 0;
		vector<double> *px      = 0;
		vector<double> *py      = 0;
		vector<double> *pz      = 0;
		flux->SetBranchAddress("avg_x",  &x);
		flux->SetBranchAddress("avg_y",  &y);
		flux->SetBranchAddress("pid",    &pid);
		flux->SetBranchAddress("mpid",   &mpid);
		flux->SetBranchAddress("procID", &procID);
		flux->SetBranchAddress("px",     &px);
		flux->SetBranchAddress("py",     &py);
		flux->SetBranchAddress("pz",     &pz);


		NHITS           = generated->GetEntries();
		double TWINDOW  = 250.0e-9;
		double TOT_TIME = NHITS*TWINDOW;

		cout << " Initializing Flux histos with " << NHITS << " entries in " << TOT_TIME << " total time...";

		for(auto p: partTit) {
			cout << " Defining " << p << " histo." << endl;
			pflux.push_back(new TH2F(Form("pflux_%s", p.c_str()),
									 Form("pflux_%s", p.c_str()),
									 200, -1100, 1100, 200, -1100, 1100));
			pmom.push_back(new TH1F(Form("pmom_%s", p.c_str()),
									Form("pmom_%s", p.c_str()),
									200, 0, 3000));

			pprocID.push_back(new TH1F(Form("pprocID_%s", p.c_str()),
									   Form("pprocID_%s", p.c_str()),
									   60, 0.5, 30.5));


		}

		cout << " done. Now filling tree." << endl;

		for(int i=0; i<flux->GetEntries(); i++){
			flux->GetEntry(i);


			for(unsigned d=0; d<(*x).size(); d++) {
				int thisPID     = (*pid)[d];
				int thismPID    = (*mpid)[d];
				int thisProcID  = (*procID)[d];

				double thisX = (*x)[d];
				double thisY = (*y)[d];

				double thisPx = (*px)[d];
				double thisPy = (*py)[d];
				double thisPz = (*pz)[d];

				double mom = sqrt( thisPx*thisPx + thisPy*thisPy + thisPz*thisPz);

				for(int p=0; p<partiID.size(); p++) {

					if(thisPID == 11) {
						if(thismPID == partiID[p]) {
							pflux[p]->Fill(thisX, thisY);
							pmom[p]->Fill(mom);
							pprocID[p]->Fill(thisProcID);

						}
						pflux[0]->Fill((*x)[d], (*y)[d]);
						pmom[0]->Fill(mom);
						pprocID[0]->Fill(thisProcID);

					}
				}
			}
		}

		for(auto *h: pflux) {
			h->SetDirectory(0);
		}
		for(auto *h: pmom) {
			h->SetDirectory(0);
		}
		for(auto *h: pprocID) {
			h->SetDirectory(0);
		}

		c1->Close();


		f.Close();

		// writing out to file1
		string ofname = "fluxHistos.root";
		cout << " Opening file for writing: " << ofname << endl;
		TFile of(ofname.c_str(), "RECREATE");

		for(auto *h: pflux) {
			h->Write();
		}
		for(auto *h: pmom) {
			h->Write();
		}
		for(auto *h: pprocID) {
			h->Write();
		}

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

void anaOption::showFlux() {
	cout << " ASD " << endl;
}




