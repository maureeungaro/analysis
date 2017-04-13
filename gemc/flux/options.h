#ifndef ANAHISTOS_H
#define ANAHISTOS_H

// root
#include "TH2F.h"
#include "TTree.h"

// c++
#include <string>
#include <vector>
using namespace std;


class anaOption {

public:
	anaOption(bool r);

public:
	int pIndex;      // particle index
	int cIndex;      // cofiguration index
	string PRINT;    // Print on Image File


private:
	// histograms
	// index is configuration
	// 2D flux histos:
	vector<TH2F*> pflux;

	// 1D quantities
	vector<TH1F*> pzver;
	vector<TH1F*> pmom;
	vector<TH1F*> pprocID;

	vector<string> partTit;  // not used
	vector<string> confs;
	vector<int>    partiID;

	// root trees
	TTree *generated, *flux;

	// flux tree
	vector<double> *x;
	vector<double> *y;
	vector<double> *vz;
	vector<double> *pid;
	vector<double> *mpid;
	vector<double> *procID;
	vector<double> *px;
	vector<double> *py;
	vector<double> *pz;


private:
	void setParticles();
	void defineHistos();
	void setDirHistos();
	void writeHistos();
	void initLeafs();
};

#endif
