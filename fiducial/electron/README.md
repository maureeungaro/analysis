# Electron Fiducial Cut

## Cuts

-


## Re-run e_fid to apply cuts and create histograms:

Single file example:

```
./e_fiducial \
/Volumes/e16/vertex/30540.mu \
-BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/fiducial/electron/fiducial_par.txt
```


## Run analysis:

### Interactive:

`root e_pid.C`

### Batch and print all plots:

`root -b -q e_fid.C\(1\)`

## Create web pages based on the output of the analysis

``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=cut  \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/01-tmc_sector-1.png -imagesSize="1200 1200"
mv page.html cuts.html
```

For the slices:

```
rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=cut \
                                        -addSelectableVariable=sector \
-defaultPlot=img_slices/slice-01_tmc-slice_sector-1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html
```


## Create new plots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files 
onto mauriPlots repo. It will also reset the git repo to the last commit.

