#ifndef FIDUCIAL_CUT_H
#define FIDUCIAL_CUT_H

// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"
#include "common_info.h"

// C++ includes
#include <string>
using namespace std;

class fiducial_cut : public cpars
{
	public:
		fiducial_cut(string filename) : cpars(filename)
		{
		}
		~fiducial_cut(){;}
		
		map<string, int> selection(particle);
};


#endif
