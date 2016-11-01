#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;


int main(int argc, char** argv)
{
	if(argc != 3)
	{
		cout << endl << " Usage: table <model> <option> " << endl << endl;
		cout << "    Models: " << endl;
		cout << "      dmt2001: " << endl;
		cout << "      maid2002: " << endl;
		cout << "      maid2003: " << endl;
		cout << "      maid2003woroper: " << endl;
		cout << "      maid2007: " << endl << endl;
		cout << "    Option: " << endl;
		cout << "      no:       don't include W=1.06" << endl;
		cout << "      exclurad: include W=1.06" << endl << endl ;
		exit(0);
	}
	
	// the following are file position pointers
	// obtain with commad head -N table | wc where N is line where (MeV) Re Im is on the table
	// or:
	// foreach m (S2+ S2- E2+ E2- M2+ M2-)
	//  echo $m
	//  grep -B100000 -A1 $m table/Q2_2.00_l_2.tbl | wc
   // end

	cout << endl << " Model : " << argv[1] << endl;

	
	int index_Slp, index_Slm;
	int index_Elp, index_Elm;
	int index_Mlp, index_Mlm ;

	if(strcmp(argv[1], "dmt2001") == 0)
	{
		index_Slp = 31339;  // N=439
		index_Slm = 38557;  // N=535
		index_Elp = 2467;   // N=55
		index_Elm = 9685;   // N=151
		index_Mlp = 16903;  // N=247
		index_Mlm = 24121;  // N=343
	}
 
	if(strcmp(argv[1], "maid2002") == 0)
	{
		index_Slp = 31637;  // N=445
		index_Slm = 38855;  // N=541
		index_Elp = 2765;   // N=61
		index_Elm = 9983;   // N=157
		index_Mlp = 17201;  // N=253
		index_Mlm = 24419;  // N=349
	}

	if(strcmp(argv[1], "maid2003") == 0 || strcmp(argv[1], "maid2003woroper") == 0)
	{
		index_Slp = 32922;  // N=456
		index_Slm = 40140;  // N=552
		index_Elp = 4050;   // N=72
		index_Elm = 11268;  // N=168
		index_Mlp = 18486;  // N=264
		index_Mlm = 25704;  // N=360
	}

	if(strcmp(argv[1], "maid2007") == 0)
	{
		index_Slp = 33065;  // N=458
		index_Slm = 40283;  // N=554
		index_Elp = 4193;   // N=74
		index_Elm = 11411;  // N=170
		index_Mlp = 18629;  // N=266
		index_Mlm = 25847;  // N=362
	}


	float Q2  = 0;
	float dQ2 = 0.05;
	float dW  = 0.01;
	float W;

	float Elp[6][2], Elm[6][2];
	float Mlp[6][2], Mlm[6][2];
	float Slp[6][2], Slm[6][2];

	float tmp2;

	char file[200];

	sprintf(file, "%s-PPpi.tbl", argv[1]);
	ofstream Ppi(file, ios::out);
	cout << endl << " Output table: " << file << endl << endl;

	for(int q=0; q<101; q++)
	{
		cout << " Adding Q2 = " << Q2 << " multipoles to table " << endl;
		for(int l=0; l<6; l++)
		{
			Slp[l][0] = Slp[l][1] = Slm[l][0] = Slm[l][1] = 0;
			Elp[l][0] = Elp[l][1] = Elm[l][0] = Elm[l][1] = 0;
			Mlp[l][0] = Mlp[l][1] = Mlm[l][0] = Mlm[l][1] = 0;
		}

		// Initializing multipoles and putting W=1.06 entry - if requested (exclurad option)
		if(strcmp(argv[2], "exclurad") == 0)
		{
			W = 1.06;    // Needed for exclurad - interpolation purposes
			Ppi.unsetf(ios::scientific | ios::uppercase | ios::showpos);
			Ppi.setf(ios::fixed );
			Ppi.precision(2);
			Ppi << "W=      " << W << " Q2=   " ;
			Ppi.precision(5);
			Ppi << Q2 << endl;
			Ppi.unsetf(ios::fixed);

			Ppi << "   S_{L+}" << endl;
			Ppi.setf(ios::scientific | ios::uppercase | ios::showpos);
			Ppi.precision(4);
			for(int L=0; L<3; L++) Ppi << " " << Slp[L][0] << " " << Slp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Slp[L][0] << " " << Slp[L][1] ;
			Ppi << endl;
			Ppi << "   S_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Slm[L][0] << " " << Slm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Slm[L][0] << " " << Slm[L][1] ;
			Ppi << endl;
			Ppi << "   E_{L+}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Elp[L][0] << " " << Elp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Elp[L][0] << " " << Elp[L][1] ;
			Ppi << endl;
			Ppi << "   E_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Elm[L][0] << " " << Elm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Elm[L][0] << " " << Elm[L][1] ;
			Ppi << endl;
			Ppi << "   M_{L+}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Mlp[L][0] << " " << Mlp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Mlp[L][0] << " " << Mlp[L][1] ;
			Ppi << endl;
			Ppi << "   M_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Mlm[L][0] << " " << Mlm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Mlm[L][0] << " " << Mlm[L][1] ;
			Ppi << endl;
		}

		W = 1.08;
		for(int w=0; w<93; w++)
		{
			for(int l=0; l<6; l++)
			{
				sprintf(file,"%s/Q2_%3.2f_l_%d.tbl", argv[1], Q2, l);
				if(q==100) sprintf(file,"%s/Q2_%1.0f_l_%d.tbl", argv[1], Q2, l);
				ifstream IN(file, ios::in);
				if(!IN)
				{
					cout << " file " << file << " could not be opened. Exiting..." << endl;
					exit(0);
				}

				// Sl+
				IN.seekg(index_Slp, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Slp[l][0] >> Slp[l][1];

				// Sl-
				IN.seekg(index_Slm, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Slm[l][0] >> Slm[l][1];

				// El+
				IN.seekg(index_Elp, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Elp[l][0] >> Elp[l][1];

				// El-
				IN.seekg(index_Elm, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Elm[l][0] >> Elm[l][1];

				// Ml+
				IN.seekg(index_Mlp, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Mlp[l][0] >> Mlp[l][1];

				// Ml-
				IN.seekg(index_Mlm, ios::beg);
				IN >> tmp2;
				while( fabs(tmp2 - W*1000) > .001 ) for(int d=0; d<9; d++) IN >> tmp2 ;
				IN >> Mlm[l][0] >> Mlm[l][1];

				IN.close();
			}

			Ppi.unsetf(ios::scientific | ios::uppercase | ios::showpos);
			Ppi.unsetf(ios::scientific | ios::uppercase | ios::showpos);
			Ppi.setf(ios::fixed );
			Ppi.precision(2);
			Ppi << "W=      " << W << " Q2=   " ;
			Ppi.precision(5);
			Ppi << Q2 << endl;
			Ppi.unsetf(ios::fixed);

			Ppi << "   S_{L+}" << endl;
			Ppi.setf(ios::scientific | ios::uppercase | ios::showpos);
			Ppi.precision(4);
			for(int L=0; L<3; L++) Ppi << " " << Slp[L][0] << " " << Slp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Slp[L][0] << " " << Slp[L][1] ;
			Ppi << endl;
			Ppi << "   S_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Slm[L][0] << " " << Slm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Slm[L][0] << " " << Slm[L][1] ;
			Ppi << endl;
			Ppi << "   E_{L+}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Elp[L][0] << " " << Elp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Elp[L][0] << " " << Elp[L][1] ;
			Ppi << endl;
			Ppi << "   E_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Elm[L][0] << " " << Elm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Elm[L][0] << " " << Elm[L][1] ;
			Ppi << endl;
			Ppi << "   M_{L+}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Mlp[L][0] << " " << Mlp[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Mlp[L][0] << " " << Mlp[L][1] ;
			Ppi << endl;
			Ppi << "   M_{L-}" << endl;
			for(int L=0; L<3; L++) Ppi << " " << Mlm[L][0] << " " << Mlm[L][1] ;
			Ppi << endl;
			for(int L=3; L<6; L++) Ppi << " " << Mlm[L][0] << " " << Mlm[L][1] ;
			Ppi << endl;

			W = W + dW;
		}
		Q2 = Q2 + dQ2;
	}
	Ppi.close();
	return 0;
}


