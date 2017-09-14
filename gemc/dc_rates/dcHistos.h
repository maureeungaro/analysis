#ifndef DCHISTOS_HEADER
#define DCHISTOS_HEADER 1



class dcHistos {

public:
	dcHistos(vector<string> confs, int recalc = 0);



private:
	double zlimits[2][2][4];  // r,z  --  min,max  --  zone
	// region
	const int NREG = 3;
	vector<string> regs = {"reg1", "reg2", "reg3"};

	// vertex locations
	const int NZONES = 4;
	vector<string> zones = {"target", "beampipe", "torus", "all"};

	const int NSECT = 6;

	void setParticles();
	void defineHistos(string c);
	void initLeafs();
	void fillHistos(int index);
	void setDirHistos(int index);
	void writeHistos();


	// 2D occupancy histos: 2D for each sector, wire vs layer
	vector<TH2F *> dc_pro[NSECT][NCONF];
	vector<TH2F *> dc_occ[NSECT][NCONF];

	// 1D summary occupancy histo for the 3 regions
	TH1F *dc_occ_summary[3][NENERGY][NCONF];

	
};



#endif
