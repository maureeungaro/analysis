{
 gStyle->SetOptStat(0);
 TLatex title;

 double SCALE1 = 1./5.;


 TCanvas *W = new TCanvas("W", "W", 700, 500);
  
 TFile MC("mc.root");
 TH1F *w1 = new TH1F("w1", "w1", 100, 1., 1.5);
 TH1F *w2 = new TH1F("w2", "w2", 100, 1., 1.5);
 
  
 TFile DATA("data.root");
 TH1F *w3 = new TH1F("w3", "w3", 100, 1., 1.5);  
 TH1F *w4 = new TH1F("w4", "w4", 100, 1., 1.5);   
  
  
 MC.cd();
 t->Draw("mcK.W >> w1", "mcK.W > 0 && mcK.W < 1.4 && mcK.Q2>2 && mcK.Q2 < 4 && mcK.mmeP > -0.02 && mcK.mmeP < 0.05");
 t->Draw(" pK.W >> w2", " pK.W > 0 &&  pK.W < 1.4 &&  pK.Q2>2 &&  pK.Q2 < 4 &&  pK.mmeP > -0.02 &&  pK.mmeP < 0.05");
 
 DATA.cd();
 t->Draw(" pK.W         >> w3", " pK.W > 0  &&  pK.W < 1.4 &&   pK.Q2>2 &&  pK.Q2 < 4 &&  pK.mmeP > -0.02 &&  pK.mmeP < 0.045 ");
// t->Draw(" pK.W + 0.005 >> w4", " pK.W > 0 &&   pK.Q2>2 &&  pK.Q2 < 5"); 
 
 double SCALE2 =  (double) w2->GetSum()/ (double) w3->GetSum();
 
 w1->Scale(SCALE1); 
 w3->Scale(SCALE2);  
 w4->Scale(SCALE2);   
// w3->Scale(0.96);
 
 
 w1->SetLineStyle(2);
 w1->SetLineWidth(1);
 w2->SetLineColor(4);
 w3->SetLineColor(2); 
 w4->SetLineColor(50); 
 w4->SetLineStyle(4);  
 w1->SetLineWidth(2);
  
 w1->Draw();
 w2->Draw("same");
 w3->Draw("same"); 
// w4->Draw("same");   

 title.SetNDC();
 title.SetTextFont(52);
 title.SetTextSize(0.034);
 
 title.SetTextColor(1);
 title.DrawLatex(0.2, 0.8,   " -- MC generated");
 title.SetTextColor(4);
 title.DrawLatex(0.2, 0.75,  " -- GSIM reconstructed");
 title.SetTextColor(2);
 title.DrawLatex(0.2, 0.7,   " -- Data");
// title.SetTextColor(50);
// title.DrawLatex(0.6, 0.65,  " -- Data shifted by 0.005 GeV^{2}");
 
 



}












