#!/bin/zsh

alias scons='ncpu=$(getconf _NPROCESSORS_ONLN); echo using $ncpu cores and OPT=1;  scons -j$ncpu OPT=1'

# if -h given print the reset option
if [[ $1 == "-h" ]]; then
  echo
  echo "Usage: update_mauriPlots.zsh [reset]"
  echo
  echo "If the option 'reset' is given, the history of the mauriPlot repository is reset."
  echo
  exit
fi

mdir=/opt/projects/mauriplots/epid

export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH

scons -c
ncpu=$(getconf _NPROCESSORS_ONLN)
echo using $ncpu cores and OPT=1
scons -j$ncpu OPT=1
root -b -q e_pid.C\(1\)
scons -c

# making the pages
rm -f *.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=cut  \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/cut-01-tm_sector-1.png -imagesSize="1200 1200"
mv page.html cuts.html

rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=cut \
                                        -addSelectableVariable=sector \
-defaultPlot=img_slices/slice-01_cut-01-ts_sector-1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html

# updating mauriPlots repository
rm -rf $mdir/*
mkdir -p $mdir/img $mdir/img_slices

mv img/*.png $mdir/img/
mv img_slices/*.png $mdir/img_slices/
mv cuts.html $mdir/
mv slices.html $mdir/

# if the option 'reset' is given to this script, run gitRemoveHistory
if [[ $1 == "reset" ]]; then
  cd $mdir
	git checkout --orphan new-main
	git add -A
	git commit -m 'new files'
	git branch -D main
	git branch -m main
	git push -f origin main
fi
