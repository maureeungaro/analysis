#ifndef VERTEX_CORR_SELECTION_H
#define VERTEX_CORR_SELECTION_H

// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "CLAS_Event.h"
#include "usage.h"
#include "definitions.h"
#include "common_info.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <string>
using namespace std;

class vertex_corr_selection : public cpars
{
	public:
		vertex_corr_selection(string filename) : cpars(filename)
		{
			beam_pos[0]  *= cm;
			beam_pos[1]  *= cm;
			vz_limits[0] *= cm;
			vz_limits[1] *= cm;
			delta_z      *= cm;
		}
		~vertex_corr_selection(){;}
		V3 e_v_corr;
		V3 p_v_corr;
		
		V3 vertex_corr(V3 v, V4 p);
	
		map<string, int> selection(particle, particle);
};


#endif
