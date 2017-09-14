#include "dcHistos.h"

const string rootFilePath = "/opt/root";

// configurations
const vector<string> confs = { "cadTarget", "clas12NewTarget2"};
const vector<double> conff = {           1,                  1};  // additional factor to scale the different configurations


int CONFINDEX = 0;
int REGINDEX  = 0;
int ZONEINDEX = 0;



void dcRates(bool recalc, bool recompile=false)
{
	// first compile the sources
	// can force recompiling if something changed
	// otherwise just reload the library
	// if the library doesn't exist, compile it
	if(recompile || gSystem->IsFileInIncludePath("dcHistos_cc.so") == false) {
		gROOT->ProcessLine(".L dcHistos.cc+O");
	}

	if(recalc) cout << " Re-defining histograms." << endl;
	else       cout << " Loading histos definitions." << endl;



	// style
	gStyle->SetPalette(1);
	gStyle->SetOptTitle(kWhite);
	gStyle->SetOptStat(kWhite);
	gStyle->SetOptFit(kWhite);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);

	gStyle->SetNumberContours(80);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadBorderMode(0);








	TControlBar* bar = new TControlBar("vertical", "DC Rates - Maurizio Ungaro");
	bar->AddButton("DC Occupancy Rates",  "");
	bar->AddButton("", "");
	bar->AddButton("", "");
	bar->Show();


}
