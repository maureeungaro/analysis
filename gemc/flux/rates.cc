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



	// bar to control functions
//	TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro");
	anaOption analysis(true);


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



