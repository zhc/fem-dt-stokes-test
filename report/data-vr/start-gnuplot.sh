#!/bin/sh

for NX in 20 40 80 160
do
for DT in 0.01 0.005 0.0025
do
cat make-plot-unorm.plt | sed -e "s\temp_table\temp_table_${NX}_${DT}\g; s\unorm-two\unorm-${NX}-${DT}\g" | gnuplot
done
done
