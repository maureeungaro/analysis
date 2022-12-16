#include"parameters.h"


void change_sector()
{
	SECTOR ++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}

void print_all()
{
	PRINT = "png";
	if (GSIM) {
		PRINT = "_gsim.png";
	}

//	// cc theta
//	calc_all_cc_match();
//
//
//    CCMatch->set_print(PRINT);
//
//	// cc TIMING
//	calc_all_cc_timing();
//
//	// sampling
//	calc_all_ecp();

	// indivicual sectors plots
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		show_npeSingle();
//
//		show_cc_match();
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









