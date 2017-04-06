#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"

anaOption::anaOption(bool r) : recalc(r)
{

	pIndex     = 0;
	nParticles = 6;


	PRINT = "";

	partTit.push_back("all");
	partCut.push_back("1");

	partTit.push_back("electrons");
	partCut.push_back("pid == 11");

	partTit.push_back("gammas");
	partCut.push_back("pid == 22");

	partTit.push_back("pions");
	partCut.push_back("pid == 211 || pid == -211");

	partTit.push_back("protons");
	partCut.push_back("pid == 2212");

	partTit.push_back("other");
	partCut.push_back("pid != 11 && pid != 1 && pid != 211 && pid != -211 && pid != 2212");

	if(recalc == 1) {
		string filename = "flux.root";
		TFile f(filename.c_str());

		TTree *generated, *flux;
		f.GetObject("generated", generated);
		f.GetObject("flux",      flux);

		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

		NHITS           = generated->GetEntries();
		double TWINDOW  = 250.0e-9;
		double TOT_TIME = NHITS*TWINDOW;

		cout << " Initializing Flux histos with " << NHITS << " entries in " << TOT_TIME << " total time...";

		for(int p=0; p<nParticles; p++) {
			pflux->push_back(new TH2F(Form("pflux_%s", partTit[p].c_str()),
									  Form("pflux_%s", partTit[p].c_str()),
									  200, -200, 200, 200, -200, 200));
		}

		cout << " done. " << endl;

		for(int p=0; p<nParticles; p++) {
			cout << " Now making the histos for particle : " << partTit[p] << endl;

			string hist = Form("sqrt(avg_x*avg_x + avg_y*avg_y) >> pflux_%s", partTit[p].c_str());
			string momCut = "sqrt(px*px + py*py + pz*pz) > 10";

			string hitCut = momCut + " && " + partCut[p];

			flux->Draw(hist.c_str(), hitCut.c_str());
		}


		c1->Close();
		f.Close();

		// writing out to file1
		string ofname = "fluxHistos.root";
		cout << " Opening file for writing: " << ofname << endl;
		TFile of(ofname.c_str(), "RECREATE");

		for(auto *h: *pflux) {
			h->Write();
		}

	} else {
		string fname = "fluxHistos.root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());


		for(int p=0; p<nParticles; p++) {
			pflux->push_back((TH2F*) f.Get(Form("pflux_%s", partTit[p].c_str())));
		}

		cout << " done. " << endl;
		f.Close();
		
	}
	
}
