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


## Apply cut and create histogram:



## Run analysis



## Create web page based on the output of the analysis

``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=cut  -addColumnTableVariable=sector -defaultPlot=img/cut-cctm_sector-1.png -imagesSize="1000 1000"
```