# Proton Identification

## Cuts

- delta time vs momentum


## Re-run e_pid to apply cut and create histograms:

Single file example:

```
./proton_pid \
/Volumes/e16/e_pid/30540.mu \
-BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/pid/proton/proton_id_par.txt
```


## Run analysis:

### Interactive:

`root p_pid.C`

### Batch and print all plots:

`root -b -q p_pid.C\(1\)`

## Create web pages based on the output of the analysis

``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=dist \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/dist-dtfit_sector-all.png -imagesSize="1200 1200"
mv page.html cuts.html
```

For the slices:

```
rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=sector \
-defaultPlot=img_slices/slice-2_sector-1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html
```



## Create new plots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files
onto mauriPlots repo. It will also reset the git repo to the last commit if the reset
option is used:

`./update_mauriPlots.zsh reset`

Notice that the script will also copy the data from the cloud.

<br/><br/>
