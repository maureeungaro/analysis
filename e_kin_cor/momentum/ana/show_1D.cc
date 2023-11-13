#include "kin_corr.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"
#include "TF1.h"


void EKinnCorr_CS::show_1D_each_sector(int sector, int what) {
    int s = sector - 1;

    gStyle->SetPadLeftMargin(0.14);
    gStyle->SetPadRightMargin(0.08);
    gStyle->SetPadTopMargin(0.02);
    gStyle->SetPadBottomMargin(0.1);

    TLatex lab;
    lab.SetTextFont(32);
    lab.SetTextSize(0.052);
    lab.SetNDC();


    TLine *mm_value = new TLine(mm_line[what], 0, mm_line[what], H->hH[s][1][what]->GetMaximum() * 1.2);
    mm_value->SetLineStyle(2);

    TCanvas *C_Corr = new TCanvas("C_Corr", "C_Corr", csize, csize);
    TPad *P_Corr = new TPad("P_Corr", "P_Corr", 0.02, 0.05, 0.98, 0.92);
    P_Corr->Draw();
    P_Corr->cd();

    H->hH[s][0][what]->SetLineColor(kRed + 4);
    H->hH[s][1][what]->SetLineColor(kBlue);

    H->hH[s][1][what]->GetXaxis()->SetTitle(mm_label[what].c_str());
    H->hH[s][1][what]->GetXaxis()->SetTitleOffset(1.14);

    H->hH[s][1][what]->Draw();
    H->hH[s][0][what]->Draw("same");
    mm_value->Draw("same");


    // perform gaussian fit to the peak, limit the range to 2 sigma
    double mean = mm_line[what];
    double width = mm_width[what];

    double shift = 0;
    if (what == 0 ) shift = w_shifts[s];
    if (what == 1 ) shift = pi0_shifts[s];
    if (what == 2 ) shift = n_shifts[s];
    if (what == 3 ) shift = eta_shifts[s];

    TF1 *f1 = new TF1("f1", "gaus", mean - width, mean + width);
    TF1 *f2 = new TF1("f2", "gaus", mean + shift - width, mean + shift + width);
    f1->SetLineColor(kBlack);
    f2->SetLineColor(kRed);
    H->hH[s][1][what]->Fit("f1", "R");
    H->hH[s][0][what]->Fit("f2", "R");

    C_Corr->cd();
    lab.SetTextFont(102);
    lab.SetTextSize(0.043);
    lab.SetTextColor(kBlack);
    lab.DrawLatex(0.14, 0.94, Form("Momentum Correction: %s", mm_name[what].c_str()));


    P_Corr->cd();
    lab.SetTextSize(0.04);

    if(s<6) {
        lab.DrawLatex(0.64, 0.92, Form("Sector %d", s + 1));
    } else {
        lab.DrawLatex(0.64, 0.92, "All sectors");
    }
    lab.SetTextColor(kRed);
    lab.DrawLatex(0.6, 0.85, Form("Before: #mu=%4.3f",    f2->GetParameter(1) ));
    lab.DrawLatex(0.6, 0.80, Form("        #sigma=%4.3f", f2->GetParameter(2) ));
    lab.SetTextColor(kBlue);
    lab.DrawLatex(0.6, 0.70, Form("After: #mu=%4.3f",    f1->GetParameter(1) ));
    lab.DrawLatex(0.6, 0.65, Form("       #sigma=%4.3f", f1->GetParameter(2) ));


    if (PRINT != "none") {
        if (s == 6) {
            C_Corr->Print(Form("img/dist-%s_sector-all%s", mm_names[what].c_str(), PRINT.c_str()));
        }
        else {
            C_Corr->Print(Form("img/dist-%s_sector-%d%s", mm_names[what].c_str(), s + 1, PRINT.c_str()));
        }
    }

}
