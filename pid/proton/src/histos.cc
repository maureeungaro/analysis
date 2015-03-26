// MU includes
#include "histos.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;


void histos::fill(map<string, int> passed, particle p, double tr_time)
{
	set_vars(passed);
	int sector_i   = p.sector() - 1;
	double mom     = p.p.mod();
	double beta    = speed_of_light*sqrt( mom*mom /( proton_mass*proton_mass + mom*mom ) );
	double t_calc  = (p.get("scpath")/cm) / beta + tr_time/ns - p.get("sctime")/ns;
	double beta_tr = (p.get("scpath")/cm) / (p.get("sctime")/ns - tr_time/ns) / speed_of_light;
	
	double tof_mass2 = (mom/GeV)*(mom/GeV)*(1-beta_tr*beta_tr)/(beta_tr*beta_tr);
	
	// Some particles have mom = 0 (some mistake somewhere)
	if(mom/GeV < 0.001) return;
	
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// DT_MOM: Delta T
	// no cuts
	if(p.scinfos.size() )
	{
		dt_mom[sector_i]->Fill(mom/GeV, t_calc);
		dt_mom[6]->Fill(mom/GeV, t_calc);
		dt_momz[sector_i]->Fill(mom/GeV, t_calc);
		dt_momz[6]->Fill(mom/GeV, t_calc);
		beta_vs_mom[0][sector_i]->Fill(mom/GeV, beta_tr);
		beta_vs_mom[0][6]->Fill(mom/GeV, beta_tr);
		mass_vs_mom[0][sector_i]->Fill(mom/GeV, tof_mass2);
		mass_vs_mom[0][6]->Fill(mom/GeV, tof_mass2);
	}
		
	if(passed["PASSED"] == 1)
	{
		beta_vs_mom[1][sector_i]->Fill(mom/GeV, beta_tr);
		beta_vs_mom[1][6]->Fill(mom/GeV, beta_tr);
		mass_vs_mom[1][sector_i]->Fill(mom/GeV, tof_mass2);
		mass_vs_mom[1][6]->Fill(mom/GeV, tof_mass2);
	}	
	// End DT_MOM: Delta T
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
	
	// Monitor:
	// All 
	monitor[sector_i]->Fill(0);
	monitor[6]->Fill(0);
	// Hits in SC
	if(p.scinfos.size())
	{
		monitor[sector_i]->Fill(1);
		monitor[6]->Fill(1);
		if(passed["PASSED"] == 1)
		{
			monitor[sector_i]->Fill(2);
			monitor[6]->Fill(2);
		}
	}
	// recovered
	if(passed["PASSED"] == 1 && p.pid != 2212) 
	{
		monitor[sector_i]->Fill(3);
		monitor[6]->Fill(3);
	}
	// thrown away
	if(passed["PASSED"] == 0 && p.pid == 2212) 
	{
		monitor[sector_i]->Fill(4);
		monitor[6]->Fill(4);
	}
}


void histos::set_vars(map<string, int> passed)
{
	alloth.clear();
	othneg .clear();
	
	// Delta T versus momentum cut
	if( passed["DT_MOM"] == 1)
		alloth["DT_MOM"] = 1;
	
	if( passed["DT_MOM"] == 0)
		othneg["DT_MOM"] = 1;
}





