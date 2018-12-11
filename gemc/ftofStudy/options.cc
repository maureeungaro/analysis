#include "options.h"

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TCanvas.h"

anaOption::anaOption(vector<string> configurations) : confs(configurations)
{
	PRINT  = "";

	// load paddle infos from file
	// The first column in the FTOF panel-1b conter attenuation lengths (cm)
	// and the second column is the associated counter length (cm).
	ifstream ftofIN("p1b-info.dat");

	double a, l;
	for(unsigned p=0; p<62; p++) {
		ftofIN >> a >> l;
		paddleAttLength.push_back(a*10);
		paddleLength.push_back(l*10);
	}
	ftofIN.close();
	cout << " Ftof lengths loaded with " << paddleAttLength.size() << " entries" << endl;


	TCanvas *c1 = new TCanvas("c1", "c1", 100,100);

	int cIndex = 0;
	for(auto p: confs) {
		
		string filename = "/opt/data/ftof/" + p + ".root";
		
		TFile f(filename.c_str());
		f.GetObject("generated", generated);
		f.GetObject("ftof",      ftof);
		
		cout << " File " << filename << " opened. " << endl;
		
		defineHistos(p);
		cout << " Initializing ftof histos with " << generated->GetEntries() << " entries..." << endl;
		
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
	
	ratesTotal.push_back(new TH1F(Form("ratesTotal_%s", c.c_str()),
											  Form("ratesTotal_%s", c.c_str()), 62, 0.5, 62.5));
	ratesHadronic.push_back(new TH1F(Form("ratesHadronic_%s", c.c_str()),
												Form("ratesHadronic_%s", c.c_str()), 62, 0.5, 62.5));
	ratesEm.push_back(new TH1F(Form("ratesEm_%s", c.c_str()),
										Form("ratesEm_%s", c.c_str()), 62, 0.5, 62.5));
	ratesGamma.push_back(new TH1F(Form("ratesGamma_%s", c.c_str()),
											Form("ratesGamma_%s", c.c_str()), 62, 0.5, 62.5));
	
	ratesTotalT.push_back(new TH1F(Form("ratesTotalT_%s", c.c_str()),
											 Form("ratesTotalT_%s", c.c_str()), 62, 0.5, 62.5));
	ratesHadronicT.push_back(new TH1F(Form("ratesHadronicT_%s", c.c_str()),
												 Form("ratesHadronicT_%s", c.c_str()), 62, 0.5, 62.5));
	ratesEmT.push_back(new TH1F(Form("ratesEmT_%s", c.c_str()),
										 Form("ratesEmT_%s", c.c_str()), 62, 0.5, 62.5));
	ratesGammaT.push_back(new TH1F(Form("ratesGammaT_%s", c.c_str()),
											 Form("ratesGammaT_%s", c.c_str()), 62, 0.5, 62.5));
	
	ratesTotalEdep.push_back(new TH1F(Form("ratesTotalEdep_%s", c.c_str()),
												 Form("ratesTotalEdep_%s", c.c_str()), 100, 0, 50));
	ratesHadronicEdep.push_back(new TH1F(Form("ratesHadronicEdep_%s", c.c_str()),
													 Form("ratesHadronicEdep_%s", c.c_str()), 100, 0, 50));
	ratesEmEdep.push_back(new TH1F(Form("ratesEmEdep_%s", c.c_str()),
											 Form("ratesEmEdep_%s", c.c_str()), 100, 0, 50));
	ratesGammaEdep.push_back(new TH1F(Form("ratesGammaEdep_%s", c.c_str()),
												 Form("ratesGammaEdep_%s", c.c_str()), 100, 0, 50));
	
	ratesTotalEdepZ.push_back(new TH1F(Form("ratesTotalEdepZ_%s", c.c_str()),
												  Form("ratesTotalEdepZ_%s", c.c_str()), 100, 0, 0.12));
	ratesHadronicEdepZ.push_back(new TH1F(Form("ratesHadronicEdepZ_%s", c.c_str()),
													  Form("ratesHadronicEdepZ_%s", c.c_str()), 100, 0, 0.12));
	ratesEmEdepZ.push_back(new TH1F(Form("ratesEmEdepZ_%s", c.c_str()),
											  Form("ratesEmEdepZ_%s", c.c_str()), 100, 0, 0.12));
	ratesGammaEdepZ.push_back(new TH1F(Form("ratesGammaEdepZ_%s", c.c_str()),
												  Form("ratesGammaEdepZ_%s", c.c_str()), 100, 0, 0.12));


	vertexRZ.push_back(new TH2F(Form("vertexRZ_%s", c.c_str()),
										 Form("vertexRZ_%s", c.c_str()), 600, -100, 7500, 600, -100, 4600));

	vertexR.push_back(new TH1F(Form("vertexR_%s", c.c_str()),
										Form("vertexR_%s", c.c_str()), 400, -100, 4600));

	vertexZ.push_back(new TH1F(Form("vertexZ_%s", c.c_str()),
										Form("vertexZ_%s", c.c_str()), 400, -100, 7500));

	vertexRZT.push_back(new TH2F(Form("vertexRZT_%s", c.c_str()),
										  Form("vertexRZT_%s", c.c_str()), 600, -100, 7500, 600, -100, 4600));

	vertexRT.push_back(new TH1F(Form("vertexRT_%s", c.c_str()),
										 Form("vertexRT_%s", c.c_str()), 400, -100, 4600));

	vertexZT.push_back(new TH1F(Form("vertexZT_%s", c.c_str()),
										 Form("vertexZT_%s", c.c_str()), 400, -100, 7500));


	current1a.push_back(new TH1F(Form("current1a_%s", c.c_str()),
										  Form("current1a_%s", c.c_str()), 62, 0.5, 62.5));

	current1b.push_back(new TH1F(Form("current1b_%s", c.c_str()),
											 Form("current1b_%s", c.c_str()), 62, 0.5, 62.5));

	scalers1a.push_back(new TH1F(Form("scalers1a_%s", c.c_str()),
										  Form("scalers1a_%s", c.c_str()), 62, 0.5, 62.5));

	scalers1b.push_back(new TH1F(Form("scalers1b_%s", c.c_str()),
											 Form("scalers1b_%s", c.c_str()), 62, 0.5, 62.5));




	leptons.push_back(new TH1F(Form("leptons_%s", c.c_str()),
										Form("leptons_%s", c.c_str()), 100, 0., 1000));

	gammas.push_back(new TH1F(Form("gammas_%s", c.c_str()),
									  Form("gammas_%s", c.c_str()), 100, 0., 1000));

	pions.push_back(new TH1F(Form("pions_%s", c.c_str()),
									 Form("pions_%s", c.c_str()), 100, 0., 1000));

	protons.push_back(new TH1F(Form("protons_%s", c.c_str()),
										Form("protons_%s", c.c_str()), 100, 0., 1000));

	neutrons.push_back(new TH1F(Form("neutrons_%s", c.c_str()),
										 Form("neutrons_%s", c.c_str()), 100, 0., 1000));


	leptonsZ.push_back(new TH1F(Form("leptonsZ_%s", c.c_str()),
										 Form("leptonsZ_%s", c.c_str()), 100, 0., 2));

	gammasZ.push_back(new TH1F(Form("gammasZ_%s", c.c_str()),
										Form("gammasZ_%s", c.c_str()), 100, 0., 2));

	pionsZ.push_back(new TH1F(Form("pionsZ_%s", c.c_str()),
									  Form("pionsZ_%s", c.c_str()), 100, 0., 2));

	protonsZ.push_back(new TH1F(Form("protonsZ_%s", c.c_str()),
										 Form("protonsZ_%s", c.c_str()), 100, 0., 2));

	neutronsZ.push_back(new TH1F(Form("neutronsZ_%s", c.c_str()),
										  Form("neutronsZ_%s", c.c_str()), 100, 0., 2));

}

void anaOption::setDirHistos(int cIndex) {

	cout << " Setting dir to index " << cIndex << " histos." << endl;
	
	ratesTotal[cIndex]->SetDirectory(0);
	ratesHadronic[cIndex]->SetDirectory(0);
	ratesEm[cIndex]->SetDirectory(0);
	ratesGamma[cIndex]->SetDirectory(0);
	
	ratesTotalT[cIndex]->SetDirectory(0);
	ratesHadronicT[cIndex]->SetDirectory(0);
	ratesEmT[cIndex]->SetDirectory(0);
	ratesGammaT[cIndex]->SetDirectory(0);
	
	ratesTotalEdep[cIndex]->SetDirectory(0);
	ratesHadronicEdep[cIndex]->SetDirectory(0);
	ratesEmEdep[cIndex]->SetDirectory(0);
	ratesGammaEdep[cIndex]->SetDirectory(0);
	
	ratesTotalEdepZ[cIndex]->SetDirectory(0);
	ratesHadronicEdepZ[cIndex]->SetDirectory(0);
	ratesEmEdepZ[cIndex]->SetDirectory(0);
	ratesGammaEdepZ[cIndex]->SetDirectory(0);

	vertexRZ[cIndex]->SetDirectory(0);
	vertexR[cIndex]->SetDirectory(0);
	vertexZ[cIndex]->SetDirectory(0);

	vertexRZT[cIndex]->SetDirectory(0);
	vertexRT[cIndex]->SetDirectory(0);
	vertexZT[cIndex]->SetDirectory(0);

	current1a[cIndex]->SetDirectory(0);
	current1b[cIndex]->SetDirectory(0);

	scalers1a[cIndex]->SetDirectory(0);
	scalers1b[cIndex]->SetDirectory(0);

	leptons[cIndex]->SetDirectory(0);
	gammas[cIndex]->SetDirectory(0);
	pions[cIndex]->SetDirectory(0);
	protons[cIndex]->SetDirectory(0);
	neutrons[cIndex]->SetDirectory(0);

	leptonsZ[cIndex]->SetDirectory(0);
	gammasZ[cIndex]->SetDirectory(0);
	pionsZ[cIndex]->SetDirectory(0);
	protonsZ[cIndex]->SetDirectory(0);
	neutronsZ[cIndex]->SetDirectory(0);


}

void anaOption::writeHistos() {
	
	string ofname = "ftofHistos.root";
	
	cout << " Writing all histos to file : " << ofname << endl;
	TFile of(ofname.c_str(), "RECREATE");
	
	// scaling so that the re
	for(auto *h: ratesTotal)    { h->Write(); }
	for(auto *h: ratesHadronic) { h->Write(); }
	for(auto *h: ratesEm)       { h->Write(); }
	for(auto *h: ratesGamma)    { h->Write(); }
	
	for(auto *h: ratesTotalT)    { h->Write(); }
	for(auto *h: ratesHadronicT) { h->Write(); }
	for(auto *h: ratesEmT)       { h->Write(); }
	for(auto *h: ratesGammaT)    { h->Write(); }
	
	for(auto *h: ratesTotalEdep)    { h->Write(); }
	for(auto *h: ratesHadronicEdep) { h->Write(); }
	for(auto *h: ratesEmEdep)       { h->Write(); }
	for(auto *h: ratesGammaEdep)    { h->Write(); }
	
	for(auto *h: ratesTotalEdepZ)    { h->Write(); }
	for(auto *h: ratesHadronicEdepZ) { h->Write(); }
	for(auto *h: ratesEmEdepZ)       { h->Write(); }
	for(auto *h: ratesGammaEdepZ)    { h->Write(); }

	for(auto *h: vertexRZ)   { h->Write(); }
	for(auto *h: vertexR)    { h->Write(); }
	for(auto *h: vertexZ)    { h->Write(); }
	for(auto *h: vertexRZT)   { h->Write(); }
	for(auto *h: vertexRT)    { h->Write(); }
	for(auto *h: vertexZT)    { h->Write(); }

	for(auto *h: current1a)    { h->Write(); }
	for(auto *h: current1b)  { h->Write(); }

	for(auto *h: scalers1a)    { h->Write(); }
	for(auto *h: scalers1b)  { h->Write(); }

	for(auto *h: leptons)  { h->Write(); }
	for(auto *h: gammas)   { h->Write(); }
	for(auto *h: pions)    { h->Write(); }
	for(auto *h: protons)  { h->Write(); }
	for(auto *h: neutrons) { h->Write(); }

	for(auto *h: leptonsZ)  { h->Write(); }
	for(auto *h: gammasZ)   { h->Write(); }
	for(auto *h: pionsZ)    { h->Write(); }
	for(auto *h: protonsZ)  { h->Write(); }
	for(auto *h: neutronsZ) { h->Write(); }

	of.Close();
}

void anaOption::initLeafs() {
	
	cout << " Leafs Initialized " << endl;
	
	// resetting pointer - is it necessary?
	paddle  = nullptr;
	layer   = nullptr;
	sector  = nullptr;
	lx      = nullptr;
	pid     = nullptr;
	mpid    = nullptr;
	totEdep = nullptr;
	vx      = nullptr;
	vy      = nullptr;
	vz      = nullptr;
	x       = nullptr;
	y       = nullptr;
	z       = nullptr;
	px      = nullptr;
	py      = nullptr;
	pz      = nullptr;

	ftof->SetBranchAddress("paddle",  &paddle);
	ftof->SetBranchAddress("layer",   &layer);
	ftof->SetBranchAddress("sector",  &sector);
	ftof->SetBranchAddress("avg_lx",  &lx);
	ftof->SetBranchAddress("pid",     &pid);
	ftof->SetBranchAddress("mpid",    &mpid);
	ftof->SetBranchAddress("totEdep", &totEdep);
	ftof->SetBranchAddress("vx",      &vx);
	ftof->SetBranchAddress("vy",      &vy);
	ftof->SetBranchAddress("vz",      &vz);
	ftof->SetBranchAddress("avg_x",   &x);
	ftof->SetBranchAddress("avg_y",   &y);
	ftof->SetBranchAddress("avg_z",   &z);
	ftof->SetBranchAddress("px",      &px);
	ftof->SetBranchAddress("py",      &py);
	ftof->SetBranchAddress("pz",      &pz);

}

void anaOption::fillHistos(int cindex) {
	
	int nevents = ftof->GetEntries();

	const double TWINDOW = 248E-9;
	const double threshold = 1.0;
	double totalTime = ((double) nevents)*TWINDOW;

	// weight to give rates in MHz.
	double weight       = 1.0/(totalTime*1000000);
	double weightPaddle = 1.0/(totalTime*1000000*62);

	double conversionMeVTomicroC = 0.00002768; // numbers for conversions from energy in MeV to Charge in uC are taken from Dan Carman's email of 2016/4/27

	cout << " " << nevents << " number of ecents for a total of " << totalTime * 1000 << " milliseconds of beam on target." << endl;
	
	for(int i=0; i<ftof->GetEntries(); i++){
		
		ftof->GetEntry(i);

		//		if(i%10 == 0) cout << " Entry number " << i << endl;
		
		int thisPaddle = 0;
		int thislayer  = -1;
		int thisSector = -1;

		double thisLX  = 0;

		int thisPID     = 0;
		int thismPID    = 0;
		
		double thisEdep  = 0;

		double thisVR  = 0;
		double thisVZ  = 0;

		double thisDV   = 0;

		double attRight  = 0;
		double attLeft   = 0;
		double distRight = 0;
		double distLeft  = 0;
		double eRight    = 0;
		double eLeft     = 0;

		double currentRight = 0;
		double currentLeft  = 0;

		double thisMomentum = 0;


		// looping over hits
		for(unsigned d=0; d<(*layer).size(); d++) {

			thislayer    = (*layer)[d];
			thisSector   = (*sector)[d];
			thisVR       = sqrt( (*vx)[d]*(*vx)[d] + (*vy)[d]*(*vy)[d] );
			thisVZ       = (*vz)[d];
			thisPaddle   = (*paddle)[d];
			thisMomentum = sqrt( (*px)[d]*(*px)[d] + (*py)[d]*(*py)[d] + (*pz)[d]*(*pz)[d]);

			// transverse position of the vertex
			thisDV   = sqrt( ((*vx)[d] - (*x)[d])*((*vx)[d] - (*x)[d]) + ((*vy)[d] - (*y)[d])*((*vy)[d] - (*y)[d])  );

			// careful, true hits are double counted for each ftof layer
			if(thislayer == 2 && (thisSector == 1 || thisSector == 4)) {


				double attLenght     = paddleAttLength[thisPaddle-1];
				double counterLength = paddleLength[thisPaddle-1];

				thisLX  = (*lx)[d];

				distRight = counterLength / 2 - (thisLX);
				distLeft  = counterLength / 2 + (thisLX);

				thisPID    = (*pid)[d];
				thismPID   = (*mpid)[d];

				thisEdep  = (*totEdep)[d];

				attRight = exp(-distRight/attLenght);
				attLeft  = exp(-distLeft/attLenght);
				eRight = thisEdep*attRight;
				eLeft  = thisEdep*attLeft;

				currentRight = eRight*conversionMeVTomicroC;
				currentLeft  = eLeft*conversionMeVTomicroC;

//				cout << attLenght <<  " " << distRight << endl;
//				cout << currentRight <<  " " << currentLeft << endl;

				current1a[cindex]->Fill(thisPaddle, currentLeft/totalTime);
				current1b[cindex]->Fill(thisPaddle, currentRight/totalTime);

				// scalers in KHz
				if(eRight > threshold) {
					scalers1b[cindex]->Fill(thisPaddle, weight*1000);
				}

				if(eLeft > threshold) {
					scalers1a[cindex]->Fill(thisPaddle, weight*1000);
				}


				// vertex in KHz
				vertexRZ[cindex]->Fill(thisVZ, thisVR, 1000*weightPaddle);
				vertexR[cindex]->Fill(thisVR,          1000*weightPaddle);
				vertexZ[cindex]->Fill(thisVZ,          1000*weightPaddle);
				
				if(thisEdep > threshold) {
					vertexRZT[cindex]->Fill(thisVZ, thisVR, 1000*weightPaddle);
					vertexRT[cindex]->Fill(thisVR,          1000*weightPaddle);
					vertexZT[cindex]->Fill(thisVZ,          1000*weightPaddle);
				}
				
				// filling all particles
				ratesTotal[cindex]->Fill(thisPaddle, weight);
				if(thisEdep > threshold) {
					ratesTotalT[cindex]->Fill(thisPaddle, weight);
				}
				

				ratesTotalEdep[cindex]->Fill(thisEdep, weightPaddle);
				ratesTotalEdepZ[cindex]->Fill(thisEdep, weightPaddle);

				// e.m.
				if((thisPID == 11 || thisPID == -11) ) {
					ratesEm[cindex]->Fill(thisPaddle, weight);
					if(thisEdep > threshold) {
						ratesEmT[cindex]->Fill(thisPaddle, weight);
					}
					ratesEmEdep[cindex]->Fill(thisEdep, weightPaddle);
					ratesEmEdepZ[cindex]->Fill(thisEdep, weightPaddle);
				} else if(thisPID != 22) {
					// hadronic
					ratesHadronic[cindex]->Fill(thisPaddle, weight);
					if(thisEdep > threshold) {
						ratesHadronicT[cindex]->Fill(thisPaddle, weight);
					}
					ratesHadronicEdep[cindex]->Fill(thisEdep, weightPaddle);
					ratesHadronicEdepZ[cindex]->Fill(thisEdep, weightPaddle);
				}
				// just gammas
				if(thisPID == 22) {
					ratesGamma[cindex]->Fill(thisPaddle, weight);
					if(thisEdep > threshold) {
						ratesGammaT[cindex]->Fill(thisPaddle, weight);
					}
					ratesGammaEdep[cindex]->Fill(thisEdep, weightPaddle);
					ratesGammaEdepZ[cindex]->Fill(thisEdep, weightPaddle);
				}


				// momentum in KHz
				if(thisPID == 11 || thisPID == -11 || thismPID == -11){
					leptons[cindex]->Fill(thisMomentum,   1000*weightPaddle);
					leptonsZ[cindex]->Fill(thisMomentum,  1000*weightPaddle);
				} else if(thisPID == 22 || thismPID == 22) {
					gammas[cindex]->Fill(thisMomentum,    1000*weightPaddle);
					gammasZ[cindex]->Fill(thisMomentum,   1000*weightPaddle);
				} else if(thisPID == 211 || thismPID == -211) {
					pions[cindex]->Fill(thisMomentum,     1000*weightPaddle);
					pionsZ[cindex]->Fill(thisMomentum,    1000*weightPaddle);
				} else if(thisPID == 2212 || thismPID == 2212) {
					protons[cindex]->Fill(thisMomentum,   1000*weightPaddle);
					protonsZ[cindex]->Fill(thisMomentum,  1000*weightPaddle);
				} else if(thisPID == 2112 || thismPID == 2112) {
					neutrons[cindex]->Fill(thisMomentum,  1000*weightPaddle);
					neutronsZ[cindex]->Fill(thisMomentum, 1000*weightPaddle);
				}
			}

		}
	}
	
}





