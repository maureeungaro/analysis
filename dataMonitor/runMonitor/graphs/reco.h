#ifndef RUNMONITOR_RECO_H
#define RUNMONITOR_RECO_H 1

// ROOT
TGraph *nElectrons[6];
TGraph *nPositives[6];
TGraph *nNegatives[6];
TGraph *nProtons[6];
TGraph *nPip[6];
TGraph *nPim[6];
TGraph *nKp[6];
TGraph *nKm[6];


void initRecoGraphs();
void showDC(int whichPlot);
int dcCase(int whichPlot);
int graphIndex(int whichPlot);

#endif

