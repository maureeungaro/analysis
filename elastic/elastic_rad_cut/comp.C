{

 TH1F *mmm[4]; 
 TH1F *www[4]; 
 
 TFile f("data.root");
  
 mmm[0] = (TH1F*) f.Get("dt_mm"); 
 mmm[1] = (TH1F*) f.Get("pdt_mm");     
 mmm[2] = (TH1F*) f.Get("p1dt_mm");   
 mmm[3] = (TH1F*) f.Get("p2dt_mm");         
 mmm[0]->GetXaxis()->SetNdivisions(506);
 mmm[0]->GetXaxis()->SetLabelSize(0.04);  
 mmm[0]->GetYaxis()->SetLabelSize(0.04);
 mmm[0]->GetXaxis()->SetLabelOffset(0.02);
 mmm[0]->GetYaxis()->SetLabelOffset(0.02);      
 mmm[0]->GetXaxis()->SetTitleSize(0.05);  
 mmm[0]->GetXaxis()->SetTitleOffset(1.4);
 mmm[0]->GetXaxis()->SetTitle("M_{x}^{ 2}           [GeV^{2}]"); 
 mmm[0]->SetDirectory(0);  
 mmm[1]->SetDirectory(0);  
 mmm[2]->SetDirectory(0);    
 mmm[3]->SetDirectory(0);    
 mmm[3]->SetLineColor(4); 
 
 f.Close();
 
 TFile g("gsim.root"); 
 
 www[0] = (TH1F*) g.Get("dt_mm"); 
 www[1] = (TH1F*) g.Get("pdt_mm");     
 www[2] = (TH1F*) g.Get("p1dt_mm");   
 www[3] = (TH1F*) g.Get("p2dt_mm");         
 www[0]->GetXaxis()->SetNdivisions(506);
 www[0]->GetXaxis()->SetLabelSize(0.04);  
 www[0]->GetYaxis()->SetLabelSize(0.04);
 www[0]->GetXaxis()->SetLabelOffset(0.02);
 www[0]->GetYaxis()->SetLabelOffset(0.02);      
 www[0]->GetXaxis()->SetTitleSize(0.05);  
 www[0]->GetXaxis()->SetTitle("M_{x}^{ 2}           [GeV^{2}]"); 
 www[0]->GetXaxis()->SetTitleOffset(1.4);
 www[0]->SetDirectory(0);  
 www[1]->SetDirectory(0);  
 www[2]->SetDirectory(0);    
 www[3]->SetDirectory(0);     
 www[3]->SetLineColor(4);
 g.Close();
 
 
 TH1F *h1, *h2; 
 h = (TH1F*) mmm[0]->Clone();
 h->Add(mmm[0], mmm[3], 1,-1);
 h->SetLineColor(2);
 
 h2 = (TH1F*) www[0]->Clone();
 h2->Add(www[0], www[3], 1,-1);
 h2->SetLineColor(2);
 
 TLatex title;
 title.SetTextSize(0.08);
 title.SetTextColor(514);
 title.SetNDC();

  
 TCanvas *MMW = new TCanvas("MMW" ,"MMW", 700, 500);
 MMW->Divide(2, 1);
 
 MMW->cd(1);
 mmm[0]->Draw();
 mmm[3]->Draw("same"); 
 h->Draw("same");
 title.DrawLatex(0.43, 0.92, "Data" );
 
 MMW->cd(2);
 www[0]->Draw();
 www[3]->Draw("same"); 
 h2->Draw("same");
 title.DrawLatex(0.4, 0.92, "MonteCarlo" );


}










