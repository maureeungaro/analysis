#!/bin/zsh

mdir=/opt/projects/mauriplots/ppid

export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH

scons -c
scons
root -b -q vertex.C\(1\)
scons -c


# updating mauriPlots repository

rm -rf $mdir/img/*
rm -rf $mdir/img_slices/*
mkdir -p $mdir/img $mdir/img_slices

mv img/*.png $mdir/img/
mv img_slices/*.png $mdir/img_slices/
mv cuts.html $mdir/
mv slices.html $mdir/

# reset history message
echo
echo Check the changes in the repository with:
echo
echo cd $mdir
echo gista
echo
echo if necessary, reset history:
echo
echo gitRemoveHistory
echo

