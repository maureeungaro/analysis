void Show_occupancy(int Z)
{
 TCanvas *NCY = new TCanvas("NCY","Occupancy and efficiency", 700, 800);

 NCY->Divide(2,2);

 NCY->cd(1);
 NCY_1->SetTheta(36);
 NCY_1->SetPhi(-60);
 if(Z) Occu[0][SECT_1]->GetXaxis()->SetRangeUser(WIRE_1 - 16, WIRE_1 + 16);
 if(Z) Occu[0][SECT_1]->GetYaxis()->SetRangeUser(LAYER_1 - 12, LAYER_1 + 12);
 Occu[0][SECT_1]->Draw("lego2");

 NCY->cd(2);
 NCY_2->SetTheta(36);
 NCY_2->SetPhi(-60);
 if(Z) Occu[0][SECT_2]->GetXaxis()->SetRangeUser(WIRE_2 - 16, WIRE_2 + 16);
 if(Z) Occu[0][SECT_2]->GetYaxis()->SetRangeUser(LAYER_2 - 12, LAYER_2 + 12);
 Occu[0][SECT_2]->Draw("lego2");


 NCY->cd(3);
 NCY_3->SetTheta(36);
 NCY_3->SetPhi(-60);
 if(Z) Effi[0][SECT_1]->GetXaxis()->SetRangeUser(WIRE_1 - 16, WIRE_1 + 16);
 if(Z) Effi[0][SECT_1]->GetYaxis()->SetRangeUser(LAYER_1 - 12, LAYER_1 + 12);
 Effi[0][SECT_1]->Draw("lego2");

 NCY->cd(4);
 NCY_4->SetTheta(36);
 NCY_4->SetPhi(-60);
 if(Z) Effi[0][SECT_2]->GetXaxis()->SetRangeUser(WIRE_1 - 16, WIRE_1 + 16);
 if(Z) Effi[0][SECT_2]->GetYaxis()->SetRangeUser(LAYER_1 - 12, LAYER_1 + 12);
 Effi[0][SECT_2]->Draw("lego2");


}


void Show_timing_occ()
{

 for(int i=0; i<NFILES; i++)
 {
  OCCU1[i] = Occu[i][SECT_1-1]->GetBinContent(WIRE_1, LAYER_1);
  OCCU2[i] = Occu[i][SECT_2-1]->GetBinContent(WIRE_2, LAYER_2);
 }

 COMP1 = new TGraph(NFILES, X,     OCCU1);
 COMP2 = new TGraph(NFILES, X,     OCCU2);
 CORR  = new TGraph(NFILES, OCCU1, OCCU2);

 TCanvas *COMP = new TCanvas("COMP","Selected wire occupancy",  500,700);
 COMP->Divide(1,3);
 COMP->cd(1);
 COMP1->Draw("AP");

 COMP->cd(2);
 COMP2->Draw("AP");

 COMP->cd(3);
 CORR->Draw("AP");

}

void Show_timing_eff()
{

 for(int i=0; i<NFILES; i++)
 {
  EFFI1[i] = Effi[i][SECT_1-1]->GetBinContent(WIRE_1, LAYER_1);
  EFFI2[i] = Effi[i][SECT_2-1]->GetBinContent(WIRE_2, LAYER_2);
 }

 EFF1   = new TGraph(NFILES, X,     EFFI1);
 EFF2   = new TGraph(NFILES, X,     EFFI2);
 CORRE  = new TGraph(NFILES, EFFI1, EFFI2);

 TCanvas *COMP = new TCanvas("COMP","Selected wire occupancy",  500,700);
 COMP->Divide(1,3);
 COMP->cd(1);
 EFF1->Draw("AP");

 COMP->cd(2);
 EFF2->Draw("AP");

 COMP->cd(3);
 CORRE->SetMinimum(0.4);
 CORRE->SetMaximum(1.2);
 CORRE->GetHistogram()->GetXaxis()->SetRangeUser(0.4,1.2);
 CORRE->Draw("AP");

}

void init_histos()
{

 cout << endl << " Initializing occupancy histos..." << endl << endl;
 ifstream IN("list_occu");
 char file[300];
 char his[100];
 for(int i=0; i<NFILES && IN; i++)
 {
  IN >> file ;
  TFile f(file);
  for(int s=0; s<6; s++)
  {
   sprintf(his, "h2%d0",s+1);
   Occu[i][s] = (TH2F*) f.Get(his);
   Occu[i][s]->SetMaximum(2000);
   Occu[i][s]->SetDirectory(0);
  }
  f.Close();
 }
 IN.close();

 cout << endl << " Initializing efficiency histos..." << endl << endl;
 ifstream IN("list_eff");
 char file[300];
 char his[100];
 for(int i=0; i<NFILES && IN; i++)
 {
  IN >> file ;
  TFile f(file);
  for(int s=0; s<6; s++)
  {
   sprintf(his, "WireEfficiency_Sector%d",s+1);
   Effi[i][s] = (TH2F*) f.Get(his);
   Effi[i][s]->SetMaximum(1.5);
   Effi[i][s]->SetDirectory(0);
  }
  f.Close();
 }
 IN.close();




}

















