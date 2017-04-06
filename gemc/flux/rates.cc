#include "options.h"

#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TControlBar.h"


int main(int argc, char** argv)
{
	gROOT->SetStyle("Plain");

	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1111);
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);

	// root app
	TApplication *rootApp = new TApplication("ROOT Application", &argc, argv);


	anaOption analysis(true);

	// bar to control functions
	TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Flux Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show 2D Flux",  "show_flux()");
	bar->AddButton("","");
	bar->AddButton("Show Vertex",   "show_vertex()");
	bar->AddButton("","");
	bar->Show();

	rootApp->Run();

	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q rates.C
	// print_all();
}



