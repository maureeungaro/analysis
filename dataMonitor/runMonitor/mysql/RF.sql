use g11_offline ;
select  time, runno, meanRFalltag, sigmaRFalltag, meanRFprot, sigmaRFprot, meanRFpip, sigmaRFpip, meanRFpim, sigmaRFpim, meanSTpip, sigmaSTpip, meanSTpim, sigmaSTpim from pass1 order by - time;
