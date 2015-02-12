#ifndef INFO_H
#define INFO_H
 
// %%%%%%%%%%%%%
// ROOT includes
// %%%%%%%%%%%%%
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <string>
#include <iostream>
using namespace std;

// Common Classes with ROOT analysis macro

class chistos
{
	public:
		chistos(string filename, int READ = 0);
		~chistos(){;}
		
		TFile *output;
		
		// 4 cuts, 6 sectors + all sectors
		TH1F *nphe[4][7];           // 10*number of photoelectrons
		TH1F *enphe[7];             // 10*number of photoelectrons, utility histo to draw the zero line
		TH2F *theta_vs_segm[4][7];  // Theta position in CC plane vs segment (CC theta segment matching)
		TH1F *phi_match[4][7];      // +1: right match. +2 right mismatch. -1: left match. -2: left mistmatch
		TH2F *cc_timing[4][7];      // CC time - TOF time + Dpath/c vs segment  (CC timing)
		TH1F *ecthr[4][7];          // Momentum
		TH2F *ecp[4][7];            // Etot/p vs p
		TH1F *ECu[4][7];            // u coordinate in EC
		TH1F *ECv[4][7];            // v coordinate in EC
		TH1F *ECw[4][7];            // w coordinate in EC
		TH2F *EoutEin[4][7];        // Eouter/p vs Einner/p
		TH2F *EinEtot[4][7];        // Ein/Etot
		
		// utility histos
		TH2F *nphe_phi;      // 10*number of photoelectrons vs phi
		TH2F *ECpos[5];      // x vs y of track in EC
		TH1F *monitor[3][7]; // 0: each cut individually. 1: cuts are applied one after the other. 2: counting hits in CC,EC
 
		void write_and_close();    // Write out histos and close ROOT file
};

// %%%%%%%%%%%%%%%%%%%%%%%%
// Parameters and functions
// %%%%%%%%%%%%%%%%%%%%%%%%
class cpars
{
	public:
		cpars(string filename);
		~cpars(){;}
		
		// additional infos in the file: cuts informations
		vector<string> addInfos;
	
		// all cuts are stored in the file specified in the constructor
		double min_nphe[6];                            // NPHE: min number of photoelectrons / sector
		double p_ec_threshold;                         // ECTHR:  momentum as given by EC threshold in mV.
		
		double cc_match_mean_a[6];                     // CCMA: CC theta matching mean A: a + bx + cx2
		double cc_match_mean_b[6];                     // CCMB: CC theta matching mean B: a + bx + cx2
		double cc_match_mean_c[6];                     // CCMC: CC theta matching mean C: a + bx + cx2
		double cc_match_low[6][18];                    // CCMS#: CC theta matching lower limit for each sector, segment
		double CC_NSIGMAS[2];                          // CCNS: CC Matching number of sigmas for upper/lower theta curve
		
		double cc_timing_low[6][36];                   // CCTS#:   CC timing lower limit for each sector, pmt
		double CC_T_NSIGMAS;                           // CCTNS:   CC timing number of sigmas for lower limit
		
		double ecp_mean_a[6];                          // SFMA: sampling fraction mean A: a + bx + cx2 + dx3
		double ecp_mean_b[6];                          // SFMB: sampling fraction mean B: a + bx + cx2 + dx3
		double ecp_mean_c[6];                          // SFMC: sampling fraction mean C: a + bx + cx2 + dx3
		double ecp_mean_d[6];                          // SFMD: sampling fraction mean D: a + bx + cx2 + dx3
		double ecp_sigm_a[6];                          // SFSA: sampling fraction sigma A: a + bx + cx2 + dx3
		double ecp_sigm_b[6];                          // SFSB: sampling fraction sigma B: a + bx + cx2 + dx3
		double ecp_sigm_c[6];                          // SFSC: sampling fraction sigma C: a + bx + cx2 + dx3
		double ecp_sigm_d[6];                          // SFSD: sampling fraction sigma D: a + bx + cx2 + dx3
		double NSIGMAS[2];                             // SFNS: sampling fraction number of sigmas for upper/lower SF curve
		
		double umin, umax, vmax, wmax;                 // ECUVW: U,V,W cuts
		double ecop_vs_ecip_a[6], ecop_vs_ecip_b[6];   // ECIO: function ec_o/p vs ec_i/p is a straight line / sector
		double min_ecit[6];                            // INTO: min EC inner/total / sector 
		
		double Mean(     double p, int sector);
		double Sigma(    double p, int sector);
		double ecp_limit(double p, int sector, int which);
		
		double CC_Mean(     double segm, int sector);
		double CC_Sigma(    double segm, int sector);
		double CC_limit(    double segm, int sector, int which);
	
		void write_vars(string);
};

#endif

#ifndef UTILS_H
#define UTILS_H

#include <sstream>
inline string stringify(double x)
{
	ostringstream o;
	o << x;
	return o.str();
}

inline string stringify(int x)
{
	ostringstream o;
	o << x;
	return o.str();
}

#endif






