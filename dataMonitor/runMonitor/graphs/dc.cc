// runMonitor
#include "rf.h"

void initDCGraphs()
{
	cout << " Initializing DC graphs." << endl;

	double DC_SA[6][N];
	double DC_MA[6][N];
	double DC_M[6][6][N];
	double DC_S[6][6][N];
	double Tmp[N];

	int DC_col[6] = {2,5,6,7,1,4};

	ifstream IN("mysql/DC.dat");
	for(int i=0; i<N; i++)
	{
		IN >> tmp >> run[i];
		for(int l=0; l<6; l++) IN >> DC_MA[l][i];
		for(int l=0; l<6; l++) IN >> DC_SA[l][i];
	}
	IN.close();


	for(int l=0; l<6; l++)
	{
		DC_res_mean[l] = new TGraph(N, run, DC_MA[l]);
		DC_res_mean[l]->SetMarkerStyle(20);
		DC_res_mean[l]->SetMarkerSize(0.6);
		DC_res_mean[l]->SetMarkerColor(DC_col[l]);
		DC_res_mean[l]->SetFillColor(18);
		DC_res_mean[l]->SetLineColor(18);

		DC_res_sigm[l] = new TGraph(N, run, DC_SA[l]);
		DC_res_sigm[l]->SetMarkerStyle(20);
		DC_res_sigm[l]->SetMarkerSize(0.6);
		DC_res_sigm[l]->SetMarkerColor(DC_col[l]);
		DC_res_sigm[l]->SetFillColor(18);
		DC_res_sigm[l]->SetLineColor(18);
	}


	ifstream IN("mysql/DCd.dat");
	for(int i=0; i<N; i++)
	{
		IN >> tmp >> run[i];
		for(int l=0; l<6; l++)
		{
			for(int s=0; s<6; s++) IN >> DC_M[s][l][i];
			for(int s=0; s<6; s++) IN >> DC_S[s][l][i];
		}
	}
	IN.close();

	for(int s=0; s<6; s++)
		for(int l=0; l<6; l++)
		{
			for(int i=0; i<N; i++) Tmp[i] = DC_M[s][l][i];
			DC_mean[s][l] = new TGraph(N, run, Tmp);
			DC_mean[s][l]->SetMarkerStyle(20);
			DC_mean[s][l]->SetMarkerSize(0.6);
			DC_mean[s][l]->SetMarkerColor(DC_col[l]);
			DC_mean[s][l]->SetFillColor(18);
			DC_mean[s][l]->SetLineColor(18);

			for(int i=0; i<N; i++) Tmp[i] = DC_S[s][l][i];
			DC_sigm[s][l] = new TGraph(N, run, Tmp);
			DC_sigm[s][l]->SetMarkerStyle(20);
			DC_sigm[s][l]->SetMarkerSize(0.6);
			DC_sigm[s][l]->SetMarkerColor(DC_col[l]);
			DC_sigm[s][l]->SetFillColor(18);
			DC_sigm[s][l]->SetLineColor(18);
		}



}

void showDC(int whichPlot)
{
	TCanvas *RFCanvas = getOrCreateCanvas("RFCanvas", 1200, 800);

	string gTitle[4]   = {"All Particles RF", "Protons RF", "#pi^{+}    RF", "#pi^{-}    RF"};
	string gPrint[4]   = {          "rf_all", "rf_protons",        "rf_pip",        "rf_pim"};
	double minFrame[4] = {-0.06, -0.12, -0.3, -0.3};
	double maxFrame[4] = { 0.35,  0.55,  0.3,  0.35};

	gPad->DrawFrame(FIRST_RUN, minFrame[whichParticle-1], LAST_RUN, maxFrame[whichParticle-1]);

	if(whichParticle == 1)
	{
		RF->Draw("P");
		sRF->Draw("P");
	}

	if(whichParticle == 2)
	{
		sRFP->Draw("P");
		RFP->Draw("P");
	}

	if(whichParticle == 3)
	{
		sRFpp->Draw("P");
		RFpp->Draw("P");
	}

	if(whichParticle == 4)
	{
		sRFpm->Draw("P");
		RFpm->Draw("P");
	}

	TLatex la = commonLabel();
	la.SetTextColor(1);
	la.DrawLatex(.2,.91, gTitle[whichParticle-1].c_str());
	la.SetTextColor(4);
	la.DrawLatex(.65,.91, "Mean");
	la.SetTextColor(2);
	la.DrawLatex(.8,.91, "Sigma");

	if(PRINT != ".no") RFCanvas->Print( "img/" + (gPrint[whichParticle-1] + PRINT).c_str() );

}


