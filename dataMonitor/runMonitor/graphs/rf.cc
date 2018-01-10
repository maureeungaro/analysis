// runMonitor
#include "rf.h"
#include "../N.h"

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
