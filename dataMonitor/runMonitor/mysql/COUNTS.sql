use g11_offline ;
select  time, runno, Nhb, Ntb, Nprot, NPROC from pass1 order by - time;
