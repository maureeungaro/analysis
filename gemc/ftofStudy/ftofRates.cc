#include "options.h"

#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TControlBar.h"

#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	vector<string> confs = {"noShield",	"shield0.1" , "shield0.2", "shield0.5", "shield1.0"};
	
	anaOption analysis(confs);
}



