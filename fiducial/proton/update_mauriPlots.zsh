#!/bin/zsh -i


# if -h given print the reset option
if [[ $1 == "-h" ]]; then
  echo
  echo "Usage: update_mauriPlots.zsh [reset]"
  echo
  echo "If the option 'reset' is given, the history of the mauriPlot repository is reset."
  echo
  exit
fi

mdir=/opt/projects/mauriplots/pfid

module load gemc/dev

scons -c
gia
scons
if [[ ! -f data_pfid.root ]]; then
  cp "/Users/ungaro/Library/Mobile Documents/com~apple~CloudDocs/data/data_pfid.root"  .
fi
root -b -q p_fid.C\(1\)
scons -c


# making the pages
rm -f *.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=PnPvsTmom  \
                                        -addColumnTableVariable=sector \
                                        -addSelectableVariable=plot  \
                                        -defaultPlot=img/PnPvsTmom-2.4_sector-2_plot-phiVsTheta.png \
                                        -imagesSize="1200 1200"
mv page.html phi_theta.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=phiTheta  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/phiTheta-before_sector-1.png \
                                        -imagesSize="1200 1200"
mv page.html phi_theta_ba.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=XvsYmom  \
                                        -addColumnTableVariable=sector  \
                                        -addSelectableVariable=plane  \
                                        -defaultPlot=img/XvsYmom-3.3_sector-1_plane-DC1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_mom.html


rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=plane  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/plane-DC1_sector-1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_allmom.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=plane  \
                                        -addColumnTableVariable=intsector \
                                        -defaultPlot=img/plane-DC1_intsector-1.png \
                                        -imagesSize="1200 1200"
mv page.html xvsy_intmom.html

rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=sector \
                                        -addSelectableVariable=plane \
-defaultPlot=img_slices/slice-03_sector-1_plane-DC1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html




# updating mauriPlots repository
rm -rf $mdir/*
mkdir -p $mdir/img $mdir/img_slices

mv img/*.png $mdir/img/
mv img_slices/*.png $mdir/img_slices/
mv *.html $mdir/

# if the option 'reset' is given to this script, run gitRemoveHistory
if [[ $1 == "reset" ]]; then
  cd $mdir
	git checkout --orphan new-main
	git add -A
	git commit -m 'new files'
	git branch -D main
	git branch -m main
	git push -f origin main
	git branch --set-upstream-to=origin/main main
fi
