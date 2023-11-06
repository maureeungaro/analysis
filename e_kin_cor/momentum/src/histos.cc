// MU includes
#include "histos.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;


void histos::fill(particle ele, particle pro, particle pip, CLAS_Event_opts Opts, mom_corr CORR)
{
	int e_sector_i   = ele.sector() - 1;

	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));

	V4 b(0, 0, beam_e, beam_e);       // Incident Electron Four momentum
	V4 T(0, 0,      0, target_mass);  // Target Mass

	V4 e  = ele.p;
	V4 ce = CORR.m_corr(ele.p);
	V4 P  = pro.p;
	V4 p  = pip.p;

	V4 q   = b - e;    // virtual photon 4-vector
	V4 H   = q + T;    // Outgoing Hadrons 4-vector
	V4 ePX = H - P;    // e P missing particle
	V4 epX = H - p;    // e pi+ missing particle

	V4 cq   = b - ce;
	V4 cH   = cq + T;
	V4 cePX = cH - P;
	V4 cepX = cH - p;

	hH[e_sector_i][0][0]->Fill(sqrt( H.mass())/GeV);
	hH[e_sector_i][1][0]->Fill(sqrt(cH.mass())/GeV);
	hH[6][0][0]->Fill(sqrt( H.mass())/GeV);
	hH[6][1][0]->Fill(sqrt(cH.mass())/GeV);

	hHt[e_sector_i][0][0]->Fill(e.theta()/degree, sqrt( H.mass())/GeV);
	hHt[e_sector_i][1][0]->Fill(e.theta()/degree, sqrt(cH.mass())/GeV);
	hHt[6][0][0]->Fill(e.theta()/degree, sqrt( H.mass())/GeV);
	hHt[6][1][0]->Fill(e.theta()/degree, sqrt(cH.mass())/GeV);

	hHp[e_sector_i][0][0]->Fill(loc_phi(e)/degree, sqrt( H.mass())/GeV);
	hHp[e_sector_i][1][0]->Fill(loc_phi(e)/degree, sqrt(cH.mass())/GeV);
	hHp[6][0][0]->Fill(loc_phi(e)/degree, sqrt( H.mass())/GeV);
	hHp[6][1][0]->Fill(loc_phi(e)/degree, sqrt(cH.mass())/GeV);


	if(pro.pid == 2212 && fabs(sqrt(cH.mass())/GeV-1.232)<.1) // pi0 in the delta
	{
		hH[e_sector_i][0][1]->Fill( ePX.mass()/GeV/GeV);
		hH[e_sector_i][1][1]->Fill(cePX.mass()/GeV/GeV);
		hH[6][0][1]->Fill( ePX.mass()/GeV/GeV);
		hH[6][1][1]->Fill(cePX.mass()/GeV/GeV);

		hHt[e_sector_i][0][1]->Fill(e.theta()/degree,  ePX.mass()/GeV/GeV);
		hHt[e_sector_i][1][1]->Fill(e.theta()/degree, cePX.mass()/GeV/GeV);
		hHt[6][0][1]->Fill(e.theta()/degree,  ePX.mass()/GeV/GeV);
		hHt[6][1][1]->Fill(e.theta()/degree, cePX.mass()/GeV/GeV);

		hHp[e_sector_i][0][1]->Fill(loc_phi(e)/degree,  ePX.mass()/GeV/GeV);
		hHp[e_sector_i][1][1]->Fill(loc_phi(e)/degree, cePX.mass()/GeV/GeV);
		hHp[6][0][1]->Fill(loc_phi(e)/degree,  ePX.mass()/GeV/GeV);
		hHp[6][1][1]->Fill(loc_phi(e)/degree, cePX.mass()/GeV/GeV);
	}

	if(pip.pid == 211)
	{
		hH[e_sector_i][0][2]->Fill( epX.mass()/GeV/GeV);
		hH[e_sector_i][1][2]->Fill(cepX.mass()/GeV/GeV);
		hH[6][0][2]->Fill( epX.mass()/GeV/GeV);
		hH[6][1][2]->Fill(cepX.mass()/GeV/GeV);

		hHt[e_sector_i][0][2]->Fill(e.theta()/degree,  epX.mass()/GeV/GeV);
		hHt[e_sector_i][1][2]->Fill(e.theta()/degree, cepX.mass()/GeV/GeV);
		hHt[6][0][2]->Fill(e.theta()/degree,  epX.mass()/GeV/GeV);
		hHt[6][1][2]->Fill(e.theta()/degree, cepX.mass()/GeV/GeV);

		hHp[e_sector_i][0][2]->Fill(loc_phi(e)/degree,  epX.mass()/GeV/GeV);
		hHp[e_sector_i][1][2]->Fill(loc_phi(e)/degree, cepX.mass()/GeV/GeV);
		hHp[6][0][2]->Fill(loc_phi(e)/degree,  epX.mass()/GeV/GeV);
		hHp[6][1][2]->Fill(loc_phi(e)/degree, cepX.mass()/GeV/GeV);
	}

	if(pro.pid == 2212 && fabs(sqrt(cH.mass())/GeV-1.6)<.1) // eta in W = 1.5-1.7
	{
		hH[e_sector_i][0][3]->Fill( ePX.mass()/GeV/GeV);
		hH[e_sector_i][1][3]->Fill(cePX.mass()/GeV/GeV);
		hH[6][0][3]->Fill( ePX.mass()/GeV/GeV);
		hH[6][1][3]->Fill(cePX.mass()/GeV/GeV);

		hHt[e_sector_i][0][3]->Fill(e.theta()/degree,  ePX.mass()/GeV/GeV);
		hHt[e_sector_i][1][3]->Fill(e.theta()/degree, cePX.mass()/GeV/GeV);
		hHt[6][0][3]->Fill(e.theta()/degree,  ePX.mass()/GeV/GeV);
		hHt[6][1][3]->Fill(e.theta()/degree, cePX.mass()/GeV/GeV);

		hHp[e_sector_i][0][3]->Fill(loc_phi(e)/degree,  ePX.mass()/GeV/GeV);
		hHp[e_sector_i][1][3]->Fill(loc_phi(e)/degree, cePX.mass()/GeV/GeV);
		hHp[6][0][3]->Fill(loc_phi(e)/degree,  ePX.mass()/GeV/GeV);
		hHp[6][1][3]->Fill(loc_phi(e)/degree, cePX.mass()/GeV/GeV);
	}


}
