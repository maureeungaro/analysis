void change_q2()
{
	bins Bin;
	QQ++;
	if(QQ==Bin.Q2BIN) QQ=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}

void change_w()
{
	bins Bin;
	WW++;
	if(WW==Bin.WMBIN) WW=0;
	cout << endl << " W set to " << Bin.wm_center[WW] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}

void change_ph()
{
	bins Bin;
	PH++;
	if(PH==Bin.PHBIN) PH=0;
	cout << endl << " phi set to " << Bin.ph_center[PH] << "  Q2 set to " << Bin.q2_center[QQ] << endl << endl;
}

void change_what()
{
	WHAT++;
	if(WHAT==3) WHAT=0;
	cout << endl << " WHAT set to " << what[WHAT] << endl << endl;
}


void print_all_cs()
{
	bins Bin;
	PRINT=".png";
	for(int ww=0; ww<1; ww++)
	{
		WHAT = ww;
		for(int w=0; w<Bin.WMBIN; w++)
		{
			WW=w;
			for(int q=0; q<Bin.Q2BIN; q++)
			{
				QQ=q;
				show_phi_cs();
				show_theta_cs();
			}
		}
	}
}

void print_all_cs_W()
{
	bins Bin;
	PRINT=".png";
	WHAT = 0;
	for(int p=0; p<Bin.PHBIN; p++)
	{
		PH=p;
		for(int q=0; q<Bin.Q2BIN; q++)
		{
			QQ=q;
			show_cs_WQ();
		}
	}
}

void print_all_sf()
{
	bins Bin;
	PRINT=".png";
	for(int q=0; q<Bin.Q2BIN; q++)
	{
		QQ=q;
		show_sf(0);
		show_sf(1);
		show_sf(2);
	}
	
}

void print_all_sf_W()
{
	bins Bin;
	PRINT=".png";
	WHAT = 0;
	for(int q=0; q<Bin.Q2BIN; q++)
	{
		QQ=q;
		show_sf_W(0);
		show_sf_W(1);
		show_sf_W(2);
	}	
}









