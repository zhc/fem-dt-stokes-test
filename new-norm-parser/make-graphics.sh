#!/bin/bash
COLUMN_WIDTH=600
MAX_T=20


DIRS=`ls | grep results`
echo $'===Found dirs===\n'"${DIRS}"

T1=''
for OUT_DIR in $DIRS
do
	T1+=`echo ${OUT_DIR}`$'\n'
	T1+=`cat ${OUT_DIR}/log.txt | grep unorm`$'\n'
done
echo $'===Found unorms===\n'"${T1}"

T2=`echo "$T1" | sed 's/unorm=\([0-9.]*\) at i=[0-9]*/\1/g'`
echo $'===Filtered values of unorms===\n'"${T2}"

T4=$'t\n'
for i in `seq 1 ${MAX_T}`
do
	T4+=${i}$'\n'
done
T2="${T4}${T2}"
echo $'===Appended t==='
echo "${T2}"

T3=`echo "${T2}"	| column -c ${COLUMN_WIDTH}`
echo $'===Made columns from unorms===\n'"${T3}"

echo "${T3}" > temp_table
gnuplot make-plot-2.plt
