// ROOT
#include <TStyle.h>

// runMonitor
#include "utils.h"
#include "../graphs/rf.h"
#include "../graphs/dc.h"

void setStyle()
{
	cout << " Setting ROOT Style." << endl;
	
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
}

TLatex commonLabel()
{
	TLatex la;
	la.SetTextFont(44);
	la.SetTextAlign(0);
	la.SetTextSize(40);
	la.SetTextColor(2);
	la.SetNDC();

	return la;
}

TCanvas *getOrCreateCanvas(string withName, double width, double height)
{
	TCanvas *Canvas = (TCanvas*) gROOT->FindObject(withName.c_str());

	if(Canvas== nullptr) {
		Canvas = new TCanvas(withName.c_str(), withName.c_str(), width, height);
		Canvas->SetFillColor(18);
		Canvas->SetGridx();
		Canvas->SetGridy();
	}
	Canvas->Clear();

	return Canvas;
}

void printCanvas(string withName, string withTitle)
{
	if(PRINT != ".no") {
		TCanvas *Canvas = (TCanvas*) gROOT->FindObject(withName.c_str());
		
		if(Canvas != nullptr) {
			string imageName = "img/" + withTitle + PRINT;
			Canvas->Print(imageName.c_str());
		}
	}
}


void printAll()
{

	// RF
	for(int i=1; i<5; i++) {
		showRF(i);
	}

	// DC
	showDC(1);
	showDC(2);

	for(int i=0; i<6; i++) {
		showDC(10+i);
		showDC(20+i);
	}

}








