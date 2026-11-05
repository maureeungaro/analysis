init_histos()
{
 double SCALE; 

 f = new TFile("data.root") ;
 g = new TFile("gsim.root") ; 
 
 for(int iW=0; iW<NWM; iW++) 
  for(int iQ2=0; iQ2<NQ2; iQ2++) 
   for(int iCT=0; iCT<NCT; iCT++) 
    for(int iPH=0; iPH<NPH; iPH++)     
     {
      mm[iW][iQ2][iCT][iPH]  = (TH1F*) f.Get(Form("mm%d%d%d%d", iW, iQ2, iCT, iPH) ); 
      mmG[iW][iQ2][iCT][iPH] = (TH1F*) g.Get(Form("mm%d%d%d%d", iW, iQ2, iCT, iPH) );       
      
      SCALEMM[iW][iQ2][iCT][iPH] = (double) mm[iW][iQ2][iCT][iPH]->GetSum() / (double) mmG[iW][iQ2][iCT][iPH]->GetSum() ;
         
      mmG[iW][iQ2][iCT][iPH]->Scale(SCALEMM[iW][iQ2][iCT][iPH]);
      mmG[iW][iQ2][iCT][iPH]->SetLineColor(2);
      
      mm[iW][iQ2][iCT][iPH]->GetXaxis()->SetLabelSize(0.076);
      mm[iW][iQ2][iCT][iPH]->GetYaxis()->SetLabelSize(0.076);
      mm[iW][iQ2][iCT][iPH]->GetXaxis()->SetLabelFont(52);
      mm[iW][iQ2][iCT][iPH]->GetYaxis()->SetLabelFont(52);
            
      mm[iW][iQ2][iCT][iPH]->GetXaxis()->SetNdivisions(505);
      mm[iW][iQ2][iCT][iPH]->GetYaxis()->SetNdivisions(506);
            
      mm[iW][iQ2][iCT][iPH]->GetXaxis()->SetLabelOffset(0.016);  
      mm[iW][iQ2][iCT][iPH]->GetYaxis()->SetLabelOffset(0.016);            
      
      mm[iW][iQ2][iCT][iPH]->SetDirectory(0);				          
      mmG[iW][iQ2][iCT][iPH]->SetDirectory(0);				    
     }

     
 for(int iQ2=0; iQ2<NQ2; iQ2++) 
  for(int iCT=0; iCT<NCT; iCT++) 
   for(int iPH=0; iPH<NPH; iPH++)     
    {
     ww[iQ2][iCT][iPH]  = (TH1F*) f.Get(Form("W%d%d%d", iQ2, iCT, iPH) ); 
     wwG[iQ2][iCT][iPH] = (TH1F*) g.Get(Form("W%d%d%d", iQ2, iCT, iPH) );       
      
     SCALEWM[iQ2][iCT][iPH] = (double) ww[iQ2][iCT][iPH]->GetSum() / (double) wwG[iQ2][iCT][iPH]->GetSum() ;    
     
     wwG[iQ2][iCT][iPH]->Scale(SCALEWM[iQ2][iCT][iPH]);
     wwG[iQ2][iCT][iPH]->SetLineColor(2);
      
     ww[iQ2][iCT][iPH]->GetXaxis()->SetLabelSize(0.076);
     ww[iQ2][iCT][iPH]->GetYaxis()->SetLabelSize(0.076);   
     ww[iQ2][iCT][iPH]->GetXaxis()->SetLabelFont(52);
     ww[iQ2][iCT][iPH]->GetYaxis()->SetLabelFont(52);
        
     ww[iQ2][iCT][iPH]->GetXaxis()->SetNdivisions(505);
     ww[iQ2][iCT][iPH]->GetYaxis()->SetNdivisions(506);     
     ww[iQ2][iCT][iPH]->GetXaxis()->SetLabelOffset(0.016);  
     ww[iQ2][iCT][iPH]->GetYaxis()->SetLabelOffset(0.016);            
      
     ww[iQ2][iCT][iPH]->SetDirectory(0);				          
     wwG[iQ2][iCT][iPH]->SetDirectory(0);				    
    }
     
     

}
