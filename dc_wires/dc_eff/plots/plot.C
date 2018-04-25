{
 gStyle->SetPalette(1);
 int Sec = 6;
 TH2F *HHl[Sec];
 TH2F *HHu[Sec];

 gStyle->SetPadRightMargin(0.1);
 gStyle->SetPadLeftMargin(0.1);
 gStyle->SetPadBottomMargin(0.1);

// TCanvas *EFF1 = new TCanvas("EFF1","EFF1", 0, 0, 800, 1000);
// EFF1->Range(0,0,21.5,28);
// EFF1->Divide(1,2);
 TCanvas *EFF2 = new TCanvas("EFF2","EFF2", 0, 0, 700, 500);
// TCanvas *EFF2 = new TCanvas("EFF2","EFF2", 0, 0, 800, 1000);
 EFF2->Range(0, 0, 21.5, 28);
// EFF2->Divide(1,2);


 TFile f("eff.root");

 for(int s=0; s<Sec; s++)
 {
  HHl[s] = (TH2F*)f->Get(Form("WireMap_Sector%d",s+1));
  HHu[s] = (TH2F*)f->Get(Form("WireMap_Sector%d",s+1));
  HHu[s]->SetDirectory(0);
  HHl[s]->SetDirectory(0);

//  HHl[s]->GetXaxis()->SetRange(0, 96);
//  HHl[s]->GetXaxis()->SetTitle(Form("Wire number: Lower half       Sector %d     ", s+1));
//  HHl[s]->GetYaxis()->SetTitle("Layer number         ");

//  HHu[s]->GetXaxis()->SetRange(97, 192);
//  HHu[s]->GetXaxis()->SetTitle(Form("Wire number: Upper half       Sector %d     ", s+1));
//  HHu[s]->GetYaxis()->SetTitle("Layer number         ");

  HHl[s]->GetZaxis()->SetNdivisions(505);
  HHu[s]->GetZaxis()->SetNdivisions(505);

  HHl[s]->GetXaxis()->SetTitleOffset(1.7);
  HHl[s]->GetYaxis()->SetTitleOffset(1.6);

  HHu[s]->SetDirectory(0);
  HHl[s]->SetDirectory(0);
 }

 f.Close();

 for(int s=0; s<Sec ; s++)
 {

//   EFF1->cd(1);
//   HHl[s]->Draw("box");
//
//   EFF1->cd(2);
//   HHu[s]->Draw("box");
//   EFF1->Print(Form("WireMap_box_Sector%d.eps",  s));
//   EFF1->Print(Form("WireMap_box_Sector%d.gif",  s+1));
//

//  EFF2->cd(1);
//  gPad->SetTheta(70);
//  gPad->SetPhi(305);
//  HHl[s]->Draw("box");


//  EFF2->cd(2);
//  gPad->SetTheta(70);
//  gPad->SetPhi(305);
//  HHu[s]->Draw("lego2");  

  HHl[s]->Draw("colz");


  EFF2->Print(Form("Occupancy_eg1dvcsb_s%d.gif", s+1));
 }

}





