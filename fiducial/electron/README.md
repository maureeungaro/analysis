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

#### Phi and Phi vs Theta - variable momentum
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=mom  \
                                        -addColumnTableVariable=sector \
                                        -addSelectableVariable=plot  \
                                        -defaultPlot=img/mom-03_sector-2_plot-phiVsTheta.png \
                                        -imagesSize="1200 1200"
mv page.html phi_theta.html
```

#### Phi vs Theta for all momenta, before and after
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=phiTheta  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/phiTheta-before_sector1.png \
                                        -imagesSize="1200 1200"
mv page.html phi_theta_ba.html
```

#### X vs Y of Track Intersection with Planes - variable momentum
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=XvsYmom  \
                                        -addColumnTableVariable=sector  \
                                        -addSelectableVariable=plane  \
                                        -defaultPlot=img/XvsYmom-3.3_sector-1_plane-DC1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_mom.html
```

#### X vs Y of Track Intersection with Planes - all momenta
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=plane  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/sector-1_plane-DC1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_allmom.html
```

#### X vs Y of Track Intersection with Planes - instegrated momenta
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addColumnTableVariable=intsector \
                                        -addRowTableVariable=plane  \
                                        -defaultPlot=img/intsector-1_plane-DC1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_intmom.html
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

