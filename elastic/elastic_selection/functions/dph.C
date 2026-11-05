void showdph(int w)
{
 char tit[100];

 gdphi = new TF1("gdphi" ,"gaus",160,200);   // gaussian function for W distribution
 gdphi->SetLineColor(4);
 gdphi->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","phi_e-phi_P spectra",-1,0,720,740);
 TLatex label;

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.9);
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();
 label->DrawLatex(.12,.93,"#phi(e)-#phi(P) spectrum for different sectors:");
 label.SetTextColor(2);
 label->DrawLatex(.73,.93,"elastic cut");
 
 P->Draw();
 P->Divide(2,3);
 
 for(int s=0; s<6; s++)
 {
  P->cd(s+1);
  Histos[w][s][4]->Draw();
  sprintf(tit,"#phi (e) - #phi (P)   Sector %d          (degrees)   ",s+1);
  Histos[w][s][4]->GetXaxis()->SetTitle(tit);
  Histos[w][s][4]->Fit("gdphi","R");

  meanp[s]  = gdphi->GetParameter(1);
  sigmp[s]  = gdphi->GetParameter(2);
  meanpe[s] = gdphi->GetParError(1);
  sigmpe[s] = gdphi->GetParError(2);

  dphmin[s] = gdphi->GetParameter(1) - dphsigma * gdphi->GetParameter(2) ;
  dphmax[s] = gdphi->GetParameter(1) + dphsigma * gdphi->GetParameter(2) ;

  TLine *line1 = new TLine(dphmin[s],0,dphmin[s],Histos[w][s][4]->GetMaximum());
  TLine *line2 = new TLine(dphmax[s],0,dphmax[s],Histos[w][s][4]->GetMaximum());
  line1->SetLineColor(2);
  line2->SetLineColor(2);  
  line1->Draw("same");
  line2->Draw("same");
 }

 if(PRINTOPT==1) T->Print("dph.gif");
}
