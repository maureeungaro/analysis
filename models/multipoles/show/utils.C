void switch_model()
{
	iMODEL++;
	if(iMODEL == NMODELS) iMODEL = 0;

	cout << " Model changed to: " << model[iMODEL] << endl;
}


void switch_L()
{
	ANGMOM++;
	if(ANGMOM == 6) ANGMOM = 1;

	cout << " Angular Momentum changed to: " << ANGMOM << endl;
}

void switch_plus_minus()
{
	if(PLUS_M == 1)
	{
		PLUS_M = -1;
		cout << " - Multipole selected. " << endl;
		return;
	}
	if(PLUS_M == -1)
	{
		PLUS_M = 1;
		cout << " + Multipole selected. " << endl;
		return;
	}
}


void print_all()
{
	PRINT = 1;
	for(int l=0; l<6; l++)
	{
		for(int m=0; m<NMODELS-1; m++)
		{
			iMODEL = m;
			for(int p=0; p<2; p++)
			{
				show(1);
				show(2);
				show(3);
				switch_plus_minus();
			}
		}
		switch_L();
	}
}













