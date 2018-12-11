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

	vector<TH2F*> vertexRZT;
	vector<TH1F*> vertexRT;
	vector<TH1F*> vertexZT;

	vector<TH1F*> scalers1a;
	vector<TH1F*> scalers1b;
	vector<TH1F*> current1a;
	vector<TH1F*> current1b;


	// as a function of momentum
	vector<TH1F*> leptons;
	vector<TH1F*> gammas;
	vector<TH1F*> pions;
	vector<TH1F*> protons;
	vector<TH1F*> neutrons;

	vector<TH1F*> leptonsZ;
	vector<TH1F*> gammasZ;
	vector<TH1F*> pionsZ;
	vector<TH1F*> protonsZ;
	vector<TH1F*> neutronsZ;


	vector<string> confs;


	// root trees. Generated for the number of events
	TTree *generated, *ftof;

	// ftof leafs
	vector<double> *paddle;
	vector<double> *layer;
	vector<double> *sector;
	vector<double> *x;
	vector<double> *y;
	vector<double> *z;
	vector<double> *lx;
	vector<double> *pid;
	vector<double> *mpid;
	vector<double> *totEdep;
	vector<double> *vx;
	vector<double> *vy;
	vector<double> *vz;
	vector<double> *px;
	vector<double> *py;
	vector<double> *pz;


	vector<double> paddleAttLength;
	vector<double> paddleLength;

private:
	void defineHistos(string c);
	void initLeafs();
	void fillHistos(int index);
	void setDirHistos(int index);
	void writeHistos();

};

#endif
