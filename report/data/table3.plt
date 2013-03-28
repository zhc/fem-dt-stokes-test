#set term postscript eps color
set term png size 1024, 768
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

#plot 'table' u 1:38 w l, \
#	 'table' u 1:39 w l, \
#	 'table' u 1:40 w l;

set multiplot layout 1,3
plot for [i=2:6] 'time_table_0.01' using 1:i w l;
plot for [i=2:6] 'time_table_0.005' using 1:i w l;
plot for [i=2:6] 'time_table_0.0025' using 1:i w l;
unset multiplot

pause -1
