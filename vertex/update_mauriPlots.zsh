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

mdir=/opt/projects/mauriplots/vertex

export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH

scons -c
scons
root -b -q vertex.C\(1\)
scons -c


# updating mauriPlots repository
mv *.png $mdir


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
