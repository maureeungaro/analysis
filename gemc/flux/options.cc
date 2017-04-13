#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"

anaOption::anaOption(bool recalc, vector<string> configurations) : conf(configurations)
{
	pIndex = 0;
	PRINT  = "";

	if(recalc == 1) {

		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);


		for(auto p: configurations) {

			
			string filename = "/opt/root/" + p;

			TFile f(filename.c_str());
			f.GetObject("generated", generated);
			f.GetObject("flux",      flux);

			cout << " File " << filename << " opened. " << endl;
			initLeafs();

			int NHITS       = generated->GetEntries();
			double TWINDOW  = 250.0e-9;
			double TOT_TIME = NHITS*TWINDOW;

			cout << " Initializing Flux histos with " << NHITS << " entries in " << TOT_TIME << " total time...";


		}                                                                                                                                

		c1->Close();
		f.Close();
		writeHistos();


		for(auto p: configurations) {
			cout << " Defining " << p << " histo." << endl;
			pflux.push_back(new TH2F(Form("pflux_%s", p.c_str()),
									 Form("pflux_%s", p.c_str()),
									 200, -1100, 1100, 200, -1100, 1100));

			pzver.push_back(new TH1F(Form("pzver_%s", p.c_str()),
									 Form("pzver_%s", p.c_str()),
									 200, -100, 1100));

			pmom.push_back(new TH1F(Form("pmom_%s", p.c_str()),
									Form("pmom_%s", p.c_str()),
									200, 0, 10000));

			pprocID.push_back(new TH1F(Form("pprocID_%s", p.c_str()),
									   Form("pprocID_%s", p.c_str()),
									   200, 0.5, 200.5));

			cpzver.push_back(new TH1F(Form("cpzver_%s", p.c_str()),
									  Form("cpzver_%s", p.c_str()),
									 200, -100, 1100));

			cpmom.push_back(new TH1F(Form("cpmom_%s", p.c_str()),
									 Form("cpmom_%s", p.c_str()),
									200, 0, 10000));

			cpprocID.push_back(new TH1F(Form("cpprocID_%s", p.c_str()),
										Form("cpprocID_%s", p.c_str()),
									   200, 0.5, 200.5));

		}

		cout << " done. Now filling tree." << endl;

		for(int i=0; i<flux->GetEntries(); i++){
			flux->GetEntry(i);


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

				// selecting specific mother particles
				for(int p=0; p<partiID.size(); p++) {

					if(thisPID == 11 && thismPID != 0) {
						if(thismPID == partiID[p]) {
							pflux[p]->Fill(thisX, thisY);
							pmom[p]->Fill(mom);
							pprocID[p]->Fill(thisProcID);
							pzver[p]->Fill(thisVZ);
							if(mom > 500) {
								cpmom[p]->Fill(mom);
								cpprocID[p]->Fill(thisProcID);
								cpzver[p]->Fill(thisVZ);
							}
						}
					}
				}

				// filling all particles
				if(thisPID == 11) {
					pflux[0]->Fill(thisX, thisY);
					pmom[0]->Fill(mom);
					pprocID[0]->Fill(thisProcID);
					pzver[0]->Fill(thisVZ);

					if(mom > 500) {
						cout << i << " p: " <<  mom << "   mpid: " << thismPID << "   proc: " << thisProcID <<  "   vz: " << thisVZ << endl ;
						cpmom[0]->Fill(mom);
						cpprocID[0]->Fill(thisProcID);
						cpzver[0]->Fill(thisVZ);
					}
				}
			}
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

void anaOption::defineHistos() {
}

void anaOption::setDirHistos() {
	cout << " Setting dir to 0 for all histos." << endl;

	for(auto *h: pflux)    { h->SetDirectory(0); }
	for(auto *h: pmom)     { h->SetDirectory(0); }
	for(auto *h: pprocID)  { h->SetDirectory(0); }
	for(auto *h: pzver)    { h->SetDirectory(0); }
	for(auto *h: cpmom)    { h->SetDirectory(0); }
	for(auto *h: cpprocID) { h->SetDirectory(0); }
	for(auto *h: cpzver)   { h->SetDirectory(0); }
}

void anaOption::writeHistos() {

	string ofname = "fluxHistos.root";

	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");

	for(auto *h: pflux)    { h->Write(); }
	for(auto *h: pmom)     { h->Write(); }
	for(auto *h: pprocID)  { h->Write(); }
	for(auto *h: pzver)    { h->Write(); }
	for(auto *h: cpmom)    { h->Write(); }
	for(auto *h: cpprocID) { h->Write(); }
	for(auto *h: cpzver)   { h->Write(); }

	of.Close()
}

void anaOption::initLeafs() {

	cout << " Leafs Initialized " << endl;

	cout << " x " << x << endl;

	x       = nullptr;
	y       = nullptr;
	vz      = nullptr;
	pid     = nullptr;
	mpid    = nullptr;
	procID  = nullptr;
	px      = nullptr;
	py      = nullptr;
	pz      = nullptr;

	cout << " x " << x << endl;

	flux->SetBranchAddress("avg_x",  &x);
	flux->SetBranchAddress("avg_y",  &y);
	flux->SetBranchAddress("vz",     &vz);
	flux->SetBranchAddress("pid",    &pid);
	flux->SetBranchAddress("mpid",   &mpid);
	flux->SetBranchAddress("procID", &procID);
	flux->SetBranchAddress("px",     &px);
	flux->SetBranchAddress("py",     &py);
	flux->SetBranchAddress("pz",     &pz);


}



