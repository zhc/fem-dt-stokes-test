#set term postscript eps color
set term png size 1600, 900
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

set yrange [0:0.1]

#plot 'table' u 1:38 w l, \
#	 'table' u 1:39 w l, \
#	 'table' u 1:40 w l;

set multiplot layout 3,3
plot for [i=2:14:3] 'table' using 1:i w l;
plot for [i=3:15:3] 'table' using 1:i w l;
plot for [i=4:16:3] 'table' using 1:i w l;

plot for [i=17:29:3] 'table' using 1:i w l;
plot for [i=18:30:3] 'table' using 1:i w l;
plot for [i=19:31:3] 'table' using 1:i w l;

plot for [i=32:44:3] 'table' using 1:i w l;
plot for [i=33:45:3] 'table' using 1:i w l;
plot for [i=34:46:3] 'table' using 1:i w l;

unset multiplot

pause -1
