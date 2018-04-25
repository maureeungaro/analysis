init_histos()
{
 int LowBin, HigBin, MaxBin;

 cout << endl << endl << " Initializing histograms..." ;

 for(int r=0; r<3; r++)
 {
  Reg[r]=(TH2D*)f.Get(Form("reg%d", r+1));
  Reg[r]->SetXTitle("FitDoca  (cm)");
  Reg[r]->SetYTitle("|CalcDoca| - |FitDoca|   (cm)");

  Reg[r]->GetXaxis()->SetTitleOffset(1.2);
  Reg[r]->GetYaxis()->SetTitleOffset(1.2);

  Reg[r]->GetXaxis()->SetTitleFont(44);
  Reg[r]->GetYaxis()->SetTitleFont(44);
  Reg[r]->GetXaxis()->SetTitleSize(18);
  Reg[r]->GetYaxis()->SetTitleSize(18);

  Reg[r]->GetXaxis()->SetLabelOffset(0.008);
  Reg[r]->GetYaxis()->SetLabelOffset(0.008);

  Reg[r]->SetLabelSize(.04);
  Reg[r]->SetLabelSize(.04,"Y");

  Reg[r]->FitSlicesY(0, 0, 0, 16,"MNQ");

  Res[r][0] = (TH1D *) gDirectory->Get(Form("reg%d_2", r+1));
  Rem[r][0] = (TH1D *) gDirectory->Get(Form("reg%d_1", r+1));
  
  // Filling second histos only with values as defined in doca.C
  Res[r][1] = (TH1D*) Res[r][0]->Clone();
  Rem[r][1] = (TH1D*) Rem[r][0]->Clone();
  
  
  
  LowBin = Res[r][0]->FindBin(LowLimit[r]);
  HigBin = Res[r][0]->FindBin(HigLimit[r]);
  MaxBin = Res[r][0]->GetNbinsX();

  for(int b=1; b<LowBin+1; b++)
  {
   Res[r][1]->SetBinContent(b, 0);
   Rem[r][1]->SetBinContent(b, 0);
   Res[r][1]->SetBinError(b, 0);
   Rem[r][1]->SetBinError(b, 0);
  }
  for(int b=LowBin+1; b<HigBin+1; b++)
  {
   Res[r][1]->SetBinContent(b, Res[r][0]->GetBinContent(b));
   Rem[r][1]->SetBinContent(b, Rem[r][0]->GetBinContent(b));
  }
  for(int b=HigBin+1; b<MaxBin+1; b++)
  {
   Res[r][1]->SetBinContent(b, 0.0);
   Rem[r][1]->SetBinContent(b, 0.0);
   Res[r][1]->SetBinError(b,   0.0);
   Rem[r][1]->SetBinError(b,   0.0001*(r+1));
  }

  Res[r][1]->SetLineColor(2);
  Res[r][0]->SetLineColor(29);
  Rem[r][1]->SetLineColor(2);
  Rem[r][0]->SetLineColor(29);
  
  Res[r][1]->SetMaximum(MaxSigma[r]);
  Res[r][1]->SetMinimum(MinSigma[r]);
  Rem[r][1]->SetMaximum(MaxMean[r]);
  Rem[r][1]->SetMinimum(MinMean[r]);
  
 }
 cout << "done." << endl << endl;
}


