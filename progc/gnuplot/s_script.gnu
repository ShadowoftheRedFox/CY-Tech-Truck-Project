#!/usr/bin/gnuplot -persist
set title 'Section length for each route'
set xlabel 'Route ID'
set ylabel 'Distances (km)'
set output './images/s_image.png'
set key noenhanced

# set terminal so it use pngcairo, with the font arial in 20 size
# and the image size is 1920x1080
set terminal pngcairo enhanced font "arial,20" size 1920,1080
# tell that the data separator is ; in our file
set datafile separator ';'

# to start from 0 as a minimum value, the rest is automatically calculated
# set yrange [0<*:0<*]  
# set xrange [0<*:0<*] 

# automatically set the range for every range (x and x1, same for y and y2)
# cbrnage is the color palette, rrange is to set radial range in polar mode
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

# nomirror is to prevent ticks on both sides of the graph
# set a tick on y automatically
set ytics autofreq
# set a tick on x automatically, and rotate the label by 90 degrees
set xtics autofreq nomirror rotate by 90 right

# style for the line, with color and thickness
set style line 100 lc rgb "grey" lw 0.5
# enable grid with the line style we made
set grid ls 100

# 1:2 set in x the value in the first field, and in y the value in the second field (for lines function)
# 1:3:4 is using the value in the first field as x, and fill between the y value provided by teh 3rd and 4th field (for filled curves function)
# lt -1 set the color as black, with lw 2 set the line width
# lc rgb sets a color using RGB rules 
# title set the title for the used functions (line and filled curve here)

plot './temp/s_argument_result.txt' using (2*$0+1):2:xticlabel(1) with lines lt -1 lw 2 title 'Average', \
    '' using (2*$0+1):3:4 with filledcurve lc rgb "#80FF8080" title 'Min/Max'