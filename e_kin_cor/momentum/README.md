# Momentum Correction 



## Re-run e_mom_corr to apply cut and create histograms:

Single file example:

```
./e_mom_corr \
/Volumes/e16/p_fidxy/30540.mu \
-BEAM_E=5.7542 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/e_kin_cor/momentum/emom_corr_pars.txt
```


## Run analysis:

### Interactive:

`root mom_corr.C`

### Batch and print all plots:

`root -b -q mom_corr.C\(1\)`



## Create new mauriPlots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files
onto mauriPlots repo. It will also reset the git repo to the last commit if the reset
option is used:

`./update_mauriPlots.zsh reset`

Notice that the script will also copy the data from the cloud.

<br/><br/>
