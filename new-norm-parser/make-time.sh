#!/bin/sh

for NX in 20 40 80 160
do
  for SCHEME in cn dr im lb pr vr
  do
    for DT in 0.01 0.005 0.0025
    do
      OUT_DIR="results_${NX}_${DT}_${SCHEME}"
      echo ${OUT_DIR}
      cat ${OUT_DIR}/log.txt | grep 'timer test' | head -n 1 | awk '{print $6}'
    done
  done
done

cat table_time | sed 'N;s/\n/\t/g'

#!/bin/bash

for DT in 0.01 0.005 0.0025
do
  for SCHEME in cn dr im lb pr vr
  do
#	for NX in 20 40 80 160
#    do
      #OUT_DIR="results_${NX}_${DT}"
	  echo ${SCHEME}_${DT}
	  cat table_time2 | grep _${DT} | grep _${SCHEME}  | awk '{print $2}'
#    done
  done
done

cat table_time3 | column -c 300 