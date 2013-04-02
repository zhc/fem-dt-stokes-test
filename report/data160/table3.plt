#set term postscript eps color
set term png size 1024, 768
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

set multiplot layout 1,3
plot for [i=2:6] 'table_time4' using 1:i w l;
plot for [i=7:11] 'table_time4' using 1:i w l;
plot for [i=12:16] 'table_time4' using 1:i w l;
unset multiplot

pause -1
