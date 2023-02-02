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

```
./e_pid \
/Volumes/e16/fullRuns/30540.mu \
-BEAM_E=5.754 -TARGET=proton  -OUTPUT=30540.mu -ROOT_OUTPUT=30540.root \
-PARS_FILE=/opt/projects/analysis/pid/electron/electron_id_par.txt
```


## Run analysis:

### Interactive:

`root e_pid.C`

### Batch and print all plots:

`root -b -q e_pid.C\(1\)`

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


## Create new plots

The script `update_mauriPlots.zsh` will compile the code, run it in batch
to produce the plots, create the web pages and move the images and html files 
onto mauriPlots repo. It will also reset the git repo to the last commit.

#### Documentation on the git reset:

`git checkout --orphan new-main`: create a temporary branch

`git add -A`:  Add all files and commit them

`git commit -m 'new files'`

`git branch -D main`: Deletes the master branch

`git branch -m main`: Rename the current branch to main

`git push -f origin main`: Force push main branch to Git server

