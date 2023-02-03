

#set datafile separator ";"
set xrange [-0.2:2.2]
set yrange [-0.2:1.2]
set zeroaxis
plot "battery.dat" using 1:2:(-0.1*$1/$2):(-0.1) with vectors head filled title "coucou"
