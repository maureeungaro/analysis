{
 cout << endl << " Root loogon by Maurizio Ungaro" << endl;
 cout << " No Title, no Stat, loading MU palette" << endl << endl;

 TStyle *mystyle  = new TStyle("mystyle","Plain Style");
 mystyle->SetPalette(1);

 TColor *background1 = new TColor(666, 0.92, 0.92, 1.0, "background1");
 TColor *background2 = new TColor(667, 0.9,   1.0, 1.0, "background2");
 TColor *background3 = new TColor(668, 1.0,   0.9, 1.0, "background3");

 mystyle->SetOptTitle(0);
 mystyle->SetOptStat(0);
 mystyle->SetOptFit(0);
 mystyle->SetCanvasColor(kWhite);
 mystyle->SetFillStyle(0);
 mystyle->SetNumberContours(80);
 mystyle->SetErrorX(0);

 mystyle->SetFrameFillColor(kWhite);
 mystyle->SetPadColor(kWhite);


 mystyle->SetNdivisions(505);

 mystyle->SetPaperSize(16, 20);
 mystyle->SetHeaderPS("220 500 translate");


	// Pads
	//  mystyle->SetPadLeftMargin(0.14);
	//  mystyle->SetPadRightMargin(0.14);
	//  mystyle->SetPadTopMargin(0.12);
	//  mystyle->SetPadBottomMargin(0.15);
	//

 mystyle->SetCanvasBorderMode(0);
 mystyle->SetFrameBorderMode(0);
 mystyle->SetPadBorderMode(0);

 gROOT->SetStyle("mystyle");

	// gROOT->LoadMacro("/opt/projects/analysis/rootUtils/palette.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/asym.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/definitions.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices2by5.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices2by3.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices2by4.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices3by5.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices3by3.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices3by4.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices3by7.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices5by2.C");
 gROOT->LoadMacro("/opt/projects/analysis/rootUtils/slices6by2.C");

	
	// palette();
	
}


