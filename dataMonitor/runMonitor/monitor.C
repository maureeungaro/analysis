// ROOT
#include <TControlBar.h>

// runMonitor
#include "utils/utils.cc" // style
#include "graphs/beam.cc" // beam

// monitor macro
// -------------
//
// To run:
//
// root monitor.C
// or
// root monitor.C+

void monitor() {
	
	int print     = 0;
	int LAST_RUN  = 44200;
	int FIRST_RUN = 43450;
	
	setStyle();

	initBeamGraphs();

//	TLatex la;
//	la.SetTextFont(44);
//	la.SetTextAlign(0);
//	la.SetTextSize(24);
//	la.SetNDC();
//	la.SetTextColor(2);
	
	TControlBar *bar = new TControlBar("vertical", "Data histograms visualizer", 2300, 40);
	
	bar->AddButton(" "," ");
	bar->AddButton("Show RF offset",    "show_RF(1)");
	bar->AddButton("Show RF protons",   "show_RF(2)");
	bar->AddButton("Show RF pi+",       "show_RF(3)");
	bar->AddButton("Show RF pi-",       "show_RF(4)");

	bar->AddButton(" "," ");
	bar->AddButton("Show DC mean ",     "show_DC(1)");
	bar->AddButton("Show DC sigma ",    "show_DC(2)");
	bar->AddButton(" "," ");
	
	bar->AddButton("Show DC mean Sector 1 ",        "show_DC(10)");
	bar->AddButton("Show DC mean Sector 2 ",        "show_DC(11)");
	bar->AddButton("Show DC mean Sector 3 ",        "show_DC(12)");
	bar->AddButton("Show DC mean Sector 4 ",        "show_DC(13)");
	bar->AddButton("Show DC mean Sector 5 ",        "show_DC(14)");
	bar->AddButton("Show DC mean Sector 6 ",        "show_DC(15)");
	bar->AddButton(" "," ");
	bar->AddButton("Show DC Sigma Sector 1 ",        "show_DC(20)");
	bar->AddButton("Show DC Sigma Sector 2 ",        "show_DC(21)");
	bar->AddButton("Show DC Sigma Sector 3 ",        "show_DC(22)");
	bar->AddButton("Show DC Sigma Sector 4 ",        "show_DC(23)");
	bar->AddButton("Show DC Sigma Sector 5 ",        "show_DC(24)");
	bar->AddButton("Show DC Sigma Sector 6 ",        "show_DC(25)");
	bar->AddButton(" "," ");
	bar->AddButton("CPU time ",             "show_CPU()");
	bar->AddButton("Show ET time sigma ",   "show_EC()");
	bar->AddButton("Show Yelds",            "show_yelds()");
	bar->AddButton("Show X beam",           "show_beam(1)");
	bar->AddButton("Show Y beam",           "show_beam(2)");
	bar->AddButton("Show missing masses",   "show_mm()");
	bar->AddButton(" "," ");
	bar->AddButton("Print all gifs",        "print_all()");
	bar->AddButton(" "," ");
	bar->Show();

}



