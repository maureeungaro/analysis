// MU includes
#include "common_info.h"
#include "bin.h"

// C++ includes
#include <fstream>
#include <cstdlib>
#include <cmath>

double ana_chistos::value_rebin(double data1, double data2, double acc1, double acc2)
{
	double cy1, cy2, cy; // corrected yields in both bins, total bin

	// if all bins have zero acceptance or no data return zero
	if(acc1 == 0  && acc2 == 0)  return 0;
	if(data1 == 0 && data2 == 0) return 0;
	
	// if all bins have non-zero acceptance
	if(acc1*acc2 > 0)
	{
		// if all data bins are full
		if(data1*data2>0)
		{
			cy1 = data1/acc1;
			cy2 = data2/acc2;
			cy  = cy1 + cy2;
		}
		// if one (or both) data bin are zero:
		// 1. calculate the average acceptance
		// 2. divide the non-zero bin by that acceptance
		// 3. multiply the result by two
		else
		{
			double acc = (acc1+acc2)/2.0;
			cy = 2*(data1 + data2)/acc;
		}
	}

	// if only one bin has zero acceptance
	// the other will account for the total acceptance
	if(acc1*acc2 == 0)
	{
		double acc = (acc1+acc2);
		
		// if all data bins are full
		if(data1*data2>0)
		{
			cy1 = data1/acc;
			cy2 = data2/acc;
			cy  = cy1 + cy2;
		}
		// if one (or both) data bin are zero:
		// 1. divide the non-zero bin by the above acceptance
		// 2. multiply the result by two
		else
		{
			cy = 2*(data1 + data2)/acc;
		}
	}

	return cy;
}

// sums corrected yields in two bins if they're both full
// otherwise multiply the non zero bin by two
// (we're assuming neighbors bins are almost the same)
double ana_chistos::value_srebin(double data1, double data2)
{
	
	if(data1 == 0 && data2 == 0) return 0;
	
	if(data1*data2>0)
	{
		return data1 + data2;
	}
	// if one (or both) data bin are zero:
	// multiply the one bin result by two
	else
	{
		return 2*(data1 + data2);
	}
	

	return 0;
}

// error on sums of corrected yields
double ana_chistos::error_srebin(double edata1, double edata2)
{
	
	if(edata1 == 0 && edata2 == 0) return 0;
	
	if(edata1*edata2>0)
	{
		return sqrt(edata1*edata1 + edata2*edata2);
	}
	// if one (or both) data bin are zero:
	// multiply the one bin result by two
	else
	{
		return 2*(edata1 + edata2);
	}

	return 0;
}

double ana_chistos::error_rebin(double data1, double data2, double edata1, double edata2, double acc1, double acc2, double eacc1, double eacc2)
{
	// if all bins have zero acceptance or no data return zero
	if(acc1 == 0  && acc2 == 0)  return 0;
	if(data1 == 0 && data2 == 0) return 0;

	double ecy1, ecy2, ecy; // corrected yields in both bins, total bin

// 	double value = value_rebin(data1, data2, acc1, acc2);
	
	// if all bins have non-zero acceptance
	if(acc1*acc2 > 0)
	{
		// if all data bins are full
		if(data1*data2>0)
		{
			ecy1 = error_quotient(data1, edata1, acc1, eacc1);
			ecy2 = error_quotient(data2, edata2, acc2, eacc2);
			ecy  = sqrt(ecy1*ecy1 + ecy2*ecy2);
		}
		// if one (or both) data bin are zero:
		// 1. calculate the average acceptance
		// 2. divide the non-zero bin by that acceptance
		// 3. multiply the result by two
		else
		{
			double data  = data1 + data2;
			double edata = data*sqrt((edata1/data1)*(edata1/data1) + (edata2/data2)*(edata2/data2));
			double acc  = (acc1+acc2)/2.0;
			double eacc = sqrt(acc1*acc1 + acc2*acc2)/2.0;
			ecy = 2*error_quotient(data, edata, acc, eacc);
		}
	}
	

	// if only one bin has zero acceptance
	// the other will account for the total acceptance
	if(acc1*acc2 == 0)
	{
		double acc = (acc1+acc2);
		double eacc = sqrt(acc1*acc1 + acc2*acc2)/2.0;
		
		// if all data bins are full
		if(data1*data2>0)
		{
			ecy1 = error_quotient(data1, edata1, acc, eacc);
			ecy2 = error_quotient(data2, edata2, acc, eacc);
			ecy  = sqrt(ecy1*ecy1 + ecy2*ecy2);
		}
		// if one (or both) data bin are zero:
		// 1. divide the non-zero bin by the above acceptance
		// 2. multiply the result by two
		else
		{
			double data  = data1 + data2;
			double edata = data*sqrt((edata1/data1)*(edata1/data1) + (edata2/data2)*(edata2/data2));
			ecy = 2*error_quotient(data, edata, acc, eacc);
		}
	}

	return ecy;

	
}

double ana_chistos::error_quotient(double nomi, double enomi, double deno, double edeno)
{
	if(deno==0) return 0;
	
	double value = nomi/deno;

	double err = value*sqrt((enomi/nomi)*(enomi/nomi) + (edeno/deno)*(edeno/deno));

	return err;
	
}























