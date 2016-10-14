// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "pi0_sel.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <sstream>
#include <fstream>
#include <cstdlib>

map<string, int> pi0_selection::selection(V4 e, V4 P, CLAS_Event_opts Opts)
{
	map<string, int> selection;
		
	
	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));
	
	V4 b(0, 0, beam_e, beam_e);       // Incident Electron Four momentum
	V4 T(0, 0,      0, target_mass);  // Target Mass
	
	V4 q = b - e;  // virtual photon 4-vector
	V4 H = q + T;  // Outgoing Hadrons 4-vector
	V4 X = H - P;  // e P missing particle

	double W =  sqrt(H.mass())/GeV;
	
	// Initialize map to zero
	selection["PHI"]    = 0;
	selection["DTH1"]   = 0;
	selection["DTH2"]   = 0;
	selection["PASSED"] = 0;
	
	// don't consider W > 2.3, mm < 0.1 or W < 1.1
	if(X.mass()/GeV/GeV > 1 || sqrt(H.mass())/GeV > 2.3 || sqrt(H.mass())/GeV < 1.1)
		return selection;
	
	double dth1v = atan(1/(tan(e.theta()/2.)*( 1 + b.t/proton_mass)))/degree - P.theta()/degree;
	double dth2v = atan(1/(tan(e.theta()/2.)*(1+(proton_mass*e.t/(proton_mass-e.t+e.t*cos(e.theta()))/proton_mass))))/degree - P.theta()/degree;
	double dphiv = ( e.phi() - P.phi() )/degree;
  if(dphiv <  0) dphiv = dphiv + 360;
	
	if(dphiv<=phiMin/degree || dphiv>=phiMax/degree)
		selection["PHI"] = 1;

	if(dth1v<=dth1Min/degree || dth1v>=dth1Max/degree)
		selection["DTH1"] = 1;

	double dth2_max = (dth2_mean_a + W*dth2_mean_b) + 4*dth2_sigma + (W-1.1)*2.5;
	if(dth2v>=dth2_max)
		selection["DTH2"] = 1;
	
	
	if(selection["PHI"]*selection["DTH1"]*selection["DTH2"] == 1)
		selection["PASSED"] = 1;
		
	return selection;
}




