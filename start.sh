#!/bin/bash
ID=`date +%s`

function run_test {
    NX=$1
    DT=$2
    SCHEME=$3
    RESULT_DIR="results_${NX}_${DT}_${SCHEME}"
    CMD="./fem-dt-stokes-test -n $NX -d $DT -s $SCHEME -o $RESULT_DIR"
    echo $CMD
    mkdir -p $RESULT_DIR
    $CMD > $RESULT_DIR/log.txt
}



for NX in 20 40 80
do
    for SCHEME in cn dr im lb pr
    do
        for DT in 0.01 0.001
        do
            run_test $NX $DT $SCHEME
        done
    done
done

run_test 80 0.0001 im
