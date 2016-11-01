#ifndef HISTOS_H
#define HISTOS_H

// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"
#include "common_info.h"

// C++ includes
#include <vector>
using namespace std;

class histos : public meson_chistos
{
	public:
		histos(string filename, int READ = 0) : meson_chistos(filename, READ){;}
		~histos(){;}
		
		void fill(CLAS_Event Ev, CLAS_Event_opts Opts);  // Fills histos according to cuts
};

#endif




