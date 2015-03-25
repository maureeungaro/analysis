// MU includes
#include "histos.h"
#include "utilities.h"

// %%%%%%%%%%%%
// C++ includes
// %%%%%%%%%%%%
#include <string>
#include <iostream>
using namespace std;

void histos::fill(map<string, int> passed, particle p)
{
	set_vars(passed);
	int sector_i = p.sector() - 1;
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// NPHE
	// no cuts
	double npe = p.get("npe");
	if(p.ccinfos.size() && p.cainfos.size())
	{
		nphe[0][sector_i]->Fill(npe);
		nphe[0][6]->Fill(npe);
		// all other on
		if(alloth["NPHE"] == 1)
		{
			nphe[1][sector_i]->Fill(npe); 
			nphe[1][6]->Fill(npe);
		}	
		// all other off
		if(othneg["NPHE"] == 1)
		{
			nphe[2][sector_i]->Fill(npe); 
			nphe[2][6]->Fill(npe);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			nphe[3][sector_i]->Fill(npe); 
			nphe[3][6]->Fill(npe);
		}
	}
	// End NPHE
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// CCMATCH
	// X Pos vs Segment
	double xpos       = p.vget("CCxyz").theta()/degree;
	double segm       = p.get("ccsegm");
	double ccphimatch = p.get("ccphimatch");
	double time_corr  = fabs( (p.vget("CCxyz") - p.vget("SCxyz") ).mod()/cm) / speed_of_light;
	double ccdtime    = p.get("cctime") + time_corr - p.get("sctime");
	int    pmt_number = ( p.get("ccpmt") > 0 ? (int) segm*2 :(int) segm*2-1 );
	// no cuts
	if(p.ccinfos.size() && p.scinfos.size())
	{
		theta_vs_segm[0][sector_i]->Fill(segm, xpos);
		theta_vs_segm[0][6]->Fill(segm, xpos);
		phi_match[0][sector_i]->Fill(ccphimatch);
		phi_match[0][6]->Fill(ccphimatch);
		cc_timing[0][sector_i]->Fill(pmt_number, ccdtime);
		cc_timing[0][6]->Fill(pmt_number, ccdtime);
		
		// all other on
		if(alloth["CCMATCH"] == 1)
		{
			theta_vs_segm[1][sector_i]->Fill(segm, xpos);
			theta_vs_segm[1][6]->Fill(segm, xpos);
			phi_match[1][sector_i]->Fill(ccphimatch);
			phi_match[1][6]->Fill(ccphimatch);
			cc_timing[1][sector_i]->Fill(pmt_number, ccdtime);
			cc_timing[1][6]->Fill(pmt_number, ccdtime);
		}
		// all other off
		if(othneg["CCMATCH"] == 1)
		{
			theta_vs_segm[2][sector_i]->Fill(segm, xpos);
			theta_vs_segm[2][6]->Fill(segm, xpos);
			phi_match[2][sector_i]->Fill(ccphimatch);
			phi_match[2][6]->Fill(ccphimatch);
			cc_timing[2][sector_i]->Fill(pmt_number, ccdtime);
			cc_timing[2][6]->Fill(pmt_number, ccdtime);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			theta_vs_segm[3][sector_i]->Fill(segm, xpos);
			theta_vs_segm[3][6]->Fill(segm, xpos);
			phi_match[3][sector_i]->Fill(ccphimatch);
			phi_match[3][6]->Fill(ccphimatch);
			cc_timing[3][sector_i]->Fill(pmt_number, ccdtime);
			cc_timing[3][6]->Fill(pmt_number, ccdtime);
		}
	}
	// End CCMATCH
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ECTHR
	// no cuts
	double mom = p.p.mod()/GeV;
	if(p.ccinfos.size() && p.cainfos.size())
	{
		ecthr[0][sector_i]->Fill(mom);
		ecthr[0][6]->Fill(mom);
		// all other on
		if(alloth["ECTHR"] == 1)
		{
			ecthr[1][sector_i]->Fill(mom);
			ecthr[1][6]->Fill(mom);
		}
		// all other off
		if(othneg["ECTHR"] == 1)
		{
			ecthr[2][sector_i]->Fill(mom);
			ecthr[2][6]->Fill(mom);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			ecthr[3][sector_i]->Fill(mom);
			ecthr[3][6]->Fill(mom);
		}
	}
	// End ECTHR
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ECP: Sampling Fraction
	// no cuts
	double Etot  = p.get("Emax")/GeV;
	double ecvsp = Etot/mom;
	if(p.ccinfos.size() && p.cainfos.size() && p.scinfos.size())
	{
		ecp[0][sector_i]->Fill(mom, ecvsp);
		ecp[0][6]->Fill(mom, ecvsp);
		// all other on
		if(alloth["ECP"] == 1)
		{
			ecp[1][sector_i]->Fill(mom, ecvsp);
			ecp[1][6]->Fill(mom, ecvsp);
		}
		// all other off
		if(othneg["ECP"] == 1)
		{
			ecp[2][sector_i]->Fill(mom, ecvsp);
			ecp[2][6]->Fill(mom, ecvsp);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			ecp[3][sector_i]->Fill(mom, ecvsp);
			ecp[3][6]->Fill(mom, ecvsp);
		}
	}
	// End ECP: Sampling Fraction
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// EC u,v,w coordinate cut
	// no cuts
	V3 uvw    = p.vget("ECuvw");
	V3 hitpos = p.vget("ECxyz");;
	if(p.ccinfos.size() && p.cainfos.size())
	{
		ECu[0][sector_i]->Fill(uvw.x/cm);
		ECu[0][6]->Fill(uvw.x/cm);
		ECv[0][sector_i]->Fill(uvw.y/cm);
		ECv[0][6]->Fill(uvw.y/cm);
		ECw[0][sector_i]->Fill(uvw.z/cm);
		ECw[0][6]->Fill(uvw.z/cm);
		ECpos[0]->Fill(hitpos.x/cm, hitpos.y/cm);
		// all other on
		if(alloth["ECUVW"] == 1)
		{
			ECu[1][sector_i]->Fill(uvw.x/cm);
			ECu[1][6]->Fill(uvw.x/cm);
			ECv[1][sector_i]->Fill(uvw.y/cm);
			ECv[1][6]->Fill(uvw.y/cm);
			ECw[1][sector_i]->Fill(uvw.z/cm);
			ECw[1][6]->Fill(uvw.z/cm);
			ECpos[1]->Fill(hitpos.x/cm, hitpos.y/cm);
		}
		// all other off
		if(othneg["ECUVW"] == 1)
		{
			ECu[2][sector_i]->Fill(uvw.x/cm);
			ECu[2][6]->Fill(uvw.x/cm);
			ECv[2][sector_i]->Fill(uvw.y/cm);
			ECv[2][6]->Fill(uvw.y/cm);
			ECw[2][sector_i]->Fill(uvw.z/cm);
			ECw[2][6]->Fill(uvw.z/cm);
			ECpos[2]->Fill(hitpos.x/cm, hitpos.y/cm);
		}
		// every cut
		if(passed["CCMATCH"]*passed["ECTHR"]*passed["ECP"]*passed["EPOU"]*passed["ECIO"]*passed["INTO"] == 1)
		{
			ECu[3][sector_i]->Fill(uvw.x/cm);
			ECu[3][6]->Fill(uvw.x/cm);
		}
		if(passed["CCMATCH"]*passed["ECTHR"]*passed["ECP"]*passed["EPOV"]*passed["ECIO"]*passed["INTO"] == 1)
		{
			ECv[3][sector_i]->Fill(uvw.y/cm);
			ECv[3][6]->Fill(uvw.y/cm);
		}
		if(passed["CCMATCH"]*passed["ECTHR"]*passed["ECP"]*passed["EPOW"]*passed["ECIO"]*passed["INTO"] == 1)
		{
			ECw[3][sector_i]->Fill(uvw.z/cm);
			ECw[3][6]->Fill(uvw.z/cm);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			ECpos[3]->Fill(hitpos.x/cm, hitpos.y/cm);
		}
		// Only UVW cut
		if(passed["ECUVW"] == 1)
			ECpos[4]->Fill(hitpos.x/cm, hitpos.y/cm);
	}
	// End ECP: u,v,w coordinate cut
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// ECIO:  Eout/p vs Ein/p
	// no cuts
	double EinP  = (p.get("Ein")/GeV) /mom;
	double EoutP = (p.get("Eout")/GeV)/mom;
	if(p.ccinfos.size() && p.cainfos.size())
	{
		EoutEin[0][sector_i]->Fill(EinP, EoutP);
		EoutEin[0][6]->Fill(EinP, EoutP);
		// all other on
		if(alloth["ECIO"] == 1)
		{
			EoutEin[1][sector_i]->Fill(EinP, EoutP);
			EoutEin[1][6]->Fill(EinP, EoutP);
		}
		// all other off
		if(othneg["ECIO"] == 1)
		{
			EoutEin[2][sector_i]->Fill(EinP, EoutP);
			EoutEin[2][6]->Fill(EinP, EoutP);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			EoutEin[3][sector_i]->Fill(EinP, EoutP);
			EoutEin[3][6]->Fill(EinP, EoutP);
		}
	}
	// End ECIO: Ein/p vs Eout/p
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// INTO: inner/total
	// no cuts
	double into = (p.get("Ein")/GeV)/Etot;
	if(p.ccinfos.size() && p.cainfos.size())
	{
		EinEtot[0][sector_i]->Fill(mom, into);
		EinEtot[0][6]->Fill(mom, into);
	
		// all other on
		if(alloth["INTO"] == 1)
		{
			EinEtot[1][sector_i]->Fill(mom, into);
			EinEtot[1][6]->Fill(mom, into);
		}
		// all other off
		if(othneg["INTO"] == 1)
		{
			EinEtot[2][sector_i]->Fill(mom, into);
			EinEtot[2][6]->Fill(mom, into);
		}
		// every cut
		if(passed["PASSED"] == 1)
		{
			EinEtot[3][sector_i]->Fill(mom, into);
			EinEtot[3][6]->Fill(mom, into);
		}
	}
	// End INTO: inner/total
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
	// utility histos
	if(p.ccinfos.size() && alloth["CCMATCH"] ) nphe_phi->Fill(p.ccinfos[0].npe, 60*sector_i + p.rel_phi()/degree);
	
	// Monitor:
	if(p.ccinfos.size() && p.cainfos.size())
	{
		monitor[0][sector_i]->Fill(0);
		monitor[0][6]->Fill(0);
		// each cut individually	
		if(passed["NPHE"] == 1)
		{
			monitor[0][sector_i]->Fill(1);
			monitor[0][6]->Fill(1);
		}
		if(passed["ECTHR"] == 1)
		{
			monitor[0][sector_i]->Fill(2);
			monitor[0][6]->Fill(2);
		}
		if(passed["ECP"] == 1)
		{
			monitor[0][sector_i]->Fill(3);
			monitor[0][6]->Fill(3);
		}
		if(passed["EPOU"] == 1)
		{
			monitor[0][sector_i]->Fill(4);
			monitor[0][6]->Fill(4);
		}
		if(passed["EPOV"] == 1)
		{
			monitor[0][sector_i]->Fill(5);
			monitor[0][6]->Fill(5);
		}
		if(passed["EPOW"] == 1)
		{
			monitor[0][sector_i]->Fill(6);
			monitor[0][6]->Fill(6);
		}
		if(passed["ECUVW"] == 1)
		{
			monitor[0][sector_i]->Fill(7);
			monitor[0][6]->Fill(7);
		}
		if(passed["ECIO"] == 1)
		{
			monitor[0][sector_i]->Fill(8);
			monitor[0][6]->Fill(8);
		}
		if(passed["INTO"] == 1)
		{
			monitor[0][sector_i]->Fill(9);
			monitor[0][6]->Fill(9);
		}
		if(passed["CCMATCH"] == 1)
		{
			monitor[0][sector_i]->Fill(10);
			monitor[0][6]->Fill(10);
		}
		
		// cuts are applied one after the other
		monitor[1][sector_i]->Fill(0);
		monitor[1][6]->Fill(0);
		if(passed["NPHE"] == 1 || 1)
		{
			monitor[1][sector_i]->Fill(1);
			monitor[1][6]->Fill(1);
			if(passed["ECTHR"] == 1)
			{
				monitor[1][sector_i]->Fill(2);
				monitor[1][6]->Fill(2);
				if(passed["ECP"] == 1)
				{
					monitor[1][sector_i]->Fill(3);
					monitor[1][6]->Fill(3);
					if(passed["EPOU"] == 1)
					{
						monitor[1][sector_i]->Fill(4);
						monitor[1][6]->Fill(4);
						if(passed["EPOV"] == 1)
						{
							monitor[1][sector_i]->Fill(5);
							monitor[1][6]->Fill(5);
							if(passed["EPOW"] == 1)
							{
								monitor[1][sector_i]->Fill(6);
								monitor[1][6]->Fill(6);
								if(passed["ECUVW"] == 1)
								{
									monitor[1][sector_i]->Fill(7);
									monitor[1][6]->Fill(7);
									if(passed["ECIO"] == 1)
									{
										monitor[1][sector_i]->Fill(8);
										monitor[1][6]->Fill(8);
										if(passed["INTO"] == 1)
										{
											monitor[1][sector_i]->Fill(9);
											monitor[1][6]->Fill(9);
											if(passed["CCMATCH"] == 1)
											{
												monitor[1][sector_i]->Fill(10);
												monitor[1][6]->Fill(10);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// Counting Hits in CC, EC
	monitor[2][sector_i]->Fill(0);
	monitor[2][6]->Fill(0);
	if(p.ccinfos.size())
	{
		monitor[2][sector_i]->Fill(1);
		monitor[2][6]->Fill(1);
	}
	if(p.cainfos.size())
	{
		monitor[2][sector_i]->Fill(2);
		monitor[2][6]->Fill(2);
	}
	if(p.ccinfos.size() && p.cainfos.size())
	{
		monitor[2][sector_i]->Fill(3);
		monitor[2][6]->Fill(3);
	}
}


void histos::set_vars(map<string, int> passed)
{
	alloth.clear();
	othneg .clear();
	
	// NPHE cut	
	if( passed["ECP"]* passed["ECUVW"]* passed["ECIO"]* passed["INTO"]* passed["ECTHR"] == 1)
		alloth["NPHE"] = 1;
	if(!passed["ECP"]*!passed["ECUVW"]*!passed["ECIO"]*!passed["INTO"]*!passed["ECTHR"] == 1)
		othneg["NPHE"] = 1;
	
	// CCMATCH cut
	if( passed["ECP"]* passed["ECUVW"]* passed["ECIO"]* passed["INTO"]* passed["ECTHR"] == 1)
		alloth["CCMATCH"] = 1;
	if(!passed["ECP"]*!passed["ECUVW"]*!passed["ECIO"]*!passed["INTO"]*!passed["ECTHR"] == 1)
		othneg["CCMATCH"] = 1;
	
	// ECTHR cut
	if( passed["CCMATCH"]* passed["ECP"]* passed["ECUVW"]* passed["ECIO"]* passed["INTO"] == 1)
		alloth["ECTHR"] = 1;
	if(!passed["CCMATCH"]*!passed["ECP"]*!passed["ECUVW"]*!passed["ECIO"]*!passed["INTO"] == 1) 
		othneg["ECTHR"] = 1;
	
	// ECP: sampling fraction
	if( passed["CCMATCH"]* passed["ECUVW"]* passed["ECIO"] *passed["INTO"] == 1)
		alloth["ECP"] = 1;
	if(!passed["CCMATCH"]*!passed["ECUVW"]*!passed["ECIO"]*!passed["INTO"] == 1) 
		othneg["ECP"] = 1;
	
	// ECUVW: coordinates in EC
	if( passed["CCMATCH"]* passed["ECP"]* passed["ECIO"] *passed["INTO"]* passed["ECTHR"] == 1)
		alloth["ECUVW"] = 1;
	if(!passed["CCMATCH"]*!passed["ECP"]*!passed["ECIO"]*!passed["INTO"]*!passed["ECTHR"] == 1) 
		othneg["ECUVW"] = 1;
	
	// ECIO: Ein/p vs Eout/p
	if( passed["CCMATCH"]* passed["ECP"]* passed["ECUVW"] *passed["INTO"]* passed["ECTHR"] == 1)
		alloth["ECIO"] = 1;
	if(!passed["CCMATCH"]*!passed["ECP"]*!passed["ECUVW"]*!passed["INTO"]*!passed["ECTHR"] == 1) 
		othneg["ECIO"] = 1;
	
	// INTO: inner/total
	if( passed["CCMATCH"]* passed["ECP"]* passed["ECUVW"]* passed["ECIO"]* passed["ECTHR"] == 1)
		alloth["INTO"] = 1;
	if(!passed["CCMATCH"]*!passed["ECP"]*!passed["ECUVW"]*!passed["ECIO"] == 1) 
		othneg["INTO"] = 1;
}








