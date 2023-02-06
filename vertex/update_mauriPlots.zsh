#!/bin/zsh

mdir=/opt/projects/mauriplots/vertex

export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH

scons -c
scons
root -b -q vertex.C\(1\)
scons -c


# updating mauriPlots repository


mv *.png $mdir


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

