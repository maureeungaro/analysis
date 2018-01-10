void show_yelds()
{
 TCanvas *A[5];
 for(int c=0; c<5; c++)
 {
  A[c]  = new TCanvas(Form("A%d",c),  Form("A%d",c), 700, 480);
  A[c]->SetFillColor(18);
  A[c]->SetGridx();
  A[c]->SetGridy();
  A[c]->Clear();
 }


 A[0]->cd();
 gPad->DrawFrame(43450, 0.0, LAST_RUN, 3);
 TB->Draw("P");
 la.SetTextColor(4);
 la.DrawLatex(.33 ,.9, "Time based tracks / Events");
 la.SetTextColor(4);

 A[1]->cd();
 gPad->DrawFrame(43450, 0.0, LAST_RUN, 4);
 HB->Draw("P");
 la.SetTextColor(4);
 la.DrawLatex(.35 ,.9, "Hit based tracks / Events");
 la.SetTextColor(4);

 A[2]->cd();
 gPad->DrawFrame(43450, 0.0, LAST_RUN, 1);
 TH->Draw("P");
 la.SetTextColor(4);
 la.DrawLatex(.24 ,.9, "Time based tracks / Hit based tracks");
 la.SetTextColor(4);

 A[3]->cd();
 gPad->DrawFrame(43450, 0.0, LAST_RUN, 1.2);
 PR->Draw("P");
 la.SetTextColor(4);
 la.DrawLatex(.42 ,.9, "Protons / Events");
 la.SetTextColor(4);

 A[4]->cd();
 gPad->DrawFrame(43450, 0.0, LAST_RUN, 1000000);
 TOT->Draw("P");
 la.SetTextColor(4);
 la.DrawLatex(.48 ,.9, "Events");
 la.SetTextColor(4);




 for(int c=0; c<5; c++)
 {
  if(print==1) A[c]->Print(Form("counts%d.gif",c+1));
  //if(print==1) A[c]->Print("c.eps");
 }

}
