// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "CLAS_Event.h"
#include "definitions.h"
#include "usage.h"
#include "bin.h"
#include "generator.h"


// %%%%%%%%%%%
// ROOT includes
// %%%%%%%%%%%
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"


// %%%%%%%%%%%%%
// CLAS includes
// %%%%%%%%%%%%%
extern "C"
{
#include <ntypes.h>
#include <bostypes.h>
#include <pid.h>
#include <dc.h>
#include <sc.h>
#include <vertex.h>
#include <utility.h>
#include <map_manager.h>

#include <trk.h>              // This is to rebuild TDPL and TBLA
#include <trk_run_control.h>
int dc_begin_run_(int *);
void dc_set_def_();
void trk_set_def_();
void trk_swim2pln_(float pln[8], float vins[9], float vect[9],
						 float tintp[7], float *sint, float *zangle,
		             float *minstep, float *maxstep, float *lmax,
					    int *l_int, int *stepnumber);
//
//   Inputs  :
//             pln     - plane (see sdaswim.inc: sda_pln)
//                     note: if pln(8)>pln(7) plane is assumed to be
//                           a plane, otherwise it is assumed to be a
//                           cylinder.  also note that this does not take
//                           take into account R1 DC where the "plane"
//                           is made up of both a plane & a cylinder.  The
//                           user of this routine is presumed to know which
//                           half he is looking for.
//             vins(9) - Starting values {x,y,z,Px/P,Py/P,Pz/P,P,m,Q}
//             zangle  - replaces tcl variables trk_zangle
//             minstep - replaces tcl variable trk_zstep(1)
//             maxstep - replaces tcl variable trk_zstep(2)
//             lmax    - maximum track length before giving up
//             stepnumber - used to determine if "first" step
//
//   Outputs : vect(9) -last starting value of step before intercept (same def as vins)
//             tintp(7)- track intersection with plane
//                      {x,y,z,Px/P,Py/P,Pz/P,L}
//                      where L is the track length from vins to tintp
//             l_int =0 if no intercept found, 1 otherwise
//             sint    - step size from last starting point to intercept
//   Controls:
//
}





int main(int argc, char **argv)
{
	CLAS_Event_opts Opts;
	Opts.Set(argc, argv);

	bins Bin;

	pi0_generator pi0s(Bin, 5.7542);
	
	int max_n      = (int) Opts.args["N"].arg ;
	int print      = (int) Opts.args["PRINT"].arg;
	string hd_msg  = Opts.args["LOG_MSG"].args + " pi0 generator >> " ;


	int   Nevents   = 1;
	while(Nevents <= max_n )
	{




		if(Nevents++%print == 0) cout << hd_msg << Nevents -1 << " events generated." << endl;;
	}

}


















