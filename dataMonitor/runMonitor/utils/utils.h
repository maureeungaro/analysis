#ifndef RUNMONITOR_UTILS_H
#define RUNMONITOR_UTILS_H 1

void setStyle();

TLatex commonLabel();

TCanvas *getOrCreateCanvas(string withName, double width, double height);

void printCanvas(string withName, string withTitle);

void printAll();

#endif

