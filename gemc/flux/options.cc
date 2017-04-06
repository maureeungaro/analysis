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


		vector<double> *x   = 0;
		vector<double> *y   = 0;
		vector<double> *pid = 0;
		flux->SetBranchAddress("avg_x", &x);
		flux->SetBranchAddress("avg_y", &y);
		flux->SetBranchAddress("pid",   &pid);


		NHITS           = generated->GetEntries();
		double TWINDOW  = 250.0e-9;
		double TOT_TIME = NHITS*TWINDOW;

		cout << " Initializing Flux histos with " << NHITS << " entries in " << TOT_TIME << " total time...";

		for(auto p: partTit) {
			cout << " Defining " << p << " histo." << endl;
			pflux.push_back(new TH2F(Form("pflux_%s", p.c_str()),
									 Form("pflux_%s", p.c_str()),
									 200, -2000, 2000, 200, -2000, 2000));
		}

		cout << " done. " << endl;
		for(int i=0; i<flux->GetEntries(); i++){
			flux->GetEntry(i);

			cout << (*x).size() << endl;

			for(unsigned d=0; d<(*x).size(); d++) {
				int thisPID     = (*pid)[d];

				//double r = sqrt( (*x)[d]*(*x)[d] + (*y)[d]*(*y)[d]);

				for(int p=0; p<partiID.size(); p++) {

					if(thisPID == partiID[p]) {
						pflux[p]->Fill((*x)[d], (*y)[d]);
					}
				}

			}




		}
//		for(int p=0; p<partTit.size(); p++) {
//			cout << " Now making the histos for particle : " << partTit[p].c_str() << endl;
//
//			string hist = Form("sqrt(avg_x*avg_x + avg_y*avg_y) >> pflux_%s", partTit[p].c_str());
//			string momCut = "sqrt(px*px + py*py + pz*pz) > 10";
//
//			string hitCut = momCut + " && " + partCut[p];
//
//			flux->Draw(hist.c_str(), hitCut.c_str());
//		}

		for(auto *h: pflux) {
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
