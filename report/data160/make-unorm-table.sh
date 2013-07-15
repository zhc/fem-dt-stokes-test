#!/bin/bash

for NX in 20 40 80 160
do
  for SCHEME in cn dr im lb pr
  do
    for DT in 0.01 0.005 0.0025
    do
      OUT_DIR="results_${NX}_${DT}_${SCHEME}"
      echo ${OUT_DIR}
      cat ${OUT_DIR}/log.txt | grep unorm
    done
  done
done

