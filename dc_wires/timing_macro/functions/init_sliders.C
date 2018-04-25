void init_sliders()
{
 SECTOR.SetTextFont(44);
 SECTOR.SetTextSize(18);
 SECTOR.SetTextColor(4);
 SECTOR.SetNDC();
 
 Layer.SetTextFont(44);
 Layer.SetTextSize(18);
 Layer.SetTextColor(4);
 Layer.SetNDC();

 Wire.SetTextFont(44);
 Wire.SetTextSize(18);
 Wire.SetTextColor(4);
 Wire.SetNDC();


 sector_s1 = new TSlider("sector_s1","SECTOR",  0.02, 0.9, 0.8, 0.95);
 sector_s1->SetMethod("change_sec1()");
 sector_s1->SetMinimum(0.);
 sector_s1->SetRange(0.,0.05);
 sector_w1 = new TPad("sector_w1", "", 0.82, 0.86, 0.98, 0.99);
 sector_w1->SetFillColor(7);
 sector_w1->Draw();

 layer_s1 = new TSlider("layer_s1","LAYER",  0.02, 0.75, 0.8, 0.8);
 layer_s1->SetMethod("change_layer1()");
 layer_s1->SetMinimum(0.);
 layer_s1->SetRange(0.,0.05);
 layer_w1 = new TPad("layer_w1", "", 0.82, 0.71, 0.98, 0.84);
 layer_w1->SetFillColor(7);
 layer_w1->Draw();

 wire_s1 = new TSlider("wire_s1","WIRE",  0.02, 0.6, 0.8, 0.65);
 wire_s1->SetMethod("change_wire1()");
 wire_s1->SetMinimum(0.);
 wire_s1->SetRange(0.,0.03);
 wire_w1 = new TPad("wire_w1", "", 0.82, 0.56, 0.98, 0.69);
 wire_w1->SetFillColor(7);
 wire_w1->Draw();

 sector_s2 = new TSlider("sector_s2","SECTOR",  0.02, 0.4, 0.8, 0.45);
 sector_s2->SetMethod("change_sec2()");
 sector_s2->SetMinimum(0.);
 sector_s2->SetRange(0.,0.05);
 sector_w2 = new TPad("sector_w2", "", 0.82, 0.36, 0.98, 0.49);
 sector_w2->SetFillColor(41);
 sector_w2->Draw();

 layer_s2= new TSlider("layer_s2","LAYER",  0.02, 0.25, 0.8, 0.3);
 layer_s2->SetMethod("change_layer2()");
 layer_s2->SetMinimum(0.);
 layer_s2->SetRange(0.,0.05);
 layer_w2 = new TPad("layer_w2", "", 0.82, 0.21, 0.98, 0.34);
 layer_w2->SetFillColor(41);
 layer_w2->Draw();

 wire_s2 = new TSlider("wire_s2","WIRE",  0.02, 0.1, 0.8, 0.15);
 wire_s2->SetMethod("change_wire2()");
 wire_s2->SetMinimum(0.);
 wire_s2->SetRange(0.,0.03);
 wire_w2 = new TPad("wire_w2", "", 0.82, 0.06, 0.98, 0.19);
 wire_w2->SetFillColor(41);
 wire_w2->Draw();

}











