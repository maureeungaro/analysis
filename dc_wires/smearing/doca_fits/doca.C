{
#include <iomanip>
 double LowLimit[3] = {  0.17,  0.17,  0.2 } ;  // limits for slicing the histos: outside these limits the 
 double HigLimit[3] = {  0.65,   1.1,  1.7 } ;  // sliced will be set to zero

 double Constras[3] = {  0.11,  0.12,  0.14 };  // At doca = 0 the fit function MUST intersect this point. Sigma
 double Constram[3] = {  -0.01,   0.016,  0.05 };  // At doca = 0 the fit function MUST intersect this point. Mean

 double MaxSigma[3] = {  0.12,  0.12,  0.15 };  // Histogram limits for nice visualization
 double MinSigma[3] = {   0.0,   0.0,  0.0  }; 
 double MaxMean[3]  = {  0.02,  0.03,  0.07 };
 double MinMean[3]  = { -0.02, -0.03, -0.03 }; 
 
 double CellSize[3] = {   0.7,   1.4,  2.0  };  // Cell Size. Outside this value the mean will be at limit. 
                                                // It's here just for reference and visualtization, in GPP it's harcoded.
 
 TMarker *ccm[3];
 TMarker *ccs[3];
 for(int r=0; r<3; r++)
 {
  ccm[r] = new TMarker(0, Constram[r], 20);
  ccm[r]->SetMarkerColor(2);
  ccs[r] = new TMarker(0, Constras[r], 20);
  ccs[r]->SetMarkerColor(2);
 }
 
 TText *t = new TText();
 t->SetTextFont(32);
 t->SetTextSize(0.08);
 t->SetTextAlign(12);
 t->SetNDC();

 double parameters[3][11][2];  // 11 parameters for each region, mean and sigma
 int Npars = 5;                // only Npars will be used in sigma fit
 int Nparm = 8;                // only Nparm will be used in mean fit

 gROOT->LoadMacro("histos_utils.C");
 gROOT->LoadMacro("plots.C");
 gROOT->LoadMacro("fit.C");

 TF1   *Frem[3];
 TF1   *Fres[3];
 TLine *Csize[3];
 for(int r=0; r<3; r++)
 {
  Frem[r] = new TF1(Form("Frem%d", r+1), func,          -1,           4, 11);
  Fres[r] = new TF1(Form("Fres%d", r+1), func,          -1,           4, 11);
  Frem[r]->SetLineColor(4);
  Frem[r]->SetLineWidth(1);
  Fres[r]->SetLineColor(4);
  Fres[r]->SetLineWidth(1);
  
  Csize[r] = new TLine(CellSize[r], -10, CellSize[r], 10);
  
 }
 

 


 TH2D* Reg[3];      // residual versus fitdoca
 TH1D* Res[3][2];   // sigma of Reg, before and after limits
 TH1D* Rem[3][2];   // mean  of Reg, before and after limits

 f = new TFile("muana.root");
 init_histos();

 bar = new TControlBar("vertical", " -  doca analysis  - ");
 bar->AddButton("","");
 bar->AddButton("Show spacial residual for different regions",   "plot_doca()");
 bar->AddButton("Show sigmas of residual for different regions", "plot_sigmas(0)");
 bar->AddButton("Show means  of residual for different regions", "plot_means(0)");
 bar->AddButton("Fit means and sigmas distributions",            "fit()");
 bar->AddButton("","");
 bar->AddButton("Save paramters in file pars.txt",               "save()");
 bar->AddButton("","");
 bar->Show();

}



