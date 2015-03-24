#include <fstream>
#include <iostream>
using namespace std;

fcMonitor()
{
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetPadLeftMargin(0.12);

	string path = "/Volumes/e1-6/pass1/fullRuns/root/";
	
	ifstream rfiles("rootFiles");
	
	if(!rfiles)
		cout << " rootFiles cannot be opened " << endl;
	
	string rfile;
	
	TCanvas *fcC = new TCanvas("fCc", "fcC", 1000, 700);
	
	while(!rfiles.eof())
	{
		rfiles >> rfile;
		string file = path + rfile + ".root";
		
		cout << " Opening root file: " << file << endl;
		
		
		TFile f(file.c_str());
		
		f.ls();
		
		TH1D *ratio = (TH1D*) f.Get("ratio");
		TH1D *summary = (TH1D*) f.Get("summary");
		
		ratio->SetMinimum(0);
		ratio->SetMaximum(100000);
		ratio->Draw();
		
		
		TLatex lab;
		lab.SetTextFont(42);
		lab.SetTextSize(0.052);
		lab.SetNDC();
		
		lab.SetTextColor(kRed+3);
		lab.DrawLatex(0.45, 0.92,  Form("Run %s", rfile.c_str()));
		
		lab.SetTextFont(52);
		lab.SetTextSize(0.045);
		lab.SetTextColor(kBlue+3);
		lab.DrawLatex(0.45, 0.80,  Form("Number of Events:  %3.4e", summary->GetBinContent(1)));
		lab.DrawLatex(0.55, 0.72,  Form("Total FC:  %4.3f #muC", summary->GetBinContent(2)));

	
		lab.SetTextColor(kBlack);
		lab.DrawLatex(0.4, 0.02,  "Scaler event number");
		
		lab.SetTextColor(kBlack);
		lab.SetTextAngle(90);
		lab.DrawLatex(0.05, 0.3,  "Events per scaler event");
		
		fcC->Print(  Form("img/%s.png", rfile.c_str()) );

		
		f.Close();
	}
	
}


