{
    cout << endl << " Root loogon by Maurizio Ungaro" << endl;

    TStyle *mystyle  = new TStyle("mystyle","Plain Style");
    mystyle->SetPalette(1);

    TColor *background1 = new TColor(666, 0.92, 0.92, 1.0, "background1");
    TColor *background2 = new TColor(667, 0.9,   1.0, 1.0, "background2");
    TColor *background3 = new TColor(668, 1.0,   0.9, 1.0, "background3");

    mystyle->SetOptTitle(0);
    mystyle->SetOptStat(0);
    mystyle->SetOptFit(0);
    mystyle->SetCanvasColor(kWhite);
    mystyle->SetCanvasLineColor(kWhite);
    mystyle->SetFillStyle(0);
    mystyle->SetNumberContours(80);
    mystyle->SetErrorX(0);
    mystyle->SetFrameFillColor(kWhite);
    mystyle->SetPadColor(kWhite);
    mystyle->SetNdivisions(505);
    mystyle->SetPaperSize(16, 20);
    mystyle->SetHeaderPS("220 500 translate");

    mystyle->SetCanvasBorderMode(0);
    mystyle->SetFrameBorderMode(0);
    mystyle->SetPadBorderMode(0);

    gROOT->SetStyle("mystyle");

//    gROOT->LoadMacro("/opt/projects/analysis/rootUtils/definitions.C");
//
//    // load e_pid shared libraries
//    gROOT->ProcessLine(".L libepid.dylib");
//
//    // load e_pid analysis libraries
//    gROOT->ProcessLine(".L libana_epid.dylib");

}
