#include "dcHistos.h"



dcHistos::dcHistos(vector<string> confs, int recalc)
{
	// zone limits
	// -----------
	// near target
	zlimits[0][0][0] = -10;    zlimits[0][1][0] =  150;
	zlimits[2][0][0] = -100;   zlimits[2][1][0] = 1000;

	// beampipe
	zlimits[0][0][1] = -100;   zlimits[0][1][1] = 1400;
	zlimits[2][0][1] = -100;   zlimits[2][1][1] = 1600;

	// torus
	zlimits[0][0][2] = -200;    zlimits[0][1][2] = 1500;
	zlimits[2][0][2] = 2500;   zlimits[2][1][2] = 6000;

	// all
	zlimits[0][0][3] = -100;   zlimits[0][1][3] = 2000;
	zlimits[2][0][3] = -100;   zlimits[2][1][3] = 3000;










}
