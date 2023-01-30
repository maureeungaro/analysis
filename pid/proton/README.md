# Proton Identification

## Cuts

- cut-01: delta time vs momentum


## Re-run e_pid to apply cut and create histograms:

Single file example:

```
./proton_pid \
/Volumes/e16/e_pid/30540.mu \
-BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/pid/proton/proton_id_par.txt
```


## Run analysis:

`root p_pid.C`


## Create web pages based on the output of the analysis

``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=cut  \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/cut-01-cc-theta-match_sector-1.png -imagesSize="1200 1200"
mv page.html cuts.html
```

For the slices:

```
rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=cut \
                                        -addSelectableVariable=sector \
-defaultPlot=img_slices/slice-01_cut-01-cc-theta-slice_sector-1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html
```
