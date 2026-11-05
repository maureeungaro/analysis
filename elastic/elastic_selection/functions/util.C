void switchPRINT(int *OPT)
{
 if(*OPT==0)
 {
  cout << " Printing enabled." << endl;
  *OPT=1;
  return;
 }
 if(*OPT==1)
 {
  cout << " Printing disabled." << endl;
  *OPT=0;
  return;
 }
}

