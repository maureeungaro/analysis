// void palette()
// {
// 
//  const int nb=40;
//  const int ng=40;
//  const int nr=80;
//  const int ny=80;
//  const int nw=40;
// 
//  int PALETTE[nb+ng+nr+ny+nw];
// 
//  for (int i=0;i<nb;i++) 
//  {
//   TColor *color = new TColor(500+i, .4, 0, .2+.7*i/(nb*1.0),"");
//   PALETTE[i] = 500+i;
//  }
// 
//  for (int i=0;i<ng;i++) 
//  {
//   TColor *color2 = new TColor(500+nb+i,.2,i/(ng*1.0),1.-i/(ng*1.0),"");
//   PALETTE[nb+i] = 500+nb+i;
//  }
// 
//  for (int i=0;i<nr;i++) 
//  {
//   TColor *color3 = new TColor(500+nb+ng+i,.2+.8*i/(nr*1.0)  ,1.-i/(nr*1.0),0,"");
//   PALETTE[nb+ng+i] = 500+nb+ng+i;
//  }
// 
//  for (int i=0;i<ny;i++) 
//  {
//   TColor *color4 = new TColor(500+nb+ng+nr+i,1 ,i/(ny*1.0),0,"");
//   PALETTE[nb+ng+nr+i] = 500+nb+ng+nr+i;
//  }
// 
//  for (int i=0;i<nw;i++) 
//  {
//   TColor *color5 = new TColor(500+nb+ng+nr+ny+i,1 ,1 ,i/(nw*1.0) ,"");
//   PALETTE[nb+ng+nr+ny+i] = 500+nb+ng+nr+ny+i;
//  }
// 
//  gStyle->SetPalette(nb+ng+nr+ny+nw,PALETTE);  
// }


// #include <iostream>
// using namespace std;
// 
//  void palette()
//  {
//  //example of new colors and definition of a new palette
// 
//  const Int_t colNum = 30,paletteSize=100;
//  Int_t startColor=700;
//  Int_t palette[paletteSize],n=5;
//  Float_t R,G,B;
// 
//  for (Int_t i=0;i<paletteSize;i++) {
// 
//    if(i<colNum){
//      R=1-(i/((colNum)*2.0));
//      G=1-(i/((colNum)*2.0));
//      B=1-(i/((colNum)*2.0));
// 
//      B+=0.5*pow(i*1.0/(colNum*1.0),n);
//    }
//    if(i>=colNum && i<2*colNum){
//      R=0;
//      G=0;
//      B=1-((i-colNum)/((colNum)*2.0));
// 
//      R+=0.5*pow((2.0*colNum-i)/(colNum*1.0),n);
//      G+=0.5*pow((2.0*colNum-i)/(colNum*1.0),n);
//      G+=1.0*pow((i-1.0*colNum)/(colNum*1.0),n);
//      //B+=0.5-((i-colNum)/((colNum)*2.0));
//    }
//    if(i>=2*colNum &&i<3*colNum){
//      R=0;
//      G=1-((i-2*colNum)/((colNum)*2.));
//      B=0;
//      B+=0.5*pow((3.0*colNum-i*1.0)/(colNum*1.0),n);
//      //     R+=1.0*pow((i-2.0*colNum)/(colNum*1.0),n);
// 
//      //fprintf(stderr,"B=%f G=%f R=%d\n",B,G,R);
//    }
//    if(i>=3*colNum && i<4*colNum){
// 
//      R=1-(((140-i)-3*colNum)/((colNum)*1.5));
//      G=0;
//      B=0;
// 
//      G+=0.5*pow((4.0*colNum-(140-i))/(colNum*1.0),n);
//      //da chiaro a scuro
// //      R=1-((i-3*colNum)/((colNum)*2.0));
// //      G=0;
// //      B=0;
// 
//      G+=0.5*pow((4.0*colNum-i)/(colNum*1.0),n);
//    }
// 
//    if(i>=4*colNum && i<=5*colNum){
//  
// //rosso ancora piu' scuro
// //      R=(0.5-0.3*((i-4*colNum)/((colNum)*2.0)));
// //      G=0;
// //      B=0;
// 
//      //giallo da scuro a chiaro
// //      G=1-(((180-i)-4*colNum)/((colNum)*2.0));
// //      R=1-(((180-i)-4*colNum)/((colNum)*2.0));
// //      B=0;
// 
// //      R-=0.5*pow((4.0*colNum-(180-i)*1.0)/(colNum*1.0),n);
// //      G+=0.5*pow((4.0*colNum-(180-i)*1.0)/(colNum*1.0),n);
// 
//      //giallo da chiaro a scuro
//      G=1-(((i)-4*colNum)/((colNum)*2.0));
//      R=1-(((i)-4*colNum)/((colNum)*2.0));
//      B=0;
// 
// 
//      G-=0.5*pow((5.0*colNum-(i)*1.0)/(colNum*1.0),n);
// 
// 
// 
//      //B+=0.5*pow((4.0*colNum-i)/(colNum*1.0),n);
// 
//    }
//    /*
//      R=0;
//      G=0;
// 
//      B=1-(i/((colNum)*6.0));
//    */
//    TColor *color = new TColor(startColor+i,R,G,B,"");
//    palette[i] = startColor+i;
//  }
// 
//  //changing default palette
// 
//  gStyle->SetPalette(paletteSize,palette);
// 
//  // can comment stuff below if don't want to see contur plot
// 
//  TF2 *f2 = new TF2("f2","exp(-(x^2) - (y^2))",-3,3,-3,3);
//  f2->SetContour(paletteSize-2); //<I changed colNum to colNum-2
//  f2->SetFillColor(0);
//  // f2->Draw("colz");
//  cout<<"macro to change palette loaded"<<endl;
// 
//  }

 void palette_bw()
 {
 //example of new colors and definition of a new palette
 const int NCOL = 5512;

 const int paletteSize=NCOL;
 int startColor=1000;
 int palette[paletteSize];
 double R,G,B;

 //changing default palette
 R = G = B = 1.0;
 for(int i = 0; i < NCOL ; i++) {
   double a;
   a = 1- ((double) i) / NCOL;
   TColor *color = new TColor(startColor+i,a*R,a*G,a*B,"");
   palette[i] = startColor+i;
 }
 gStyle->SetPalette(paletteSize,palette);
}





void MU()
{
 f=new TFile("muana.root");
 f.ls();
 t->Print();
}

