#set term postscript eps color
set term png size 1600, 2000
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

set yrange [0:0.1]

#plot 'table' u 1:38 w l, \
#	 'table' u 1:39 w l, \
#	 'table' u 1:40 w l;

set multiplot layout 5,3
plot for [i=2:45:15] 'table' using 1:i w l;
plot for [i=3:45:15] 'table' using 1:i w l;
plot for [i=4:45:15] 'table' using 1:i w l;
plot for [i=5:45:15] 'table' using 1:i w l;
plot for [i=6:45:15] 'table' using 1:i w l;
plot for [i=7:45:15] 'table' using 1:i w l;
plot for [i=8:45:15] 'table' using 1:i w l;
plot for [i=9:45:15] 'table' using 1:i w l;
plot for [i=10:45:15] 'table' using 1:i w l;
plot for [i=11:45:15] 'table' using 1:i w l;
plot for [i=12:45:15] 'table' using 1:i w l;
plot for [i=13:45:15] 'table' using 1:i w l;
plot for [i=14:45:15] 'table' using 1:i w l;
plot for [i=15:45:15] 'table' using 1:i w l;
plot for [i=16:46:15] 'table' using 1:i w l;
unset multiplot

pause -1
