#include "kin_corr.h"

// root
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"
#include "TF1.h"


void EKinnCorr_CS::show_2D_each_sector(int sector, int what, int phi_theta) {
    int s = sector - 1;

    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.08);
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadBottomMargin(0.16);

    TLatex lab;
    lab.SetTextFont(32);
    lab.SetTextSize(0.052);
    lab.SetNDC();

    float minX=H->hHp[0][0][what]->GetXaxis()->GetXmin();
    float maxX=H->hHp[0][0][what]->GetXaxis()->GetXmax();
    if (phi_theta == 1) {
        minX=H->hHt[0][0][what]->GetXaxis()->GetXmin();
        maxX=H->hHt[0][0][what]->GetXaxis()->GetXmax();
    }

    TLine *mm_value = new TLine(minX, mm_line[what], maxX, mm_line[what]);
    mm_value->SetLineStyle(2);

    TCanvas *C_Corr = new TCanvas("C_Corr", "C_Corr", csize, csize);
    TPad *P_Corr = new TPad("P_Corr", "P_Corr", 0.02, 0.05, 0.98, 0.92);
    P_Corr->Divide(1, 2);
    P_Corr->Draw();

    for (int c = 0; c < 2; c++) {
        P_Corr->cd(c+1);
        if (phi_theta == 0) {
            H->hHp[s][c][what]->GetYaxis()->SetTitle(mm_label[what].c_str());
            H->hHp[s][c][what]->GetXaxis()->SetTitle("#phi       [deg]");
            H->hHp[s][c][what]->GetXaxis()->SetTitleOffset(1.0);
            H->hHp[s][c][what]->GetYaxis()->SetTitleOffset(0.9);

            H->hHp[s][c][what]->GetXaxis()->SetTitleSize(0.07);
            H->hHp[s][c][what]->GetYaxis()->SetTitleSize(0.07);

            H->hHp[s][c][what]->GetXaxis()->SetLabelSize(0.06);
            H->hHp[s][c][what]->GetYaxis()->SetLabelSize(0.06);
            H->hHp[s][c][what]->Draw("colz");
        } else {
            H->hHt[s][c][what]->GetYaxis()->SetTitle(mm_label[what].c_str());
            H->hHt[s][c][what]->GetXaxis()->SetTitle("#theta       [deg]");

            H->hHt[s][c][what]->GetXaxis()->SetTitleOffset(1.14);
            H->hHt[s][c][what]->GetYaxis()->SetTitleOffset(0.9);

            H->hHt[s][c][what]->GetXaxis()->SetTitleSize(0.07);
            H->hHt[s][c][what]->GetYaxis()->SetTitleSize(0.07);

            H->hHt[s][c][what]->Draw("colz");
            H->hHt[s][c][what]->GetXaxis()->SetLabelSize(0.06);
            H->hHt[s][c][what]->GetYaxis()->SetLabelSize(0.06);
        }
        mm_value->Draw("same");
    }

    string d2_name = "vs #phi";
    string d2_names = "vsPhi";
    if (phi_theta == 1) {
        d2_name  = "vs #theta";
        d2_names = "vsTheta";
    }

    C_Corr->cd();
    lab.SetTextFont(102);
    lab.SetTextSize(0.04);
    lab.SetTextColor(kBlack);
    lab.DrawLatex(0.14, 0.94, Form("Momentum Correction: %s %s", mm_name[what].c_str(), d2_name.c_str() ));

    P_Corr->cd();
    lab.SetTextSize(0.035);
    if (s < 6) {
        lab.DrawLatex(0.64, 0.92, Form("Sector %d", s + 1));
    } else {
        lab.DrawLatex(0.64, 0.92, "All sectors");
    }

//



    if (PRINT != "none") {
        C_Corr->Print(Form("img/dist-%s%s_sector-%d%s", mm_names[what].c_str(), d2_names.c_str(),  s + 1, PRINT.c_str()));
    }

}
