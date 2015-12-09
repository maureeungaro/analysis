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

slices_5by2(TH1D *slice[10][4],  char TITLES[50][300], double limits[5], int opt)
{  
 const int NPADS = 10; 
 gStyle->SetErrorX(0.);
 TLine *ZERO = new TLine(-10000, limits[4], 1000000, limits[4]);
 ZERO->SetLineWidth(2);
 ZERO->SetLineColor(31); 
 ZERO->SetLineStyle(2);  
   
 // ----- Pads creation and settings -------------------------------------------------------
 TCanvas *c2by5 = new TCanvas(TITLES[3], TITLES[3], 1000, 700);

 TPad    *padph[NPADS];
 double y_lim[3]   = {0.12, 0.54, 0.92};

 double x_lim1[10] = {0.05, 0.23, 0.41, 0.59, 0.77, 0.05, 0.23, 0.41, 0.59, 0.77};
 double x_lim2[10] = {0.23, 0.41, 0.59, 0.77, 0.97, 0.23, 0.41, 0.59, 0.77, 0.97};
  



 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]= new TPad(Form("p%d", sl), Form("p%d", sl), x_lim1[sl], y_lim[((int)sl)/5], x_lim2[sl], y_lim[((int)sl)/5+1], 0);
  padph[sl]->Draw();
 }
 
 for(int sl=0; sl<5; sl++)
 {
  padph[sl]->cd();
  gPad->SetRightMargin(0);
  gPad->SetLeftMargin(0);
  if(sl==4)gPad->SetRightMargin(.01);
  gPad->SetBottomMargin(0.2);
//  gPad->SetBottomMargin(0.23);
  gPad->SetTopMargin(.0);
  if(opt & GRIDS) gPad->SetGridx();
  if(opt & GRIDS) gPad->SetGridy();  
 }
 for(int sl=5; sl<NPADS; sl++)
 {
  padph[sl]->cd();
  gPad->SetRightMargin(0);
  gPad->SetLeftMargin(0);
  if(sl==9) gPad->SetRightMargin(.01);
  gPad->SetTopMargin(0.0);
//  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.0);
  if(opt & GRIDS) gPad->SetGridx();
  if(opt & GRIDS) gPad->SetGridy();  
 } 



 // ----- Histos limits --------------------------------------------------------------------
 // If max and min are 99, then set max and min to histo default times values passed by functions
 if(limits[0] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum() - limits[2]*fabs(slice[sl][0]->GetMinimum()));
 if(limits[1] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(slice[sl][0]->GetMaximum() + limits[3]*fabs(slice[sl][0]->GetMaximum()));  
 if(limits[0] != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(limits[0]);
 if(limits[1] != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(limits[1]);





 // ----- Single labels --------------------------------------------------------------------- 
 TLatex L[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L[i].SetTextColor(4);
  L[i].SetTextFont(13);
  L[i].SetTextSize(15);
  L[i].SetNDC();
 }


 TGaxis *xax = new TGaxis(10, .0, 350, .0, 0, 370, 305, "C");
 xax->SetLabelSize(.1);
 xax->SetLabelOffset(.05);
 xax->SetTextAngle(90);

 // ----- Drawing --------------------------------------------------------------------------- 
 for(int sl=0;sl<NPADS;sl++)
 {
 
  slice[sl][0]->GetYaxis()->SetTickLength(0);
  slice[sl][0]->GetXaxis()->SetTickLength(0); 
  slice[sl][0]->GetYaxis()->SetLabelSize(0);
  slice[sl][0]->GetXaxis()->SetLabelSize(0);   
  
  padph[sl]->cd(); 

  slice[sl][0]->Draw("E");
 
  if(sl<5) xax->Draw("B");

  
  if(opt & ZEROLINE) ZERO->Draw("");
  if(opt & SUPER2) slice[sl][1]->Draw("same");
  if(opt & SUPER3) slice[sl][2]->Draw("same");
  if(opt & SUPER4) slice[sl][3]->Draw("same");
    
  if(opt & L_TITLE)
  {
   if(sl>4 && sl<9)  L[sl].DrawLatex(0.18, 0.75, TITLES[sl+10]);
   if(sl==9)         L[sl].DrawLatex(0.14, 0.75, TITLES[sl+10]);
   if(sl<4)          L[sl].DrawLatex(0.2, 0.85, TITLES[sl+10]);
   if(sl==4)         L[sl].DrawLatex(0.14, 0.85, TITLES[sl+10]);
  }
 }


 c2by5->cd();




 TGaxis *axisy = new TGaxis(.1, 0.88, 0.1, .8801, 0, 10, 1, "SNBU");
 axisy->SetTitle(TITLES[1]);
 axisy->SetTickSize(0);
 axisy->SetTitleSize(.034);
 axisy->SetGridLength(0);
 axisy->Draw("B");
 if(opt & Y_TITLE) axisy->Draw("B");

 TLatex title1;
 title1.SetTextColor(1);
 title1.SetTextFont(12);
 title1.SetTextSize(0.06);
 if(opt & BIG_TITLE)title1.DrawLatex(0.1, 0.94, TITLES[2]);

 title1.SetTextColor(1);
 if(opt & X_TITLE) title1.DrawLatex(0.4, 0.032, TITLES[0]);

 if(opt & PRINTING)
 {
  c2by5->Print(Form("%s.gif",TITLES[3]),"gif");
  c2by5->Close();
 }





}


















