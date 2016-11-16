// MU includes
#include "common_info.h"
#include "bin.h"
#include "utilities.h"

// C++ includes
#include <fstream>
#include <cstdlib>
#include <cmath>

// construct histos based on yields 
ana_chistos::ana_chistos(TH2D *pi0[45][7][3])
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};

	min_acceptance = 0.005;

	phifit  = new TF1("phifit", "[0] + [1]*cos(x*0.017453288889) + [2]*cos(2*x*0.017453288889)", 0, 360);
	phifit->SetLineWidth(1);
	phifit->SetLineColor(kBlue+3);

	
	for(unsigned int q=0; q<Bin[0]->Q2BIN; q++) {
		chi2s_ctr[q] = new TH1D(Form("chi2_phifit_Q2%4.3f", Bin[0]->q2_center[q]),
										Form("chi2_phifit_Q2%4.3f", Bin[0]->q2_center[q]), 40, 0.0, 4.0);
		chi2s_ctr[q]->SetDirectory(0);
	}
	
	for(unsigned int w=0; w<Bin[0]->WMBIN; w++)
		for(unsigned int q=0; q<Bin[0]->Q2BIN; q++)
		{
			for(int b=0; b<3; b++)
			{
				// yields
				pi0_l1[w][q][b] = (TH2D*) pi0[w][q][b]->Clone(Form("pi0_l1_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
				// divided by acceptance - it still has 24 bins (that's why pi0[w][q][0])
				pi0_l2[w][q][b] = (TH2D*) pi0[w][q][0]->Clone(Form("pi0_l2_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
			}
			pi0_l3[w][q] = (TH2D*) pi0[w][q][0]->Clone(Form("pi0_l3_W_%4.3f_Q2_%4.3f",  Bin[0]->wm_center[w], Bin[0]->q2_center[q])); // divided by radiative correction
			pi0_cs[w][q] = (TH2D*) pi0[w][q][0]->Clone(Form("pi0_cs_W_%4.3f_Q2_%4.3f",  Bin[0]->wm_center[w], Bin[0]->q2_center[q])); // divided by bin correction
			
			if(w==25 && q==2)
				cout << " Integral Measured Yields for W=" << Bin[0]->wm_center[25] << ", Q2=" << Bin[0]->q2_center[2]
				     << "  pi0: " <<  pi0_l1[w][q][0]->GetEntries() << endl;
		}
}

// divide histos by acceptance 
void ana_chistos::divide_by_acc_cor(TH2D *pi0[45][7][3])
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);

	for(unsigned int w=0; w<Bin[0]->WMBIN; w++)
		for(unsigned int q=0; q<Bin[0]->Q2BIN; q++)
		{
			pi0_l2[w][q][0]->Divide(pi0_l1[w][q][0], pi0[w][q][0], 1, 1);
			if(w==25 && q==2)
				cout << " Integral Acc Corr Yields for W=" << Bin[0]->wm_center[25] << ", Q2=" << Bin[0]->q2_center[2]
				     << "  pi0: " <<  pi0_l2[w][q][0]->Integral() <<  endl;

			// now rebinning the 48 version
			for(unsigned int c=0; c<Bin[1]->CTBIN; c++)
				for(unsigned int p=0; p<Bin[1]->PHBIN/2; p++)
				{
				
					double data1 = pi0_l1[w][q][1]->GetBinContent(c+1, 2*p+1);
					double data2 = pi0_l1[w][q][1]->GetBinContent(c+1, 2*p+2);
					double acc1  = pi0[w][q][1]->GetBinContent(c+1, 2*p+1);
					double acc2  = pi0[w][q][1]->GetBinContent(c+1, 2*p+2);
					double eacc1 = pi0[w][q][1]->GetBinError(c+1, 2*p+1);
					double eacc2 = pi0[w][q][1]->GetBinError(c+1, 2*p+2);

					
					pi0_l2[w][q][1]->SetBinContent(c+1, p+1, value_rebin(data1, data2, acc1, acc2));
					pi0_l2[w][q][1]->SetBinError(c+1, p+1,   error_rebin(data1, data2, sqrt(data1), sqrt(data2), acc1, acc2, eacc1, eacc2));
				}
				
			// now rebinning the 96 version
			for(unsigned int c=0; c<Bin[2]->CTBIN; c++)
				for(unsigned int p=0; p<Bin[2]->PHBIN/4; p++)
				{
					// rebin first 2 bins
					double data1_1 = pi0_l1[w][q][2]->GetBinContent(c+1, 4*p+1);
					double data1_2 = pi0_l1[w][q][2]->GetBinContent(c+1, 4*p+2);
					double acc1_1  = pi0[w][q][2]->GetBinContent(c+1, 4*p+1);
					double acc1_2  = pi0[w][q][2]->GetBinContent(c+1, 4*p+2);
					double eacc1_1 = pi0[w][q][2]->GetBinError(c+1, 4*p+1);
					double eacc1_2 = pi0[w][q][2]->GetBinError(c+1, 4*p+2);
					double data1   = value_rebin(data1_1, data1_2, acc1_1, acc1_2);
					double edata1  = error_rebin(data1_1, data1_2, sqrt(data1_1), sqrt(data1_2), acc1_1, acc1_2, eacc1_1, eacc1_2);

					// rebin bins 3 and 4
					double data2_1 = pi0_l1[w][q][2]->GetBinContent(c+1, 4*p+3);
					double data2_2 = pi0_l1[w][q][2]->GetBinContent(c+1, 4*p+4);
					double acc2_1  = pi0[w][q][2]->GetBinContent(c+1, 4*p+3);
					double acc2_2  = pi0[w][q][2]->GetBinContent(c+1, 4*p+4);
					double eacc2_1 = pi0[w][q][2]->GetBinError(c+1, 4*p+3);
					double eacc2_2 = pi0[w][q][2]->GetBinError(c+1, 4*p+4);
					double data2   = value_rebin(data2_1, data2_2, acc2_1, acc2_2);
					double edata2  = error_rebin(data2_1, data2_2, sqrt(data2_1), sqrt(data2_2), acc2_1, acc2_2, eacc2_1, eacc2_2);

					
					
// 					if(w==10 && q == 1 && c==0)
// 						cout << p << " " << data1_1 << " " << data1_2 << " " << acc1_1 << " " << acc1_2 << " " << data1 << " " << acc1 << endl;

					// need to renormalize data1 and data2 (otherwise I'm dividing by acceptance twice)
					pi0_l2[w][q][2]->SetBinContent(c+1, p+1, value_srebin(data1, data2));
					pi0_l2[w][q][2]->SetBinError(  c+1, p+1, error_srebin(edata1, edata2));
				}
				

			// now chosing the smallest error value between all the binning.
			double error;
			for(unsigned int c=0; c<Bin[0]->CTBIN; c++)
				for(unsigned int p=0; p<Bin[0]->PHBIN; p++)
				{
					error = 1000000;
					for(int b=0; b<3; b++)
						if(pi0_l2[w][q][b]->GetBinError(c+1, p+1) < error)
							error = pi0_l2[w][q][b]->GetBinError(c+1, p+1);

					for(int b=0; b<3; b++)
						pi0_l2[w][q][b]->SetBinError(c+1, p+1, error);
				}
					
		}
}

// divide histos by radiative correction 
void ana_chistos::divide_by_rad_cor(TH2D *pi0[45][7], int which)
{
	bins Bin;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			// the systematic error should be saved somewhere
			for(unsigned int c=0; c<Bin.CTBIN; c++)
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					pi0[w][q]->SetBinError(c+1, p+1, 0);
				}
		
			pi0_l3[w][q]->Divide(pi0_l2[w][q][which], pi0[w][q], 1, 1);
			if(w==25 && q==2)
				cout << " Integral Rad Corr Yields for W=" << Bin.wm_center[25] << ", Q2=" << Bin.q2_center[2]
				     << "  pi0: " <<  pi0_l3[w][q]->Integral() << endl;
		}
}

// divide histos by bin correction - and sanity check on the error
void ana_chistos::multiply_by_bin_cor(TH2D *pi0[45][7])
{
	bins Bin;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			// the systematic error should be saved somewhere
			for(unsigned int c=0; c<Bin.CTBIN; c++)
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					pi0[w][q]->SetBinError(c+1, p+1, 0);
				}
				
				pi0_cs[w][q]->Multiply(pi0_l3[w][q], pi0[w][q], 1, 1);
			if(w==25 && q==2)
				cout << " Integral Bin Corr Yields for W=" << Bin.wm_center[25] << ", Q2=" << Bin.q2_center[2]
				<< "  pi0: " <<  pi0_cs[w][q]->Integral() << endl;
		}
}


void ana_chistos::quality_check(TH2D *pi0[45][7][3])
{
	bins Bin;
	cout << " Quality check: setting bins with acceptance < " << min_acceptance << " to -1 with 0 error" << endl;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			for(unsigned int c=0; c<Bin.CTBIN; c++)
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					if(pi0[w][q][0]->GetBinContent(c+1, p+1) < min_acceptance)
					{
						pi0_cs[w][q]->SetBinContent(c+1, p+1, -1.0);
						pi0_cs[w][q]->SetBinError(c+1, p+1, 0.0);
					}
				}
}


void ana_chistos::write(string filename)
{
	bins Bin;
	TFile output(filename.c_str(), "RECREATE");
	cout << endl << " Writing ROOT file " << filename << "..." ;

	// cross sections, structure functions
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			pi0_cs[w][q]->Write();
			for(int b=0; b<3; b++) {
				pi0_l1[w][q][b]->Write();
				pi0_l2[w][q][b]->Write();
			}

			for(unsigned int c=0; c<Bin.CTBIN; c++)
				pi0_cs_phi[w][q][c]->Write();

			for(int s=0; s<3; s++)
				pi0_sf[w][q][s]->Write();
		}

	for(unsigned int q=0; q<Bin.Q2BIN; q++) {
		chi2s_ctr[q]->Write();
	}


	cout << "done. " << endl ;
	output.Close();
}


void ana_chistos::slice_and_style(int also)
{
	bins Bin;
	Color_t colors = kBlue+1;
	// slicing the histos
	cout << " Slicing histos in theta and phi..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			for(unsigned int c=0; c<Bin.CTBIN && also; c++)
			{
				pi0_cs_phi[w][q][c] = pi0_cs[w][q]->ProjectionY(Form("pi0_cs_phi_W_%4.3f_Q2_%4.3f_th_%4.3f",
																				Bin.wm_center[w], Bin.q2_center[q], Bin.ct_center[c]), c+1, c+1);
				pi0_cs_phi[w][q][c]->SetDirectory(0);
			}
			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				pi0_cs_the[w][q][p] = pi0_cs[w][q]->ProjectionX(Form("pi0_cs_the_W_%4.3f_Q2_%4.3f_ph_%4.3f",
																						Bin.wm_center[w], Bin.q2_center[q], Bin.ph_center[p]), p+1, p+1);
				pi0_cs_the[w][q][p]->SetDirectory(0);
			}
		}
		
		bins *BinA[3];
		BinA[0] = new bins(45, 10, 24);
		BinA[1] = new bins(45, 10, 48);
		BinA[2] = new bins(45, 10, 96);
		string bindex[3] = {"b24", "b48", "b96"};
		
		// corrected yields, if requested
		if(also != 0)
		{
			for(int b=0; b<3; b++)
				for(unsigned int w=0; w<BinA[b]->WMBIN; w++)
					for(unsigned int q=0; q<BinA[b]->Q2BIN; q++)
					{
						for(unsigned int c=0; c<BinA[b]->CTBIN; c++)
						{
							pi0_l2_phi[w][q][c][b] = pi0_l2[w][q][b]->ProjectionY(Form("pi0_l2_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f",
																			      bindex[b].c_str(), BinA[b]->wm_center[w], BinA[b]->q2_center[q], BinA[b]->ct_center[c]), c+1, c+1);
							pi0_l2_phi[w][q][c][b]->SetDirectory(0);
						}
					}
				
		}
			
		// Style and Maxs
		cout << " Setting Style and Maximums..." ;
		for(unsigned int w=0; w<Bin.WMBIN; w++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
			{
				double tmax = find_max_the(w, q, 0);
				double pmax = find_max_phi(w, q, 0);
				
				for(unsigned int c=0; c<Bin.CTBIN; c++)
				{
					pi0_cs_phi[w][q][c]->SetMarkerStyle(21);
					pi0_cs_phi[w][q][c]->SetMarkerSize(0.65);
					pi0_cs_phi[w][q][c]->SetMarkerColor(colors);
					pi0_cs_phi[w][q][c]->SetLineColor(colors);
					pi0_cs_phi[w][q][c]->SetLineWidth(2);
					pi0_cs_phi[w][q][c]->GetXaxis()->SetNdivisions(508);
					pi0_cs_phi[w][q][c]->GetYaxis()->SetNdivisions(805);
					pi0_cs_phi[w][q][c]->SetMinimum(0.0);
					pi0_cs_phi[w][q][c]->SetMaximum(pmax);
					pi0_cs_phi[w][q][c]->GetXaxis()->SetLabelSize(0.14);
					pi0_cs_phi[w][q][c]->GetYaxis()->SetLabelSize(0.14);
					pi0_cs_phi[w][q][c]->GetXaxis()->SetLabelOffset(0.03);
					pi0_cs_phi[w][q][c]->GetYaxis()->SetLabelOffset(0.04);
				}
				for(unsigned int p=0; p<Bin.PHBIN; p++)
				{
					pi0_cs_the[w][q][p]->SetMarkerStyle(21);
					pi0_cs_the[w][q][p]->SetMarkerSize(0.65);
					pi0_cs_the[w][q][p]->SetMarkerColor(colors);
					pi0_cs_the[w][q][p]->SetLineColor(colors);
					pi0_cs_the[w][q][p]->SetLineWidth(2);
					pi0_cs_the[w][q][p]->GetXaxis()->SetNdivisions(508);
					pi0_cs_the[w][q][p]->GetYaxis()->SetNdivisions(805);
					pi0_cs_the[w][q][p]->SetMinimum(0.0);
					pi0_cs_the[w][q][p]->SetMaximum(tmax);
					pi0_cs_the[w][q][p]->GetXaxis()->SetLabelSize(0.14);
					pi0_cs_the[w][q][p]->GetYaxis()->SetLabelSize(0.14);
					pi0_cs_the[w][q][p]->GetXaxis()->SetLabelOffset(0.03);
					pi0_cs_the[w][q][p]->GetYaxis()->SetLabelOffset(0.04);
					
				}
			}

		// corrected yields, if requested
		if(also != 0)
		{
			Color_t cols[3] = {kBlack, kRed+1, kBlue+2};
			
			for(int b=0; b<3; b++)
				for(unsigned int w=0; w<BinA[b]->WMBIN; w++)
					for(unsigned int q=0; q<BinA[b]->Q2BIN; q++)
					{
						// double pmax = find_max_phi(w, q, 0);
						
						for(unsigned int c=0; c<BinA[b]->CTBIN; c++)
						{
							pi0_l2_phi[w][q][c][b]->SetMarkerStyle(21);
							pi0_l2_phi[w][q][c][b]->SetMarkerSize(0.65);
							pi0_l2_phi[w][q][c][b]->SetMarkerColor(cols[b]);
							pi0_l2_phi[w][q][c][b]->SetLineColor(cols[b]);
							pi0_l2_phi[w][q][c][b]->SetLineWidth(2);
							pi0_l2_phi[w][q][c][b]->GetXaxis()->SetNdivisions(508);
							pi0_l2_phi[w][q][c][b]->GetYaxis()->SetNdivisions(805);
							pi0_l2_phi[w][q][c][b]->SetMinimum(0.0);
// 							pi0_l2_phi[w][q][c][b]->SetMaximum(pmax);
							pi0_l2_phi[w][q][c][b]->GetXaxis()->SetLabelSize(0.14);
							pi0_l2_phi[w][q][c][b]->GetYaxis()->SetLabelSize(0.14);
							pi0_l2_phi[w][q][c][b]->GetXaxis()->SetLabelOffset(0.03);
							pi0_l2_phi[w][q][c][b]->GetYaxis()->SetLabelOffset(0.04);
						}
					}

		}
	cout << " done. " << endl ;
}


double ana_chistos::find_max_the(int w, int q, int which)
{
	bins Bin;
	double max = 0.0001;
	if(which == 0)  // pi0 cs distributions
		for(unsigned int i=0; i<Bin.PHBIN; i++)
		{
			if(pi0_cs_the[w][q][i]->GetMaximum() > max)
				max = pi0_cs_the[w][q][i]->GetMaximum();
		}
	if(which == 10) // pi0 LPT distributions
		for(unsigned int i=0; i<Bin.CTBIN; i++)
		{
			if(pi0_sf[w][q][0]->GetMaximum() > max)
				max = pi0_sf[w][q][0]->GetMaximum();
		}
	if(which == 11) // pi0 TT distributions
		for(unsigned int i=0; i<Bin.CTBIN; i++)
		{
			if(pi0_sf[w][q][1]->GetMaximum() > max)
				max = pi0_sf[w][q][1]->GetMaximum();
		}
	if(which == 12) // pi0 LT distributions
		for(unsigned int i=0; i<Bin.CTBIN; i++)
		{
			if(pi0_sf[w][q][2]->GetMaximum() > max)
				max = pi0_sf[w][q][2]->GetMaximum();
		}
		
	return max*1.1;
}

double ana_chistos::find_max_phi(int w, int q, int which)
{
	bins Bin;
	double max = 0;
	if(which == 0)
		for(unsigned int i=0; i<Bin.CTBIN; i++)
		{
			if(pi0_cs_phi[w][q][i]->GetMaximum() > max)
				max = pi0_cs_phi[w][q][i]->GetMaximum();
		}
	return max*1.1;
}


#include <cmath>
void ana_chistos::normalize()
{
	bins Bin;
	
	double FARADAY = 0.01992;        // charge in coulomb.
	double BEAM    = 5.7542 ;        // beam energy in GeV
	double MP      = 0.93827231;     // Proton mass GeV/c2
	double mp      = 0.1349764;      // pi0 mass GeV/c2
	double PI      = 3.141592653589;
	
	double ne;                       // Number of electrons hitting the target
	double np;                       // Density of target -------- nuclei/cm^2
	double qe    = 1.602177E-19;     // Electron charge ---------- Coulomb;
	double rho   = 0.0708 ;          // Density of H2 at 20K ----- g/cm3
	double A0    = 6.0221367E23;     // Avogado number ----------- mol^-1
	double MH    = 1.00794;          // Atomic mass of hydrogen -- amu = g/mol
	double LT    = 5.0;              // Lenght of target --------- cm
	double CMB   = 1E30;             // cm^2 to microbarn -------- mcbarn/cm^2
	
	np           = LT*rho*A0/MH;     // number of target nuclei per cm2
	ne           = FARADAY/qe;       // Number of electron hitting the target
	
	double scale[Bin.Q2BIN];         
	double norma[Bin.Q2BIN];         // Normalization factors NUMBERS -> microBARN

	double dphi     = 2*PI/Bin.PHBIN;       // delta phi (radians)

	double alpha = 1/137.035989;
	double ep[Bin.WMBIN][Bin.Q2BIN] ;        // Scattered electron energy
	double nu[Bin.WMBIN][Bin.Q2BIN];         // Energy loss. This is also q0, time component of four vector E-E'
	double Q[Bin.WMBIN][Bin.Q2BIN];          // Virtual photon 3-momentum
	double Qcm[Bin.WMBIN][Bin.Q2BIN];        // Virtual photon 3-momentum in CM
	double x[Bin.WMBIN][Bin.Q2BIN];          // pi0 CM momentum
	double k[Bin.WMBIN][Bin.Q2BIN];          // Photon equivalent energy
	double kcm[Bin.WMBIN][Bin.Q2BIN];        // Photon equivalent energy in CM
	double theta[Bin.WMBIN][Bin.Q2BIN];      // angle of scattered electron
//	double epst[Bin.WMBIN][Bin.Q2BIN];       // Transverse polarization of virtual photon
//	double epsl[Bin.WMBIN][Bin.Q2BIN];       // Longitudinal polarization of virtual photon
	double GFLUXTP[Bin.WMBIN][Bin.Q2BIN];    // photon flux (as function of theta and integrated over phi)
	double GFLUXWQ[Bin.WMBIN][Bin.Q2BIN];    // photon flux as a function of W,Q2 (the above multiplied by the jacobian)
	double J[Bin.WMBIN][Bin.Q2BIN];          // Jacobian fron E,Omega to W,Q2
	

	for(unsigned int q=0; q<Bin.Q2BIN; q++) {
		scale[q] = ne*np*Bin.dwm[0]*Bin.dq2[q]*Bin.dct[0]*dphi/CMB;
		norma[q] = 1.0/(2*PI*scale[q]);
	}

	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++) {
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
			
			GFLUXTP[w][q] = (alpha/(2*PI*PI))*(ep[w][q]/BEAM)*(k[w][q]/Bin.q2_center[q])/(1-epst[w][q]);
			J[w][q]       = Bin.wm_center[w]/(2*BEAM*ep[w][q]*MP);
			GFLUXWQ[w][q] = GFLUXTP[w][q]*J[w][q];
			

/*			cout << " W: "       << Bin.wm_center[w]   << "  Q2: "      << Bin.q2_center[q];
			cout << " theta: "   << theta[w][q]*180/3.141592653589     << "  nu: "      << nu[w][q];
			cout << " epst: "    << epst[w][q]         << "  epsl: "    << epsl[w][q];
			cout << " GFLUXTP: " << GFLUXTP[w][q]      << "  GFLUXWQ: " << GFLUXWQ[w][q];
			cout << " JACO: "    << J[w][q]            << "  x: "       << x[w][q]/kcm[w][q];
			cout << " norma: "   << norma[q] << endl;*/
			
				pi0_cs[w][q]->Scale(norma[q]/GFLUXWQ[w][q]);
		}
}



// read histos file
ana_chistos::ana_chistos(string filename, int bin)
{
	string which[3] = {"LPT", "TT", "LT"};

	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};

	TFile f(filename.c_str());
	cout << " Loading histos from: " << filename << endl;
	for(unsigned int w=0; w<Bin[bin]->WMBIN; w++)
		for(unsigned int q=0; q<Bin[bin]->Q2BIN; q++)
		{
			if(w==0) cout << " Q2: " << Bin[bin]->q2_center[q] << endl;

			// cross sections
			pi0_cs[w][q] = (TH2D*) f.Get(Form("pi0_cs_W_%4.3f_Q2_%4.3f", Bin[bin]->wm_center[w], Bin[bin]->q2_center[q]));
			if(pi0_cs[w][q])
				pi0_cs[w][q]->SetDirectory(0);

			// as a function of phi
			for(unsigned int c=0; c<Bin[bin]->CTBIN; c++) {
				pi0_cs_phi[w][q][c] = (TH1D*) f.Get(Form("pi0_cs_phi_W_%4.3f_Q2_%4.3f_th_%4.3f",
																 Bin[bin]->wm_center[w], Bin[bin]->q2_center[q], Bin[bin]->ct_center[c]));

				pi0_cs_phi[w][q][c]->SetDirectory(0);
			}

			// corrected yields
			for(int b=0; b<3; b++) {
				pi0_l1[w][q][b] = (TH2D*) f.Get(Form("pi0_l1_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
				pi0_l2[w][q][b] = (TH2D*) f.Get(Form("pi0_l2_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
				if(pi0_l1[w][q])
					pi0_l1[w][q][b]->SetDirectory(0);
				if(pi0_l2[w][q])
					pi0_l2[w][q][b]->SetDirectory(0);
			}

			// structure functions
			for(int s=0; s<3; s++){
				pi0_sf[w][q][s] = (TH1D*) f.Get(Form("pi0_sigma_%s_W_%4.3f_Q2_%4.3f", which[s].c_str(), Bin[bin]->wm_center[w], Bin[bin]->q2_center[q]));
				if(pi0_sf[w][q][s])
					pi0_sf[w][q][s]->SetDirectory(0);
			}
		}

	for(unsigned int q=0; q<Bin[0]->Q2BIN; q++) {
		chi2s_ctr[q] = (TH1D*) f.Get(Form("chi2_phifit_Q2%4.3f", Bin[0]->q2_center[q]));
		chi2s_ctr[q]->SetDirectory(0);
	}


	cout << " done. " << endl ;
}

void ana_chistos::fill_WQ2_histos()
{
	bins Bin;
	cout << " Filling W, Q2 cross sections distributions..." ;

	for(unsigned int c=0; c<Bin.CTBIN; c++)
		for(unsigned int p=0; p<Bin.PHBIN; p++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++){
				pi0_cs_W[q][c][p] = new TH1D(Form("pi0_cs_W_Q2_%4.3f_th_%3.2f_ph_%3.2f",  Bin.q2_center[q], Bin.ct_center[c], Bin.ph_center[p]),
													  Form("pi0_cs_W_Q2_%4.3f_th_%3.2f_ph_%3.2f",  Bin.q2_center[q], Bin.ct_center[c], Bin.ph_center[p]),
													 Bin.WMBIN, 1.1, 2.0);
																		 
				for(unsigned int w=0; w<Bin.WMBIN; w++){
					pi0_cs_W[q][c][p]->SetBinContent(w+1, pi0_cs_the[w][q][p]->GetBinContent(c+1));
					pi0_cs_W[q][c][p]->SetBinError(  w+1, pi0_cs_the[w][q][p]->GetBinError(c+1));
				}

				pi0_cs_W[q][c][p]->SetMarkerStyle(21);
				pi0_cs_W[q][c][p]->SetMarkerSize(0.65);
				pi0_cs_W[q][c][p]->SetMarkerColor(kBlue+3);
				pi0_cs_W[q][c][p]->SetLineColor(kBlue+3);
				pi0_cs_W[q][c][p]->SetLineWidth(2);
				pi0_cs_W[q][c][p]->GetXaxis()->SetNdivisions(508);
				pi0_cs_W[q][c][p]->GetYaxis()->SetNdivisions(805);
				pi0_cs_W[q][c][p]->SetMinimum(0.0);
				pi0_cs_W[q][c][p]->GetXaxis()->SetLabelSize(0.14);
				pi0_cs_W[q][c][p]->GetYaxis()->SetLabelSize(0.14);
				pi0_cs_W[q][c][p]->GetXaxis()->SetLabelOffset(0.03);
				pi0_cs_W[q][c][p]->GetYaxis()->SetLabelOffset(0.04);
				pi0_cs_W[q][c][p]->SetDirectory(0);

			}

	cout << " done. " << endl ;
}


void ana_chistos::fill_WQ2_sfhistos()
{
	bins Bin;

	cout << " Filling W, Q2 structure functions distributions..." ;
	string which[3] = {"LPT", "TT", "LT"};
	
	for(int s=0; s<3; s++)
		for(unsigned int c=0; c<Bin.CTBIN; c++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++) {
				pi0_sf_W[q][c][s] = new TH1D(Form("pi0_sigma_%s_W_Q2_%4.3f_th_%3.2f", which[s].c_str(), Bin.q2_center[q], Bin.ct_center[c] ),
													  Form("pi0_sigma_%s_W_Q2_%4.3f_th_%3.2f", which[s].c_str(), Bin.q2_center[q], Bin.ct_center[c] ), Bin.WMBIN, 1.1, 2.0);
																 
				for(unsigned int w=0; w<Bin.WMBIN; w++) {
					pi0_sf_W[q][c][s]->SetBinContent(w+1, pi0_sf[w][q][s]->GetBinContent(c+1));
					pi0_sf_W[q][c][s]->SetBinError(  w+1, pi0_sf[w][q][s]->GetBinError(c+1));
				}
				
				pi0_sf_W[q][c][s]->SetMarkerStyle(21);
				pi0_sf_W[q][c][s]->SetMarkerSize(0.65);
				pi0_sf_W[q][c][s]->SetMarkerColor(kBlue+3);
				pi0_sf_W[q][c][s]->SetLineColor(kBlue+3);
				pi0_sf_W[q][c][s]->SetLineWidth(2);
				pi0_sf_W[q][c][s]->GetXaxis()->SetNdivisions(508);
				pi0_sf_W[q][c][s]->GetYaxis()->SetNdivisions(805);
				pi0_sf_W[q][c][s]->SetMinimum(0.0);
				pi0_sf_W[q][c][s]->GetXaxis()->SetLabelSize(0.14);
				pi0_sf_W[q][c][s]->GetYaxis()->SetLabelSize(0.14);
				pi0_sf_W[q][c][s]->GetXaxis()->SetLabelOffset(0.03);
				pi0_sf_W[q][c][s]->GetYaxis()->SetLabelOffset(0.04);
				pi0_sf_W[q][c][s]->SetDirectory(0);
				
		}
		
		cout << " done. " << endl ;
}

void ana_chistos::write_sf_table()
{
	// sid=1,2,3 for sig(T+L) sigTT sigLT
	int sid[3] = {1, 2, 3};
	
	bins Bin;

	ofstream ot("sf_tables.dat");
		
	for(int s=0; s<3; s++)
		for(unsigned int c=0; c<Bin.CTBIN; c++)
			for(unsigned int q=0; q<Bin.Q2BIN; q++)
				for(unsigned int w=0; w<Bin.WMBIN; w++) {
					ot << 5.7542 << " " << Bin.q2_center[q] << " " << Bin.wm_center[w] << " " << epsl[w][q] << " " << Bin.ct_center[c] << " " 
					   << pi0_sf[w][q][s]->GetBinContent(c+1) << " " << pi0_sf[w][q][s]->GetBinError(c+1) << " " 
						 << 0 << " " 
						 << sid[s] << " " 
						 << 1 << endl;
				}
}







