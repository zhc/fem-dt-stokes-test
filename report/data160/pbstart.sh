#!/bin/bash

for NX in 20 40 80 160
do
    for SCHEME in cn dr im lb pr
    do
        for DT in 0.01 0.005 0.0025
        do
	    qsub -l nodes=1:ppn=1 -v NX=${NX},SCHEME=${SCHEME},DT=${DT} fem-dt-stokes-test.pbs
        done
    done
done

