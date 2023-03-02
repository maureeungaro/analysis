# Electron Fiducial Cut


Notice the cuts can be on Phi vs Theta or on X vs Y of the track intersection with the planes.
The choice is made on line 60 of fiducial_cut.cc

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
                                        -addRowTableVariable=PnPvsTmom  \
                                        -addColumnTableVariable=sector \
                                        -addSelectableVariable=plot  \
                                        -defaultPlot=img/PnPvsTmom-2.4_sector-2_plot-phiVsTheta.png \
                                        -imagesSize="1200 1200"
mv page.html phi_theta.html
```

#### Phi vs Theta for all momenta, before and after
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=phiTheta  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/phiTheta-before_sector-1.png \
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
                                        -defaultPlot=img/plane-DC1_sector-1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_allmom.html
```

#### X vs Y of Track Intersection with Planes - instegrated momenta
``` 
rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=plane  \
                                        -addColumnTableVariable=intsector \
                                        -defaultPlot=img/plane-DC1_intsector-1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_intmom.html
```

#### For the slices:

```
rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=sector \
                                        -addSelectableVariable=plane \
-defaultPlot=img_slices/slice-03_sector-1_plane-DC1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html
```


## Create new plots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files
onto mauriPlots repo. It will also reset the git repo to the last commit if the reset
option is used.
