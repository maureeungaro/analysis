// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <fstream>
#include <cstdlib>
using namespace std;

// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"

// %%%%%%%%%%%%%%%%%
// mom_corr includes
// %%%%%%%%%%%%%%%%%
#include "histos.h"
#include "mom_corr.h"

// Usage
// ./e_mom_corr -PARS_FILE=emom_corr_pars.txt -ROOT_OUTPUT=corr.root /enkil/e1-6/p_pid/3116*.mu -BEAM_E=5.7542 -TARGET=proton -VERBOSITY=0

int main(int argc, char **argv)
{
	CLAS_Event_opts Opts;
	Opts.Set(argc, argv);
	string hd_msg        = Opts.args["LOG_MSG"].args + " e momentum correction >> " ;
	string hd_msg_scaler = Opts.args["LOG_MSG"].args + " Scaler Event" ;
	int max_n            = (int) Opts.args["N"].arg;
	int print            = (int) Opts.args["PRINT"].arg;
	int Nevents          = 1;
	cout  << hd_msg  << endl;
	double beam_e      = Opts.args["BEAM_E"].arg*GeV;
	double target_mass = pdg_mass(particle_id(Opts.args["TARGET"].args));
	cout  << hd_msg  << " Beam Energy: " << beam_e/GeV << " GeV" << endl;
	cout  << hd_msg  << " Target Mass: " << target_mass/GeV << " GeV" << endl;
	
	// if ROOT output name is given, write out the ROOT histos
	histos H(Opts.args["ROOT_OUTPUT"].args);
	
	mom_corr CORR(Opts.args["PARS_FILE"].args);
	ofstream ofile;
	
	int n_scaler_events  = 0;
	int n_physics_events = 0;
	
	// if an output name is given, write out the mu filtered file
	if(Opts.args["OUTPUT"].args != "none")
	{
		cout << hd_msg << " Opening Output File: " << Opts.args["OUTPUT"].args << endl;
		ofile.open(Opts.args["OUTPUT"].args.c_str(), ios::out | ios::binary);
	}
	
	for (unsigned int f=0; f<Opts.ifiles.size(); f++)
	{
		cout << hd_msg << " Opening Input File: " << Opts.ifiles[f] << endl;
		ifstream file(Opts.ifiles[f].c_str(), ios::in | ios::binary);
		if(!file)
		{
			cout << hd_msg << " " << Opts.ifiles[f] << " can't be opened" << endl;
			return 0;
		}

		while(!file.eof() && (Nevents <= max_n || max_n==0))
		{
			CLAS_Event Ev(&Opts);
			file >> Ev;
			if(file.eof()) break;

			// Scaler Event
			// Adding Infos
			if(Ev.Scaler.size())
			{
				n_scaler_events++;
				// Printing just the first scaler infos
				for(unsigned int i=0; i<Ev.Scaler[0].dataInfos.size() && n_scaler_events == 1; i++)
				{
					cout << Ev.Scaler[0].dataInfos[i] << endl;	
				}
				if(Ev.Scaler[0].dataInfos.size() && n_scaler_events == 1)
				{
					cout << endl;
					if(Opts.args["OUTPUT"].args != "none")
						cout << hd_msg << " The Following Cuts Information will be added: " << endl;
					
					Ev.Scaler[0].dataInfos.push_back("");	
					Ev.Scaler[0].dataInfos.push_back(" ###### Momentum Correction ######");
					for(unsigned int s=0; s<CORR.addInfos.size(); s++)
					{
						cout <<  CORR.addInfos[s] << endl;
						Ev.Scaler[0].dataInfos.push_back(CORR.addInfos[s]);
					}
				}
				if(Opts.args["OUTPUT"].args != "none")
					ofile << Ev;
			}
			// end of scaler event

			// Physics Event
			if(Ev.start_time > 0)
			{
				n_physics_events++;
				
				if( get_particles(Ev, "electron").size() < 1)
					continue;
				
				particle ele = get_particles(Ev, "electron").front();
				particle pro;
				particle pip;
				vector<particle> protons = get_particles(Ev, "proton");
				if(protons.size())
					pro = protons[0];
				vector<particle> pions = get_particles(Ev, "pi+");
				if(pions.size())
					pip = pions[0];

				
				// if ROOT output name is given, fill ROOT histos
				if(Opts.args["ROOT_OUTPUT"].args != "none")
					H.fill(ele, pro, pip, Opts, CORR);
				
				// Verbosity:
				if(Opts.args["VERBOSITY"].arg > 0)
				{
					cout << hd_msg << " Evn: " << Ev.Ev_n << endl;
					cout << hd_msg << " Originial e 4-vector: ";
					ele.p.l();
					cout << hd_msg << " Corrected e 4-vector: ";
					CORR.m_corr(ele.p).l();
				}
				
				// now correct all electron momentum
				if(Ev.particles[0].pid != 11)
				{
					cout << hd_msg << " Something is wrong with event " << Ev.Ev_n << ": first particle not an electron?" << endl;
					exit(0);
				}
				
				V4 e_corr =  CORR.m_corr(ele.p);
				
				Ev.particles[0].p.x = e_corr.x;
				Ev.particles[0].p.y = e_corr.y;
				Ev.particles[0].p.z = e_corr.z;
				Ev.particles[0].p.t = e_corr.t;
				
				if(Opts.args["OUTPUT"].args != "none")
					ofile << Ev;
			}
			// end of physics event
			if(Nevents++%print == 0) cout << hd_msg << Nevents -1 << " events analyzed." << endl;;
		}
	}
	if(Opts.args["ROOT_OUTPUT"].args != "none")
		H.write_and_close();
	
   cout << endl;
	return 1;
}














