use g11_offline ;
select  time, runno, ResSL1_ave, ResSL2_ave, ResSL3_ave, ResSL4_ave, ResSL5_ave, ResSL6_ave,
                     ResSL1_sig, ResSL2_sig, ResSL3_sig, ResSL4_sig, ResSL5_sig, ResSL6_sig from pass1 order by - time;
