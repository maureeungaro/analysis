void showdth(int w)
{
 char tit[100];

 gdth = new TF1("gdth" ,"gaus",-0.002,0.002);   // gaussian function for W distribution
 gdth->SetLineColor(4);
 gdth->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","genoa dth spectra",-1,0,720,740);
 TLatex label;

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.9);
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();
 label->DrawLatex(.14,.93,"#Delta (#theta) spectrum for different sectors:");
 label.SetTextColor(2);
 label->DrawLatex(.7,.93,"elastic cut");
 
 P->Draw();
 P->Divide(2,3);
 
 for(int s=0; s<6 ; s++)
 {
  P->cd(s+1);
  Histos[w][s][2]->Draw();
  sprintf(tit,"#Delta (#theta)   Sector %d          (radians)   ",s+1);
  Histos[w][s][2]->GetXaxis()->SetTitle(tit);
  Histos[w][s][2]->Fit("gdth","R");

  meant[s]  = gdth->GetParameter(1);
  sigmt[s]  = gdth->GetParameter(2);
  meante[s] = gdth->GetParError(1);
  sigmte[s] = gdth->GetParError(2);
  dthmin[s] = gdth->GetParameter(1) - dthsigma * gdth->GetParameter(2) ;
  dthmax[s] = gdth->GetParameter(1) + dthsigma * gdth->GetParameter(2) ;

  TLine *line1 = new TLine(dthmin[s],0,dthmin[s],Histos[w][s][2]->GetMaximum());
  TLine *line2 = new TLine(dthmax[s],0,dthmax[s],Histos[w][s][2]->GetMaximum());
  line1->SetLineColor(2);
  line2->SetLineColor(2);  
  line1->Draw("same");
  line2->Draw("same");
 }

 if(PRINTOPT==1) T->Print("dth.gif");
}
