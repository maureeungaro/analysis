// Vertex includes
#include "histos.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

void histos::fill(map<string, int> passed, particle e, particle p, V3 e_v_corr, V3 p_v_corr)
{
	set_vars(passed);
	int e_sector_i = e.sector() - 1;
	int p_sector_i = p.sector() - 1;
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// VCUT: vertex cuts
	// no cuts
	deltavz_vz[e_sector_i][0]->Fill(e.v.z/cm, (e.v.z - p.v.z)/cm);
	    phi_vz[e_sector_i][0][0]->Fill(e.v.z/cm, e.p.phi()/degree);
	    phi_vz[p_sector_i][0][1]->Fill(p.v.z/cm, p.p.phi()/degree);
	        vz[e_sector_i][0][0]->Fill(e.v.z/cm);
	        vz[p_sector_i][0][1]->Fill(p.v.z/cm);

	// all sectors
	deltavz_vz[6][0]->Fill(e.v.z/cm, (e.v.z - p.v.z)/cm);
	    phi_vz[6][0][0]->Fill(e.v.z/cm, e.p.phi()/degree);
	    phi_vz[6][0][1]->Fill(p.v.z/cm, p.p.phi()/degree);
	        vz[6][0][0]->Fill(e.v.z/cm);
	        vz[6][0][1]->Fill(p.v.z/cm);
	
	// after correction
	deltavz_vz[e_sector_i][1]->Fill(e_v_corr.z/cm, (e_v_corr.z - p_v_corr.z)/cm);
	    phi_vz[e_sector_i][1][0]->Fill(e_v_corr.z/cm, e.p.phi()/degree);	
	    phi_vz[p_sector_i][1][1]->Fill(p_v_corr.z/cm, p.p.phi()/degree);
	        vz[e_sector_i][1][0]->Fill(e_v_corr.z/cm);
	        vz[p_sector_i][1][1]->Fill(p_v_corr.z/cm);

	// all sectors
	deltavz_vz[6][1]->Fill(e_v_corr.z/cm, (e_v_corr.z - p_v_corr.z)/cm);
	    phi_vz[6][1][0]->Fill(e_v_corr.z/cm, e.p.phi()/degree);
	    phi_vz[6][1][1]->Fill(p_v_corr.z/cm, p.p.phi()/degree);
	    vz[6][1][0]->Fill(e_v_corr.z/cm);
	    vz[6][1][1]->Fill(p_v_corr.z/cm);
	
	// corrected, passed the cut
	if(passed["PASSED"] == 1)
	{
		deltavz_vz[e_sector_i][2]->Fill(e_v_corr.z/cm, (e_v_corr.z - p_v_corr.z)/cm);
		    phi_vz[e_sector_i][2][0]->Fill(e_v_corr.z/cm, e.p.phi()/degree);	
		    phi_vz[p_sector_i][2][1]->Fill(p_v_corr.z/cm, p.p.phi()/degree);
		        vz[e_sector_i][2][0]->Fill(e_v_corr.z/cm);
		        vz[p_sector_i][2][1]->Fill(p_v_corr.z/cm);
		// all sectors
		deltavz_vz[6][2]->Fill(e_v_corr.z/cm, (e_v_corr.z - p_v_corr.z)/cm);
		    phi_vz[6][2][0]->Fill(e_v_corr.z/cm, e.p.phi()/degree);
		    phi_vz[6][2][1]->Fill(p_v_corr.z/cm, p.p.phi()/degree);
		        vz[6][2][0]->Fill(e_v_corr.z/cm);
		        vz[6][2][1]->Fill(p_v_corr.z/cm);
	}
	// End VCUT: vertex cuts
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	
	
}


void histos::set_vars(map<string, int> passed)
{
	alloth.clear();
	othneg .clear();
	
	// Delta T versus momentum cut
	if( passed["VCUT"] == 1)
		alloth["VCUT"] = 1;
	
	if(passed["VCUT"] == 0)
		othneg["VCUT"] = 1;
}
