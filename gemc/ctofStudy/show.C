
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

vector<string>   confs;
vector<Color_t> colors;

string rateType;
bool withThreshold;
bool zoomed;

void loadHistos() {
	string fname = "ctofHistos.root";
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
		ratesTotalT.back()->SetMaximum(0.5);
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
		ratesGammaT.back()->SetMaximum(0.02);
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
		vertexRZ.back()->SetMaximum(800);
		vertexRZ.back()->SetDirectory(0);

		name = "vertexR_" + confs[h];
		vertexR.push_back((TH1F*) f->Get(name.c_str()));
		vertexR.back()->SetLineColor(colors[h]);
		vertexR.back()->SetDirectory(0);

		name = "vertexZ_" + confs[h];
		vertexZ.push_back((TH1F*) f->Get(name.c_str()));
		vertexZ.back()->SetLineColor(colors[h]);
		vertexZ.back()->SetDirectory(0);




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

	confs  = {"bstNoShieldCtofNoShield", "bstShieldCtofNoShield",	"bstShieldCtof1mm", "bstShieldCtof2mm", "bstShieldCtof3mm"	};
	colors = {                  kBlack,                    kBlue,                kRed-2,             kOrange,           kPink  };

	rateType = "total";
	withThreshold = true;
	zoomed = false;

	loadHistos();

	TControlBar *bar = new TControlBar("vertical", "Ctof Study", 1400, 200);
	bar->AddButton("", "");
	bar->AddButton("Show Paddle Rates",     "showPaddles()");
	bar->AddButton("Show Energy Deposited", "showEdep()");
	bar->AddButton("", "");
	bar->AddButton("Show 2D Vertex",        "show2DVertex()");
	bar->AddButton("Show Z Vertex",         "showZVertex()");
	bar->AddButton("", "");
	bar->AddButton("Set rates to Total",    "setRates(0)");
	bar->AddButton("Set rates to EM",       "setRates(1)");
	bar->AddButton("Set rates to Hadronic", "setRates(2)");
	bar->AddButton("Set rates to Gamma",    "setRates(3)");
	bar->AddButton("", "");
	bar->AddButton("Switch Threshold",      "switchT()");
	bar->AddButton("Switch Zoomed",         "switchZ()");
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

	histos[0]->Draw();
	for(unsigned h=1; h<confs.size(); h++) {
		histos[h]->Draw("same");
	}

	// fitting and getting avg
	vector<double> avg;
	for(unsigned h=0; h<confs.size(); h++) {
		histos[h]->Fit("pol0", "", "REM");
		histos[h]->GetFunction("pol0")->SetLineColor(colors[h]);
		avg.push_back(histos[h]->GetFunction("pol0")->GetParameter(0));
	}

	TLegend *tconfs  = new TLegend(0.6, 0.82, 0.99, 0.99);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs->AddEntry(histos[h], Form("%s: %3.2f MHz", confs[h].c_str(), avg[h] ), "F");
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

	lab.DrawLatex(0.06, 0.55,  "Rates (MHz)" );

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

	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);


	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);


	vector<TH1F*> histos = getEHistos(rateType);

	histos[0]->Draw();
	for(unsigned h=1; h<confs.size(); h++) {
		histos[h]->Draw("same");
	}

	// fitting and getting avg
	vector<double> integrals;
	for(unsigned h=0; h<confs.size(); h++) {
		integrals.push_back(histos[h]->Integral());
	}

	TLegend *tconfs  = new TLegend(0.6, 0.4, 0.95, 0.99);
	for(unsigned h=0; h<confs.size(); h++) {
		if(zoomed) {
			tconfs->AddEntry(histos[h], Form("%3.2f MHz in 0-120 KeV", integrals[h] ), "F");
		} else {
			tconfs->AddEntry(histos[h], Form("%3.2f MHz in 0-50 MeV", integrals[h] ), "F");
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
	lab.DrawLatex(0.06, 0.55,  "Rates (MHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.6, 0.02,  "Energy Deposited [Mev]" );


	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.1, 0.9,  Form("%s rate for different shielding", rateType.c_str()) );

}


void show2DVertex() {

	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.1);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);
	gStyle->SetPalette(1);

	vector<TCanvas*> verts;

	for(unsigned h=0; h<confs.size(); h++) {

		verts.push_back(new TCanvas(confs[h].c_str(), confs[h].c_str(), 1400, 1000));

		vertexRZ[h]->Draw("colz");

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
		lab.DrawLatex(0.2, 0.92,  Form("Rate for configuration: %s", confs[h].c_str()));

	}
}

void showZVertex() {

	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.1);

	TCanvas *rates = new TCanvas("rates", "rates", 1400, 1000);

	vertexZ[0]->Draw("");


	for(unsigned h=1; h<confs.size(); h++) {
		vertexZ[h]->Draw("same");
	}

	TLatex lab;
	lab.SetTextFont(42);
	lab.SetTextSize(0.045);
	lab.SetTextColor(kBlue+3);
	lab.SetNDC(1);

	lab.SetTextAngle(90);
	lab.DrawLatex(0.04, 0.55,  "Rates (MHz)" );

	lab.SetTextAngle(0);
	lab.DrawLatex(0.7, 0.02,  "Vertex Z    [cm]" );

	lab.SetTextSize(0.05);
	lab.SetTextColor(kRed+3);
	lab.DrawLatex(0.2, 0.92,  Form("Z vertex for all configurations"));

	TLegend *tconfs  = new TLegend(0.65, 0.4, 0.95, 0.85);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs->AddEntry(vertexZ[h], Form("%s", confs[h].c_str() ), "F");
	}

	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();


}




