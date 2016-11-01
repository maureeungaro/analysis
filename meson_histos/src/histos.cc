// MU includes
#include "histos.h"
#include "bin.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

// Kinematics:
// b + T -> e + P + X
// q = b - e
// H = q + T = P + X

void histos::fill(CLAS_Event Ev, CLAS_Event_opts Opts)
{
	// don't consider it if it's scaler event
	if(Ev.start_time == 0) return;

	bins Bin[3];
	Bin[0] =  bins(45, 10, 24);
	Bin[1] =  bins(45, 10, 48);
	Bin[2] =  bins(45, 10, 96);
	
	// don't consider it if there isn't at least 1 electron, 1 proton
	if(get_particles(Ev, "electron").size()*get_particles(Ev, "proton").size() == 0) return;
	
	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));
	
	V4 b(0, 0, beam_e, beam_e);       // Incident Electron Four momentum
	V4 T(0, 0,      0, target_mass);  // Target Mass
	
	V4 e = get_particles(Ev, "electron").front().p;
	V4 P = get_particles(Ev, "proton").front().p;
	
	
	V4 q   = b - e;  // virtual photon 4-vector
	V4 H   = q + T;  // Outgoing Hadrons 4-vector
	V4 X   = H - P;  // e P missing particle
	V4 XCM = lab_to_res(H, X);	
	
	double phi = XCM.phi()/degree;
	double cth = cos(XCM.theta());

	Q2_W[0]->Fill(sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
	W_epXmm2[0]->Fill(sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
	
	// pi0
	if(X.mass()/GeV/GeV < 0.07)
	{ 
		Q2_W[1]->Fill(sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		W_epXmm2[1]->Fill(sqrt(H.mass())/GeV, X.mass()/GeV/GeV);

		
		for(int b=0; b<3; b++)
		{
			unsigned int wb = Bin[b].wmbin(sqrt(H.mass())/GeV);
			unsigned int qb = Bin[b].q2bin(-q.mass()/GeV/GeV);
			// cout << wb << " " << sqrt(H.mass())/GeV << "      " << qb << " " << -q.mass()/GeV/GeV << "     " << phi << " " << cth << endl;
			if(wb < Bin[b].WMBIN && qb<Bin[b].Q2BIN)
				pi0[wb][qb][b]->Fill(cth, phi);
		}
		
	}
	// eta
	if(X.mass()/GeV/GeV > 0.25 && X.mass()/GeV/GeV < 0.37 )
	{ 
		Q2_W[2]->Fill(sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		W_epXmm2[2]->Fill(sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
		for(int b=0; b<3; b++)
		{
			unsigned int wb = Bin[b].wmbin(sqrt(H.mass())/GeV);
			unsigned int qb = Bin[b].q2bin(-q.mass()/GeV/GeV);
			// cout << wb << " " << sqrt(H.mass())/GeV << "      " << qb << " " << -q.mass()/GeV/GeV << "     " << phi << " " << cth << endl;
			if(wb > MEB && wb < Bin[b].WMBIN && qb<Bin[b].Q2BIN)
				eta[wb][qb][b]->Fill(cth, phi);
		}
	}
	
	
}





