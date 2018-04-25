double func(double *x, double *par)
{
 double value=0;
 for(int k=0; k<11; k++){ value += par[k]*pow(x[0],k);}
 return value;
}

void fit()
{
 TF1 *freg[3][2];

 for(int r=0; r<3; r++)
 {
//  freg[r][0] = new TF1(Form("frem%d", r+1), func, LowLimit[r], HigLimit[r] + 0.1*(r+1), 11);  // Added shift so that mean is forced to zero 
  freg[r][0] = new TF1(Form("frem%d", r+1), func, LowLimit[r], HigLimit[r],      11);  // Added shift so that mean is forced to zero 
  freg[r][1] = new TF1(Form("fres%d", r+1), func, LowLimit[r], HigLimit[r],             11);

  
  // MEAN
  freg[r][0]->SetParameter(0, Constram[r]);                      // first parameter is fixed 
  freg[r][0]->SetParLimits(0, 1,1);           
  for(int p=Nparm; p<11; p++) freg[r][0]->SetParLimits(p, 1, 1); // only Nparm parameters used for mean
  Rem[r][1]->Fit(Form("frem%d", r+1), "REMN");
  for(int p=0; p<11; p++)
  {
   parameters[r][p][0] = freg[r][0]->GetParameter(p);
   Frem[r]->SetParameter(p, parameters[r][p][0]);
  }

    
  // SIGMA
  freg[r][1]->SetParameter(0, Constras[r]);                      // first parameter is fixed   
  freg[r][1]->SetParLimits(0, 1, 1);
  for(int p=Npars; p<11; p++) freg[r][1]->SetParLimits(p, 1, 1); // only Nparm parameters used for mean
  Res[r][1]->Fit(Form("fres%d", r+1), "REMN");
  for(int p=0; p<11; p++)
  {
   parameters[r][p][1] = freg[r][1]->GetParameter(p);
   Fres[r]->SetParameter(p, parameters[r][p][1]);
  }
 
 }
 
 plot_means(1);
 plot_sigmas(1);
}


void save()
{
 cout << endl << " Saving parameters to file pars.txt..." <<  endl;
 ofstream OUT("pars.txt");
  
 for(int p=0; p<11; p++)
 {
  OUT << setw(10) << Frem[0]->GetParameter(p) << " " << setw(10) << Frem[1]->GetParameter(p) << " " << setw(10) << Frem[2]->GetParameter(p) << "                 " ;
  OUT << setw(10) << Fres[0]->GetParameter(p) << " " << setw(10) << Fres[1]->GetParameter(p) << " " << setw(10) << Fres[2]->GetParameter(p) << endl;
 }

 OUT.close();

}