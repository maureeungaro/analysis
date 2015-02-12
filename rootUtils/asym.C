// Return histo with correct error.
// Here, hAsym = (h1 - h2)/(h1 + h2).

TH1F* Asym_error(TH1F* h1, TH1F *h2)
{
	double error;
	TH1F *hAsym = new TH1F("hAsym", "hAsym", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
	
	for (int i=1;i<h1->GetNbinsX()+1; i++)
	{
		double value1 = h1->GetBinContent(i);
		double value2 = h2->GetBinContent(i);
		double error1 = h1->GetBinError(i);
		double error2 = h2->GetBinError(i);
		if((value1+value2) == 0)
			error = 0;
		else
			error  = 2 * sqrt( pow(value2, 2)*pow(error1, 2) + pow(value1, 2)*pow(error2, 2) )/pow(value1+value2, 2);
		
		hAsym->SetBinContent(i, (value1 - value2)/(value1 + value2));
		hAsym->SetBinError(i, error);
	}
	
	return hAsym;
}


TH1D* Asym_error(TH1D* h1, TH1D *h2)
{
	double error;
	TH1D *hAsym = new TH1D("hAsym", "hAsym", h1->GetNbinsX(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
	
	for (int i=1;i<h1->GetNbinsX()+1; i++)
	{
		double value1 = h1->GetBinContent(i);
		double value2 = h2->GetBinContent(i);
		double error1 = h1->GetBinError(i);
		double error2 = h2->GetBinError(i);
		if((value1+value2) == 0)
			error = 0;
		else
			error  = 2 * sqrt( pow(value2, 2)*pow(error1, 2) + pow(value1, 2)*pow(error2, 2) )/pow(value1+value2, 2);
		
		hAsym->SetBinContent(i, (value1 - value2)/(value1 + value2));
		hAsym->SetBinError(i, error);
	}
	
	return hAsym;
}





