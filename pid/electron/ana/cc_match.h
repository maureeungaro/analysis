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
    CC_Match(chistos *common_histo, cpars *common_pars, string P, const Color_t colors[4]);

    // set print
    void set_print(string P) { PRINT = P; }

    // theta match
    void calc_cc_match(int sector);
    void calc_all_cc_match();
    void show_cc_theta_match_all_cuts(int sector);
    void show_cc_theta_match(int sector);
    void CC_DrawFit_ThetaSlice(int sectorIndex, int hid);
    void show_theta_vs_segm_all_sectors();
    void CC_DynamicExec(int sector);

    // phi match
    void show_phi_match(int sector);
    void show_phi_match_all_sectors();

    // time match
    void calc_cc_time_match(int sector);
    void calc_all_cc_time_match();
    void show_cc_timing(int sector);
    void show_cc_timings(int sector);
    void CCT_DrawFit_TimeSlice(int sectorIndex, int hid);
    void show_cc_timing_all_sectors();
    void CCT_DynamicExec(int sector);

    // npe
    void show_npe(int sector);
    void show_npe_all_sectors();



private:

    chistos *H;
    cpars *Pars;
    string PRINT;
    const int NDIV = 15;
    const int csize = 1200; // common canvas size
    Color_t colors[4];


    // CC theta match histos, variables, functions

    TH1F *cc_match1d[6][18];      // 1 dimensional projections, fitted with GAUSS+PARABOLE
    double cc_matchmean[6][18];
    double cc_matchsigm[6][18];
    double cc_matchmeane[6][18];
    double cc_matchsigme[6][18];
    TGraphErrors *cc_match_mean[6];
    TGraphErrors *cc_match_sigm[6];

    // functions based on parameters in Pars
    Double_t cc_match_Mean( Double_t *x, Double_t *par);
    Double_t cc_match_Mean2(Double_t *x, Double_t *par);
    Double_t cc_match_Sigma(Double_t *x, Double_t *par);
    Double_t cc_match_limit(Double_t *x, Double_t *par);

    TF1 *cc_match_me;
    TF1 *cc_match_up;
    TF1 *cc_match_dn;


    // CC timing histos, variables, functions
    TH1F *cc_timing1d[6][36];      // 1 dimensional projections, fitted with GAUSS
    TGraphErrors *cc_timing_low[6];

};


#endif