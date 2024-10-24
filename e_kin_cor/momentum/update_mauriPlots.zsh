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

mdir=/opt/projects/mauriplots/e_kin_cor

# make sure $mdir is a git repository
if [[ ! -d $mdir/.git ]]; then
  echo
  echo "ERROR: $mdir is not a git repository."
  echo
  exit 2
fi

module load gemc/dev

scons -c
gia
scons
if [[ ! -f e_kin_cor.root ]]; then
  cp "/Users/ungaro/Library/Mobile Documents/com~apple~CloudDocs/data/ekin_corr.root"  .
fi
root -b -q mom_corr.C\(1\)
scons -c


# making the pages
rm -f *.html

rm -rf imageslist.txt ; ls img > imageslist.txt
../../../htmlBrowserCreator/pageCreator \
                                        -addRowTableVariable=dist  \
                                        -addColumnTableVariable=sector \
                                        -defaultPlot=img/dist-W_sector-1.png \
                                        -imagesSize="1200 1200"
mv page.html e_kin_cor.html




# updating mauriPlots repository
rm -rf $mdir/*
mkdir -p $mdir/img

mv img/*.png $mdir/img/
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
