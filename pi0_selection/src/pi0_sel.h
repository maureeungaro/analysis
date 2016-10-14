#ifndef PI0_SELECTION_H
#define PI0_SELECTION_H

// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"
#include "common_info.h"

// C++ includes
#include <string>
using namespace std;

class pi0_selection : public cpars
{
	public:
		pi0_selection(string filename) : cpars(filename)
		{
			phiMin  *= degree;
			phiMax  *= degree;
			dth1Min *= degree;
			dth1Max *= degree;
		}
		~pi0_selection(){;}
	
		map<string, int> selection(V4, V4, CLAS_Event_opts);
};


#endif
