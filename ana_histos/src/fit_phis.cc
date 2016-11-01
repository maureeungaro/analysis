// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "common_info.h"
#include "bin.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <fstream>
#include <cstdlib>
#include <cmath>

// fit phi distributions of cross sections and models
void ana_chistos::fit_phis()
{
	bins Bin;
	string which[3] = {"LPT", "TT", "LT"};
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(int s=0; s<3; s++)
			{
				pi0_sf[w][q][s] = new TH1D(Form("pi0_sigma_%s_W_%4.3f_Q2_%4.3f", which[s].c_str(), Bin.wm_center[w], Bin.q2_center[q]),
																	 Form("pi0_sigma_%s_W_%4.3f_Q2_%4.3f", which[s].c_str(), Bin.wm_center[w], Bin.q2_center[q]), Bin.CTBIN, -1, 1);
			}
	
	double BEAM    = 5.7542 ;        // beam energy in GeV
	double MP      = 0.93827231;     // Proton mass GeV/c2
	double mp      = 0.1349764;      // pi0 mass GeV/c2

	double ep[Bin.WMBIN][Bin.Q2BIN] ;        // Scattered electron energy
	double nu[Bin.WMBIN][Bin.Q2BIN];         // Energy loss. This is also q0, time component of four vector E-E'
	double Q[Bin.WMBIN][Bin.Q2BIN];          // Virtual photon 3-momentum
	double Qcm[Bin.WMBIN][Bin.Q2BIN];        // Virtual photon 3-momentum in CM
	double x[Bin.WMBIN][Bin.Q2BIN];          // pi0 CM momentum
	double k[Bin.WMBIN][Bin.Q2BIN];          // Photon equivalent energy
	double kcm[Bin.WMBIN][Bin.Q2BIN];        // Photon equivalent energy in CM
	double theta[Bin.WMBIN][Bin.Q2BIN];      // angle of scattered electron
	double epst[Bin.WMBIN][Bin.Q2BIN];       // Transverse polarization of virtual photon
	double epsl[Bin.WMBIN][Bin.Q2BIN];       // Longitudinal polarization of virtual photon
	double kl[Bin.WMBIN][Bin.Q2BIN];         // kcm[ww][qq] / x[ww][qq];
	
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			nu[w][q]      = ( Bin.wm_center[w]*Bin.wm_center[w] + Bin.q2_center[q]  - MP*MP ) / ( 2.0*MP );
			ep[w][q]      = BEAM - nu[w][q];
			theta[w][q]   = acos( 1.0 - Bin.q2_center[q] / ( 2*BEAM*ep[w][q] ) );
			Q[w][q]       = sqrt( Bin.q2_center[q] +  nu[w][q]*nu[w][q] );
			Qcm[w][q]     = MP*Q[w][q]/Bin.wm_center[w];
			x[w][q]       = sqrt( pow( (Bin.wm_center[w]*Bin.wm_center[w] + mp*mp - MP*MP )/(2*Bin.wm_center[w]), 2) - mp*mp );
			
			k[w][q]       = ( Bin.wm_center[w]*Bin.wm_center[w] - MP*MP ) / (2*MP);
			kcm[w][q]     = MP*k[w][q]/Bin.wm_center[w];

			epst[w][q]    = 1.0 / (1 + ( 2*Q[w][q]*Q[w][q]*pow(tan(theta[w][q]/2.0),2)/Bin.q2_center[q] ) );
			epsl[w][q]    = Bin.q2_center[q]*epst[w][q]/pow(Qcm[w][q],2);
			kl[w][q]      = kcm[w][q] / x[w][q];  // common factor!
			
		}

	double aa, bb, cc;
	double ea, eb, ec;
	
	double   Slpt,  Stt,  Slt;
	double  eSlpt, eStt, eSlt;
	
	double sint, sin2t;            // Sin theta* and its square

	cout << " Fitting phi distributions...";
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phifit->SetParameters(0, 0, 0);
				if(pi0_cs_phi[w][q][c]->GetEntries()>1)
				{
					pi0_cs_phi[w][q][c]->Fit("phifit", "0QEM");
					phifit->SetParameters(phifit->GetParameter(0), phifit->GetParameter(1), phifit->GetParameter(2));
					pi0_cs_phi[w][q][c]->Fit("phifit",  "QEM+");
				}


				chi2s_ctr[q]->Fill(phifit->GetChisquare()/21);

				sint  = sin(acos(Bin.ct_center[c]));
				sin2t = pow(sint, 2);
				
				aa = phifit->GetParameter(0) *kl[w][q];
				bb = phifit->GetParameter(1) *kl[w][q];
				cc = phifit->GetParameter(2) *kl[w][q];
				ea = phifit->GetParError(0)  *kl[w][q];
				eb = phifit->GetParError(1)  *kl[w][q];
				ec = phifit->GetParError(2)  *kl[w][q];
				
				Slpt  = aa ;
				eSlpt = ea ;
				
				Stt   = cc / ( sin2t*epst[w][q]) ;
				eStt  = ec / ( sin2t*epst[w][q]) ;

				Slt   = bb / ( sint*sqrt( 2*epsl[w][q]*(epst[w][q]+1) ) ) ;
				eSlt  = eb / ( sint*sqrt( 2*epsl[w][q]*(epst[w][q]+1) ) ) ;
				
				pi0_sf[w][q][0]->SetBinContent(c+1, Slpt);
				pi0_sf[w][q][1]->SetBinContent(c+1, Stt);
				pi0_sf[w][q][2]->SetBinContent(c+1, Slt);
				pi0_sf[w][q][0]->SetBinError(  c+1, eSlpt);
				pi0_sf[w][q][1]->SetBinError(  c+1, eStt);
				pi0_sf[w][q][2]->SetBinError(  c+1, eSlt);


				for(int s=0; s<3; s++)
				{
					pi0_sf[w][q][s]->SetMarkerStyle(21);
					pi0_sf[w][q][s]->SetMarkerSize(0.65);
					pi0_sf[w][q][s]->SetMarkerColor(kBlue+1);
					pi0_sf[w][q][s]->SetLineColor(kBlue+1);
					pi0_sf[w][q][s]->SetLineWidth(2);
					pi0_sf[w][q][s]->GetXaxis()->SetNdivisions(508);
					pi0_sf[w][q][s]->GetYaxis()->SetNdivisions(805);
					pi0_sf[w][q][s]->SetMaximum(find_max_the(w, q, s));
					pi0_sf[w][q][s]->GetXaxis()->SetLabelSize(0.14);
					pi0_sf[w][q][s]->GetYaxis()->SetLabelSize(0.14);
					pi0_sf[w][q][s]->GetXaxis()->SetLabelOffset(0.03);
					pi0_sf[w][q][s]->GetYaxis()->SetLabelOffset(0.04);
				}
				
			}
	cout << " done." << endl;

}



















