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
	anaOption(bool r, vector<string> configs);

public:
	int cIndex;      // cofiguration index
	string PRINT;    // Print on Image File


private:

	vector<TH2F*> dmom;
	vector<TH1F*> deMom;
	vector<TH1F*> theta;
	vector<TH2F*> deMomTheta;

	vector<string> confs;

	// root trees
	TTree *generated, *ftof;

	// ftof leafs
	vector<double> *sector;
	vector<double> *layer;
	vector<double> *x;
	vector<double> *y;
	vector<double> *pid;
	vector<double> *mpid;
	vector<double> *px;
	vector<double> *py;
	vector<double> *pz;

	// generated leafs
	vector<double> *gpx;
	vector<double> *gpy;
	vector<double> *gpz;


private:
	void defineHistos(string c);
	void initLeafs();
	void fillHistos(int index);
	void setDirHistos(int index);
	void writeHistos();

};

#endif
