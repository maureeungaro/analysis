{
 #include <string>
 gStyle->SetPadBottomMargin(0.26);
 gStyle->SetPadTopMargin(0.04);
 gStyle->SetOptStat(0); 
 
 
 int NWM = 3;
 int NQ2 = 5;
 int NCT = 4;
 int NPH = 4;
 
 TH1F *mm[3][5][4][4];   
 TH1F *mmG[3][5][4][4];   
 
 TH1F *ww[5][4][4];   
 TH1F *wwG[5][4][4];   
 
 double SCALEWM[5][4][4];
 double SCALEMM[3][5][4][4]; 
  
 string Ws[3]  = {"1.15",   "1.25", "1.35"};
 string Qs[5]  = {"2.35",  "3.05",  "3.75", "4.45", "5.25"};  
 string Cts[4] = {"-0.75", "-0.25", "0.25", "0.75"};
 string Phs[4] = {"45",    "135",   "225",  "315"};
 
 int iWM   = 0;
 int iQ2   = 0;
 int PRINT = 0;
 
 gROOT->LoadMacro("utils.C");
 gROOT->LoadMacro("show.C"); 
 gROOT->LoadMacro("init.C");  
 init_histos();
 
 
 bar = new TControlBar("vertical", "  Maurizio Ungaro");
 bar->AddButton("DATA/GSIM comparison","");
 bar->AddButton("","");
 
 bar->AddButton("Show mm distributions",  "show_mm()"); 
 bar->AddButton("Show W distributions",   "show_ww()");  
 bar->AddButton("","");
  
 bar->AddButton("Switch W bin",            "switch_WM()"); 
 bar->AddButton("Switch Q2 bin",           "switch_Q2()");  
 bar->AddButton("Print all distributions", "print_all()"); 
 bar->AddButton("","");
 bar->Show();
 return 0;




}
