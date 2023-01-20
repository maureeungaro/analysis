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


void print_cc_match()
{
    activate_PRINT();

    // This will also print the pars plots
    CCMatch->calc_all_cc_match();

    for (int s = 0; s < 6; s++) {
        SECTOR = s+1;
        // show all cuts for this sector
        CCMatch->show_cc_theta_match_all_cuts(SECTOR);

        // show cc match for this sector
        CCMatch->show_cc_theta_match(SECTOR);

        // cc theta slices
        for(int b=0; b<18; b++) {
            CCMatch->CC_DrawFit_ThetaSlice(s, b);
        }

    }

    // theta matching all sectors for calorimeter cuts in one plot
    CCMatch->show_theta_vs_segm_all_sectors();

    // phi match
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_phi_match(SECTOR);
    }
    CCMatch->show_phi_match_all_sectors();


    // time match all
    CCMatch->calc_all_cc_time_match();

    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_cc_timing(SECTOR);
        CCMatch->show_cc_timings(SECTOR);

        // cc timing slices
        for(int b=0; b<36; b++) {
            CCMatch->CCT_DrawFit_TimeSlice(s,b);
        }
    }

    // cc timing all sectors
    CCMatch->show_cc_timing_all_sectors();


    // npe
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        CCMatch->show_npe(SECTOR);
    }
    CCMatch->show_npe_all_sectors();


}


void print_ec_match()
{
    // thresholds
    for (int s = 0; s < 6; s++) {
        SECTOR = s + 1;
        ECMatch->show_ecthr(SECTOR);
    }

    ECMatch->show_ecthr_all_sectors();

}

void print_all()
{
    cout << " > Printing all histograms " << endl;

	PRINT = DATA_PRINT;
	if (is_simulation) {
		PRINT = SIM_PRINT;
	}

    print_cc_match();

    print_ec_match();

//
//	// sampling
//	calc_all_ecp();



//
//		show_ecp();
//		show_ecps();
//
//		show_uvw(H.ECu);
//		show_uvw(H.ECv);
//		show_uvw(H.ECw);
//
//		show_EoEi();
//
//		show_EinEtot();
//

//

//
//		// sampling slices
//		for(int b=0; b<NDIV; b++) {
//			DrawFit(s, b);
//		}
//
//	}




//	// P MIN all sectors
//	show_ecthrAll();
//
//	// sampling fraction all sectors
//	show_ecp_all_sectors();
//
//	// uvw all sectors
//	show_uvwAll(H.ECu);
//	show_uvwAll(H.ECv);
//	show_uvwAll(H.ECw);
//
//	// y vs x
//	show_ecyx();
//
//	// eout vs ein
//	show_EoEi_all();
//
//	// ein / etot
//	show_EinEtotAll();
//
//
//	// summary
//	show_summary();


	PRINT = "none";
}









