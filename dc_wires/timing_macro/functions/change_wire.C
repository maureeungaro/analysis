void change_sec1()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 sector_w1->cd(); 
 SECT_1 = (int) ((sector_s1->GetMinimum() + 0.025 )* 6) + 1; 
 sprintf(tit,"    SECTOR\n          %d",SECT_1); 
 sector_w1->Clear(); 
 SECTOR->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}

void change_sec2()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 sector_w2->cd(); 
 SECT_2 = (int) ((sector_s2->GetMinimum() + 0.025 )* 6) + 1; 
 sprintf(tit,"    SECTOR\n         %d",SECT_2); 
 sector_w2->Clear(); 
 SECTOR->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}

void change_layer1()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 layer_w1->cd(); 
 LAYER_1 = (int) ((layer_s1->GetMinimum() + 0.025 )* 36) + 1; 
 sprintf(tit,"    LAYER\n         %d",LAYER_1); 
 layer_w1->Clear(); 
 Layer->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}

void change_layer2()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 layer_w2->cd(); 
 LAYER_2 = (int) ((layer_s2->GetMinimum() + 0.025 )* 36) + 1; 
 sprintf(tit,"    LAYER\n         %d",LAYER_2); 
 layer_w2->Clear(); 
 Layer->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}

void change_wire1()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 wire_w1->cd(); 
 WIRE_1 = (int) ((wire_s1->GetMinimum() + 0.005 )* 197) + 1; 
 sprintf(tit,"      WIRE\n         %d",WIRE_1); 
 wire_w1->Clear(); 
 Wire->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}

void change_wire2()
{ 
 wireS->SetEditable(1); 
 char tit[100]; 
 wire_w2->cd(); 
 WIRE_2 = (int) ((wire_s2->GetMinimum() + 0.005 )* 197) + 1; 
 sprintf(tit,"      WIRE\n         %d",WIRE_2); 
 wire_w2->Clear();
 Wire->DrawLatex(0.05,0.4,tit); 
 wireS->SetEditable(0);
}



































