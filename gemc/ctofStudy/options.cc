#include "options.h"

#include <iostream>

#include "TFile.h"
#include "TCanvas.h"

anaOption::anaOption(vector<string> configurations) : confs(configurations)
{
	PRINT  = "";
	
	TCanvas *c1 = new TCanvas("c1", "c1", 100,100);
	
	int cIndex = 0;
	for(auto p: confs) {
		
		string filename = "/opt/data/ctof/" + p + ".root";
		
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
	
	
	
}


void anaOption::defineHistos(string c) {
	
	cout << " Defining " << c << " histo." << endl;
	
	ctofRatesTotal.push_back(new TH1F(Form("ctofRatesTotal_%s", c.c_str()),
												 Form("ctofRatesTotal_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesHadronic.push_back(new TH1F(Form("ctofRatesHadronic_%s", c.c_str()),
													 Form("ctofRatesHadronic_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesEm.push_back(new TH1F(Form("ctofRatesEm_%s", c.c_str()),
											 Form("ctofRatesEm_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesGamma.push_back(new TH1F(Form("ctofRatesGamma_%s", c.c_str()),
												 Form("ctofRatesGamma_%s", c.c_str()), 48, 0.5, 48.5));

	ctofRatesTotalT.push_back(new TH1F(Form("ctofRatesTotalT_%s", c.c_str()),
												  Form("ctofRatesTotalT_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesHadronicT.push_back(new TH1F(Form("ctofRatesHadronicT_%s", c.c_str()),
													  Form("ctofRatesHadronicT_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesEmT.push_back(new TH1F(Form("ctofRatesEmT_%s", c.c_str()),
											  Form("ctofRatesEmT_%s", c.c_str()), 48, 0.5, 48.5));
	ctofRatesGammaT.push_back(new TH1F(Form("ctofRatesGammaT_%s", c.c_str()),
												  Form("ctofRatesGammaT_%s", c.c_str()), 48, 0.5, 48.5));

	ctofRatesTotalEdep.push_back(new TH1F(Form("ctofRatesTotalEdep_%s", c.c_str()),
													  Form("ctofRatesTotalEdep_%s", c.c_str()), 200, 0, 100));
	ctofRatesHadronicEdep.push_back(new TH1F(Form("ctofRatesHadronicEdep_%s", c.c_str()),
														  Form("ctofRatesHadronicEdep_%s", c.c_str()), 200, 0, 100));
	ctofRatesEmEdep.push_back(new TH1F(Form("ctofRatesEmEdep_%s", c.c_str()),
												  Form("ctofRatesEmEdep_%s", c.c_str()), 200, 0, 100));
	ctofRatesGammaEdep.push_back(new TH1F(Form("ctofRatesGammaEdep_%s", c.c_str()),
													  Form("ctofRatesGammaEdep_%s", c.c_str()), 200, 0, 100));
	
	ctofRatesTotalEdepZ.push_back(new TH1F(Form("ctofRatesTotalEdepZ_%s", c.c_str()),
														Form("ctofRatesTotalEdepZ_%s", c.c_str()), 200, 0, 0.2));
	ctofRatesHadronicEdepZ.push_back(new TH1F(Form("ctofRatesHadronicEdepZ_%s", c.c_str()),
															Form("ctofRatesHadronicEdepZ_%s", c.c_str()), 200, 0, 0.2));
	ctofRatesEmEdepZ.push_back(new TH1F(Form("ctofRatesEmEdepZ_%s", c.c_str()),
													Form("ctofRatesEmEdepZ_%s", c.c_str()), 200, 0, 0.2));
	ctofRatesGammaEdepZ.push_back(new TH1F(Form("ctofRatesGammaEdepZ_%s", c.c_str()),
														Form("ctofRatesGammaEdepZ_%s", c.c_str()), 200, 0, 0.2));
	
}

void anaOption::setDirHistos(int cIndex) {
	cout << " Setting dir to index " << cIndex << " histos." << endl;
	
	ctofRatesTotal[cIndex]->SetDirectory(0);
	ctofRatesHadronic[cIndex]->SetDirectory(0);
	ctofRatesEm[cIndex]->SetDirectory(0);
	ctofRatesGamma[cIndex]->SetDirectory(0);

	ctofRatesTotalT[cIndex]->SetDirectory(0);
	ctofRatesHadronicT[cIndex]->SetDirectory(0);
	ctofRatesEmT[cIndex]->SetDirectory(0);
	ctofRatesGammaT[cIndex]->SetDirectory(0);

	ctofRatesTotalEdep[cIndex]->SetDirectory(0);
	ctofRatesHadronicEdep[cIndex]->SetDirectory(0);
	ctofRatesEmEdep[cIndex]->SetDirectory(0);
	ctofRatesGammaEdep[cIndex]->SetDirectory(0);
	
	ctofRatesTotalEdepZ[cIndex]->SetDirectory(0);
	ctofRatesHadronicEdepZ[cIndex]->SetDirectory(0);
	ctofRatesEmEdepZ[cIndex]->SetDirectory(0);
	ctofRatesGammaEdepZ[cIndex]->SetDirectory(0);
	
}

void anaOption::writeHistos() {
	
	string ofname = "ctofHistos.root";
	
	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");
	
	// scaling so that the re
	for(auto *h: ctofRatesTotal)    { h->Write(); }
	for(auto *h: ctofRatesHadronic) { h->Write(); }
	for(auto *h: ctofRatesEm)       { h->Write(); }
	for(auto *h: ctofRatesGamma)    { h->Write(); }

	for(auto *h: ctofRatesTotalT)    { h->Write(); }
	for(auto *h: ctofRatesHadronicT) { h->Write(); }
	for(auto *h: ctofRatesEmT)       { h->Write(); }
	for(auto *h: ctofRatesGammaT)    { h->Write(); }

	for(auto *h: ctofRatesTotalEdep)    { h->Write(); }
	for(auto *h: ctofRatesHadronicEdep) { h->Write(); }
	for(auto *h: ctofRatesEmEdep)       { h->Write(); }
	for(auto *h: ctofRatesGammaEdep)    { h->Write(); }
	
	for(auto *h: ctofRatesTotalEdepZ)    { h->Write(); }
	for(auto *h: ctofRatesHadronicEdepZ) { h->Write(); }
	for(auto *h: ctofRatesEmEdepZ)       { h->Write(); }
	for(auto *h: ctofRatesGammaEdepZ)    { h->Write(); }
	
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
	
	int nevents = ctof->GetEntries();
	
	const double TWINDOW = 248E-9;
	const double threshold = 1.0;
	double totalTime = ((double) nevents)*TWINDOW;


	cout << " " << nevents << " number of ecents for a total of " << totalTime * 1000 << " milliseconds of beam on target." << endl;
	
	for(int i=0; i<ctof->GetEntries(); i++){
		
		ctof->GetEntry(i);
		generated->GetEntry(i);
		
		//		if(i%10 == 0) cout << " Entry number " << i << endl;
		
		int thisPaddle = 0;
		
		double thisX  = 0;
		double thisY  = 0;
		double thisZ  = 0;
		
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
			
			// weight to give rates in MHz.
			double weight = 1.0/(totalTime*1000000);
			
			// filling all particles
			ctofRatesTotal[cindex]->Fill(thisPaddle, weight);
			if(thisEdep > threshold) {
				ctofRatesTotalT[cindex]->Fill(thisPaddle, weight);
			}
			ctofRatesTotalEdep[cindex]->Fill(thisEdep, weight);
			ctofRatesTotalEdepZ[cindex]->Fill(thisEdep, weight);
			
			// e.m.
			if(thisPID ==11 || thisPID == -11 || thisPID == 22) {
				ctofRatesEm[cindex]->Fill(thisPaddle, weight);
				if(thisEdep > threshold) {
					ctofRatesEmT[cindex]->Fill(thisPaddle, weight);
				}
				ctofRatesEmEdep[cindex]->Fill(thisEdep, weight);
				ctofRatesEmEdepZ[cindex]->Fill(thisEdep, weight);
			} else {
				// hadronic
				ctofRatesHadronic[cindex]->Fill(thisPaddle, weight);
				if(thisEdep > threshold) {
					ctofRatesHadronicT[cindex]->Fill(thisPaddle, weight);
				}
				ctofRatesHadronicEdep[cindex]->Fill(thisEdep, weight);
				ctofRatesHadronicEdepZ[cindex]->Fill(thisEdep, weight);
			}
			// just gammas
			if(thisPID == 22 || thismPID == 22) {
				ctofRatesGamma[cindex]->Fill(thisPaddle, weight);
				if(thisEdep > threshold) {
					ctofRatesGammaT[cindex]->Fill(thisPaddle, weight);
				}
				ctofRatesGammaEdep[cindex]->Fill(thisEdep, weight);
				ctofRatesGammaEdepZ[cindex]->Fill(thisEdep, weight);
			}
			
		}
	}
	
}





