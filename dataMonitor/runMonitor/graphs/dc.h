#ifndef RUNMONITOR_RF_H
#define RUNMONITOR_RF_H 1

// ROOT
TGraph *DC_res_mean[6], *DC_res_sigm[6];
TGraph *DC_mean[6][6],  *DC_sigm[6][6];


void initDCGraphs();
void showDC(int whichPlot);

#endif

