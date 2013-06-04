#!/bin/bash

function run_test {
    TEST_N=$1
    TEST_DT=$2
    TEST_SCHEME=$3

    EX_N=30
    EX_DT=0.005
    EX_SCHEME=im

    OUT_DIR="results_${TEST_N}_${TEST_DT}_${TEST_SCHEME}"
    CMD="./fem-dt-stokes-test --test-mesh-size=${TEST_N} --test-delta-time=${TEST_DT} --test-scheme=${TEST_SCHEME} --ex-mesh-size=${EX_N} --ex-delta-time=${EX_DT} --ex-scheme=${EX_SCHEME} --output-dir=${OUT_DIR}"
    echo $CMD
    mkdir -p ${OUT_DIR}
    $CMD > ${OUT_DIR}/log.txt
}

run_test 20 0.01 im
run_test 20 0.01 cn
./make-graphics.sh
rm temp_table
