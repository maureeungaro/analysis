double cut(double W, double x, int UD)
{
 double R_y = 100   - (W-1.08)*180;
 double R_x = 0.065 + (W-1.08)*0.08;
 
 double C_x = -.058 - (W-1.08)*0.03;
 double C_y = 180;

 double y0 = 180;
 double x0 = -0.06;
 double a  = 1.5 - (W-1.08)*1.6;
     
 double up1 =  C_y + R_y * sqrt( 1 -  pow( (x-C_x)/R_x, 2 )  ); 
 double dw1 =  C_y - R_y * sqrt( 1 -  pow( (x-C_x)/R_x, 2 )  ); 
 
 if(x>R_x+C_x) 
 {
  up1 = 180; 
  dw1 = 180; 
 }
 
 
 double up2 =  y0 + a/(x-x0);
 double dw2 =  y0 - a/(x-x0);
 
 double up, dw;
 up = up1<= up2 ? up2 : up1;
 dw = dw1<= dw2 ? dw1 : dw2;
  
 
 if(UD==1  ) return up;
 if(UD==-1 ) return dw; 
 
 return  180; 
}



double cut3(double W, double x)
{
 double a = 0.4 + 4.5*(W-1.08);
 double b = 0.01 + (W-1.08)*0.15;
  
 return b + a*x;   
}


init()
{
 TFile f("muana.root");

 double W;
 double x[100], y[3][100];
 for(int i=0; i<100; i++)
  x[i] = -0.04+i*0.0012;
 
  
 mmm[0] = (TH1F*) f.Get("dt_mm"); 
 mmm[1] = (TH1F*) f.Get("pdt_mm");     
 mmm[2] = (TH1F*) f.Get("p1dt_mm");   
 mmm[3] = (TH1F*) f.Get("p2dt_mm");         
 mmm[0]->GetXaxis()->SetNdivisions(506);
 mmm[0]->GetXaxis()->SetLabelSize(0.04);  
 mmm[0]->GetYaxis()->SetLabelSize(0.04);
 mmm[0]->GetXaxis()->SetLabelOffset(0.02);
 mmm[0]->GetYaxis()->SetLabelOffset(0.02);      
 mmm[0]->GetXaxis()->SetTitleSize(0.05);  
 mmm[0]->GetXaxis()->SetTitleOffset(1.4);
 mmm[0]->GetXaxis()->SetTitle("M_{x}^{ 2}           [GeV^{2}]"); 
 mmm[0]->SetDirectory(0);  
 mmm[1]->SetDirectory(0);  
 mmm[2]->SetDirectory(0);    
 mmm[3]->SetDirectory(0);    
 mmm[3]->SetLineColor(4);
  
 www[0] = (TH1F*) f.Get("dt_W"); 
 www[1] = (TH1F*) f.Get("pdt_W");     
 www[2] = (TH1F*) f.Get("p1dt_W");   
 www[3] = (TH1F*) f.Get("p2dt_W");         
 www[0]->GetXaxis()->SetNdivisions(506);
 www[0]->GetXaxis()->SetLabelSize(0.04);  
 www[0]->GetYaxis()->SetLabelSize(0.04);
 www[0]->GetXaxis()->SetLabelOffset(0.02);
 www[0]->GetYaxis()->SetLabelOffset(0.02);      
 www[0]->GetXaxis()->SetTitleSize(0.05);  
 www[0]->GetXaxis()->SetTitle("W                    [GeV]");
 www[0]->GetXaxis()->SetTitleOffset(1.4);
 www[0]->SetDirectory(0);  
 www[1]->SetDirectory(0);  
 www[2]->SetDirectory(0);    
 www[3]->SetDirectory(0);    
 
 www[3]->SetLineColor(4);
  
  
    
 for(int w=0; w<8; w++)
 {
  W = 1.105 + w*0.05;
  
  phmm[w][0] = (TH2F*) f.Get(Form("dt_dphi_mm_w%d",   w));  
  phmm[w][1] = (TH2F*) f.Get(Form("pdt_dphi_mm_w%d",  w));    
  phmm[w][2] = (TH2F*) f.Get(Form("p1dt_dphi_mm_w%d", w));  
  phmm[w][3] = (TH2F*) f.Get(Form("p2dt_dphi_mm_w%d", w));      
  phmm[w][0]->GetXaxis()->SetNdivisions(506);
  phmm[w][0]->GetXaxis()->SetLabelSize(0.07);  
  phmm[w][0]->GetYaxis()->SetLabelSize(0.07);
  phmm[w][0]->GetXaxis()->SetLabelOffset(-0.01);
  phmm[w][0]->GetYaxis()->SetLabelOffset(0.03);      
  phmm[w][0]->GetXaxis()->SetNdivisions(505);
  phmm[w][0]->GetXaxis()->SetTitle(Form("   W = %4.3f #pm 0.025   ", W));
  phmm[w][0]->GetXaxis()->SetTitleSize(0.07);    
  phmm[w][0]->SetDirectory(0);  
  phmm[w][1]->SetDirectory(0);  
  phmm[w][2]->SetDirectory(0);    
  phmm[w][3]->SetDirectory(0);         
  
  mm_dth[w][0] = (TH2F*) f.Get(Form("dt_mm_dth_w%d",   w));  
  mm_dth[w][1] = (TH2F*) f.Get(Form("pdt_mm_dth_w%d",  w));    
  mm_dth[w][2] = (TH2F*) f.Get(Form("p1dt_mm_dth_w%d", w));  
  mm_dth[w][3] = (TH2F*) f.Get(Form("p2dt_mm_dth_w%d", w));      
  
  mm_dth[w][0]->GetXaxis()->SetNdivisions(504);
  mm_dth[w][0]->GetXaxis()->SetLabelSize(0.062);  
  mm_dth[w][0]->GetYaxis()->SetLabelSize(0.062);
  mm_dth[w][0]->GetXaxis()->SetLabelOffset(0.01);
  mm_dth[w][0]->GetYaxis()->SetLabelOffset(0.03);      
  mm_dth[w][0]->GetXaxis()->SetTitle(Form("   W = %4.3f #pm 0.025   ", W));
  mm_dth[w][0]->GetXaxis()->SetTitleSize(0.07); 
  
  mm_dth[w][1]->GetXaxis()->SetNdivisions(504);
  mm_dth[w][1]->GetXaxis()->SetLabelSize(0.062);  
  mm_dth[w][1]->GetYaxis()->SetLabelSize(0.062);
  mm_dth[w][1]->GetXaxis()->SetLabelOffset(0.01);
  mm_dth[w][1]->GetYaxis()->SetLabelOffset(0.03);      
  mm_dth[w][1]->GetXaxis()->SetTitle(Form("   W = %4.3f #pm 0.025   ", W));
  mm_dth[w][1]->GetXaxis()->SetTitleSize(0.07); 
   
  mm_dth[w][0]->SetDirectory(0);  
  mm_dth[w][1]->SetDirectory(0);    
  mm_dth[w][2]->SetDirectory(0);    
  mm_dth[w][3]->SetDirectory(0);      
  
  mm_dthb[w][0] = (TH2F*) f.Get(Form("dt_mm_dthb_w%d",   w));
  mm_dthb[w][1] = (TH2F*) f.Get(Form("pdt_mm_dthb_w%d",  w));
  mm_dthb[w][2] = (TH2F*) f.Get(Form("p1dt_mm_dthb_w%d", w));  
  mm_dthb[w][3] = (TH2F*) f.Get(Form("p2dt_mm_dthb_w%d", w));        
  mm_dthb[w][2]->GetXaxis()->SetNdivisions(506);
  mm_dthb[w][2]->GetXaxis()->SetLabelSize(0.062);  
  mm_dthb[w][2]->GetYaxis()->SetLabelSize(0.062);
  mm_dthb[w][2]->GetXaxis()->SetLabelOffset(0.01);
  mm_dthb[w][2]->GetYaxis()->SetLabelOffset(0.02);      
  mm_dthb[w][2]->GetXaxis()->SetTitle(Form("W = %4.3f #pm 0.025  ", W));
  mm_dthb[w][2]->GetXaxis()->SetTitleSize(0.07);  
  mm_dthb[w][0]->SetDirectory(0);    
  mm_dthb[w][1]->SetDirectory(0);    
  mm_dthb[w][2]->SetDirectory(0);  
  mm_dthb[w][3]->SetDirectory(0);  
    
  dth[w][0] = (TH1F*) f.Get(Form("dt_dth_w%d",   w)); 
  dth[w][1] = (TH1F*) f.Get(Form("pdt_dth_w%d",  w));     
  dth[w][2] = (TH1F*) f.Get(Form("p1dt_dth_w%d", w));   
  dth[w][3] = (TH1F*) f.Get(Form("p2dt_dth_w%d", w));         
  dth[w][1]->GetXaxis()->SetNdivisions(506);
  dth[w][1]->GetXaxis()->SetLabelSize(0.06);  
  dth[w][1]->GetYaxis()->SetLabelSize(0.06);
  dth[w][1]->GetXaxis()->SetLabelOffset(0.02);
  dth[w][1]->GetYaxis()->SetLabelOffset(0.02);      
  dth[w][1]->GetXaxis()->SetTitle(Form("W = %4.3f #pm 0.025   ", W));
  dth[w][1]->GetXaxis()->SetTitleSize(0.07);  
  dth[w][0]->SetDirectory(0);  
  dth[w][1]->SetDirectory(0);  
  dth[w][2]->SetDirectory(0);    
  dth[w][3]->SetDirectory(0);    
     
  dthb[w][0] = (TH1F*) f.Get(Form("dt_dthb_w%d",   w));  
  dthb[w][1] = (TH1F*) f.Get(Form("pdt_dthb_w%d",  w));    
  dthb[w][2] = (TH1F*) f.Get(Form("p1dt_dthb_w%d", w));
  dthb[w][3] = (TH1F*) f.Get(Form("p2dt_dthb_w%d", w));      
  dthb[w][2]->GetXaxis()->SetNdivisions(506);
  dthb[w][2]->GetXaxis()->SetLabelSize(0.06);  
  dthb[w][2]->GetYaxis()->SetLabelSize(0.06);
  dthb[w][2]->GetXaxis()->SetLabelOffset(0.02);
  dthb[w][2]->GetYaxis()->SetLabelOffset(0.02);      
  dthb[w][2]->GetXaxis()->SetTitle(Form("W = %4.3f #pm 0.025  ", W));
  dthb[w][2]->GetXaxis()->SetTitleSize(0.07);  
  dthb[w][0]->SetDirectory(0);  
  dthb[w][1]->SetDirectory(0);    
  dthb[w][2]->SetDirectory(0);    
  dthb[w][3]->SetDirectory(0);    
       
  dth[w][2]->SetLineColor(2);
  dthb[w][3]->SetLineColor(2);  
  
  
  for(int i=0; i<100; i++)
  {
   y[0][i]    = cut(W,  x[i],   1);
   y[1][i]    = cut(W,  x[i],  -1);
   y[2][i]    = cut3(W, x[i]);
         
   Cutu[w]  = new TGraph(100, x, y[0]);
   Cutl[w]  = new TGraph(100, x, y[1]);
   Cut3[w]  = new TGraph(100, x, y[2]);
      
   Cutu[w]->SetLineWidth(2);
   Cutl[w]->SetLineWidth(2);   
   Cut3[w]->SetLineWidth(2);         
  }    
 }
       
}



