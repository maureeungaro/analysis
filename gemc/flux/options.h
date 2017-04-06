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
	int pIndex, nParticles; // particle index
	string PRINT;           // Print on Image File


//private:
	bool recalc;

	// histograms
	// 2D flux histos:
	vector<TH2F*> *pflux;

	// Vertex histos
	vector<TH1F*> *pzver;

	vector<string> partTit;
	vector<string> partCut;

};

#endif
