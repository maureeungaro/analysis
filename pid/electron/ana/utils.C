#include"parameters.h"



void change_sector()
{
	SECTOR++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}

void print_all()
{
    cout << " > Printing all histograms " << endl;

	PRINT = DATA_PRINT;
	if (is_simulation) {
		PRINT = SIM_PRINT;
	}
    CCMatch->set_print(PRINT);

    // CC matching

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

    // CC matching show all sectors for all other cuts in one plot
    CCMatch->show_theta_vs_segm_all_sectors();

//
//	// cc TIMING
//	calc_all_cc_timing();
//
//	// sampling
//	calc_all_ecp();

	// indivicual sectors plots

//		SECTOR = s+1;
//		show_npeSingle();
//
//		show_theta_vs_segms();
//
//		show_phi_match();
//
//		show_cc_timing();
//		show_cc_timings();
//
//		show_ecthr();
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
//		// cc theta slices
//		for(int b=0; b<18; b++) {
//			CC_DrawFit(s, b);
//		}
//
//		// cc timing slices
//		for(int b=0; b<36; b++) {
//			CCT_DrawFit(s,b);
//		}
//
//		// sampling slices
//		for(int b=0; b<NDIV; b++) {
//			DrawFit(s, b);
//		}
//
//	}

//	// NPHE all sectors
//	show_npe();
//
//	// cc theta all sectors
//	show_theta_vs_segm_all_sectors();
//
//	// cc phi all sectors
//	show_phi_matchAll();
//
//	// cc timing all sectors
//	show_cc_timing_all_sectors();

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


	PRINT = "";
}









