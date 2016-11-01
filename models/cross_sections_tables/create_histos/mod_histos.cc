// %%%%%%%%%%%%%
// ROOT includes
// %%%%%%%%%%%%%
#include "mod_histos.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <cmath>
using namespace std;


mod_histos::mod_histos(string mod)
{
	model = mod;

	col  = kBlack;
	lsty = 1;

	if(model == "dmt2001")
	{
		col  = kGreen+1;
		lsty = 1;
	}
	if(model == "maid2002")
	{
		col  = kOrange+7;
		lsty = 2;
	}
	if(model == "maid2003")
	{
		col  = kOrange+7;
		lsty = 5;
	}
	if(model == "maid2003woroper")
	{
		col  = kMagenta;
		lsty = 7;
	}
	if(model == "maid2007")
	{
		col  = kRed+1;
		lsty = 1;
	}
	if(model == "said2008")
	{
		col  =  kGreen+2;
		lsty = 1;
	}

	phifit  = new TF1("phifit", "[0] + [1]*cos(x*0.017453288889) + [2]*cos(2*x*0.017453288889)", 0, 360);
	phifit->SetLineWidth(1);
	phifit->SetLineColor(col);
}

void mod_histos::define_histos(string filename)
{
	bins Bin;
	if(filename=="")
	{
		cout << endl << " Defining histos for " << model <<  "...";
		for(unsigned int w=0; w<Bin.WMBIN; w++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
				pht_model[w][q] = new TH2D(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),
				                           Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),
																	 Bin.CTBIN, -1, 1, Bin.PHBIN, 0, 360);
	}
	else
	{
		TFile f(filename.c_str());
		cout << endl << " Loading histos for " << model <<  " from " << filename << "...";
		for(unsigned int w=0; w<Bin.WMBIN; w++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
			{
				pht_model[w][q] = (TH2D*) f.Get(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]));
				pht_model[w][q]->SetDirectory(0);
			}
	}

	cout << "done." << endl;
}

void mod_histos::write_histos(string filename)
{
	bins Bin;
	cout << " Writing histos to " << filename << " for " << model <<  "...";
	TFile OUT(filename.c_str(),"RECREATE");
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			pht_model[w][q]->Write();
		}
	cout << "done. " << endl;
}

void mod_histos::slice_histos()
{
	bins Bin;
	cout << " Slicing histos in theta and phi for " << model <<  "...";

	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phi_model[w][q][c] = pht_model[w][q]->ProjectionY(Form("W_%4.3f_Q2_%4.3f_th_%4.3f",
																															 Bin.wm_center[w], Bin.q2_center[q], Bin.ct_center[c]), c+1, c+1);
				phi_model[w][q][c]->SetLineColor(col);
				phi_model[w][q][c]->SetLineStyle(lsty);
				phi_model[w][q][c]->SetLineWidth(2);
				phi_model[w][q][c]->GetXaxis()->SetLabelSize(0.14);
				phi_model[w][q][c]->GetYaxis()->SetLabelSize(0.14);
				phi_model[w][q][c]->GetXaxis()->SetLabelOffset(0.03);
				phi_model[w][q][c]->GetYaxis()->SetLabelOffset(0.04);
				phi_model[w][q][c]->GetXaxis()->SetNdivisions(508);
				phi_model[w][q][c]->GetYaxis()->SetNdivisions(805);
				phi_model[w][q][c]->SetMinimum(0.0);
				phi_model[w][q][c]->SetDirectory(0);
				
			}

			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				the_model[w][q][p] = pht_model[w][q]->ProjectionX(Form("W_%4.3f_Q2_%4.3f_ph_%4.3f",
																															 Bin.wm_center[w], Bin.q2_center[q], Bin.ph_center[p]), p+1, p+1);
				the_model[w][q][p]->SetLineColor(col);
				the_model[w][q][p]->SetLineStyle(lsty);
				the_model[w][q][p]->SetLineWidth(2);
				the_model[w][q][p]->GetXaxis()->SetLabelSize(0.14);
				the_model[w][q][p]->GetYaxis()->SetLabelSize(0.14);
				the_model[w][q][p]->GetXaxis()->SetLabelOffset(0.03);
				the_model[w][q][p]->GetYaxis()->SetLabelOffset(0.04);
				the_model[w][q][p]->GetXaxis()->SetNdivisions(508);
				the_model[w][q][p]->GetYaxis()->SetNdivisions(805);
				the_model[w][q][p]->SetMinimum(0.0);
				the_model[w][q][p]->SetDirectory(0);
			}
		}
	cout << "done. " << endl ;
}


void mod_histos::fill_WQ2_histos()
{
	bins Bin;
	cout << " Filling W, Q2 cross sections distributions for " << model <<  "...";
	
	for(unsigned int c=0; c<Bin.CTBIN; c++)
		for(unsigned int p=0; p<Bin.PHBIN; p++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
			{
				pi0_cs_W_model[q][c][p] = new TH1D(Form("pi0_cs_W_%s_Q2_%4.3f_th_%3.2f_ph_%3.2f", model.c_str(), Bin.q2_center[q], Bin.ct_center[c], Bin.ph_center[p]),
																					 Form("pi0_cs_W_%s_Q2_%4.3f_th_%3.2f_ph_%3.2f", model.c_str(), Bin.q2_center[q], Bin.ct_center[c], Bin.ph_center[p]),
																					 Bin.WMBIN, 1.1, 2.0);
																					 
				for(unsigned int w=0; w<Bin.WMBIN; w++)
				{
					pi0_cs_W_model[q][c][p]->SetBinContent(w+1, pht_model[w][q]->GetBinContent(c+1, p+1));
					pi0_cs_W_model[q][c][p]->SetBinError(  w+1, 0);
				}
				pi0_cs_W_model[q][c][p]->SetLineColor(col);
				pi0_cs_W_model[q][c][p]->SetLineStyle(lsty);
				pi0_cs_W_model[q][c][p]->SetLineWidth(2);
				pi0_cs_W_model[q][c][p]->GetXaxis()->SetLabelSize(0.14);
				pi0_cs_W_model[q][c][p]->GetYaxis()->SetLabelSize(0.14);
				pi0_cs_W_model[q][c][p]->GetXaxis()->SetLabelOffset(0.03);
				pi0_cs_W_model[q][c][p]->GetYaxis()->SetLabelOffset(0.04);
				pi0_cs_W_model[q][c][p]->GetXaxis()->SetNdivisions(508);
				pi0_cs_W_model[q][c][p]->GetYaxis()->SetNdivisions(805);
				pi0_cs_W_model[q][c][p]->SetDirectory(0);

			}

	cout << "done. " << endl ;

}


void mod_histos::fit_phis()
{
	bins Bin;
	string which[3] = {"LPT", "TT", "LT"};
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(int s=0; s<3; s++)
			{
				pi0_sf_model[w][q][s] = new TH1D(Form("pi0_sigma_%s_%s_W_%4.3f_Q2_%4.3f", which[s].c_str(), model.c_str(), Bin.wm_center[w], Bin.q2_center[q]),
																				 Form("pi0_sigma_%s_%s_W_%4.3f_Q2_%4.3f", which[s].c_str(), model.c_str(), Bin.wm_center[w], Bin.q2_center[q]),
																				 Bin.CTBIN, -1, 1);
			}

	double BEAM    = 5.7542 ;        // beam energy in GeV
	double MP      = 0.93827231;     // Proton mass GeV/c2
	double mp      = 0.1349764;      // pi0 mass GeV/c2

	// can't put Bin.WMBIN because cint doesn't allow
	// non-static-const in array dimensions
	const int WMBIN = Bin.WMBIN;
	const int Q2BIN = Bin.Q2BIN;
	
	double ep[WMBIN][Q2BIN] ;        // Scattered electron energy
	double nu[WMBIN][Q2BIN];         // Energy loss. This is also q0, time component of four vector E-E'
	double Q[WMBIN][Q2BIN];          // Virtual photon 3-momentum
	double Qcm[WMBIN][Q2BIN];        // Virtual photon 3-momentum in CM
	double x[WMBIN][Q2BIN];          // pi0 CM momentum
	double k[WMBIN][Q2BIN];          // Photon equivalent energy
	double kcm[WMBIN][Q2BIN];        // Photon equivalent energy in CM
	double theta[WMBIN][Q2BIN];      // angle of scattered electron
	double epst[WMBIN][Q2BIN];       // Transverse polarization of virtual photon
	double epsl[WMBIN][Q2BIN];       // Longitudinal polarization of virtual photon
	double kl[WMBIN][Q2BIN];         // kcm[ww][qq] / x[ww][qq];

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

	double aa, bb, cc;        // a,b,c phi fit coefficients
	double Slpt,  Stt,  Slt;  // structure functions
	double sint, sin2t;       // Sin theta* and its square

	cout << " Fitting phi distributions for " << model <<  "...";

	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phifit->SetParameters(0, 0, 0);
				sint  = sin(acos(Bin.ct_center[c]));
				sin2t = pow(sint, 2);

				aa = bb = cc = 0;

				if(phi_model[w][q][c]->GetEntries()>0)
				{
					phi_model[w][q][c]->Fit("phifit", "0QEM");
					phifit->SetParameters(phifit->GetParameter(0), phifit->GetParameter(1), phifit->GetParameter(2));
					phi_model[w][q][c]->Fit("phifit",  "0QEM+");
					
					aa = phifit->GetParameter(0) *kl[w][q];
					bb = phifit->GetParameter(1) *kl[w][q];
					cc = phifit->GetParameter(2) *kl[w][q];
				}
				
				Slpt  = aa ;
				Stt   = cc / ( sin2t*epst[w][q]) ;
				Slt   = bb / ( sint*sqrt( 2*epsl[w][q]*(epst[w][q]+1) ) ) ;
				
				pi0_sf_model[w][q][0]->SetBinContent(c+1, Slpt);
				pi0_sf_model[w][q][1]->SetBinContent(c+1, Stt);
				pi0_sf_model[w][q][2]->SetBinContent(c+1, Slt);
				pi0_sf_model[w][q][0]->SetBinError(  c+1, 0);
				pi0_sf_model[w][q][1]->SetBinError(  c+1, 0);
				pi0_sf_model[w][q][2]->SetBinError(  c+1, 0);

				for(int s=0; s<3; s++)
				{
					pi0_sf_model[w][q][s]->SetMarkerSize(0.2);
					pi0_sf_model[w][q][s]->SetMarkerColor(col);
					pi0_sf_model[w][q][s]->SetLineColor(col);
					pi0_sf_model[w][q][s]->SetLineStyle(lsty);
					pi0_sf_model[w][q][s]->SetLineWidth(2);
					pi0_sf_model[w][q][s]->GetXaxis()->SetNdivisions(508);
					pi0_sf_model[w][q][s]->GetYaxis()->SetNdivisions(805);
					pi0_sf_model[w][q][s]->GetXaxis()->SetLabelSize(0.14);
					pi0_sf_model[w][q][s]->GetYaxis()->SetLabelSize(0.14);
					pi0_sf_model[w][q][s]->GetXaxis()->SetLabelOffset(0.03);
					pi0_sf_model[w][q][s]->GetYaxis()->SetLabelOffset(0.04);
					pi0_sf_model[w][q][s]->SetDirectory(0);
					
				}
			}
	cout << "done. " << endl ;
}



void mod_histos::fill_WQ2_sfhistos()
{
	bins Bin;
	string which[3] = {"LPT", "TT", "LT"};
	cout << " Filling W, Q2 structure functions distributions for " << model <<  "...";
	
	for(int s=0; s<3; s++)
		for(unsigned int c=0; c<Bin.CTBIN; c++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
			{
				pi0_sf_W_model[q][c][s] = new TH1D(Form("pi0_sigma_%s_%s_W_Q2_%4.3f_th_%3.2f", which[s].c_str(), model.c_str(), Bin.q2_center[q], Bin.ct_center[c]),
																					 Form("pi0_sigma_%s_%s_W_Q2_%4.3f_th_%3.2f", which[s].c_str(), model.c_str(), Bin.q2_center[q], Bin.ct_center[c]),
																								 Bin.WMBIN, 1.1, 2.0);
				for(unsigned int w=0; w<Bin.WMBIN; w++)
				{
					pi0_sf_W_model[q][c][s]->SetBinContent(w+1, pi0_sf_model[w][q][s]->GetBinContent(c+1));
					pi0_sf_W_model[q][c][s]->SetBinError(  w+1, pi0_sf_model[w][q][s]->GetBinError(c+1));
					pi0_sf_W_model[q][c][s]->SetLineColor(col);
					pi0_sf_W_model[q][c][s]->SetLineStyle(lsty);
					pi0_sf_W_model[q][c][s]->SetLineWidth(2);
					pi0_sf_W_model[q][c][s]->GetXaxis()->SetNdivisions(508);
					pi0_sf_W_model[q][c][s]->GetYaxis()->SetNdivisions(805);
					pi0_sf_W_model[q][c][s]->GetXaxis()->SetLabelSize(0.14);
					pi0_sf_W_model[q][c][s]->GetYaxis()->SetLabelSize(0.14);
					pi0_sf_W_model[q][c][s]->GetXaxis()->SetLabelOffset(0.03);
					pi0_sf_W_model[q][c][s]->GetYaxis()->SetLabelOffset(0.04);
					pi0_sf_W_model[q][c][s]->SetDirectory(0);
				}
			}

	cout << "done. " << endl ;
	
}

































