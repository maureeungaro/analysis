// slice[12][4]        12 slices, 4 histos each
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

slices_3by4(TH1D *slice[12][4],  char TITLES[50][300], double limits[5], int opt)
{
 gStyle->SetPadLeftMargin(0.22);
 gStyle->SetPadRightMargin(0.22);
 const int NPADS = 12; 
 gStyle->SetErrorX(0.);
 TLine *ZERO = new TLine(-10000, limits[4], 1000000, limits[4]);
 ZERO->SetLineWidth(2);
 ZERO->SetLineColor(2); 
 ZERO->SetLineStyle(2);  


 // ----- Pads creation and settings -------------------------------------------------------
 TCanvas *c3by4 = new TCanvas(TITLES[3], TITLES[3], 460, 530);
// TCanvas *c3by4 = new TCanvas(TITLES[3], TITLES[3], 650, 750); 
 TPad    *padph[NPADS];
 double x_lim[4]   = {0.08, 0.36, 0.63, 0.94};
 double y_lim1[12] = {0.70, 0.70, 0.70, 0.50, 0.50, 0.50, 0.3, 0.3, 0.3, 0.1, 0.1, 0.1};
 double y_lim2[12] = {0.90, 0.90, 0.90, 0.70, 0.70, 0.70, 0.5, 0.5, 0.5, 0.3, 0.3, 0.3};
 
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]= new TPad(Form("p%d", sl), Form("p%d", sl), x_lim[sl%3], y_lim1[sl], x_lim[sl%3 + 1], y_lim2[sl], 0);
  padph[sl]->Draw();
 }
         
 // Pads settings
 for(int sl=0; sl<NPADS; sl++)
 {
  padph[sl]->cd();
  padph[sl]->SetFillColor(666); 
                                                                             gPad->SetRightMargin(0);
  if(sl==1 || sl==2 || sl==4 || sl==5 || sl==7 || sl==8 || sl==10 || sl==11) gPad->SetLeftMargin(0);
  if(sl==2 || sl==5 || sl==8 || sl==11)                                      gPad->SetRightMargin(.16);
  if(sl>2)                                                                   gPad->SetTopMargin(0);
  if(sl<9)                                                                   gPad->SetBottomMargin(0);
  if(sl<3)                                                                   gPad->SetTopMargin(.08);
 }
 
 // ----- Histos limits --------------------------------------------------------------------
 // If max and min are 99, then set max and min to histo default times values passed by functions
 double absolute_max = 0;
 for(int sl=0; sl<NPADS; sl++)
  absolute_max = absolute_max + slice[sl][0]->GetMaximum();
 absolute_max = limits[3]*absolute_max/10; 


 if(limits[0] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum() - limits[2]*fabs(slice[sl][0]->GetMinimum()));
 if(limits[1] == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(absolute_max);
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

//   miny[i] = slice[i][0]->GetMinimum();
//   maxy[i] = slice[i][0]->GetMaximum();    

 miny[i] = slice[i][0]->GetMinimum() + Maxy[i]*.01;
 maxy[i] = slice[i][0]->GetMaximum()*.9;    


  
  slice[i][0]->GetYaxis()->SetTickLength(0);
  slice[i][0]->GetXaxis()->SetTickLength(0); 

  slice[i][0]->GetYaxis()->SetLabelSize(0);
  slice[i][0]->GetXaxis()->SetLabelSize(0);   

  slice[i][0]->GetYaxis()->SetNdivisions(5);
  slice[i][0]->GetXaxis()->SetNdivisions(5); 

//  slice[i][0]->SetMarkerStyle(22);  
 // slice[i][0]->SetLineColor(1);       
 }

 TGaxis *xx1 = new TGaxis(Minx[9],  Miny[9],  Maxx[9],  Miny[9],  minx[9],  maxx[9],  307);
 TGaxis *xx2 = new TGaxis(Minx[10], Miny[10], Maxx[10], Miny[10], minx[10], maxx[10], 307);  
 TGaxis *xx3 = new TGaxis(Minx[11], Miny[11], Maxx[11], Miny[11], minx[11], maxx[11], 307);   
 xx1->SetLabelSize(.09);
 xx1->SetLabelOffset(.06); 
 xx2->SetLabelSize(.09);
 xx2->SetLabelOffset(.06);
 xx3->SetLabelSize(.09);
 xx3->SetLabelOffset(.06);
 
 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%3 == 0)  yy[i]= new TGaxis(Minx[i], Miny[i], Minx[i], Maxy[i], miny[i], maxy[i], 305,"");
  if(i%3 != 0)  yy[i]= new TGaxis(Maxx[i], Miny[i], Maxx[i], Maxy[i], miny[i], maxy[i], 305,"+");

  if(i%3 == 0)  yy[i]->SetLabelOffset(.05);
  if(i%3 != 0)  yy[i]->SetLabelOffset(.13);
  yy[i]->SetLabelSize(.1);
  yy[i]->CenterLabels();

 }

 

 // Single labels
 TLatex L[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L[i].SetTextColor(4);
  L[i].SetTextFont(13);
  L[i].SetTextSize(14);
  if(i==3 || i==4 || i==5)  L[i].SetTextSize(14);
  L[i].SetNDC();
 }

 // Drawing
 for(int sl=0;sl<NPADS;sl++)
 {
  padph[sl]->cd();   
  slice[sl][0]->Draw("E");
  
  if(sl==9)  xx1->Draw();
  if(sl==10) xx2->Draw();  
  if(sl==11) xx3->Draw();    
  if(sl%3==0 || sl%3==2) yy[sl]->Draw();
  
  if(opt & ZEROLINE) ZERO->Draw("");
//   ZERO->Draw("");
  if(opt & SUPER2) 
  {
	  TF1 *b = (TF1*) slice[sl][1]->GetListOfFunctions();
	  b->Delete();
	  slice[sl][1]->Draw("Bsame");
  }
  if(opt & SUPER3) slice[sl][2]->Draw("Bsame");
  if(opt & SUPER4) slice[sl][3]->Draw("Csame");
    
  slice[sl][0]->Draw("Esame");





  if(opt & L_TITLE)
  {
   if(sl < 3) L[sl].DrawLatex(0.31, 0.81, TITLES[sl+10]);
   if(sl > 2) L[sl].DrawLatex(0.33, 0.87, TITLES[sl+10]);        
  }
 }


 
 
 c3by4->cd();
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
  c3by4->Print(Form("%s.gif",TITLES[3]),"gif");
  c3by4->Close();
 }

}












