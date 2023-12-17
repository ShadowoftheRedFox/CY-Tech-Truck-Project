#!/usr/bin/gnuplot -persist
# set title, x and y labels and output
set title 'Top 10 drivers with the most distance traveled'
set xlabel 'Distance traveled (km)'
set ylabel 'Name'
set output './images/d2_image.png'
set key noenhanced

# set terminal so it use pngcairo, with the font arial in 0.8 size
# and the image size is 1920x1080
set terminal pngcairo enhanced font "arial,20" size 1920,1080
# tell that the data separator is ; in our file
set datafile separator ';'

# to start from 0 to auto, [0<*:*] is from 0 minimal auto to auto
set xrange [0<*:*]

# nomirror is to prevent ticks on both sides of the graph
# set a tick on y every 1 units
set ytics 1 nomirror
# set a tick on x automatically
set xtics autofreq nomirror

# style for the line, with color and thickness
set style line 100 lc rgb "grey" lw 0.5
# enable grid with the line style we made
set grid ls 100

# configure boxes style color, width and border
set style fill solid 1.0 border lt -1

# variable to configure boxes style width
myBoxWidth = 0.8
# variable to configure boxes offset
myOffset = 0.5
# set the offset
set offsets 0,0,myOffset-myBoxWidth/2.,myOffset

# plot data horizontally using boxxy
# we draw rectangle shap at given coordinates: 0 in X, offset times the line read, to same line in X to offset upward for width, the length of the data value
# lc var set automatically the color, notitle hide the different color title
plot './temp/d2_argument_top10.csv' using (myOffset*$2):0:(myOffset*$2):(myBoxWidth/2.):($0+1):ytic(1) with boxxy lc var notitle