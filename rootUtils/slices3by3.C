slices_3by3(TH1D *slice[9][4],  char TITLES[20][200], double minimum, double maximum, int opt)
{
 TLine *ZERO = new TLine(-10000, 1, 1000000, 1);
 ZERO->SetLineWidth(2);
 //ZERO->SetLineColor(31); 
 ZERO->SetLineStyle(2);  
 
 gStyle->SetPadBorderMode(0);
 double    small = 1e-8;
 const int NPADS = 9;

 // If max and min are positive, then set max and min
 if(maximum <  0) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(slice[sl][0]->GetMaximum()*1.4);
 if(minimum <  0) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum());
 if(maximum >= 0) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(maximum);
 if(minimum >= 0) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(minimum);

 // Pads creation
 TCanvas *c3by3 = new TCanvas(TITLES[3], TITLES[3], 640, 640);
 TPad    *padth[NPADS];
 padth[6]  = new TPad("padth6", "padth6", 0.06, 0.1,  0.36, 0.38, 0);
 padth[7]  = new TPad("padth7", "padth7", 0.36, 0.1,  0.63, 0.38, 0);
 padth[8]  = new TPad("padth8", "padth8", 0.63, 0.1,  0.93, 0.38, 0);
 padth[3]  = new TPad("padth3", "padth3", 0.06, 0.38, 0.36, 0.62, 0);
 padth[4]  = new TPad("padth4", "padth4", 0.36, 0.38, 0.63, 0.62, 0);
 padth[5]  = new TPad("padth5", "padth5", 0.63, 0.38, 0.93, 0.62, 0);
 padth[0]  = new TPad("padth0", "padth0", 0.06, 0.62, 0.36, 0.88, 0);
 padth[1]  = new TPad("padth1", "padth1", 0.36, 0.62, 0.63, 0.88, 0);
 padth[2]  = new TPad("padth2", "padth2", 0.63, 0.62, 0.93, 0.88, 0);
 for(int i=0; i<NPADS; i++) padth[i]->Draw();

 // Pads settings
 for(int sl=0; sl<NPADS; sl++)
 {
  padth[sl]->cd();
                                                         gPad->SetRightMargin(small);
  if(sl==1 || sl==2 || sl==4 || sl==5 || sl==7 || sl==8) gPad->SetLeftMargin(small);
  if(sl==2 || sl==5 || sl==8)                            gPad->SetRightMargin(.16);
  if(sl>2)                                               gPad->SetTopMargin(small);
  if(sl<6)                                               gPad->SetBottomMargin(small);
  if(sl<3)                                               gPad->SetTopMargin(.08);
 }

 // Axis setting
 double Minx = slice[0][0]->GetXaxis()->GetXmin();
 double Maxx = slice[0][0]->GetXaxis()->GetXmax();
 double minx = slice[0][0]->GetXaxis()->GetXmin() + slice[0][0]->GetXaxis()->GetXmax()*.001;
 double maxx = slice[0][0]->GetXaxis()->GetXmax()*.9;
// TGaxis *xx = new TGaxis(-1, Minx, Maxx, 1, minx, maxx, 307);
 TGaxis *xx = new TGaxis(Minx, 0, Maxx, 0, minx, maxx, 307);
 xx->SetLabelSize(.075);
 xx->SetLabelOffset(.06);

 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%3 == 0)  yy[i]= new TGaxis(-1, slice[i][0]->GetMinimum(),
                                  -1, slice[i][0]->GetMaximum(),
                                  slice[i][0]->GetMinimum(),
				  slice[i][0]->GetMaximum(), 505,"");
  if(i%3 != 0)  yy[i]= new TGaxis(Maxx, slice[i][0]->GetMinimum(),
                                  Maxx, slice[i][0]->GetMaximum(),
                                  slice[i][0]->GetMinimum(),
				  slice[i][0]->GetMaximum(), 505,"+");

  if(i%3 == 0)  yy[i]->SetLabelOffset(.05);
  if(i%3 == 2)  yy[i]->SetLabelOffset(.15);
                yy[i]->SetLabelSize(.07);
 }


 // Single labels
 TLatex L[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  L[i].SetTextColor(510);
  L[i].SetTextFont(13);
  L[i].SetTextSize(14);
  if(i==3 || i==4 || i==5)  L[i].SetTextSize(15);
  L[i].SetNDC();
 }

 // Drawing
 for(int sl=0; sl<NPADS; sl++)
 {
  padth[sl]->cd();
  slice[sl][0]->GetYaxis()->SetNdivisions(0);
  slice[sl][0]->GetXaxis()->SetNdivisions(0);
  slice[sl][0]->Draw("");
  xx->Draw();
    ZERO->Draw("");
  if(sl%3 == 0) yy[sl]->Draw();
  if(sl%3 == 2) yy[sl]->Draw();

  if(opt & SUPER2) slice[sl][1]->Draw("sameCL");

  if(opt & L_TITLE)
  {
   if(sl < 3) L[sl]->DrawLatex(0.36, 0.83, TITLES[sl+10]);
   if(sl > 2) L[sl]->DrawLatex(0.38, 0.89, TITLES[sl+10]);
  }
 }

 c3by3->cd();
 TGaxis *axisy = new TGaxis(.1, 0.88, 0.1, .8801, 0, 10, 1, "SNBU");
 axisy->SetTitle(TITLES[1]);
 axisy->SetTickSize(0);
 axisy->SetTitleSize(.034);
 axisy->SetGridLength(0);
 if(opt & Y_TITLE) axisy->Draw("B");

 TLatex title1;
 title1.SetTextColor(640);
 title1.SetTextFont(12);
 title1.SetTextSize(0.034);
 if(opt & BIG_TITLE)title1.DrawLatex(0.08, 0.95, TITLES[2]);

 title1.SetTextColor(510);
 if(opt & X_TITLE) title1.DrawLatex(0.4, 0.036, TITLES[0]);

 if(opt & PRINTING)
 {
  c3by3->Print(Form("%s.gif",TITLES[3]),"gif");
  c3by3->Close();
 }

}












