#!/bin/bash

cd /data/users/yihuilai/cepc_layer

START_TIME=`/bin/date`
echo "started at $START_TIME"


# setup software environment at UMD
#
source /cvmfs/sft.cern.ch/lcg/contrib/gcc/6.3/x86_64-slc6/setup.sh
source /cvmfs/geant4.cern.ch/geant4/10.5/x86_64-slc6-gcc63-opt-MT/CMake-setup.sh
export CXX=`which g++`
export CC=`which gcc`
export PATH=$PATH:/cvmfs/sft.cern.ch/lcg/contrib/CMake/3.11.1/Linux-x86_64/bin
source /cvmfs/sft.cern.ch/lcg/views/LCG_95/x86_64-slc6-gcc62-opt/setup.sh
source $ROOTSYS/bin/thisroot.sh
#export LIBRARY_PATH=/data/users/yihuilai/dualReadout/fakelib:$LIBRARY_PATH
#export LD_LIBRARY_PATH=/data/users/yihuilai/dualReadout/fakelib:$LD_LIBRARY_PATH
export LIBRARY_PATH=/home/eno/dualReadout/fakelib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/home/eno/dualReadout/fakelib:$LD_LIBRARY_PATH
echo $LIBRARY_path
echo $LD_LIBRARY_PATH

#
# run 
#


 ./CEPC_CaloTiming -c template_ts.cfg -m run_30GeV_electron_N500.mac -o electron_30GeV_N500_4 > run_30GeV_electron_N500_4.log

exitcode=$?


#
# end run
#

echo ""
END_TIME=`/bin/date`
echo "finished at $END_TIME"
exit $exitcode


