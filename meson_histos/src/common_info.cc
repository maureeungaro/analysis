// MU includes
#include "common_info.h"
#include "bin.h"
#include "utilities.h"


// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
meson_chistos::meson_chistos(string filename, int READ)
{
	// Default: filename is output file
	string part[3] = {"all", "pi0", "eta"};
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};

	MEB = 18;
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none")
		{
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}
		for(int p=0; p<3; p++)
		{
			Q2_W[p]      =  new TH2F(Form("Q2_W_%s",    part[p].c_str()),
															 Form("Q2_W_%s",    part[p].c_str()), 440, 1.1+p*0.3, 2.0+p*0.3, 300, 1.0, 7.0);
			W_epXmm2[p]  =  new TH2F(Form("W_epXmm2%s", part[p].c_str()),
															 Form("W_epXmm2%s", part[p].c_str()), 300, -0.02, 1.0, 440, 1.1+p*0.3, 2.0+p*0.3);
															
		}
		
		for(int b=0; b<3; b++)
			for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
				for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
				{
					pi0[w][q][b] = new TH2D(Form("pi0_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																	Form("pi0_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),  Bin[b]->CTBIN, -1, 1, Bin[b]->PHBIN, 0, 360);
					if(w>MEB)
					eta[w][q][b] = new TH2D(Form("eta_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																	Form("eta_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),  Bin[b]->CTBIN, -1, 1, Bin[b]->PHBIN, 0, 360);
				}
			
	}
	// Reading from Input file
	else
	{
		if(filename!= "none")
		{
			TFile f(filename.c_str());
			cout << " Loading histos from: " << filename << endl;
			for(int p=0; p<3; p++)
			{
				Q2_W[p]     =  (TH2F*) f.Get(Form("Q2_W_%s",     part[p].c_str()));
				W_epXmm2[p] =  (TH2F*) f.Get(Form("W_epXmm2%s",  part[p].c_str()));
				if(Q2_W[p])     Q2_W[p]->SetDirectory(0);
				if(W_epXmm2[p]) W_epXmm2[p]->SetDirectory(0);
			}
			for(int b=0; b<3; b++)
				for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
					for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
					{
						pi0[w][q][b] = (TH2D*) f.Get(Form("pi0_%s_W_%4.3f_Q2_%4.3f",  bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
						if(w>MEB)
						eta[w][q][b] = (TH2D*) f.Get(Form("eta_%s_W_%4.3f_Q2_%4.3f",  bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
						if(pi0[w][q][b])
						{
							pi0[w][q][b]->Sumw2();
							pi0[w][q][b]->SetDirectory(0);
						}
						if(w>MEB && eta[w][q][b])
						{
							eta[w][q][b]->Sumw2();
							eta[w][q][b]->SetDirectory(0);
						}
					}
				cout << " done. " << endl ;
		}
		else
		{
			cout << " No Input File selected. Exiting constructor..." << endl;
			return;
		}
	}
}

void meson_chistos::write_and_close()
{
	if(output)
	{
		cout << endl << " Writing ROOT file...  " << endl;
		output->Write();
		output->Close();
	}
}


void meson_chistos::slice()
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};
	
	// slicing the histos
	cout << " Slicing histos in theta and phi..." ;
	for(int b=0; b<3; b++)
		for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
			for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
			{
				for(unsigned int c=0; c<Bin[b]->CTBIN; c++)
				{
					pi0_phi[w][q][c][b] = pi0[w][q][b]->ProjectionY(Form("pi0_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ct_center[c]), c+1, c+1);
					if(w>MEB)
					eta_phi[w][q][c][b] = eta[w][q][b]->ProjectionY(Form("eta_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ct_center[c]), c+1, c+1);

					pi0_phi[w][q][c][b]->SetDirectory(0);
					if(w>MEB)
					eta_phi[w][q][c][b]->SetDirectory(0);
				}
				for(unsigned int p=0; p<Bin[b]->PHBIN; p++)
				{
					pi0_the[w][q][p][b] = pi0[w][q][b]->ProjectionX(Form("pi0_the_%s_W_%4.3f_Q2_%4.3f_ph_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ph_center[p]), p+1, p+1);
					if(w>MEB)
					eta_the[w][q][p][b] = eta[w][q][b]->ProjectionX(Form("eta_the_%s_W_%4.3f_Q2_%4.3f_ph_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ph_center[p]), p+1, p+1);
					pi0_the[w][q][p][b]->SetDirectory(0);
					if(w>MEB)
					eta_the[w][q][p][b]->SetDirectory(0);
				}
			}
			
	// Style and Maxs
	Color_t colors = kBlue+1;
	Color_t cols[3] = {kBlack, kRed+1, kBlue+2};
	cout << " Setting Style and Maximums..." ;
	for(int b=0; b<3; b++)
		for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
		for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
		{
			
			pi0[w][q][b]->SetMinimum(0.0);
			pi0[w][q][b]->GetXaxis()->SetNdivisions(505);
			pi0[w][q][b]->GetYaxis()->SetNdivisions(505);
			pi0[w][q][b]->GetZaxis()->SetNdivisions(505);
			pi0[w][q][b]->GetXaxis()->SetLabelSize(0.04);
			pi0[w][q][b]->GetYaxis()->SetLabelSize(0.04);
			pi0[w][q][b]->GetZaxis()->SetLabelSize(0.04);
			pi0[w][q][b]->GetXaxis()->SetLabelOffset(0.005);
			pi0[w][q][b]->GetYaxis()->SetLabelOffset(0.01);
			pi0[w][q][b]->GetZaxis()->SetLabelOffset(0.02);
			if(w>MEB)
			{
				eta[w][q][b]->SetMinimum(0.0);
				eta[w][q][b]->GetXaxis()->SetNdivisions(505);
				eta[w][q][b]->GetYaxis()->SetNdivisions(505);
				eta[w][q][b]->GetZaxis()->SetNdivisions(505);
				eta[w][q][b]->GetXaxis()->SetLabelSize(0.04);
				eta[w][q][b]->GetYaxis()->SetLabelSize(0.04);
				eta[w][q][b]->GetZaxis()->SetLabelSize(0.04);
				eta[w][q][b]->GetXaxis()->SetLabelOffset(0.005);
				eta[w][q][b]->GetYaxis()->SetLabelOffset(0.01);
				eta[w][q][b]->GetZaxis()->SetLabelOffset(0.02);
			}
			
			double tmax[2] = {find_max_the(w, q, b, 0), find_max_the(w, q, b, 1)} ;
			double pmax[2] = {find_max_phi(w, q, b, 0), find_max_phi(w, q, b, 1)} ;

			for(unsigned int c=0; c<Bin[b]->CTBIN; c++)
			{
				pi0_phi[w][q][c][b]->SetMarkerStyle(21);
				pi0_phi[w][q][c][b]->SetMarkerSize(0.65);
				pi0_phi[w][q][c][b]->SetMarkerColor(colors);
				pi0_phi[w][q][c][b]->SetLineColor(colors);
				pi0_phi[w][q][c][b]->SetLineWidth(2);
				pi0_phi[w][q][c][b]->GetXaxis()->SetNdivisions(508);
				pi0_phi[w][q][c][b]->GetYaxis()->SetNdivisions(805);
				pi0_phi[w][q][c][b]->SetMinimum(0.0);
				pi0_phi[w][q][c][b]->SetMaximum(pmax[0]);
				pi0_phi[w][q][c][b]->GetXaxis()->SetLabelSize(0.14);
				pi0_phi[w][q][c][b]->GetYaxis()->SetLabelSize(0.14);
				pi0_phi[w][q][c][b]->GetXaxis()->SetLabelOffset(0.03);
				pi0_phi[w][q][c][b]->GetYaxis()->SetLabelOffset(0.04);
				if(w>MEB)
				{
					eta_phi[w][q][c][b]->SetMarkerStyle(21);
					eta_phi[w][q][c][b]->SetMarkerSize(0.65);
					eta_phi[w][q][c][b]->SetMarkerColor(colors);
					eta_phi[w][q][c][b]->SetLineColor(colors);
					eta_phi[w][q][c][b]->SetLineWidth(2);
					eta_phi[w][q][c][b]->GetXaxis()->SetNdivisions(508);
					eta_phi[w][q][c][b]->GetYaxis()->SetNdivisions(805);
					eta_phi[w][q][c][b]->SetMinimum(0.0);
					eta_phi[w][q][c][b]->SetMaximum(pmax[1]);
					eta_phi[w][q][c][b]->GetXaxis()->SetLabelSize(0.14);
					eta_phi[w][q][c][b]->GetYaxis()->SetLabelSize(0.14);
					eta_phi[w][q][c][b]->GetXaxis()->SetLabelOffset(0.03);
					eta_phi[w][q][c][b]->GetYaxis()->SetLabelOffset(0.04);
				}
			}
			for(unsigned int p=0; p<Bin[b]->PHBIN; p++)
			{
				pi0_the[w][q][p][b]->SetMarkerStyle(21);
				pi0_the[w][q][p][b]->SetMarkerSize(0.65);
				pi0_the[w][q][p][b]->SetMarkerColor(cols[b]);
				pi0_the[w][q][p][b]->SetLineColor(cols[b]);
				pi0_the[w][q][p][b]->SetLineWidth(2);
				pi0_the[w][q][p][b]->GetXaxis()->SetNdivisions(508);
				pi0_the[w][q][p][b]->GetYaxis()->SetNdivisions(805);
				pi0_the[w][q][p][b]->SetMinimum(0.0);
				pi0_the[w][q][p][b]->SetMaximum(tmax[0]);
				pi0_the[w][q][p][b]->GetXaxis()->SetLabelSize(0.14);
				pi0_the[w][q][p][b]->GetYaxis()->SetLabelSize(0.14);
				pi0_the[w][q][p][b]->GetXaxis()->SetLabelOffset(0.03);
				pi0_the[w][q][p][b]->GetYaxis()->SetLabelOffset(0.04);
				
				if(w>MEB)
				{
					eta_the[w][q][p][b]->SetMarkerStyle(21);
					eta_the[w][q][p][b]->SetMarkerSize(0.65);
					eta_the[w][q][p][b]->SetMarkerColor(colors);
					eta_the[w][q][p][b]->SetLineColor(colors);
					eta_the[w][q][p][b]->SetLineWidth(2);
					eta_the[w][q][p][b]->GetXaxis()->SetNdivisions(508);
					eta_the[w][q][p][b]->GetYaxis()->SetNdivisions(805);
					eta_the[w][q][p][b]->SetMinimum(0.0);
					eta_the[w][q][p][b]->SetMaximum(tmax[1]);
					eta_the[w][q][p][b]->GetXaxis()->SetLabelSize(0.14);
					eta_the[w][q][p][b]->GetYaxis()->SetLabelSize(0.14);
					eta_the[w][q][p][b]->GetXaxis()->SetLabelOffset(0.03);
					eta_the[w][q][p][b]->GetYaxis()->SetLabelOffset(0.04);
				}
			}
		}
		cout << " done. " << endl ;
}


double meson_chistos::find_max_the(int w, int q, int b, int which)
{
	if(which==1 && w <= (int) MEB)
	{
		return 1;
	}
	
	
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);

	double max = 0;
	if(which == 0)
		for(unsigned int i=0; i<Bin[b]->PHBIN; i++)
		{
			if(pi0_the[w][q][i][b]->GetMaximum() > max)
				max = pi0_the[w][q][i][b]->GetMaximum();
		}
	if(which == 1)
		for(unsigned int i=0; i<Bin[b]->PHBIN; i++)
		{
			if(eta_the[w][q][i][b]->GetMaximum() > max)
				max = eta_the[w][q][i][b]->GetMaximum();
		}
		
	return max*1.1;
}

double meson_chistos::find_max_phi(int w, int q, int b, int which)
{
	if(which==1 && w <= (int) MEB)
	{
		return 1;
	}

	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);

	double max = 0;
	if(which == 0)
		for(unsigned int i=0; i<Bin[b]->CTBIN; i++)
		{
			if(pi0_phi[w][q][i][b]->GetMaximum() > max)
				max = pi0_phi[w][q][i][b]->GetMaximum();
		}
	if(which == 1)
		for(unsigned int i=0; i<Bin[b]->CTBIN; i++)
		{
			if(eta_phi[w][q][i][b]->GetMaximum() > max)
				max = eta_phi[w][q][i][b]->GetMaximum();
		}
	return max*1.1;
}
















