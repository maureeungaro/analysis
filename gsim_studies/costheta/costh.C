show_costh()
{
   
 TCanvas *C = new TCanvas("C", "C", 800, 800); 
 TPad *CC = new TPad("CC","CC", 0.02, 0.05, 0.98, 0.9);
 CC->Draw();
 CC->Divide(2,2);
 
 title.SetTextSize(0.12);
 
 
 CC->cd(1); 
 invT->Draw();
 LorT->Draw("same"); 
 title.SetTextColor(1);
 title.DrawLatex(0.8, 0.8, "a)");
 
 CC->cd(2); 
 invF->Draw();
 LorF->Draw("same"); 
 title.SetTextColor(1);
 title.DrawLatex(0.8, 0.8, "b)");
 
 CC->cd(3); 
 invR->Draw();
 LorR->Draw("same"); 
 title.SetTextColor(1);
 title.DrawLatex(0.8, 0.8, "c)");
   
 CC->cd(4); 
 title.SetTextSize(0.06); 
 title.SetTextColor(2);
 title.DrawLatex(0.32, 0.85, " - Invariant method");
 title.SetTextColor(4);
 title.DrawLatex(0.32, 0.77, " - Lorentz method");
 
 title.SetTextSize(0.064);  
 title.SetTextColor(1);
 title.DrawLatex(0.25, 0.6, "a)  Generated events "); 
 title.DrawLatex(0.25, 0.42, "b)  Generated events after");   
 title.DrawLatex(0.32, 0.36, "geometrical fiducial cut");     
 title.DrawLatex(0.25, 0.2, "c)  Reconstructed events ");  
 
 C->cd(0);  
 title.SetTextSize(0.036); 
 title.SetTextColor(9);
 title.DrawLatex(0.3, 0.95, Form("Cos #theta^{*} distributions for  Q^{2} = %3.2f", q2_values[iQ2]));
 
 
 
 
}
















