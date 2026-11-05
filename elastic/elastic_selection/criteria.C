{
#include <string>

// ./muana -k0x2 -t0x2 
// This takes events and writes par.txt with various cuts
// to identify elastic events.
// File is then read by sel_mu program

 gStyle->SetPadLeftMargin(0.12);     
 gStyle->SetPadRightMargin(0.04);     
 gStyle->SetPadTopMargin(0.14);     
 gStyle->SetPadBottomMargin(0.22);     
 
 int PRINTOPT = 0;
 int BANK = 0 ;           // 0 = PART    --   1 = EVNT
 
 // Here global variables for cut
 double Wmin[6]   , Wmax[6];
 double mmmin[6]  , mmmax[6];
 double dphmin[6] , dphmax[6];
 double dthmin[6] , dthmax[6];
 double dthbmin[6], dthbmax[6];

 double Wsigma    = 3.0 ;  // cut around elastic peak : mean +- Wsigma * sigma
 double mmsigma   = 3.0 ;        
 double dphsigma  = 2.0 ;        
 double dthsigma  = 2.0 ;        
 double dthbsigma = 2.0 ;        

 // Global variables for mean, sigma and their errors
 double meanw[7],  sigmw[7];  
 double meanm[7],  sigmm[7]; 
 double meanp[7],  sigmp[7]; 
 double meant[7],  sigmt[7]; 
 double meanb[7],  sigmb[7];  
 double meanwe[7], sigmwe[7];  
 double meanme[7], sigmme[7]; 
 double meanpe[7], sigmpe[7]; 
 double meante[7], sigmte[7]; 
 double meanbe[7], sigmbe[7];  

 f=new TFile("muana.root");
 TH1F *Histos[2][7][5];     // bank / sector / W, mm, dth, dthb, dph

 gROOT->LoadMacro("functions/util.C");
 gROOT->LoadMacro("functions/init_histos.C");
 gROOT->LoadMacro("functions/W.C");
 gROOT->LoadMacro("functions/mm.C");
 gROOT->LoadMacro("functions/dph.C");
 gROOT->LoadMacro("functions/dth.C");
 gROOT->LoadMacro("functions/dthb.C");
 gROOT->LoadMacro("functions/summary.C"); 
 gROOT->LoadMacro("functions/printc.C");

 init_histos(Histos); 


 bar = new TControlBar("vertical", "Fiducial cut analysis   by Maurizio Ungaro");
 bar->AddButton("Elastic Selection Cut Analysis","");
 bar->AddButton("","");
 bar->AddButton("Enable/Disable printing","switchPRINT(&PRINTOPT)");
 bar->AddButton("","");
 bar->AddButton("Show W cut"             , "showW(BANK)");
 bar->AddButton("Show mm cut"            , "showmm(BANK)");
 bar->AddButton("Show phi(e)-phi(p) cut" , "showdph(BANK)");
 bar->AddButton("Show dth cut"           , "showdth(BANK)");
 bar->AddButton("Show dthb cut"          , "showdthb(BANK)");
 bar->AddButton("Show summary"          ,  "summary(BANK)"); 
 bar->AddButton("","");
 bar->AddButton("Print cuts","printc(BANK)");
 bar->AddButton("","");
 bar->Show();

}
