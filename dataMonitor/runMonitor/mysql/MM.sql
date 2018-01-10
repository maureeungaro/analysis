use g11_offline ;
select  time, runno, mm_p_pip, smm_p_pip, mm_pip_pim, smm_pip_pim, mm_kp_lambda, smm_kp_lambda, mm_kp_sigma, smm_kp_sigma from pass1 order by - time;
