
vector<TH1F*> ratesTotal;
vector<TH1F*> ratesHadronic;
vector<TH1F*> ratesEm;
vector<TH1F*> ratesGamma;

vector<TH1F*> ratesTotalT;
vector<TH1F*> ratesHadronicT;
vector<TH1F*> ratesEmT;
vector<TH1F*> ratesGammaT;

vector<TH1F*> ratesTotalEdep;
vector<TH1F*> ratesHadronicEdep;
vector<TH1F*> ratesEmEdep;
vector<TH1F*> ratesGammaEdep;

vector<TH1F*> ratesTotalEdepZ;
vector<TH1F*> ratesHadronicEdepZ;
vector<TH1F*> ratesEmEdepZ;
vector<TH1F*> ratesGammaEdepZ;

vector<TH2F*> vertexRZ;
vector<TH1F*> vertexR;
vector<TH1F*> vertexZ;

vector<TH2F*> vertexRZT;
vector<TH1F*> vertexRT;
vector<TH1F*> vertexZT;

vector<string>   confs;
vector<string>   confsn;
vector<Color_t> colors;

vector<TH1F*> scalers1a;
vector<TH1F*> scalers1b;
vector<TH1F*> current1a;
vector<TH1F*> current1b;

// as a function of momentum
vector<TH1F*> leptons;
vector<TH1F*> gammas;
vector<TH1F*> pions;
vector<TH1F*> protons;
vector<TH1F*> neutrons;


// as a function of momentum
vector<TH1F*> leptonsZ;
vector<TH1F*> gammasZ;
vector<TH1F*> pionsZ;
vector<TH1F*> protonsZ;
vector<TH1F*> neutronsZ;

string rateType;
bool withThreshold;
bool zoomed;

void loadHistos() {
	string fname = "ftofHistos.root";
	cout << " Opening file " << fname << endl;

	TFile *f = new TFile(fname.c_str());

	for(unsigned h=0; h<confs.size(); h++) {
		cout << " Loading " << confs[h] << " configuration " << endl;

		string name = "ratesTotal_" + confs[h];
		ratesTotal.push_back((TH1F*) f->Get(name.c_str()));
		ratesTotal.back()->SetMinimum(0);
		ratesTotal.back()->SetLineColor(colors[h]);
		ratesTotal.back()->SetDirectory(0);

		name = "ratesHadronic_" + confs[h];
		ratesHadronic.push_back((TH1F*) f->Get(name.c_str()));
		ratesHadronic.back()->SetMinimum(0);
		ratesHadronic.back()->SetLineColor(colors[h]);
		ratesHadronic.back()->SetDirectory(0);

		name = "ratesEm_" + confs[h];
		ratesEm.push_back((TH1F*) f->Get(name.c_str()));
		ratesEm.back()->SetMinimum(0);
		ratesEm.back()->SetLineColor(colors[h]);
		ratesEm.back()->SetDirectory(0);

		name = "ratesGamma_" + confs[h];
		ratesGamma.push_back((TH1F*) f->Get(name.c_str()));
		ratesGamma.back()->SetMinimum(0);
		ratesGamma.back()->SetLineColor(colors[h]);
		ratesGamma.back()->SetDirectory(0);


		name = "ratesTotalT_" + confs[h];
		ratesTotalT.push_back((TH1F*) f->Get(name.c_str()));
		ratesTotalT.back()->SetMaximum(1.1);
		ratesTotalT.back()->SetMinimum(0);
		ratesTotalT.back()->SetLineColor(colors[h]);
		ratesTotalT.back()->SetDirectory(0);

		name = "ratesHadronicT_" + confs[h];
		ratesHadronicT.push_back((TH1F*) f->Get(name.c_str()));
		ratesHadronicT.back()->SetMaximum(0.25);
		ratesHadronicT.back()->SetMinimum(0);
		ratesHadronicT.back()->SetLineColor(colors[h]);
		ratesHadronicT.back()->SetDirectory(0);

		name = "ratesEmT_" + confs[h];
		ratesEmT.push_back((TH1F*) f->Get(name.c_str()));
		ratesEmT.back()->SetMaximum(0.3);
		ratesEmT.back()->SetMinimum(0);
		ratesEmT.back()->SetLineColor(colors[h]);
		ratesEmT.back()->SetDirectory(0);

		name = "ratesGammaT_" + confs[h];
		ratesGammaT.push_back((TH1F*) f->Get(name.c_str()));
		ratesGammaT.back()->SetMaximum(0.2);
		ratesGammaT.back()->SetMinimum(0);
		ratesGammaT.back()->SetLineColor(colors[h]);
		ratesGammaT.back()->SetDirectory(0);

		name = "ratesTotalEdep_" + confs[h];
		ratesTotalEdep.push_back((TH1F*) f->Get(name.c_str()));
		ratesTotalEdep.back()->SetMaximum(0.014);
		ratesTotalEdep.back()->SetMinimum(0.000001);
		ratesTotalEdep.back()->SetLineColor(colors[h]);
		ratesTotalEdep.back()->SetDirectory(0);

		name = "ratesHadronicEdep_" + confs[h];
		ratesHadronicEdep.push_back((TH1F*) f->Get(name.c_str()));
		ratesHadronicEdep.back()->SetMaximum(0.014);
		ratesHadronicEdep.back()->SetMinimum(0.000001);
		ratesHadronicEdep.back()->SetLineColor(colors[h]);
		ratesHadronicEdep.back()->SetDirectory(0);

		name = "ratesEmEdep_" + confs[h];
		ratesEmEdep.push_back((TH1F*) f->Get(name.c_str()));
		ratesEmEdep.back()->SetMaximum(0.014);
		ratesEmEdep.back()->SetMinimum(0.000001);
		ratesEmEdep.back()->SetLineColor(colors[h]);
		ratesEmEdep.back()->SetDirectory(0);

		name = "ratesGammaEdep_" + confs[h];
		ratesGammaEdep.push_back((TH1F*) f->Get(name.c_str()));
		ratesGammaEdep.back()->SetMaximum(0.014);
		ratesGammaEdep.back()->SetMinimum(0.000001);
		ratesGammaEdep.back()->SetLineColor(colors[h]);
		ratesGammaEdep.back()->SetDirectory(0);



		name = "ratesTotalEdepZ_" + confs[h];
		ratesTotalEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ratesTotalEdepZ.back()->SetMinimum(0.000001);
		ratesTotalEdepZ.back()->SetLineColor(colors[h]);
		ratesTotalEdepZ.back()->SetDirectory(0);

		name = "ratesHadronicEdepZ_" + confs[h];
		ratesHadronicEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ratesHadronicEdepZ.back()->SetMinimum(0.000001);
		ratesHadronicEdepZ.back()->SetLineColor(colors[h]);
		ratesHadronicEdepZ.back()->SetDirectory(0);

		name = "ratesEmEdepZ_" + confs[h];
		ratesEmEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ratesEmEdepZ.back()->SetMinimum(0.000001);
		ratesEmEdepZ.back()->SetLineColor(colors[h]);
		ratesEmEdepZ.back()->SetDirectory(0);

		name = "ratesGammaEdepZ_" + confs[h];
		ratesGammaEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ratesGammaEdepZ.back()->SetMinimum(0.000001);
		ratesGammaEdepZ.back()->SetLineColor(colors[h]);
		ratesGammaEdepZ.back()->SetDirectory(0);



		name = "vertexRZ_" + confs[h];
		vertexRZ.push_back((TH2F*) f->Get(name.c_str()));
		vertexRZ.back()->SetMaximum(1);
		vertexRZ.back()->SetDirectory(0);

		name = "vertexR_" + confs[h];
		vertexR.push_back((TH1F*) f->Get(name.c_str()));
		vertexR.back()->SetLineColor(colors[h]);
		vertexR.back()->SetDirectory(0);

		name = "vertexZ_" + confs[h];
		vertexZ.push_back((TH1F*) f->Get(name.c_str()));
		vertexZ.back()->SetLineColor(colors[h]);
		vertexZ.back()->SetDirectory(0);

		name = "vertexRZT_" + confs[h];
		vertexRZT.push_back((TH2F*) f->Get(name.c_str()));
		vertexRZT.back()->SetMaximum(0.2);
		vertexRZT.back()->SetDirectory(0);

		name = "vertexRT_" + confs[h];
		vertexRT.push_back((TH1F*) f->Get(name.c_str()));
		vertexRT.back()->SetLineColor(colors[h]);
		vertexRT.back()->SetDirectory(0);

		name = "vertexZT_" + confs[h];
		vertexZT.push_back((TH1F*) f->Get(name.c_str()));
		vertexZT.back()->SetLineColor(colors[h]);
		vertexZT.back()->SetDirectory(0);


		name = "scalers1a_" + confs[h];
		scalers1a.push_back((TH1F*) f->Get(name.c_str()));
		scalers1a.back()->SetMinimum(0);
		scalers1a.back()->SetLineColor(colors[h]);
		scalers1a.back()->SetDirectory(0);

		name = "scalers1b_" + confs[h];
		scalers1b.push_back((TH1F*) f->Get(name.c_str()));
		scalers1b.back()->SetMinimum(0);
		scalers1b.back()->SetLineColor(colors[h]);
		scalers1b.back()->SetDirectory(0);


		name = "current1a_" + confs[h];
		current1a.push_back((TH1F*) f->Get(name.c_str()));
		current1a.back()->SetMinimum(0);
		current1a.back()->SetLineColor(colors[h]);
		current1a.back()->SetDirectory(0);

		name = "current1b_" + confs[h];
		current1b.push_back((TH1F*) f->Get(name.c_str()));
		current1b.back()->SetMinimum(0);
		current1b.back()->SetLineColor(colors[h]);
		current1b.back()->SetDirectory(0);

	



		name = "leptons_" + confs[h];
		leptons.push_back((TH1F*) f->Get(name.c_str()));
		leptons.back()->SetLineColor(colors[0]);
		leptons.back()->SetMinimum(0.001);
		leptons.back()->SetDirectory(0);

		name = "gammas_" + confs[h];
		gammas.push_back((TH1F*) f->Get(name.c_str()));
		gammas.back()->SetLineColor(colors[1]);
		gammas.back()->SetMinimum(0.001);
		gammas.back()->SetDirectory(0);

		name = "pions_" + confs[h];
		pions.push_back((TH1F*) f->Get(name.c_str()));
		pions.back()->SetLineColor(colors[2]);
		pions.back()->SetMinimum(0.001);
		pions.back()->SetDirectory(0);

		name = "protons_" + confs[h];
		protons.push_back((TH1F*) f->Get(name.c_str()));
		protons.back()->SetLineColor(colors[3]);
		protons.back()->SetMinimum(0.001);
		protons.back()->SetDirectory(0);

		name = "neutrons_" + confs[h];
		neutrons.push_back((TH1F*) f->Get(name.c_str()));
		neutrons.back()->SetLineColor(colors[4]);
		neutrons.back()->SetMinimum(0.001);
		neutrons.back()->SetDirectory(0);


		// zoomed in
		name = "leptonsZ_" + confs[h];
		leptonsZ.push_back((TH1F*) f->Get(name.c_str()));
		leptonsZ.back()->SetLineColor(colors[0]);
		leptonsZ.back()->SetMinimum(0.001);
		leptonsZ.back()->SetDirectory(0);

		name = "gammasZ_" + confs[h];
		gammasZ.push_back((TH1F*) f->Get(name.c_str()));
		gammasZ.back()->SetLineColor(colors[1]);
		gammasZ.back()->SetMinimum(0.001);
		gammasZ.back()->SetDirectory(0);

		name = "pionsZ_" + confs[h];
		pionsZ.push_back((TH1F*) f->Get(name.c_str()));
		pionsZ.back()->SetLineColor(colors[2]);
		pionsZ.back()->SetMinimum(0.001);
		pionsZ.back()->SetDirectory(0);

		name = "protonsZ_" + confs[h];
		protonsZ.push_back((TH1F*) f->Get(name.c_str()));
		protonsZ.back()->SetLineColor(colors[3]);
		protonsZ.back()->SetMinimum(0.001);
		protonsZ.back()->SetDirectory(0);

		name = "neutronsZ_" + confs[h];
		neutronsZ.push_back((TH1F*) f->Get(name.c_str()));
		neutronsZ.back()->SetLineColor(colors[4]);
		neutronsZ.back()->SetMinimum(0.001);
		neutronsZ.back()->SetDirectory(0);


	}

	cout << " done. " << endl;
	f->Close();

}

vector<TH1F*> getRateHistos(string kind) {
	if(        kind == "total") {
		if(withThreshold) {
			return ratesTotalT;
		}
		return ratesTotal;
	} else if (kind == "em") {
		if(withThreshold) {
			return ratesEmT;
		}
		return ratesEm;
	} else if (kind == "hadronic") {
		if(withThreshold) {
			return ratesHadronicT;
		}
		return ratesHadronic;
	} else if (kind == "gamma") {
		if(withThreshold) {
			return ratesGammaT;
		}
		return ratesGamma;
	}

	return ratesTotalT;
}

vector<TH1F*> getEHistos(string kind) {
	if(        kind == "total") {
		if(zoomed) {
			return ratesTotalEdepZ;
		}
		return ratesTotalEdep;
	} else if (kind == "em") {
		if(zoomed) {
			return ratesEmEdepZ;
		}
		return ratesEmEdep;
	} else if (kind == "hadronic") {
		if(zoomed) {
			return ratesHadronicEdepZ;
		}
		return ratesHadronicEdep;
	} else if (kind == "gamma") {
		if(zoomed) {
			return ratesGammaEdepZ;
		}
		return ratesGammaEdep;
	}

	return ratesTotalEdep;
}



// root[0] .x show.C
void show()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	confs  = { "noShield",	"shield01" , "shield02", "shield05", "shield10" };
	confsn = {       "no",     "0.1mm" ,    "0.2mm",    "0.5mm",    "1.0mm" };
	colors = {     kBlack,        kBlue,     kRed-2,   kOrange+1,     kPink };

//	confs  = {"bstShieldftofNoShield",	"bstShieldftof0.1mm"	 };
//	confsn = {            "bstShield", 	             "0.1mm"  };
//	colors = {                 kBlack,                 kRed-2 };


	rateType = "total";
	withThreshold = true;
	zoomed = false;

	loadHistos();

	TControlBar *bar = new TControlBar("vertical", "ftof Study", 1600, 200);
	bar->AddButton("", "");
	bar->AddButton("Show Paddle Rates",     "showPaddles()");
	bar->AddButton("Show Energy Deposited", "showEdep()");
	bar->AddButton("", "");
	bar->AddButton("Show 2D Vertex",        "show2DVertex()");
	bar->AddButton("Show Z Vertex",         "showZVertex()");
	bar->AddButton("Show R Vertex",         "showRVertex()");
	bar->AddButton("", "");
	bar->AddButton("Show Scalers",          "showScalers()");
	bar->AddButton("Show Current",          "showCurrent()");
	bar->AddButton("", "");
	bar->AddButton("Set rates to Total",    "setRates(0)");
	bar->AddButton("Set rates to EM",       "setRates(1)");
	bar->AddButton("Set rates to Hadronic", "setRates(2)");
	bar->AddButton("Set rates to Gamma",    "setRates(3)");
	bar->AddButton("", "");
	bar->AddButton("Switch Threshold",      "switchT()");
	bar->AddButton("Switch Zoomed",         "switchZ()");
	bar->AddButton("", "");
	bar->AddButton("Show Momentum",         "showMomentum()");
	bar->AddButton("", "");
	bar->Show();
	gROOT->SaveContext();
}


void switchT() {
	withThreshold = !withThreshold;
	cout << " Threshold: " << withThreshold << endl;
}

void switchZ() {
	zoomed = !zoomed;
	cout << " Zoomed: " << zoomed << endl;
}


void setRates(int kind){
	if(         kind ==0) {
		rateType = "total";
	} else if (kind == 1) {
		rateType = "em";
	} else if (kind == 2) {
		rateType = "hadronic";
	} else if (kind == 3) {
		rateType = "gamma";
	}
	cout << " Rates set to " << rateType << endl;
}



void showPaddles() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);


	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);

	vector<TH1F*> histos = getRateHistos(rateType);

	histos[0]->Draw("H");
	for(unsigned h=1; h<confs.size(); h++) {
		histos[h]->Draw("Hsame");
	}

	// fitting and getting avg
	vector<double> avg;
	for(unsigned h=0; h<confs.size(); h++) {
		avg.push_back(histos[h]->Integral());
	}

	TLegend *tconfs  = new TLegend(0.6, 0.82, 0.99, 0.99);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs->AddEntry(histos[h], Form("%s: %3.2f MHz", confsn[h].c_str(), avg[h] ), "F");
	}

	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();

	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);
	lab.SetTextAngle(90);

	lab.DrawLatex(0.05, 0.55,  "Rates (MHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.6, 0.02,  "Paddle Number" );


	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.1, 0.9,  Form("%s rate for different shielding", rateType.c_str()) );
	if(withThreshold) {
		lab.DrawLatex(0.1, 0.85,  "with 1 MeV Threshold");
	} else {
		lab.DrawLatex(0.1, 0.85,  "No Threshold");
	}
}



void showEdep() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);


	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);


	vector<TH1F*> histos = getEHistos(rateType);

	histos[0]->Draw("H");
	for(unsigned h=1; h<confs.size(); h++) {
		histos[h]->Draw("Hsame");
	}

	// integral
	vector<double> integrals;
	for(unsigned h=0; h<confs.size(); h++) {
		integrals.push_back(histos[h]->Integral());
	}

	TLegend *tconfs  = new TLegend(0.6, 0.3, 0.96, 0.99);
	for(unsigned h=0; h<confs.size(); h++) {
		if(zoomed) {
			tconfs->AddEntry(histos[h], Form("%s %3.2f MHz in 0-120 KeV", confsn[h].c_str(), integrals[h] ), "F");
		} else {
			tconfs->AddEntry(histos[h], Form("%s %3.2f MHz in 0-50 MeV",  confsn[h].c_str(), integrals[h] ), "F");
		}
	}

	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();

	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);

	lab.SetTextAngle(90);
	lab.DrawLatex(0.04, 0.55,  "Rates (MHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.6, 0.02,  "Energy Deposited [Mev]" );


	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.1, 0.9,  Form("%s rate for different shielding", rateType.c_str()) );

}


void show2DVertex() {

	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPalette(1);

	vector<TCanvas*> verts;

	for(unsigned h=0; h<confs.size(); h++) {

		verts.push_back(new TCanvas(confs[h].c_str(), confs[h].c_str(), 1400, 1000));

		if(withThreshold) {
			vertexRZT[h]->Draw("colz");
		} else {
			vertexRZ[h]->Draw("colz");
		}

		TLatex lab;
		lab.SetTextFont(42);
		lab.SetTextSize(0.045);
		lab.SetTextColor(kBlue+3);
		lab.SetNDC(1);

		lab.SetTextAngle(90);
		lab.DrawLatex(0.04, 0.52,  "Vertex R    [cm]" );

		lab.SetTextAngle(0);
		lab.DrawLatex(0.7, 0.02,  "Vertex Z    [cm]" );

		lab.SetTextSize(0.05);
		lab.SetTextColor(kRed+3);
		lab.DrawLatex(0.2, 0.92,  Form("Rate for configuration: %s", confsn[h].c_str()));

	}
}

void showZVertex() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);

	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);

	if(withThreshold) {
		vertexZT[4]->Draw("H");
		for(unsigned h=0; h<confs.size(); h++) {
			vertexZT[h]->Draw("Hsame");
		}
	} else {
		vertexZ[0]->Draw("H");
		for(unsigned h=1; h<confs.size(); h++) {
			vertexZ[h]->Draw("Hsame");
		}
	}



	// integral
	vector<double> integrals;
	for(unsigned h=0; h<confs.size(); h++) {
		if(withThreshold) {
			integrals.push_back(vertexZT[h]->Integral());
		} else {
			integrals.push_back(vertexZ[h]->Integral());
		}
	}

	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);

	lab.SetTextAngle(90);
	lab.DrawLatex(0.04, 0.55,  "Rates (KHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.7, 0.02,  "Vertex Z    [mm]" );

	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.2, 0.92,  Form("Z vertex for all configurations"));

	TLegend *tconfs  = new TLegend(0.6, 0.35, 0.96, 0.9);
	for(unsigned h=0; h<confs.size(); h++) {
		if(withThreshold) {
			tconfs->AddEntry(vertexZT[h], Form("%s: %3.2f KHz", confsn[h].c_str(), integrals[h] ), "F");
		} else {
			tconfs->AddEntry(vertexZ[h], Form("%s: %3.2f KHz", confsn[h].c_str(), integrals[h] ), "F");
		}
	}

	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();
}


void showRVertex() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);

	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);

	if(withThreshold) {
		vertexRT[4]->Draw("H");
		for(unsigned h=0; h<confs.size(); h++) {
			vertexRT[h]->Draw("Hsame");
		}
	} else {
		vertexR[0]->Draw("H");
		for(unsigned h=1; h<confs.size(); h++) {
			vertexR[h]->Draw("Hsame");
		}
	}



	// integral
	vector<double> integrals;
	if(withThreshold) {
		for(unsigned h=0; h<confs.size(); h++) {
			integrals.push_back(vertexRT[h]->Integral());
		}
	} else {
		for(unsigned h=0; h<confs.size(); h++) {
			integrals.push_back(vertexR[h]->Integral());
		}
	}

	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);

	lab.SetTextAngle(90);
	lab.DrawLatex(0.04, 0.55,  "Rates (KHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.7, 0.02,  "Vertex R    [mm]" );

	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.2, 0.92,  Form("R vertex for all configurations"));

	TLegend *tconfs  = new TLegend(0.6, 0.3, 0.96, 0.9);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs->AddEntry(vertexR[h], Form("%s: %3.2f KHz", confsn[h].c_str(), integrals[h] ), "F");
	}

	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();
}




void showScalers() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);

	TCanvas *ratesUp = new TCanvas("ratesUp", "ratesUp", 1400, 1000);

	double adjustedMax = scalers1a[0]->GetMaximum()*1.3;

	scalers1a[0]->SetMaximum(adjustedMax);

	scalers1a[0]->Draw("H");

	for(unsigned h=1; h<confs.size(); h++) {
		scalers1a[h]->Draw("Hsame");
	}

	TLatex lab1;
	lab1.SetTextFont(42);
	lab1.SetTextSize(0.045);
	lab1.SetTextColor(kBlue+3);
	lab1.SetNDC(1);

	lab1.SetTextAngle(90);
	lab1.DrawLatex(0.04, 0.55,  "Rates (KHz)" );

	lab1.SetTextAngle(0);
	lab1.DrawLatex(0.6, 0.02,  "Paddle Number" );

	lab1.SetTextSize(0.05);
	lab1.SetTextColor(kRed+3);
	lab1.DrawLatex(0.2, 0.92,  Form("Upstream Scaler Rates"));

	TLegend *tconfs1  = new TLegend(0.4, 0.2, 0.9, 0.6);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs1->AddEntry(scalers1a[h], confsn[h].c_str(), "F");
	}

	tconfs1->SetBorderSize(0);
	tconfs1->SetFillColor(0);
	tconfs1->Draw();

	TCanvas *ratesDown = new TCanvas("ratesDown", "ratesDown", 1400, 1000);

	adjustedMax = scalers1b[0]->GetMaximum()*1.3;
	scalers1b[0]->SetMaximum(adjustedMax);
	
	scalers1b[0]->Draw("H");

	for(unsigned h=1; h<confs.size(); h++) {
		scalers1b[h]->Draw("Hsame");
	}

	TLatex lab2;
	lab2.SetTextFont(42);
	lab2.SetTextSize(0.045);
	lab2.SetTextColor(kBlue+3);
	lab2.SetNDC(1);

	lab2.SetTextAngle(90);
	lab2.DrawLatex(0.04, 0.55,  "Rates (KHz)" );

	lab2.SetTextAngle(0);
	lab2.DrawLatex(0.6, 0.02,  "Paddle Number" );

	lab2.SetTextSize(0.05);
	lab2.SetTextColor(kRed+3);
	lab2.DrawLatex(0.2, 0.92,  Form("Downstream Scaler Rates"));

	TLegend *tconfs2  = new TLegend(0.4, 0.2, 0.9, 0.6);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs2->AddEntry(scalers1b[h], confsn[h].c_str(), "F");
	}

	tconfs2->SetBorderSize(0);
	tconfs2->SetFillColor(0);
	tconfs2->Draw();
}


void showCurrent() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);

	TCanvas *ratesUp = new TCanvas("ratesUp", "ratesUp", 1400, 1000);

	current1a[0]->Draw("H");

	for(unsigned h=1; h<confs.size(); h++) {
		current1a[h]->Draw("Hsame");
	}

	TLatex lab1;
	lab1.SetTextFont(42);
	lab1.SetTextSize(0.045);
	lab1.SetTextColor(kBlue+3);
	lab1.SetNDC(1);

	lab1.SetTextAngle(90);
	lab1.DrawLatex(0.04, 0.55,  "Current (#muA)" );

	lab1.SetTextAngle(0);
	lab1.DrawLatex(0.6, 0.02,  "Paddle Number" );

	lab1.SetTextSize(0.05);
	lab1.SetTextColor(kRed+3);
	lab1.DrawLatex(0.2, 0.92,  Form("Upstream Current"));

	TLegend *tconfs1  = new TLegend(0.2, 0.2, 0.8, 0.6);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs1->AddEntry(current1a[h], confsn[h].c_str(), "F");
	}

	tconfs1->SetBorderSize(0);
	tconfs1->SetFillColor(0);
	tconfs1->Draw();

	TCanvas *ratesDown = new TCanvas("ratesDown", "ratesDown", 1400, 1000);

	current1b[0]->Draw("H");

	for(unsigned h=1; h<confs.size(); h++) {
		current1b[h]->Draw("Hsame");
	}

	TLatex lab2;
	lab2.SetTextFont(42);
	lab2.SetTextSize(0.045);
	lab2.SetTextColor(kBlue+3);
	lab2.SetNDC(1);

	lab2.SetTextAngle(90);
	lab2.DrawLatex(0.04, 0.55,  "Current (#muA)" );

	lab2.SetTextAngle(0);
	lab2.DrawLatex(0.6, 0.02,  "Paddle Number" );

	lab2.SetTextSize(0.05);
	lab2.SetTextColor(kRed+3);
	lab2.DrawLatex(0.2, 0.92,  Form("Downstream Current"));

	TLegend *tconfs2  = new TLegend(0.2, 0.2, 0.8, 0.6);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs2->AddEntry(current1b[h], confsn[h].c_str(), "F");
	}

	tconfs2->SetBorderSize(0);
	tconfs2->SetFillColor(0);
	tconfs2->Draw();
}


void showMomentum() {

	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.14);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPalette(1);


	vector<TCanvas*> moms;

	for(unsigned h=0; h<confs.size(); h++) {

		moms.push_back(new TCanvas(confs[h].c_str(), confs[h].c_str(), 1400, 1000));
		gPad->SetLogy();

		if(zoomed) {
			leptonsZ[h]->Draw("H");
			gammasZ[h]->Draw("Hsame");
			pionsZ[h]->Draw("Hsame");
			protonsZ[h]->Draw("Hsame");
			neutronsZ[h]->Draw("Hsame");
		} else {
			leptons[h]->Draw("H");
			gammas[h]->Draw("Hsame");
			pions[h]->Draw("Hsame");
			protons[h]->Draw("Hsame");
			neutrons[h]->Draw("Hsame");
		}
		TLatex lab;
		lab.SetTextFont(42);
		lab.SetTextSize(0.045);
		lab.SetTextColor(kBlue+3);
		lab.SetNDC(1);

		lab.SetTextAngle(90);
		lab.DrawLatex(0.04, 0.52,  "Rates    [KHz]" );

		lab.SetTextAngle(0);
		lab.DrawLatex(0.7, 0.02,  "Momentum    [MeV]" );

		lab.SetTextSize(0.05);
		lab.SetTextColor(kRed+3);
		lab.DrawLatex(0.2, 0.92,  Form("Rate for configuration: %s", confs[h].c_str()));


		TLegend *tconfs2  = new TLegend(0.5, 0.5, 0.92, 0.9);
		tconfs2->AddEntry(leptons[h],  "leptons", "F");
		tconfs2->AddEntry(gammas[h],   "gammas", "F");
		tconfs2->AddEntry(pions[h],    "pions", "F");
		tconfs2->AddEntry(protons[h],  "protons", "F");
		tconfs2->AddEntry(neutrons[h], "neutrons", "F");


		tconfs2->SetBorderSize(0);
		tconfs2->SetFillColor(0);
		tconfs2->Draw();


	}
}
