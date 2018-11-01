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
	anaOption(vector<string> configs);

public:
	int cIndex;      // cofiguration index
	string PRINT;    // Print on Image File


private:

	// rates as a function of paddle
	vector<TH1F*> ratesTotal;
	vector<TH1F*> ratesHadronic;
	vector<TH1F*> ratesEm;
	vector<TH1F*> ratesGamma;

	vector<TH1F*> ratesTotalT;
	vector<TH1F*> ratesHadronicT;
	vector<TH1F*> ratesEmT;
	vector<TH1F*> ratesGammaT;

	vector<TH1F*> ratesTotalEdep;
	vector<TH1F*> ratesHadronicEdep;
	vector<TH1F*> ratesEmEdep;
	vector<TH1F*> ratesGammaEdep;

	vector<TH1F*> ratesTotalEdepZ;
	vector<TH1F*> ratesHadronicEdepZ;
	vector<TH1F*> ratesEmEdepZ;
	vector<TH1F*> ratesGammaEdepZ;

	vector<TH2F*> vertexRZ;
	vector<TH1F*> vertexR;
	vector<TH1F*> vertexZ;

	vector<string> confs;

	// root trees. Generated for the number of events
	TTree *generated, *ctof;

	// ctof leafs
	vector<double> *paddle;
	vector<double> *x;
	vector<double> *y;
	vector<double> *z;
	vector<double> *pid;
	vector<double> *mpid;
	vector<double> *totEdep;
	vector<double> *vx;
	vector<double> *vy;
	vector<double> *vz;

private:
	void defineHistos(string c);
	void initLeafs();
	void fillHistos(int index);
	void setDirHistos(int index);
	void writeHistos();

};

#endif
