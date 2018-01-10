void show_EC()
{
 TCanvas *A  = new TCanvas("A",  "A", 700, 480);
 A->SetFillColor(18);
 A->SetGridx();
 A->SetGridy();
 A->Clear();


 gPad->DrawFrame(FIRST_RUN, 0.0.6, LAST_RUN, 1.00);
 sECt->Draw("P");
 mECt->Draw("P");

 la.SetTextColor(4);
  la.DrawLatex(.4,.88, "EC_{t} - SC_{t}");
 la.SetTextColor(4);
 la.SetTextColor(4);
 la.DrawLatex(.65,.91, "Mean");
 la.SetTextColor(2);
 la.DrawLatex(.8,.91, "Sigma");


 if(print==1) A->Print("ec.gif");
// if(print==1) A->Print("ec.eps");
}
