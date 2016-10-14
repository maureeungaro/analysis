{
 	string pars_file = "pi0_selection_pars.txt";
	string root_file = "nobh.root";
	int GSIM         = 0;

	// dont need a different pars file for GSIM... (unless we generate elastic events)
// 	string pars_file = "pi0_selection_pars_GSIM.txt";
// 	string root_file = "pi0_gsim.root";
// 	string root_file = "elastic_gsim.root";
// 	int GSIM         = 1;

	string datatype[2] = {"data", "MC"};
	gROOT->LoadMacro("src/common_info.cc");

	
	int STAGE = 0;
	const int NSTAGES = 5;
	const int NWBINS  = 18;
	double dw = (2.0 - 1.1)/NWBINS;
	string cut[NSTAGES]   = {"no_cut", "phi_cut", "th1_cut", "th2_cut", "all_cuts"};
	string scut[NSTAGES]  = {"no cut", "#Delta#phi cut", "#Delta#theta_{1} cut", "#Delta#theta_{2} cut", "all cuts"};
	
	
	chistos H(root_file, 1);
	cpars   Pars(pars_file);

	int nbefore = H.W[0]->GetEntries();
	int nafter  = H.W[4]->GetEntries();
	
	
	gROOT->LoadMacro("ana/utils.C");
	gROOT->LoadMacro("ana/show_dist.C");
	gROOT->LoadMacro("ana/fit_phis.C");

	TGraphErrors *dphi_means_g;
	TGraphErrors *dphi_sigmas_g;
	TGraphErrors *dth1_means_g;
	TGraphErrors *dth1_sigmas_g;
	TGraphErrors *dth2_means_g;
	TGraphErrors *dth2_sigmas_g;
	
	string PRINT   = "";
		
	
	bar = new TControlBar("vertical", "  Maurizio Ungaro");
	bar->AddButton("pi0 Selection", "");
	bar->AddButton("","");
	bar->AddButton("Show mm",                    "show_dists(H.epXmm2)");
	bar->AddButton("Show W",                     "show_dists(H.W)");
	bar->AddButton("Show Q2",                    "show_dists(H.Q2)");
	bar->AddButton("","");
	bar->AddButton("Show mm vs W",               "show_dists(H.epXmm2_W)");
	bar->AddButton("Show Q2 vs W",               "show_dists(H.Q2_W)");
	bar->AddButton("","");
	bar->AddButton("Show dphi vs mm",            "show_dist(H.dphi_epXmm2)");
	bar->AddButton("Show dth1 vs mm",            "show_dist(H.dth1_epXmm2)");
	bar->AddButton("Show dth2 vs mm",            "show_dist(H.dth2_epXmm2)");
	bar->AddButton("Show dphi vs mm zoomed",     "show_dist(H.dphi_epXmm2z)");
	bar->AddButton("Show dth1 vs mm zoomed",     "show_dist(H.dth1_epXmm2z)");
	bar->AddButton("Show dth2 vs mm zoomed",     "show_dist(H.dth2_epXmm2z)");
	bar->AddButton("","");
	bar->AddButton("Show mm",                    "show_dist(H.epXmm2s)");
	bar->AddButton("Show dphi",                  "show_dist(H.dphi)");
	bar->AddButton("Show dth1",                  "show_dist(H.dth1)");
	bar->AddButton("Show dth2",                  "show_dist(H.dth2)");
	bar->AddButton("Show dphi zoomed",           "show_dist(H.dphiz)");
	bar->AddButton("Show dth1 zoomed",           "show_dist(H.dth1z)");
	bar->AddButton("Show dth2 zoomed",           "show_dist(H.dth2z)");
	bar->AddButton("","");
	bar->AddButton("Fit phis",                   "fit_phis(H.dphiz, 176, 184)");
	bar->AddButton("Fit dth1",                   "fit_phis(H.dth1z, -0.5, 0.5)");
	bar->AddButton("Fit dth2",                   "fit_phis(H.dth2z, -1, 1)");
	bar->AddButton("Show dphi fits",             "show_phi_fits(dphi_means_g, dphi_sigmas_g, \"phi\")");
	bar->AddButton("Show dth1 fits",             "show_phi_fits(dth1_means_g, dth1_sigmas_g, \"dth1\")");
	bar->AddButton("Show dth2 fits",             "show_phi_fits(dth2_means_g, dth2_sigmas_g, \"dth2\")");
	bar->AddButton("","");
	bar->AddButton("","");
	bar->AddButton("Change Stage",               "change_stage()");
	bar->AddButton("Write Parameters",           "Pars.write_vars(pars_file)");
	bar->AddButton("","");
	bar->Show();
}











