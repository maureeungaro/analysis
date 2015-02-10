#include "TFile.h"

#include "rad_histos.h"

#include <iostream>
using namespace std;

void rad_histos::define_histos()
{
	bins Bin;
	cout << endl << " Defining histos..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			pht_rad_cor[w][q] = new TH2D(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),
												           Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]),  Bin.CTBIN, -1, 1, Bin.PHBIN, 0, 360);

	cout << "done." << endl << endl;
}


void rad_histos::write_histos(string filename)
{
	bins Bin;
	cout << " Writing histos to " << filename << "...";
	TFile OUT(filename.c_str(),"RECREATE");
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
			pht_rad_cor[w][q]->Write();
	cout << "done. "  << endl;
}

void rad_histos::init_histos(string filename)
{
	bins Bin;
	cout << " Initializing histos from " << filename << "...";
	TFile IN(filename.c_str());
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			pht_rad_cor[w][q] = (TH2D*)IN.Get(Form("W_%4.3f_Q2_%4.3f",  Bin.wm_center[w], Bin.q2_center[q]));
 			pht_rad_cor[w][q]->SetDirectory(0);
		}
	cout << "done. " << endl << endl;
	IN.Close();
}


void rad_histos::slice_histos()
{
	bins Bin;
	cout << " Slicing histos in theta and phi..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phi_rad_cor[w][q][c] = pht_rad_cor[w][q]->ProjectionY(Form("W_%4.3f_Q2_%4.3f_th_%4.3f", Bin.wm_center[w], Bin.q2_center[q], Bin.ct_center[c]), c+1, c+1);
				phi_rad_cor[w][q][c]->SetDirectory(0);
			}

			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				the_rad_cor[w][q][p] = pht_rad_cor[w][q]->ProjectionX(Form("W_%4.3f_Q2_%4.3f_ph_%4.3f", Bin.wm_center[w], Bin.q2_center[q], Bin.ph_center[p]), p+1, p+1);
				the_rad_cor[w][q][p]->SetDirectory(0);
			}
		}
	cout << "done. " << endl << endl;
}



void rad_histos::style_histos(int m)
{
	Color_t mcols[6] = {kGreen+1, kOrange+7, kBlue+1, kMagenta, kRed+1, kBlack};
	int     msytl[6] = {       1,         2,       3,        4,      1,      1};
	bins Bin;
	cout << " Styling histos..." ;
	for(unsigned int w=0; w<Bin.WMBIN; w++)
		for(unsigned int q=0; q<Bin.Q2BIN; q++)
		{
			double max = find_max_phi(w, q);
			for(unsigned int c=0; c<Bin.CTBIN; c++)
			{
				phi_rad_cor[w][q][c]->SetLineColor(mcols[m]);
				phi_rad_cor[w][q][c]->SetLineStyle(msytl[m]);
				phi_rad_cor[w][q][c]->SetLineWidth(2);
				phi_rad_cor[w][q][c]->GetXaxis()->SetNdivisions(508);
				phi_rad_cor[w][q][c]->GetYaxis()->SetNdivisions(805);
				phi_rad_cor[w][q][c]->GetXaxis()->SetLabelSize(0.14);
				phi_rad_cor[w][q][c]->GetYaxis()->SetLabelSize(0.14);
				phi_rad_cor[w][q][c]->GetXaxis()->SetLabelOffset(0.03);
				phi_rad_cor[w][q][c]->GetYaxis()->SetLabelOffset(0.04);
				phi_rad_cor[w][q][c]->SetMaximum(max);
				phi_rad_cor[w][q][c]->SetMinimum(0.6);
			}
			
			max = find_max_the(w, q);
			for(unsigned int p=0; p<Bin.PHBIN; p++)
			{
				the_rad_cor[w][q][p]->SetLineColor(mcols[m]);
				the_rad_cor[w][q][p]->SetLineStyle(msytl[m]);
				the_rad_cor[w][q][p]->SetLineWidth(2);
				the_rad_cor[w][q][p]->GetXaxis()->SetNdivisions(508);
				the_rad_cor[w][q][p]->GetYaxis()->SetNdivisions(805);
				the_rad_cor[w][q][p]->GetXaxis()->SetLabelSize(0.14);
				the_rad_cor[w][q][p]->GetYaxis()->SetLabelSize(0.14);
				the_rad_cor[w][q][p]->GetXaxis()->SetLabelOffset(0.03);
				the_rad_cor[w][q][p]->GetYaxis()->SetLabelOffset(0.04);
				the_rad_cor[w][q][p]->SetMaximum(max);
				the_rad_cor[w][q][p]->SetMinimum(0.6);
			}
		}
		cout << "done. " << endl << endl;
}




double rad_histos::find_max_phi(int w, int q)
{
	bins Bin;
	
	double max = 0;
	for(unsigned int i=0; i<Bin.CTBIN; i++)
	{
		if(phi_rad_cor[w][q][i]->GetMaximum() > max)
			max = phi_rad_cor[w][q][i]->GetMaximum();
	}
	return max*1.1;
	
}

double rad_histos::find_max_the(int w, int q)
{
	bins Bin;
	
	double max = 0;
	for(unsigned int i=0; i<Bin.PHBIN; i++)
	{
		if(the_rad_cor[w][q][i]->GetMaximum() > max)
			max = the_rad_cor[w][q][i]->GetMaximum();
	}
	return max*1.1;
	
}








