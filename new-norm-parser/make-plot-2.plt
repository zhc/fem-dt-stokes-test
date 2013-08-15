set term png size 1024, 768
set output 'unorm-two.png'
set key on autotitle columnheader
set yrange [0:0.1]
plot for [i=7:14:1] 'temp_table' using 1:i w l
