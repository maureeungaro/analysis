use g11_offline ;
select  time, runno, xbeam, ybeam, sig_xbeam, sig_ybeam from pass1 order by - time;
