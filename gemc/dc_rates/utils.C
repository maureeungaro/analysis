void print_all()
{
	PRINT = "jpg";
	
	for(int s=0; s<NSECT; s++)
	{
		SECT = s;
		CONF = 0;
		show_dc_occ();
		CONF = 1;
		show_dc_occ();
	}
	PRINT = "";

}

void change_sector()
{
	SECT++;
	if(SECT == NSECT) SECT=0;
	cout << " Sector changed to: " << SECT << endl;
}

void change_energy()
{
	ENERGY++;
	if(ENERGY == NENERGY) ENERGY=0;
	cout << " Energy cut changed to: " << EDEP[ENERGY] << endl;
}

void change_conf()
{
	CONF++;
	if(CONF == NCONF) CONF=0;
	cout << " Configuration changed to: " << sconf[CONF] << endl;
}


void change_region()
{
	REG++;
	if(REG == NREG) REG=0;
	cout << " Region changed to: " << sreg[REG] << endl;
}


void change_zone()
{
	ZONE++;
	if(ZONE == NZONES) ZONE=0;
	cout << " Zone changed to: " << SZONE[ZONE] << endl;
}



void print_all()
{
	PRINT = "png";
	for(int c=0; c<NCONF; c++)
	{
		CONF = c;

		show_dc_occ();
		show_dc_int_occ();

		for(int r=0; r<NREG; r++)
		{
			REG = r;
			show_zvertex();
			
			for(int z=0; z<NZONES; z++)
			{
				ZONE = z;
				show_vertex();
			}
		}
	}
	PRINT = "";
}

