#include "TFile.h"

#include "binc_histos.h"

#include <iostream>
using namespace std;

binc_histos::binc_histos(string mod)
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
	
	
}



void binc_histos::define_histos()
{
	bins Bin;
	cout << endl << " Defining histos..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			pht_binc_cor[w][q] = new TH2D(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),
												            Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),  Bin.CTBIN, -1, 1, Bin.PHBIN, 0, 360);

	cout << "done." << endl << endl;
}


void binc_histos::write_histos(string filename)
{
	bins Bin;
	cout << " Writing histos to " << filename << "...";
	TFile OUT(filename.c_str(),"RECREATE");
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			pht_binc_cor[w][q]->Write();
	cout << "done. "  << endl;
}

void binc_histos::init_histos(string filename)
{
	bins Bin;
	cout << " Initializing histos from " << filename << "...";
	TFile IN(filename.c_str());
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			pht_binc_cor[w][q] = (TH2D*)IN.Get(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]));
 			pht_binc_cor[w][q]->SetDirectory(0);
		}
	cout << "done. " << endl << endl;
	IN.Close();
}


void binc_histos::slice_histos()
{
	bins Bin;
	cout << " Slicing histos in theta and phi..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phi_binc_cor[w][q][c] = pht_binc_cor[w][q]->ProjectionY(Form("W_%4.3f_Q2_%4.3f_th_%4.3f", Bin.wm_center[w], Bin.q2_center[q], Bin.ct_center[c]), c+1, c+1);
				phi_binc_cor[w][q][c]->SetDirectory(0);
			}

			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				the_binc_cor[w][q][p] = pht_binc_cor[w][q]->ProjectionX(Form("W_%4.3f_Q2_%4.3f_ph_%4.3f", Bin.wm_center[w], Bin.q2_center[q], Bin.ph_center[p]), p+1, p+1);
				the_binc_cor[w][q][p]->SetDirectory(0);
			}
		}
	cout << "done. " << endl << endl;
}



void binc_histos::style_histos(int m)
{
	bins Bin;
	cout << " Styling histos..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			double max = find_max_phi(w, q);
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phi_binc_cor[w][q][c]->SetLineColor(col);
				phi_binc_cor[w][q][c]->SetLineStyle(lsty);
				phi_binc_cor[w][q][c]->SetLineWidth(2);
				phi_binc_cor[w][q][c]->SetMarkerColor(col);
				phi_binc_cor[w][q][c]->SetMarkerStyle(21);
				phi_binc_cor[w][q][c]->SetMarkerSize(0.5);
				phi_binc_cor[w][q][c]->GetXaxis()->SetNdivisions(508);
				phi_binc_cor[w][q][c]->GetYaxis()->SetNdivisions(805);
				phi_binc_cor[w][q][c]->GetXaxis()->SetLabelSize(0.14);
				phi_binc_cor[w][q][c]->GetYaxis()->SetLabelSize(0.14);
				phi_binc_cor[w][q][c]->GetXaxis()->SetLabelOffset(0.03);
				phi_binc_cor[w][q][c]->GetYaxis()->SetLabelOffset(0.04);
				phi_binc_cor[w][q][c]->SetMaximum(max);
				phi_binc_cor[w][q][c]->SetMinimum(0.8);
			}
			
			max = find_max_the(w, q);
			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				the_binc_cor[w][q][p]->SetLineColor(col);
				the_binc_cor[w][q][p]->SetLineStyle(lsty);
				the_binc_cor[w][q][p]->SetLineWidth(2);
				the_binc_cor[w][q][p]->SetMarkerColor(col);
				the_binc_cor[w][q][p]->SetMarkerStyle(21);
				the_binc_cor[w][q][p]->SetMarkerSize(0.5);
				the_binc_cor[w][q][p]->GetXaxis()->SetNdivisions(508);
				the_binc_cor[w][q][p]->GetYaxis()->SetNdivisions(805);
				the_binc_cor[w][q][p]->GetXaxis()->SetLabelSize(0.14);
				the_binc_cor[w][q][p]->GetYaxis()->SetLabelSize(0.14);
				the_binc_cor[w][q][p]->GetXaxis()->SetLabelOffset(0.03);
				the_binc_cor[w][q][p]->GetYaxis()->SetLabelOffset(0.04);
				the_binc_cor[w][q][p]->SetMaximum(max);
				the_binc_cor[w][q][p]->SetMinimum(0.8);
			}
		}
		cout << "done. " << endl << endl;
}




double binc_histos::find_max_phi(int w, int q)
{
	bins Bin;
	
	double max = 0;
	for(unsigned int i=0; i<Bin.CTBIN; i++)
	{
		if(phi_binc_cor[w][q][i]->GetMaximum() > max)
			max = phi_binc_cor[w][q][i]->GetMaximum();
	}
	return max*1.1;
	
}

double binc_histos::find_max_the(int w, int q)
{
	bins Bin;
	
	double max = 0;
	for(unsigned int i=0; i<Bin.PHBIN; i++)
	{
		if(the_binc_cor[w][q][i]->GetMaximum() > max)
			max = the_binc_cor[w][q][i]->GetMaximum();
	}
	return max*1.1;
	
}








