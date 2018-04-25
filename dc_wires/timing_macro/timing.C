{
 const int NFILES = 400;

 int SECT_1  = 6 ;
 int LAYER_1 = 20 ;
 int WIRE_1  = 80 ;
 int SECT_2  = 6 ;
 int LAYER_2 = 21 ;
 int WIRE_2  = 82 ;

 double OCCU1[NFILES];
 double EFFI1[NFILES];

 double OCCU2[NFILES];
 double EFFI2[NFILES];

 double X[NFILES];
 for(int i=0; i<NFILES; i++) X[i] = i+1;

 TH2F *Occu[NFILES][6];
 TH2F *Effi[NFILES][6];

 TGraph *COMP1;
 TGraph *COMP2;
 TGraph *CORR;
 
 TGraph *EFF1;
 TGraph *EFF2;
 TGraph *CORRE;

 TLatex SECTOR, Layer, Wire;

 gROOT->LoadMacro("functions/go.C");
 gROOT->LoadMacro("functions/change_wire.C");
 gROOT->LoadMacro("functions/init_sliders.C");
 init_histos();

 TCanvas *wireS = new TCanvas("wireS","Wire selection", 700, 500);

 TSlider *sector_s1;
 TSlider *sector_s2;
 TPad *sector_w1;
 TPad *sector_w2;

 TSlider *layer_s1;
 TSlider *layer_s2;
 TPad *layer_w1;
 TPad *layer_w2;

 TSlider *wire_s1;
 TSlider *wire_s2;
 TPad *wire_w1;
 TPad *wire_w2;
 init_sliders();


 bar = new TControlBar("vertical", "Drift chamber timing   by Maurizio Ungaro");
 bar->AddButton("","");
 bar->AddButton("Show occupancy and efficiency",                        "Show_occupancy(0)");
 bar->AddButton("Show occupancy and efficiency around selected wires",  "Show_occupancy(1)");
 bar->AddButton("","");
 bar->AddButton("Show selected wires occupancy",         "Show_timing_occ()");
 bar->AddButton("Show selected wires efficiency",        "Show_timing_eff()");
 bar->AddButton("","");
 bar->Show();

 wireS->SetEditable(0);

}
