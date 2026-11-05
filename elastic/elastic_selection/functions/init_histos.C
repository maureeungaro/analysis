void init_histos(TH1F *Histos[2][7][5])
{
 string bank[2]  = {"part_","evnt_"};
 string var[5]   = {"W_", "mmeP_", "dth_", "dthb_","dphi_"};
 string sect1[7] = {"sec1_z","sec2_z", "sec3_z", "sec4_z", "sec5_z", "sec6_z", "sec7_z"}; 
 string sect2[7] = {"sec1",  "sec2",   "sec3",   "sec4",   "sec5",   "sec6",   "sec7"}; 
 
 string title;

 cout << " Getting histograms from file." << endl;
 
 for(int b=0; b<1; b++)
 {
  for(int w=0; w<5; w++)  
  {
   for(int s=0; s<7; s++)
   {
    title = bank[b];
    title.insert(5, var[w]);
    if(w  < 2) title.append(sect1[s]);
    if(w >= 2) title.append(sect2[s]);

    Histos[b][s][w] = (TH1F*) f->Get(title.c_str());

    Histos[b][s][w]->Sumw2();
    Histos[b][s][w]->SetLabelSize(.06,"X");
    Histos[b][s][w]->SetLabelSize(.06,"Y");
    Histos[b][s][w]->SetLabelOffset(.016,"Y");
    Histos[b][s][w]->SetLabelOffset(.024,"X");
    Histos[b][s][w]->SetTitleSize(.08,"X");
    //Histos[b][s][w]->SetTitleSize(.07,"Y");
    Histos[b][s][w]->SetTitleOffset(1.4,"X");
    Histos[b][s][w]->SetTitleOffset(1.7,"Y");
    Histos[b][s][w]->GetXaxis()->SetAxisColor(1);    
    Histos[b][s][w]->GetYaxis()->SetAxisColor(1);
    Histos[b][s][w]->GetXaxis()->SetNdivisions(506);
    Histos[b][s][w]->GetYaxis()->SetNdivisions(506);    
    Histos[b][s][w]->GetXaxis()->SetTickLength(.02);
    Histos[b][s][w]->GetYaxis()->SetTickLength(.02);
   }
  }
 }

}

