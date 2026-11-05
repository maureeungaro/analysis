#include <iostream>
#include <cmath>   
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

#include "Clas_event.C"
#include "definition.h"
#include <utilities.C>
#include "fiducial.C"
#include "bad_regions.C"

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"


TROOT root("hello","Mu Analysis");
int main(int argc, char **argv)    
{
 double E = 5.7542;
 const int NQ2 = 7;
 
 static double pars[6][6];	     // 6 sectors - 6 parameters 
 static double PARS[6][5][3][2];     // 6 sectors - 5 parameters  - par of parameter - down/up
 
 ifstream IN("electron_par.txt");
 if(!IN) 
 {
  cout << " File electron_par.txt not found. Exiting. " << endl;
  exit(9);
 }
 for(int s=0; s<6; s++)
  for(int p=0; p<6; p++)
   IN >> pars[s][p] ;  
 IN.close();               
  
 IN.open("proton_fiducial.txt"); 
 if(!IN) 
 {
  cout << " File proton_fiducial.txt not found. Exiting. " << endl;
  exit(9);
 } 
 for(int s=0; s<6; s++) 
  for(int p=0; p<5; p++)
   for(int pp=0; pp<3; pp++)   
    for(int w=0; w<2; w++)
     IN >> PARS[s][p][pp][w] ; 
 IN.close();            

    
 Clas_event Ev;
 particle   mce, mcP, pi0;              // thrown particle
 particle     e,   P;                   // recon particle
  
 V4         k, Pi;                      // thrown 4-vectors
 
 V4         mckf, mcPf;                 // recon 4-vectors
 V4           kf,   Pf, PP;             // recon 4-vectors
 
 V4         mcq,  mcH,  mcmiss,  mcmissCM;  // thrown 4-vectors
 V4         mcq2, mcH2, mcmiss2, mcmissCM2; // thrown 4-vectors 
 V4           q,    H,    miss,    missCM;  // recon 4-vectors
 
 k.t = k.z = E;
 k.x = k.y = Pi.x = Pi.y = Pi.z =0;
  
 Pi.t = MP;
 int acce, accp;
 int depe, depp;
 double W, mcW;
 
 double q2_values[NQ2]  = { 2.00, 2.40, 3.00, 3.50, 4.20, 5.00, 6.00};
 double diQ2[NQ2]       = { 0.36, 0.43, 0.51, 0.62, 0.73, 0.88, 1.05};  

 string Qs[NQ2] = {"Q2=2+-0.18", "Q2=2.4+-0.21", "Q2=3+-0.25", "Q2=3.5+-0.31", "Q2=4.2+-0.36", "Q2=5+-0.44", "Q2=6+-0.52"};  
 string what[3] = {"ele", "pro", "pi0"};
 string cut[3]  = {"noc", "fid", "rec"};
 
 
 // ROOT initializations  --------------------------------------------------------------------

 TFile *output = new TFile("muana.root","RECREATE",""); 
 
 TH1F *CT[2][3][NQ2];        // COSTH* --- invar and lorentz invariant methos ---  after fiducial - after recon -- for different Q2 
 TH1F *CT_diff[2][2][NQ2];   // COSTH* (rec-gen) --- invar and lorentz invariant methos ---  after fiducial - after recon -- for different Q2
 TH2F *CTp_diff[2][2][NQ2];  // COSTH* (rec-gen) --- invar and lorentz invariant methos ---  after fiducial - after recon -- for different Q2 as a function of proton momenta
 TH2F *CTt_diff[2][2][NQ2];  // COSTH* (rec-gen) --- invar and lorentz invariant methos ---  after fiducial - after recon -- for different Q2 as a function of proton angle
 TH2F *CTh_diff[2][2][NQ2];  // COSTH* (rec-gen) --- invar and lorentz invariant methos ---  after fiducial - after recon -- for different Q2 as a function of cm miss angle
  
 TH2F *phth[3][3][NQ2];      // Phi vs theta for electron - proton - CM missing -- before fiducial - after fiducial - after recon  --- for different Q2
    

 for(int iQ2=0; iQ2<NQ2; iQ2++) 
 {
  for(int icut=0; icut<3; icut++)
  {
   phth[0][icut][iQ2]    = new TH2F(Form("phth_e_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), Form("phth_e_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), 100, 10+q2_values[iQ2]*2, 24+q2_values[iQ2]*5, 100, -40, 340);       
   phth[1][icut][iQ2]    = new TH2F(Form("phth_p_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), Form("phth_p_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), 100, 5, 50, 100, -40, 340);       
   phth[2][icut][iQ2]    = new TH2F(Form("phth_x_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), Form("phth_x_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), 100, 0, 180, 100, -10, 370);        
   
   CT[0][icut][iQ2]      = new TH1F(Form("Costh_invar_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), Form("Costh_invar_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), 100, -1.3, 1.3);
   CT[1][icut][iQ2]      = new TH1F(Form("Costh_loren_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), Form("Costh_loren_%s_Q2_%f", cut[icut].c_str(), q2_values[iQ2]), 100, -1.3, 1.3);      
  }   
  
  CT_diff[0][0][iQ2]    = new TH1F(Form("diff_costh_invar_thr_Q2_%f",     q2_values[iQ2]), Form("diff_costh_invar_thr_Q2_%f",     q2_values[iQ2]), 100, -10, 10 );  
  CT_diff[0][1][iQ2]    = new TH1F(Form("diff_costh_invar_rec_Q2_%f",     q2_values[iQ2]), Form("diff_costh_invar_rec_Q2_%f",     q2_values[iQ2]), 100, -10, 10 );  
  CT_diff[1][0][iQ2]    = new TH1F(Form("diff_costh_loren_thr_Q2_%f",     q2_values[iQ2]), Form("diff_costh_loren_thr_Q2_%f",     q2_values[iQ2]), 100, -10, 10 ); 
  CT_diff[1][1][iQ2]    = new TH1F(Form("diff_costh_loren_rec_Q2_%f",     q2_values[iQ2]), Form("diff_costh_loren_rec_Q2_%f",     q2_values[iQ2]), 100, -10, 10 ); 
   
  CTt_diff[0][0][iQ2]   = new TH2F(Form("diff_costh_th_invar_thr_Q2_%f",  q2_values[iQ2]), Form("diff_costh_th_invar_thr_Q2_%f",  q2_values[iQ2]), 100, 10, 48, 100, -10, 10 );  
  CTt_diff[0][1][iQ2]   = new TH2F(Form("diff_costh_th_invar_rec_Q2_%f",  q2_values[iQ2]), Form("diff_costh_th_invar_rec_Q2_%f",  q2_values[iQ2]), 100, 10, 48, 100, -10, 10 );  
  CTt_diff[1][0][iQ2]   = new TH2F(Form("diff_costh_th_loren_thr_Q2_%f",  q2_values[iQ2]), Form("diff_costh_th_loren_thr_Q2_%f",  q2_values[iQ2]), 100, 10, 48, 100, -10, 10 ); 
  CTt_diff[1][1][iQ2]   = new TH2F(Form("diff_costh_th_loren_rec_Q2_%f",  q2_values[iQ2]), Form("diff_costh_th_loren_rec_Q2_%f",  q2_values[iQ2]), 100, 10, 48, 100, -10, 10 ); 
   
  CTh_diff[0][0][iQ2]   = new TH2F(Form("diff_costh_ht_invar_thr_Q2_%f",  q2_values[iQ2]), Form("diff_costh_ht_invar_thr_Q2_%f",  q2_values[iQ2]), 100, -10, 190, 100, -10, 10 );  
  CTh_diff[0][1][iQ2]   = new TH2F(Form("diff_costh_ht_invar_rec_Q2_%f",  q2_values[iQ2]), Form("diff_costh_ht_invar_rec_Q2_%f",  q2_values[iQ2]), 100, -10, 190, 100, -10, 10 );  
  CTh_diff[1][0][iQ2]   = new TH2F(Form("diff_costh_ht_loren_thr_Q2_%f",  q2_values[iQ2]), Form("diff_costh_ht_loren_thr_Q2_%f",  q2_values[iQ2]), 100, -10, 190, 100, -10, 10 ); 
  CTh_diff[1][1][iQ2]   = new TH2F(Form("diff_costh_ht_loren_rec_Q2_%f",  q2_values[iQ2]), Form("diff_costh_ht_loren_rec_Q2_%f",  q2_values[iQ2]), 100, -10, 190, 100, -10, 10 );            
 }
 
 
 TH2F *momdiff = new TH2F("momdiff", "momdiff", 100, 0, 3, 100, -0.8, 0.8);    
 
 double COSTH;
 
 // Getting file list ------------------------------------------------------------------------
 char file[300];
 int Counter=0;

 ifstream LIST("list_of_files",ios::in);
 LIST >> file; 
 while(!LIST.eof()) 
 {
  ifstream ANA(file, ios::in | ios::binary);
  cout << endl << " input File " << file << endl;
 
  ANA >> Ev;
  while(!ANA.eof())
  {
   if(Ev.Particle.size())
   {
    acce = accp = 0;
    mce  = get_particle(Ev, 0);
    mcP  = get_particle(Ev, 1);
    pi0  = get_particle(Ev, 7);
    e    = get_particle(Ev, 100);
    P    = get_particle(Ev, 101);
                
    if(e.p[0].id == 1003 && P.p[0].id == 1014)
    {
     kf     = get_4vector(e);
//     Pf     = get_4vector(P);
     PP     = get_4vector(P);     
     Pf.set(PP.mod() - 0.004 , PP.theta(), PP.phi());
     Pf.t = sqrt(PP.mod()*PP.mod()+MP*MP);
    } 
    
    if(mce.p[0].id == 3 && mcP.p[0].id == 14)
    {
     mckf     = get_4vector(mce);
     mcPf     = get_4vector(mcP);
     mcmiss   = get_4vector(pi0);     
    }                     

     q        =   k -   kf;    
     H        =   q  +   Pi ;        
     miss     =   H  -   Pf ;        
     W        = sqrt(  H.mass());
     missCM   = lab_to_res(  H,   miss);              
        
     mcq      =   k - mckf;   
     mcH      = mcq  +   Pi ;        
     mcmiss   = mcH  - mcPf ;
     mcmissCM = lab_to_res(mcH, mcmiss);
     mcW      = sqrt(mcH.mass());      
     
/*     mcq       = k - mckf;        
     mcH       = mcPf  +   mcmiss ;              
     mcW       = sqrt(mcH.mass());           
     mcmissCM  = lab_to_res(mcH, mcmiss);     */

             
    if( fabs(rel_phi(mckf.phi()))  < fidu(sect(mckf.phi()), mckf.mod(), mckf.theta(), pars) )          acce = 1 ;
    if( rel_phi(mcPf.phi())  <=  fidu_p(sect(mcPf.phi()), mcPf.mod(), mcPf.theta()*RD,  1, PARS) &&
        rel_phi(mcPf.phi())  >=  fidu_p(sect(mcPf.phi()), mcPf.mod(), mcPf.theta()*RD, -1, PARS)    )  accp = 1 ;
	
    depe = e_bad_regions(mckf);     
    depp = p_bad_regions(mcPf);       
    
    phth[0][0][q2bin(-q.mass())]->Fill(    mckf.theta()*RD,     mckf.phib()*RD); 	 
    phth[1][0][q2bin(-q.mass())]->Fill(    mcPf.theta()*RD,     mcPf.phib()*RD);
    phth[2][0][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD, mcmissCM.phi()*RD);  
    
    CT[0][0][q2bin(-mcq.mass())]->Fill(  mcmissCM.z * 2 * mcW /sqrt( (mcW*mcW-(MP-Mpi0)*(MP-Mpi0))*(mcW*mcW-(MP+Mpi0)*(MP+Mpi0)))  );
    CT[1][0][q2bin(-mcq.mass())]->Fill( cos(mcmissCM.theta()) );
     
    
    if(e.p[0].id == 1003 && P.p[0].id == 1014)
    {        
     COSTH = missCM.z * 2 * W /sqrt( (W*W-(MP-Mpi0)*(MP-Mpi0))*(W*W-(MP+Mpi0)*(MP+Mpi0))) ;
     CT_diff[0][0][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD -  acos( COSTH )*RD);    
     CT_diff[1][0][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD - missCM.theta()*RD);
    
     CTt_diff[0][0][q2bin(-q.mass())]->Fill(mcPf.theta()*RD, mcmissCM.theta()*RD -  acos( COSTH )*RD);    
     CTt_diff[1][0][q2bin(-q.mass())]->Fill(mcPf.theta()*RD, mcmissCM.theta()*RD - missCM.theta()*RD);
    
     CTh_diff[0][0][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD, mcmissCM.theta()*RD -  acos( COSTH )*RD);    
     CTh_diff[1][0][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD, mcmissCM.theta()*RD - missCM.theta()*RD);
    }
    
                  
    if(acce*accp*depe*depp)
    {          
     phth[0][1][q2bin(-q.mass())]->Fill(    mckf.theta()*RD,     mckf.phib()*RD); 
     phth[1][1][q2bin(-q.mass())]->Fill(    mcPf.theta()*RD,     mcPf.phib()*RD);  
     phth[2][1][q2bin(-q.mass())]->Fill(mcmissCM.theta()*RD,  mcmissCM.phi()*RD);   
     
     CT[0][1][q2bin(-mcq.mass())]->Fill(  mcmissCM.z * 2 * mcW /sqrt( (mcW*mcW-(MP-Mpi0)*(MP-Mpi0))*(mcW*mcW-(MP+Mpi0)*(MP+Mpi0)))  );
     CT[1][1][q2bin(-mcq.mass())]->Fill( cos(mcmissCM.theta()) );
    }
           
    if(e.p[0].id == 1003 && P.p[0].id == 1014)
    {            
     COSTH = missCM.z * 2 * W /sqrt( (W*W-(MP-Mpi0)*(MP-Mpi0))*(W*W-(MP+Mpi0)*(MP+Mpi0)))  ;    
     CT[0][2][q2bin(-mcq.mass())]->Fill( COSTH );
     CT[1][2][q2bin(-mcq.mass())]->Fill(cos(missCM.theta()));
             
     CT_diff[0][1][q2bin(-mcq.mass())]->Fill(mcmissCM.theta()*RD -  acos( COSTH )*RD);         
     CT_diff[1][1][q2bin(-mcq.mass())]->Fill(mcmissCM.theta()*RD - missCM.theta()*RD);     
     
     CTt_diff[0][1][q2bin(-mcq.mass())]->Fill(mcPf.theta()*RD, mcmissCM.theta()*RD -  acos( COSTH )*RD);    
     CTt_diff[1][1][q2bin(-mcq.mass())]->Fill(mcPf.theta()*RD, mcmissCM.theta()*RD - missCM.theta()*RD);
     
     CTh_diff[0][1][q2bin(-mcq.mass())]->Fill(mcmissCM.theta()*RD, mcmissCM.theta()*RD -  acos( COSTH )*RD);    
     CTh_diff[1][1][q2bin(-mcq.mass())]->Fill(mcmissCM.theta()*RD, mcmissCM.theta()*RD - missCM.theta()*RD);
    }
   	
      
           
    Counter++;     
   }      
   Ev.Particle.clear();
   Ev.Scaler.clear();
   ANA >> Ev;
  }

  ANA.close();
  cout << " Events analysed  " << Counter << endl;
  LIST >> file; 
 }
 LIST.close();

 
 // Closing and writing -------------------
 for(int iQ2=0; iQ2<NQ2; iQ2++) 
 {
  for(int icut=0; icut<3; icut++)
  {
   phth[0][icut][iQ2]->Write();    
   phth[1][icut][iQ2]->Write();
   phth[2][icut][iQ2]->Write();  

   CT[0][icut][iQ2]->Write();
   CT[1][icut][iQ2]->Write();        
  } 
   
  CT_diff[0][0][iQ2]->Write();   
  CT_diff[0][1][iQ2]->Write();        
  CT_diff[1][0][iQ2]->Write();   
  CT_diff[1][1][iQ2]->Write();        
   
  CTt_diff[0][0][iQ2]->Write();   
  CTt_diff[0][1][iQ2]->Write();        
  CTt_diff[1][0][iQ2]->Write();   
  CTt_diff[1][1][iQ2]->Write();   
    
 }
 
 momdiff->Write();    
 output->Close();
 return 0;
}








