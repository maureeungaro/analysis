
// how to create the bstxy histo
// 100K events - see build histo routine
// 
// TH2F *bstyx = new TH2F("bstyx", "bstyx", 2000, -200, 200, 2000, -200, 200);
// bstT->Draw("x:y>>bstyx", "Edep>0", "")

{

	gStyle->SetPadLeftMargin(0.08);
	gStyle->SetPadRightMargin(0.04);
	gStyle->SetPadTopMargin(0.16);
	gStyle->SetPadBottomMargin(0.12);
	
	TLatex lab;
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	gStyle->SetCanvasColor(0);

	TCanvas *eventC  = new TCanvas("eventC", "eventC", 900, 900);

	TH2F *bstyx;
	TGraph *gen_XY;
	TGraph *bgen_XY;
	
	double EMIN = 0.02;
	
	// generated particles
	int evn;
	int ngen;
	int id[20];
	float px[20];   // momentum and energy of generated particle
	float py[20];
	float pz[20];
	float gE[20];

	
	// BST Hits from signal
	int    nbsthit;
	float x[100];
	float y[100];
	float Edep[1000];
	int pid[1000];
	int strip[1000];
	int layer[1000];
	int sector[1000];
	
	// BST Hits from background
	int    bnbsthit;
	float bax[10000];
	float bay[10000];
	float bEdep[10000];
	
	
	
	// getting the yx distribution
	TFile f("../rootfiles/bstyx.root");
	bstyx = (TH2F*) f.Get("bstyx");
	bstyx->SetDirectory(0);
	f.Close();
	
	string part   = "protons_b";
	string target = "lh2";
	
//	TFile *ifile = new TFile(Form("bstn.root", part));
	TFile *ifile = new TFile(Form("/arena/BST/root/%s.root", part));
	TTree *genT  = (TTree*)ifile->Get("generated");
	TTree *bstT  = (TTree*)ifile->Get("bst");
//	genT->SetBranchAddress("evn",  &evn);
//	genT->SetBranchAddress("ngen", &ngen);
//	genT->SetBranchAddress("id",   id);
//	genT->SetBranchAddress("px",   px);
//	genT->SetBranchAddress("py",   py);
//	genT->SetBranchAddress("pz",   pz);
	
	
	bstT->SetBranchAddress("hitn",   &nbsthit);
	bstT->SetBranchAddress("avg_x",         x);
	bstT->SetBranchAddress("avg_y",         y);
	bstT->SetBranchAddress("totEdep",      Edep);
	bstT->SetBranchAddress("pid",       pid);
	bstT->SetBranchAddress("strip",     strip);
	bstT->SetBranchAddress("layer",     layer);
	bstT->SetBranchAddress("sector",    sector);
	
	
	TFile *bfile = new TFile(Form("/arena/BST/root/%s.root", target));
	TTree *bbstT = (TTree*)bfile->Get("bstT");

	bbstT->SetBranchAddress("nbsthit",   &bnbsthit);
	bbstT->SetBranchAddress("x",         bax);
	bbstT->SetBranchAddress("y",         bay);
	bbstT->SetBranchAddress("Edep",      bEdep);


	int evni = 0;

	gROOT->LoadMacro("event_utils.C");

}



