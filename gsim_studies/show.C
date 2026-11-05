show_mm()
{
 gStyle->SetFrameLineColor(0);
 TLatex title;
 title.SetTextFont(12);
 title.SetNDC();

 TCanvas *C = new TCanvas("C","Gsim/Data comparison: mm", 900, 900);
 TPad  *CC  = new TPad("CC", "CC", 0.1, 0.1, 0.98, 0.9);

 CC->Draw();
 CC->Divide(4,4);
 
 for(int iCT = 0; iCT < NCT; iCT++)
  for(int iPH = 0; iPH < NPH; iPH++)
  {
   CC->cd(iCT + 1 + iPH*4);
   gPad->SetGrid(1,1);
   mm[iWM][iQ2][iCT][iPH]->Draw();
   mmG[iWM][iQ2][iCT][iPH]->Draw("same");   
   title.SetTextColor(4);
   title.SetTextSize(0.1);   
   title.DrawLatex(0.18, 0.06, Form("cos#theta = %s    #phi = %s", Cts[iCT].c_str(), Phs[iPH].c_str() ) );
   title.SetTextColor(1);  
   title.SetTextSize(0.14);   
   title.DrawLatex(0.62, 0.82, Form("R=%3.1f", 1.0/SCALEMM[iWM][iQ2][iCT][iPH]) );   
   
  }
 
 C->cd();
 title.SetTextSize(0.04);
 title.SetTextColor(50); 
 title.DrawLatex(0.28, 0.93, Form("W = %s #pm 0.05     Q^{ 2} = %s #pm 0.35", Ws[iWM].c_str(), Qs[iQ2].c_str() ) );
 
 title.SetTextAngle(90);
 title.DrawLatex(0.06, 0.5, "#leftarrow #phi" );
 title.SetTextAngle(0);
 title.DrawLatex(0.5, 0.04, "cos #theta #rightarrow" );
   
 if(PRINT) C->Print(Form("W%d_Q2%d.gif", iWM + 1, iQ2));
  
}

show_ww()
{
 gStyle->SetFrameLineColor(0);

 TLatex title;
 title.SetTextFont(12);
 title.SetNDC();

 TCanvas *C2 = new TCanvas("C2","Gsim/Data comparison: W", 900, 900);
 TPad  *CC2  = new TPad("CC2", "CC2", 0.1, 0.1, 0.98, 0.9);

 CC2->Draw();
 CC2->Divide(4,4);
 
 for(int iCT = 0; iCT < NCT; iCT++)
  for(int iPH = 0; iPH < NPH; iPH++)
  {
   CC2->cd(iCT + 1 + iPH*4);
   gPad->SetGrid(1,1);
   ww[iQ2][iCT][iPH]->Draw();
   wwG[iQ2][iCT][iPH]->Draw("same"); 
   title.SetTextColor(4);  
   title.SetTextSize(0.1);
   title.DrawLatex(0.18, 0.06, Form("cos#theta = %s    #phi = %s", Cts[iCT].c_str(), Phs[iPH].c_str() ) );
   title.SetTextColor(1);   
   title.SetTextSize(0.14);
   title.DrawLatex(0.4, 0.32, Form("R = %3.1f", 1.0/SCALEWM[iQ2][iCT][iPH]) );   
   
  }
 
 C2->cd();
 title.SetTextSize(0.04);
 title.SetTextColor(50); 
 title.DrawLatex(0.4, 0.93, Form("  Q^{ 2} = %s #pm 0.35", Qs[iQ2].c_str() ) );
 
 title.SetTextAngle(90);
 title.DrawLatex(0.06, 0.5, "#leftarrow #phi" );
 title.SetTextAngle(0);
 title.DrawLatex(0.5, 0.04, "cos #theta #rightarrow" );

 
 
 if(PRINT) C2->Print(Form("Q2%d.gif", iQ2));  
}

