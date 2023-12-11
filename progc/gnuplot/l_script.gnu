#!/usr/bin/gnuplot -persist
set title 'Top 10 of the longest routes'
set xlabel 'Route ID'
set ylabel 'Distances (km)'
set output './temp/l_image.png'
set key noenhanced

# set so it use pngcairo, with the font arial in 0.8 size
# and the image size is 1920x1080
set terminal pngcairo enhanced font "arial,20" size 1920,1080
# tell that the data separator is ; in our file
set datafile separator ';'

# to start from 0 to 2000, [0:*] is from 0 to auto
set yrange [0<*<2000:*] # [0:2000] 

# set a tick every 100 units
set ytics autofreq
# set a tick every 1 units
set xtics 1 nomirror

# linestyle for the grid
set style line 100 lc rgb "grey" lw 0.5
# enable grid with specific linestyle
set grid ls 100

# configure boxes style color and form
set style fill solid 1.0 border lt -1

# configure boxes style width
set boxwidth 0.5 relativ

# notitle remove the legend
# u is a shortcut of using
# $0 represent teh line number of the read data
# (2*$0+1) is the x position
# 1 is the y position (the data in the field 1)
# xticlabel(2) put a label on the x axis with the content in the field 2
# using boxes style and removing the legend titles
plot './temp/l_argument_top10_finish.csv' u (2*$0+1):1:xticlabel(2) with boxes notitle