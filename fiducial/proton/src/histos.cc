// MU includes
#include "histos.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;


void histos::fill(map<string, int> passed, particle P)
{
	set_vars(passed);
	int sector = P.sector() - 1;
	
	vector<V3> pos = P.vvget("DCxyz");
	// EC position is in global coordinate, converting to local coordinates
	V3 glob_ec = P.vget("ECxyz");
	float theta_loc = (sector * 60)*degree;
	
	pos.push_back(glob_ec.Zrot(theta_loc));
	pos.push_back(P.vget("SCxyz"));
	
	if(pos.size() != 5) return;
	
	int binp = (int) floor( (P.p.mod()/GeV - minp)/dp );
	if(binp > NDIV_P-1)
		binp = NDIV_P-1;
	if(binp < 0)
		binp = 0;
	
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// FID_XY: X vs Y fiducial cuts
	// no cuts
	phi_theta[0][sector][binp]->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
	phi_theta[0][6][binp]     ->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
	for(int p=0; p<5; p++)
	{
		x_y[0][sector][p][binp]->Fill(pos[p].y/cm, pos[p].x/cm);
		x_y[0][6][p][binp]     ->Fill(pos[p].y/cm, pos[p].x/cm);
		x_y_tot[0][sector][p]  ->Fill(pos[p].y/cm, pos[p].x/cm);
		x_y_tot[0][6][p]       ->Fill(pos[p].y/cm, pos[p].x/cm);
	}
	
	if(alloth["FID_XY"] == 1)
	{
		phi_theta[1][sector][binp]->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		phi_theta[1][6][binp]     ->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		for(int p=0; p<5; p++)
		{
			x_y[1][sector][p][binp]->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y[1][6][p][binp]     ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[1][sector][p]  ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[1][6][p]       ->Fill(pos[p].y/cm, pos[p].x/cm);
		}
	}
	
	if(othneg["FID_XY"] == 1)
	{
		phi_theta[2][sector][binp]->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		phi_theta[2][6][binp]     ->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		for(int p=0; p<5; p++)
		{
			x_y[2][sector][p][binp]->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y[2][6][p][binp]     ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[2][sector][p]  ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[2][6][p]       ->Fill(pos[p].y/cm, pos[p].x/cm);
		}
	}
	
	if(passed["PASSED"] == 1)
	{
		phi_theta[3][sector][binp]->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		phi_theta[3][6][binp]     ->Fill(P.p.theta()/degree, loc_phi(P.p)/degree);
		for(int p=0; p<5; p++)
		{
			x_y[3][sector][p][binp]->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y[3][6][p][binp]     ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[3][sector][p]  ->Fill(pos[p].y/cm, pos[p].x/cm);
			x_y_tot[3][6][p]       ->Fill(pos[p].y/cm, pos[p].x/cm);
		}
	}
	// FID_XY: X vs Y fiducial cuts
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
}


void histos::set_vars(map<string, int> passed)
{
	alloth.clear();
	othneg.clear();
	
	// X vs Y Fiducial cut
	if( passed["FID_XY"] == 1)
		alloth["FID_XY"] = 1;
		
	if( passed["FID_XY"] == 0)
		othneg["FID_XY"] = 1;
	
}






