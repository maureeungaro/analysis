show_ph_mm()
{
 gStyle->SetPadRightMargin(0.2);
 TCanvas *PHMMM = new TCanvas("PHMMM" ,"PHMMM", 1200, 1000);
 TPad *PHMM = new TPad("PHMM", "PHMM", 0.1, 0.09, 0.96, 0.98);
 PHMM->Draw();
 PHMM->Divide(4, 2);
 
 for(int w=0; w<8; w++)
 {
  PHMM->cd(w+1);
  gPad->SetLogz();
  phmm[w][0]->Draw("cont1 colz");
  PHMM->Update();
  
  TPaletteAxis *palette;
  palette = (TPaletteAxis*)phmm[w][0]->FindObject("palette");
  palette->SetLabelSize(0.08);

  palette->SetLabelOffset(0.016);
  palette->SetBorderSize(10);
  palette->SetX1NDC(0.82);
  palette->SetX2NDC(0.86);  
  phmm[w][0]->Draw("cont1 colz");
    
  Cutu[w]->Draw();
  Cutl[w]->Draw();  
 }
 
 PHMMM->cd();
   
 TLatex title;
 title.SetTextSize(0.04);
 title.SetTextColor(514);
 title.DrawLatex(0.43, 0.05, "#leftarrow   M_{x}^{ 2}   #rightarrow                               [GeV^{2} ]" );

 title.SetTextAngle(90);
 title.DrawLatex(0.07, 0.42, "#leftarrow   #phi_{P}^{c.m.}   #rightarrow                      [deg]" );
 
 
 
}

show_mm_dth()
{
 TLine *pi0s = new TLine(-0.04, 0.0182, 0.04, 0.0182);
 pi0s->SetLineWidth(1);
// pi0s->SetLineColor(2);

  gStyle->SetPadRightMargin(0.14);
  gStyle->SetPadLeftMargin(0.18);  
 TCanvas *MMDTHH = new TCanvas("MMDTHH" ,"MMDTHH", 1200, 1000);
 TPad *MMDTH = new TPad("MMDTH", "MMDTH", 0.1, 0.09, 0.96, 0.98);
 MMDTH->Draw(); 
 MMDTH->Divide(4, 2);
 
 for(int w=0; w<8; w++)
 {
  MMDTH->cd(w+1);
  mm_dth[w][1]->Draw("cont1 colz");
  MMDTH->Update();
  TPaletteAxis *palette;
  palette = (TPaletteAxis*)mm_dth[w][1]->FindObject("palette");
  palette->SetLabelSize(0.06);

  palette->SetLabelOffset(0.016);
  palette->SetBorderSize(10);
  palette->SetX1NDC(0.88);
  palette->SetX2NDC(0.92);  
  mm_dth[w][1]->Draw("cont1 colz");  
  
  pi0s->Draw();
 }
  MMDTHH->cd(); 
 TLatex title;
 title.SetTextSize(0.04);
 title.SetTextColor(514);
 title.DrawLatex(0.43, 0.05, "#leftarrow   #Delta#theta   #rightarrow                                    [rad]" );

 title.SetTextAngle(90);

 title.DrawLatex(0.07, 0.42, "#leftarrow   M_{x}^{ 2}   #rightarrow                     [GeV^{2} ]" ); 
 
 
 
/* TCanvas *MMDTH2 = new TCanvas("MMDTH2" ,"MMDTH2", 1200, 1000);
 MMDTH2->Divide(4, 2);
 
 for(int w=0; w<8; w++)
 {
  MMDTH2->cd(w+1);
  dth[w][1]->Draw();
  dth[w][2]->Draw("same");  
 }*/
     
}

show_mm_dthb()
{
  gStyle->SetPadRightMargin(0.14);
  gStyle->SetPadLeftMargin(0.18);  
 TLine *pi0s = new TLine(-0.03, 0.0182, 0.06, 0.0182);
 pi0s->SetLineWidth(1);
// pi0s->SetLineColor(2);
 TCanvas *MMDTHBB = new TCanvas("MMDTHBB" ,"MMDTHBB", 1200, 1000);
 TPad *MMDTHB = new TPad("MMDTHB" ,"MMDTHB",  0.1, 0.09, 0.96, 0.98); 
 MMDTHB->Draw();
 MMDTHB->Divide(4, 2);
 
 for(int w=0; w<8; w++)
 {
  MMDTHB->cd(w+1);
  mm_dthb[w][2]->Draw("cont1 colz");
  MMDTHB->Update();
  TPaletteAxis *palette;
  palette = (TPaletteAxis*)mm_dthb[w][2]->FindObject("palette");
  palette->SetLabelSize(0.06);

  palette->SetLabelOffset(0.016);
  palette->SetBorderSize(10);
  palette->SetX1NDC(0.88);
  palette->SetX2NDC(0.92);  
  mm_dthb[w][2]->Draw("cont1 colz");       
   pi0s->Draw(); 
  Cut3[w]->Draw();
 }
  MMDTHBB->cd();   
 TLatex title;
 title.SetTextSize(0.04);
 title.SetTextColor(514);
 title.DrawLatex(0.43, 0.05, "#leftarrow   #Delta#theta_{2}   #rightarrow                                    [rad]" );

 title.SetTextAngle(90);

 title.DrawLatex(0.07, 0.42, "#leftarrow   M_{x}^{ 2}   #rightarrow                     [GeV^{2} ]" ); 
 
/* TCanvas *MMDTHB2 = new TCanvas("MMDTHB2" ,"MMDTHB2", 1200, 1000);
 MMDTHB2->Divide(4, 2);*/
 
/* for(int w=0; w<8; w++)
 {
  MMDTHB2->cd(w+1);
  gPad->SetLogy();
  dthb[w][2]->Draw();
  dthb[w][3]->Draw("same");  
 } */   
}

show_mm_w()
{
 TH1F *h; 
 h = (TH1F*) mmm[0]->Clone();
 h->Add(mmm[0], mmm[3], 1,-1);
 h->SetLineColor(2);
 
 TH1F *h2; 
 h2 = (TH1F*) www[0]->Clone();
 h2->Add(www[0], www[3], 1,-1);
 h2->SetLineColor(2);

  
 TCanvas *MMW = new TCanvas("MMW" ,"MMW", 600, 600);
// MMW->Divide(2, 1);
 
/* MMW->cd(1);
 www[0]->Draw();
 www[3]->Draw("same"); 
 h2->Draw("same");*/

 MMW->cd(2);
 //mmm[0]->Draw();
 mmm[3]->Draw(""); 
// h->Draw("same");



}










