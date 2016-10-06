#ifndef HISTOS_H
#define HISTOS_H


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
#include <vector>
using namespace std;

class histos : public chistos
{
	public:
		histos(string filename, int READ = 0) : chistos(filename, READ){;}
		~histos(){;}
		
		map<string, int> alloth;   // all other cuts are on
		map<string, int> othneg;   // all other negative cuts are on
		
		void fill(map<string, int>, particle, particle, V3, V3);  // Fills histos according to cuts
		void set_vars(map<string, int>);                          // Sets the parameters map
};

#endif




