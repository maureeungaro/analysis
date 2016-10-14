#ifndef MOM_CORR_H
#define MOM_CORR_H

// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"
#include "common_info.h"

// C++ includes
#include <string>
using namespace std;

class mom_corr : public cpars
{
	public:
		mom_corr(string filename) : cpars(filename){}
		~mom_corr(){;}

		V4 m_corr(V4 x);

};


#endif
