{

 gStyle->SetFrameLineColor(0);  
 gStyle->SetPadRightMargin(0.14);
 gStyle->SetPadBottomMargin(0.3);
 
 const int iQ2 = 4;
 double q2_values[7]  = { 2.00, 2.40, 3.00, 3.50, 4.20, 5.00, 6.00};
 
 TH1F *LorT, *LorR, *LorF; 
 TH1F *invT, *invR, *invF;
 
 TH1F *dLorT, *dLorF;
 TH1F *dinvT, *dinvF; 
 
 TH2F *dLorTt, *dLorFt;
 TH2F *dinvTt, *dinvFt; 
 
   
 TFile *f = new TFile("muana.root"); 
 
 TLatex title;
 title.SetTextFont(12);
 title.SetNDC();

  
 gROOT->LoadMacro("costh.C");
 gROOT->LoadMacro("ctdiff.C");
 gROOT->LoadMacro("init_histos.C");
 init_histos();
 show_ctdiff();

 bar = new TControlBar("vertical", "  Maurizio Ungaro");
 bar->AddButton("Systematics","");
 bar->AddButton("","");

 bar->AddButton("Show cos(theta*) distribution", "show_costh()");
 bar->AddButton("Show D theta* distributions",   "show_ctdiff()");
  
 bar->AddButton("","");
 bar->Show();
 return 0;




}
