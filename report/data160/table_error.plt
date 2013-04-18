#set term postscript eps color
set term png size 1024, 500
set key on autotitle columnheader
#set ylabel "{/Symbol e}"
#set xlabel 'time layer'
set yrange [0:0.1]
#set title 'ololo' offset 0, -1;
set output 'error_1.png'
set multiplot layout 1,3
set title 'a)'; plot for [i=2:14:3] 'table_error' using 1:i w l;
set title 'b)'; plot for [i=3:15:3] 'table_error' using 1:i w l;
set title 'c)'; plot for [i=4:16:3] 'table_error' using 1:i w l;
unset multiplot

set output 'error_2.png'
set multiplot layout 1,3
set title 'a)'; plot for [i=17:29:3] 'table_error' using 1:i w l;
set title 'b)'; plot for [i=18:30:3] 'table_error' using 1:i w l;
set title 'c)'; plot for [i=19:31:3] 'table_error' using 1:i w l;
unset multiplot

set output 'error_3.png'
set multiplot layout 1,3
set title 'a)'; plot for [i=32:44:3] 'table_error' using 1:i w l;
set title 'b)'; plot for [i=33:45:3] 'table_error' using 1:i w l;
set title 'c)'; plot for [i=34:46:3] 'table_error' using 1:i w l;
unset multiplot

set output 'error_4.png'
set multiplot layout 1,3
set title 'a)'; plot for [i=47:59:3] 'table_error' using 1:i w l;
set title 'b)'; plot for [i=48:60:3] 'table_error' using 1:i w l;
set title 'c)'; plot for [i=49:61:3] 'table_error' using 1:i w l;
unset multiplot

