#set term postscript eps color
set term png size 1024, 500
set key on autotitle columnheader
#set xlabel 't'
#set ylabel 'velocity error'
#set title ''

set output 'scheme-time.png'
set multiplot layout 1,3
set title 'a)'; plot for [i=2:6] 'scheme-time' using 1:i w l;
set title 'b)'; plot for [i=7:11] 'scheme-time' using 1:i w l;
set title 'c)'; plot for [i=12:16] 'scheme-time' using 1:i w l;
unset multiplot
