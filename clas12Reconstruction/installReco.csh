#!/bin/csh -f


# install clara with CLAS software version 4a.0.0
# check https://claraweb.jlab.org/clara/docs/clas/installation.html for info
mkdir reco
cd reco
setenv CLARA_HOME /opt/projects/reco/clara-home
mkdir clara_install
cd clara_install
wget --no-check-certificate https://claraweb.jlab.org/clara/_downloads/install-claracre-clas.sh
chmod +x install-claracre-clas.sh
./install-claracre-clas.sh

# install coatjava (not strictly necessary because it also comes with the Clara installation)
# check http://clasweb.jlab.org/clas12offline/docs/software/3.0/html/ for info
cd ..
wget --no-check-certificate http://clasweb.jlab.org/clas12offline/distribution/coatjava/coatjava-4a.0.0.tar.gz
tar xvfz coatjava-4a.0.0.tar.gz


# to change LTCC jar, replace the jar /opt/projects/reco/clara-home/plugins/clas12/lib/services
# quello che lancia e' in /opt/projects/reco/clara-home/plugins/clas12/config/services.yaml
# golden run: 795 (outbending) - 805 (inbending) bassa luminosita'
#
# $COATJAVA/bin/notsouseful-util -i clas12_000795_a00001.hipo -o clas12_000795_a00001.hipo.out -c 2
#
# -c 2 < standard services
# $COATJAVA/bin/notsouseful-util -i test.hipo -o rec.hipo org.jlab.rec.ft.cal.FTCALEngine org.jlab.rec.ft.hodo.FTHODOEngine org.jlab.rec.ft.FTEBEngine
#
# bank defs:
# $COATJAVA/etc/bankdefs/hipo

# Raffa kpp plots:
# $COATJAVA/bin/kpp-plots


# https://github.com/gavalian/groot


# in netbeans:
# -DCLAS12DIR=/opt/projects/reco/clara-home/plugins/clas12
#
# raffa plots
# https://github.com/raffaelladevita/KPP-Plots
