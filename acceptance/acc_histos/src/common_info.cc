// MU includes
#include "common_info.h"
#include "utilities.h"
#include "bin.h"

// C++ includes
#include <fstream>
#include <cstdlib>

// Histograms
acc_chistos::acc_chistos(string filename, int READ, int OACC)
{
	// Default: filename is output file
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};
	
	if(READ == 0)
	{
		output = NULL;
		if(filename!= "none") 
		{
			output = new TFile(filename.c_str(), "RECREATE");
			cout << " Opening ROOT file " << filename << " for writing..." << endl;
		}

	for(int b=0; b<3; b++)
		for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
			for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
			{
				pi0_gen[w][q][b] = new TH2D(Form("pi0_gen_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																		Form("pi0_gen_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																		Bin[b]->CTBIN, -1, 1, Bin[b]->PHBIN, 0, 360);
				pi0_rec[w][q][b] = new TH2D(Form("pi0_rec_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																		Form("pi0_rec_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]),
																		Bin[b]->CTBIN, -1, 1, Bin[b]->PHBIN, 0, 360);
			}
	}
	// Reading from Input file
	else
	{
		// loading gen/rec histos
		if(filename!= "none" && OACC==-1) 
		{
			TFile f(filename.c_str());
			cout << " Loading gen/rec acceptance histos from: " << filename << "...";
			for(int b=0; b<3; b++)
				for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
					for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
					{
						pi0_gen[w][q][b] = (TH2D*) f.Get(Form("pi0_gen_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
						pi0_rec[w][q][b] = (TH2D*) f.Get(Form("pi0_rec_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
						if(pi0_gen[w][q][b])
						{
							pi0_gen[w][q][b]->Sumw2();
							pi0_gen[w][q][b]->SetDirectory(0);
						}
						if(pi0_rec[w][q][b])
						{
							pi0_rec[w][q][b]->Sumw2();
							pi0_rec[w][q][b]->SetDirectory(0);
						}
					}
					cout << " done. " << endl ;
		}
		
		// loading histos from a particular bin
		else if(filename!= "none" && OACC>-1)
		{
			TFile f(filename.c_str());
			cout << " Loading " << bindex[OACC] << " acceptance histos from: " << filename << "...";
				for(unsigned int w=0; w<Bin[OACC]->WMBIN; w++)
					for(unsigned int q=0; q<Bin[OACC]->Q2BIN; q++)
					{
						pi0_acc[w][q][OACC] = (TH2D*) f.Get(Form("pi0_acc_%s_W_%4.3f_Q2_%4.3f", bindex[OACC].c_str(), Bin[OACC]->wm_center[w], Bin[OACC]->q2_center[q]));
						if(pi0_acc[w][q][OACC])
						{
							pi0_acc[w][q][OACC]->Sumw2();
							pi0_acc[w][q][OACC]->SetDirectory(0);
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

void acc_chistos::write_and_close()
{
	if(output)
	{
		cout << endl << " Writing ROOT file...  "  << endl;
		output->Write();
		output->Close();
	}
}


void acc_chistos::calc_acc()
{
	// Default: filename is output file
	cout << " Calculating acceptance histos...";
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};

	// dividing the histos.
	for(int b=0; b<3; b++)
		for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
			for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
			{
				pi0_acc[w][q][b] = (TH2D*) pi0_gen[w][q][b]->Clone();
				pi0_acc[w][q][b]->SetName(Form("pi0_acc_%s_W_%4.3f_Q2_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q]));
				pi0_acc[w][q][b]->Divide(pi0_rec[w][q][b], pi0_gen[w][q][b], 1, 1);
				pi0_acc[w][q][b]->SetDirectory(0);
			}
	cout << " done. " << endl ;
}

void acc_chistos::slice(int OACC)
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	string bindex[3] = {"b24", "b48", "b96"};

	if(OACC==-1)
	{
		cout << " Slicing all histos in theta and phi..." ;
		for(int b=0; b<3; b++)
			for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
				for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
				{
					for(unsigned int c=0; c<Bin[b]->CTBIN; c++)
					{
						pi0_phi[w][q][c][0][b] = pi0_gen[w][q][b]->ProjectionY(Form("pi0_gen_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ct_center[c]), c+1, c+1);
						pi0_phi[w][q][c][1][b] = pi0_rec[w][q][b]->ProjectionY(Form("pi0_rec_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ct_center[c]), c+1, c+1);
						pi0_phi[w][q][c][2][b] = pi0_acc[w][q][b]->ProjectionY(Form("pi0_acc_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f", bindex[b].c_str(), Bin[b]->wm_center[w], Bin[b]->q2_center[q], Bin[b]->ct_center[c]), c+1, c+1);
						pi0_phi[w][q][c][0][b]->SetDirectory(0);
						pi0_phi[w][q][c][1][b]->SetDirectory(0);
						pi0_phi[w][q][c][2][b]->SetDirectory(0);
					}
				}
		cout << " done. " << endl ;
	}
	else
	{
		cout << " Slicing " << bindex[OACC] << " histos in theta and phi..." ;
		for(unsigned int w=0; w<Bin[OACC]->WMBIN; w++)
			for(unsigned int q=0; q<Bin[OACC]->Q2BIN; q++)
				{
					for(unsigned int c=0; c<Bin[OACC]->CTBIN; c++)
					{
						pi0_phi[w][q][c][2][OACC] = pi0_acc[w][q][OACC]->ProjectionY(Form("pi0_acc_phi_%s_W_%4.3f_Q2_%4.3f_th_%4.3f",
																																							bindex[OACC].c_str(), Bin[OACC]->wm_center[w], Bin[OACC]->q2_center[q], Bin[OACC]->ct_center[c]), c+1, c+1);
						pi0_phi[w][q][c][2][OACC]->SetDirectory(0);
					}
				}
		cout << " done. " << endl ;	
	}
	
}



void acc_chistos::style(int OACC)
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	
	// Style and Maxs
	Color_t colors[3] = {kBlack, kRed+1, kBlue+2};
	
	cout << " Setting Style and maximums..." ;

	if(OACC==-1)
	{
		for(int b=0; b<3; b++)
			for(unsigned int w=0; w<Bin[b]->WMBIN; w++)
				for(unsigned int q=0; q<Bin[b]->Q2BIN; q++)
				{
					// maxs calculation is outsize the angular loop
					double pmax[3];
					for(int ww=0; ww<3; ww++)
					{
						pmax[ww] = find_max_phi(w, q, b, ww);
					}
					for(unsigned int c=0; c<Bin[b]->CTBIN; c++)
						for(int ww=0; ww<3; ww++)
						{
							pi0_phi[w][q][c][ww][b]->SetMarkerStyle(21);
							pi0_phi[w][q][c][ww][b]->SetMarkerSize(0.45);
							pi0_phi[w][q][c][ww][b]->SetMarkerColor(colors[ww]);
							pi0_phi[w][q][c][ww][b]->SetLineColor(colors[ww]);
							pi0_phi[w][q][c][ww][b]->SetLineWidth(2);
							if(ww==2)
							{
								pi0_phi[w][q][c][ww][b]->SetMarkerColor(colors[b]);
								pi0_phi[w][q][c][ww][b]->SetLineColor(colors[b]);
							}
							pi0_phi[w][q][c][ww][b]->GetXaxis()->SetNdivisions(508);
							pi0_phi[w][q][c][ww][b]->GetYaxis()->SetNdivisions(805);
							pi0_phi[w][q][c][ww][b]->GetXaxis()->SetLabelSize(0.14);
							pi0_phi[w][q][c][ww][b]->GetYaxis()->SetLabelSize(0.14);
							pi0_phi[w][q][c][ww][b]->GetXaxis()->SetLabelOffset(0.03);
							pi0_phi[w][q][c][ww][b]->GetYaxis()->SetLabelOffset(0.04);
							pi0_phi[w][q][c][ww][b]->SetMinimum(0.0);
							pi0_phi[w][q][c][ww][b]->SetMaximum(pmax[ww]);
						}
				}
	}
	else
	{
		for(unsigned int w=0; w<Bin[OACC]->WMBIN; w++)
			for(unsigned int q=0; q<Bin[OACC]->Q2BIN; q++)
			{
				for(unsigned int c=0; c<Bin[OACC]->CTBIN; c++)
					{
						pi0_phi[w][q][c][2][OACC]->SetMarkerStyle(21);
						pi0_phi[w][q][c][2][OACC]->SetMarkerSize(0.65);
						pi0_phi[w][q][c][2][OACC]->SetMarkerColor(colors[OACC]);
						pi0_phi[w][q][c][2][OACC]->SetLineColor(colors[OACC]);
						pi0_phi[w][q][c][2][OACC]->SetLineWidth(2);
						pi0_phi[w][q][c][2][OACC]->GetXaxis()->SetNdivisions(508);
						pi0_phi[w][q][c][2][OACC]->GetYaxis()->SetNdivisions(805);
						pi0_phi[w][q][c][2][OACC]->GetXaxis()->SetLabelSize(0.14);
						pi0_phi[w][q][c][2][OACC]->GetYaxis()->SetLabelSize(0.14);
						pi0_phi[w][q][c][2][OACC]->GetXaxis()->SetLabelOffset(0.03);
						pi0_phi[w][q][c][2][OACC]->GetYaxis()->SetLabelOffset(0.04);
						pi0_phi[w][q][c][2][OACC]->SetMinimum(0.0);
					}
			}
	}
	cout << "done. " << endl;
}


double acc_chistos::find_max_phi(int w, int q, int b, int which)
{
	bins *Bin[3];
	Bin[0] = new bins(45, 10, 24);
	Bin[1] = new bins(45, 10, 48);
	Bin[2] = new bins(45, 10, 96);
	
	double max = 0;
	for(unsigned int i=0; i<Bin[b]->CTBIN; i++)
	{
		if(pi0_phi[w][q][i][which][b]->GetMaximum() > max)
			max = pi0_phi[w][q][i][which][b]->GetMaximum();
	}
	return max*1.1;
}












