void init_histos()
{


	
	
	
	
	
	
	
	
	// DC

	
	// EC
	ifstream IN("mysql/EC.dat");
	double dECt[N], dsECt[N];
	for(int i=0; i<N; i++)
		IN >> tmp >> run[i] >> dECt[i] >> dsECt[i] ;
	IN.close();
	
	sECt = new TGraph(N, run, dsECt);
	sECt->SetMarkerStyle(20);
	sECt->SetMarkerSize(0.6);
	sECt->SetMarkerColor(2);
	mECt = new TGraph(N, run, dECt);
	mECt->SetMarkerStyle(20);
	mECt->SetMarkerSize(0.6);
	mECt->SetMarkerColor(4);
	
	
	// CPU
	ifstream IN("mysql/CPU.dat");
	double dCPU[N], dcpu;
	for(int i=0; i<N; i++)
	{
		IN >> tmp >> run[i] >> dcpu;
		dCPU[i] = dcpu/3600;
	}
	IN.close();
	cpu = new TGraph(N, run, dCPU);
	cpu->SetMarkerStyle(20);
	cpu->SetMarkerSize(0.6);
	cpu->SetMarkerColor(4);
	
	
	// COUNTS
	ifstream IN("mysql/COUNTS.dat");
	double dTOT[N], dTB[N], dHB[N], dPR[N], dTH[N];
	double tb, hb, pr;
	for(int i=0; i<N; i++)
	{
		IN >> tmp >> run[i] >> hb >> tb >> pr >> dTOT[i];
		if(dTOT[i]!=0) dTB[i] = tb/dTOT[i];
		if(dTOT[i]!=0) dHB[i] = hb/dTOT[i];
		if(hb!=0)      dTH[i] = tb/hb;
		if(dTOT[i]!=0) dPR[i] = pr/dTOT[i];
	}
	
	IN.close();
	TB  = new TGraph(N, run, dTB);
	HB  = new TGraph(N, run, dHB);
	TH  = new TGraph(N, run, dTH);
	PR  = new TGraph(N, run, dPR);
	TOT = new TGraph(N, run, dTOT);
	
	TB->SetMarkerStyle(20);
	TB->SetMarkerSize(0.6);
	TB->SetMarkerColor(4);
	HB->SetMarkerStyle(20);
	HB->SetMarkerSize(0.6);
	HB->SetMarkerColor(4);
	TH->SetMarkerStyle(20);
	TH->SetMarkerSize(0.6);
	TH->SetMarkerColor(4);
	PR->SetMarkerStyle(20);
	PR->SetMarkerSize(0.6);
	PR->SetMarkerColor(4);
	TOT->SetMarkerStyle(20);
	TOT->SetMarkerSize(0.6);
	TOT->SetMarkerColor(4);
	
	// BEAM
	ifstream IN("mysql/BEAM.dat");
	double dXB[N], dsXB[N], dYB[N], dsYB[N];
	for(int i=0; i<N; i++)
		IN >> tmp >> run[i] >> dXB[i] >> dYB[i] >> dsXB[i] >> dsYB[i];
	IN.close();
	
	xb  = new TGraph(N, run, dXB);
	yb  = new TGraph(N, run, dYB);
	sxb = new TGraph(N, run, dsXB);
	syb = new TGraph(N, run, dsYB);
	
	xb->SetMarkerStyle(20);
	xb->SetMarkerSize(0.6);
	xb->SetMarkerColor(4);
	
	yb->SetMarkerStyle(20);
	yb->SetMarkerSize(0.6);
	yb->SetMarkerColor(4);
	
	sxb->SetMarkerStyle(20);
	sxb->SetMarkerSize(0.6);
	sxb->SetMarkerColor(2);
	
	syb->SetMarkerStyle(20);
	syb->SetMarkerSize(0.6);
	syb->SetMarkerColor(2);
	
	// MM
	ifstream IN("mysql/MM.dat");
	double  MM_p_pip[N],  MM_pip_pim[N],  MM_kp_lambda[N],  MM_kp_sigma[N];
	double sMM_p_pip[N], sMM_pip_pim[N], sMM_kp_lambda[N], sMM_kp_sigma[N];
	for(int i=0; i<N; i++)
		IN >> tmp >> run[i] >> MM_p_pip[i] >> sMM_p_pip[i] >> MM_pip_pim[i] >> sMM_pip_pim[i] >> MM_kp_lambda [i] >> sMM_kp_lambda[i] >> MM_kp_sigma[i] >> sMM_kp_sigma[i] ;
	IN.close();
	
	mm_p_pip     = new TGraph(N, run, MM_p_pip);
	mm_pip_pim   = new TGraph(N, run, MM_pip_pim);
	mm_kp_lambda = new TGraph(N, run, MM_kp_lambda);
	mm_kp_sigma  = new TGraph(N, run, MM_kp_sigma);
	
	smm_p_pip     = new TGraph(N, run, sMM_p_pip);
	smm_pip_pim   = new TGraph(N, run, sMM_pip_pim);
	smm_kp_lambda = new TGraph(N, run, sMM_kp_lambda);
	smm_kp_sigma  = new TGraph(N, run, sMM_kp_sigma);
	
	mm_p_pip->SetMarkerStyle(20);
	mm_p_pip->SetMarkerSize(0.6);
	mm_p_pip->SetMarkerColor(4);
	smm_p_pip->SetMarkerStyle(20);
	smm_p_pip->SetMarkerSize(0.6);
	smm_p_pip->SetMarkerColor(2);
	
	mm_pip_pim->SetMarkerStyle(20);
	mm_pip_pim->SetMarkerSize(0.6);
	mm_pip_pim->SetMarkerColor(4);
	smm_pip_pim->SetMarkerStyle(20);
	smm_pip_pim->SetMarkerSize(0.6);
	smm_pip_pim->SetMarkerColor(2);
	
	
	mm_kp_lambda->SetMarkerStyle(20);
	mm_kp_lambda->SetMarkerSize(0.6);
	mm_kp_lambda->SetMarkerColor(4);
	smm_kp_lambda->SetMarkerStyle(20);
	smm_kp_lambda->SetMarkerSize(0.6);
	smm_kp_lambda->SetMarkerColor(2);
	
	mm_kp_sigma->SetMarkerStyle(20);
	mm_kp_sigma->SetMarkerSize(0.6);
	mm_kp_sigma->SetMarkerColor(4);
	smm_kp_sigma->SetMarkerStyle(20);
	smm_kp_sigma->SetMarkerSize(0.6);
	smm_kp_sigma->SetMarkerColor(2);
	
	
}

void print_all()
{
	print=1;
	for(int i=1; i<7; i++) show_RF(i);
	
	show_DC(1);
	show_DC(2);
	
	for(int i=0; i<6; i++)
	{
		show_DC(10+i);
		show_DC(20+i);
	}
	
	show_CPU();
	show_EC();
	show_yelds();
	show_beam(1);
	show_beam(2);
	show_mm();
	
	
	print=0;
}






