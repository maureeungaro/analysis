switch_WM()
{
 iWM++;
 if(iWM==NWM) iWM = 0;
 cout << endl << " W bin changed to " << iWM + 1 << endl;
 return;
}

switch_Q2()
{
 iQ2++;
 if(iQ2==NQ2) iQ2 = 0;
 cout << endl << " Q2 bin changed to " << iQ2 + 1 << endl;
 return;
}

void print_all()
{
 PRINT = 1;
 iWM   = 0;
 iQ2   = 0;
 for(int q=0; q<NQ2; q++)
 { 
  for(int w=0; w<NWM; w++)
  {
   show_mm();
   switch_WM();    
  }
  show_ww();        
  switch_Q2();
 }
 PRINT = 0;
}
