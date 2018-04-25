#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>

const int LAYERS       = 36;
const int SECTORS      = 6;
const int MAX_WIRES    = 192;

int    opt             = 0;      // 1 for verbose mode
int    SSector         = 0;      // 1 to analyze each sector individually.
int    Force_LW        = 0;      // 1 to force first 4 wires in R1 to have efficiency = 1 (in case SSector=1 and steep change in occupancy) 
bool   WriteROOT       = false;
bool   WriteASCII      = false;
int    minLayers       = 1;
int    maxLayers       = 36;
double lowLimit        = 1e-3;
double highLimit       = 0.9;
double buddies         = 0.16;   // wires with occupancy within this percentage are considered buddies
string   ROOToutfile    ;
string   ASCIIoutfile  ;
string inputFile      ;
TFile  *rootout        = NULL;                 // for ROOT output
ofstream OUT ;                    // ascii file to put in map

typedef struct
{
	int Min;                       // structure for wire limits
	int Max;                       // it holds the actual number of wires in each layer
}Wlimits_t;

void PrintUsage(string processName); 

#include "usage.C"
#include "utils.C"

int main(int argc,char **argv)
{
	// use 18 neighboring wires
	// on the boundary, use 12 instead of 18
	// If SSector = 0, group all sectors
	// otherwise consider each sector individually
	
	int nXbin[SECTORS], nYbin[SECTORS];
	double hits[SECTORS][LAYERS][MAX_WIRES];       // wire occupancy
	double efficiency[SECTORS][LAYERS][MAX_WIRES]; // wire efficiency
	double average[LAYERS][MAX_WIRES];             // wire average
	usage(argc, argv);
	
	// initialize chambers wires limits / per layer
	Wlimits_t WIRES[36];
	initWireLimit(WIRES);
	
	// Load occupancy values from input file - initialize efficiency values
	TH2F *h;
	TFile fin(inputFile.c_str());
	if(!fin.IsOpen())
	{
    cerr << " Error opening input ROOT file\t" << inputFile << endl;
    exit(1);
	}
	for(int sec = 0; sec < SECTORS; sec++)
	{
    h = (TH2F*)fin.Get(Form("h%d", 200+10*(sec+1)));
    if(!h) cout << Form("h%d", 200+10*(sec+1)) << " not found." << endl;
    nXbin[sec] = h->GetNbinsX();
    nYbin[sec] = h->GetNbinsY();
		
		for(int layer = 0; layer < nYbin[sec]; layer++)
			for(int wire = 0; wire < nXbin[sec]; wire++)
			{
        hits[sec][layer][wire] = h->GetBinContent(wire+1, layer+1);
        efficiency[sec][layer][wire] = -1;
			}
	}
	fin.Close();
	
	// Now analyzing each wire, find efficiency
	double a[18];   // Array of 18 neighboring wires
	int reject[18]; // = 1 if no wire exists
	
	// If grouping all sectors:
	if(SSector == 0)
	{
    for(int layer = minLayers-1; layer < maxLayers; layer++)
    {
			cerr << " Analyzing Layer " << layer+1 << "\r";
			// loops over all existing wires
			for(int wire = WIRES[layer].Min-1; wire < WIRES[layer].Max; wire++)
			{
				for(int i = 0; i < 18 ; i++)
				{
					a[i]      = 0.0;
					reject[i] = 1;
				}
				for(int sec = 0; sec < SECTORS; sec++)
				{
					if(wire != WIRES[layer].Min-1 && wire != WIRES[layer].Max-1)
					{
						a[sec]                = hits[sec][layer][wire];      // actual wire
						a[sec+SECTORS]        = hits[sec][layer][wire-1];    // left neighbor
						a[sec+2*SECTORS]      = hits[sec][layer][wire+1];    // right neighbor
					}
					else if(wire == WIRES[layer].Min-1)                     // no left neighbor
					{
						a[sec]                = hits[sec][layer][wire];
						a[sec+SECTORS]        = hits[sec][layer][wire+1];    // right neighbor
						a[sec+2*SECTORS]      = hits[sec][layer][wire+2];    // right right neighbor
					}
					else if(wire == WIRES[layer].Max-1)                     // no right neighbor
					{
						a[sec]                = hits[sec][layer][wire];
						a[sec+SECTORS]        = hits[sec][layer][wire-1];    // left neighbor
						a[sec+SECTORS]        = hits[sec][layer][wire-2];    // left left neighbor
					}
				}
				for(int sec = 0; sec < SECTORS; sec++) efficiency[sec][layer][wire] = eff(hits[sec][layer][wire], a, reject, &average[layer][wire]);
			}
    }
	}
	
  // If treating each sectors individually
	if(SSector == 1)
	{
    for(int layer = minLayers-1; layer < maxLayers; layer++)
    {
			cerr << " Analyzing Layer " << layer+1 << "\r";
			// loops over all existing wires
			for(int wire = WIRES[layer].Min-1; wire < WIRES[layer].Max; wire++)
			{
				for(int i = 0; i < 18 ; i++)
				{
					a[i]      = 0.0;
					reject[i] = 1;
				}
				for(int sec = 0; sec < SECTORS; sec++)
				{
					
					//              cout << " layer: " << layer << "    wire: " << wire
					//                   << "   min: " << wire_limits(wire+1, WIRES[layer]).Min
					//                   << "   max: " << wire_limits(wire+1, WIRES[layer]).Max << endl;
					
					if(layer != 0 && layer != maxLayers-1)
					{
						int indx = 0;
						for(int i=wire_limits(wire+1, WIRES[layer]).Min - 1; i<wire_limits(wire+1, WIRES[layer]).Max; i++)
							a[indx++] = hits[sec][layer][i];
						for(int i=wire_limits(wire+1, WIRES[layer-1]).Min - 1; i<wire_limits(wire+1, WIRES[layer-1]).Max; i++)
							a[indx++] = hits[sec][layer-1][i];
						for(int i=wire_limits(wire+1, WIRES[layer+1]).Min - 1; i<wire_limits(wire+1, WIRES[layer+1]).Max; i++)
							a[indx++] = hits[sec][layer+1][i];
					}
					if(layer == 0)
					{
						int indx = 0;
						for(int i=wire_limits(wire+1, WIRES[layer]).Min - 1; i<wire_limits(wire+1, WIRES[layer]).Max; i++)
							a[indx++] = hits[sec][layer][i];
						for(int i=wire_limits(wire+1, WIRES[layer+1]).Min - 1; i<wire_limits(wire+1, WIRES[layer+1]).Max; i++)
							a[indx++] = hits[sec][layer+1][i];
						for(int i=wire_limits(wire+1, WIRES[layer+2]).Min - 1; i<wire_limits(wire+1, WIRES[layer+2]).Max; i++)
							a[indx++] = hits[sec][layer+2][i];
					}
					if(layer == maxLayers-1)
					{
						int indx = 0;
						for(int i=wire_limits(wire+1, WIRES[layer]).Min - 1; i<wire_limits(wire+1, WIRES[layer]).Max; i++)
							a[indx++] = hits[sec][layer][i];
						for(int i=wire_limits(wire+1, WIRES[layer-1]).Min - 1; i<wire_limits(wire+1, WIRES[layer-1]).Max; i++)
							a[indx++] = hits[sec][layer-1][i];
						for(int i=wire_limits(wire+1, WIRES[layer-2]).Min - 1; i<wire_limits(wire+1, WIRES[layer-2]).Max; i++)
							a[indx++] = hits[sec][layer-2][i];
					}
					
					efficiency[sec][layer][wire] = eff(hits[sec][layer][wire], a, reject, &average[layer][wire]);
					if(Force_LW && wire < WIRES[layer].Min + 4 && layer < 16)  efficiency[sec][layer][wire] = 1;
				}
			}
    }
	}
	
	
	
	// Counting wires in different efficiency situations -- printing out results
	int GRADE[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // How many wires in different efficiency situations
	double TOT = 0;                           // Total numbers of wires analyzied
	for(int sec = 0; sec < SECTORS; sec++)
	{
    for(int layer = 0; layer < LAYERS; layer++)
    {
			for(int wire = 0; wire < MAX_WIRES; wire++)
			{
				if(efficiency[sec][layer][wire] < 0.05    && efficiency[sec][layer][wire] >= 0.0 )   GRADE[0]++;
				if(efficiency[sec][layer][wire] < 0.1     && efficiency[sec][layer][wire] >= 0.05 )  GRADE[1]++;
				if(efficiency[sec][layer][wire] < 0.5     && efficiency[sec][layer][wire] >= 0.1 )   GRADE[2]++;
				if(efficiency[sec][layer][wire] < 0.9     && efficiency[sec][layer][wire] >= 0.5 )   GRADE[3]++;
				if(efficiency[sec][layer][wire] < 1.1     && efficiency[sec][layer][wire] >= 0.9 )   GRADE[4]++;
				if(efficiency[sec][layer][wire] < 1.5     && efficiency[sec][layer][wire] >= 1.1 )   GRADE[5]++;
				if(efficiency[sec][layer][wire] < 10.0    && efficiency[sec][layer][wire] >= 1.5 )   GRADE[6]++;
				if(efficiency[sec][layer][wire] >= 10.0)                                             GRADE[7]++;
			}
    }
	}
	for(int i=0; i<8; i++) TOT = TOT + GRADE[i];
	cout << endl << endl << " Results: " << endl;
	cout << " Efficiency range     Number of wires       Percentage"<< endl << endl << std::setprecision(3);
	cout << "     < 0.05     " << setw(15)   << GRADE[0]  << "  \t" << setw(13)   << 100*GRADE[0]/TOT << "%" << endl;
	cout << "   0.05 - 0.1   " << setw(15)   << GRADE[1]  << "  \t" << setw(13)   << 100*GRADE[1]/TOT << "%" << endl;
	cout << "   0.1  - 0.5   " << setw(15)   << GRADE[2]  << "  \t" << setw(13)   << 100*GRADE[2]/TOT << "%" << endl;
	cout << "   0.5  - 0.9   " << setw(15)   << GRADE[3]  << "  \t" << setw(13)   << 100*GRADE[3]/TOT << "%" << endl;
	cout << "   0.9  - 1.1   " << setw(15)   << GRADE[4]  << "  \t" << setw(13)   << 100*GRADE[4]/TOT << "%" << endl;
	cout << "   1.1  - 1.5   " << setw(15)   << GRADE[5]  << "  \t" << setw(13)   << 100*GRADE[5]/TOT << "%" << endl;
	cout << "   1.5  - 10    " << setw(15)   << GRADE[6]  << "  \t" << setw(13)   << 100*GRADE[6]/TOT << "%" << endl;
	cout << "      > 10      " << setw(15)   << GRADE[7]  << "  \t" << setw(13)   << 100*GRADE[7]/TOT << "%" << endl;
	cout << endl;
	cout << " Total number of wires analyzed: " << std::setprecision(6) << TOT << endl;
	cout << endl;
	
	// Writing ROOT output
	if(WriteROOT && rootout)
	{
    rootout->cd();
    cout << " Saving histos to ROOT file " << ROOToutfile << " ..." << endl;
	}
	
	TH2F *heff[SECTORS];
	TH2F *hmap[SECTORS];
	TH2F have("have", "Expected value", 192, 0.5, 192.5, 36, 0.5, 36.5);
	
	for(int sec = 0; sec < SECTORS; sec++)
	{
    heff[sec] = new TH2F(Form("WireEfficiency_Sector%d", sec+1), Form("Wire Efficiency for Sector %d", sec+1),     192, 0.5, 192.5, 36, 0.5, 36.5);
    hmap[sec] = new TH2F(Form("WireMap_Sector%d", sec+1),        Form("Wire Efficiency Map for Sector %d", sec+1), 192, 0.5, 192.5, 36, 0.5, 36.5);
    for(int layer = 0; layer < LAYERS; layer++)
			for(int wire = 0; wire < MAX_WIRES; wire++)
			{
        heff[sec]->SetBinContent(wire+1, layer+1, efficiency[sec][layer][wire]);
        have.SetBinContent(      wire+1, layer+1, average[layer][wire]);
				
        if(efficiency[sec][layer][wire] > lowLimit && efficiency[sec][layer][wire] < highLimit)
          hmap[sec]->SetBinContent(wire+1, layer+1, efficiency[sec][layer][wire]);
				
        // if eff too small, write it as zero
        if(efficiency[sec][layer][wire] <= lowLimit)
          hmap[sec]->SetBinContent(wire+1, layer+1, 0);
				
        // if eff too high, write it as one
        if(efficiency[sec][layer][wire] >= highLimit)
          hmap[sec]->SetBinContent(wire+1, layer+1, 1);
				
        if(lowLimit==highLimit && efficiency[sec][layer][wire] >= highLimit)
          hmap[sec]->SetBinContent(wire+1, layer+1, 0);
        if(lowLimit==highLimit && efficiency[sec][layer][wire] < highLimit)
          hmap[sec]->SetBinContent(wire+1, layer+1, 1);
				
			}
		
    if(WriteROOT && rootout)
    {
			heff[sec]->Write();
			hmap[sec]->Write();
    }
		
    heff[sec]->Delete();
    hmap[sec]->Delete();
	}
	if(WriteROOT && rootout) have.Write();
	
	
	//Writing map file
	if(WriteASCII)  cout << " Saving gpp efficiency to file " << ASCIIoutfile << " ..." << endl;
	
	double effi_gpp;
	for(int layer = 0; layer < LAYERS; layer++)
		for(int wire = 0; wire < MAX_WIRES; wire++)
		{
			for(int sec = 0; sec < SECTORS; sec++)
			{
				effi_gpp = efficiency[sec][layer][wire];
				if(effi_gpp <=lowLimit)   effi_gpp = 0;
				if(effi_gpp >= highLimit) effi_gpp = 1;
				
				if(effi_gpp <=lowLimit  && lowLimit==highLimit)  effi_gpp = 1;
				if(effi_gpp > highLimit && lowLimit==highLimit)  effi_gpp = 0;
				
				if(WriteASCII) OUT << effi_gpp << "\t";
			}
			if(WriteASCII) OUT << endl;
		}
	
	if(WriteASCII) OUT.close();
	if(WriteROOT && rootout) rootout->Close();
	
	cout << endl << " Done" << endl << endl;
	return (0);
}

































