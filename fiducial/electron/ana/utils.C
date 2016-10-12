void init()
{

	for(int s=0; s<7; s++)
		for(int pl=0; pl<5; pl++)
	{
		y_left[s][pl]  = NULL;
		y_right[s][pl] = NULL;
	}
	
	double x_lims[5]  = { 30,   100,   150,  200,   200};
	
	for(int s=0; s<7; s++)
		for(int pl=0; pl<5; pl++)
	{
			// don't consider EC
		if(pl == 3)
			continue;
			
		left_para[s][pl] = new TF1(Form("left_para_s%d_pl%d", s+1, pl+1), parabole,      -x_lims[pl], Pars.YMIN[pl][s], 3);
		rite_para[s][pl] = new TF1(Form("rite_para_s%d_pl%d", s+1, pl+1), parabole, Pars.YMIN[pl][s],       x_lims[pl], 3);
		left_para[s][pl]->SetLineColor(kRed+3);
		rite_para[s][pl]->SetLineColor(kRed+3);
		left_para[s][pl]->SetLineStyle(1);
		rite_para[s][pl]->SetLineStyle(1);
		left_para[s][pl]->SetLineWidth(2);
		rite_para[s][pl]->SetLineWidth(2);
	
	
		double a_left, a_rite;
			
		if(pl==0)
		{
			a_left = Pars.XMIN[pl] - Pars.r1_b_left[s]*Pars.YMIN[pl][s] - Pars.r1_c_left[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			a_rite = Pars.XMIN[pl] - Pars.r1_b_rite[s]*Pars.YMIN[pl][s] - Pars.r1_c_rite[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			left_para[s][pl]->SetParameter( 1, Pars.r1_b_left[s]);
			rite_para[s][pl]->SetParameter( 1, Pars.r1_b_rite[s]);
			left_para[s][pl]->SetParameter( 2, Pars.r1_c_left[s]);
			rite_para[s][pl]->SetParameter( 2, Pars.r1_c_rite[s]);
		}
	
		if(pl==1)
		{
			a_left = Pars.XMIN[pl] - Pars.r2_b_left[s]*Pars.YMIN[pl][s] - Pars.r2_c_left[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			a_rite = Pars.XMIN[pl] - Pars.r2_b_rite[s]*Pars.YMIN[pl][s] - Pars.r2_c_rite[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			left_para[s][pl]->SetParameter( 1, Pars.r2_b_left[s]);
			rite_para[s][pl]->SetParameter( 1, Pars.r2_b_rite[s]);
			left_para[s][pl]->SetParameter( 2, Pars.r2_c_left[s]);
			rite_para[s][pl]->SetParameter( 2, Pars.r2_c_rite[s]);
		}

		if(pl==2)
		{
			a_left = Pars.XMIN[pl] - Pars.r3_b_left[s]*Pars.YMIN[pl][s] - Pars.r3_c_left[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			a_rite = Pars.XMIN[pl] - Pars.r3_b_rite[s]*Pars.YMIN[pl][s] - Pars.r3_c_rite[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			left_para[s][pl]->SetParameter( 1, Pars.r3_b_left[s]);
			rite_para[s][pl]->SetParameter( 1, Pars.r3_b_rite[s]);
			left_para[s][pl]->SetParameter( 2, Pars.r3_c_left[s]);
			rite_para[s][pl]->SetParameter( 2, Pars.r3_c_rite[s]);
		}
	
		if(pl==4)
		{
			a_left = Pars.XMIN[pl] - Pars.sc_b_left[s]*Pars.YMIN[pl][s] - Pars.sc_c_left[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			a_rite = Pars.XMIN[pl] - Pars.sc_b_rite[s]*Pars.YMIN[pl][s] - Pars.sc_c_rite[s]*Pars.YMIN[pl][s]*Pars.YMIN[pl][s];
			left_para[s][pl]->SetParameter( 1, Pars.sc_b_left[s]);
			rite_para[s][pl]->SetParameter( 1, Pars.sc_b_rite[s]);
			left_para[s][pl]->SetParameter( 2, Pars.sc_c_left[s]);
			rite_para[s][pl]->SetParameter( 2, Pars.sc_c_rite[s]);
		}
			
		left_para[s][pl]->SetParameter( 0, a_left);
		rite_para[s][pl]->SetParameter( 0, a_rite);
	}
	
	for(int s=0; s<6; s++)
		for(int c=0; c<10; c++)
			for(int w=0; w<2; w++)
				for(int pl=0; pl<2; pl++)
				{
					wire_axial[s][pl][c][w] = NULL;
					wire_stereo[s][pl][c][w] = NULL;
				}
	
	for(int c=0; c<Pars.r1_axial_limits.size()/3; c++)
	{
		int s =  Pars.r1_axial_limits[c*3] - 1;
		wire_axial[s][0][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[0], x_lims[0]);
		wire_axial[s][0][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[0], x_lims[0]);
		wire_axial[s][0][c][0]->SetParameter(0, Pars.r1_axial_limits[c*3+1]);
		wire_axial[s][0][c][1]->SetParameter(0, Pars.r1_axial_limits[c*3+2]);
		wire_axial[s][0][c][0]->SetLineWidth(1);
		wire_axial[s][0][c][0]->SetLineStyle(9);
		wire_axial[s][0][c][1]->SetLineWidth(1);
		wire_axial[s][0][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.r2_axial_limits.size()/3; c++)
	{
		int s =  Pars.r2_axial_limits[c*3] - 1;
		wire_axial[s][1][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[1], x_lims[1]);
		wire_axial[s][1][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[1], x_lims[1]);
		wire_axial[s][1][c][0]->SetParameter(0, Pars.r2_axial_limits[c*3+1]);
		wire_axial[s][1][c][1]->SetParameter(0, Pars.r2_axial_limits[c*3+2]);
		wire_axial[s][1][c][0]->SetLineWidth(1);
		wire_axial[s][1][c][0]->SetLineStyle(9);
		wire_axial[s][1][c][1]->SetLineWidth(1);
		wire_axial[s][1][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.r3_axial_limits.size()/3; c++)
	{
		int s =  Pars.r3_axial_limits[c*3] - 1;
		wire_axial[s][2][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[2], x_lims[2]);
		wire_axial[s][2][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[2], x_lims[2]);
		wire_axial[s][2][c][0]->SetParameter(0, Pars.r3_axial_limits[c*3+1]);
		wire_axial[s][2][c][1]->SetParameter(0, Pars.r3_axial_limits[c*3+2]);
		wire_axial[s][2][c][0]->SetLineWidth(1);
		wire_axial[s][2][c][0]->SetLineStyle(9);
		wire_axial[s][2][c][1]->SetLineWidth(1);
		wire_axial[s][2][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.sc_axial_limits.size()/3; c++)
	{
		int s =  Pars.sc_axial_limits[c*3] - 1;
		wire_axial[s][3][c][0] = new TF1(Form("wire_axial_lower_r1_%d", c), "pol0", -x_lims[3], x_lims[3]);
		wire_axial[s][3][c][1] = new TF1(Form("wire_axial_upper_r1_%d", c), "pol0", -x_lims[3], x_lims[3]);
		wire_axial[s][3][c][0]->SetParameter(0, Pars.sc_axial_limits[c*3+1]);
		wire_axial[s][3][c][1]->SetParameter(0, Pars.sc_axial_limits[c*3+2]);
		wire_axial[s][3][c][0]->SetLineWidth(1);
		wire_axial[s][3][c][0]->SetLineStyle(9);
		wire_axial[s][3][c][1]->SetLineWidth(1);
		wire_axial[s][3][c][1]->SetLineStyle(9);
	}


	for(int c=0; c<Pars.r1_stereo_limits.size()/3; c++)
	{
		int s =  Pars.r1_stereo_limits[c*3] - 1;
		wire_stereo[s][0][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[0], x_lims[0]);
		wire_stereo[s][0][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[0], x_lims[0]);
		wire_stereo[s][0][c][0]->SetParameter(0, Pars.r1_stereo_limits[c*3+1]);
		wire_stereo[s][0][c][1]->SetParameter(0, Pars.r1_stereo_limits[c*3+2]);
		wire_stereo[s][0][c][0]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][0][c][1]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][0][c][0]->SetLineWidth(1);
		wire_stereo[s][0][c][0]->SetLineStyle(9);
		wire_stereo[s][0][c][1]->SetLineWidth(1);
		wire_stereo[s][0][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.r2_stereo_limits.size()/3; c++)
	{
		int s =  Pars.r2_stereo_limits[c*3] - 1;
		wire_stereo[s][1][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[1], x_lims[1]);
		wire_stereo[s][1][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[1], x_lims[1]);
		wire_stereo[s][1][c][0]->SetParameter(0, Pars.r2_stereo_limits[c*3+1]);
		wire_stereo[s][1][c][1]->SetParameter(0, Pars.r2_stereo_limits[c*3+2]);
		wire_stereo[s][1][c][0]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][1][c][1]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][1][c][0]->SetLineWidth(1);
		wire_stereo[s][1][c][0]->SetLineStyle(9);
		wire_stereo[s][1][c][1]->SetLineWidth(1);
		wire_stereo[s][1][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.r3_stereo_limits.size()/3; c++)
	{
		int s =  Pars.r3_stereo_limits[c*3] - 1;
		wire_stereo[s][2][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[2], x_lims[2]);
		wire_stereo[s][2][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[2], x_lims[2]);
		wire_stereo[s][2][c][0]->SetParameter(0, Pars.r3_stereo_limits[c*3+1]);
		wire_stereo[s][2][c][1]->SetParameter(0, Pars.r3_stereo_limits[c*3+2]);
		wire_stereo[s][2][c][0]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][2][c][1]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][2][c][0]->SetLineWidth(1);
		wire_stereo[s][2][c][0]->SetLineStyle(9);
		wire_stereo[s][2][c][1]->SetLineWidth(1);
		wire_stereo[s][2][c][1]->SetLineStyle(9);
	}

	for(int c=0; c<Pars.sc_stereo_limits.size()/3; c++)
	{
		int s =  Pars.sc_stereo_limits[c*3] - 1;
		wire_stereo[s][3][c][0] = new TF1(Form("wire_stereo_lower_r1_%d", c), "pol1", -x_lims[3], x_lims[3]);
		wire_stereo[s][3][c][1] = new TF1(Form("wire_stereo_upper_r1_%d", c), "pol1", -x_lims[3], x_lims[3]);
		wire_stereo[s][3][c][0]->SetParameter(0, Pars.sc_stereo_limits[c*3+1]);
		wire_stereo[s][3][c][1]->SetParameter(0, Pars.sc_stereo_limits[c*3+2]);
		wire_stereo[s][3][c][0]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][3][c][1]->SetParameter(1, -Pars.stereo_angle_slope);
		wire_stereo[s][3][c][0]->SetLineWidth(1);
		wire_stereo[s][3][c][0]->SetLineStyle(9);
		wire_stereo[s][3][c][1]->SetLineWidth(1);
		wire_stereo[s][3][c][1]->SetLineStyle(9);
	}







}


void draw_limits()
{
	int s  = SECTOR - 1;

	if(PLANE == 1)
	{
		for(int c=0; c<Pars.r1_axial_limits.size()/3; c++)
		{
			if(s == Pars.r1_axial_limits[c*3]-1)
			{
				wire_axial[s][0][c][0]->Draw("same");
				wire_axial[s][0][c][1]->Draw("same");
			}
		}
		for(int c=0; c<Pars.r1_stereo_limits.size()/3; c++)
		{
			if(s == Pars.r1_stereo_limits[c*3]-1)
			{
				wire_stereo[s][0][c][0]->Draw("same");
				wire_stereo[s][0][c][1]->Draw("same");
			}
		}
	}

	if(PLANE == 2)
	{
		for(int c=0; c<Pars.r2_axial_limits.size()/3; c++)
		{
			if(s == Pars.r2_axial_limits[c*3]-1)
			{
				wire_axial[s][1][c][0]->Draw("same");
				wire_axial[s][1][c][1]->Draw("same");
			}
		}
		for(int c=0; c<Pars.r2_stereo_limits.size()/3; c++)
		{
			if(s == Pars.r2_stereo_limits[c*3]-1)
			{
				wire_stereo[s][1][c][0]->Draw("same");
				wire_stereo[s][1][c][1]->Draw("same");
			}
		}
	}

	if(PLANE == 3)
	{
		for(int c=0; c<Pars.r3_axial_limits.size()/3; c++)
		{
			if(s == Pars.r3_axial_limits[c*3]-1)
			{
				wire_axial[s][2][c][0]->Draw("same");
				wire_axial[s][2][c][1]->Draw("same");
			}
		}
		for(int c=0; c<Pars.r3_stereo_limits.size()/3; c++)
		{
			if(s == Pars.r3_stereo_limits[c*3]-1)
			{
				wire_stereo[s][2][c][0]->Draw("same");
				wire_stereo[s][2][c][1]->Draw("same");
			}
		}
	}

	if(PLANE == 5)
	{
		for(int c=0; c<Pars.sc_axial_limits.size()/3; c++)
		{
			if(s == Pars.sc_axial_limits[c*3]-1)
			{
				wire_axial[s][3][c][0]->Draw("same");
				wire_axial[s][3][c][1]->Draw("same");
			}
		}
		for(int c=0; c<Pars.sc_stereo_limits.size()/3; c++)
		{
			if(s == Pars.sc_stereo_limits[c*3]-1)
			{
				wire_stereo[s][3][c][0]->Draw("same");
				wire_stereo[s][3][c][1]->Draw("same");
			}
		}
	}



}


void change_mom()
{
	MOM++;
	if(MOM == H.NDIV_P+1) MOM = 1;
	
	cout << " Momentum Bin set to: " << MOM << endl;
}

void change_sector()
{
	SECTOR++;
	if(SECTOR == 7) SECTOR = 1;
	
	cout << " Sector set to: " << SECTOR << endl;
}

void change_plane()
{
	PLANE++;
	if(PLANE == 6) PLANE = 1;
	
	cout << " Plane set to: " << PLANE << endl;
}

void switch_logz()
{
	if(LOGZ==0) LOGZ = 1;
	else if(LOGZ==1) LOGZ = 0;
}


void print_all()
{
	PRINT = "png";
	for(int s=0; s<6; s++)
	{
		SECTOR = s+1;
		for(int p=0; p<H.NDIV_P; p++)
		{
			MOM = p+1;
//			show_phi_theta();
			show_phis();
//			for(int pl=1; pl<6; pl++)
//			{
//				if(pl == 4) continue;
//				PLANE = pl;
//				show_plane();
//			}
		}
//		show_phi_thetas(0);  // all phi vs theta before
//		show_phi_thetas(1);
//		for(int pl=1; pl<6; pl++)
//		{
//			if(pl == 4) continue;
//			PLANE = pl;
//			show_planes();
//			show_integrated_plane();
/*			for(int y=2; y<12; y++)
			{
				DrawFit(s, pl-1, y);
			}*/
//		}
	}
	PRINT = "";
}

TGraph *fidcut(int s, double p, int which)
{
	const int npoints = 160;
	double x[npoints];
	double y[npoints];
	for(int i=0; i<npoints; i++)
	{
		x[i] = 10 + i/3.0;
		
		if(which ==  1 )  y[i] =  Pars.dphi(s, p, x[i]);
		if(which == -1 )  y[i] = -Pars.dphi(s, p, x[i]);
		if(y[i] == 0) x[i] = Pars.theta_cut(s, p);
	}
 
	TGraph *a = new TGraph(npoints, x, y);
	a->SetLineWidth(2);
	a->SetLineColor(kRed+3);
	a->SetLineStyle(9);

	return a;
}




