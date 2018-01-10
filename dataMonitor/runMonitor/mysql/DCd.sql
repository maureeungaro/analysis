use g11_offline ;
select  time, runno, ResSL1S1_ave, ResSL1S2_ave, ResSL1S3_ave, ResSL1S4_ave, ResSL1S5_ave, ResSL1S6_ave,
                     ResSL1S1_sig, ResSL1S2_sig, ResSL1S3_sig, ResSL1S4_sig, ResSL1S5_sig, ResSL1S6_sig,
                     ResSL2S1_ave, ResSL2S2_ave, ResSL2S3_ave, ResSL2S4_ave, ResSL2S5_ave, ResSL2S6_ave,
                     ResSL2S1_sig, ResSL2S2_sig, ResSL2S3_sig, ResSL2S4_sig, ResSL2S5_sig, ResSL2S6_sig,
                     ResSL3S1_ave, ResSL3S2_ave, ResSL3S3_ave, ResSL3S4_ave, ResSL3S5_ave, ResSL3S6_ave,
                     ResSL3S1_sig, ResSL3S2_sig, ResSL3S3_sig, ResSL3S4_sig, ResSL3S5_sig, ResSL3S6_sig,
                     ResSL4S1_ave, ResSL4S2_ave, ResSL4S3_ave, ResSL4S4_ave, ResSL4S5_ave, ResSL4S6_ave,
                     ResSL4S1_sig, ResSL4S2_sig, ResSL4S3_sig, ResSL4S4_sig, ResSL4S5_sig, ResSL4S6_sig,
                     ResSL5S1_ave, ResSL5S2_ave, ResSL5S3_ave, ResSL5S4_ave, ResSL5S5_ave, ResSL5S6_ave,
                     ResSL5S1_sig, ResSL5S2_sig, ResSL5S3_sig, ResSL5S4_sig, ResSL5S5_sig, ResSL5S6_sig,
                     ResSL6S1_ave, ResSL6S2_ave, ResSL6S3_ave, ResSL6S4_ave, ResSL6S5_ave, ResSL6S6_ave,
                     ResSL6S1_sig, ResSL6S2_sig, ResSL6S3_sig, ResSL6S4_sig, ResSL6S5_sig, ResSL6S6_sig from pass1 order by - time;
