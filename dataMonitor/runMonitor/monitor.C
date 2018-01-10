{
#include "N.h"
#include "monitor.h"
int print     = 0;
int LAST_RUN  = 44200;
int FIRST_RUN = 43450;

 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetCanvasBorderMode(0);
 gStyle->SetFrameBorderMode(0);
 gStyle->SetPadBorderMode(0);

 gStyle->SetPadTopMargin(0.16);
 gStyle->SetPadBottomMargin(0.14);
 gStyle->SetPadLeftMargin(0.18);

 gStyle->SetTitleFont(13);
 gStyle->SetTitleColor(2);

 gStyle->SetLabelOffset(0.02,"XY");
 gStyle->SetTitleSize(0.044,"XY");
 gStyle->SetTitleOffset(1.5,"XY");

 gStyle->SetLabelFont(13,"xy"); //use font 1 precision 3
 gStyle->SetLabelSize(14, "xy"); //set label size in pixels

 gStyle->SetCanvasColor(19);
 gStyle->SetPadColor(19);


 gROOT->LoadMacro("init_histos.C");
 gROOT->LoadMacro("mon_RF.C");
 gROOT->LoadMacro("mon_DC.C");
 gROOT->LoadMacro("mon_EC.C");
 gROOT->LoadMacro("mon_CPU.C");
 gROOT->LoadMacro("mon_COUNTS.C");
 gROOT->LoadMacro("mon_BEAM.C");
 gROOT->LoadMacro("mon_MM.C");
 init_histos();

 TLatex la;
 la.SetTextFont(44);
 la.SetTextAlign(0);
 la.SetTextSize(24);
 la.SetNDC();
 la.SetTextColor(2);

 bar = new TControlBar("vertical", "  Data histograms visualizer   ");
 bar->AddButton(" "," ");
 bar->AddButton("Show RF offset",    "show_RF(1)");
 bar->AddButton("Show RF protons",   "show_RF(2)");
 bar->AddButton("Show RF pi+",       "show_RF(3)");
 bar->AddButton("Show RF pi-",       "show_RF(4)");
 bar->AddButton("Show ST RF pi+",    "show_RF(5)");
 bar->AddButton("Show ST RF pi-",    "show_RF(6)");


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
