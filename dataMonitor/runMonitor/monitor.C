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

void monitor() {
	
	int print = 0;
	
	setStyle();

	initRFGraphs();
	initDCGraphs();

	
	TControlBar *bar = new TControlBar("vertical", "Data histograms visualizer", 2300, 40);


	// RF
	bar->AddButton(" "," ");
	bar->AddButton("Show RF offset",    "showRF(1)");
	bar->AddButton("Show RF protons",   "showRF(2)");
	bar->AddButton("Show RF pi+",       "showRF(3)");
	bar->AddButton("Show RF pi-",       "showRF(4)");

	// DC
	bar->AddButton(" "," ");
	bar->AddButton("Show DC mean all sectors",  "showDC(1)");
	bar->AddButton("Show DC sigma all sectors", "showDC(2)");
	bar->AddButton(" "," ");
	bar->AddButton("Show DC mean Sector 1 ",    "showDC(10)");
	bar->AddButton("Show DC mean Sector 2 ",    "showDC(11)");
	bar->AddButton("Show DC mean Sector 3 ",    "showDC(12)");
	bar->AddButton("Show DC mean Sector 4 ",    "showDC(13)");
	bar->AddButton("Show DC mean Sector 5 ",    "showDC(14)");
	bar->AddButton("Show DC mean Sector 6 ",    "showDC(15)");
	bar->AddButton(" "," ");
	bar->AddButton("Show DC Sigma Sector 1 ",    "showDC(20)");
	bar->AddButton("Show DC Sigma Sector 2 ",    "showDC(21)");
	bar->AddButton("Show DC Sigma Sector 3 ",    "showDC(22)");
	bar->AddButton("Show DC Sigma Sector 4 ",    "showDC(23)");
	bar->AddButton("Show DC Sigma Sector 5 ",    "showDC(24)");
	bar->AddButton("Show DC Sigma Sector 6 ",    "showDC(25)");

	// CPU
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



