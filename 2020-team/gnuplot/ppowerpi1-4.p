#set datafile seperator to "," for csv files
set datafile separator ","
#filter first line for metadata
set key autotitle columnhead
#set time x line
set xdata time
set timefmt '%H:%M:%S'
#change range to used time slot
set xrange["00:00:00":"24:00:00"]
set xtics format '%H:%M:%S'
set xlabel "Time"
#set Power on y line
set ylabel "Watt"
#set png size
set terminal png size 4096,2160
#set output file
set output 'power.png'
#set title
set title 'Power pi 1 to 4'
#plot graph
plot 'raspberrypi-0.csv' using 2:6 w l t "Watt 0", 'raspberrypi-1.csv' using 2:6 w l t "Watt 1", 'raspberrypi-2.csv' u 2:6 w l t "Watt 2", 'raspberrypi-3.csv' u 2:6 w l t "Watt 3"
