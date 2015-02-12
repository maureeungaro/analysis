slices_3by7(TH1D *slice[21][4],  char TITLES[40][200], double minimum, double maximum, int opt)
{
 TLine *ZERO = new TLine(-10000, 0, 1000000, 0);
 ZERO->SetLineWidth(2);
 //ZERO->SetLineColor(31); 
 ZERO->SetLineStyle(2);  
 
 gStyle->SetPadBorderMode(0);
 double    small = 1e-8;
 const int NPADS = 21;


 if(maximum == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(slice[sl][0]->GetMaximum() + fabs(slice[sl][0]->GetMaximum())*.4);
 if(minimum == 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(slice[sl][0]->GetMinimum() - fabs(slice[sl][0]->GetMinimum())*.4);
 if(maximum != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMaximum(maximum);
 if(minimum != 99) for(int sl=0; sl<NPADS; sl++) slice[sl][0]->SetMinimum(minimum);

 // Pads creation
 TCanvas *c3by7 = new TCanvas(TITLES[3], TITLES[3], 640, 740);
 TPad    *padth[NPADS];

 padth[18]  = new TPad("padth18", "padth18", 0.06, 0.09,   0.36, 0.21, 0);
 padth[19]  = new TPad("padth19", "padth19", 0.36, 0.09,   0.63, 0.21, 0);
 padth[20]  = new TPad("padth20", "padth20", 0.63, 0.09,   0.93, 0.21, 0);
 padth[15]  = new TPad("padth15", "padth15", 0.06, 0.21,  0.36, 0.32, 0);
 padth[16]  = new TPad("padth16", "padth16", 0.36, 0.21,  0.63, 0.32, 0);
 padth[17]  = new TPad("padth17", "padth17", 0.63, 0.21,  0.93, 0.32, 0);
 padth[12]  = new TPad("padth12", "padth12", 0.06, 0.32,  0.36, 0.43, 0);
 padth[13]  = new TPad("padth13", "padth13", 0.36, 0.32,  0.63, 0.43, 0);
 padth[14]  = new TPad("padth14", "padth14", 0.63, 0.32,  0.93, 0.43, 0);
 padth[9]   = new TPad("padth9",  "padth9",  0.06, 0.43,  0.36, 0.54, 0);
 padth[10]  = new TPad("padth10", "padth10", 0.36, 0.43,  0.63, 0.54, 0);
 padth[11]  = new TPad("padth11", "padth11", 0.63, 0.43,  0.93, 0.54, 0);
 padth[6]   = new TPad("padth6",  "padth6",  0.06, 0.54,  0.36, 0.65, 0);
 padth[7]   = new TPad("padth7",  "padth7",  0.36, 0.54,  0.63, 0.65, 0);
 padth[8]   = new TPad("padth8",  "padth8",  0.63, 0.54,  0.93, 0.65, 0);
 padth[3]   = new TPad("padth3",  "padth3",  0.06, 0.65,  0.36, 0.76, 0);
 padth[4]   = new TPad("padth4",  "padth4",  0.36, 0.65,  0.63, 0.76, 0);
 padth[5]   = new TPad("padth5",  "padth5",  0.63, 0.65,  0.93, 0.76, 0);
 padth[0]   = new TPad("padth0",  "padth0",  0.06, 0.76,  0.36, 0.87, 0);
 padth[1]   = new TPad("padth1",  "padth1",  0.36, 0.76,  0.63, 0.87, 0);
 padth[2]   = new TPad("padth2",  "padth2",  0.63, 0.76,  0.93, 0.87, 0);
 for(int i=0; i<NPADS; i++) padth[i]->Draw();

 // Pads settings
 for(int sl=0; sl<NPADS; sl++)
 {
  padth[sl]->cd();
                                                                           gPad->SetRightMargin(small);
  if(sl==1  || sl==2  || sl==4  || sl==5  || sl==7  || sl==8)              gPad->SetLeftMargin(small);
  if(sl==10 || sl==11 || sl==13 || sl==14 || sl==16 || sl==17)             gPad->SetLeftMargin(small);
  if(sl==19 || sl==20 )                                                    gPad->SetLeftMargin(small);
  if(sl==0 || sl==3 || sl==6 || sl==9  || sl == 12 || sl==15 || sl ==18)   gPad->SetLeftMargin(.2);
  if(sl==2 || sl==5 || sl==8 || sl==11 || sl == 14 || sl==17 || sl ==20)   gPad->SetRightMargin(.16);
  if(sl>2)                                                                 gPad->SetTopMargin(small);
  if(sl<18)                                                                gPad->SetBottomMargin(small);
  if(sl>17)                                                                gPad->SetBottomMargin(0.2);
  if(sl<3)                                                                 gPad->SetTopMargin(.08);
 }

 // Axis setting
 double Minx = slice[0][0]->GetXaxis()->GetXmin();
 double Maxx = slice[0][0]->GetXaxis()->GetXmax();
 double minx = slice[0][0]->GetXaxis()->GetXmin() + slice[0][0]->GetXaxis()->GetXmax()*.001;
 double maxx = slice[0][0]->GetXaxis()->GetXmax()*.9;

 TGaxis *xx1 = new TGaxis(Minx, slice[18][0]->GetMinimum(), Maxx, slice[18][0]->GetMinimum(), minx, maxx, 307);
 TGaxis *xx2 = new TGaxis(Minx, slice[19][0]->GetMinimum(), Maxx, slice[19][0]->GetMinimum(), minx, maxx, 307);
 TGaxis *xx3 = new TGaxis(Minx, slice[20][0]->GetMinimum(), Maxx, slice[20][0]->GetMinimum(), minx, maxx, 307);
 xx1->SetLabelSize(.15);
 xx2->SetLabelSize(.15);
 xx3->SetLabelSize(.15);
 xx1->SetLabelOffset(.06);
 xx2->SetLabelOffset(.06);
 xx3->SetLabelOffset(.06);

 TGaxis *yy[NPADS];
 for(int i=0; i<NPADS; i++)
 {
  if(i%3 == 0)  yy[i]= new TGaxis(-1, slice[i][0]->GetMinimum() ,
                                  -1, slice[i][0]->GetMaximum(),
                                  slice[i][0]->GetMinimum(),
				  slice[i][0]->GetMaximum(), 505,"");
  if(i%3 != 0)  yy[i]= new TGaxis(Maxx, slice[i][0]->GetMinimum(),
                                  Maxx, slice[i][0]->GetMaximum(),
                                  slice[i][0]->GetMinimum(),
				  slice[i][0]->GetMaximum(), 505,"+");

  if(i%3 == 0)  yy[i]->SetLabelOffset(.05);
  if(i%3 == 2)  yy[i]->SetLabelOffset(.15);
                yy[i]->SetLabelSize(.16);
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
 // ZERO->Draw("");
  if(sl==18) xx1->Draw();
  if(sl==19) xx2->Draw();
  if(sl==20) xx3->Draw();
  if(sl%3 == 0) yy[sl]->Draw();
  if(sl%3 == 2) yy[sl]->Draw();

  if(opt & SUPER2) slice[sl][1]->Draw("sameCL");

  if(opt & L_TITLE)
  {
   if(sl < 3) L[sl]->DrawLatex(0.36, 0.83, TITLES[sl+10]);
   if(sl > 2) L[sl]->DrawLatex(0.38, 0.89, TITLES[sl+10]);
  }

 }

 c3by7->cd();
 TGaxis *axisy = new TGaxis(.1, 0.88, 0.1, .8801, 0, 10, 1, "SNBU");
 axisy->SetTitle(TITLES[1]);
 axisy->SetTickSize(0);
 axisy->SetTitleSize(.028);
 axisy->SetTitleOffset(1.5);
 axisy->SetGridLength(0);
 if(opt & Y_TITLE) axisy->Draw("B");

 TLatex title1;
 title1.SetTextColor(640);
 title1.SetTextFont(12);
 title1.SetTextSize(0.034);
 if(opt & BIG_TITLE)title1.DrawLatex(0.08, 0.95, TITLES[2]);

 TLatex title2;
 title2.SetTextColor(1);
 title2.SetTextFont(12);
 title2.SetTextSize(0.034);
 if(opt & TITLE2)title2.DrawLatex(0.08, 0.9, TITLES[3]);



 title1.SetTextColor(510);
 if(opt & X_TITLE) title1.DrawLatex(0.4, 0.036, TITLES[0]);

 if(opt & PRINTING)
 {
  c3by7->Print(Form("%s.gif",TITLES[3]),"gif");
  c3by7->Close();
 }

}












