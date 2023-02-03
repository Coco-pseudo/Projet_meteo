

set datafile separator ";"
set xlabel "longitude"
set ylabel "latitude"

set title "Graphique Vents"
set xtics rotated by 90
set ytics

set xrange [*:*]
set yrange [*:*]
set autoscale noextend
plot "ValeursRetours.csv" using 2:3:4:5 with vectors arrowstyle 3 notitle 'blabla'