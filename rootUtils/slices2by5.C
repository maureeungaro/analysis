// slice[10][4]        10 slices, 4 histos each
//
// TITLES[50][300]     various titles 
// Conventions on TITLES:
// 0-1 axis titles
// 2 overall title
// 3 sub title
// 10 - 20 little label each, enabled with opt 0x8
//
// limits[5]            
// 0 minimum
// 1 maximum
// 2 multiplicative factor for minimum
// 3 multiplicative factor for maximum
// 4 zero line value

slices_2by5(TH1D *slice[10][4],  char TITLES[50][300], double limits[5], int opt)
{  
 gStyle->SetPadLeftMargin(0.22);
 gStyle->SetPadRightMargin(0.22);
 const int NPADS = 10; 
 gStyle->SetErrorX(0.);
 TLine *ZERO = new TLine(-10000, limits[4], 1000000, limits[4]);
 ZERO->SetLineWidth(2);
 ZERO->SetLineColor(2); 
 ZERO->SetLineStyle(2);  
   
 // ----- Pads creation and settings -------------------------------------------------------
 TCanvas *c2by5 = new TCanvas(TITLES[3], TITLES[3], 460, 530);
  c2by5->SetFrameFillColor(666);
// TCanvas *c2by5 = new TCanvas(TITLES[3], TITLES[3], 650, 750); 
 TPad    *padph[NPADS];
 double x_lim[3]   = {0.08, 0.50, 0.93};
 double y_lim1[10] = {0.77, 0.77, 0.61, 0.61, 0.45, 0.45, 0.29, 0.29, 0.07, 0.07};
 double y_lim2[10] = {0.93, 0.93, 0.77, 0.77, 0.61, 0.61, 0.45, 0.45, 0.29, 0.29};
  
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]= new TPad(Form("p%d", sl), Form("p%d", sl), x_lim[sl%2], y_lim1[sl], x_lim[sl%2 + 1], y_lim2[sl], 0);
  padph[sl]->Draw();
 }
 
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]->cd();
           gPad->SetRightMargin(0);
  if(sl%2) gPad->SetLeftMargin(0);
  if(sl%2) gPad->SetRightMargin(.14);
  if(sl>1) gPad->SetTopMargin(0);
           gPad->SetBottomMargin(0);
  if(sl>7) gPad->SetBottomMargin(.26);
  if(sl<2) gPad->SetTopMargin(.08);
  if(opt & GRIDS) gPad->SetGridx();
  if(opt & GRIDS) gPad->SetGridy();  
 }
 
 // ----- Histos limits --------------------------------------------------------------------
 double absolute_max = 0;
 for(int sl=0; sl<NPADS; sl++)
  absolute_max = absolute_max + slice[sl][0]->GetMaximum();
 absolute_max = limits[3]*absolute_max/10; 


 // If max (min) are 99, then set max (min) to the larger of max (lesser of min) of histos times the value passed by functions
 if(limits[1] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(absolute_max);
 if(limits[0] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum() - limits[2]*fabs(slice[sl][0]->GetMinimum()));
// if(limits[1] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(slice[sl][0]->GetMaximum() + limits[3]*fabs(slice[sl][0]->GetMaximum()));  


 if(limits[0] != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(limits[0]);
 if(limits[1] != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(limits[1]);

 
 
 // ----- Axis setting --------------------------------------------------------------------- 
 double Minx[NPADS];
 double Maxx[NPADS];
 double minx[NPADS];
 double maxx[NPADS];
 
 double Miny[NPADS];
 double Maxy[NPADS];
 double miny[NPADS];
 double maxy[NPADS];


 for(int i=0; i<NPADS; i++)
 {
  Minx[i] = slice[i][0]->GetXaxis()->GetXmin();
  Maxx[i] = slice[i][0]->GetXaxis()->GetXmax();

  minx[i] = slice[i][0]->GetXaxis()->GetXmin() + Maxx[i]*.01;
  maxx[i] = slice[i][0]->GetXaxis()->GetXmax()*.9;



  Miny[i] = slice[i][0]->GetMinimum();
  Maxy[i] = slice[i][0]->GetMaximum();

  miny[i] = slice[i][0]->GetMinimum() + Maxy[i]*.001;

//  miny[i] = slice[i][0]->GetMinimum() ;  
//  maxy[i] = slice[i][0]->GetMaximum();    

  maxy[i] = slice[i][0]->GetMaximum()*.9;    
  
  slice[i][0]->GetYaxis()->SetTickLength(0);
  slice[i][0]->GetXaxis()->SetTickLength(0); 

  slice[i][0]->GetYaxis()->SetLabelSize(0);
  slice[i][0]->GetXaxis()->SetLabelSize(0);   

  slice[i][0]->GetYaxis()->SetNdivisions(5);
  slice[i][0]->GetXaxis()->SetNdivisions(5); 

 // slice[i][0]->SetMarkerStyle(22);  
 // slice[i][0]->SetLineColor(1);       
 }
    
 TGaxis *xx1 = new TGaxis(Minx[8], Miny[8], Maxx[8], Miny[8], minx[8], maxx[8], 307);
 TGaxis *xx2 = new TGaxis(Minx[9], Miny[9], Maxx[9], Miny[9], minx[9], maxx[9], 307);  
 xx1->SetLabelSize(.08);
 xx1->SetLabelOffset(.06);
 xx2->SetLabelSize(.08);
 xx2->SetLabelOffset(.06);
 
 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%2 == 0)  yy[i]= new TGaxis(Minx[i], Miny[i], Minx[i], Maxy[i], miny[i], maxy[i], 305,"");
  if(i%2 != 0)  yy[i]= new TGaxis(Maxx[i], Miny[i], Maxx[i], Maxy[i], miny[i], maxy[i], 305,"+");

  if(i%2 == 0)  yy[i]->SetLabelOffset(.06);
  if(i%2 != 0)  yy[i]->SetLabelOffset(.13);
  if(i<8)       yy[i]->SetLabelSize(.12);
  if(i>=8)      yy[i]->SetLabelSize(.09);

  yy[i]->CenterLabels();
// yy[i]->SetLabelColor(666);

 }

 // ----- Single labels --------------------------------------------------------------------- 
 TLatex L[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L[i].SetTextColor(2);
  L[i].SetTextFont(13);
  if(i==0 || i==1 || i==4 || i==5 || i==8 || i==9)  L[i].SetTextSize(15);
  if(i==2 || i==3 || i==6 || i==7)                  L[i].SetTextSize(14);
  L[i].SetNDC();
 }

 // ----- Drawing --------------------------------------------------------------------------- 
 for(int sl=0;sl<NPADS;sl++)
 {
  padph[sl]->cd();
  padph[sl]->SetFillColor(666); 
// slice[sl][0]->Draw("C");
 slice[sl][0]->Draw("E");
  
  if(sl==8) xx1->Draw();
  if(sl==9) xx2->Draw();  
  
  yy[sl]->Draw();
  
  if(opt & ZEROLINE) ZERO->Draw("");
  if(opt & SUPER2) {
	  TF1 *b = (TF1*) slice[sl][1]->GetListOfFunctions();
	  b->Delete();
	  slice[sl][1]->Draw("Esame");}

  if(opt & SUPER3) slice[sl][2]->Draw("Bsame");

  slice[sl][0]->Draw("Esame");
  if(opt & SUPER2) slice[sl][1]->Draw("Esame");




  if(opt & SUPER4) slice[sl][3]->Draw("B");
    
  if(opt & L_TITLE)
  {
   if(sl == 0)                      L[sl].DrawLatex(0.36, 0.78, TITLES[sl+10]);
   if(sl == 1)                      L[sl].DrawLatex(0.24, 0.78, TITLES[sl+10]);
   if(sl>0 && sl%2 == 0 && sl != 8) L[sl].DrawLatex(0.38, 0.83, TITLES[sl+10]);
   if(sl>1 && sl%2 != 0 && sl != 9) L[sl].DrawLatex(0.26, 0.83, TITLES[sl+10]);
   if(sl == 8)                      L[sl].DrawLatex(0.38, 0.89, TITLES[sl+10]);
   if(sl == 9)                      L[sl].DrawLatex(0.26, 0.9,  TITLES[sl+10]);
  }
 }

 c2by5->cd();
 TGaxis *axisy = new TGaxis(.1, 0.88, 0.1, .8801, 0, 10, 1, "SNBU");
 axisy->SetTitle(TITLES[1]);
 axisy->SetTickSize(0);
 axisy->SetTitleSize(.034);
 axisy->SetGridLength(0);
 if(opt & Y_TITLE) axisy->Draw("B");

 TLatex title1;
 title1.SetTextColor(4);
 title1.SetTextFont(12);
 title1.SetTextSize(0.034);
 if(opt & BIG_TITLE)title1.DrawLatex(0.08, 0.95, TITLES[2]);

 title1.SetTextColor(4);
 if(opt & X_TITLE) title1.DrawLatex(0.4, 0.036, TITLES[0]);

 if(opt & PRINTING)
 {
  c2by5->Print(Form("%s.gif",TITLES[3]),"gif");
  c2by5->Close();
 }
}


