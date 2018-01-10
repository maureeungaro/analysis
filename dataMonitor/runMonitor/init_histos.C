void init_histos()
{
 char tmp[100];
 double run[N];

 // RF
 double dRF[N], dsRF[N], dRFP[N], dsRFP[N], dRFpp[N], dsRFpp[N], dRFpm[N], dsRFpm[N], dRFstpp[N], dsRFstpp[N], dRFstpm[N], dsRFstpm[N];
 ifstream IN("mysql/RF.dat");
 for(int i=0; i<N; i++)
  IN >> tmp >> run[i] >> dRF[i] >> dsRF[i] >> dRFP[i] >> dsRFP[i] >> dRFpp[i] >> dsRFpp[i] >> dRFpm[i] >>  dsRFpm[i] >> dRFstpp[i] >> dsRFstpp[i] >> dRFstpm[i] >> dsRFstpm[i]  ;

 IN.close();

 RF      = new TGraph(N, run, dRF);
 sRF     = new TGraph(N, run, dsRF);
 RFP     = new TGraph(N, run, dRFP);
 sRFP    = new TGraph(N, run, dsRFP);
 RFpp    = new TGraph(N, run, dRFpp);
 sRFpp   = new TGraph(N, run, dsRFpp);
 RFpm    = new TGraph(N, run, dRFpm);
 sRFpm   = new TGraph(N, run, dsRFpm);
 RFstpp  = new TGraph(N, run, dRFstpp);
 sRFstpp = new TGraph(N, run, dsRFstpp);
 RFstpm  = new TGraph(N, run, dRFstpm);
 sRFstpm = new TGraph(N, run, dsRFstpm);

 RF->SetMarkerStyle(20);
 sRF->SetMarkerStyle(20);
 RFP->SetMarkerStyle(20);
 sRFP->SetMarkerStyle(20);
 RFpp->SetMarkerStyle(20);
 sRFpp->SetMarkerStyle(20);
 RFpm->SetMarkerStyle(20);
 sRFpm->SetMarkerStyle(20);
 RFstpp->SetMarkerStyle(20);
 sRFstpp->SetMarkerStyle(20);
 RFstpm->SetMarkerStyle(20);
 sRFstpm->SetMarkerStyle(20);

 RF->SetMarkerSize(0.6);
 sRF->SetMarkerSize(0.6);
 RFP->SetMarkerSize(0.6);
 sRFP->SetMarkerSize(0.6);
 RFpp->SetMarkerSize(0.6);
 sRFpp->SetMarkerSize(0.6);
 RFpm->SetMarkerSize(0.6);
 sRFpm->SetMarkerSize(0.6);
 RFstpp->SetMarkerSize(0.6);
 sRFstpp->SetMarkerSize(0.6);
 RFstpm->SetMarkerSize(0.6);
 sRFstpm->SetMarkerSize(0.6);



 RF->SetMarkerColor(4);
 sRF->SetMarkerColor(2);

 RFP->SetMarkerColor(4);
 sRFP->SetMarkerColor(2);

 RFpp->SetMarkerColor(4);
 sRFpp->SetMarkerColor(2);

 RFpm->SetMarkerColor(4);
 sRFpm->SetMarkerColor(2);

 RFstpp->SetMarkerColor(4);
 sRFstpp->SetMarkerColor(2);

 RFstpm->SetMarkerColor(4);
 sRFstpm->SetMarkerColor(2);

 RF->GetYaxis()->SetTitleColor(4);
 RF->GetYaxis()->SetTitle("nanoseconds");
 RF->GetXaxis()->SetNdivisions(8);

 RFP->GetYaxis()->SetTitleColor(4);
 RFP->GetYaxis()->SetTitle("nanoseconds");
 RFP->GetXaxis()->SetNdivisions(6);

 RFpp->GetYaxis()->SetTitleColor(4);
 RFpp->GetYaxis()->SetTitle("nanoseconds");
 RFpp->GetXaxis()->SetNdivisions(6);

 RFpm->GetYaxis()->SetTitleColor(4);
 RFpm->GetYaxis()->SetTitle("nanoseconds");
 RFpm->GetXaxis()->SetNdivisions(6);

 RFstpp->GetYaxis()->SetTitleColor(4);
 RFstpp->GetYaxis()->SetTitle("nanoseconds");
 RFstpp->GetXaxis()->SetNdivisions(6);

 RFstpm->GetYaxis()->SetTitleColor(4);
 RFstpm->GetYaxis()->SetTitle("nanoseconds");
 RFstpm->GetXaxis()->SetNdivisions(6);









// DC
 double DC_SA[6][N];
 double DC_MA[6][N];
 double DC_M[6][6][N];
 double DC_S[6][6][N];
 double Tmp[N];

 int DC_col[6] = {2,5,6,7,1,4};

 ifstream IN("mysql/DC.dat");
 for(int i=0; i<N; i++)
 {
  IN >> tmp >> run[i];
  for(int l=0; l<6; l++) IN >> DC_MA[l][i];
  for(int l=0; l<6; l++) IN >> DC_SA[l][i];
 }
 IN.close();
 for(int l=0; l<6; l++)
 {
  DC_res_mean[l] = new TGraph(N, run, DC_MA[l]);
  DC_res_mean[l]->SetMarkerStyle(20);
  DC_res_mean[l]->SetMarkerSize(0.6);
  DC_res_mean[l]->SetMarkerColor(DC_col[l]);
  DC_res_mean[l]->SetFillColor(18);
  DC_res_mean[l]->SetLineColor(18);
  DC_res_sigm[l] = new TGraph(N, run, DC_SA[l]);
  DC_res_sigm[l]->SetMarkerStyle(20);
  DC_res_sigm[l]->SetMarkerSize(0.6);
  DC_res_sigm[l]->SetMarkerColor(DC_col[l]);
  DC_res_sigm[l]->SetFillColor(18);
  DC_res_sigm[l]->SetLineColor(18);
 }


 ifstream IN("mysql/DCd.dat");
 for(int i=0; i<N; i++)
 {
  IN >> tmp >> run[i];
  for(int l=0; l<6; l++)
  {
   for(int s=0; s<6; s++) IN >> DC_M[s][l][i];
   for(int s=0; s<6; s++) IN >> DC_S[s][l][i];
  }
 }
 IN.close();

 for(int s=0; s<6; s++)
  for(int l=0; l<6; l++)
  {
   for(int i=0; i<N; i++) Tmp[i] = DC_M[s][l][i];
   DC_mean[s][l] = new TGraph(N, run, Tmp);
   DC_mean[s][l]->SetMarkerStyle(20);
   DC_mean[s][l]->SetMarkerSize(0.6);
   DC_mean[s][l]->SetMarkerColor(DC_col[l]);
   DC_mean[s][l]->SetFillColor(18);
   DC_mean[s][l]->SetLineColor(18);

   for(int i=0; i<N; i++) Tmp[i] = DC_S[s][l][i];
   DC_sigm[s][l] = new TGraph(N, run, Tmp);
   DC_sigm[s][l]->SetMarkerStyle(20);
   DC_sigm[s][l]->SetMarkerSize(0.6);
   DC_sigm[s][l]->SetMarkerColor(DC_col[l]);
   DC_sigm[s][l]->SetFillColor(18);
   DC_sigm[s][l]->SetLineColor(18);
  }


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






