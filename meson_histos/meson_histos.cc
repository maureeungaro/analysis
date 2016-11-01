// C++ includes
#include <fstream>
using namespace std;

// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"

// kinematics includes
#include "histos.h"

// ./meson_histos -BEAM_E=5.754 -TARGET=proton -ROOT_OUTPUT=meson_histos.root /enkil/e1-6/nobh/*.mu

int main(int argc, char **argv)
{
	CLAS_Event_opts Opts;
	Opts.Set(argc, argv);
	string hd_msg        = Opts.args["LOG_MSG"].args + " Kinematics >> " ;
	
	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));
	cout  << hd_msg  << " CLAS Kinematics" << endl;
	cout  << hd_msg  << " Beam Energy: " << beam_e/GeV << " GeV" << endl;
	cout  << hd_msg  << " Target Mass: " << target_mass/GeV << " GeV" << endl;
	
	
	// if ROOT output name is given, write out the ROOT histos
	histos H(Opts.args["ROOT_OUTPUT"].args);
	
	for (unsigned int f=0; f<Opts.ifiles.size(); f++)
	{
		cout << hd_msg << " Opening Input File: " << Opts.ifiles[f] << endl;
		ifstream file(Opts.ifiles[f].c_str(), ios::in | ios::binary);
		if(!file)
		{
			cout << hd_msg << " " << Opts.ifiles[f] << " can't be opened" << endl;
			return 0;
		}

		int n_scaler_events = 0;
		while(!file.eof())
		{
			CLAS_Event Ev(&Opts);
			file >> Ev;
			if(file.eof()) break;

			// Scaler event
			// Printing just the first scaler infos
			if(Ev.Scaler.size() && Opts.args["VERBOSITY"].arg > 1)
			{
				n_scaler_events++;	
				for(unsigned int i=0; i<Ev.Scaler[0].dataInfos.size() && n_scaler_events == 1; i++)
				{
					cout << Ev.Scaler[0].dataInfos[i] << endl;	
				}
			}
			// end of scaler event

			// Physics Event
			if(Ev.start_time > 0)
			{
				// if ROOT output name is given, fill ROOT histos
				if(Opts.args["ROOT_OUTPUT"].args != "none")
					H.fill(Ev, Opts);
			}
			// end of physics event
		}
	}
	if(Opts.args["ROOT_OUTPUT"].args != "none")
		H.write_and_close();
	
   cout << endl;
	return 1;
}














