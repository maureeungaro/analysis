void showmm(int w)
{
 char tit[100];

 gmm = new TF1("gmm" ,"gaus",-.0005,.0005);   // gaussian function for mm distribution
 gmm->SetLineColor(4);
 gmm->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","mm spectra",-1,0,720,740);
 TLatex label;

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.9);
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();
 label->DrawLatex(.06,.93,"eP missing mass spectrum for different sectors:");
 label.SetTextColor(2);
 label->DrawLatex(.79,.93,"elastic cut");
 
 P->Draw();
 P->Divide(2,3);
 
 for(int s=0; s<6 ; s++)
 {
  P->cd(s+1);
  Histos[w][s][1]->Draw();
  sprintf(tit,"  mm   Sector %d                  GeV^{          2} ",s+1);
  Histos[w][s][1]->GetXaxis()->SetTitle(tit);
  Histos[w][s][1]->Fit("gmm","R");

  meanm[s]  = gmm->GetParameter(1);
  sigmm[s]  = gmm->GetParameter(2);
  meanme[s] = gmm->GetParError(1);
  sigmme[s] = gmm->GetParError(2);

  mmmin[s]  = gmm->GetParameter(1) - mmsigma * gmm->GetParameter(2) ;
  mmmax[s]  = gmm->GetParameter(1) + mmsigma * gmm->GetParameter(2) ;

  TLine *line1 = new TLine(mmmin[s],0,mmmin[s],Histos[w][s][1]->GetMaximum());
  TLine *line2 = new TLine(mmmax[s],0,mmmax[s],Histos[w][s][1]->GetMaximum());
  line1->SetLineColor(2);
  line2->SetLineColor(2);  
  line1->Draw("same");
  line2->Draw("same");
 }

 if(PRINTOPT==1) T->Print("mm.gif");
}
