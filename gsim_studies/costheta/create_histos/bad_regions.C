double fun(double  x, double p0, double p1, double p2) {return p0 + p1 * sqrt(x - p2 ) ;}
double fun2(double x, double p0, double p1, double p2) {return p0 + p1 * pow(x - p2,2) ;}

int e_bad_regions(V4 k)
{
 int Y    = 1;
 int S    = sect(k.phi());
 double t = k.theta()*RD;
 double p = k.mod();
 
 double pm, pM, up, low;
 
 if(S==2) 
 {
  up  = fun(p, 35.5, -4, 1.5);
  low = fun(p, 34,   -4, 1.5);  
  pm  = 1.6;
  pM  = 4;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
   
  up  = fun(p, 27.3, -4.8, 1.5);
  low = fun(p, 26.7, -4.8, 1.5);  
  pm  = 1.6;
  pM  = 4.15;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
  
  up  = fun(p, 28.5, -4.8, 1.5);
  low = fun(p, 28.1, -4.8, 1.5);  
  pm  = 1.6;
  pM  = 4.0;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
 }
 
  
 if(S==5)
 {
  up  = 21;
  low = fun(p, 21.3,  -2.4, 2);
  pm  = 2;
  pM = 4.6;
  if(t<up && t>low && p>pm && p<pM) Y=0;

  
  up  = fun(p, 25.3, 2.4, 1.9);
  low = fun(p, 26.3,  -2.4, 1.9);  
  pm  = 1.9;
  pM  = 4.6;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
 }
 

 if(S==6) 
 {
  up  = fun(p, 31, -5, 1.5);
  low = fun(p, 29.5, -5.2, 1.5);  
  pm  = 1.6;
  pM  = 4.6;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
   
  up  = fun(p, 38, -3, 1.5);
  low = fun(p, 36, -3.0, 1.5);  
  pm  = 1.6;
  pM  = 3.6;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
 }
 
 return Y;
}



int p_bad_regions(V4 k)
{
 int Y    = 1;
 int S    = sect(k.phi());
 double t = k.theta()*RD;
 double p = k.mod();
 
 double pm, pM, up, low;
 
 if(S==2) 
 {
  up  = fun(p, 33.4, 8,   0.9);
  low = fun(p, 31.0, 8.7, 0.9);  
  pm  = 0.9;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
   
  up  = 27.2;
  low = 24.7;  
  pm  = 0.9;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
 }
 
 if(S==3)
 {
  up  = fun(p, 37.7, 6.0, 0.9);
  low = fun(p, 31.5, 9.0, 0.9);  
  pm  = 0.9;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;  
 }
 
 
 if(S==5)
 {
  up  = fun(p,  11, 3.5, 0.9);
  low = fun2(p, 13.5, -0.38, 4.0);  
  pm  = 0.9;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;  

  up  = 11.2;
  low = 10.1;  
  pm  = 1.0;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;        
 }
 
 
 
 if(S==6)
 {
  up  = fun2(p, 29.2, -1.9, 3.2);
  low = fun2(p, 26, -1.3, 3.5);  
  pm  = 0.9;
  pM  = 4.4;
  if(t<up && t>low && p>pm && p<pM) Y=0;  
  
  up  = fun2(p, 29.2, -1.9, 3.2);
  low = fun(p, 10.0, 14, 0.9);  
  pm  = 0.9;
  pM  = 1.5;
  if(t<up && t>low && p>pm && p<pM) Y=0;  
  
  
  up  = fun(p, 32.4, 5, 0.9);
  low = fun(p, 30.7, 5.5, 0.9);  
  pm  = 0.9;
  pM  = 2.5;
  if(t<up && t>low && p>pm && p<pM) Y=0;    

  up  = fun(p, 7.5, 9, 0.9);
  low = fun(p, 6.5, 9, 0.9);  
  pm  = 0.9;
  pM  = 4.0;
  if(t<up && t>low && p>pm && p<pM) Y=0;    
 }
 
 return Y;
}
