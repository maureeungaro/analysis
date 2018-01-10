void show_DC(int what)
{
 TCanvas *A  = new TCanvas("A",  "A", 700, 480);
 A->SetFillColor(18);
 A->SetGridx();
 A->SetGridy();
 A->Clear();

 string printc[2] = {"dc_mean", "dc_sigm"};

 TLegend *SL = new TLegend(0.84, 0.75, 1, 0.98);
 SL->SetFillColor(18);
 SL->SetLineColor(18);
// SL->SetFillStyle(0);
 string SLS[6] = {"Superlayer1", "Superlayer2","Superlayer3","Superlayer4","Superlayer5","Superlayer6"};


 if(what==1)
 {
  gPad->DrawFrame(43450, -200, LAST_RUN, 100);
  for(int l=0; l<6; l++)
  {
   DC_res_mean[l]->Draw("P");
   SL->AddEntry(DC_res_mean[l], SLS[l].c_str());
  }
  la.SetTextColor(4);
  la.DrawLatex(.16,.91, "DC Mean for different superlayers (all sectors)");
 }

 if(what==2)
 {
  gPad->DrawFrame(43450, 180, LAST_RUN, 340);
  for(int l=0; l<6; l++)
  {
   DC_res_sigm[l]->Draw("P");
   SL->AddEntry(DC_res_sigm[l], SLS[l].c_str());
  }
  la.SetTextColor(4);
  la.DrawLatex(.16,.91, "DC Sigma for different superlayers (all sectors)");
 }

 if(what>=10 && what <20)
 {
  gPad->DrawFrame(43450, -200, LAST_RUN, 120);
  for(int l=0; l<6; l++)
  {
   DC_mean[what-10][l]->Draw("P");
   SL->AddEntry(DC_mean[what-10][l], SLS[l].c_str());
  }
  la.SetTextColor(4);
  la.DrawLatex(.18,.91, Form("DC Mean for different superlayers - sector %d", what-9));
 }

 if(what>=20 && what <30)
 {
  gPad->DrawFrame(43450, 180, LAST_RUN, 360);
  for(int l=0; l<6; l++)
  {
   DC_sigm[what-20][l]->Draw("P");
   SL->AddEntry(DC_sigm[what-20][l], SLS[l].c_str());
  }
  la.SetTextColor(4);
  la.DrawLatex(.18,.91, Form("DC Sigma for different superlayers - sector %d", what-19));
 }

 SL->Draw();

 if(print==1)
 {
  if(what<10)
  {
//   A->Print(Form("%s_all.eps", printc[what-1].c_str()));
   A->Print(Form("%s_all.gif", printc[what-1].c_str()));
  }
  if(what>=10 && what <20)
  {
//   A->Print(Form("%s_sec%d.eps", printc[0].c_str(), what%10 + 1));
   A->Print(Form("%s_sec%d.gif", printc[0].c_str(), what%10 + 1));
  }
  if(what>=20 && what <30)
  {
//   A->Print(Form("%s_sec%d.eps", printc[1].c_str(), what%10 + 1));
   A->Print(Form("%s_sec%d.gif", printc[1].c_str(), what%10 + 1));
  }

 }



}














