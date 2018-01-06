{
	
	const int NTARGET     = 1;
	string starget[NTARGET] = { "lh2"};
	
	const int NPART     = 3;
	string SPART[NPART] = { "pions"   ,  "protons" , "kaons" };
	Color_t pcol[NPART] = {   kRed    ,   kOrange  ,  kGreen};
	double fmass[NPART] = { 139.57018 ,  938.27203 , 493.677};
	double fpid[NPART]  = { 211       ,     2212   ,    321};
	

	// binning from 200 MeV to 4.2 GeV
	const int NPBINS = 20;
	int plims[NPBINS+1];
	for(int b=0; b<NPBINS+1; b++)
		plims[b] = 200 + b*200;


	TH1F *back_edep[2][NTARGET];          // background E deposited 0 = e.m. 1 = hadronic
	TH1F *sign_edep[NPART][NPBINS];       // signals E deposited

	const int NPUR = 200;   // 1 = 1 KeV
	double X[NPUR];   // X values for purity graph
	double BY[2][NTARGET][NPUR];  // background Y values for purity graph
	double SY[NPART][NPBINS][NPUR];       // signals Y values for purity graph
	Color_t fcol[2] = { kBlue, kRed+2};
	
	TGraph *back_purity[2][NTARGET];
	TGraph *sign_purity[NPART][NPBINS];
	
	// background energy histos
	for(int t=0; t<NTARGET; t++)
	{
		TFile f(Form("../rootfiles/%s.root", starget[t].c_str()));
		back_edep[0][t] = (TH1F*) f.Get(Form("edep_em_%s", starget[t].c_str()));
		back_edep[1][t] = (TH1F*) f.Get(Form("edep_ha_%s", starget[t].c_str()));
		back_edep[0][t]->SetLineColor(fcol[0]);
		back_edep[1][t]->SetLineColor(fcol[1]);
		back_edep[0][t]->SetDirectory(0);
		back_edep[1][t]->SetDirectory(0);
		f.Close();
	}	
	
	// calculating background purity
	for(int t=0; t<NTARGET; t++)
	{
		int TOTEM = back_edep[0][t]->Integral(2, 4000);
		int TOTHA = back_edep[1][t]->Integral(2, 4000);
		int TOT = TOTEM + TOTHA;
		for(int i=1; i<NPUR; i++)
		{
			X[i] = i+1;
			
			// edep histos are 4000 bins form 0 to 0.5 MeV 
			double dbin = 0.5/4.0; // in KeV
			int tindex  = i / dbin + 1;
			
			BY[0][t][i] = back_edep[0][t]->Integral(2, tindex)/TOTEM;
			BY[1][t][i] = back_edep[1][t]->Integral(2, tindex)/TOTHA;
		}
		
		for(int j=0; j<2; j++)
		{
			back_purity[j][t] = new TGraph(NPUR, X, BY[j][t]);
			back_purity[j][t]->SetMarkerStyle(21);
			back_purity[j][t]->SetMarkerSize(0.5);
			back_purity[j][t]->SetMarkerColor(fcol[j]);
		
		}
	}

	// signal energy histos
	TFile f("../rootfiles/hadrons.root");
	for(int p=0; p<NPART; p++)
		for(int b=0; b<NPBINS; b++)
		{	
			sign_edep[p][b] = (TH1F*) f.Get(Form("edep_p%d_%d_%s", plims[b], plims[b+1], SPART[p].c_str()));
			sign_edep[p][b]->SetLineColor(pcol[p]);
			sign_edep[p][b]->SetDirectory(0);
	}
	
	// calculating signal purity
	for(int p=0; p<NPART; p++)
		for(int b=0; b<NPBINS; b++)
		{
			int TOT = sign_edep[p][b]->Integral(2, 2000);
			
			for(int i=1; i<NPUR; i++)
			{
				
				// edep histos are 2000 bins form 0 to 0.5 MeV 
				double dbin = 0.5/2.0; // in KeV
				int tindex  = i / dbin + 1;
				
				SY[p][b][i] = sign_edep[p][b]->Integral(2, tindex)/TOT;
			}
			
			sign_purity[p][b] = new TGraph(NPUR, X, SY[p][b]);
			sign_purity[p][b]->SetMarkerStyle(21);
			sign_purity[p][b]->SetMarkerSize(0.5);
			sign_purity[p][b]->SetMarkerColor(pcol[p]);
			
			
		}	
	
	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetCanvasColor(0);

	
	
	// Background ENERGY
	TCanvas *benergy  = new TCanvas("benergy", "benergy", 900, 650);
	gPad->SetLogy();
	
	
	for(int b=0; b<NPBINS; b++)
	{
		back_edep[0][0]->Draw();
		back_edep[1][0]->Draw("same");
		
		lab.SetTextSize(0.04);
		lab.SetTextColor(kBlue+3);
		lab.SetTextFont(42);
		lab.SetNDC(1);
		lab.DrawLatex(0.1, 0.915, Form("Energy Distribution for all Background"));
		
		TLegend *emodel  = new TLegend(0.6, 0.6, 0.9, 0.8);
		emodel->AddEntry(back_edep[0][0], "e.m. background",     "L");	
		emodel->AddEntry(back_edep[1][0], "hadronic background", "L");
				
		emodel->SetBorderSize(0);
		emodel->SetFillColor(0);
		emodel->Draw();
		
		benergy->Print(Form("../html/img/benergy_p%d.gif", b+1));
	}
	
	
	
	// ENERGY
	TCanvas *energy  = new TCanvas("energy", "energy", 900, 650);
	gPad->SetLogy();
	
	
	for(int b=0; b<NPBINS; b++)
	{
		back_edep[0][0]->Draw();
		back_edep[1][0]->Draw("same");
		for(int p=0; p<NPART; p++)
			sign_edep[p][b]->Draw("same");
		
		lab.SetTextSize(0.04);
		lab.SetTextColor(kBlue+3);
		lab.SetTextFont(42);
		lab.SetNDC(1);
		lab.DrawLatex(0.1, 0.915, Form("Energy Distribution for all Background, Signal %d < p < %d MeV", plims[b], plims[b+1]));
		
		TLegend *emodel  = new TLegend(0.6, 0.5, 0.9, 0.8);
		emodel->AddEntry(back_edep[0][0], "e.m. background",     "L");	
		emodel->AddEntry(back_edep[1][0], "hadronic background", "L");
		
		for(int p=0; p<NPART; p++)
			emodel->AddEntry(sign_edep[p][b], Form("%s", SPART[p]),   "L");
		
		emodel->SetBorderSize(0);
		emodel->SetFillColor(0);
		emodel->Draw();
		
		energy->Print(Form("../html/img/energy_p%d.gif", b+1));
	}
	
	
	
	// PURITY	
	TCanvas *purity  = new TCanvas("purity", "purity", 900, 650);
	
	
	for(int b=0; b<NPBINS; b++)
	{
		back_purity[0][0]->Draw("AP");
		back_purity[1][0]->Draw("Psame");
		for(int p=0; p<NPART; p++)
			sign_purity[p][b]->Draw("Psame");
	
		lab.SetTextSize(0.04);
		lab.SetTextColor(kBlue+3);
		lab.SetTextFont(42);
		lab.SetNDC(1);
		lab.DrawLatex(0.1, 0.915, Form("Rejection Factor for all Background, Signal %d < p < %d MeV", plims[b], plims[b+1]));
		
		TLegend *pmodel  = new TLegend(0.25, 0.45, 0.53, 0.65);
		pmodel->AddEntry(back_edep[0][0], "e.m. background",     "L");	
		pmodel->AddEntry(back_edep[1][0], "hadronic background", "L");
		
		for(int p=0; p<NPART; p++)
			pmodel->AddEntry(sign_edep[p][b], Form("%s", SPART[p]),   "L");
		
		pmodel->SetBorderSize(0);
		pmodel->SetFillColor(0);
		pmodel->Draw();
		
		purity->Print(Form("../html/img/rejection_p%d.gif", b+1));
	
	}
	
			
	// PURITY Log Scale	
	TCanvas *purityl  = new TCanvas("purityl", "purityl", 900, 650);
	gPad->SetLogy();
	
	for(int b=0; b<NPBINS; b++)
	{
		back_purity[0][0]->Draw("AP");
		back_purity[1][0]->Draw("Psame");
		for(int p=0; p<NPART; p++)
			sign_purity[p][b]->Draw("Psame");
	
		lab.SetTextSize(0.04);
		lab.SetTextColor(kBlue+3);
		lab.SetTextFont(42);
		lab.SetNDC(1);
		lab.DrawLatex(0.1, 0.915, Form("Rejection Factor for all Background, Signal %d < p < %d MeV", plims[b], plims[b+1]));
		
		TLegend *pmodel  = new TLegend(0.65, 0.35, 0.90, 0.55);
		pmodel->AddEntry(back_edep[0][0], "e.m. background",     "L");	
		pmodel->AddEntry(back_edep[1][0], "hadronic background", "L");
		
		for(int p=0; p<NPART; p++)
			pmodel->AddEntry(sign_edep[p][b], Form("%s", SPART[p]),   "L");
		
		pmodel->SetBorderSize(0);
		pmodel->SetFillColor(0);
		pmodel->Draw();
		
		purityl->Print(Form("../html/img/rejection_logy_p%d.gif", b+1));
	
	}
	
			
			
							
}
















