import org.jlab.clas.physics.GenericKinematicFitter;
import org.jlab.clas.physics.Particle;
import org.jlab.clas.physics.PhysicsEvent;
import org.jlab.clas.physics.RecEvent;
import org.jlab.groot.data.H1F;
import org.jlab.groot.data.H2F;
import org.jlab.groot.math.F1D;
import org.jlab.groot.fitter.DataFitter;
import org.jlab.groot.fitter.ParallelSliceFitter;
import org.jlab.groot.data.GraphErrors;
import org.jlab.groot.ui.TCanvas;
import org.jlab.groot.graphics.EmbeddedCanvas;
import org.jlab.io.base.DataBank;
import org.jlab.io.base.DataEvent;
import org.jlab.io.hipo.*;
import org.jlab.io.evio.*;
import org.jlab.clas.physics.Vector3;
import org.jlab.clas.detector.DetectorResponse;
import org.jlab.clas.detector.DetectorParticle;
import org.jlab.detector.base.DetectorType;
import org.jlab.service.ec.*;
import org.jlab.geom.prim.Vector3D;


// useful parameters
double[] ftofThickness = [5,6,5];
int[] nPaddles = [23, 62, 5];
ftofThickness[0]=5;
ftofThickness[1]=6;
ftofThickness[2]=5;

double[] len1a = [32.3, 48.1, 64.01, 79.8, 95.7, 106.6, 122.4, 138.3, 154.1, 170.01, 185.8, 201.7,
217.6, 233.4, 249.3, 265.1, 281.01, 296.8, 312.7, 328.5, 344.4, 360.2, 376.1];

double[] len1b = [17.27, 23.62, 30.08, 36.43, 42.89, 49.24, 55.70, 62.05, 68.51, 74.86, 81.32,
87.67, 94.13, 100.48, 106.94, 113.29, 119.75, 126.10, 132.56, 138.91, 145.37, 151.72, 158.17, 164.52,
170.98, 177.33, 183.79, 190.14, 196.60, 202.95, 209.41, 215.76, 222.22, 228.57, 235.03, 241.38, 247.84,
254.19, 260.65, 267.00, 273.46, 279.81, 286.27, 292.62, 299.08, 305.43, 311.88, 318.23, 324.69, 331.04,
337.50, 343.85, 350.31, 356.66, 363.12, 369.47, 375.93, 382.28, 388.74, 395.09, 401.55, 407.90];

double tdcconv= 23.45/1000.0;
double zoom = 1;

// histograms
H1F hi_gen_p        = new H1F("hi_gen_p",        "hi_gen_p",      100, 0, 10);                   hi_gen_p.setOptStat(1111);        hi_gen_p.setTitleX("P (GeV)");          hi_gen_p.setTitleY("Counts");
H2F hi_gen_ptheta   = new H2F("hi_gen_ptheta",   "hi_gen_ptheta", 100, 0, 50, 100, 0, 10);       hi_gen_ptheta.setTitleX("#theta (deg)"); hi_gen_ptheta.setTitleY("P (GeV)");
H2F hi_gen_thetaphi = new H2F("hi_gen_thetaphi", "hi_gen_thetaphi", 100, -180, 180, 100, 0, 50); hi_gen_thetaphi.setTitleX("#phi (deg)"); hi_gen_thetaphi.setTitleY("#theta (deg)");
H1F hi_rec_p        = new H1F("hi_rec_p",        "hi_rec_p",      100, 0, 10);                   hi_rec_p.setOptStat(1111);        hi_rec_p.setTitleX("P (GeV)");          hi_rec_p.setTitleY("Counts");
H2F hi_rec_ptheta   = new H2F("hi_rec_ptheta",   "hi_rec_ptheta", 100, 0, 50, 100, 0, 10);       hi_rec_ptheta.setTitleX("#theta (deg)"); hi_rec_ptheta.setTitleY("P (GeV)");
H2F hi_rec_thetaphi = new H2F("hi_rec_thetaphi", "hi_rec_thetaphi", 100, -180, 180, 100, 0, 50); hi_rec_thetaphi.setTitleX("#phi (deg)"); hi_rec_thetaphi.setTitleY("#theta (deg)");
// tracking
H1F hi_dp_EL     = new H1F("hi_dp_EL",     "hi_dp_EL", 100, -0.8, 0.8);     hi_dp_EL.setOptStat(1111);     hi_dp_EL.setTitleX("#DeltaP (GeV)");
H1F hi_dtheta_EL = new H1F("hi_dtheta_EL", "hi_dtheta_EL", 100, -4.0, 4.0); hi_dtheta_EL.setOptStat(1111); hi_dtheta_EL.setTitleX("#Delta#theta (deg)");
H1F hi_dphi_EL   = new H1F("hi_dphi_EL",   "hi_dphi_EL", 100, -8.0, 8.0);   hi_dphi_EL.setOptStat(1111);   hi_dphi_EL.setTitleX("#Delta#phi (deg)");
H1F hi_vz_EL     = new H1F("hi_vz_EL",     "hi_vz_EL", 100, -20.0, 20.0);   hi_vz_EL.setOptStat(1111);     hi_vz_EL.setTitleX("Vz (cm)");
H1F hi_dp_HB     = new H1F("hi_dp_HB",     "hi_dp_HB", 100, -0.8, 0.8);     hi_dp_HB.setOptStat(1111);     hi_dp_HB.setTitleX("#DeltaP (GeV)");
H1F hi_dtheta_HB = new H1F("hi_dtheta_HB", "hi_dtheta_HB", 100, -4.0, 4.0); hi_dtheta_HB.setOptStat(1111); hi_dtheta_HB.setTitleX("#Delta#theta (deg)");
H1F hi_dphi_HB   = new H1F("hi_dphi_HB",   "hi_dphi_HB", 100, -8.0, 8.0);   hi_dphi_HB.setOptStat(1111);   hi_dphi_HB.setTitleX("#Delta#phi (deg)");
H1F hi_vz_HB     = new H1F("hi_vz_HB",     "hi_vz_HB", 100, -20.0, 20.0);   hi_vz_HB.setOptStat(1111);     hi_vz_HB.setTitleX("Vz (cm)");

// FTOF
H1F hi_ftof_energy_PA = new H1F("hi_ftof_energy_PA", "hi_ftof_energy_PA", 100, 0.0, 30.0); hi_ftof_energy_PA.setOptStat(1111); hi_ftof_energy_PA.setTitleX("Edep (MeV)");
H1F hi_ftof_energy_PB = new H1F("hi_ftof_energy_PB", "hi_ftof_energy_PA", 100, 0.0, 30.0); hi_ftof_energy_PB.setOptStat(1111); hi_ftof_energy_PB.setTitleX("Edep (MeV)");
H1F hi_ftof_energy_PA_MIPS = new H1F("hi_ftof_energy_PA_MIPS", "hi_ftof_energy_PA_MIPS", 100, 0.0, 30.0); hi_ftof_energy_PA_MIPS.setOptStat(1111); hi_ftof_energy_PA_MIPS.setTitleX("Edep (MeV)"); hi_ftof_energy_PA_MIPS.setLineColor(2);
H1F hi_ftof_energy_PB_MIPS = new H1F("hi_ftof_energy_PB_MIPS", "hi_ftof_energy_PA_MIPS", 100, 0.0, 30.0); hi_ftof_energy_PB_MIPS.setOptStat(1111); hi_ftof_energy_PB_MIPS.setTitleX("Edep (MeV)"); hi_ftof_energy_PB_MIPS.setLineColor(2);
H1F hi_elec_t0 = new H1F("hi_elec_t0", "hi_elec_t0", 150, -2.0, 2.0);
hi_elec_t0.setOptStat(1111);
hi_elec_t0.setTitleX("#DeltaT (ns)");
hi_elec_t0.setTitleY("Counts");
H2F hi_elec_t0_adcl = new H2F("hi_elec_t0_adcl", "hi_elec_t0_adcl",50, 200,3000, 100, -2.0, 2.0);
hi_elec_t0_adcl.setTitleX("ADCL");
hi_elec_t0_adcl.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_adcr = new H2F("hi_elec_t0_adcr", "hi_elec_t0_adcr",50, 200,3000, 100, -2.0, 2.0);
hi_elec_t0_adcr.setTitleX("ADCR");
hi_elec_t0_adcr.setTitleY("#DeltaT (ns)");

H2F hi_elec_t0_tdcl = new H2F("hi_elec_t0_tdcl", "hi_elec_t0_tdcl",50, 24500,27500, 100, -2.0, 2.0);
hi_elec_t0_tdcl.setTitleX("TDCL");
hi_elec_t0_tdcl.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_tdcr = new H2F("hi_elec_t0_tdcr", "hi_elec_t0_tdcr",50, 24500,27500, 100, -2.0, 2.0);
hi_elec_t0_tdcr.setTitleX("TDCR");
hi_elec_t0_tdcr.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_p = new H2F("hi_elec_t0_p", "hi_elec_t0_p",50, 0.5,5, 100, -2.0, 2.0);
hi_elec_t0_p.setTitleX("p (GeV)");
hi_elec_t0_p.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_path = new H2F("hi_elec_t0_path", "hi_elec_t0_path",50, 6.88,6.98, 100, -2.0, 2.0);
hi_elec_t0_path.setTitleX("path (m)");
hi_elec_t0_path.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_pos = new H2F("hi_elec_t0_pos", "hi_elec_t0_pos",50, -0.6,0.6, 100, -2.0, 2.0);
hi_elec_t0_pos.setTitleX("hit position (m)");
hi_elec_t0_pos.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_rf = new H2F("hi_elec_t0_rf", "hi_elec_t0_rf",50, 0,2.004, 100, -2.0, 2.0);
hi_elec_t0_rf.setTitleX("rf (ns)");
hi_elec_t0_rf.setTitleY("#DeltaT (ns)");
H2F hi_elec_t0_vz = new H2F("hi_elec_t0_vz", "hi_elec_t0_vz",50,0,10, 100, -2.0, 2.0);
hi_elec_t0_vz.setTitleX("vz (cm)");
hi_elec_t0_vz.setTitleY("#DeltaT (ns)");
H1F hi_rf_t0 = new H1F("hi_rf_t0", "hi_rf_t0", 200, -3.0, 3.0); hi_rf_t0.setOptStat(1111);       hi_rf_t0.setTitleX("#DeltaT (ns)"); hi_rf_t0.setTitleY("Counts");

H2F hi_twl = new H2F("hi_twl", "hi_twl", 30, 500, 3000, 80, -2.0, 2.0); hi_twl.setTitleX("ADC"); hi_twl.setTitleY("#DeltaT(ns)");
H2F hi_twr = new H2F("hi_twr", "hi_twr", 30, 500, 3000, 80, -2.0, 2.0); hi_twr.setTitleX("ADC"); hi_twr.setTitleY("#DeltaT(ns)");
H2F hi_rsl = new H2F("hi_rsl", "hi_rsl", 30, 500, 3000, 80,-20.0,20.0); hi_rsl.setTitleX("ADC"); hi_rsl.setTitleY("#DeltaL(cm)");
H2F hi_rsr = new H2F("hi_rsr", "hi_rsr", 30, 500, 3000, 80,-20.0,20.0); hi_rsr.setTitleX("ADC"); hi_rsr.setTitleY("#DeltaL(cm)");
H2F hi_rxl = new H2F("hi_rxl", "hi_rxl", 30, 500, 3000, 80,-20.0,20.0); hi_rxl.setTitleX("ADC"); hi_rxl.setTitleY("#DeltaX(cm)");
H2F hi_rxr = new H2F("hi_rxr", "hi_rxr", 30, 500, 3000, 80,-20.0,20.0); hi_rxr.setTitleX("ADC"); hi_rxr.setTitleY("#DeltaX(cm)");
H2F hi_rxx = new H2F("hi_rxx", "hi_rxx", 50, -60,   60, 80,-20.0,20.0); hi_rxx.setTitleX("X(cm)"); hi_rxx.setTitleY("#DeltaX(cm)");
H2F hi_ryl = new H2F("hi_ryl", "hi_ryl", 30, 500, 3000, 80,-20.0,20.0); hi_ryl.setTitleX("ADC"); hi_ryl.setTitleY("#DeltaY(cm)");
H2F hi_ryr = new H2F("hi_ryr", "hi_ryr", 30, 500, 3000, 80,-20.0,20.0); hi_ryr.setTitleX("ADC"); hi_ryr.setTitleY("#DeltaY(cm)");
H2F hi_ryx = new H2F("hi_ryx", "hi_ryx", 50, -60,   60, 80,-190.0,-150.0); hi_ryx.setTitleX("X(cm)"); hi_ryx.setTitleY("Y(cm)");
H2F hi_rzl = new H2F("hi_rzl", "hi_rzl", 30, 500, 3000, 80,-20.0,20.0); hi_rzl.setTitleX("ADC"); hi_rzl.setTitleY("#DeltaZ(cm)");
H2F hi_rzr = new H2F("hi_rzr", "hi_rzr", 30, 500, 3000, 80,-20.0,20.0); hi_rzr.setTitleX("ADC"); hi_rzr.setTitleY("#DeltaZ(cm)");
H2F hi_rzx = new H2F("hi_rzx", "hi_rzx", 50, -60,   60, 80,-20.0,20.0); hi_rzx.setTitleX("X(cm)"); hi_rzx.setTitleY("#DeltaZ(cm)");
H2F hi_txl = new H2F("hi_txl", "hi_txl", 30, 500, 3000, 80,-100.0,100.0); hi_txl.setTitleX("ADC"); hi_txl.setTitleY("X (cm)");
H2F hi_txr = new H2F("hi_txr", "hi_txr", 30, 500, 3000, 80,-100.0,100.0); hi_txr.setTitleX("ADC"); hi_txr.setTitleY("X (cm)");
H2F hi_tyl = new H2F("hi_tyl", "hi_tyl", 30, 500, 3000, 80,-190.0,-150.0); hi_tyl.setTitleX("ADC"); hi_tyl.setTitleY("Y (cm)");
H2F hi_tyr = new H2F("hi_tyr", "hi_tyr", 30, 500, 3000, 80,-190.0,-150.0); hi_tyr.setTitleX("ADC"); hi_tyr.setTitleY("Y (cm)");
H2F hi_tzl = new H2F("hi_tzl", "hi_tzl", 30, 500, 3000, 80, 660.0,680.0); hi_tzl.setTitleX("ADC"); hi_tzl.setTitleY("Z (cm)");
H2F hi_tzr = new H2F("hi_tzr", "hi_tzr", 30, 500, 3000, 80, 660.0,680.0); hi_tzr.setTitleX("ADC"); hi_tzr.setTitleY("Z (cm)");

H2F hi_tdc = new H2F("hi_tdc", "hi_tdc", 100, 0, 50000, 65, 0, 65); hi_tdc.setTitleX("tdc"); hi_tdc.setTitleY("paddle");
H2F hi_tdc_2 = new H2F("hi_tdc_2", "hi_tdc_2", 100, 0, 50000, 65, 0, 65); hi_tdc_2.setTitleX("tdc"); hi_tdc_2.setTitleY("paddle");
H2F hi_occ = new H2F("hi_occ", "hi_occ", 65, 0, 65, 6, 1, 7.0); hi_occ.setTitleX("paddle"); hi_occ.setTitleY("sector");
H2F hi_occ_2 = new H2F("hi_occ_2", "hi_occ_2", 65, 0, 65, 6, 1, 7.0); hi_occ_2.setTitleX("paddle"); hi_occ_2.setTitleY("sector");
H2F hi_mult = new H2F("hi_mult", "hi_mult", 65, 0, 65, 6, 1, 7.0); hi_mult.setTitleX("paddle"); hi_mult.setTitleY("sector");
H2F hi_mult_2 = new H2F("hi_mult_2", "hi_mult_2", 65, 0, 65, 6, 1, 7.0); hi_mult_2.setTitleX("paddle"); hi_mult_2.setTitleY("sector");

HipoDataSource reader = new HipoDataSource();
//reader.open("/Users/devita/big.804-808.pass4.1.hipo");
//reader.open("/Users/devita/big.804-808.newdec.filteredbanksfilteredtracks.hipo");
//reader.open("/Users/devita/big.809.0-99.pass4.filteredbanksfilteredtracks.hipo");
//reader.open("/Users/devita/r804_810_1track_pass4.negativetracksfilteredbanks.hipo");
reader.open("/Users/devita/big.804-810.pass5.filteredbanksfilteredtracks.hipo");

int nevent = -1;
int nmultitrk=0;
while(reader.hasEvent() == true && nevent<40000000)
{
   DataEvent event = reader.getNextEvent();
   nevent++;
   if(nevent%10000 == 0) System.out.println("Analyzed " + nevent + " events" + " " + nmultitrk);
//   event.show();


   Particle partGen = null;
   Particle electronGen = null;
   Particle electronRec = null;
   Particle pionRec = null;
   Particle partRecHB = null;

   // loop over generated particles
   DataBank genBank = event.getBank("MC::Particle");
   if(genBank!=null) {
      int nrows = genBank.rows();
      for(int loop = 0; loop < nrows; loop++) {   
          Particle genPart = new Particle(
                                          genBank.getInt("pid", loop),
                                          genBank.getFloat("px", loop),
                                          genBank.getFloat("py", loop),
                                          genBank.getFloat("pz", loop),
                                          genBank.getFloat("vx", loop),
                                          genBank.getFloat("vy", loop),
                                          genBank.getFloat("vz", loop));
	  if(genPart.pid()==11) {
             if(partGen == null) {
	        partGen = genPart;
		electronGen = genPart;
		hi_gen_p.fill(partGen.p());
	        hi_gen_ptheta.fill(Math.toDegrees(partGen.theta()),partGen.p());
       	        hi_gen_thetaphi.fill(Math.toDegrees(partGen.phi()),Math.toDegrees(partGen.theta()));
	     }
	  }
       }
   }
   
   double t0 = 124.25;
   // loop over Ftof reconstructed hits
   // get FTOFRec and Tracking banks
   DataBank recFTOF = event.getBank("FTOF::hits");
   DataBank recHBTR = event.getBank("TimeBasedTrkg::TBTracks");
   DataBank recEB   = event.getBank("REC::Particle");
   DataBank recRF   = event.getBank("RUN::rf");
   DataBank ftofADC = event.getBank("FTOF::adc");
   DataBank ftofTDC = event.getBank("FTOF::tdc");
   if(ftofTDC!=null && false) {
       // check tdc ranges
      for(int i=0; i<ftofTDC.rows(); i++) {
          if(ftofTDC.getByte("sector", i)==2 && ftofTDC.getByte("layer", i)==2 ) {
	     hi_tdc.fill(ftofTDC.getInt("TDC", i),ftofTDC.getShort("component", i));
	  }
      }
   }
   if(recFTOF!=null && recHBTR!=null) {
      double trf= 0;
      if(recRF.rows()>0) {
         for(int i=0; i<recRF.rows(); i++) {
	     if(recRF.getInt("id",i)==1) trf =recRF.getFloat("time",i);
	 }
      }
      hi_rf_t0.fill((trf+100*2.004-t0)%2.004);
      int nrows = recFTOF.rows();
      int ntrks = recHBTR.rows();
      if(ntrks>1) nmultitrk++;
      // first find the electron to get the startime
      double startTime  = 0;
      for(int loop = 0; loop < nrows; loop++){
          int sector    = recFTOF.getByte("sector", loop);
          int panel     = recFTOF.getByte("layer", loop);
          int trk_id    = recFTOF.getShort("trackid", loop);
          int paddle    = recFTOF.getShort("component", loop);
          double energy = recFTOF.getFloat("energy", loop);
   	  double time   = recFTOF.getFloat("time", loop);
   	  double x      = recFTOF.getFloat("x", loop);
   	  double y      = recFTOF.getFloat("y", loop);
          double z      = recFTOF.getFloat("z", loop);
   	  double tx     = recFTOF.getFloat("tx", loop);
   	  double ty     = recFTOF.getFloat("ty", loop);
          double tz     = recFTOF.getFloat("tz", loop);
	  int adcId1    = recFTOF.getShort("adc_idx1", loop);
	  int adcId2    = recFTOF.getShort("adc_idx2", loop);
	  int tdcId1    = recFTOF.getShort("tdc_idx1", loop);
	  int tdcId2    = recFTOF.getShort("tdc_idx2", loop);
	  double adc1 = (double) ftofADC.getInt("ADC",adcId1);
	  double adc2 = (double) ftofADC.getInt("ADC",adcId2);
	  double adct1 = (double) ftofADC.getFloat("time",adcId1);
	  double adct2 = (double) ftofADC.getFloat("time",adcId2);
	  double tdc1 = (double) ftofTDC.getInt("TDC",tdcId1);
	  double tdc2 = (double) ftofTDC.getInt("TDC",tdcId2);
	  if(trk_id!=-1) {
	     hi_tdc_2.fill(tdc1,paddle);
	     hi_tdc_2.fill(tdc2,paddle);
	  }
          Vector3D hit = new Vector3D(x,y,z);
	  Vector3D trk = new Vector3D(tx,ty,tz);
	  double angle = Math.toRadians(90-60*(sector-1));
	  hit.rotateZ(angle);
	  trk.rotateZ(angle);
	  angle = Math.toRadians(25);
	  hit.rotateX(angle);
	  trk.rotateX(angle);
	  Vector3D delta = new Vector3D(hit);
	  delta.sub(trk);
	  Vector3D trkZoom = new Vector3D(trk.x()*zoom,trk.y(),trk.z());
	  int[] mult = [0,0,0,0];
/*	  for(int i=0; i<ftofADC.rows(); i++) {
	      if(sector==ftofADC.getByte("sector", i) && panel==ftofADC.getByte("layer", i) && paddle==ftofADC.getShort("component", i)) {
	         int index = (int) ftofADC.getByte("order", i);
	         mult[index]++;
	      }
	  }
	  for(int i=0; i<ftofTDC.rows(); i++) {
	      if(sector==ftofTDC.getByte("sector", i) && panel==ftofTDC.getByte("layer", i) && paddle==ftofTDC.getShort("component", i)) {
	         int index = (int) ftofTDC.getByte("order", i);
	         if((ftofTDC.getInt("TDC",i)>23000 && ftofTDC.getInt("TDC",i)<29000) || false) mult[index]++;
	      }
	  }*/
	  double nmult = /*mult[0]+mult[1]+*/mult[2]+mult[3];
//	  System.out.println(mult[0] + " " + mult[1] + " " + mult[2] + " " + mult[3]);
	  if(panel==2) {
	     if((tdc1>23000 && tdc1<29000 && tdc2>23000 && tdc2<29000) || false) {
	        hi_occ.fill(paddle*1.0,sector*1.0);
	        hi_mult.fill(paddle*1.0,sector*1.0,nmult);
	     }
	  }
          if(trk_id!=-1 && ntrks==1 && energy>0) {                             // select FTOF hits that were associated to a track and with reasonable energy deposition
	     double c3x  = recHBTR.getFloat("c3_x",trk_id-1);
	     double c3y  = recHBTR.getFloat("c3_y",trk_id-1);
	     double c3z  = recHBTR.getFloat("c3_z",trk_id-1);
             double path = recHBTR.getFloat("pathlength",trk_id-1) + Math.sqrt((tx-c3x)*(tx-c3x)+(ty-c3y)*(ty-c3y)+(tz-c3z)*(tz-c3z));
	     path = Math.sqrt(path*path-trk.x()*trk.x()+trkZoom.x()*trkZoom.x());
	     int    q    = recHBTR.getByte("q",trk_id-1);
	     double p0x  = recHBTR.getFloat("p0_x",trk_id-1);
	     double p0y  = recHBTR.getFloat("p0_y",trk_id-1);
             double p0z  = recHBTR.getFloat("p0_z",trk_id-1);
	     double vx   = recHBTR.getFloat("Vtx0_x",trk_id-1);
	     double vy   = recHBTR.getFloat("Vtx0_y",trk_id-1);
             double vz   = recHBTR.getFloat("Vtx0_z",trk_id-1);
             double chi2 = recHBTR.getFloat("chi2",trk_id-1)/recHBTR.getShort("ndf",trk_id-1);
	     Particle recParticle = new Particle(11,p0x,p0y,p0z,0,0,0);
	     int pid     = recEB.getInt("pid",0);
 	     if(q==-1 && pid!=11 && recParticle.p()>0 && panel==2 && Math.abs(vz)<15 /*&& chi2<70*/) {
                hi_occ_2.fill(paddle*1.0,sector*1.0);
    	        hi_mult_2.fill(paddle*1.0,sector*1.0,nmult);
		if(partRecHB==null) partRecHB=recParticle;
//		if(recParticle!= null && electronGen!=null) {
//      	        if(Math.abs(recParticle.p()-electronGen.p())<0.5
//	        && Math.abs(Math.toDegrees(recParticle.theta()-electronGen.theta()))<2.0
//	        && Math.abs(Math.toDegrees(recParticle.phi()-electronGen.phi()))<8) {	// select negative tracks matching the generated electron as electron candidates
//	    	   if(electronRec==null) {
		      electronRec = recParticle;
		      hi_rec_p.fill(electronRec.p());
         	      hi_rec_ptheta.fill(Math.toDegrees(electronRec.theta()),electronRec.p());
         	      hi_rec_thetaphi.fill(Math.toDegrees(electronRec.phi()),Math.toDegrees(electronRec.theta()));
		      double beta = electronRec.p()/Math.sqrt(electronRec.p()*electronRec.p()+0.1396*0.1396);
		      if(paddle==15 && sector==2  /* && Math.abs(delta.z()+0.0001)>0.0001 && mult[2]==1 && mult[3]==1 && Math.sqrt(adc1*adc2)>1000*/) {
		         double plength = len1b[paddle-1]/2.0;
			 double veff = 14.582*zoom; 
			 double RFPad = -0.288;
			 double paddle2paddle = 14.028;
			 double timeOffset = -0.479;
			 double tw11 = 45.109;
			 double tw12 = 0.486;
			 double tw21 = 48.605;
			 double tw22 = 0.480;
			 if(paddle==8) {
			    veff = 13.925;
			    timeOffset = -1.169;
			    RFPad = -0.137;
			    tw11 = 47.181;
			    tw12 = 0.477;
			    tw21 = 45.854;
			    tw22 = 0.473;
			 }
			 double tw1=tw11/Math.pow(adc1,tw12);
			 double tw2=tw21/Math.pow(adc2,tw22);
//			 tw1 = 40/Math.pow(adc1,0.5);
//			 tw2 = 40/Math.pow(adc2,0.5);
		         double t1 = tdcconv * tdc1-(plength-trkZoom.x())/veff-/*tw1*/40/Math.pow(adc1,0.5) - timeOffset / 2.0 + paddle2paddle + RFPad;
		         double t2 = tdcconv * tdc2-(plength+trkZoom.x())/veff-/*tw2*/40/Math.pow(adc2,0.5) + timeOffset / 2.0 + paddle2paddle + RFPad;
			 double time1 = tdcconv * tdc1 - tw1 - timeOffset / 2.0 + paddle2paddle + RFPad;
			 double time2 = tdcconv * tdc2 - tw2 + timeOffset / 2.0 + paddle2paddle + RFPad;
//			 System.out.println(tdcconv + " " + veff + " " + timeOffset + " " + paddle2paddle + " " + RFPad);
			 double myTime = (time1 + time2)/2.0 - plength/veff;
			 myTime = time;
			 double myX    = (time2 - time1)/2.0 * veff;
		         hi_twl.fill(adc1,(t1-path/(beta*29.97)-trf+120.5*2.004) % 2.004 -1.002);
		         hi_twr.fill(adc2,(t2-path/(beta*29.97)-trf+120.5*2.004) % 2.004 -1.002);
		         hi_rsl.fill(adc1,delta.mag());
		         hi_rsr.fill(adc2,delta.mag());
		         hi_rxl.fill(adc1,myX-trkZoom.x());
		         hi_rxr.fill(adc2,myX-trkZoom.x());
		         hi_rxx.fill(trkZoom.x(),myX-trkZoom.x());
		         hi_ryl.fill(adc1,delta.y());
		         hi_ryr.fill(adc2,delta.y());
		         hi_ryx.fill(trkZoom.x(),trkZoom.y());
		         hi_rzl.fill(adc1,delta.z());
		         hi_rzr.fill(adc2,delta.z());
		         hi_rzx.fill(trkZoom.x(),delta.z());
		         hi_txl.fill(adc1,trkZoom.x());
		         hi_txr.fill(adc2,trkZoom.x());
		         hi_tyl.fill(adc1,trkZoom.y());
		         hi_tyr.fill(adc2,trkZoom.y());
		         hi_tzl.fill(adc1,trkZoom.z());
		         hi_tzr.fill(adc2,trkZoom.z());
//			 System.out.println(delta.z());
			 if((mult[2]>1 || mult[3]>1)) {
		            System.out.println(adc1 + " " + adc2 + " " + adct1 + " " + adct2 + " " + tdc1 + " " + tdc2);
			    ftofTDC.show();
			 }
			 startTime  = myTime-(path)/(beta*29.97);
			 double dt = (startTime-trf+120.5*2.004)%2.004-1.002;
//			 dt = (trf - startTime +1000.5*2.004)%2.004-1.002;
			 if(adc1>1200 && adc2>1200 && Math.abs(trk.x())<10) {
			 hi_elec_t0.fill(dt);
       		         hi_elec_t0_adcl.fill(adc1,dt);
       		         hi_elec_t0_adcr.fill(adc2,dt);
       		         hi_elec_t0_tdcl.fill(ftofTDC.getInt("TDC",tdcId1),dt);
       		         hi_elec_t0_tdcr.fill(ftofTDC.getInt("TDC",tdcId2),dt);
       		         hi_elec_t0_p.fill(electronRec.p(),dt);
       		         hi_elec_t0_path.fill(path/100,dt);
       		         hi_elec_t0_pos.fill(trkZoom.x()/100,dt);
       		         hi_elec_t0_rf.fill((trf+100*2.004)%2.004,dt);
       		         hi_elec_t0_vz.fill(vz,dt);
			 }
		      }
		   }
//	     }}
	 }
      }
   }

   if(electronGen != null && partRecHB != null) {
      hi_dp_HB.fill(partRecHB.p()-electronGen.p());
      hi_dtheta_HB.fill(Math.toDegrees(partRecHB.theta()-electronGen.theta()));
      hi_dphi_HB.fill(Math.toDegrees(partRecHB.phi()-electronGen.phi()));
      hi_vz_HB.fill(partRecHB.vz());
   }
   if(electronGen != null && electronRec != null) {
      hi_dp_EL.fill(electronRec.p()-electronGen.p());
      hi_dtheta_EL.fill(Math.toDegrees(electronRec.theta()-electronGen.theta()));
      hi_dphi_EL.fill(Math.toDegrees(electronRec.phi()-electronGen.phi()));
      hi_vz_EL.fill(electronRec.vz());
   }
}



TCanvas can = new TCanvas("can", 1200, 700);
can.divide(3,2); 
can.getCanvas().setGridX(false); can.getCanvas().setGridY(false);
can.getCanvas().setAxisFontSize(18);
can.getCanvas().setAxisTitleSize(24);
can.cd(0);
can.draw(hi_gen_p);
can.cd(1);
can.draw(hi_gen_ptheta);
can.cd(2);
can.draw(hi_gen_thetaphi);
can.cd(3);
can.draw(hi_rec_p);
can.cd(4);
can.draw(hi_rec_ptheta);
can.cd(5);
can.draw(hi_rec_thetaphi);

TCanvas occ = new TCanvas("occ", 800, 800);
occ.divide(2,2);
occ.getCanvas().setGridX(false); occ.getCanvas().setGridY(false);
occ.getCanvas().setAxisFontSize(18);
occ.getCanvas().setAxisTitleSize(24);
occ.cd(0);
occ.draw(hi_occ);
occ.cd(1);
for(int loop = 0; loop < hi_occ.getDataBufferSize(); loop++) {
    int nent=hi_occ.getDataBufferBin(loop);
    if(nent>0) {
       float nmult=hi_mult.getDataBufferBin(loop)*1.0/nent/2.0;
       hi_mult.setDataBufferBin(loop,nmult);
    }
}
occ.draw(hi_mult);
occ.cd(2);
occ.draw(hi_occ_2);
occ.cd(3)
for(int loop = 0; loop < hi_occ_2.getDataBufferSize(); loop++) {
    int nent=hi_occ_2.getDataBufferBin(loop);
    if(nent>0) {
       float mult=hi_mult_2.getDataBufferBin(loop)*1.0/nent/2.0;
       hi_mult_2.setDataBufferBin(loop,mult);
    }
}
occ.draw(hi_mult_2);

TCanvas tdc = new TCanvas("tdc", 800, 800);
tdc.divide(1,2);
tdc.getCanvas().setGridX(false); tdc.getCanvas().setGridY(false);
tdc.getCanvas().setAxisFontSize(18);
tdc.getCanvas().setAxisTitleSize(24);
tdc.cd(0);
tdc.draw(hi_tdc);
tdc.cd(1);
tdc.draw(hi_tdc_2);

TCanvas resolution = new TCanvas("resolution", 1400, 800);
resolution.divide(4, 2);
resolution.getCanvas().setGridX(false); resolution.getCanvas().setGridY(false);
resolution.getCanvas().setAxisFontSize(18);
resolution.getCanvas().setAxisTitleSize(24);
resolution.cd(0);
resolution.draw(hi_dp_HB);
resolution.cd(1);
resolution.draw(hi_dtheta_HB);
resolution.cd(2);
resolution.draw(hi_dphi_HB);
resolution.cd(3);
resolution.draw(hi_vz_HB);
resolution.cd(4);
resolution.draw(hi_dp_EL);
resolution.cd(5);
resolution.draw(hi_dtheta_EL);
resolution.cd(6);
resolution.draw(hi_dphi_EL);
resolution.cd(7);
resolution.draw(hi_vz_EL);

TCanvas ftof = new TCanvas("ftof", 1600, 1000);
ftof.divide(3, 2);
ftof.getCanvas().setGridX(false); ftof.getCanvas().setGridY(false);
ftof.getCanvas().setAxisFontSize(18);
ftof.getCanvas().setAxisTitleSize(24);
ftof.cd(0);
F1D ftw=new F1D("ftw","50*pow(x,-0.5)",500, 3000);
ftw.setLineWidth(3);
ftw.setLineColor(2)
ftof.draw(hi_twl);
//ftof.draw(ftw,"same");
ParallelSliceFitter fitterL = new ParallelSliceFitter(hi_twl);
fitterL.setBackgroundOrder(0);
fitterL.fitSlicesX();
GraphErrors meanL = fitterL.getMeanSlices();
ftof.cd(1);
ftof.draw(meanL);
F1D twLeftFunc = new F1D("twLeftFunc", "(([a]/(x^[b]))-(40.0/(x^0.5))+[d])", 500,3000);
twLeftFunc.setParameter(0, 40.0);
twLeftFunc.setParameter(1, 0.5);
twLeftFunc.setParLimits(1, 0.45, 0.55);
twLeftFunc.setLineColor(2)
DataFitter.fit(twLeftFunc,meanL,"Q");
ftof.draw(twLeftFunc,"sameS");
twLeftFunc.setOptStat("111111");
ftof.getCanvas().getPad(1).getAxisY().setRange(-1.0, 1.0);
ftof.cd(2);
ftof.draw(hi_rsl);
ftof.cd(3);
ftof.draw(hi_twr);
ParallelSliceFitter fitterR = new ParallelSliceFitter(hi_twr);
fitterR.setBackgroundOrder(0);
fitterR.fitSlicesX();
GraphErrors meanR = fitterR.getMeanSlices();
ftof.cd(4);
ftof.draw(meanR);
F1D twRightFunc = new F1D("twRightFunc", "(([a]/(x^[b]))-(40.0/(x^0.5))+[d])", 500,3000);
twRightFunc.setParameter(0, 40.0);
twRightFunc.setParameter(1, 0.5);
twRightFunc.setParLimits(1, 0.40, 0.55);
twRightFunc.setLineColor(2)
DataFitter.fit(twRightFunc,meanR,"Q");
ftof.draw(twRightFunc,"sameS");
twRightFunc.setOptStat("111111");
ftof.getCanvas().getPad(4).getAxisY().setRange(-1.0, 1.0);
ftof.cd(5);
ftof.draw(hi_rsr);

TCanvas res = new TCanvas("res", 1600, 1000);
res.divide(3, 3);
res.getCanvas().setGridX(false); res.getCanvas().setGridY(false);
res.getCanvas().setAxisFontSize(18);
res.getCanvas().setAxisTitleSize(24);
res.cd(0);
res.draw(hi_rxl);
res.cd(1);
res.draw(hi_ryl);
res.cd(2);
res.draw(hi_rzl);
res.cd(3);
res.draw(hi_rxr);
res.cd(4);
res.draw(hi_ryr);
res.cd(5);
res.draw(hi_rzr);
res.cd(6);
res.draw(hi_rxx);
res.cd(7);
res.draw(hi_ryx);
res.cd(8);
res.draw(hi_rzx);


TCanvas trk = new TCanvas("trk", 1600, 1000);
trk.divide(3, 2);
trk.getCanvas().setGridX(false); trk.getCanvas().setGridY(false);
trk.getCanvas().setAxisFontSize(18);
trk.getCanvas().setAxisTitleSize(24);
trk.cd(0);
trk.draw(hi_txl);
trk.cd(1);
trk.draw(hi_tyl);
trk.cd(2);
trk.draw(hi_tzl);
trk.cd(3);
trk.draw(hi_txr);
trk.cd(4);
trk.draw(hi_tyr);
trk.cd(5);
trk.draw(hi_tzr);

TCanvas vt = new TCanvas("vt", 1800, 1000);
vt.divide(3,2);
vt.getCanvas().setGridX(false); vt.getCanvas().setGridY(false);
vt.getCanvas().setAxisFontSize(18);
vt.getCanvas().setAxisTitleSize(24);
vt.cd(0);
F1D f1 = new F1D("f1","[amp]*gaus(x,[mean],[sigma])+[p0]", -1.0, 1.0);
f1.setParameter(0, 1000.0);
f1.setParameter(1, -0.0);
f1.setParameter(2, 0.1);
f1.setParameter(3, 0.0);
f1.setLineWidth(2);
f1.setLineColor(2)
f1.setOptStat("1111");
DataFitter.fit(f1,hi_elec_t0,"Q");
vt.cd(0);
vt.draw(hi_elec_t0);
vt.draw(f1,"same");
vt.cd(1);
vt.draw(hi_elec_t0_p);
vt.cd(2);
vt.draw(hi_elec_t0_vz);
vt.cd(3);
vt.draw(hi_elec_t0_pos);
vt.cd(4);
vt.draw(hi_elec_t0_path);
vt.cd(5);
vt.draw(hi_elec_t0_rf);

TCanvas vt_adc = new TCanvas("vt_adc", 1400, 1000);
vt_adc.divide(2,2);
vt_adc.getCanvas().setGridX(false); vt.getCanvas().setGridY(false);
vt_adc.getCanvas().setAxisFontSize(18);
vt_adc.getCanvas().setAxisTitleSize(24);
vt_adc.cd(0);
vt_adc.draw(hi_elec_t0_adcl);
vt_adc.cd(2);
vt_adc.draw(hi_elec_t0_adcr);
vt_adc.cd(1);
vt_adc.draw(hi_elec_t0_tdcl);
vt_adc.cd(3);
vt_adc.draw(hi_elec_t0_tdcr);
