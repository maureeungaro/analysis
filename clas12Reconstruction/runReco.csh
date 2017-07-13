#!/bin/csh -f

setenv CLARA_HOME /opt/projects/reco/clara-home
setenv COATJAVA /opt/projects/reco/clara-home/plugins/clas12

# convert evio file to hipo only for gemc
# $COATJAVA/bin/evio2hipo -r 11 -t -1 -s 1 -i ../gemc/out.ev -o out.hipo

# run reconstruction
mkdir -p /opt/projects/reco/data
mkdir -p /opt/projects/reco/output


\echo "out.hipo" >  /opt/projects/reco/file.list
# opzionale:
# cp /work/clas12/devita/gemc_gcards/4a.0.0/services.yaml $CLARA_HOME/plugins/clas12/config/
# -i = dir of input files
# -o = dir of output files
# -t = n. threads
# -m = local or farm
$CLARA_HOME/bin/run-clara -f file.list -i data -o output -t 15 -m local
\echo $COATJAVA
# the output file is out_out.hipo


# decoder:
# http://clasweb.jlab.org/clas12offline/docs/software/3.0/html/rec/inputfiles.html

# files in volatile:
/volatile/clas12/kpp/production/pass0/decoded


# dump:
# $COATJAVA/bin/eviodump filename
