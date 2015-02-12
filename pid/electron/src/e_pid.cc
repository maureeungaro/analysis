// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <fstream>
using namespace std;


// %%%%%%%%%%%
// MU includes
// %%%%%%%%%%%
#include "CLAS_Event.h"
#include "usage.h"
#include "definitions.h"

// %%%%%%%%%%%%%
// epid includes
// %%%%%%%%%%%%%
#include "histos.h"
#include "e_pid_selection.h"


int main(int argc, char **argv) 
{
	CLAS_Event_opts Opts;
	Opts.Set(argc, argv);
	string hd_msg        = Opts.args["LOG_MSG"].args + " e_pid >> " ;
	string hd_msg_scaler = Opts.args["LOG_MSG"].args + " Scaler Event" ;
	int max_n            = (int) Opts.args["N"].arg;
	int print            = (int) Opts.args["PRINT"].arg;
	int Nevents          = 1;
	cout  << hd_msg  << " CLAS electron identification" << endl;
	
	// if ROOT output name is given, write out the ROOT histos
	histos H(Opts.args["ROOT_OUTPUT"].args);
	
	e_pid_selection SEL(Opts.args["PARS_FILE"].args);
	ofstream ofile;
	
	int n_scaler_events  = 0;
	int n_physics_events = 0;
	int n_e_candidates   = 0;
	int is_gsim          = 0;
	
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

			// Scaler event
			if(Ev.Scaler.size())
			{
				n_scaler_events++;
				if(Ev.Scaler[0].dataInfos.size()) 
					cout << endl << hd_msg << " File Information: " << endl;
				for(unsigned int i=0; i<Ev.Scaler[0].dataInfos.size(); i++)
				{
					cout << Ev.Scaler[0].dataInfos[i] << endl;
					if(Ev.Scaler[0].dataInfos[i].find("GSIM") != string::npos)
					{
						is_gsim = 1;
						cout << hd_msg << " This is a GSIM simulation." << endl;
					}
				}
				if(Ev.Scaler[0].dataInfos.size())
				{
					cout << endl;
					if(Opts.args["OUTPUT"].args != "none")
						cout << hd_msg << " The Following Cuts Information will be added: " << endl;
					
					Ev.Scaler[0].dataInfos.push_back("");	
					Ev.Scaler[0].dataInfos.push_back(" ###### Electron Identification Cuts: ######");	
					for(unsigned int s=0; s<SEL.addInfos.size(); s++)
					{
						cout <<  SEL.addInfos[s] << endl;
						Ev.Scaler[0].dataInfos.push_back(SEL.addInfos[s]);	
					}
				}
				if(Opts.args["OUTPUT"].args != "none")
					ofile << Ev;
			}
			// end of scaler event

			// Physics Event
			if(Ev.start_time != 0 || is_gsim)
			{
				n_physics_events++;
				// getting negative trigger
				particle candidate = get_trigger(Ev, -1);
				if(candidate.q == -1) // it means there is a reconstructed candidate
				{
					n_e_candidates++;
					map<string, int> passed = SEL.selection(candidate);
					
					// if ROOT output name is given, fill ROOT histos
					if(Opts.args["ROOT_OUTPUT"].args != "none")
						H.fill(passed, candidate);
					
					// Makes sure electron ID (count how many changes?)
					if(passed["PASSED"] == 1 && Opts.args["OUTPUT"].args != "none")
					{
						// reassigning PID to the trigger particle
						for(unsigned int i=0; i<Ev.particles.size(); i++)
							if(Ev.particles[i].type != 0)
							{
								if(Ev.particles[i].q == -1)
									Ev.particles[i].pid = electron_id;
							}
							
						ofile << Ev;
					}

					// Verbosity:
					if(Opts.args["VERBOSITY"].arg > 0)
					{
						cout << hd_msg << " Evn: " << Ev.Ev_n << endl;
						cout << " nphe:    " << passed["NPHE"]    << endl;
						cout << " ccmatch: " << passed["CCMATCH"] << endl;
						cout << " pmin:    " << passed["ECTHR"]   << endl;
						cout << " S.F.:    " << passed["ECP"]     << endl;
						cout << " EC U:    " << passed["EPOU"]    << endl;
						cout << " EC V:    " << passed["EPOV"]    << endl;
						cout << " EC W:    " << passed["EPOW"]    << endl;
						cout << "  UWV:    " << passed["ECUVW"]   << endl;
						cout << "  MIP:    " << passed["ECIO"]    << endl;
						cout << " SHAP:    " << passed["INTO"]    << endl;
						cout << "  TOT:    " << passed["PASSED"]  << endl;
					}
				}
				// if GSIM
				if(is_gsim && Opts.args["OUTPUT"].args != "none" && Ev.start_time > -1)
				{
					map<string, int> passed = SEL.selection(candidate);
					if(passed["PASSED"] == 0 &&  Ev.start_time>= 0)
					{
						int npart = Ev.particles.size();
						for(unsigned int i=npart; i>0; i--)
						{
// 								cout << i-1 << " " << Ev.particles[i-1].type << " " <<  Ev.particles[i-1].pid << " " <<  Ev.particles.size() << endl;
								if(Ev.particles[i-1].type == 1) Ev.particles.pop_back();
						}
						ofile << Ev;
					}
				}
				
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














