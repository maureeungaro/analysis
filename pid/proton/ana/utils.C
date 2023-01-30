#include"parameters.h"

void activate_PRINT()
{
    if (is_simulation) {
        PRINT = SIM_PRINT;
    } else {
        PRINT = DATA_PRINT;
    }
    CCMatch->set_print(PRINT);
    ECMatch->set_print(PRINT);
}


void switch_print() {
    if ( PRINT == "none") {
        activate_PRINT();
    } else {
        PRINT = "none";
    }

    cout << " > PRINT set to  " << PRINT << endl;
}


void change_sector()
{
    SECTOR++;
    if(SECTOR == 7) SECTOR = 1;

    cout << " Sector set to: " << SECTOR << endl;
}


//void calc_all_parameters()
//{
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		calc_2d(H->dt_momz[s], H->dt_mom[s]);
//	}
//	Pars->write_vars("new_Pars->txt");
//}

void print_all()
{
    activate_PRINT();

//	if(dt_mean[5] == 0) {
//        calc_all();
//    }
//
//	for(int s=0; s<6; s++) {
//		SECTOR = s+1;
//		show_dt_vs_mom();
//		for(int b=0; b<NDIV; b++)
//			DrawFit(s, b);
//
//		show_mass_beta();
//	}
	
//	show_dt_vs_moms();
//	show_betaAll();
	
	PRINT = "none";
}

