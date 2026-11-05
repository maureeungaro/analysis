{
 
 TH2F *phmm[8][4];
 TH2F *mm_dth[8][4]; 
 TH2F *mm_dthb[8][4];  
 TH1F *dth[8][4];
 TH1F *dthb[8][4]; 
 
 TH1F *mmm[4];
 TH1F *www[4];  
  
 TGraph *Cutu[8];
 TGraph *Cutl[8];
 TGraph *Cut3[8];

      
 gROOT->LoadMacro("init.C");
 gROOT->LoadMacro("show.C");
 init();
 show_mm_w();
 
 bar = new TControlBar("vertical", "  Maurizio Ungaro");
 bar->AddButton("Elastic radiative tail removal", "");
 bar->AddButton("Show phi versus mm",             "show_ph_mm()");
 bar->AddButton("Show mm versus dth",             "show_mm_dth()");
 bar->AddButton("Show mm versus dthb",            "show_mm_dthb()"); 
 bar->AddButton("Show mm, W",                     "show_mm_w()");
 bar->AddButton("",""); 
 bar->Show();


}
