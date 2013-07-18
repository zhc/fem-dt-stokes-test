#set term png size 1024, 768
#set term png size 340, 500
set term png size 400, 400
set output 'unorm-two.png'
set key on autotitle columnheader
set yrange [0:0.15]
plot for [i=2:7:1] 'temp_table' using 1:i w l
#plot 'temp_table' using 1:2 w l
#plot 'temp_table' using 1:5 w l
