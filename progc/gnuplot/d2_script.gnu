#!/usr/bin/gnuplot -persist
set title 'Top 10 drivers with the most distance traveled'
set xlabel 'Distance traveled (km)'
set ylabel 'Name'
set output './temp/d2_image.png'
set key noenhanced

# set so it use pngcairo, with the font arial in 0.8 size
# and the image size is 1920x1080
set terminal pngcairo enhanced font "arial,20" size 1920,1080
# tell that the data separator is ; in our file
set datafile separator ';'

# to start from 0 to auto, [0<*:*] is from 0 minimal auto to auto
set xrange [0<*:*]

# set a tick every 1 units
set ytics 1 nomirror
set xtics autofreq nomirror

# linestyle for the grid
set style line 100 lc rgb "grey" lw 0.5
# enable grid with specific linestyle
set grid ls 100

# configure boxes style color and form
set style fill solid 1.0 border lt -1

# configure boxes style width
# set boxwidth 0.5 relativ
myBoxWidth = 0.8
myOffset = 0.5
set offsets 0,0,myOffset-myBoxWidth/2.,myOffset

# TODO add comment, and find a way to center the data
plot './temp/d2_argument_top10.csv' using (myOffset*$2):0:(myOffset*$2):(myBoxWidth/2.):($0+1):ytic(1) with boxxy lc var notitle