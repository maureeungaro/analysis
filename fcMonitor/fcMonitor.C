#include <fstream>
#include <iostream>
using namespace std;

fcMonitor()
{
	gStyle->SetPadBottomMargin(0.12);
	gStyle->SetPadLeftMargin(0.12);

	
	ifstream rfiles("rootFiles");
	
	if(!rfiles)
		cout << " rootFiles cannot be opened " << endl;
	
	string rfile;
	
	TCanvas *fcC = new TCanvas("fCc", "fcC", 1000, 700);
	
	while(!rfiles.eof())
	{
		rfiles >> rfile;
		
		
		// finding run number
		size_t pos  = rfile.find("root/");
		string run1 = rfile.substr(pos+5);
		pos = run1.find(".");
		string run = run1.substr(0, pos);

		// finding pass
		pos  = rfile.find("e1-6/");
		string pass1 = rfile.substr(pos+5);
		pos = pass1.find("/");
		string pass = pass1.substr(0, pos);

		// finding analysis stage
		pos  = rfile.find(pass);
		string stage1 = rfile.substr(pos+6);
		pos = stage1.find("/");
		string stage = stage1.substr(0, pos);
		
		
		
		
		cout << " Opening root file: " << rfile << " for run number: " << run << ", pass: " << pass << " stage: " << stage << endl;
		
		
		TFile f(rfile.c_str());
		
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
		lab.DrawLatex(0.4, 0.92,  Form("Run %s %s %s", run.c_str(), pass.c_str(), stage.c_str() ));
		
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
		
		fcC->Print(  Form("img/%s_%s_%s.png", run.c_str(), pass.c_str(), stage.c_str()  ) );

		
		f.Close();
	}
	
}


