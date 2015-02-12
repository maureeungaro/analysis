#ifndef PROTON_PID_SELECTION_H
#define PROTON_PID_SELECTION_H

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

class p_pid_selection : public cpars
{
	public:
		p_pid_selection(string filename) : cpars(filename){;}
		~p_pid_selection(){;}
	
		map<string, int> selection(particle p, double tr_time);
};

#endif
