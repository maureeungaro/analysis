// MU includes
#include "fiducial_cut.h"

// C++ includes
#include <sstream>
#include <fstream>
#include <cstdlib>

map<string, int> fiducial_cut::selection(particle e)
{
	map<string, int> selection;
	selection.clear();
	
	if(e.get("dcstat")<=0)
		return selection;
	
	// Initialize map to zero
	selection["FID_PT"]     = 0;
	selection["FID_XY"]     = 0;
	selection["FID_XY_DC1"] = 0;
	selection["FID_XY_DC2"] = 0;
	selection["FID_XY_DC3"] = 0;
	selection["FID_XY_SC"]  = 0;
	selection["FID_HOLES"]  = 0;
	
	selection["PASSED"] = 0;

	// phi vs theta fiducal cut
	if( fabs(loc_phi(e.p)/degree)  < dphi(sector(e.p), e.p.mod()/GeV, e.p.theta()/degree) )
		selection["FID_PT"] = 1;
	
	
	// x vs y fiducal cut
	vector<V3> dcpos = e.vvget("DCxyz");
	V3         scpos = e.vget("SCxyz");
	
	if(dcpos.size() != 3) return selection;
	
	if(xycut(sector(e.p), 1, dcpos[0].x/cm, dcpos[0].y/cm) == 1)
		selection["FID_XY_DC1"] = 1;
	
	if(xycut(sector(e.p), 2, dcpos[1].x/cm, dcpos[1].y/cm) == 1)
		selection["FID_XY_DC2"] = 1;
		
	if(xycut(sector(e.p), 3, dcpos[2].x/cm, dcpos[2].y/cm) == 1)
		selection["FID_XY_DC3"] = 1;
		
	if(xycut(sector(e.p), 5,    scpos.x/cm,    scpos.y/cm) == 1)
		selection["FID_XY_SC"] = 1;

	if(selection["FID_XY_DC1"]*selection["FID_XY_DC2"]*selection["FID_XY_DC3"]*selection["FID_XY_SC"] == 1)
		selection["FID_XY"] = 1;
	
	// x vs y holes
	if(xyholes(sector(e.p), 1, dcpos[0].x/cm, dcpos[0].y/cm)*
		xyholes(sector(e.p), 2, dcpos[1].x/cm, dcpos[1].y/cm)*
		xyholes(sector(e.p), 3, dcpos[2].x/cm, dcpos[2].y/cm)*
		xyholes(sector(e.p), 5,    scpos.x/cm,    scpos.y/cm) == 1 )
		selection["FID_HOLES"] = 1;
		
	if(selection["FID_PT"]*selection["FID_HOLES"])
//		if(selection["FID_XY"]*selection["FID_HOLES"])
			selection["PASSED"] = 1;
		
	
	return selection;
}



