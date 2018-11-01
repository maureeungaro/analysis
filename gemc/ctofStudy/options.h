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
	vector<TH1F*> ctofRatesTotal;
	vector<TH1F*> ctofRatesHadronic;
	vector<TH1F*> ctofRatesEm;
	vector<TH1F*> ctofRatesGamma;

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

private:
	void defineHistos(string c);
	void initLeafs();
	void fillHistos(int index);
	void setDirHistos(int index);
	void writeHistos();

};

#endif
