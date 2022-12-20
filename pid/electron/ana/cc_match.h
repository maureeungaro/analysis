#ifndef CCMATCH_PARAMETERS_LOADED
#define CCMATCH_PARAMETERS_LOADED

// histos and parameters
#include "../src/common_info.h"

// root
#include "TGraphErrors.h"
#include "TF1.h"


class CC_Match {

public:

    CC_Match();
    ~CC_Match();

    // constructor using chisto and cpars
    CC_Match(chistos *common_histo, cpars *common_pars, string P);

    // set print
    void set_print(string P) { PRINT = P; }
    void calc_cc_match(int sector);
    void calc_all_cc_match();
    void show_cc_theta_match_all_cuts(int sector);
    void show_cc_theta_match(int sector);
    void CC_DrawFit_ThetaSlice(int sector_index, int hid);
    void show_theta_vs_segm_all_sectors();
    void CC_DynamicExec(int sector);

private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int NDIV = 15;

    // CC theta match histos, variables, functions
    TH1F *cc_match1d[6][18];      // 1 dimensional projections, fitted with GAUSS+PARABOLE
    double cc_matchmean[6][18];
    double cc_matchsigm[6][18];
    double cc_matchmeane[6][18];
    double cc_matchsigme[6][18];
    TGraphErrors *cc_match_mean[6];
    TGraphErrors *cc_match_sigm[6];

    //Color_t colors[4] = { kBlack, kBlue, kRed, kGreen+3 };

    // CC timing histos, variables, functions
    TH1F *cc_timing1d[6][36];      // 1 dimensional projections, fitted with GAUSS
    TGraphErrors *cc_timing_low[6];

    TF1 *cc_match_me;
    TF1 *cc_match_up;
    TF1 *cc_match_dn;

    // adds the functions defined in cc_match.cc
    Double_t cc_match_Mean( Double_t *x, Double_t *par);
    Double_t cc_match_Mean2(Double_t *x, Double_t *par);
    Double_t cc_match_Sigma(Double_t *x, Double_t *par);
    Double_t cc_match_limit(Double_t *x, Double_t *par);
};


#endif