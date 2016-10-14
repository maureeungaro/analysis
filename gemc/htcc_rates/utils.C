

void changeNpheCut()
{
	IPHE++;
	if(IPHE == NNPHE) IPHE=0;
	cout << " nphe cut changed to: " << SNPHE[IPHE] << endl;
}

void change_conf()
{
	CONF++;
	if(CONF == NCONF) CONF=0;
	cout << " Configuration changed to: " << sconf[CONF] << endl;
}



void print_all()
{
	PRINT = "png";
	for(int c=0; c<NCONF; c++)
	{
		CONF = c;

		showNpheRates();

		
	}
	PRINT = "";
}

