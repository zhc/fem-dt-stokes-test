#set term postscript eps color
set term png size 1024, 500
#set term png size 3024, 1024
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

set output 'scheme-time.png'
set multiplot layout 1,3
plot for [i=2:7] 'scheme-time' using 1:i w l;
plot for [i=8:13] 'scheme-time' using 1:i w l;
plot for [i=14:19] 'scheme-time' using 1:i w l;
unset multiplot
