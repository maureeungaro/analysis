#include "options.h"

#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TControlBar.h"

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	vector<string> confs = {"bstNoShieldCtofNoShield",	"bstShieldCtof0.5mm", "bstShieldCtof1mm", "bstShieldCtof2mm", "bstShieldCtof3mm",	"bstShieldCtofNoShield"};

	anaOption analysis(confs);
}



