set term png size 1024, 768
set output 'unorm-two.png'
set key on autotitle columnheader
set yrange [0:0.1]
plot 'temp_table' using 1:2 w l, 'temp_table' using 1:3 w l;