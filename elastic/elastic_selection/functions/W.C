void showW(int w)
{
 char tit[100];

 gW = new TF1("gW" ,"gaus",.88,1.0);   // gaussian function for W distribution
 gW->SetLineColor(4);
 gW->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","W spectra",-1,0,720,740);
 TLatex label;
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.9);
 label->DrawLatex(.15,.93,"W spectrum for different sectors:");
 label.SetTextColor(2);
 label->DrawLatex(.66,.93,"elastic cut");
 
 P->Draw();
 P->Divide(2,3);
 
 for(int s=0; s<6; s++)
 {
  P->cd(s+1);
  Histos[w][s][0]->Draw();
  sprintf(tit,"W   Sector %d                 (GeV)     ",s+1);
  Histos[w][s][0]->GetXaxis()->SetTitle(tit);
  Histos[w][s][0]->Fit("gW","R");

  meanw[s]  = gW->GetParameter(1);
  sigmw[s]  = gW->GetParameter(2);
  meanwe[s] = gW->GetParError(1);
  sigmwe[s] = gW->GetParError(2);
  Wmin[s]   = gW->GetParameter(1) - Wsigma * gW->GetParameter(2) ;
  Wmax[s]   = gW->GetParameter(1) + Wsigma * gW->GetParameter(2) ;

  TLine *line1 = new TLine(Wmin[s],0,Wmin[s],Histos[w][s][0]->GetMaximum());
  TLine *line2 = new TLine(Wmax[s],0,Wmax[s],Histos[w][s][0]->GetMaximum());
  line1->SetLineColor(2);
  line2->SetLineColor(2);  
  line1->Draw("same");
  line2->Draw("same");
 }

 if(PRINTOPT==1) T->Print("w.gif");
}
