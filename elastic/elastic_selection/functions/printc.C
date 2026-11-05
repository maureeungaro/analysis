void printc(int w)
{
 gStyle->SetPadLeftMargin(0.14);     
 gStyle->SetPadRightMargin(0.04);     
 gStyle->SetPadTopMargin(0.01);     
 gStyle->SetPadBottomMargin(0.26);     

 double x[7],ex[7];

 for(int s=0; s<6; s++) {x[s] = s+1 ; ex[s]=0;}

 TCanvas *G=new TCanvas("G","fits results",700,850);
 TPad *P = new TPad("P","P", 0.0, 0.01, 1, 0.94);
 TLatex label;
 label.SetTextFont(44);
 label.SetTextSize(24);
 label.SetTextColor(4);
 label.SetNDC();

 label->DrawLatex(.08,.96,"Means and sigmas for   W");
 label.SetTextColor(9);
 label->DrawLatex(.5,.96,"mm(eP)");
 label.SetTextColor(6);
 label->DrawLatex(.65,.96,"#phi(e)-#phi(P)");
 label.SetTextColor(8);
 label->DrawLatex(.8,.96,"#Delta (#theta)");
 label.SetTextColor(45);
 label->DrawLatex(.88,.96," #Delta(#theta)_{ 2}");

 P->Draw();
 P->Divide(2,5);
 gStyle->SetTitleFont(44);

 TLine *lw = new TLine(0,0.9382,7,0.9382);
 TLine *lm = new TLine(0,0.    ,7,0.);
 TLine *lp = new TLine(0,180.  ,7,180);
 TLine *lt = new TLine(0,0.    ,7,0.);
 TLine *lb = new TLine(0,0.    ,7,0.);
  
 lw->SetLineColor(2);
 lm->SetLineColor(2);
 lp->SetLineColor(2);
 lt->SetLineColor(2);
 lb->SetLineColor(2);

 wgr1 = new TGraphErrors(6,x,meanw,ex,meanwe);
 wgr2 = new TGraphErrors(6,x,sigmw,ex,sigmwe);
 mgr1 = new TGraphErrors(6,x,meanm,ex,meanme);
 mgr2 = new TGraphErrors(6,x,sigmm,ex,sigmme);
 pgr1 = new TGraphErrors(6,x,meanp,ex,meanpe);
 pgr2 = new TGraphErrors(6,x,sigmp,ex,sigmpe);
 tgr1 = new TGraphErrors(6,x,meant,ex,meante);
 tgr2 = new TGraphErrors(6,x,sigmt,ex,sigmte);
 bgr1 = new TGraphErrors(6,x,meanb,ex,meanbe);
 bgr2 = new TGraphErrors(6,x,sigmb,ex,sigmbe);
 
 wgr1->SetMarkerStyle(22);
 wgr2->SetMarkerStyle(22);
 mgr1->SetMarkerStyle(22);
 mgr2->SetMarkerStyle(22);
 pgr1->SetMarkerStyle(22);
 pgr2->SetMarkerStyle(22);
 tgr1->SetMarkerStyle(22);
 tgr2->SetMarkerStyle(22);
 bgr1->SetMarkerStyle(22);
 bgr2->SetMarkerStyle(22);

 wgr1->SetMarkerColor(4);
 wgr2->SetMarkerColor(4);
 mgr1->SetMarkerColor(9);
 mgr2->SetMarkerColor(9);
 pgr1->SetMarkerColor(6);
 pgr2->SetMarkerColor(6);
 tgr1->SetMarkerColor(8);
 tgr2->SetMarkerColor(8);
 bgr1->SetMarkerColor(45);
 bgr2->SetMarkerColor(45);

 P->cd(1);  wgr1->Draw("AP");  
 P->cd(2);  wgr2->Draw("AP");
 P->cd(3);  mgr1->Draw("AP");
 P->cd(4);  mgr2->Draw("AP");
 P->cd(5);  pgr1->Draw("AP");
 P->cd(6);  pgr2->Draw("AP");
 P->cd(7);  tgr1->Draw("AP");
 P->cd(8);  tgr2->Draw("AP");
 P->cd(9);  bgr1->Draw("AP");
 P->cd(10); bgr2->Draw("AP");
 

 wgr1->GetHistogram()->SetXTitle("      W                  peak position            ");
 mgr1->GetHistogram()->SetXTitle("      mm                 peak position            ");
 pgr1->GetHistogram()->SetXTitle("  #Delta #phi            peak position            ");
 tgr1->GetHistogram()->SetXTitle("  #Delta #theta             peak position            ");
 bgr1->GetHistogram()->SetXTitle("  #Delta #theta _{  2}       peak position            ");

 wgr2->GetHistogram()->SetXTitle("      W                  sigma of peak            ");
 mgr2->GetHistogram()->SetXTitle("      mm                 sigma of peak            ");
 pgr2->GetHistogram()->SetXTitle("  #Delta #phi            sigma of peak            ");
 tgr2->GetHistogram()->SetXTitle("  #Delta #theta            sigma of peak            ");
 bgr2->GetHistogram()->SetXTitle("  #Delta #theta _{  2}        sigma of peak            ");

 wgr1->GetHistogram()->SetTitleSize(13,"X");
 mgr1->GetHistogram()->SetTitleSize(13,"X");
 pgr1->GetHistogram()->SetTitleSize(13,"X");
 tgr1->GetHistogram()->SetTitleSize(13,"X");
 bgr1->GetHistogram()->SetTitleSize(13,"X");
 
 wgr1->GetHistogram()->SetLabelSize(.08,"X");
 mgr1->GetHistogram()->SetLabelSize(.08,"X");
 pgr1->GetHistogram()->SetLabelSize(.08,"X");
 tgr1->GetHistogram()->SetLabelSize(.08,"X");
 bgr1->GetHistogram()->SetLabelSize(.08,"X");
 
 wgr1->GetHistogram()->SetLabelOffset(.03,"X");
 mgr1->GetHistogram()->SetLabelOffset(.03,"X");
 pgr1->GetHistogram()->SetLabelOffset(.03,"X");
 tgr1->GetHistogram()->SetLabelOffset(.03,"X");
 bgr1->GetHistogram()->SetLabelOffset(.03,"X");
 
 
 
 wgr1->GetHistogram()->SetTitleOffset(7,"X");
 mgr1->GetHistogram()->SetTitleOffset(7,"X");
 pgr1->GetHistogram()->SetTitleOffset(7,"X");
 tgr1->GetHistogram()->SetTitleOffset(7,"X");
 bgr1->GetHistogram()->SetTitleOffset(7,"X");
 
 wgr1->GetHistogram()->GetYaxis()->SetNdivisions(6);
 mgr1->GetHistogram()->GetYaxis()->SetNdivisions(6);
 pgr1->GetHistogram()->GetYaxis()->SetNdivisions(6);
 tgr1->GetHistogram()->GetYaxis()->SetNdivisions(6);
 bgr1->GetHistogram()->GetYaxis()->SetNdivisions(6);
 
 wgr1->GetHistogram()->GetXaxis()->SetNdivisions(6);
 mgr1->GetHistogram()->GetXaxis()->SetNdivisions(6);
 pgr1->GetHistogram()->GetXaxis()->SetNdivisions(6);
 tgr1->GetHistogram()->GetXaxis()->SetNdivisions(6);
 bgr1->GetHistogram()->GetXaxis()->SetNdivisions(6);
 
 wgr1->GetHistogram()->SetLabelOffset(.03,"Y");
 mgr1->GetHistogram()->SetLabelOffset(.03,"Y");
 pgr1->GetHistogram()->SetLabelOffset(.03,"Y");
 tgr1->GetHistogram()->SetLabelOffset(.03,"Y");
 bgr1->GetHistogram()->SetLabelOffset(.03,"Y");

  
 wgr1->GetHistogram()->SetLabelSize(.08,"Y");
 mgr1->GetHistogram()->SetLabelSize(.08,"Y");
 pgr1->GetHistogram()->SetLabelSize(.08,"Y");
 tgr1->GetHistogram()->SetLabelSize(.08,"Y");
 bgr1->GetHistogram()->SetLabelSize(.08,"Y");

 
 wgr1->GetHistogram()->GetXaxis()->SetTitleColor(4);
 mgr1->GetHistogram()->GetXaxis()->SetTitleColor(9);
 pgr1->GetHistogram()->GetXaxis()->SetTitleColor(6);
 tgr1->GetHistogram()->GetXaxis()->SetTitleColor(8);
 bgr1->GetHistogram()->GetXaxis()->SetTitleColor(45);

 wgr2->GetHistogram()->SetTitleSize(13,"X");
 mgr2->GetHistogram()->SetTitleSize(13,"X");
 pgr2->GetHistogram()->SetTitleSize(13,"X");
 tgr2->GetHistogram()->SetTitleSize(13,"X");
 bgr2->GetHistogram()->SetTitleSize(13,"X");
 
 wgr2->GetHistogram()->SetLabelSize(.08,"X");
 mgr2->GetHistogram()->SetLabelSize(.08,"X");
 pgr2->GetHistogram()->SetLabelSize(.08,"X");
 tgr2->GetHistogram()->SetLabelSize(.08,"X");
 bgr2->GetHistogram()->SetLabelSize(.08,"X");
 
 wgr2->GetHistogram()->SetLabelSize(.08,"Y");
 mgr2->GetHistogram()->SetLabelSize(.08,"Y");
 pgr2->GetHistogram()->SetLabelSize(.08,"Y");
 tgr2->GetHistogram()->SetLabelSize(.08,"Y");
 bgr2->GetHistogram()->SetLabelSize(.08,"Y");
 
 wgr2->GetHistogram()->SetLabelOffset(.03,"X");
 mgr2->GetHistogram()->SetLabelOffset(.03,"X");
 pgr2->GetHistogram()->SetLabelOffset(.03,"X");
 tgr2->GetHistogram()->SetLabelOffset(.03,"X");
 bgr2->GetHistogram()->SetLabelOffset(.03,"X");
 
 wgr2->GetHistogram()->SetLabelOffset(.03,"Y");
 mgr2->GetHistogram()->SetLabelOffset(.03,"Y");
 pgr2->GetHistogram()->SetLabelOffset(.03,"Y");
 tgr2->GetHistogram()->SetLabelOffset(.03,"Y");
 bgr2->GetHistogram()->SetLabelOffset(.03,"Y");
 
 
 wgr2->GetHistogram()->SetTitleOffset(7,"X");
 mgr2->GetHistogram()->SetTitleOffset(7,"X");
 pgr2->GetHistogram()->SetTitleOffset(7,"X");
 tgr2->GetHistogram()->SetTitleOffset(7,"X");
 bgr2->GetHistogram()->SetTitleOffset(7,"X");
 
 wgr2->GetHistogram()->GetYaxis()->SetNdivisions(6);
 mgr2->GetHistogram()->GetYaxis()->SetNdivisions(6);
 pgr2->GetHistogram()->GetYaxis()->SetNdivisions(6);
 tgr2->GetHistogram()->GetYaxis()->SetNdivisions(6);
 bgr2->GetHistogram()->GetYaxis()->SetNdivisions(6);
 
 wgr2->GetHistogram()->GetXaxis()->SetNdivisions(6);
 mgr2->GetHistogram()->GetXaxis()->SetNdivisions(6);
 pgr2->GetHistogram()->GetXaxis()->SetNdivisions(6);
 tgr2->GetHistogram()->GetXaxis()->SetNdivisions(6);
 bgr2->GetHistogram()->GetXaxis()->SetNdivisions(6);
 
 wgr2->GetHistogram()->GetXaxis()->SetTitleColor(4);
 mgr2->GetHistogram()->GetXaxis()->SetTitleColor(9);
 pgr2->GetHistogram()->GetXaxis()->SetTitleColor(6);
 tgr2->GetHistogram()->GetXaxis()->SetTitleColor(8);
 bgr2->GetHistogram()->GetXaxis()->SetTitleColor(45);

 
 

  
 
 wgr1->SetMinimum(0.91);
 wgr1->SetMaximum(1);
 wgr2->SetMinimum(0.015);
 wgr2->SetMaximum(0.045);

 mgr1->SetMaximum(0.0004);
 mgr1->SetMinimum(-0.0004);
 mgr2->SetMaximum(0.0006);
 mgr2->SetMinimum(0);

 pgr1->SetMinimum(178);
 pgr1->SetMaximum(182);
 pgr2->SetMinimum(8);
 pgr2->SetMaximum(12);


 tgr1->SetMinimum(-0.003);
 tgr1->SetMaximum(0.003);
 tgr2->SetMinimum(0.00);
 tgr2->SetMaximum(0.004);

 bgr1->SetMinimum(-0.001);
 bgr1->SetMaximum(0.003);
 bgr2->SetMinimum(0.001);
 bgr2->SetMaximum(0.006);

 P->cd(1);  wgr1->Draw("P"); lw->Draw("same");
 P->cd(2);  wgr2->Draw("P");
 P->cd(3);  mgr1->Draw("P"); lm->Draw("same");
 P->cd(4);  mgr2->Draw("P");
 P->cd(5);  pgr1->Draw("P"); lp->Draw("same");
 P->cd(6);  pgr2->Draw("P");
 P->cd(7);  tgr1->Draw("P"); lt->Draw("same");
 P->cd(8);  tgr2->Draw("P");
 P->cd(9);  bgr1->Draw("P"); lb->Draw("same");
 P->cd(10); bgr2->Draw("P");

 if(PRINTOPT==1) G->Print("means.gif");

 cout << " Saving paramenters into file elastic_par.txt..." << endl;
 ofstream OUT("elastic_par.txt",ios::out);
 for(int s=0; s<6; s++)
 {
  OUT << Wmin[s]    << " " << Wmax[s]    << " ";
  OUT << mmmin[s]   << " " << mmmax[s]   << " ";
  OUT << dphmin[s]  << " " << dphmax[s]  << " ";
  OUT << dthmin[s]  << " " << dthmax[s]  << " ";
  OUT << dthbmin[s] << " " << dthbmax[s] << " ";
  OUT << endl;
 }
 OUT.close();
}
