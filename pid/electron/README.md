# Electron Identification

## Cuts

- cut-01: theta match
- cut-02: phi match
- cut-03: time match
- cut-04: p threshold
- cut-05: sampling fraction
- cut-06,7,8: u,v,w
- cut-09: 2d uvw (not a cut)
- cut-10: EoVsEi
- cut-11: shshape
- cut-12: nphe (not a cut)


## Re-run e_pid to apply cut and create histograms:

Single file example:

`/opt/projects/analysis/pid/electron/e_pid   /Volumes/e1-6/pass4/fullRuns/30540.mu  -BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root -PARS_FILE=/opt/projects/analysis/pid/electron/electron_id_par.txt
`

All files:

`go_SEL /Volumes/e1-6/pass4/fullRuns    /Volumes/e1-6Proc/pass4/e_pid   /opt/projects/analysis/pid/electron/e_pid             /opt/projects/analysis/pid/electron/electron_id_par.txt
`
## Run analysis:

`root e_pid.C`


## Create web pages based on the output of the analysis

``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=cut  \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/cut-01-cc-theta-match_sector-1.png -imagesSize="1000 1000"
mv page.html cuts.html
```

For the slices:

```
rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=cut \
                                        -addSelectableVariable=sector \
-defaultPlot=img_slices/slice-01_cut-01-cc-theta-slice_sector-1.png \
-imagesSize="800 800" -d=img_slices
mv page.html slices.html
```
