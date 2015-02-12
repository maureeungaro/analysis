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

slices_2by4(TH1D *slice[10][10],  char TITLES[50][300], double limits[5], int opt)
{  
 gStyle->SetPadLeftMargin(0.2);
 gStyle->SetPadRightMargin(0.22);
 const int NPADS = 8; 
 gStyle->SetErrorX(0.);
 TLine *ZERO = new TLine(-10000, limits[4], 1000000, limits[4]);
 ZERO->SetLineWidth(2);
 ZERO->SetLineColor(2); 
 ZERO->SetLineStyle(2);  
   
 // ----- Pads creation and settings -------------------------------------------------------
 TCanvas *c2by4 = new TCanvas(TITLES[3], TITLES[3], 650, 750);
 //TCanvas *c2by4 = new TCanvas(TITLES[3], TITLES[3], 480, 560);
 c2by4->SetFrameFillColor(0);


 
 TPad    *padph[NPADS];
 double x_lim[3]   = {0.08, 0.50, 0.93};
 double y_lim1[8]  = {0.73, 0.73, 0.53, 0.53, 0.33, 0.33, 0.08, 0.08};
 double y_lim2[8]  = {0.93, 0.93, 0.73, 0.73, 0.53, 0.53, 0.33, 0.33};
  
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
  if(sl>5) gPad->SetBottomMargin(.22);
  if(sl<2) gPad->SetTopMargin(.08);
  if(opt & GRIDS) gPad->SetGridx();
  if(opt & GRIDS) gPad->SetGridy();  
 }
 
 // ----- Histos limits --------------------------------------------------------------------
 double absolute_max = 0;
 for(int sl=0; sl<NPADS; sl++)
  absolute_max = absolute_max + slice[sl][0]->GetMaximum();
 absolute_max = limits[3]*absolute_max/8; 


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

 TGaxis *xx1 = new TGaxis(Minx[6], Miny[6], Maxx[6], Miny[6], minx[6], maxx[6], 307);
 TGaxis *xx2 = new TGaxis(Minx[7], Miny[7], Maxx[7], Miny[7], minx[7], maxx[7], 307);  
 xx1->SetLabelSize(.1);
 xx1->SetLabelOffset(.07);
 xx2->SetLabelSize(.1);
 xx2->SetLabelOffset(.07);
 
 xx1->SetNdivisions(506);
 xx2->SetNdivisions(506);


 
 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%2 == 0)  yy[i]= new TGaxis(Minx[i], Miny[i], Minx[i], Maxy[i], miny[i], maxy[i], 506,"");
  if(i%2 != 0)  yy[i]= new TGaxis(Maxx[i], Miny[i], Maxx[i], Maxy[i], miny[i], maxy[i], 506,"+");

  if(i%2 == 0)  yy[i]->SetLabelOffset(.05);
  if(i%2 != 0)  yy[i]->SetLabelOffset(.11);
  if(i<6)       yy[i]->SetLabelSize(.12);
  if(i>5)       yy[i]->SetLabelSize(.1);

  yy[i]->SetNdivisions(4);
  //yy[i]->CenterLabels();
// yy[i]->SetLabelColor(666);

 }





 // ----- Single labels --------------------------------------------------------------------- 
 TLatex L[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L[i].SetTextColor(12);
  L[i].SetTextFont(42);
  if(i<6)  L[i].SetTextSize(.12);
  if(i>5)  L[i].SetTextSize(.096);
  L[i].SetNDC();
 }

 TLatex L2[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L2[i].SetTextColor(6);
  L2[i].SetTextFont(13);
  

  if(i==0 || i==1 || i==4 || i==5 || i==8 || i==9)  L2[i].SetTextSize(15);
  if(i==2 || i==3 || i==6 || i==7)                  L2[i].SetTextSize(14);
  L2[i].SetNDC();
 }


 // ----- Drawing --------------------------------------------------------------------------- 
 for(int sl=0;sl<NPADS;sl++)
 {
  padph[sl]->cd();   
  padph[sl]->SetFillColor(0); 
  slice[sl][0]->Draw("E1");
  
  if(sl==6) xx1->Draw();
  if(sl==7) xx2->Draw();  

  yy[sl]->Draw();
  
  if(opt & ZEROLINE)  ZERO->Draw("");


  if(opt & SUPER2) 
  {
   TF1 *bbb = (TF1*) slice[sl][0]->GetFunction("phifit");
   bbb->SetLineColor(12);
   //	  b->Delete();
   slice[sl][1]->Draw("Esame");
   //  cout << bbb->GetChisquare()/9 << endl;
   }



  if(opt & SUPER3) slice[sl][2]->Draw("same");
  if(opt & SUPER4) slice[sl][3]->Draw("same");    
  slice[sl][0]->Draw("Esame");
  if(opt & SUPER2) slice[sl][1]->Draw("Esame");


  if(opt & L_TITLE)
  {
   if(sl == 0)                      L[sl].DrawLatex(0.36 + .1, 0.78, TITLES[sl+10]);
   if(sl == 1)                      L[sl].DrawLatex(0.24 + .1, 0.78, TITLES[sl+10]);
   if(sl>0 && sl%2 == 0 && sl != 6) L[sl].DrawLatex(0.38 + .1, 0.83, TITLES[sl+10]);
   if(sl>1 && sl%2 != 0 && sl != 7) L[sl].DrawLatex(0.26 + .1, 0.83, TITLES[sl+10]);
   if(sl == 6)                      L[sl].DrawLatex(0.38 + .1, 0.88, TITLES[sl+10]);
   if(sl == 7)                      L[sl].DrawLatex(0.23 + .1, 0.88,  TITLES[sl+10]);
  }


 }

 c2by4->cd();
 TGaxis *axisy = new TGaxis(.1, 0.88, 0.1, .8801, 0, 10, 1, "SNBU");
 axisy->SetTitle(TITLES[1]);
 axisy->SetTickSize(0);
 axisy->SetTitleSize(.034);
 axisy->SetTitleOffset(.7);
 axisy->SetGridLength(0);
 if(opt & Y_TITLE) axisy->Draw("B");


 TLatex title1;
 title1.SetTextColor(1);
 title1.SetTextFont(22);
 title1.SetTextSize(0.034);
 if(opt & BIG_TITLE)title1.DrawLatex(0.2, 0.95, TITLES[2]);

 title1.SetTextColor(1);
 if(opt & X_TITLE) title1.DrawLatex(0.4, 0.036, TITLES[0]);

 if(opt & PRINTING)
 {
  c2by4->Print(Form("%s.eps",TITLES[3]));
  c2by4->Close();
 }
}


























