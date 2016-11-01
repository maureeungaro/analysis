#include <iostream>
#include <fstream>
#include <cstdlib>

#include "poles.h"


poles::poles(string m)
{
	model = m;
//	double conv = 1;            // Conversion factor from 10^3/mpi+ to sqrt(mubarn) - choose 1 to compare with the table
	double conv = 0.141218;       // Conversion factor from 10^3/mpi+ to sqrt(mubarn)
	complex<double> i(0,1);
	
	cout << " Loading multipoles for " << model << endl;

	string file = "/opt/models/" + m + "-PPpi.tbl";
	char tmp[20];

	ifstream IN(file.c_str());
   if(!IN)
	{
		cout << " File " << file << " could not be opened. Exiting." << endl << endl;
		exit(0);
	}
	double start_w = 1.1;
	double dQ2     = 0.05;
	
	if(m.find("eta") != string::npos)
		start_w = 1.49;

	if(m.find("janr") != string::npos)
		dQ2 = 0.1;
	
	
	
	while(IN)
	{
		int    w, q2;
		double W, Q2;
		double tmpSP[6][2];
		double tmpSM[6][2];
		double tmpEP[6][2];
		double tmpEM[6][2];
		double tmpMP[6][2];
		double tmpMM[6][2];
		IN >> tmp >> W >> tmp >> Q2;
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpSP[l][c];
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpSM[l][c];
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpEP[l][c];
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpEM[l][c];
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpMP[l][c];
		IN >> tmp; for(int l=0; l<6; l++) for(int c=0; c<2; c++) IN >> tmpMM[l][c];
		if(W>=start_w && W<=2.0 && Q2>=0.0 && Q2<=5)
		{
			w  =(int) floor ((W  - start_w + 0.005)/0.01);
			q2 =(int) floor ((Q2 + dQ2/2.0)/dQ2);
			if(Q2 == 0) q2 = 0;
			
			for(int l=0; l<6; l++)
			{
				Sp[l][w][q2] = conv * ( tmpSP[l][0] + tmpSP[l][1]*i );
				Sm[l][w][q2] = conv * ( tmpSM[l][0] + tmpSM[l][1]*i );
				Ep[l][w][q2] = conv * ( tmpEP[l][0] + tmpEP[l][1]*i );
				Em[l][w][q2] = conv * ( tmpEM[l][0] + tmpEM[l][1]*i );
				Mp[l][w][q2] = conv * ( tmpMP[l][0] + tmpMP[l][1]*i );
				Mm[l][w][q2] = conv * ( tmpMM[l][0] + tmpMM[l][1]*i );
			}
		}
	}
}


poles_histos::poles_histos(poles *P)
{
	int nw  = 91;
	int nq2 = 101;
	double start_w = 1.1;
	double max_q2 = 5.05;
	double dQ2     = 0.05;
	string model = P->model;

	if(model.find("eta") != string::npos)
	{
		nw = 51;
		start_w = 1.49;
	}
	if(model.find("janr") != string::npos)
	{
		nq2 = 81;
		dQ2 = 0.1;
		max_q2 = 4.05;
	}
	
	cout << " Defining histos for " << model << "...";
	string part[2] = {"Re", "Im"};
	for(int l=0; l<6; l++)
		for(int p=0; p<2; p++)
		{
			Sp[l][p] = new TH2F(Form("%s_S%d+_%s", model.c_str(), l, part[p].c_str()), Form("%s_S%d+_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);
			Sm[l][p] = new TH2F(Form("%s_S%d-_%s", model.c_str(), l, part[p].c_str()), Form("%s_S%d-_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);

			Ep[l][p] = new TH2F(Form("%s_E%d+_%s", model.c_str(), l, part[p].c_str()), Form("%s_E%d+_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);
			Em[l][p] = new TH2F(Form("%s_E%d-_%s", model.c_str(), l, part[p].c_str()), Form("%s_E%d-_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);

			Mp[l][p] = new TH2F(Form("%s_M%d+_%s", model.c_str(), l, part[p].c_str()), Form("%s_M%d+_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);
			Mm[l][p] = new TH2F(Form("%s_M%d-_%s", model.c_str(), l, part[p].c_str()), Form("%s_M%d-_%s", model.c_str(), l, part[p].c_str()), nw, start_w, 2.01, nq2, 0.0, max_q2);
		}
	cout << "done, now filling histos for " << model << "..." ;


	for(int w=0; w<nw; w++)
		for(int q=0; q<nq2; q++)
			for(int l=0; l<6; l++)
			{
				int bin = Sp[0][0]->GetBin(w+1, q+1);
				Sp[l][0]->SetBinContent(bin,real(P->Sp[l][w][q]));
				Sp[l][1]->SetBinContent(bin,imag(P->Sp[l][w][q]));
				Sm[l][0]->SetBinContent(bin,real(P->Sm[l][w][q]));
				Sm[l][1]->SetBinContent(bin,imag(P->Sm[l][w][q]));
				Ep[l][0]->SetBinContent(bin,real(P->Ep[l][w][q]));
				Ep[l][1]->SetBinContent(bin,imag(P->Ep[l][w][q]));
				Em[l][0]->SetBinContent(bin,real(P->Em[l][w][q]));
				Em[l][1]->SetBinContent(bin,imag(P->Em[l][w][q]));
				Mp[l][0]->SetBinContent(bin,real(P->Mp[l][w][q]));
				Mp[l][1]->SetBinContent(bin,imag(P->Mp[l][w][q]));
				Mm[l][0]->SetBinContent(bin,real(P->Mm[l][w][q]));
				Mm[l][1]->SetBinContent(bin,imag(P->Mm[l][w][q]));
//				if(l==1) cout  << w << " " << q << " " << l << " " << real(P->Sp[l][w][q]) << " " << imag(P->Sp[l][w][q]) << endl;
			}
	
	cout << "done." << endl;

}


#include "TFile.h"
poles_histos::poles_histos(string model, string file)
{
	TFile *f = new TFile(file.c_str());
	
	cout << " Defining histos for " << model << "...";
	string part[2] = {"Re", "Im"};
	for(int l=0; l<6; l++)
		for(int p=0; p<2; p++)
	{
		Sp[l][p] = (TH2F*) f->Get(Form("%s_S%d+_%s", model.c_str(), l, part[p].c_str()));
		Sm[l][p] = (TH2F*) f->Get(Form("%s_S%d-_%s", model.c_str(), l, part[p].c_str()));

		Ep[l][p] = (TH2F*) f->Get(Form("%s_E%d+_%s", model.c_str(), l, part[p].c_str()));
		Em[l][p] = (TH2F*) f->Get(Form("%s_E%d-_%s", model.c_str(), l, part[p].c_str()));

		Mp[l][p] = (TH2F*) f->Get(Form("%s_M%d+_%s", model.c_str(), l, part[p].c_str()));
		Mm[l][p] = (TH2F*) f->Get(Form("%s_M%d-_%s", model.c_str(), l, part[p].c_str()));

		Sp[l][p]->GetXaxis()->SetTitle("W                 [GeV]");
		Sm[l][p]->GetXaxis()->SetTitle("W                 [GeV]");
		Ep[l][p]->GetXaxis()->SetTitle("W                 [GeV]");
		Em[l][p]->GetXaxis()->SetTitle("W                 [GeV]");
		Mp[l][p]->GetXaxis()->SetTitle("W                 [GeV]");
		Mm[l][p]->GetXaxis()->SetTitle("W                 [GeV]");

		Sp[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		Sm[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		Ep[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		Em[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		Mp[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		Mm[l][p]->GetYaxis()->SetTitle("Q^{2}              [GeV^{2}]");
		
		Sp[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");
		Sm[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");
		Ep[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");
		Em[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");
		Mp[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");
		Mm[l][p]->GetZaxis()->SetTitle("#sqrt{#mu barn}");

		Sp[l][p]->GetXaxis()->SetTitleSize(0.054);
		Sm[l][p]->GetXaxis()->SetTitleSize(0.054);
		Ep[l][p]->GetXaxis()->SetTitleSize(0.054);
		Em[l][p]->GetXaxis()->SetTitleSize(0.054);
		Mp[l][p]->GetXaxis()->SetTitleSize(0.054);
		Mm[l][p]->GetXaxis()->SetTitleSize(0.054);
		
		Sp[l][p]->GetYaxis()->SetTitleSize(0.054);
		Sm[l][p]->GetYaxis()->SetTitleSize(0.054);
		Ep[l][p]->GetYaxis()->SetTitleSize(0.054);
		Em[l][p]->GetYaxis()->SetTitleSize(0.054);
		Mp[l][p]->GetYaxis()->SetTitleSize(0.054);
		Mm[l][p]->GetYaxis()->SetTitleSize(0.054);

		Sp[l][p]->GetZaxis()->SetTitleSize(0.054);
		Sm[l][p]->GetZaxis()->SetTitleSize(0.054);
		Ep[l][p]->GetZaxis()->SetTitleSize(0.054);
		Em[l][p]->GetZaxis()->SetTitleSize(0.054);
		Mp[l][p]->GetZaxis()->SetTitleSize(0.054);
		Mm[l][p]->GetZaxis()->SetTitleSize(0.054);


		Sp[l][p]->GetXaxis()->SetTitleOffset(1.4);
		Sm[l][p]->GetXaxis()->SetTitleOffset(1.4);
		Ep[l][p]->GetXaxis()->SetTitleOffset(1.4);
		Em[l][p]->GetXaxis()->SetTitleOffset(1.4);
		Mp[l][p]->GetXaxis()->SetTitleOffset(1.4);
		Mm[l][p]->GetXaxis()->SetTitleOffset(1.4);
		
		
		Sp[l][p]->GetYaxis()->SetTitleOffset(1.3);
		Sm[l][p]->GetYaxis()->SetTitleOffset(1.3);
		Ep[l][p]->GetYaxis()->SetTitleOffset(1.3);
		Em[l][p]->GetYaxis()->SetTitleOffset(1.3);
		Mp[l][p]->GetYaxis()->SetTitleOffset(1.3);
		Mm[l][p]->GetYaxis()->SetTitleOffset(1.3);
		
		Sp[l][p]->GetZaxis()->SetTitleOffset(1.1);
		Sm[l][p]->GetZaxis()->SetTitleOffset(1.1);
		Ep[l][p]->GetZaxis()->SetTitleOffset(1.1);
		Em[l][p]->GetZaxis()->SetTitleOffset(1.1);
		Mp[l][p]->GetZaxis()->SetTitleOffset(1.1);
		Mm[l][p]->GetZaxis()->SetTitleOffset(1.1);
		
	}
	
	cout << "done." << endl;
}


TH2F* poles_histos::get_pole(int which, int plus_minus, int L, int Re_Im)
{
	if(which == 1 && plus_minus ==  1) return Sp[L][Re_Im];
	if(which == 2 && plus_minus ==  1) return Ep[L][Re_Im];
	if(which == 3 && plus_minus ==  1) return Mp[L][Re_Im];
	if(which == 1 && plus_minus == -1) return Sm[L][Re_Im];
	if(which == 2 && plus_minus == -1) return Em[L][Re_Im];
	if(which == 3 && plus_minus == -1) return Mm[L][Re_Im];
	return NULL;
}















