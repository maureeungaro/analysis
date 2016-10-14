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

class histos : public chistos
{
	public:
		histos(string filename, int READ = 0) : chistos(filename, READ){;}
		~histos(){;}
		
		void fill(V4 e, V4 P, CLAS_Event_opts Opts, map<string, int> passed);  // Fills histos according to cuts
};

#endif




