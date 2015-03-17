// MU includes
#include "histos.h"
#include "bin.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;


void histos::fill(CLAS_Event Ev, CLAS_Event_opts Opts)
{
	// generated particles will always be there
	V4 gen_e   = get_gparticles(Ev, "electron").front().p;
	V4 gen_P   = get_gparticles(Ev, "proton").front().p;

	// the reconstructed particle might not be there
	// need to define their quantities first
	vector<particle> ele = get_particles(Ev, "electron");
	vector<particle> pro = get_particles(Ev, "proton");

	
	
	if(ele.size())
	{
		
		particle elep = ele.front();
		V4 rec_e = elep.p;
		
		int sector = elep.sector() - 1;
		
		mom[sector][0]->Fill( rec_e.mod()   - gen_e.mod());
		phi[sector][0]->Fill((rec_e.phi()   - gen_e.phi()   ) / degree);
		the[sector][0]->Fill((rec_e.theta() - gen_e.theta() ) / degree);
		
		momPhi[sector][0]->Fill(elep.rel_phi()/degree, rec_e.mod() - gen_e.mod());
		thePhi[sector][0]->Fill(elep.rel_phi()/degree, (rec_e.theta() - gen_e.theta() ) / degree);
		phiPhi[sector][0]->Fill(elep.rel_phi()/degree, (rec_e.phi() - gen_e.phi() ) / degree);

		
		
		
		mom[6][0]->Fill(rec_e.mod() - gen_e.mod());
		phi[6][0]->Fill( (rec_e.phi()   - gen_e.phi()   ) / degree);
		the[6][0]->Fill( (rec_e.theta() - gen_e.theta() ) / degree);

		momPhi[6][0]->Fill(rec_e.phi()/degree, rec_e.mod() - gen_e.mod());
		thePhi[6][0]->Fill(rec_e.phi()/degree, (rec_e.theta() - gen_e.theta() ) / degree);
		phiPhi[6][0]->Fill(rec_e.phi()/degree, (rec_e.phi() - gen_e.phi() ) / degree);

		
		
	}
	
	if(pro.size())
	{
		particle prop = pro.front();
		V4 rec_P = prop.p;
		
		int sector = pro.front().sector() - 1;
		


	}
	
	
}





