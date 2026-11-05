{
 gStyle->SetOptStat(0);
 TLatex title;

 double SCALE1 = 1./100.;


 TCanvas *MM = new TCanvas("MM", "MM", 700, 500);
  
 TFile MC("mc.root");
 TH1F *mm1 = new TH1F("mm1", "mm1", 100, -0.03, 0.1);
 TH1F *mm2 = new TH1F("mm2", "mm2", 100, -0.03, 0.1);
 
  
 TFile DATA("data.root");
 TH1F *mm3 = new TH1F("mm3", "mm3", 100, -0.03, 0.1);  
 TH1F *mm4 = new TH1F("mm4", "mm4", 100, -0.03, 0.1);   
  
  
 MC.cd();
 t->Draw("mcK.mmeP >> mm1", "mcK.W > 0 && mcK.mmeP > -0.05 && mcK.mmeP < 0.1 && mcK.Q2>2 && mcK.Q2 < 5");
 t->Draw(" pK.mmeP >> mm2", " pK.W > 0 &&  pK.mmeP > -0.05 &&  pK.mmeP < 0.1 &&  pK.Q2>2 &&  pK.Q2 < 5");
 
 DATA.cd();
 t->Draw(" pK.mmeP         >> mm3", " pK.W > 0 &&  pK.mmeP > -0.05 &&  pK.mmeP < 0.1 &&  pK.Q2>2 &&  pK.Q2 < 5");
 t->Draw(" pK.mmeP + 0.005 >> mm4", " pK.W > 0 &&  pK.mmeP > -0.05 &&  pK.mmeP < 0.1 &&  pK.Q2>2 &&  pK.Q2 < 5"); 
 
 double SCALE2 =  (double) mm2->GetSum()/ (double) mm3->GetSum();
 
 mm1->Scale(SCALE1); 
 mm3->Scale(SCALE2);  
 mm4->Scale(SCALE2);   
// mm3->Scale(0.96);
 
 
 mm1->SetLineStyle(2);
 mm1->SetLineWidth(1);
 mm2->SetLineColor(4);
 mm3->SetLineColor(2); 
 mm4->SetLineColor(50); 
 mm4->SetLineStyle(4);  
 mm1->SetLineWidth(2);
  
 mm1->Draw();
 mm2->Draw("same");
 mm3->Draw("same"); 
 mm4->Draw("same");   

 title.SetNDC();
 title.SetTextFont(52);
 title.SetTextSize(0.034);
 
 title.SetTextColor(1);
 title.DrawLatex(0.6, 0.8,   " -- MC generated");
 title.SetTextColor(4);
 title.DrawLatex(0.6, 0.75,  " -- GSIM reconstructed");
 title.SetTextColor(2);
 title.DrawLatex(0.6, 0.7,   " -- Data");
 title.SetTextColor(50);
 title.DrawLatex(0.6, 0.65,  " -- Data shifted by 0.005 GeV^{2}");
 
 
}












