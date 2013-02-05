#!/bin/sh
ID=`date +%s`
for NX in 20 30 40 50 60
do
    for SCHEME in cn dr implicit lb pr
    do
        for DT in 0.01 0.001 0.0001
        do
          echo ./fem-dt-stokes-test -n $NX -d $DT -s $SCHEME -o results_${NX}_${DT}_${SCHEME}
        #       echo $NX $SCHEME $DT
        done
    done
done
