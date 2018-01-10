void show_CPU()
{
 TCanvas *A  = new TCanvas("A",  "A", 700, 480);
 A->SetFillColor(18);
 A->SetGridx();
 A->SetGridy();
 A->Clear();


  gPad->DrawFrame(43450, -2, LAST_RUN, 26);
  cpu->Draw("P");


  la.SetTextColor(4);
  la.DrawLatex(.3,.91, "CPU Process Time (one file, hours)");
  la.SetTextColor(4);


 if(print==1) A->Print("cpu.gif");
// if(print==1) A->Print("cpu.eps");
}
