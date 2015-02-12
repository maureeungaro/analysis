// C++ includes
#include <fstream>
using namespace std;


// MU includes
#include "CLAS_Event.h"
#include "usage.h"
#include "utilities.h"

// epid includes
#include "histos.h"
#include "proton_pid_selection.h"


int main(int argc, char **argv)
{
	CLAS_Event_opts Opts;
	Opts.Set(argc, argv);
	string hd_msg        = Opts.args["LOG_MSG"].args + " proton_pid >> " ;
	string hd_msg_scaler = Opts.args["LOG_MSG"].args + " Scaler Event" ;
	int max_n            = (int) Opts.args["N"].arg;
	int print            = (int) Opts.args["PRINT"].arg;
	int Nevents          = 1;
	cout  << hd_msg  << " CLAS proton identification" << endl;
	
	// if ROOT output name is given, write out the ROOT histos
	histos H(Opts.args["ROOT_OUTPUT"].args);
	
	p_pid_selection SEL(Opts.args["PARS_FILE"].args);
	ofstream ofile;
	
	int n_scaler_events  = 0;
	int n_physics_events = 0;
	int n_p_candidates   = 0;
	int n_good_p         = 0;
	int p_recovered      = 0;
	int p_thrown         = 0;
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
				// Printing just the first scaler infos
				for(unsigned int i=0; i<Ev.Scaler[0].dataInfos.size() && n_scaler_events == 1; i++)
				{
					cout << Ev.Scaler[0].dataInfos[i] << endl;	
					if(Ev.Scaler[0].dataInfos[i].find("GSIM") != string::npos)
					{
						is_gsim = 1;
						cout << hd_msg << " This is a GSIM simulation." << endl;
					}
				}
				if(Ev.Scaler[0].dataInfos.size() && n_scaler_events == 1)
				{
					cout << endl;
					if(Opts.args["OUTPUT"].args != "none")
						cout << hd_msg << " The Following Cuts Information will be added: " << endl;
					
					Ev.Scaler[0].dataInfos.push_back("");	
					Ev.Scaler[0].dataInfos.push_back(" ###### Proton Identification Cuts: ######");	
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
			if(Ev.start_time > 0 || is_gsim)
			{
				n_physics_events++;
				int is_there_good_proton = 0;
				for(unsigned int p=0; p<Ev.particles.size(); p++)
				{
					if(Ev.particles[p].q > 0 && Ev.particles[p].type != 0)
					{
						n_p_candidates++;
						 
						map<string, int> passed = SEL.selection(Ev.particles[p], Ev.start_time);
						
						// if ROOT output name is given, fill ROOT histos
						if(Opts.args["ROOT_OUTPUT"].args != "none")
							H.fill(passed, Ev.particles[p], Ev.start_time);
					
						if(passed["PASSED"] == 1)
						{
							is_there_good_proton = 1;
							Ev.particles[p].pid  = proton_id;
							n_good_p++;
						}
						
						// Verbosity:
						if(Opts.args["VERBOSITY"].arg > 0)
						{
							cout << hd_msg << " Evn: " << Ev.Ev_n << endl;
							cout << hd_msg << " Originial ID: " << Ev.particles[p].pid <<  "  PASSED: " << passed["PASSED"] << endl;
						}
						
						if(is_there_good_proton  && Ev.particles[p].pid != 2212) p_recovered++;
						if(!is_there_good_proton && Ev.particles[p].pid == 2212) p_thrown++;
						
						// if it's not a proton but was labeled as proton, change id to 99
						if(passed["PASSED"] == 0)
							if(Ev.particles[p].pid == proton_id) Ev.particles[p].pid = 99;
						
					}
				}
				if(is_there_good_proton && Opts.args["OUTPUT"].args != "none")
					ofile << Ev;
				
				// if GSIM
				if(is_gsim && !is_there_good_proton && Opts.args["OUTPUT"].args != "none" && Ev.start_time > -1)
				{
					int npart = Ev.particles.size();
					for(unsigned int i=npart; i>0; i--)
					{
						// cout << i-1 << " " << Ev.particles[i-1].type << " " <<  Ev.particles[i-1].pid << " " <<  Ev.particles.size() << endl;
						if(Ev.particles[i-1].type == 1) Ev.particles.pop_back();
					}
					ofile << Ev;
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














