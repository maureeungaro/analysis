double theta_cut(int s, double p, double pars[6][6])
{
 return pars[s-1][0] + pars[s-1][1]/(p + pars[s-1][5]) ; 
}

double expon(int s, double p, double pars[6][6])
{
 return pars[s-1][2] * pow(p, pars[s-1][4]) ;
}

double fidu(int s, double p, double t, double pars[6][6])
{
 double thc  = theta_cut(s, p, pars);
 double expo = expon(    s, p, pars);

 
 if(t>thc/RD && t<thc/RD + 3.141592) return pars[s-1][3] * pow( sin(t - thc/RD) , expo);
 else return 0;
}

double fidu_p(int s, double p, double t, int UD, double PARS[6][5][3][2])
{
 double a[5], b[5];
 
 for(int r=0; r<5; r++)
 {
  a[r] =  PARS[s-1][r][0][0] + p*PARS[s-1][r][1][0] + p*p*PARS[s-1][r][2][0];
  b[r] =  PARS[s-1][r][0][1] + p*PARS[s-1][r][1][1] + p*p*PARS[s-1][r][2][1];  
 }
 if(t>42) t=42;
 if(UD == -1) return a[0] + t*a[1] + t*t*a[2] + t*t*t*a[3] + t*t*t*t*a[4];
 if(UD ==  1) return b[0] + t*b[1] + t*t*b[2] + t*t*t*b[3] + t*t*t*t*b[4]; 
 
 else return 0; 
}




int q2bin(double Q2)
{
 
 if(fabs(Q2-2.0) < 0.19) return 0;
 if(fabs(Q2-2.4) < 0.22) return 1;
 if(fabs(Q2-3.0) < 0.26) return 2;
 if(fabs(Q2-3.5) < 0.31) return 3;
 if(fabs(Q2-4.2) < 0.37) return 4;
 if(fabs(Q2-5.0) < 0.44) return 5;
 if(fabs(Q2-6.0) < 0.53) return 6;     

}














