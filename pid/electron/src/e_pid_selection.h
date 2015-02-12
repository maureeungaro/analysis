#ifndef E_PID_SELECTION_H
#define E_PID_SELECTION_H


// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"
#include "common_info.h"

// C++ includes
#include <string>
using namespace std;

class e_pid_selection : public cpars
{
	public:
		e_pid_selection(string filename) : cpars(filename)
		{
			p_ec_threshold *= GeV;
			umin *= cm;
			umax *= cm;
			vmax *= cm;
			wmax *= cm;
		}
		
		~e_pid_selection(){;}

		map<string, int> selection(particle p);
};

#endif
