#include "TH2.h"

#include <complex>
#include <string>
using namespace std;

// Six values of angular momentum l from zero to five.
// W binning:  1.1 to 2.0, bin size = .01 ==> 92  bins
// Q2 binning: 1 to 5, bin size = 0.05    ==> 101 bins
class poles
{
	public:
		poles(string);
	  ~poles(){;}
	  
	public:
		string model;
		complex<double> Sp[6][92][101];
		complex<double> Sm[6][92][101];
		complex<double> Ep[6][92][101];
		complex<double> Em[6][92][101];
		complex<double> Mp[6][92][101];
		complex<double> Mm[6][92][101];

};

class poles_histos
{
	public:
		poles_histos(poles*);
		poles_histos(string, string);
	  ~poles_histos(){;}

	public:
		// 6 angular momenta from 0 to 5, real/imaginary part
		TH2F* Sp[6][2];
		TH2F* Sm[6][2];
		TH2F* Ep[6][2];
		TH2F* Em[6][2];
		TH2F* Mp[6][2];
		TH2F* Mm[6][2];

	public:
		TH2F* get_pole(int, int, int, int);
};