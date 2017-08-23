void init_dc_histos(string filename, int cindex)
{
	if(recalc == 1)
	{
		TFile f(filename.c_str());
		TCanvas *c1 = new TCanvas("c1", "c1", 100,100);
		
		NHITS           = generated->GetEntries();
		double TWINDOW  = 250.0e-9;
		double TOT_TIME = NHITS*TWINDOW;

		
		double TWINDOWR[3] = {250.0e-9, 250.0e-9, 500.0e-9};
		
		twindscale = new TH2F("twindscale", "twindscale", 112, 0.5, 112.5, 36, 0.5, 36.5);
		for(int l=0; l<36; l++)
			for(int w=0; w<112; w++)
			{
				if(l <12)         twindscale->SetBinContent(w+1, l+1, TWINDOW/TWINDOWR[0]);
				if(l>=12 && l<24) twindscale->SetBinContent(w+1, l+1, TWINDOW/TWINDOWR[1]);
				if(l>=24)         twindscale->SetBinContent(w+1, l+1, TWINDOW/TWINDOWR[2]);
				// twindscale->SetBinContent(w+1, l+1, 1);
			}
		twindscale->SetDirectory(0);
		
		cout << " Initializing DC histos for configuration " << sconf[cindex] << " with " << NHITS << " entries in " << TOT_TIME << " total time...";
		for(int e=0; e<NENERGY; e++)
		{
			for(int s=0; s<NSECT; s++)
			{
				// 2D occupancy histos: 2D for each sector, wire vs layer
				dc_pro[s][e][cindex] = new TH2F(Form("dc_pro_s%d_E%s_%s", s+1, SEDEP[e].c_str(), sconf[cindex].c_str()),
														  Form("dc_pro_s%d_E%s_%s", s+1, SEDEP[e].c_str(), sconf[cindex].c_str()),
														  112, 0.5, 112.5, 36, 0.5, 36.5);
				
				dc_occ[s][e][cindex] = (TH2F*) dc_pro[s][e][cindex]->Clone();
				
				
			}
			
			for(int r=0; r<NREG; r++)
			{
				// 2D vertex histos
				for(int z=0; z<NZONES; z++)
				{
					dc_ver[e][cindex][z][r] = new TH2F(Form("dc_ver_E%s_%s_z%s_r%d", SEDEP[e].c_str(), sconf[cindex].c_str(), SZONE[z].c_str(), r+1),
													           Form("dc_ver_E%s_%s_z%s_r%d", SEDEP[e].c_str(), sconf[cindex].c_str(), SZONE[z].c_str(), r+1),
													           200, zlimits[2][0][z], zlimits[2][1][z], 200, zlimits[0][0][z], zlimits[0][1][z]);
				}
				// 1D vertex histos
				double hzend = 8000;
				if(r==0) hzend = 3500;
				for(int p=0; p<NPART; p++)
					dc_zver[e][cindex][r][p] = new TH1F(Form("dc_zver_E%s_%s_r%d_%s", SEDEP[e].c_str(), sconf[cindex].c_str(), r+1, SPART[p].c_str()),
					     							   			Form("dc_zver_E%s_%s_r%d_%s", SEDEP[e].c_str(), sconf[cindex].c_str(), r+1, SPART[p].c_str()),
															   	 200, -200, hzend);
			}
			
			// 1D summary occupancy histo for the 3 regions
			for(int r=0; r<NREG; r++)
				dc_occ_summary[r][e][cindex] = new TH1F(Form("dc_occ_summary_r%d_E%s_%s", r+1, SEDEP[e].c_str(), sconf[cindex].c_str()),
                                                    Form("dc_occ_summary_r%d_E%s_%s", r+1, SEDEP[e].c_str(), sconf[cindex].c_str()),
														          6, 0.5, 6.5);
			
			
			// process ID histos
			dc_procID[cindex] = new TH1F(Form("dc_procID_%s", sconf[cindex].c_str()),
                                      Form("dc_procID_%s", sconf[cindex].c_str()), 20, 0.5, 20.5);
			
			// process ID vs Layer
			dc_procIDvsLayer[cindex] = new TH2F(Form("dc_procIDvsLayer_%s", sconf[cindex].c_str()),
                                             Form("dc_procIDvsLayer_%s", sconf[cindex].c_str()), 6, 0.5, 6.5, 20, 0.5, 20.5);
			
			// process ID vs Z
			for(int r=0; r<NREG; r++)
				dc_procIDvsZ[r][cindex] = new TH2F(Form("dc_procIDvsZ_r%d_%s", r+1, sconf[cindex].c_str()),
                                               Form("dc_procIDvsZ_r%d_%s", r+1, sconf[cindex].c_str()), 100, -200, 10000, 20, 0.5, 20.5);

			// process ID vs pid
			dc_procIDvspid[cindex] = new TH2F(Form("dc_procIDvspid_%s", sconf[cindex].c_str()),
                                           Form("dc_procIDvspid_%s", sconf[cindex].c_str()), 100, -250, 250, 20, 0.5, 20.5);
			
			// process ID vs Edep
			dc_procIDvsEdep[cindex] = new TH2F(Form("dc_procIDvsEdep_%s", sconf[cindex].c_str()),
                                            Form("dc_procIDvsEdep_%s", sconf[cindex].c_str()), 100, 0, 0.01, 20, 0.5, 20.5);
			
			// process ID vs track energy
			// different track energy ranges
			dc_procIDvsTrackE[0][cindex] = new TH2F(Form("dc_procIDvsTrackE1_%s", sconf[cindex].c_str()),
                                                 Form("dc_procIDvsTrackE1_%s", sconf[cindex].c_str()), 100, 0, 3000, 20, 0.5, 20.5);
			dc_procIDvsTrackE[1][cindex] = new TH2F(Form("dc_procIDvsTrackE2_%s", sconf[cindex].c_str()),
                                                 Form("dc_procIDvsTrackE2_%s", sconf[cindex].c_str()), 100, 0, 30,   20, 0.5, 20.5);
			dc_procIDvsTrackE[2][cindex] = new TH2F(Form("dc_procIDvsTrackE3_%s", sconf[cindex].c_str()),
                                                 Form("dc_procIDvsTrackE3_%s", sconf[cindex].c_str()), 100, 0, 1,    20, 0.5, 20.5);

			
		}
		cout << " done. " << endl;
		
		
		for(int e=0; e<NENERGY; e++)
		{
			cout << " Now making the histos for the energy: " << SEDEP[e] << endl;
			
			string hitCut    = "wire>0 && wire < 112 && " + EDEP[e];
			for(int s=0; s<NSECT; s++)
			{
				string sectcut= Form("sector == %d", s+1);
				
				string allCuts    = hitCut + "  && " + sectcut;
				
				// 2D occupancy histos: 2D for each sector, wire vs layer
				// layer is from 1 to 36
				string hist = Form("(layer:wire >> dc_pro_s%d_E%s_%s", s+1, SEDEP[e].c_str(), sconf[cindex].c_str());
				dc->Draw(hist.c_str(), allCuts.c_str());
				
				dc_pro[s][e][cindex]->Scale(100*factor[cindex]/NHITS);
				dc_occ[s][e][cindex]->Divide(dc_pro[s][e][cindex], twindscale, 1, 1);
				
				
				// can't set it at definition times
				dc_pro[s][e][cindex]->SetDirectory(0);
				dc_occ[s][e][cindex]->SetDirectory(0);
			}
			
			for(int r=0; r<NREG; r++)
			{
				string hitCutR;
				if(r==0) hitCutR = hitCut + "               && layer < 13)";
				if(r==1) hitCutR = hitCut + " && layer > 12 && layer < 25";
				if(r==2) hitCutR = hitCut + " && layer > 24 ";

				// 2D vertex histos
				for(int z=0; z<NZONES; z++)
				{
					string hist = Form("sqrt(vx*vx+vy*vy):vz >> dc_ver_E%s_%s_z%s_r%d", SEDEP[e].c_str(), sconf[cindex].c_str(), SZONE[z].c_str(), r+1);
					
					
					dc->Draw(hist.c_str(), hitCutR.c_str());
					dc_ver[e][cindex][z][r]->Scale(100*factor[cindex]/NHITS);
					dc_ver[e][cindex][z][r]->SetDirectory(0);
				}
				// 1D vertex histos
				for(int p=0; p<NPART; p++)
				{
					string hist = Form("vz >> dc_zver_E%s_%s_r%d_%s", SEDEP[e].c_str(), sconf[cindex].c_str(), r+1, SPART[p].c_str());
					
					string hitCutRP = hitCutR + " && " + pcut[p];
					
					cout << hitCutRP << endl;
					
					dc->Draw(hist.c_str(), hitCutRP.c_str());
					dc_zver[e][cindex][r][p]->Scale(factor[cindex]/NHITS);
					dc_zver[e][cindex][r][p]->SetDirectory(0);
				}
				
			}
			
			// 1D summary occupancy histo for the 3 regions
			double nwires = 112.0;
			double nlayers = 12.0;
			for(int r=0; r<3; r++)
			{
				string regionCut = Form("(layer > %d && layer < %d)", 12*r, 12*r+1);
				string allCuts    = hitCut + "  && " + regionCut;
				string histSum   = Form("sector - 0.5 >> dc_occ_summary_r%d_E%s_%s", r+1, SEDEP[e].c_str(), sconf[cindex].c_str());
				dc->Draw(histSum.c_str(), allCuts.c_str());
				dc_occ_summary[r][e][cindex]->Sumw2();
				dc_occ_summary[r][e][cindex]->Scale(100*factor[cindex]*(TWINDOWR[r]/TWINDOW)/(NHITS*nwires*nlayers));
				dc_occ_summary[r][e][cindex]->SetDirectory(0);
			}
		
		
			// procID. Attention: assuming NENERGY = 1 otherwise we'd have to be in external loop
			dc->Draw(Form("procID>>dc_procID_%s",                   sconf[cindex].c_str()), hitCut.c_str());
			dc->Draw(Form("procID:layer>>dc_procIDvsLayer_%s", sconf[cindex].c_str()), hitCut.c_str());
			
			for(int r=0; r<3; r++)
			{
				string regionCut = Form("(layer > %d && layer < %d)", 12*r, 12*r+1);
				string allCuts   = hitCut + "  && " + regionCut;
            string histSum   = Form("procID:vz>>dc_procIDvsZ_r%d_%s", r+1, sconf[cindex].c_str());

				dc->Draw(histSum.c_str(), allCuts.c_str());
			}

			dc->Draw(Form("procID:pid>>dc_procIDvspid_%s",      sconf[cindex].c_str()), hitCut.c_str());
			dc->Draw(Form("procID:totEdep>>dc_procIDvsEdep_%s", sconf[cindex].c_str()), hitCut.c_str());
			
			dc->Draw(Form("procID:trackE>>dc_procIDvsTrackE1_%s", sconf[cindex].c_str()), hitCut.c_str());
			dc->Draw(Form("procID:trackE>>dc_procIDvsTrackE2_%s", sconf[cindex].c_str()), hitCut.c_str());
			dc->Draw(Form("procID:trackE>>dc_procIDvsTrackE3_%s", sconf[cindex].c_str()), hitCut.c_str());
			
			
         dc_procID[cindex]->Scale(factor[cindex]/NHITS);
         dc_procID[cindex]->SetDirectory(0);
         dc_procIDvsLayer[cindex]->Scale(factor[cindex]/NHITS);
         dc_procIDvsLayer[cindex]->SetDirectory(0);
         
         for(int r=0; r<NREG; r++)
         {
            dc_procIDvsZ[r][cindex]->Scale(factor[cindex]/NHITS);
            dc_procIDvsZ[r][cindex]->SetDirectory(0);
         }
         // process ID vs pid
         dc_procIDvspid[cindex]->Scale(factor[cindex]/NHITS);
         dc_procIDvspid[cindex]->SetDirectory(0);
         
         // process ID vs Edep
         dc_procIDvsEdep[cindex]->Scale(factor[cindex]/NHITS);
         dc_procIDvsEdep[cindex]->SetDirectory(0);
         
         // process ID vs track energy
         // different track energy ranges
         dc_procIDvsTrackE[0][cindex]->Scale(factor[cindex]/NHITS);
         dc_procIDvsTrackE[1][cindex]->Scale(factor[cindex]/NHITS);
         dc_procIDvsTrackE[2][cindex]->Scale(factor[cindex]/NHITS);
         
         dc_procIDvsTrackE[0][cindex]->SetDirectory(0);
         dc_procIDvsTrackE[1][cindex]->SetDirectory(0);
         dc_procIDvsTrackE[2][cindex]->SetDirectory(0);
         

			
		}
		
		
		c1->Close();
		f.Close();
		
		
		// writing out to file1
		string ofname =   sconf[cindex] + ".root";
		cout << " Opening file for writing: " << ofname << endl;
		TFile of(ofname.c_str(), "RECREATE");
		for(int e=0; e<NENERGY; e++)
		{
			for(int s=0; s<NSECT; s++)
			{
				dc_occ[s][e][cindex]->Write();
			}
			
			for(int r=0; r<NREG; r++)
			{
				for(int z=0; z<NZONES; z++)
				{
					dc_ver[e][cindex][z][r]->Write();
				}

				for(int p=0; p<NPART; p++)
					dc_zver[e][cindex][r][p]->Write();
				
				dc_occ_summary[r][e][cindex]->Write();
			}
		}
      
      
		dc_procID[cindex]->Write();
      dc_procIDvsLayer[cindex]->Write();
      
      for(int r=0; r<NREG; r++)
      {
         dc_procIDvsZ[r][cindex]->Write();
      }
      // process ID vs pid
      dc_procIDvspid[cindex]->Write();
      
      // process ID vs Edep
      dc_procIDvsEdep[cindex]->Write();
      
      // process ID vs track energy
      // different track energy ranges
      dc_procIDvsTrackE[0][cindex]->Write();
      dc_procIDvsTrackE[1][cindex]->Write();
      dc_procIDvsTrackE[2][cindex]->Write();

      
		of.Close();
		cout << " done. "  << endl;
	}
	else
	{
		string fname =   sconf[cindex] + ".root";
		cout << " Opening file " << fname << endl;
		TFile f(fname.c_str());
		for(int e=0; e<NENERGY; e++)
		{
			for(int s=0; s<NSECT; s++)
			{
				// 2D occupancy histos: 2D for each sector, wire vs layer
				dc_occ[s][e][cindex] = (TH2F*) f.Get(Form("dc_pro_s%d_E%s_%s", s+1, SEDEP[e].c_str(), sconf[cindex].c_str()));
				dc_occ[s][e][cindex]->Scale(0.02);
				dc_occ[s][e][cindex]->SetDirectory(0);

			}
			
			// vertex histos
			for(int r=0; r<NREG; r++)
			{
				for(int z=0; z<NZONES; z++)
				{
					dc_ver[e][cindex][z][r] = (TH2F*) f.Get(Form("dc_ver_E%s_%s_z%s_r%d", SEDEP[e].c_str(), sconf[cindex].c_str(), SZONE[z].c_str(), r+1) );

					dc_ver[e][cindex][z][r]->SetDirectory(0);
				}
				
				for(int p=0; p<NPART; p++)
				{
					dc_zver[e][cindex][r][p] = (TH1F*) f.Get(Form("dc_zver_E%s_%s_r%d_%s", SEDEP[e].c_str(), sconf[cindex].c_str(), r+1, SPART[p].c_str()) );
					dc_zver[e][cindex][r][p]->SetDirectory(0);
				}
				
				
				dc_occ_summary[r][e][cindex] = (TH1F*) f.Get(Form("dc_occ_summary_r%d_E%s_%s", r+1, SEDEP[e].c_str(), sconf[cindex].c_str()));
				//dc_occ_summary[r][e][cindex]->Scale(0.02);
				dc_occ_summary[r][e][cindex]->SetDirectory(0);
				
			}
		}
      
      // process ID histos
      dc_procID[cindex] = (TH1F*) f.Get(Form("dc_procID_%s", sconf[cindex].c_str()));
	 	dc_procID[cindex]->SetDirectory(0);
      
      // process ID vs Layer
      dc_procIDvsLayer[cindex] = (TH2F*) f.Get(Form("dc_procIDvsLayer_%s", sconf[cindex].c_str()));
      dc_procIDvsLayer[cindex]->SetDirectory(0);

      // process ID vs Z
      for(int r=0; r<NREG; r++)
      {
         dc_procIDvsZ[r][cindex] = (TH2F*) f.Get(Form("dc_procIDvsZ_r%d_%s", r+1, sconf[cindex].c_str()));
         dc_procIDvsZ[r][cindex]->SetDirectory(0);
      }
      // process ID vs pid
      dc_procIDvspid[cindex] = (TH2F*) f.Get(Form("dc_procIDvspid_%s", sconf[cindex].c_str()));
      dc_procIDvspid[cindex]->SetDirectory(0);

      // process ID vs Edep
      dc_procIDvsEdep[cindex] = (TH2F*) f.Get(Form("dc_procIDvsEdep_%s", sconf[cindex].c_str()));
      dc_procIDvsEdep[cindex]->SetDirectory(0);

      // process ID vs track energy
      // different track energy ranges
      dc_procIDvsTrackE[0][cindex] = (TH2F*) f.Get(Form("dc_procIDvsTrackE1_%s", sconf[cindex].c_str()));
      dc_procIDvsTrackE[1][cindex] = (TH2F*) f.Get(Form("dc_procIDvsTrackE2_%s", sconf[cindex].c_str()));
      dc_procIDvsTrackE[2][cindex] = (TH2F*) f.Get(Form("dc_procIDvsTrackE3_%s", sconf[cindex].c_str()));

      dc_procIDvsTrackE[0][cindex]->SetDirectory(0);
      dc_procIDvsTrackE[1][cindex]->SetDirectory(0);
      dc_procIDvsTrackE[2][cindex]->SetDirectory(0);
      
		cout << " done. " << endl;
		f.Close();

	}
	
	
}









