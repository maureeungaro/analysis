source /group/clas/builds/PRODUCTION/packages/tcl/recsis_proc.tcl;
#
# define packages
turnoff ALL;
global_section off;
turnon seb trk cc tof egn lac user pid;
#
# additional trigger:
# set trigger_particle_s 2212;
#
#
inputfile            gpp.bos;
setc chist_filename  gpp.hst;
setc log_file_name   gpp.log;
#
#level of analysis 0: raw  2: hbt 4: tbt
#set trk_level 4;
#set trk_maxiter 6;
#
set dc_xvst_choice     0;
set torus_current      3375;
set mini_torus_current 6000;
set poltarget_current  0;
set TargetPos(3)       -4.;
#
#setc outbanknames(1) "HEADPARTEVNT";
#setc outbanknames(1) "TRGSHEADEC  SC  DC0 CC  ECPIECHBPARTTBIDHEVTEVNTDCPBCCPBSCPBECPBCALLTBERTGBITRKSTBTRSCR SCRCECPCCL01LCPBBMPRTDPL";
setc outbanknames(1) "TRGSHEADEC  SC  DC0 CC  PARTTBIDHEVTEVNTDCPBCCPBSCPBECPBCALLTBERTGBITRKSTBTRCL01BMPRTDPL";
outputfile recsis PROC1 2047;
#
setc prlink_file_name "prlink_e16_tg4.bos" ; #for target at zero (-4cm)
setc bfield_file_name "bgrid_T67to33.fpk"
#
set lseb_nt_do  -1;
set lall_nt_do  -1;
set lscr_nt_do  -1;
#set lmctk_nt_do -1;
set lseb_hist   -1;
set lseb_h_do   -1;
set lmon_hist   -1;
set ltrk_h_do   -1;
set legn_h_do   -1;
set ltof_h_do   -1;
set lec1_h_do   -1;
set lfec_hist   -1;
set lfec_h_do   -1;
set lpart_nt_do -1;
#set lmysql      -1;
#set nmysql      -1;
#
# tell FPACK not to stop if it thinks you are running out of time
fpack "timestop -9999999999"
# do not send events to event display
set lscat $false;
set ldisplay_all $false;
setc rec_prompt "e16MC_recsis> ";
go 20000;
exit_pend;
