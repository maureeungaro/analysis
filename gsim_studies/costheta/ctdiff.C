show_ctdiff()
{


 TCanvas *Cd = new TCanvas("Cd", "Cd", 800, 800); 
 TPad *CCd = new TPad("CCd","CCd", 0.02, 0.05, 0.96, 0.85);
 CCd->Draw();
 CCd->Divide(2,2);
 
 title.SetTextSize(0.08);
 
 CCd->cd(1); 
 dLorT->Draw();
 dinvT->Draw("same"); 
 title.SetTextColor(1);
 title.DrawLatex(0.2, 0.94, "Generated - Reconstructed");

 CCd->cd(2); 
 dLorF->Draw();
 dinvF->Draw("same"); 
 title.SetTextColor(1);
 title.DrawLatex(0.1, 0.94, "Generated (fiducial) - Reconstructed");

 
 CCd->cd(3); 
 dinvTt->Draw("cont colz");
 CCd->Update();
 TPaletteAxis *palette;
 palette = (TPaletteAxis*)dinvTt->FindObject("palette");
 palette->SetLabelSize(0.05);

 palette->SetLabelOffset(0.016);
 palette->SetBorderSize(10);
 palette->SetX1NDC(0.82);
 palette->SetX2NDC(0.86);  
 dinvTt->Draw("cont1 colz");
 title.SetTextColor(1);
 title.DrawLatex(0.15, 0.01, "Generated - Invariant method");

 
 
 CCd->cd(4); 
 dLorTt->Draw("cont colz");
 CCd->Update();
 TPaletteAxis *palette2;
 palette2 = (TPaletteAxis*)dLorTt->FindObject("palette");
 palette2->SetLabelSize(0.05);

 palette2->SetLabelOffset(0.016);
 palette2->SetBorderSize(10);
 palette2->SetX1NDC(0.82);
 palette2->SetX2NDC(0.86);  
 dLorTt->Draw("cont1 colz"); 
 title.SetTextColor(1);
 title.DrawLatex(0.15, 0.02, "Generated - Lorentz method");

 Cd->cd(0);  
 title.SetTextSize(0.036); 
 title.SetTextColor(9);
 title.DrawLatex(0.2, 0.95, Form("#Delta#theta^{*} = #theta^{*}_{gen} - #theta^{*}_{rec} distributions for  Q^{2} = %3.2f", q2_values[iQ2]));


 title.SetTextSize(0.026); 
 title.SetTextColor(2);
 title.DrawLatex(0.3, 0.9, " - Invariant method");
 title.SetTextColor(4);
 title.DrawLatex(0.5, 0.9, " - Lorentz method");

 
 
 
 
 
}














