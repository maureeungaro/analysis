#ifndef RUNMONITOR_RF_H
#define RUNMONITOR_RF_H 1

// ROOT
TGraph *RF, *sRF;
TGraph *RFP, *sRFP;
TGraph *RFpp, *sRFpp;
TGraph *RFpm, *sRFpm;

void initRF();
void showRF(int whichParticle);
void addRFButtons(TControlBar *toBar);

#endif

