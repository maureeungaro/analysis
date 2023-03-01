#include"parameters.h"

void activate_PRINT()
{
    if (is_simulation) {
        PRINT = SIM_PRINT;
    } else {
        PRINT = DATA_PRINT;
    }
    CCMatch->set_print(PRINT);
    ECMatch->set_print(PRINT);
}


void switch_print() {
    if ( PRINT == "none") {
        activate_PRINT();
    } else {
        PRINT = "none";
    }

    cout << " > PRINT set to  " << PRINT << endl;
}


void change_sector()
{
	SECTOR++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}


void print_cc_match()
{
    activate_PRINT();

    // This will also print the pars plots
    CCMatch->calc_all_cc_match();

    for (int s = 0; s < 6; s++) {
        SECTOR = s+1;

        CCMatch->show_cc_theta_match_comparison(SECTOR);
        CCMatch->show_cc_theta_match(SECTOR);

        // cc theta slices
        for(int b=0; b<CC_Match::NDIV; b++) {
            CCMatch->CC_DrawFit_ThetaSlice(s, b);
        }

    }

    // theta matching all sectors for calorimeter cuts in one plot
    CCMatch->show_theta_vs_segm_all_sectors();

    // phi match
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_phi_match(SECTOR);
    }
    CCMatch->show_phi_match_all_sectors();


    // time match all
    CCMatch->calc_all_cc_time_match();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_cc_timing(SECTOR);
        CCMatch->show_cc_timings(SECTOR);

        // cc timing slices
        for(int b=0; b<2*CC_Match::NDIV; b++) {
            CCMatch->CCT_DrawFit_TimeSlice(s,b);
        }
    }

    // cc timing all sectors
    CCMatch->show_cc_timing_all_sectors();


    // npe
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_npe(SECTOR);
    }
    CCMatch->show_npe_all_sectors();

}


void print_ec_match() {

    activate_PRINT();

    // thresholds
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        ECMatch->show_ecthr(SECTOR);
    }

    ECMatch->show_ecthr_all_sectors();


    // sampling fraction
    ECMatch->calc_sf_all_sectors();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;

        ECMatch->show_sf_comparison(SECTOR);
        ECMatch->show_sf(SECTOR);

        // sf slices
        for (int b = 0; b < EC_Match::NDIV; b++) {
            ECMatch->DrawFit_SF(s, b);
        }
    }

    ECMatch->show_sf_all_sectors();


    // Track position in calorimeters
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        ECMatch->show_uvw(SECTOR, 0);
        ECMatch->show_uvw(SECTOR, 1);
        ECMatch->show_uvw(SECTOR, 2);
    }

    ECMatch->show_uvw_all_sectors(0);
    ECMatch->show_uvw_all_sectors(1);
    ECMatch->show_uvw_all_sectors(2);


    ECMatch->show_ecyx();


    //    MIP cut
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        ECMatch->show_EoEi(SECTOR);
    }

    ECMatch->show_EoEi_all_sectors();

    // Shower Shape cut
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        ECMatch->show_EinEtot(SECTOR);
    }
    ECMatch->show_EinEtot_all_sectors();

}







void print_summary() {

    activate_PRINT();

    TLatex lab;
    lab.SetTextColor(kBlue+3);
    lab.SetTextFont(32);
    lab.SetTextSize(0.055);
    lab.SetNDC();

    gStyle->SetPadLeftMargin(0.08);
    gStyle->SetPadRightMargin(0.04);
    gStyle->SetPadTopMargin(0.16);
    gStyle->SetPadBottomMargin(0.12);
    double effectiveness[10] =
            {
                    1,
                    H->ecthr[3][6]->GetEntries()   / H->ecthr[1][6]->GetEntries(),
                    H->ecp[3][6]->GetEntries()     / H->ecp[1][6]->GetEntries(),
                    H->ECu[3][6]->GetEntries()     / H->ECu[1][6]->GetEntries(),
                    H->ECv[3][6]->GetEntries()     / H->ECv[1][6]->GetEntries(),
                    H->ECw[3][6]->GetEntries()     / H->ECw[1][6]->GetEntries(),
                    H->ECpos[3]->GetEntries()      / H->ECpos[1]->GetEntries(),
                    H->EoutEin[3][6]->GetEntries() / H->EoutEin[1][6]->GetEntries(),
                    H->EinEtot[3][6]->GetEntries() / H->EinEtot[1][6]->GetEntries(),
                    H->nphe[3][6]->GetEntries()    / H->nphe[1][6]->GetEntries(),
            };


    TH1F *s1 = new TH1F("s1", "s1", 10, 0, 10);
    TH1F *s2 = new TH1F("s2", "s2", 10, 0, 10);
    TH1F *s3 = new TH1F("s3", "s3", 10, 0, 10);

    for(int c=1; c<11; c++) {

        s1->SetBinContent(c, 100.0*H->monitor[0][6]->GetBinContent(c+1) / H->monitor[0][6]->GetBinContent(1));
        s2->SetBinContent(c, 100.0*effectiveness[c-1]);
        s3->SetBinContent(c, 100.0*H->monitor[1][6]->GetBinContent(c+1) / H->monitor[0][6]->GetBinContent(1));

        s1->GetYaxis()->SetRangeUser(0, 110);
        s2->GetYaxis()->SetRangeUser(0, 110);
        s3->GetYaxis()->SetRangeUser(0, 110);

        s1->GetXaxis()->SetLabelSize(0.00);
        s2->GetXaxis()->SetLabelSize(0.00);
        s3->GetXaxis()->SetLabelSize(0.00);

        s1->GetYaxis()->SetLabelSize(0.05);
        s2->GetYaxis()->SetLabelSize(0.05);
        s3->GetYaxis()->SetLabelSize(0.05);

        s1->GetYaxis()->SetLabelOffset(0.01);
        s2->GetYaxis()->SetLabelOffset(0.01);
        s3->GetYaxis()->SetLabelOffset(0.01);

        s1->GetYaxis()->SetNdivisions(505);
        s2->GetYaxis()->SetNdivisions(505);
        s3->GetYaxis()->SetNdivisions(505);
    }

    string cutn[10] = {
            "nphe",
            "EC thr",
            "S. F.",
            "U",
            "V ",
            "W",
            "UVW",
            "MIP",
            "EC Shape",
            "cc match",
    };


    TCanvas *Csum  = new TCanvas("Csum", "Csum", csize, csize);
    TPad    *Psum  = new TPad("Psum", "Psum", 0.02, 0.02,  0.98, 0.92);
    Psum->Divide(1, 3);
    Psum->Draw();

    Psum->cd(1);
    gPad->SetGridx();
    s1->SetFillColor(kGreen-9);
    s1->SetFillStyle(1001);
    s1->SetBarWidth(0.8);
    s1->SetBarOffset(0.1);
    s1->Draw("bar1");

    float pos_slope  = 0.088;
    float pos_slope2 = 0.087;

    lab.SetTextColor(kBlack);
    for(int c=0; c<10; c++) {
        lab.DrawLatex(0.11+c*pos_slope2, 0.05, Form("%s",      cutn[c].c_str()  ));
        lab.DrawLatex(0.11+c*pos_slope, 0.4,   Form("%3.1f%%", 100.0*H->monitor[0][6]->GetBinContent(c+2)  / H->monitor[0][6]->GetBinContent(1)  ));
    }


    Psum->cd(2);
    gPad->SetGridx();
    s2->SetFillColor(kGreen-9);
    s2->SetFillStyle(1001);
    s2->SetBarWidth(0.8);
    s2->SetBarOffset(0.1);
    s2->Draw("bar1");
    for(int c=0; c<10; c++) {
        lab.DrawLatex(0.11+c*pos_slope2, 0.05, Form("%s",      cutn[c].c_str()  ));
        lab.DrawLatex(0.11+c*pos_slope, 0.4,   Form("%3.1f%%", 100.0*effectiveness[c]  ));
    }



    Psum->cd(3);
    gPad->SetGridx();
    s3->SetFillColor(kGreen-9);
    s3->SetFillStyle(1001);
    s3->SetBarWidth(0.8);
    s3->SetBarOffset(0.1);
    s3->Draw("bar1");
    for(int c=0; c<10; c++) {
        lab.DrawLatex(0.11+c*pos_slope2, 0.05, Form("%s",      cutn[c].c_str()  ));
        lab.DrawLatex(0.11+c*pos_slope, 0.7,  Form("%3.1f%%", 100.0*H->monitor[1][6]->GetBinContent(c+2)  / H->monitor[0][6]->GetBinContent(1)  ));
    }

    lab.SetTextSize(0.08);
    lab.SetTextColor(kBlue+3);
    lab.SetTextFont(42);
    Psum->cd(1);
    lab.DrawLatex(0.39, 0.88, "Individual cuts effect");
    Psum->cd(2);
    lab.DrawLatex(0.37, 0.88, "Effectiveness (all other on) ");
    Psum->cd(3);
    lab.DrawLatex(0.35, 0.88, "Cumulative (ordered) cuts effect");

    Csum->cd(0);
    lab.SetTextFont(102);
    lab.SetTextColor(kBlack);
    lab.SetTextSize(0.046);
    lab.DrawLatex(0.16, 0.945,  "Electron Identification Summary");

    if(PRINT != "none") {
        Csum->Print(  Form("img/epidsummary%s", PRINT.c_str()) );
    }

}


void print_all()
{
    cout << " > Printing all histograms " << endl;

    print_cc_match();
    print_ec_match();

    print_summary();

    PRINT = "none";
}

void print_all_message() {
    cout << " > To print all histos see README " << endl;
}
