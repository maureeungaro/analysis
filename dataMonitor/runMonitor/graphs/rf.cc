// runMonitor
#include "rf.h"

void initRFGraphs()
{
	cout << " Initializing RF graphs." << endl;

	char tmp[100];
	double run[N];
	double dRF[N], dsRF[N], dRFP[N], dsRFP[N], dRFpp[N], dsRFpp[N], dRFpm[N], dsRFpm[N];

	ifstream IN("mysql/RF.dat");
	for(int i=0; i<N; i++)
		IN >> tmp >> run[i] >> dRF[i] >> dsRF[i] >> dRFP[i] >> dsRFP[i] >> dRFpp[i] >> dsRFpp[i] >> dRFpm[i] >>  dsRFpm[i] >> tmp >> tmp >> tmp >> tmp  ;
	IN.close();

	RF      = new TGraph(N, run, dRF);
	sRF     = new TGraph(N, run, dsRF);
	RFP     = new TGraph(N, run, dRFP);
	sRFP    = new TGraph(N, run, dsRFP);
	RFpp    = new TGraph(N, run, dRFpp);
	sRFpp   = new TGraph(N, run, dsRFpp);
	RFpm    = new TGraph(N, run, dRFpm);
	sRFpm   = new TGraph(N, run, dsRFpm);


	// putting all in a vector so we can style them all together
	vector<TGraph*> allGraphs = {RF, sRF, RFP, sRFP, RFpp, sRFpp, RFpm, sRFpm};

	for(auto g: allGraphs) {
		g->SetMarkerStyle(20);
		g->SetMarkerSize(0.6);
		g->GetYaxis()->SetTitleColor(4);
		g->GetYaxis()->SetTitle("nanoseconds");
		g->GetXaxis()->SetNdivisions(8);
		g->SetMarkerColor(4);

	}

	// sigmas are red
	sRF->SetMarkerColor(2);
	sRFP->SetMarkerColor(2);
	sRFpp->SetMarkerColor(2);
	sRFpm->SetMarkerColor(2);

}

void showRF(int whichParticle)
{
	TCanvas *RFCanvas = (TCanvas*) gROOT->FindObject("RFCanvas");

	if(RFCanvas== nullptr) {
		RFCanvas = new TCanvas("RFCanvas",  "RFCanvas", 1200, 800);
		RFCanvas->SetFillColor(18);
		RFCanvas->SetGridx();
		RFCanvas->SetGridy();
	}
	RFCanvas->Clear();

	string gTitle[4]   = {"All Particles RF", "Protons RF", "#pi^{+}    RF", "#pi^{-}    RF"};
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


}
