#!/bin/bash
cd ..
path=$(pwd)
cd ./template
#Particle="electron" 
#Particle="pion"
#pa="e-" 
#pa="pi-"
#tag=""
temp_name="template_ts.cfg"
ex_name="submit.sh"
echo "" > $ex_name
for Particle in pion electron
do
if [[ "$Particle" == "electron" ]]; then
  pa="e-"
else
  pa="pi-"
fi

for number in 500 # 100
do
#echo "the particle is $Particle ($pa), the number is $number /n"
for energy in 1 2 5 10 30 50 #1 2 5 10 20 30 40 50 60 70 80 90 100
do
for tag in $(seq 0 1 9)  #0 1 2 3 4 5 6 7 8 9 
do
  source temp_mac.sh $pa $energy $number > run_${energy}GeV_${Particle}_N${number}.mac
  source temp_jdl.sh $path ${Particle} $energy $number $tag > condor-jobs_${energy}GeV_${Particle}_N${number}_${tag}.jdl
  source temp_condor_sh.sh $path ${Particle} $energy $number $tag $temp_name > condor-executable_${energy}GeV_${Particle}_N${number}_${tag}.sh
  chmod 777 condor-executable_${energy}GeV_${Particle}_N${number}_${tag}.sh
  echo "condor_submit condor-jobs_${energy}GeV_${Particle}_N${number}_${tag}.jdl" >> $ex_name
done
done
done
done

cd ..
if [ ! -d "condor_output" ]; then
   mkdir condor_output
fi
cd ./template
