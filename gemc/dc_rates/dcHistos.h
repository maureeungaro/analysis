#ifndef DCHISTOS_HEADER
#define DCHISTOS_HEADER 1



class dcHistos {

public:
	dcHistos(const string rootFilePath,
			 const vector<string> confs,
			 const vector<string> regs,
			 const vector<string> zones,
			 int recalc = 0);



private:
	double zlimits[2][2][4];  // r,z  --  min,max  --  zone

	int defineHistos();
	int setHisto

	
};



#endif
