#!/bin/zsh

mdir=/opt/projects/mauriplots/ppid

export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH

scons -c
scons
root -b -q p_pid.C\(1\)
scons -c

# making the pages
rm -f *.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=dist \
                                        -addColumnTableVariable=sector \
-defaultPlot=img/dist-dtfit_sector-all.png -imagesSize="1200 1200"
mv page.html cuts.html

rm -rf imageslist.txt ; ls img_slices > imageslist.txt
../../../htmlBrowserCreator/pageCreator -addRowTableVariable=slice \
                                        -addColumnTableVariable=sector \
-defaultPlot=img_slices/slice-2_sector-1.png \
-imagesSize="1200 1200" -d=img_slices
mv page.html slices.html

# updating mauriPlots repository

rm -rf $mdir/img/*
rm -rf $mdir/img_slices/*
mkdir -p $mdir/img $mdir/img_slices

mv img/*.png $mdir/img/
mv img_slices/*.png $mdir/img_slices/
mv cuts.html $mdir/
mv slices.html $mdir/

## resetting repository to latest content
cd $mdir
git checkout --orphan new-main
git add -A
git commit -m 'new files'
git branch -D main
git branch -m main
git push -f origin main

