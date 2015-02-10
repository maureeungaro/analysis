#include "bin.h"
#include "rad_histos.h"

// make sure the .sum file is not corrupted - check for "*" and NaN
// usually it's the log approx, can be ignored - just copy the previous entry

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char** argv)
{
	bins Bin;
	string model = argv[1];
	string vcut  = argv[2];
	
	rad_histos RH;
	RH.define_histos();
	
	
	double ww,  qq,  cc,  pp;
	unsigned int www, qqq, ccc, ppp;
	double tmp;
	double cor;
	
	string filename = model + "_rad_cor_" + vcut + ".sum";
	cout << " Reading datafile for model: " << model << " from file " << filename << "...";
	ifstream IN(filename.c_str());
	if(!IN)
	{
		cout << " File " <<  filename << " could not be opened. Exiting." << endl;
		exit(0);
	}
	
	while(IN)
	{
		IN >>  ww >>  qq >> tmp >>  cc >>  pp >> cor >> tmp >> tmp ;
		IN >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp ;
		
		for(unsigned int w=0; w<Bin.WMBIN; w++) if(fabs(ww - Bin.wm_center[w]) < 0.001) www = w;
		for(unsigned int q=0; q<Bin.Q2BIN; q++) if(fabs(qq - Bin.q2_center[q]) < 0.001) qqq = q;
		for(unsigned int c=0; c<Bin.CTBIN; c++) if(fabs(cc - Bin.ct_center[c]) < 0.001) ccc = c;
		for(unsigned int p=0; p<Bin.PHBIN; p++) if(fabs(pp - Bin.ph_center[p]) < 0.001) ppp = p;
		
		RH.pht_rad_cor[www][qqq]->SetBinContent(ccc+1, ppp+1, cor);
		if(qq == 5.0) RH.pht_rad_cor[www][qqq+1]->SetBinContent(ccc+1, ppp+1, cor);
	}
	IN.close();
	cout << "done. " << endl << endl;
	
	string out_filename = model + "_rad_cor_" + vcut + ".root";
	RH.write_histos(out_filename);
	
}











