// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "vertex_corrsel.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <sstream>
#include <fstream>
#include <cstdlib>

map<string, int> vertex_corr_selection::selection(particle e, particle p)
{
	map<string, int> selection;
		
	// Initialize map to zero
	selection["VCUT"]   = 0;	
	selection["PASSED"] = 0;
			
	e_v_corr = vertex_corr(e.v, e.p);
	p_v_corr = vertex_corr(p.v, p.p);
	
	// Delta VZ cut, single particles VZ cut
	if(fabs(e_v_corr.z - p_v_corr.z) < delta_z)
		if(e_v_corr.z >= vz_limits[0] && e_v_corr.z <= vz_limits[1])
			if(p_v_corr.z >= vz_limits[0] && p_v_corr.z <= vz_limits[1])
				selection["VCUT"] = 1;
				
	if(selection["VCUT"] == 1)
		selection["PASSED"] = 1;
		
	return selection;
}

V3 vertex_corr_selection::vertex_corr(V3 v, V4 p)
{
	V3 vc;

	double s0, sp, sv;
	static double n[3][6];
	n[0][0] = 1.;
	n[1][0] = 0.;
	
	n[0][1] = 0.5 ;
	n[1][1] = 0.866025388;

	n[0][2] = -0.5 ;
	n[1][2] = 0.866025388;

	n[0][3] = -1. ;
	n[1][3] = 0.;

	n[0][4] = -0.5 ;
	n[1][4] = -0.866025388;

	n[0][5] = 0.5 ;
	n[1][5] = -0.866025388;
 
	static double x0 =  beam_pos[0]/cm;
	static double y0 =  beam_pos[1]/cm;
	static double z0 =   0.;

	int s = sector(p) - 1; 
	double A; 

	s0 =     x0  * n[0][s]  +     y0  * n[1][s] +     z0  * n[2][s];
	sp = p.x/GeV * n[0][s]  + p.y/GeV * n[1][s] + p.z/GeV * n[2][s];
	sv = v.x/cm  * n[0][s]  +  v.y/cm * n[1][s] +  v.z/cm * n[2][s];
 
	if(sp)
	{
		A = (s0-sv)/sp;
		vc.x = (v.x/cm + A*p.x/GeV)*cm;
		vc.y = (v.y/cm + A*p.y/GeV)*cm;
		vc.z = (v.z/cm + A*p.z/GeV)*cm;
		return vc;
	}
	
	return v;
}




