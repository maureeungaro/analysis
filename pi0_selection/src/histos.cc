// MU includes
#include "histos.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

// Kinematics:
// b + T -> e + P + X
// q = b - e
// H = q + T = P + X

void histos::fill(V4 e, V4 P, CLAS_Event_opts Opts, map<string, int> passed)
{
	const int NWBINS  = 18;
	double dw = (2.0 - 1.1)/NWBINS;

	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));

	V4 b(0, 0, beam_e, beam_e);       // Incident Electron Four momentum
	V4 T(0, 0,      0, target_mass);  // Target Mass

	V4 q = b - e;  // virtual photon 4-vector
	V4 H = q + T;  // Outgoing Hadrons 4-vector
	V4 X = H - P;  // e P missing particle
	// don't consider W > 2 or mm < 0.1
	if(X.mass()/GeV/GeV > 1 || sqrt(H.mass())/GeV > 2.0)
		return;
	
	double dth1v = atan(1/(tan(e.theta()/2.)*( 1 + b.t/proton_mass)))/degree - P.theta()/degree;
	double dth2v = atan(1/(tan(e.theta()/2.)*(1+(proton_mass*e.t/(proton_mass-e.t+e.t*cos(e.theta()))/proton_mass))))/degree - P.theta()/degree;
	double dphiv = ( e.phi() - P.phi() )/degree;

	//double ct    = cos(X.theta()/rad);
	
	// check on calculation of dphi
	double aaa   = X.phi()/degree;
	
	cout << aaa - dphiv << endl;
	
  if(dphiv <  0) dphiv = dphiv + 360;



	// No cuts
	W[0]->Fill(     sqrt(H.mass())/GeV);
	Q2[0]->Fill(        -q.mass()/GeV/GeV);
	epXmm2[0]->Fill(     X.mass()/GeV/GeV);
	epXmm2_W[0]->Fill(    sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
	Q2_W[0]->Fill(        sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
	
	for(int w=0; w<NWBINS; w++)
	{
		double Wmin = 1.1 + dw*w;
		double Wmax = 1.1 + dw*w + dw;
		if(sqrt(H.mass())/GeV >= Wmin && sqrt(H.mass())/GeV < Wmax)
		{
			epXmm2s[0][w]->Fill(X.mass()/GeV/GeV);
			dth1[0][w]->Fill(dth1v);
			dth2[0][w]->Fill(dth2v);
			dphi[0][w]->Fill(dphiv);
			dth1z[0][w]->Fill(dth1v);
			dth2z[0][w]->Fill(dth2v);
			dphiz[0][w]->Fill(dphiv);
			dth1_epXmm2[0][w]->Fill(X.mass()/GeV/GeV, dth1v);
			dth2_epXmm2[0][w]->Fill(X.mass()/GeV/GeV, dth2v);
			dphi_epXmm2[0][w]->Fill(X.mass()/GeV/GeV, dphiv);
			dth1_epXmm2z[0][w]->Fill(X.mass()/GeV/GeV, dth1v);
			dth2_epXmm2z[0][w]->Fill(X.mass()/GeV/GeV, dth2v);
			dphi_epXmm2z[0][w]->Fill(X.mass()/GeV/GeV, dphiv);
			
			// int it = floor( (ct-0.1)/0.2 );
			
			
		}
	}
	
	// phi cut
	if(passed["PHI"] == 1)
	{
		W[1]->Fill(         sqrt(H.mass())/GeV);
		Q2[1]->Fill(        -q.mass()/GeV/GeV);
		epXmm2[1]->Fill(      X.mass()/GeV/GeV);
		epXmm2_W[1]->Fill(     sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
		Q2_W[1]->Fill(         sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		
		for(int w=0; w<NWBINS; w++)
		{
			double Wmin = 1.1 + dw*w;
			double Wmax = 1.1 + dw*w + dw;
			if(sqrt(H.mass())/GeV >= Wmin && sqrt(H.mass())/GeV < Wmax)
			{
				epXmm2s[1][w]->Fill(X.mass()/GeV/GeV);
				dth1[1][w]->Fill(dth1v);
				dth2[1][w]->Fill(dth2v);
				dphi[1][w]->Fill(dphiv);
				dth1z[1][w]->Fill(dth1v);
				dth2z[1][w]->Fill(dth2v);
				dphiz[1][w]->Fill(dphiv);
				dth1_epXmm2[1][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2[1][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2[1][w]->Fill(X.mass()/GeV/GeV, dphiv);
				dth1_epXmm2z[1][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2z[1][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2z[1][w]->Fill(X.mass()/GeV/GeV, dphiv);
			}
		}
	}
	
	// dth1 cut
	if(passed["DTH1"] == 1)
	{
		W[2]->Fill(         sqrt(H.mass())/GeV);
		Q2[2]->Fill(        -q.mass()/GeV/GeV);
		epXmm2[2]->Fill(      X.mass()/GeV/GeV);
		epXmm2_W[2]->Fill(     sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
		Q2_W[2]->Fill(         sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		
		for(int w=0; w<NWBINS; w++)
		{
			double Wmin = 1.1 + dw*w;
			double Wmax = 1.1 + dw*w + dw;
			if(sqrt(H.mass())/GeV >= Wmin && sqrt(H.mass())/GeV < Wmax)
			{
				epXmm2s[2][w]->Fill(X.mass()/GeV/GeV);
				dth1[2][w]->Fill(dth1v);
				dth2[2][w]->Fill(dth2v);
				dphi[2][w]->Fill(dphiv);
				dth1z[2][w]->Fill(dth1v);
				dth2z[2][w]->Fill(dth2v);
				dphiz[2][w]->Fill(dphiv);
				dth1_epXmm2[2][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2[2][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2[2][w]->Fill(X.mass()/GeV/GeV, dphiv);
				dth1_epXmm2z[2][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2z[2][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2z[2][w]->Fill(X.mass()/GeV/GeV, dphiv);
			}
		}
	}
	
	// dth2 cut
	if(passed["DTH2"] == 1)
	{
		W[3]->Fill(         sqrt(H.mass())/GeV);
		Q2[3]->Fill(        -q.mass()/GeV/GeV);
		epXmm2[3]->Fill(      X.mass()/GeV/GeV);
		epXmm2_W[3]->Fill(     sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
		Q2_W[3]->Fill(         sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		
		for(int w=0; w<NWBINS; w++)
		{
			double Wmin = 1.1 + dw*w;
			double Wmax = 1.1 + dw*w + dw;
			if(sqrt(H.mass())/GeV >= Wmin && sqrt(H.mass())/GeV < Wmax)
			{
				epXmm2s[3][w]->Fill(X.mass()/GeV/GeV);
				dth1[3][w]->Fill(dth1v);
				dth2[3][w]->Fill(dth2v);
				dphi[3][w]->Fill(dphiv);
				dth1z[3][w]->Fill(dth1v);
				dth2z[3][w]->Fill(dth2v);
				dphiz[3][w]->Fill(dphiv);
				dth1_epXmm2[3][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2[3][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2[3][w]->Fill(X.mass()/GeV/GeV, dphiv);
				dth1_epXmm2z[3][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2z[3][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2z[3][w]->Fill(X.mass()/GeV/GeV, dphiv);
			}
		}
	}
	
	// all cut
	if(passed["PASSED"] == 1)
	{
		W[4]->Fill(         sqrt(H.mass())/GeV);
		Q2[4]->Fill(        -q.mass()/GeV/GeV);
		epXmm2[4]->Fill(      X.mass()/GeV/GeV);
		epXmm2_W[4]->Fill(     sqrt(H.mass())/GeV, X.mass()/GeV/GeV);
		Q2_W[4]->Fill(         sqrt(H.mass())/GeV, -q.mass()/GeV/GeV);
		
		for(int w=0; w<NWBINS; w++)
		{
			double Wmin = 1.1 + dw*w;
			double Wmax = 1.1 + dw*w + dw;
			if(sqrt(H.mass())/GeV >= Wmin && sqrt(H.mass())/GeV < Wmax)
			{
				epXmm2s[4][w]->Fill(X.mass()/GeV/GeV);
				dth1[4][w]->Fill(dth1v);
				dth2[4][w]->Fill(dth2v);
				dphi[4][w]->Fill(dphiv);
				dth1z[4][w]->Fill(dth1v);
				dth2z[4][w]->Fill(dth2v);
				dphiz[4][w]->Fill(dphiv);
				dth1_epXmm2[4][w]->Fill( X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2[4][w]->Fill( X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2[4][w]->Fill( X.mass()/GeV/GeV, dphiv);
				dth1_epXmm2z[4][w]->Fill(X.mass()/GeV/GeV, dth1v);
				dth2_epXmm2z[4][w]->Fill(X.mass()/GeV/GeV, dth2v);
				dphi_epXmm2z[4][w]->Fill(X.mass()/GeV/GeV, dphiv);
			}
		}
	}
	
	
}






