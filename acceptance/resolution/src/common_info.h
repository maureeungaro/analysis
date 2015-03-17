#ifndef ACC_INFO_H
#define ACC_INFO_H
 
// ROOT includes
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

// C++ includes
#include <string>
#include <iostream>
using namespace std;

// Common Classes with ROOT analysis macro

class reso_chistos
{
	public:
		// READ    =  0 will create the histos
		// READ    =  1 will read the histos
		reso_chistos(string filename, int READ=0);
	  ~reso_chistos(){;}
		
		TFile *output;

		// momentum, phi, theta per sector
		// phi vs momentum
		TH1D *mom[7];
		TH1D *phi[7];
		TH1D *the[7];

		// phi vs momentum
		TH2D *phiMom[7];
	
		void write_and_close();                 // Write out histos and close ROOT file
};
#endif








