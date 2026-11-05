void showdthb(int w)
{
 char tit[100];

 gdthb = new TF1("gdthb" ,"gaus",-0.008,0.008);   // gaussian function for W distribution
 gdthb->SetLineColor(4);
 gdthb->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","genoa dthb spectra",-1,0,720,740);
 TLatex label;

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.9);
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();
 label->DrawLatex(.14,.93,"#Delta (#theta)_{ 2} spectrum for different sectors:");
 label.SetTextColor(2);
 label->DrawLatex(.7,.93,"elastic cut");
 
 P->Draw();
 P->Divide(2,3);
 
 for(int s=0; s<6 ; s++)
 {
  P->cd(s+1);
  Histos[w][s][3]->Draw();
  sprintf(tit,"#Delta (#theta)_{  2}   Sector %d          (radians)   ",s+1);
  Histos[w][s][3]->GetXaxis()->SetTitle(tit);
  Histos[w][s][3]->Fit("gdthb","R");

  meanb[s]  = gdthb->GetParameter(1);
  sigmb[s]  = gdthb->GetParameter(2);
  meanbe[s] = gdthb->GetParError(1);
  sigmbe[s] = gdthb->GetParError(2);

  dthbmin[s] = gdthb->GetParameter(1) - dthbsigma * gdthb->GetParameter(2) ;
  dthbmax[s] = gdthb->GetParameter(1) + dthbsigma * gdthb->GetParameter(2) ;

  TLine *line1 = new TLine(dthbmin[s],0,dthbmin[s],Histos[w][s][3]->GetMaximum());
  TLine *line2 = new TLine(dthbmax[s],0,dthbmax[s],Histos[w][s][3]->GetMaximum());
  line1->SetLineColor(2);
  line2->SetLineColor(2);  
  line1->Draw("same");
  line2->Draw("same");
 }

 if(PRINTOPT==1) T->Print("dthb.gif");
}
