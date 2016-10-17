// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "histos.h"
#include "bin.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <string>
#include <iostream>
using namespace std;

// Kinematics:
// b + T -> e + P + X
// q = b - e
// H = q + T = P + X

void histos::fill(CLAS_Event Ev, CLAS_Event_opts Opts)
{
	bins Bin[3];
	Bin[0] =  bins(45, 10, 24);
	Bin[1] =  bins(45, 10, 48);
	Bin[2] =  bins(45, 10, 96);

	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));
	
	V4 b(0, 0, beam_e, beam_e);       // Incident Electron Four momentum
	V4 T(0, 0,      0, target_mass);  // Target Mass

	// generated particles will always be there
	V4 gen_e   = get_gparticles(Ev, "electron").front().p;
	V4 gen_P   = get_gparticles(Ev, "proton").front().p;
	V4 gen_q   = b     - gen_e;   // virtual photon 4-vector
	V4 gen_H   = gen_q + T;       // Outgoing Hadrons 4-vector
	V4 gen_X   = gen_H - gen_P;   // e P missing particle
	V4 gen_XCM = lab_to_res(gen_H, gen_X);

	
	// the reconstructed particle might not be there
	// need to define their quantities first
	int rec = get_particles(Ev, "electron").size()*get_particles(Ev, "proton").size();
	V4 rec_e, rec_P;
	V4 rec_q;   // virtual photon 4-vector
	V4 rec_H;   // Outgoing Hadrons 4-vector
	V4 rec_X;   // e P missing particle
	V4 rec_XCM;
	if(rec)
	{
		rec_e = get_particles(Ev, "electron").front().p;
		rec_P = get_particles(Ev, "proton").front().p;
		rec_q   = b     - rec_e;   
		rec_H   = rec_q + T;       
		rec_X   = rec_H - rec_P;   
		rec_XCM = lab_to_res(rec_H, rec_X);
	}


	// generated pi0s
	// do I need the cut for generated events?
	// 	if(gen_X.mass()/GeV/GeV < 0.08)
	for(int b=0; b<3; b++)
	{
		unsigned int wb = Bin[b].wmbin(sqrt(gen_H.mass())/GeV);
		unsigned int qb = Bin[b].q2bin(-gen_q.mass()/GeV/GeV);
		// 		cout << wb << " " << sqrt(H.mass())/GeV << "      " << qb << " " << -q.mass()/GeV/GeV << "     " << phi << " " << cth << endl;
		if(wb < Bin[b].WMBIN && qb<Bin[b].Q2BIN)
			pi0_gen[wb][qb][b]->Fill(cos(gen_XCM.theta()), gen_XCM.phi()/degree);
	}
	
	// reconstructed info
	if(rec && rec_X.mass()/GeV/GeV < 0.07)
		for(int b=0; b<3; b++)
		{
			unsigned int wb = Bin[b].wmbin(sqrt(rec_H.mass())/GeV);
			unsigned int qb = Bin[b].q2bin(-rec_q.mass()/GeV/GeV);
			if(wb < Bin[b].WMBIN && qb<Bin[b].Q2BIN)
				pi0_rec[wb][qb][b]->Fill(cos(rec_XCM.theta()), rec_XCM.phi()/degree);
		}
		
	
	
	
}





