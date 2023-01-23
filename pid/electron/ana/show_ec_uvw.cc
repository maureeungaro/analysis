#include "ec_match.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLine.h"


void EC_Match::show_uvw(int sector, int which)
{
	gStyle->SetPadLeftMargin(0.12);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.12);
	gStyle->SetPadBottomMargin(0.12);

	TLatex lab;
    lab.SetNDC();

	int s = sector -1;

    TH1F *UCW[4][6];
    TLine *UVW_cut1 = nullptr;
    TLine *UVW_cut2 = nullptr;

    for(int c=0; c<4; c++) {
        for(int s=0; s<6; s++) {
            if (which == 0) {
                UCW[c][s] = H->ECu[c][s];
            } else if (which == 1) {
                UCW[c][s] = H->ECv[c][s];
            } else if (which  == 2) {
                UCW[c][s] = H->ECw[c][s];
            }

            UCW[c][s]->SetBinContent(6, 0);
            UCW[c][s]->GetXaxis()->SetTitleSize(0.042);
            UCW[c][s]->GetXaxis()->SetTitleOffset(1.1);
            UCW[c][s]->GetXaxis()->SetLabelSize(0.034);
            UCW[c][s]->GetYaxis()->SetLabelSize(0.034);
        }
    }

    if(which == 0) {
        UVW_cut1 = new TLine(Pars->umin, 0, Pars->umin, UCW[1][s]->GetMaximum());
        UVW_cut2 = new TLine(Pars->umax, 0, Pars->umax, UCW[1][s]->GetMaximum()/5);
        UVW_cut1->SetLineStyle(9);
        UVW_cut2->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
        UVW_cut2->SetLineWidth(2);
    } else if(which == 1) {
        UVW_cut1 = new TLine(Pars->vmax, 0, Pars->vmax, UCW[1][s]->GetMaximum());
        UVW_cut1->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
    } else if(which == 2) {
        UVW_cut1 = new TLine(Pars->wmax, 0, Pars->wmax, UCW[1][s]->GetMaximum());
        UVW_cut1->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
    }


	TCanvas *Cuvw  = new TCanvas(Form("Cuvw%d", which), "Cuvw", csize, csize);
	TPad    *Puvw  = new TPad(   Form("Puvw%d", which), "Puvw", 0.02, 0.00,  0.98, 0.92);
	Puvw->Draw();

    UCW[1][s]->Draw();
    UCW[2][s]->Draw("same");
    UCW[3][s]->Draw("same");


	UVW_cut1->Draw();
	if(UVW_cut2){
		UVW_cut2->Draw();
	}

	lab.SetTextColor(colors[0]);
	lab.SetTextFont(42);
	lab.SetTextSize(0.034);
	lab.SetTextColor(kBlue);

    if(which == 0) {
		lab.DrawLatex(0.5, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.5, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.5, 0.73,  Form("U cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()));
    } else if(which == 1) {
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("V cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()));
    } else if(which == 2) {
		lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kRed);
		lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()));
		lab.SetTextColor(kGreen+3);
		lab.DrawLatex(0.2, 0.73,  Form("W cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()));
	}

	lab.SetTextFont(102);
	lab.SetTextColor(kBlack);
	lab.SetTextSize(0.04);

    if(which == 0) {
	    lab.DrawLatex(0.1, 0.94,  "U coordinate in EC");
    } else if(which == 1) {
	    lab.DrawLatex(0.1, 0.94,  "V coordinate in EC");
    } else if(which == 2) {
        lab.DrawLatex(0.1, 0.94, "W coordinate in EC");
    }


	lab.SetTextFont(42);
	lab.SetTextSize(0.025);
	lab.SetTextColor(kBlue);
	lab.DrawLatex(0.65, 0.97,  "#rightarrow all other cuts applied");
	lab.SetTextColor(kRed);
	lab.DrawLatex(0.65, 0.93,  "#rightarrow negative cuts applied");
	lab.SetTextColor(kGreen+3);
	lab.DrawLatex(0.65, 0.89,  "#rightarrow all cuts applied");

	if(PRINT != "none")
	{
        if(which == 0) {
			Cuvw->Print(Form("img/cut-06-ECU_sector-%d%s", sector, PRINT.c_str() ));
        } else if(which == 1) {
			Cuvw->Print(Form("img/cut-07-ECV_sector-%d%s", sector, PRINT.c_str() ));
        } else if(which == 2) {
			Cuvw->Print(Form("img/cut-08-ECW_sector-%d%s", sector, PRINT.c_str() ));
		}
	}
	
}

void EC_Match::show_uvw_integrated_sectors(int which)
{
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPadTopMargin(0.12);
    gStyle->SetPadBottomMargin(0.12);

    TLatex lab;
    lab.SetNDC();

    TH1F *UCW[4];
    TLine *UVW_cut1 = nullptr;
    TLine *UVW_cut2 = nullptr;

    for(int c=0; c<4; c++) {
        if (which == 0) {
            UCW[c] = H->ECu[c][6];
        } else if (which == 1) {
            UCW[c] = H->ECv[c][6];
        } else if (which  == 2) {
            UCW[c] = H->ECw[c][6];
        }

        UCW[c]->SetBinContent(6, 0);
        UCW[c]->GetXaxis()->SetTitleSize(0.04);
        UCW[c]->GetXaxis()->SetTitleOffset(1.1);
        UCW[c]->GetXaxis()->SetLabelSize(0.034);
        UCW[c]->GetYaxis()->SetLabelSize(0.034);
    }


    if(which == 0) {
        UVW_cut1 = new TLine(Pars->umin, 0, Pars->umin, UCW[1]->GetMaximum());
        UVW_cut2 = new TLine(Pars->umax, 0, Pars->umax, UCW[1]->GetMaximum()/5);
        UVW_cut1->SetLineStyle(9);
        UVW_cut2->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
        UVW_cut2->SetLineWidth(2);
    } else if(which == 1) {
        UVW_cut1 = new TLine(Pars->vmax, 0, Pars->vmax, UCW[1]->GetMaximum());
        UVW_cut1->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
        UVW_cut2 = nullptr;
    } else if(which == 2) {
        UVW_cut1 = new TLine(Pars->wmax, 0, Pars->wmax, UCW[1]->GetMaximum());
        UVW_cut1->SetLineStyle(9);
        UVW_cut1->SetLineWidth(2);
        UVW_cut2 = nullptr;
    }

    TCanvas *Cuvw  = new TCanvas(Form("Cuvw%d", which), "Cuvw", csize, csize);
    TPad    *Puvw  = new TPad(   Form("Puvw%d", which), "Puvw", 0.02, 0.00,  0.98, 0.92);
    Puvw->Draw();

    UCW[1]->Draw();
    UCW[2]->Draw("same");
    UCW[3]->Draw("same");

    UVW_cut1->Draw();

    if(UVW_cut2){
        UVW_cut2->Draw();
    }

    lab.SetTextColor(colors[0]);
    lab.SetTextFont(42);
    lab.SetTextSize(0.034);
    lab.SetTextColor(kBlue);

    if(which == 0) {
        lab.DrawLatex(0.5, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1]->GetEntries() / UCW[0]->GetEntries()) );
        lab.SetTextColor(kRed);
        lab.DrawLatex(0.5, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2]->GetEntries() / UCW[0]->GetEntries()) );
        lab.SetTextColor(kGreen+3);
        lab.DrawLatex(0.5, 0.73,  Form("U cut / all others:  %3.1f%%",         100.0*UCW[3]->GetEntries() / UCW[1]->GetEntries()) );
    } else if(which == 1) {
        lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1]->GetEntries() / UCW[0]->GetEntries()));
        lab.SetTextColor(kRed);
        lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2]->GetEntries() / UCW[0]->GetEntries()));
        lab.SetTextColor(kGreen+3);
        lab.DrawLatex(0.2, 0.73,  Form("V cut / all others:  %3.1f%%",         100.0*UCW[3]->GetEntries() / UCW[1]->GetEntries()));
    } else if(which == 2) {
        lab.DrawLatex(0.2, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1]->GetEntries() / UCW[0]->GetEntries()));
        lab.SetTextColor(kRed);
        lab.DrawLatex(0.2, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2]->GetEntries() / UCW[0]->GetEntries()));
        lab.SetTextColor(kGreen+3);
        lab.DrawLatex(0.2, 0.73,  Form("W cut / all others:  %3.1f%%",         100.0*UCW[3]->GetEntries() / UCW[1]->GetEntries()));
    }

    lab.SetTextFont(102);
    lab.SetTextColor(kBlack);
    lab.SetTextSize(0.04);
    if(which == 0) {
        lab.DrawLatex(0.1, 0.94, "U coordinate in EC");
    } else if(which == 1) {
        lab.DrawLatex(0.1, 0.94, "V coordinate in EC");
    } else if(which == 2) {
        lab.DrawLatex(0.1, 0.94, "W coordinate in EC");
    }

    lab.SetTextFont(42);
    lab.SetTextSize(0.025);
    lab.SetTextColor(kBlue);
    lab.DrawLatex(0.65, 0.97,  "#rightarrow all other cuts applied");
    lab.SetTextColor(kRed);
    lab.DrawLatex(0.65, 0.93,  "#rightarrow negative cuts applied");
    lab.SetTextColor(kGreen+3);
    lab.DrawLatex(0.65, 0.89,  "#rightarrow all cuts applied");

    if(PRINT != "none") {
        if(which == 0) {
            Cuvw->Print(Form("img/cut-06-ECU_sector-integral%s", PRINT.c_str() ));
        } else if(which == 1) {
            Cuvw->Print(Form("img/cut-07-ECV_sector-integral%s", PRINT.c_str() ));
        } else if(which == 2) {
            Cuvw->Print(Form("img/cut-08-ECW_sector-integral%s", PRINT.c_str() ));
        }
    }
}

void EC_Match::show_uvw_all_sectors(int which)
{

    gStyle->SetPadLeftMargin(0.08);
    gStyle->SetPadRightMargin(0.02);
    gStyle->SetPadTopMargin(0.06);
    gStyle->SetPadBottomMargin(0.1);

    TLatex lab;
    lab.SetNDC();

    TH1F *UCW[4][6] = {{nullptr}};

    TLine *UVW_cut1[6] = {nullptr};
    TLine *UVW_cut2[6] = {nullptr};

    for(int c=0; c<4; c++) {
        for(int s=0; s<6; s++) {
            if (which == 0) {
                UCW[c][s] = H->ECu[c][s];
            } else if (which == 1) {
                UCW[c][s] = H->ECv[c][s];
            } else if (which  == 2) {
                UCW[c][s] = H->ECw[c][s];
            }

            UCW[c][s]->SetBinContent(6, 0);
            UCW[c][s]->GetXaxis()->SetTitleSize(0.05);
            UCW[c][s]->GetXaxis()->SetTitleOffset(1.1);
            UCW[c][s]->GetXaxis()->SetLabelSize(0.045);
            UCW[c][s]->GetYaxis()->SetLabelSize(0.045);
        }
    }

    for(int s=0; s<6; s++) {
        if (which == 0) {
            UVW_cut1[s] = new TLine(Pars->umin, 0, Pars->umin, UCW[1][s]->GetMaximum());
            UVW_cut2[s] = new TLine(Pars->umax, 0, Pars->umax, UCW[1][s]->GetMaximum() / 5);
            UVW_cut1[s]->SetLineStyle(9);
            UVW_cut2[s]->SetLineStyle(9);
            UVW_cut1[s]->SetLineWidth(2);
            UVW_cut2[s]->SetLineWidth(2);
        } else if (which == 1) {
            UVW_cut1[s] = new TLine(Pars->vmax, 0, Pars->vmax, UCW[1][s]->GetMaximum());
            UVW_cut1[s]->SetLineStyle(9);
            UVW_cut1[s]->SetLineWidth(2);
        } else if (which == 2) {
            UVW_cut1[s] = new TLine(Pars->wmax, 0, Pars->wmax, UCW[1][s]->GetMaximum());
            UVW_cut1[s]->SetLineStyle(9);
            UVW_cut1[s]->SetLineWidth(2);
        }
    }

    TCanvas *Cuvw  = new TCanvas(Form("Cuvw%d", which), "Cuvw", csize, csize);
    TPad    *Puvw  = new TPad(   Form("Puvw%d", which), "Puvw", 0.02, 0.00,  0.98, 0.88);
    Puvw->Divide(3, 2);
    Puvw->Draw();

    for(int s=0; s<6; s++) {

        Puvw->cd(s+1);

        UCW[1][s]->Draw();
        UCW[2][s]->Draw("same");
        UCW[3][s]->Draw("same");

        UVW_cut1[s]->Draw();

        if (UVW_cut2[s]) {
            UVW_cut2[s]->Draw();
        }

        lab.SetTextColor(colors[0]);
        lab.SetTextFont(42);
        lab.SetTextSize(0.05);
        lab.SetTextColor(kBlue);

        if(which == 0) {
            lab.DrawLatex(0.35, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kRed);
            lab.DrawLatex(0.35, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kGreen+3);
            lab.DrawLatex(0.35, 0.73,  Form("U cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()) );
        } else if(which == 1) {
            lab.DrawLatex(0.15, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kRed);
            lab.DrawLatex(0.15, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kGreen+3);
            lab.DrawLatex(0.15, 0.73,  Form("V cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()) );
        } else if(which == 2) {
            lab.DrawLatex(0.15, 0.83,  Form("all others / no cut:  %3.1f%%",        100.0*UCW[1][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kRed);
            lab.DrawLatex(0.15, 0.78,  Form("negative others / no cut:  %3.1f%%",   100.0*UCW[2][s]->GetEntries() / UCW[0][s]->GetEntries()) );
            lab.SetTextColor(kGreen+3);
            lab.DrawLatex(0.15, 0.73,  Form("W cut / all others:  %3.1f%%",         100.0*UCW[3][s]->GetEntries() / UCW[1][s]->GetEntries()) );
        }

        Cuvw->Update();

    }

    Cuvw->cd(0);

    lab.SetTextFont(102);
    lab.SetTextColor(kBlack);
    lab.SetTextSize(0.04);

    if(which == 0) {
        lab.DrawLatex(0.1, 0.94, "U coordinate in EC");
    } else if(which == 1) {
        lab.DrawLatex(0.1, 0.94, "V coordinate in EC");
    } else if(which == 2) {
        lab.DrawLatex(0.1, 0.94, "W coordinate in EC");
    }


    lab.SetTextFont(42);
    lab.SetTextSize(0.025);
    lab.SetTextColor(kBlue);
    lab.DrawLatex(0.65, 0.97,  "#rightarrow all other cuts applied");
    lab.SetTextColor(kRed);
    lab.DrawLatex(0.65, 0.93,  "#rightarrow negative cuts applied");
    lab.SetTextColor(kGreen+3);
    lab.DrawLatex(0.65, 0.89,  "#rightarrow all cuts applied");

    if(PRINT != "none") {
        if(which == 0) {
            Cuvw->Print(Form("img/cut-06-ECU_sector-all%s", PRINT.c_str() ));
        } else if(which == 1) {
            Cuvw->Print(Form("img/cut-07-ECV_sector-all%s", PRINT.c_str() ));
        } else if(which == 2) {
            Cuvw->Print(Form("img/cut-08-ECW_sector-all%s", PRINT.c_str() ));
        }
    }


}
