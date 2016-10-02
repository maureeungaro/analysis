void init()
{
	for(int s=0; s<7; s++)
	{
		no_cc_or_ec[s]   = H.monitor[2][s]->GetBinContent(1);
		hit_cc[s]        = H.monitor[2][s]->GetBinContent(2);
		hit_ec[s]        = H.monitor[2][s]->GetBinContent(3);
		hit_cc_and_ec[s] = H.monitor[2][s]->GetBinContent(4);
		
		if(s<6)
		{
			cc_match_mean[s] = NULL;
			cc_timing_low[s] = NULL;
		}
	}
}


void change_sector()
{
	SECTOR ++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}

void print_all()
{
	PRINT = "png";

//	// cc theta
//	calc_all_cc_match();
//
//	// cc TIMING
//	calc_all_cc_timing();
//
//	// sampling
//	calc_all_ecp();

//	// indivicual sectors plots
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

	// NPHE all sectors
	show_npe();

	// cc theta all sectors
	show_theta_vs_segm_all_sectors();

	// cc phi all sectors
	show_phi_matchAll();

	// cc timing all sectors
	show_cc_timing_all_sectors();

	// P MIN all sectors
	show_ecthrAll();


//	
//	// TRACK POSITION IN EC
//	show_uvw(ECu);
//	show_uvw(ECv);
//	show_uvw(ECw);
//	show_ecyx();
//	
//	// MIP cut: E OUT vs E IN
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		show_EoEi();
//	}
//	show_EoEi_all();
//	
//	// Shower Shape cut:  E IN / E TOT
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		show_EinEtot();
//	}
//	
//	show_summary();
//	
//	Pars.write_vars(pars_file);

	PRINT = "";
}









