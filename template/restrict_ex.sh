#!/bin/bash
input="submit.sh"
num=0
restrict=200
totaln=0
while IFS= read -r line
do
  $line
  totaln=$(( $totaln + 1 ))
  num=`condor_q yihuilai |wc -l`
  num=$(( $num - 7  ))
  while [ $num -gt $restrict ]
  do
    echo "Current job: $num, too much, wait..."
    num=`condor_q yihuilai |wc -l`
    num=$(( $num - 7  ))
    echo "current ====> $totaln"
    sleep 300
  done
done < "$input"

