// SLICES DEFINITIONS:        ------------------------------------------------------------
int BIG_TITLE = 0x1;    // Top of the page title
int X_TITLE   = 0x2;    // X label
int Y_TITLE   = 0x4;    // Y label
int L_TITLE   = 0x8;    // Single pad label
int TITLE2    = 0x10;   // Sub Top of the page title
int SUPER2    = 0x20;   // Superimpose second set of histos
int SUPER3    = 0x40;   // Superimpose third set of histos
int SUPER4    = 0x80;   // Superimpose fourth set of histos
int PRINTING  = 0x800;   // Printing enabled
int ZEROLINE  = 0x100;  // zero line printing
int GRIDS     = 0x200;  // grids


// basic functions

//  exponential
double exponential(double *x, double *par)  { return par[0]*exp(par[1]*x[0]); }
double line(double *x, double *par)         { return par[0] + par[1]*x[0] ; }
double parabole(double *x, double *par)     { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] ; }
double thirdOrder(double *x, double *par)   { return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] ; }
double gaussian(double *x, double *par)     { return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2)); }



// gaussian + exponential
double gauss_expo(double *x, double *par)  { return exponential(x, par) + gaussian(x, &par[2]); }

// gaussian + first
double gauss_line(double *x, double *par)  { return line(x, par) + gaussian(x, &par[2]); }

// gaussian + parabole
double gauss_para(double *x, double *par)  { return parabole(x, par) + gaussian(x, &par[3]); }

// 2 gaussians + parabole
double gauss2_para(double *x, double *par) { return parabole(x, par) + gaussian(x, &par[3]) + gaussian(x, &par[6]); }

// gaussian + third
double gauss_third(double *x, double *par) { return thirdOrder(x, par) + gaussian(x, &par[4]); }


//// gaussian + exponential fit
//void FitGpE(TH1F *histo, double min, double max)
//{
//	TF1 MyFit("MyFit", Gauss_Expo, min, max, 5);
//	MyFit->SetLineWidth(1);
//	MyFit->SetParameter(4, 0.01);
//	
//	TF1 *MySign = new TF1("MySign", Gauss, min, max, 3);
//	TF1 *MyBack = new TF1("MyBack", Expo,  min, max, 2);
//	
//	histo->Fit("MyFit","REM");
// 
//	MyBack->SetParameter(0, MyFit->GetParameter(0));
//	MyBack->SetParameter(1, MyFit->GetParameter(1));
//	MyBack->SetLineWidth(1);
//	MyBack->SetLineColor(2);
//	MyBack->Draw("same");
// 
//	MySign->SetParameter(0, MyFit->GetParameter(2));
//	MySign->SetParameter(1, MyFit->GetParameter(3));
//	MySign->SetParameter(2, MyFit->GetParameter(4));
//	MySign->SetLineWidth(1);
//	MySign->SetLineColor(4);
//	MySign->Draw("same");
//}
//
//TF1* FitGpT(TH1F *histo, double min, double max)
//{
// TF1 *MyFit = new TF1("MyFit", Gauss_Thir, min, max, 7);
// MyFit->SetLineWidth(1);
// MyFit->SetParameter(6, 0.01);
//	
// TF1 *MySign = new TF1("MySign", Gauss, min, max, 3);
// TF1 *MyBack = new TF1("MyBack", Thir,  min, max, 4);
//	
//	
// 
// histo->Fit("MyFit","REM");
// 
// MyBack->SetParameter(0, MyFit->GetParameter(0));
// MyBack->SetParameter(1, MyFit->GetParameter(1));
// MyBack->SetParameter(2, MyFit->GetParameter(2));
// MyBack->SetParameter(3, MyFit->GetParameter(3));
// MyBack->SetLineWidth(1);
// MyBack->SetLineColor(2);
// MyBack->Draw("same");
// 
//	
// MySign->SetParameter(0, MyFit->GetParameter(4));
// MySign->SetParameter(1, MyFit->GetParameter(5));
// MySign->SetParameter(2, MyFit->GetParameter(6));
// MySign->SetLineWidth(1);
// MySign->SetLineColor(4);
// MySign->Draw("same");
//	
// return MySign;
//}
//
//
//void FitGpS(TH1F *histo, double min, double max)
//{
// TF1 MyFit("MyFit", Gauss_Para, min, max, 6);
// MyFit->SetLineWidth(1);
// MyFit->SetParameter(5, 0.01);
//	
// TF1 *MySign = new TF1("MySign", Gauss, min, max, 3);
// TF1 *MyBack = new TF1("MyBack", Para,  min, max, 3);
//	
//	
// 
// histo->Fit("MyFit","REM");
// 
// MyBack->SetParameter(0, MyFit->GetParameter(0));
// MyBack->SetParameter(1, MyFit->GetParameter(1));
// MyBack->SetParameter(2, MyFit->GetParameter(2));
// MyBack->SetLineWidth(1);
// MyBack->SetLineColor(2);
// MyBack->Draw("same");
// 
//	
// MySign->SetParameter(0, MyFit->GetParameter(3));
// MySign->SetParameter(1, MyFit->GetParameter(4));
// MySign->SetParameter(2, MyFit->GetParameter(5));
// MySign->SetLineWidth(1);
// MySign->SetLineColor(4);
// MySign->Draw("same");
// 
//}
//
//



