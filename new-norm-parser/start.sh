#!/bin/bash

function run_test {
    TEST_N=$1
    TEST_DT=$2
    TEST_SCHEME=$3

    EX_N=200
    EX_DT=0.00125
    EX_SCHEME=im

    OUT_DIR="results_${TEST_N}_${TEST_DT}_${TEST_SCHEME}"
    CMD="./fem-dt-stokes-test --test-mesh-size=${TEST_N} --test-delta-time=${TEST_DT} --test-scheme=${TEST_SCHEME} --ex-mesh-size=${EX_N} --ex-delta-time=${EX_DT} --ex-scheme=${EX_SCHEME} --output-dir=${OUT_DIR}"
    echo $CMD
    mkdir -p ${OUT_DIR}
    $CMD > ${OUT_DIR}/log.txt
}

for NX in 20 40 80 160
do
    for SCHEME in cn dr im lb pr vr
    do
        for DT in 0.01 0.005 0.0025
        do
        	run_test ${NX} ${DT} ${SCHEME}
        done
    done
done

