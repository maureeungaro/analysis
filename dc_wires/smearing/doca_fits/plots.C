void plot_doca()
{
 t->SetTextColor(50);
 TCanvas *reg[3];
 for(int r=0; r<3; r++) 
 {
  reg[r] = new TCanvas(Form("re%d", r+1), Form("DOCA study: DC region %d", r+1), 500, 350);
  reg[r]->SetFillColor(33);
  reg[r]->SetFrameFillColor(514);  
 
  Reg[r]->Draw("cont col");
  t->DrawText(0.75,.94, Form("Region %d", r+1)); 
 }
}


void plot_sigmas(int OPT)
{
 t->SetTextColor(50);
 TCanvas *res[3];
 for(int r=0; r<3; r++) 
 {
  res[r] = new TCanvas(Form("res%d", r+1), Form("DOCA study: DC region %d  SIGMA ", r+1), 500, 350);
  res[r]->SetFillColor(33);
  res[r]->SetFrameFillColor(19);  

  Res[r][1]->Draw();
  Res[r][0]->Draw("same");
  Res[r][1]->Draw("same");
  ccs[r]->Draw();
 
  t->DrawText(0.55,.94, Form("Sigma of Region %d", r+1));
  if(OPT) Fres[r]->Draw("same");  
 }
}

void plot_means(int OPT)
{
 t->SetTextColor(4);
 
 TCanvas *rem[3];
 for(int r=0; r<3; r++) 
 {
  rem[r] = new TCanvas(Form("rem%d", r+1), Form("DOCA study: DC region %d  MEAN ", r+1), 500, 350);
  rem[r]->SetFillColor(33);
  rem[r]->SetFrameFillColor(19);  
 
  Rem[r][1]->Draw();
  Rem[r][0]->Draw("same");
  Rem[r][1]->Draw("same");
  ccm[r]->Draw();
  
  t->DrawText(0.6,.94, Form("Mean of Region %d", r+1));
  if(OPT) 
  {
   Frem[r]->Draw("same");
   Csize[r]->Draw("same");
  }
 }
}
