
vector<TH1F*> ctofRatesTotal;
vector<TH1F*> ctofRatesHadronic;
vector<TH1F*> ctofRatesEm;
vector<TH1F*> ctofRatesGamma;

vector<TH1F*> ctofRatesTotalT;
vector<TH1F*> ctofRatesHadronicT;
vector<TH1F*> ctofRatesEmT;
vector<TH1F*> ctofRatesGammaT;

vector<TH1F*> ctofRatesTotalEdep;
vector<TH1F*> ctofRatesHadronicEdep;
vector<TH1F*> ctofRatesEmEdep;
vector<TH1F*> ctofRatesGammaEdep;

vector<TH1F*> ctofRatesTotalEdepZ;
vector<TH1F*> ctofRatesHadronicEdepZ;
vector<TH1F*> ctofRatesEmEdepZ;
vector<TH1F*> ctofRatesGammaEdepZ;


vector<string>   confs;
vector<Color_t> colors;

string rateType;
bool withThreshold;

void loadHistos() {
	string fname = "ctofHistos.root";
	cout << " Opening file " << fname << endl;

	TFile *f = new TFile(fname.c_str());

	for(unsigned h=0; h<confs.size(); h++) {
		cout << " Loading " << confs[h] << " configuration " << endl;

		string name = "ctofRatesTotal_" + confs[h];
		ctofRatesTotal.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesTotal.back()->SetMinimum(0);
		ctofRatesTotal.back()->SetLineColor(colors[h]);
		ctofRatesTotal.back()->SetDirectory(0);

		name = "ctofRatesHadronic_" + confs[h];
		ctofRatesHadronic.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesHadronic.back()->SetMinimum(0);
		ctofRatesHadronic.back()->SetLineColor(colors[h]);
		ctofRatesHadronic.back()->SetDirectory(0);

		name = "ctofRatesEm_" + confs[h];
		ctofRatesEm.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesEm.back()->SetMinimum(0);
		ctofRatesEm.back()->SetLineColor(colors[h]);
		ctofRatesEm.back()->SetDirectory(0);

		name = "ctofRatesGamma_" + confs[h];
		ctofRatesGamma.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesGamma.back()->SetMinimum(0);
		ctofRatesGamma.back()->SetLineColor(colors[h]);
		ctofRatesGamma.back()->SetDirectory(0);


		name = "ctofRatesTotalT_" + confs[h];
		ctofRatesTotalT.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesTotalT.back()->SetMinimum(0);
		ctofRatesTotalT.back()->SetLineColor(colors[h]);
		ctofRatesTotalT.back()->SetDirectory(0);

		name = "ctofRatesHadronicT_" + confs[h];
		ctofRatesHadronicT.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesHadronicT.back()->SetMinimum(0);
		ctofRatesHadronicT.back()->SetLineColor(colors[h]);
		ctofRatesHadronicT.back()->SetDirectory(0);

		name = "ctofRatesEmT_" + confs[h];
		ctofRatesEmT.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesEmT.back()->SetMinimum(0);
		ctofRatesEmT.back()->SetLineColor(colors[h]);
		ctofRatesEmT.back()->SetDirectory(0);

		name = "ctofRatesGammaT_" + confs[h];
		ctofRatesGammaT.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesGammaT.back()->SetMinimum(0);
		ctofRatesGammaT.back()->SetLineColor(colors[h]);
		ctofRatesGammaT.back()->SetDirectory(0);





		name = "ctofRatesTotalEdep_" + confs[h];
		ctofRatesTotalEdep.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesTotalEdep.back()->SetMinimum(0);
		ctofRatesTotalEdep.back()->SetLineColor(colors[h]);
		ctofRatesTotalEdep.back()->SetDirectory(0);

		name = "ctofRatesHadronicEdep_" + confs[h];
		ctofRatesHadronicEdep.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesHadronicEdep.back()->SetMinimum(0);
		ctofRatesHadronicEdep.back()->SetLineColor(colors[h]);
		ctofRatesHadronicEdep.back()->SetDirectory(0);

		name = "ctofRatesEmEdep_" + confs[h];
		ctofRatesEmEdep.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesEmEdep.back()->SetMinimum(0);
		ctofRatesEmEdep.back()->SetLineColor(colors[h]);
		ctofRatesEmEdep.back()->SetDirectory(0);

		name = "ctofRatesGammaEdep_" + confs[h];
		ctofRatesGammaEdep.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesGammaEdep.back()->SetMinimum(0);
		ctofRatesGammaEdep.back()->SetLineColor(colors[h]);
		ctofRatesGammaEdep.back()->SetDirectory(0);



		name = "ctofRatesTotalEdepZ_" + confs[h];
		ctofRatesTotalEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesTotalEdepZ.back()->SetMinimum(0);
		ctofRatesTotalEdepZ.back()->SetLineColor(colors[h]);
		ctofRatesTotalEdepZ.back()->SetDirectory(0);

		name = "ctofRatesHadronicEdepZ_" + confs[h];
		ctofRatesHadronicEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesHadronicEdepZ.back()->SetMinimum(0);
		ctofRatesHadronicEdepZ.back()->SetLineColor(colors[h]);
		ctofRatesHadronicEdepZ.back()->SetDirectory(0);

		name = "ctofRatesEmEdepZ_" + confs[h];
		ctofRatesEmEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesEmEdepZ.back()->SetMinimum(0);
		ctofRatesEmEdepZ.back()->SetLineColor(colors[h]);
		ctofRatesEmEdepZ.back()->SetDirectory(0);

		name = "ctofRatesGammaEdepZ_" + confs[h];
		ctofRatesGammaEdepZ.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesGammaEdepZ.back()->SetMinimum(0);
		ctofRatesGammaEdepZ.back()->SetLineColor(colors[h]);
		ctofRatesGammaEdepZ.back()->SetDirectory(0);


	}

	cout << " done. " << endl;
	f->Close();

}

vector<TH1F*> getRateHistos(string kind) {
	if(        kind == "total") {
		if(withThreshold) {
			return ctofRatesTotalT;
		}
		return ctofRatesTotal;
	} else if (kind == "em") {
		if(withThreshold) {
			return ctofRatesEmT;
		}
		return ctofRatesEm;
	} else if (kind == "hadronic") {
		if(withThreshold) {
			return ctofRatesHadronicT;
		}
		return ctofRatesHadronic;
	} else if (kind == "gamma") {
		if(withThreshold) {
			return ctofRatesGammaT;
		}
		return ctofRatesGamma;
	}

	return ctofRatesTotal;
}

// root[0] .x show.C
void show()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	confs  = {"bstNoShieldCtofNoShield", "bstShieldCtofNoShield",	"bstShieldCtof1mm", "bstShieldCtof2mm", "bstShieldCtof3mm"	};
	colors = {                  kBlack,                    kBlue,            kRed - 3,           kRed + 3,           kGreen+4  };

	rateType = "total";
	withThreshold = true;

	loadHistos();

	TControlBar *bar = new TControlBar("vertical", "Ctof Study", 1400, 200);
	bar->AddButton("", "");
	bar->AddButton("Show Paddle Rates",     "showPaddles()");
	bar->AddButton("", "");
	bar->AddButton("Show Energy Deposited", "showEdep()");
	bar->AddButton("", "");
	bar->AddButton("Set rates to Total",    "setRates(0)");
	bar->AddButton("Set rates to EM",       "setRates(1)");
	bar->AddButton("Set rates to Hadronic", "setRates(2)");
	bar->AddButton("Set rates to Gamma",    "setRates(3)");
	bar->AddButton("", "");
	bar->AddButton("Switch Threshold",      "switchT()");
	bar->AddButton("", "");
	bar->Show();
	gROOT->SaveContext();
}


void switchT() {
	withThreshold = !withThreshold;
	cout << " Threshold: " << withThreshold << endl;
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

	gStyle->SetPadLeftMargin(0.1);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);


	TCanvas *rates = new TCanvas("rates", "rates", 900, 650);

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






