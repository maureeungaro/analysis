void show_RF(int what)
{
 TCanvas *A  = new TCanvas("A",  "A", 700, 480);
 A->SetFillColor(18);
 A->SetGridx();
 A->SetGridy();
 A->Clear();

 string printeps[6] = {"rf.eps", "srfP.eps","srfpp.eps", "srfpm.eps", "stsrfpp.eps", "stsrfpm.eps"};
 string printgif[6] = {"rf.gif", "srfP.gif","srfpp.gif", "srfpm.gif", "stsrfpp.gif", "stsrfpm.gif"};


 if(what==5)
 {
  gPad->DrawFrame(43450, -0.5, LAST_RUN, 0.7);
  sRFstpp->Draw("P");
  RFstpp->Draw("P");
  la.SetTextColor(1);
  la.DrawLatex(.2,.91, "ST #pi^{+}    RF");
  la.SetTextColor(4);
  la.DrawLatex(.65,.91, "Mean");
  la.SetTextColor(2);
  la.DrawLatex(.8,.91, "Sigma");
 }

 if(what==6)
 {
  gPad->DrawFrame(43450, -0.5, LAST_RUN, 0.7);
  sRFstpm->Draw("P");
  RFstpm->Draw("P");
  la.SetTextColor(1);
  la.DrawLatex(.2,.91, "ST #pi^{-}    RF");
  la.SetTextColor(4);
  la.DrawLatex(.65,.91, "Mean");
  la.SetTextColor(2);
  la.DrawLatex(.8,.91, "Sigma");
 }






// if(print==1) A->Print(printeps[what-1].c_str());
 if(print==1) A->Print(printgif[what-1].c_str());
}
