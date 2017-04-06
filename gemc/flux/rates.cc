#include "options.C"


void rates()
{
	gROOT->SetStyle("Plain");

	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1111);
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);

//	gStyle->SetPalette(1);
//	gStyle->SetOptTitle(kWhite);
//	gStyle->SetOptStat(kWhite);
//	gStyle->SetOptFit(kWhite);
//	gStyle->SetCanvasColor(kWhite);
//	gStyle->SetPadColor(kWhite);
//	
//	gStyle->SetNumberContours(80);
//	gStyle->SetCanvasBorderMode(0);
//	gStyle->SetFrameBorderMode(0);
//	gStyle->SetPadBorderMode(0);


//	gROOT->LoadMacro("init.C");
//	gROOT->LoadMacro("show.C");

//gROOT->Macro("init.C++(flux.root)");

//	init_histos(Form("flux.root"));
		
	TControlBar *bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("Flux Rates",  "");
	bar->AddButton("","");
	bar->AddButton("Show 2D Flux",  "show_flux()");
	bar->AddButton("","");
	bar->AddButton("Show Vertex",   "show_vertex()");
	bar->AddButton("","");
	bar->Show();

	// to print all pics, uncomment the lines below and run root
	// in batch mode: root -b -q rates.C
	// print_all();
}


