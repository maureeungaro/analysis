#include "TFile.h"

#include "poles.h"
#include <iostream>

int main(int argc, char **argv)
{
	vector<poles*>        Poles;
	vector<poles_histos*> PH;

	Poles.push_back(new poles("dmt2001"));
	Poles.push_back(new poles("maid2002"));
	Poles.push_back(new poles("maid2003"));
	Poles.push_back(new poles("maid2003woroper"));
	Poles.push_back(new poles("maid2007"));
	Poles.push_back(new poles("said2008"));
	Poles.push_back(new poles("hlee"));
	Poles.push_back(new poles("janr"));
	Poles.push_back(new poles("etamaid2001"));
	
	TFile *output = new TFile("poles.root","RECREATE","");
	for(unsigned int m=0; m<Poles.size(); m++)
	{
		PH.push_back(new poles_histos(Poles[m]));
	}

	output->Write();

	return 1;
}