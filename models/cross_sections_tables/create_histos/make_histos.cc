#include "bin.h"
#include "mod_histos.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char** argv)
{
	bins Bin;
	string model = argv[1];
	
	mod_histos TH(model);
	TH.define_histos();
	
	double ww,  qq,  cc,  pp;
	unsigned int www, qqq, ccc, ppp;
	double tmp;
	double cs;
	
	string filename = model + ".dat";
	cout << " Reading datafile for model: " << model << " from file " << filename << "...";
	ifstream IN(filename.c_str());
	if(!IN)
	{
		cout << " File " <<  filename << " could not be opened. Exiting." << endl;
		exit(0);
	}
	
	while(IN)
	{
		IN >>  ww >>  qq >> tmp >>  cc >>  pp >> cs ;
		
		
		for(unsigned int w=0; w<Bin.WMBIN; w++) if(fabs(ww - Bin.wm_center[w]) < 0.001) www = w;
		for(unsigned int q=0; q<Bin.Q2BIN; q++) if(fabs(qq - Bin.q2_center[q]) < 0.02)  qqq = q;
		for(unsigned int c=0; c<Bin.CTBIN; c++) if(fabs(cc - Bin.ct_center[c]) < 0.001) ccc = c;
		for(unsigned int p=0; p<Bin.PHBIN; p++) if(fabs(pp - Bin.ph_center[p]) < 0.001) ppp = p;

// 		cout << ww << " " << www << " " << qq << " " << qqq << " " << cc << " " << ccc << " " << pp << " " << ppp << endl;
		
		TH.pht_model[www][qqq]->SetBinContent(ccc+1, ppp+1, cs);
		if(qq == 5.0) TH.pht_model[www][qqq+1]->SetBinContent(ccc+1, ppp+1, cs);
	}
	
	IN.close();
	cout << "done. " << endl << endl;
	
	TH.slice_histos();
	
	string out_filename = model + ".root";
	TH.write_histos(out_filename);
	
}











