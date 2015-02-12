// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "proton_pid_selection.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <sstream>
#include <fstream>
#include <cstdlib>

map<string, int> p_pid_selection::selection(particle p, double tr_time)
{
	map<string, int> selection;
	selection.clear();
	
	if(p.get("dcstat")<=0)
		return selection;
		
	// Initialize map to zero
	selection["DT_MOM"] = 0;	
	selection["PASSED"] = 0;
		
	// Delta T cut
	double mom     = p.p.mod();
	double beta    = speed_of_light*sqrt( mom*mom /( proton_mass*proton_mass + mom*mom ) );
	double min     = dt_mom_limit(mom/GeV, p.sector(), NSIGMAS[0], -1);
	double max     = dt_mom_limit(mom/GeV, p.sector(), NSIGMAS[1],  1);
	double t_calc  = (p.get("scpath")/cm) / beta + tr_time/ns - p.get("sctime")/ns;
	
	if(t_calc >= min && t_calc <= max)
		selection["DT_MOM"] = 1;	
			
	if(selection["DT_MOM"] == 1) 
		selection["PASSED"] = 1;
		
	return selection;
}


