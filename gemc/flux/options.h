#ifndef ANAHISTOS_H
#define ANAHISTOS_H


#include "TH2F.h"

#include <string>
#include <vector>
using namespace std;


class anaOption {

public:
	anaOption(bool r);

public:
	int NHITS;
	int pIndex;      // particle index
	string PRINT;    // Print on Image File


private:
	bool recalc;

	// histograms
	// 2D flux histos:
	vector<TH2F*> pflux;

	// 1D quantities
	vector<TH1F*> pzver;
	vector<TH1F*> pmom;
	vector<TH1F*> pprocID;

	vector<string> partTit;
	vector<int>    partiID;

public:
	void showFlux();
};

#endif
