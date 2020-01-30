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
#set Current on y line
set ylabel "Amps/Voltage/Watts"
#set temperature on second y line
set y2tics 
set y2tics nomirror
set y2range["0":"100"] 
set y2label "Celsius"
#set png size
set terminal png size 4096,2160
#set output file
set output 'pi1.png'
#set title
set title 'Data pi 1'
#plot graph
plot 'raspberrypi-1.csv' using 2:4 w l t "Amp", 'raspberrypi-1.csv' using 2:5 w l t "Voltage", 'raspberrypi-1.csv' u 2:6 w l t "Watts", 'raspberrypi-1.csv' u 2:7 w l t "Celcius"
