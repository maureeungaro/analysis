init_histos()
{
 LorT = (TH1F*) f->Get(Form("Costh_loren_noc_Q2_%f", q2_values[iQ2]));
 LorF = (TH1F*) f->Get(Form("Costh_loren_fid_Q2_%f", q2_values[iQ2])); 
 LorR = (TH1F*) f->Get(Form("Costh_loren_rec_Q2_%f", q2_values[iQ2])); 
 invT = (TH1F*) f->Get(Form("Costh_invar_noc_Q2_%f", q2_values[iQ2]));
 invF = (TH1F*) f->Get(Form("Costh_invar_fid_Q2_%f", q2_values[iQ2])); 
 invR = (TH1F*) f->Get(Form("Costh_invar_rec_Q2_%f", q2_values[iQ2])); 
 
  
 LorT->GetXaxis()->SetTitle("cos #theta^{*}");
 invT->GetXaxis()->SetTitle("cos #theta^{*}"); 
 LorR->GetXaxis()->SetTitle("cos #theta^{*}");
 invR->GetXaxis()->SetTitle("cos #theta^{*}"); 
 LorF->GetXaxis()->SetTitle("cos #theta^{*}");
 invF->GetXaxis()->SetTitle("cos #theta^{*}"); 
 
 LorT->GetXaxis()->SetTitleSize(0.06);
 invT->GetXaxis()->SetTitleSize(0.06);
 LorR->GetXaxis()->SetTitleSize(0.06);
 invR->GetXaxis()->SetTitleSize(0.06);
 LorF->GetXaxis()->SetTitleSize(0.06);
 invF->GetXaxis()->SetTitleSize(0.06);
  
 invT->GetXaxis()->CenterTitle(1); 
 LorT->GetXaxis()->CenterTitle(1);  
 invR->GetXaxis()->CenterTitle(1); 
 LorR->GetXaxis()->CenterTitle(1);  
 invF->GetXaxis()->CenterTitle(1); 
 LorF->GetXaxis()->CenterTitle(1);  
    
 LorT->Scale(1.0/LorT->GetSum());
 LorR->Scale(1.0/LorR->GetSum()); 
 LorF->Scale(1.0/LorF->GetSum());  
 invT->Scale(1.0/invT->GetSum());
 invR->Scale(1.0/invR->GetSum()); 
 invF->Scale(1.0/invF->GetSum());  
 
 LorT->SetLineColor(4); 
 invT->SetLineColor(2);  
 LorF->SetLineColor(4); 
 invF->SetLineColor(2);    
 LorR->SetLineColor(4);
 invR->SetLineColor(2);     

 
 // -------------------------
 
 dLorT = (TH1F*) f->Get(Form("diff_costh_loren_thr_Q2_%f", q2_values[iQ2])); 
 dLorF = (TH1F*) f->Get(Form("diff_costh_loren_rec_Q2_%f", q2_values[iQ2]));  
 
 dinvT = (TH1F*) f->Get(Form("diff_costh_invar_thr_Q2_%f", q2_values[iQ2])); 
 dinvF = (TH1F*) f->Get(Form("diff_costh_invar_rec_Q2_%f", q2_values[iQ2]));  
 
 
 dLorT->SetLineColor(4); 
 dinvT->SetLineColor(2);  
 dLorF->SetLineColor(4); 
 dinvF->SetLineColor(2);    

   
 dLorTt = (TH2F*) f->Get(Form("diff_costh_th_loren_thr_Q2_%f", q2_values[iQ2])); 
 dLorFt = (TH2F*) f->Get(Form("diff_costh_th_loren_rec_Q2_%f", q2_values[iQ2]));  
 
 dinvTt = (TH2F*) f->Get(Form("diff_costh_th_invar_thr_Q2_%f", q2_values[iQ2])); 
 dinvFt = (TH2F*) f->Get(Form("diff_costh_th_invar_rec_Q2_%f", q2_values[iQ2]));  
   
 
 dLorT->GetXaxis()->SetTitle("#Delta #theta^{*}                  [deg]");
 dLorF->GetXaxis()->SetTitle("#Delta #theta^{*}                  [deg]"); 
 dLorTt->GetYaxis()->SetTitle("#Delta #theta^{*}          [deg]");
 dinvTt->GetYaxis()->SetTitle("#Delta #theta^{*}          [deg]"); 
 dLorTt->GetXaxis()->SetTitle("#theta^{lab}_{P}                  [deg]");
 dinvTt->GetXaxis()->SetTitle("#theta^{lab}_{P}                  [deg]"); 
 
 
 dLorT->GetXaxis()->SetTitleSize(0.06);
 dLorF->GetXaxis()->SetTitleSize(0.06); 
 dLorTt->GetXaxis()->SetTitleSize(0.06);
 dinvTt->GetXaxis()->SetTitleSize(0.06); 
 dLorTt->GetYaxis()->SetTitleSize(0.06);
 dinvTt->GetYaxis()->SetTitleSize(0.06); 
 
 
 
 
 


}
