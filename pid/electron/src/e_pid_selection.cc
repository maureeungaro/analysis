// MU includes
#include "e_pid_selection.h"
#include "utilities.h"

// C++ includes
#include <sstream>
#include <fstream>
#include <cstdlib>


map<string, int> e_pid_selection::selection(particle p)
{
	map<string, int> selection;
	selection.clear();
	
	if(p.get("dcstat")<=0) {
        return selection;
    }

	int sector_i = p.sector() - 1;   // getting sector from phi
	double mom = p.p.mod()/GeV;
	
	// Initialize map to zero
	selection["NPHE"]     = 0;
	selection["CCTHEM"]   = 0;
	selection["CCPHIM"]   = 0;
	selection["CCTIME"]   = 0;
	selection["CCMATCH"]  = 0;
	selection["ECTHR"]    = 0;
	selection["ECP"]      = 0;
	selection["EPOU"]     = 0;
	selection["EPOV"]     = 0;
	selection["EPOW"]     = 0;
	selection["ECUVW"]    = 0;
	selection["ECIO"]     = 0;
	selection["INTO"]     = 0;
	selection["PASSED"]   = 0;


    // The CC matching are from
    // Osipenko clas note 2004-020
    // CC Theta MATCH
    double cctheta = p.vget("CCxyz").theta()/degree;
    double segm    = (double) p.get("ccsegm");
    double pmt     =  p.get("ccpmt");
    int cc_sect    = p.get("ccsect");
    int dc_sect    = p.get("dcsect");
    double cc_min  = CC_limit(segm, sector_i+1, -1);
    double cc_max  = CC_limit(segm, sector_i+1,  1);
    // no cuts on first and last pmt
/*	if(segm == 1 || segm == 18)
		selection["CCTHEM"] = 1;*/
    if(cc_sect == dc_sect && cctheta >= cc_min && cctheta <= cc_max) {
        selection["CCTHEM"] = 1;
    }

    // pmt == 0 is when both pmt in the same
    // segment are fired.
    // in that case we bypass the cut
    if(pmt == 0) {
        selection["CCTHEM"] = 1;
    }

    // CC Phi MATCH
    double ccphimatch = p.get("ccphimatch");
    if(fabs(ccphimatch) < 2 || fabs(loc_phi(p.p)/degree) < 4) {
        selection["CCPHIM"] = 1;
    }

    // CC timing
    double time_corr  = fabs( (p.vget("CCxyz") - p.vget("SCxyz") ).mod()/cm) / speed_of_light;
    double ccdtime    = p.get("cctime") + time_corr - p.get("sctime");
    int    pmt_number = ( p.get("ccpmt") > 0 ? (int) segm*2 :(int) segm*2-1 );

    // if GSIM, don't apply this

    if(ccdtime > cc_timing_low[sector_i][pmt_number-1]) {
        selection["CCTIME"]   = 1;
    }

    // All CC Matching:
    if(selection["CCTHEM"]*selection["CCPHIM"]*selection["CCTIME"] == 1) {
        selection["CCMATCH"]  = 1;
    }

	// NPHE cut
	if(p.get("npe") >= min_nphe[sector_i]) {
		selection["NPHE"] = 1;	
    }




	// EC Threshold min p cut
	if(mom >= p_ec_threshold/GeV) {
        selection["ECTHR"] = 1;
    }
	
	// Sampling Fraction cut
	double Etot = p.get("Emax")/GeV;
	double min = ecp_limit(mom, sector_i+1, -1);
	double max = ecp_limit(mom, sector_i+1,  1);
	double ecp = Etot/mom;	
	if(ecp >= min && ecp <= max) {
        selection["ECP"] = 1;
    }
	
	// EC x vs y track Position
	V3 uvw = p.vget("ECuvw");	
	double u = uvw.x;
	double v = uvw.y;
	double w = uvw.z;
	if(u>=umin && u<=umax) { selection["EPOU"] = 1; }
	if(v<=vmax)            { selection["EPOV"] = 1; }
	if(w<=wmax)            { selection["EPOW"] = 1; }
	if(selection["EPOU"]*selection["EPOV"]*selection["EPOW"] == 1) {
        selection["ECUVW"] = 1;
    }
	
	// EC Eout/p vs Ein/p
	double EinP  = (p.get("Ein")/GeV) /mom;
	double EoutP = (p.get("Eout")/GeV)/mom;
	double ecmin = ecop_vs_ecip_a[sector_i] + ecop_vs_ecip_b[sector_i]*EinP;
	// 	if(EinP == 0 && EoutP == 0) cout << " Attention: Ein and Eout are zero." << endl;
	if(EoutP > ecmin && EoutP > 0.001) {
        selection["ECIO"] = 1;
    }
	
	// EC inner/total
	double Ein  = p.get("Ein")/GeV;
	if(Ein/Etot >= min_ecit[sector_i]) {
        selection["INTO"] = 1;
    }
		
	if(  p.ccinfos.size() && p.cainfos.size() &&
		  selection["CCMATCH"]*
		  selection["ECTHR"]*
		  selection["ECP"]*
		  selection["ECUVW"]*
		  selection["ECIO"]*
		  selection["INTO"] == 1) {
        selection["PASSED"] = 1;
    }

	return selection;
}



