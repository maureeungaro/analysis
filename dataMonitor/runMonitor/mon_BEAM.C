void show_beam(int what)
{
 TCanvas *A  = new TCanvas("A",  "A", 700, 480);
 A->SetFillColor(18);
 A->SetGridx();
 A->SetGridy();
 A->Clear();

 string printeps[2] = {"xb.eps", "yb.eps"};
 string printgif[2] = {"xb.gif", "yb.gif"};

 if(what==1)
 {
  gPad->DrawFrame(43450, -0.3, LAST_RUN, 0.8);
  xb->Draw("P");
  sxb->Draw("P");

  la.SetTextColor(1);
  la.DrawLatex(.2,.91, "Reconstructed X vertex");
  la.SetTextColor(4);
  la.DrawLatex(.65,.91, "Mean");
  la.SetTextColor(2);
  la.DrawLatex(.8,.91, "Sigma");
 }

 if(what==2)
 {
  gPad->DrawFrame(43450, -0.4, LAST_RUN, 0.8);
  yb->Draw("P");
  syb->Draw("P");
  la.SetTextColor(1);
  la.DrawLatex(.2,.91, "Reconstructed Y vertex");
  la.SetTextColor(4);
  la.DrawLatex(.65,.91, "Mean");
  la.SetTextColor(2);
  la.DrawLatex(.8,.91, "Sigma");
 }






// if(print==1) A->Print(printeps[what-1].c_str());
 if(print==1) A->Print(printgif[what-1].c_str());
}
