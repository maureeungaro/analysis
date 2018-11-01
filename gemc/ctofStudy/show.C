
//#include "TH1.h"

vector<TH1F*> ctofRatesTotal;
vector<string>   confs;
vector<Color_t> colors;

void loadHistos() {
	string fname = "ctofHistos.root";
	cout << " Opening file " << fname << endl;

	TFile *f = new TFile(fname.c_str());

	for(unsigned h=0; h<confs.size(); h++) {
		string name = "ctofRatesTotal_" + confs[h];
		cout << " Loading " << confs[h] << " configuration histos " << name << endl;
		ctofRatesTotal.push_back((TH1F*) f->Get(name.c_str()));
		ctofRatesTotal.back()->SetMinimum(0);
		ctofRatesTotal.back()->SetLineColor(colors[h]);
		ctofRatesTotal.back()->SetDirectory(0);
	}

	cout << " done. " << endl;
	f->Close();

}


// root[0] .x show.C
void show()
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	confs  = {"bstNoShieldCtofNoShield",	"bstShieldCtof1mm", "bstShieldCtof2mm", "bstShieldCtof3mm",	"bstShieldCtofNoShield"};
	colors = {                  kBlue-7,                kRed,              kBlue,           kGreen+4,                  kRed+2};

	loadHistos();

	TControlBar *bar = new TControlBar("vertical", "TGeo shapes",10, 10);
	bar->AddButton("Show Paddle Rates", "showPaddles()");
	bar->Show();
	gROOT->SaveContext();


}





void showPaddles() {

	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.2);
	gStyle->SetPadBottomMargin(0.12);



	TLatex lab;
	lab.SetTextColor(kBlue+3);
	lab.SetTextFont(32);

	TCanvas *rates = new TCanvas("rates", "rates", 900, 650);

	ctofRatesTotal[0]->Draw();

	for(unsigned h=1; h<confs.size(); h++) {
		ctofRatesTotal[h]->Draw("same");
	}

	TLegend *tconfs  = new TLegend(0.7, 0.82, 0.99, 0.99);
	for(unsigned h=0; h<confs.size(); h++) {
		tconfs->AddEntry(ctofRatesTotal[h], confs[h].c_str(), "F");
	}
	tconfs->SetBorderSize(0);
	tconfs->SetFillColor(0);
	tconfs->Draw();

}


