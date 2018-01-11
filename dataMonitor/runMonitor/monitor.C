// ROOT
#include <TControlBar.h>

// runMonitor
#include "N.h"

#include "utils/utils.cc" // style
#include "graphs/rf.cc"   // RF
#include "graphs/dc.cc"   // DC

// monitor macro
// -------------
//
// To run:
//
// root monitor.C
// or
// root monitor.C+

void monitor()
{
	setStyle();

	initRF();
	initDC();

	TControlBar *bar = new TControlBar("vertical", "Data histograms visualizer", 2300, 40);

	addRFButtons(bar);
	addDCButtons(bar);

	bar->AddButton(" "," ");
	bar->AddButton("CPU time ",             "show_CPU()");
	bar->AddButton("Show ET time sigma ",   "show_EC()");
	bar->AddButton("Show Yelds",            "show_yelds()");
	bar->AddButton("Show X beam",           "show_beam(1)");
	bar->AddButton("Show Y beam",           "show_beam(2)");
	bar->AddButton("Show missing masses",   "show_mm()");
	bar->AddButton(" "," ");
	bar->AddButton("Print all graphs",        "printAll()");
	bar->AddButton(" "," ");
	bar->Show();
}



