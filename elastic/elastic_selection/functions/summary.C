void summary(int w)
{
 gStyle->SetFrameLineColor(0);


 int s = 2;
 string What[5] = {"W", "mm(eP)", "$#Delta #theta", "#Delta #theta_{2}", "#Delta #phi"};

 gW = new TF1("gW" ,"gaus",.88,1.0);   // gaussian function for W distribution
 gW->SetLineColor(4);
 gW->SetLineWidth(2);

 TCanvas *T=new TCanvas("T","Summary spectra",720,740);
 TLatex label;
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();

 TPad *P = new TPad("P","P", 0.0, 0.02, 1, 0.98);
 
 P->Draw();
 P->Divide(2,3);
 
 P->cd(1);
 Histos[w][s-1][0]->Draw();
 Histos[w][s-1][0]->GetXaxis()->SetTitle(Form("W   Sector %d                 [GeV]", s));
 Histos[w][s-1][0]->Fit("gW","R");

 TLine *line1 = new TLine(Wmin[s],0,Wmin[s],Histos[w][s][0]->GetMaximum());
 TLine *line2 = new TLine(Wmax[s],0,Wmax[s],Histos[w][s][0]->GetMaximum());
 line1->SetLineColor(2);
 line2->SetLineColor(2);  
 line1->Draw("same");
 line2->Draw("same");
 label.DrawLatex(.82,.78,"a)");
  
 P->cd(2);
 Histos[w][s-1][1]->Draw();
 Histos[w][s-1][1]->GetXaxis()->SetTitle(Form("M_{x}(eP)  Sector %d               [GeV^{2}]", s));
 Histos[w][s-1][1]->Fit("gmm","R");

 TLine *line1 = new TLine(mmmin[s],0,mmmin[s],Histos[w][s][1]->GetMaximum());
 TLine *line2 = new TLine(mmmax[s],0,mmmax[s],Histos[w][s][1]->GetMaximum());
 line1->SetLineColor(2);
 line2->SetLineColor(2);  
 line1->Draw("same");
 line2->Draw("same");
 label.DrawLatex(.82,.78,"b)");
  
 P->cd(3);
 Histos[w][s-1][2]->Draw();
 Histos[w][s-1][2]->GetXaxis()->SetTitle(Form("#Delta #theta  Sector %d                  [rad]", s));
 Histos[w][s-1][2]->Fit("gdth","R");

 TLine *line1 = new TLine(dthmin[s],0,dthmin[s],Histos[w][s][2]->GetMaximum());
 TLine *line2 = new TLine(dthmax[s],0,dthmax[s],Histos[w][s][2]->GetMaximum());
 line1->SetLineColor(2);
 line2->SetLineColor(2);  
 line1->Draw("same");
 line2->Draw("same");
 label.DrawLatex(.82,.78,"c)");
  
 P->cd(4);
 Histos[w][s-1][3]->Draw();
 Histos[w][s-1][3]->GetXaxis()->SetTitle(Form("#Delta #theta_{2}   Sector %d            [rad]", s));
 Histos[w][s-1][3]->Fit("gdthb","R");
 TLine *line1 = new TLine(dthbmin[s],0,dthbmin[s],Histos[w][s][3]->GetMaximum());
 TLine *line2 = new TLine(dthbmax[s],0,dthbmax[s],Histos[w][s][3]->GetMaximum());
 line1->SetLineColor(2);
 line2->SetLineColor(2);  
 line1->Draw("same");
 line2->Draw("same");
 label.DrawLatex(.82,.78,"d)");
 
 P->cd(5);
 Histos[w][s-1][4]->Draw();
 Histos[w][s-1][4]->GetXaxis()->SetTitle(Form("#Delta #phi   Sector %d             [deg]", s));
 Histos[w][s-1][4]->Fit("gdphi","R");

 TLine *line1 = new TLine(dphmin[s],0,dphmin[s],Histos[w][s][4]->GetMaximum());
 TLine *line2 = new TLine(dphmax[s],0,dphmax[s],Histos[w][s][4]->GetMaximum());
 line1->SetLineColor(2);
 line2->SetLineColor(2);  
 line1->Draw("same");
 line2->Draw("same");
 label.DrawLatex(.82,.78,"e)");
  
 P->cd(6); 
 label.DrawLatex(.1,.5,"Summary of cuts for sector 2");
 

}
