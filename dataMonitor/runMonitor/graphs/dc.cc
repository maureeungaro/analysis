// runMonitor
#include "dc.h"

void initDC()
{
	cout << " Initializing DC graphs." << endl;

	char tmp[100];
	double run[N];
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


	IN.open("mysql/DCd.dat");
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
	TCanvas *DCCanvas = getOrCreateCanvas("DCCanvas", 1200, 800);

	string SLLegend[6] = {"Superlayer1", "Superlayer2","Superlayer3","Superlayer4","Superlayer5","Superlayer6"};
	string gPrint[2]   = { "dc_mean", "dc_sigm"};

	TLegend *SL = new TLegend(0.84, 0.75, 1, 0.98);
	SL->SetFillColor(18);
	SL->SetLineColor(18);

	double minFrame[4] = {-200, 180, -200, 180};
	double maxFrame[4] = { 100, 340,  120, 360};

	int dcType = dcCase(whichPlot);

	gPad->DrawFrame(FIRST_RUN, minFrame[dcType], LAST_RUN, maxFrame[dcType]);

	TLatex la = commonLabel();
	la.SetTextColor(4);

	if(dcType == 0)
	{
		for(int l=0; l<6; l++)
		{
			DC_res_mean[l]->Draw("P");
			SL->AddEntry(DC_res_mean[l], SLLegend[l].c_str());
		}
		la.DrawLatex(.16,.91, "DC Mean for different superlayers (all sectors)");
	}

	if(dcType == 1)
	{
		for(int l=0; l<6; l++)
		{
			DC_res_sigm[l]->Draw("P");
			SL->AddEntry(DC_res_sigm[l], SLLegend[l].c_str());
		}
		la.DrawLatex(.16,.91, "DC Sigma for different superlayers (all sectors)");
	}

	if(dcType == 2)
	{
		int gIndex = graphIndex(whichPlot);

		for(int l=0; l<6; l++)
		{
			DC_mean[gIndex][l]->Draw("P");
			SL->AddEntry(DC_mean[gIndex][l], SLLegend[l].c_str());
		}
		la.DrawLatex(.18,.91, Form("DC Mean for different superlayers - sector %d", gIndex + 1));
	}

	if(dcType == 3)
	{
		int gIndex = graphIndex(whichPlot);

		for(int l=0; l<6; l++)
		{
			DC_sigm[gIndex][l]->Draw("P");
			SL->AddEntry(DC_sigm[gIndex][l], SLLegend[l].c_str());
		}
		la.DrawLatex(.18,.91, Form("DC Sigma for different superlayers - sector %d", gIndex + 1));
	}

	// draw legend
	SL->Draw();

	// print if necessary
	int sector = whichPlot%10 + 1;
	string sString =  "_sec" + to_string(sector);

	if(dcType == 0 || dcType == 1) {
		printCanvas("DCCanvas", gPrint[dcType] + "all");
	} else if(dcType == 2) {
		printCanvas("DCCanvas", gPrint[0] + sString);
	} else if(dcType == 3) {
		printCanvas("DCCanvas", gPrint[1] + sString);
	}
}


// return index of the 4 cases, from 0 to 3
int dcCase(int whichPlot)
{
	if(whichPlot < 10) {
		return whichPlot - 1;
	} else if(whichPlot >= 10 && whichPlot < 20) {
		return 2;
	} else {
		return 3;
	}
}


// return index of the graph
int graphIndex(int whichPlot)
{
	if(whichPlot < 20) {
		return whichPlot - 10;
	} else {
		return whichPlot - 20;
	}
}



void addDCButtons(TControlBar *toBar)
{
	toBar->AddButton(" "," ");
	toBar->AddButton("Show DC mean all sectors",  "showDC(1)");
	toBar->AddButton("Show DC sigma all sectors", "showDC(2)");
	toBar->AddButton(" "," ");
	toBar->AddButton("Show DC mean Sector 1 ",    "showDC(10)");
	toBar->AddButton("Show DC mean Sector 2 ",    "showDC(11)");
	toBar->AddButton("Show DC mean Sector 3 ",    "showDC(12)");
	toBar->AddButton("Show DC mean Sector 4 ",    "showDC(13)");
	toBar->AddButton("Show DC mean Sector 5 ",    "showDC(14)");
	toBar->AddButton("Show DC mean Sector 6 ",    "showDC(15)");
	toBar->AddButton(" "," ");
	toBar->AddButton("Show DC Sigma Sector 1 ",    "showDC(20)");
	toBar->AddButton("Show DC Sigma Sector 2 ",    "showDC(21)");
	toBar->AddButton("Show DC Sigma Sector 3 ",    "showDC(22)");
	toBar->AddButton("Show DC Sigma Sector 4 ",    "showDC(23)");
	toBar->AddButton("Show DC Sigma Sector 5 ",    "showDC(24)");
	toBar->AddButton("Show DC Sigma Sector 6 ",    "showDC(25)");
}














