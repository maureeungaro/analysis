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

	// NPHE
	show_npe();


   // CC THETA MATCH
	calc_all_cc_match();
	for(int s=0; s<6; s++)
	{
		SECTOR = s+1;
		show_cc_match();
		show_theta_vs_segms();
		for(int b=0; b<18; b++)
			CC_DrawFit(s, b);
		
	}

//   // CC PHI MATCH
//	show_phi_match();
//
//	
//   // CC TIMING
//	calc_all_cc_timing();
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		show_cc_timing();
//		show_cc_timings();
//	}	
//
//	// P MIN
//	show_ecthr();
//
//
//	// SAMPLING FRACTION
//	calc_all_ecp();
//	for(int s=0; s<6; s++)
//	{
//		SECTOR = s+1;
//		show_ecp();
//		show_ecps();
//		for(int b=0; b<NDIV; b++)
//			DrawFit(s, b);
//	}
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









