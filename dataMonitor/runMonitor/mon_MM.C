void show_mm()
{
 TCanvas *A[4];
 string C[4] = {"mmPpp", "mmpppm", "mmkPl", "mmkPs"};
 for(int i=0; i<4; i++)
  A[i]  = new TCanvas(C[i].c_str(),  C[i].c_str(), 700, 480);

 TGaxis *axis1, *axis2, *axis3;
 TH1F *hframe1, *hframe2, *hframe3;
 gStyle->SetLabelColor(4, "Y");
 gStyle->SetAxisColor(4, "Y");

 A[0]->cd();
 gPad->DrawFrame(FIRST_RUN, 0.005, LAST_RUN, 0.028);
 mm_p_pip->Draw("P");
 smm_p_pip->Draw("P");
 la.SetTextColor(1);
 la.DrawLatex(.2,.91, "Missing mass^{2}   ( P #pi^{+} )");
 la.SetTextColor(4);
 la.DrawLatex(.65,.91, "Mean");
 la.SetTextColor(2);
 la.DrawLatex(.8,.91, "Sigma");

 A[1]->cd();
 gPad->DrawFrame(FIRST_RUN, 0.93, LAST_RUN, 0.95);
 mm_pip_pim->Draw("P");

 TPad *overlay3 = new TPad("overlay3","",0,0,1,1);
 overlay3->SetFillStyle(4000);
 overlay3->SetFillColor(0);
 overlay3->SetFrameFillStyle(4000);
 overlay3->Draw();
 overlay3->cd();
 hframe3 = overlay3->DrawFrame(FIRST_RUN, 0., LAST_RUN, 0.03);
 hframe3->GetXaxis()->SetLabelOffset(99);
 hframe3->GetYaxis()->SetLabelOffset(99);
 hframe3->GetYaxis()->SetTickLength(0);

 smm_pip_pim->Draw("P");
 axis3 = new TGaxis(LAST_RUN, 0.0, LAST_RUN, 0.03, 0.0, 0.03, 505, "+L");
 axis3->SetLineColor(kRed);
 axis3->SetLabelColor(kRed);
 axis3->Draw();

 la.SetTextColor(1);
 la.DrawLatex(.2,.91, "Missing mass   (#pi^{+}  #pi^{-} )");
 la.SetTextColor(4);
 la.DrawLatex(.65,.91, "Mean");
 la.SetTextColor(2);
 la.DrawLatex(.8,.91, "Sigma");

 A[2]->cd();
 gPad->DrawFrame(FIRST_RUN, 1.1, LAST_RUN, 1.12);
 mm_kp_lambda->Draw("P");

 TPad *overlay = new TPad("overlay","",0,0,1,1);
 overlay->SetFillStyle(4000);
 overlay->SetFillColor(0);
 overlay->SetFrameFillStyle(4000);
 overlay->Draw();
 overlay->cd();
 hframe1 = overlay->DrawFrame(FIRST_RUN, -0.005, LAST_RUN, 0.04);
 hframe1->GetXaxis()->SetLabelOffset(99);
 hframe1->GetYaxis()->SetLabelOffset(99);
 hframe1->GetYaxis()->SetTickLength(0);

 smm_kp_lambda->Draw("P");
 axis1 = new TGaxis(LAST_RUN, -0.005, LAST_RUN, 0.04, -0.005, 0.04, 505, "+L");
 axis1->SetLineColor(kRed);
 axis1->SetLabelColor(kRed);
 axis1->Draw();
 la.SetTextColor(1);
 la.DrawLatex(.2,.91, "Missing mass   (k  P [#Lambda])");
 la.SetTextColor(4);
 la.DrawLatex(.65,.91, "Mean");
 la.SetTextColor(2);
 la.DrawLatex(.8,.91, "Sigma");

 A[3]->cd();
 gPad->DrawFrame(FIRST_RUN, 1.18, LAST_RUN, 1.196);
 mm_kp_sigma->Draw("P");


 TPad *overlay2 = new TPad("overlay2","",0,0,1,1);
 overlay2->SetFillStyle(4000);
 overlay2->SetFillColor(0);
 overlay2->SetFrameFillStyle(4000);
 overlay2->Draw();
 overlay2->cd();
 hframe2 = overlay->DrawFrame(FIRST_RUN, 0.001, LAST_RUN, 0.02);
 hframe2->GetXaxis()->SetLabelOffset(99);
 hframe2->GetYaxis()->SetLabelOffset(99);
 hframe2->GetYaxis()->SetTickLength(0);

 smm_kp_sigma->Draw("P");
 axis2 = new TGaxis(LAST_RUN, 0.001, LAST_RUN, 0.02, 0.001, 0.02, 505, "+L");
 axis2->SetLineColor(kRed);
 axis2->SetLabelColor(kRed);
 axis2->Draw();
 la.SetTextColor(1);
 la.DrawLatex(.2,.91, "Missing mass   (k P [#Sigma] )");
 la.SetTextColor(4);
 la.DrawLatex(.65,.91, "Mean");
 la.SetTextColor(2);
 la.DrawLatex(.8,.91, "Sigma");




// if(print==1) A->Print(printeps[what-1].c_str());
 if(print==1) for(int i=0; i<4; i++) A[i]->Print(Form("%s.gif", C[i].c_str()));
}










