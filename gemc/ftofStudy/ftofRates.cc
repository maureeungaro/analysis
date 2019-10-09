#include "options.h"

#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TControlBar.h"

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	vector<string> confs = {"noShield"};
//	vector<string> confs = {"noShield",	"shield01" , "shield02", "shield05", "shield10"};

	anaOption analysis(confs);
}



