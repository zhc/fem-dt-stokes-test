#!/bin/bash

for DT in 0.01 0.005 0.0025
do
  for SCHEME in cn dr im lb pr
  do
#	for NX in 20 40 80 160
#    do
      #OUT_DIR="results_${NX}_${DT}"
	  echo ${SCHEME}_${DT}
	  cat table_time2 | grep _${DT} | grep _${SCHEME}  | awk '{print $2}'
#    done
  done
done
