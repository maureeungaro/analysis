# Vertex Correction and Selection


## Cuts

- delta time vs momentum


## Re-run vertex_corr_sel to apply cuts and create histograms:

Single file example:

```
./vertex_corr_sel \
/Volumes/e16/e_pid/30540.mu \
-BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/vertex/vertex_par.txt
```


## Run analysis:

### Interactive:

`root vertex.C`

### Batch and print all plots:

`root -b -q vertex.C\(1\)`



## Create new mauriPlots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files
onto mauriPlots repo. It will also reset the git repo to the last commit if the reset
option is used:

`./update_mauriPlots.zsh reset`

Notice that the script will also copy the data from the cloud.

<br/><br/>
