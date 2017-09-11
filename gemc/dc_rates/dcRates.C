

// global application settings
const bool recalc = 1; // 1 will refill all histos - 0 will open the outputf file as input

const int NCONF      = 2;
const string sconf[NCONF]  = {
	"cadTarget",
	"clas12NewTarget2"};

const double factor[NCONF] = {1, 1};  // additional factor to scale the different configurations


void dcRates()
{

	gStyle->SetPalette(1);
	gStyle->SetOptTitle(kWhite);
	gStyle->SetOptStat(kWhite);
	gStyle->SetOptFit(kWhite);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadColor(kWhite);

	gStyle->SetNumberContours(80);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPadBorderMode(0);






	TControlBar* bar =
	new TControlBar("vertical", "DC Rates - Maurizio Ungaro");
	bar->AddButton("DC Occupancy Rates",  "");
	bar->AddButton("", "");
	bar->AddButton("", "");
	bar->Show();


}
