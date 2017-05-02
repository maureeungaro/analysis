#include "options.h"

#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TControlBar.h"

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
//	gROOT->SetStyle("Plain");
//
//	gROOT->SetStyle("Plain");
//	gStyle->SetOptFit(1111);
//	gStyle->SetPalette(57);
//	gStyle->SetOptTitle(0);
//
//	// root app
//	TApplication *rootApp = new TApplication("ROOT Application", &argc, argv);

	vector<string> confs = {"EMY", "EMZ", "LIV", "PEN", "FTFP_BERT_HP", "FTFP_BERT_TRV", "FTF_BIC", "QGSP_BERT", "QGSP_FTFP_BERT", "standard" };
//	vector<string> confs = {"EMZ", "FTFP_BERT_HP", "FTFP_BERT_TRV", "FTF_BIC", "PEN", "standard"};


//	anaOption analysis(true, confs);
	anaOption analysis(true, confs);



	// bar to control functions
//	TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro");


//	bar->AddButton("Flux Rates",  "");
//	bar->AddButton("","");
//	bar->AddButton("Show 2D Flux",  "analysis.showFlux()");
//	bar->AddButton("","");
//	bar->AddButton("Show Vertex",   "gROOT->ProcessLine(\"show_vertex()\")");
//	bar->AddButton("","");
//	bar->AddButton("","");
//	bar->AddButton("Exit",          "gROOT->ProcessLine(\".q\")");
//	bar->Show();
//
//	rootApp->Run();
}



