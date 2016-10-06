void change_sector()
{
	SECTOR ++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}


void calc_all()
{
	for(int s=0; s<6; s++)
	{
		SECTOR = s+1;
		calc_2d(H.dt_momz[s], H.dt_mom[s]);
	}
	Pars.write_vars("new_pars.txt");
}

void print_all()
{
	PRINT = "png";

	if(dt_mean[5] == 0)
		calc_all();
		
	for(int s=0; s<6; s++)
	{
		SECTOR = s+1;
		show_dt_vs_mom();
		for(int b=0; b<NDIV; b++)
			DrawFit(s, b);
		
		show_mass_beta();
	}
	
	show_dt_vs_moms();	
	show_betaAll();
	
	PRINT = "";
}

