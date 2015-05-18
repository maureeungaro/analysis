{

	
	
	TFile f("out.root");
	
	
	int Nentries = out->GetEntries();
	
	double TWINDOW  = 250.0e-9;
	double TOT_TIME = Nentries*TWINDOW;
	
	cout << " Number of entries: " << Nentries << " total time: " << TOT_TIME << endl;
	
	
	TH2F *momThetap = new TH2F("momthetap", "momthetap", 100, 0, 80, 100, 0, 3000);
	TH2F *momThetam = new TH2F("momthetam", "momthetam", 100, 0, 80, 100, 0, 3000);

	TH1F *momp = new TH1F("momp", "momp", 100, 0, 3000);
	TH1F *momm = new TH1F("momm", "momm", 100, 0, 3000);
	
	TH1F *momp2 = new TH1F("momp2", "momp2", 100, 0, 3000);
	TH1F *momm2 = new TH1F("momm2", "momm2", 100, 0, 3000);

	
	
	out->Draw("mom:theta>>momthetap", "pid==211");
	out->Draw("mom:theta>>momthetam", "pid==-211");

	
	out->Draw("mom>>momp", "pid==211");
	out->Draw("mom>>momm", "pid==-211");

	out->Draw("mom>>momp2", "pid==211  && coinc == 2");
	out->Draw("mom>>momm2", "pid==-211 && coinc == 2");

	
	momThetap->Scale(50/TOT_TIME);
	momThetam->Scale(50/TOT_TIME);

	momp->Scale(50/TOT_TIME);
	momm->Scale(50/TOT_TIME);
	momp2->Scale(50/TOT_TIME);
	momm2->Scale(50/TOT_TIME);
	
}