// slice[15][4]        10 slices, 4 histos each
//
// TITLES[50][300]     various titles 
// Conventions on TITLES:
// 0-1 axis titles
// 2 overall title
// 3 sub title
// 10 - 25 little label each, enabled with opt 0x8
//
// limits[4]            
// 0 minimum
// 1 maximum
// 2 multiplicative factor for minimum
// 3 multiplicative factor for maximum
// 4 zero line value

slices_3by5(TH1D *slice[15][10],  char TITLES[50][300], double limits[5], int opt, int highl[15])
{  
gStyle->SetErrorX(0.);
 const int NPADS = 15; 
 
 TLine *ZERO = new TLine(-10000, limits[4], 1000000, limits[4]);
 ZERO->SetLineWidth(1);
 ZERO->SetLineColor(1); 
 ZERO->SetLineStyle(2);  
   
 // ----- Pads creation and settings -------------------------------------------------------
 TCanvas *c3by5 = new TCanvas(TITLES[3], TITLES[3], 530, 600);
 TPad    *padph[NPADS];
 double x_lim[4]   = {0.07, 0.38, 0.64, 0.94};
 double y_lim1[15] = {0.77, 0.77, 0.77, 0.61, 0.61, 0.61, 0.45, 0.45, 0.45, 0.29, 0.29, 0.29, 0.07, 0.07, 0.07};
 double y_lim2[15] = {0.93, 0.93, 0.93, 0.77, 0.77, 0.77, 0.61, 0.61, 0.61, 0.45, 0.45, 0.45, 0.29, 0.29, 0.29}; 

  
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]= new TPad(Form("p%d", sl), Form("p%d", sl), x_lim[sl%3], y_lim1[sl], x_lim[sl%3 + 1], y_lim2[sl], 0);
  padph[sl]->Draw();
 }
 
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]->cd();
              gPad->SetLeftMargin(0.2); 
              gPad->SetRightMargin(0);
  if(sl%3)    gPad->SetLeftMargin(0);
  if(sl%3==2) gPad->SetRightMargin(.18);
  if(sl>1)    gPad->SetTopMargin(0);
              gPad->SetBottomMargin(0);
  if(sl>11)   gPad->SetBottomMargin(.26);
  if(sl<3)    gPad->SetTopMargin(.08);

  if(opt & GRIDS) gPad->SetGridx();
  if(opt & GRIDS) gPad->SetGridy();  

  gPad->SetFrameFillColor(19);
  if(highl[sl]) gPad->SetFrameFillColor(10);
 }
 
 // ----- Histos limits --------------------------------------------------------------------
 // If max and min are 99, then set max and min to histo default times values passed by functions

 double absolute_max = 0;
 double absolute_min = 0;




 for(int sl=0; sl<NPADS; sl++)
  absolute_max = absolute_max + slice[sl][0]->GetMaximum();
 absolute_max = limits[3]*absolute_max/15; 

for(int sl=0; sl<NPADS; sl++)
  absolute_min = absolute_min + slice[sl][0]->GetMinimum();
 absolute_min = limits[4]*absolute_min/15; 



 if(limits[1] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(absolute_max);
 if(limits[0] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum() - limits[2]*fabs(slice[sl][0]->GetMinimum()));


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

  minx[i] = slice[i][0]->GetXaxis()->GetXmin() + Maxx[i]*.2;
  maxx[i] = slice[i][0]->GetXaxis()->GetXmax()*.8;
 
  Miny[i] = slice[i][0]->GetMinimum();
  Maxy[i] = slice[i][0]->GetMaximum();

  miny[i] = slice[i][0]->GetMinimum() + Maxy[i]*.01;
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

    
 TGaxis *xx1 = new TGaxis(Minx[12], Miny[12], Maxx[12], Miny[12], minx[12], maxx[12], 307);
 TGaxis *xx2 = new TGaxis(Minx[13], Miny[13], Maxx[13], Miny[13], minx[13], maxx[13], 307);
 TGaxis *xx3 = new TGaxis(Minx[14], Miny[14], Maxx[14], Miny[14], minx[14], maxx[14], 307);   
 xx1->SetLabelSize(.09);
 xx1->SetLabelOffset(.06);
 xx2->SetLabelSize(.09);
 xx2->SetLabelOffset(.06);
 xx3->SetLabelSize(.09);
 xx3->SetLabelOffset(.06);
 
 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%3 == 0)  yy[i]= new TGaxis(Minx[i], Miny[i], Minx[i], Maxy[i], miny[i], maxy[i], 506,"");
  if(i%3 == 2)  yy[i]= new TGaxis(Maxx[i], Miny[i], Maxx[i], Maxy[i], miny[i], maxy[i], 506,"+");
  
  if(i%3 == 1)  yy[i]= new TGaxis(Maxx[i], Miny[i], Maxx[i], Maxy[i], miny[i], maxy[i], 506,"+"); // dummy one

  yy[i]->SetNdivisions(5);
  yy[i]->SetLabelSize(.11);
  yy[i]->SetLabelOffset(.11);
  if(i%3 == 0) yy[i]->SetLabelOffset(.07);
  if(i>11)   yy[i]->SetLabelSize(.08);    

//  yy[i]->CenterLabels();
 }

 // ----- Single labels --------------------------------------------------------------------- 
 TLatex La[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  La[i].SetTextColor(2);
  La[i].SetTextFont(13);
  La[i].SetTextSize(15);
  La[i].SetNDC();
 }

 // ----- Drawing --------------------------------------------------------------------------- 
 for(int sl=0;sl<NPADS;sl++)
 {
  padph[sl]->cd();   
//  slice[sl][0]->Draw("HISTC");
  slice[sl][0]->Draw("9PE");
  
  if(sl==12) xx1->Draw();
  if(sl==13) xx2->Draw();
  if(sl==14) xx3->Draw();    
  if(sl%3==0 || sl%3==2) yy[sl]->Draw();
  
  if(opt & ZEROLINE) ZERO->Draw("");
  if(opt & SUPER2) {
	  TF1 *b = (TF1*) slice[sl][1]->GetListOfFunctions();
	  b->Delete();
	  
	  slice[sl][1]->Draw("sameCL");
          }
  if(opt & L_TITLE)
  {
   if(sl==2)                  La[sl].DrawLatex(0.26, 0.78, TITLES[sl+10]);
   else if(sl==13)            La[sl].DrawLatex(0.26, 0.88, TITLES[sl+10]);   
   else if(sl==1)             La[sl].DrawLatex(0.30, 0.78, TITLES[sl+10]);   
   else if(sl==5 || sl==8)    La[sl].DrawLatex(0.22, 0.82, TITLES[sl+10]);
   else if(sl%3 == 1 && sl>2) La[sl].DrawLatex(0.26, 0.84, TITLES[sl+10]); 
   else if(sl==12)            La[sl].DrawLatex(0.36, 0.88, TITLES[sl+10]);
   else if(sl%3 == 0 && sl>2) La[sl].DrawLatex(0.36, 0.84, TITLES[sl+10]);    
   else if(sl==11)            La[sl].DrawLatex(0.22, 0.82, TITLES[sl+10]); 
   else if(sl==14)            La[sl].DrawLatex(0.22, 0.88, TITLES[sl+10]);               
   
   else                       La[sl].DrawLatex(0.36, 0.78, TITLES[sl+10]);
  }
 }

 c3by5->cd();
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
  c3by5->Print(Form("%s.gif",TITLES[3]),"gif");
  c3by5->Close();
 }
}


