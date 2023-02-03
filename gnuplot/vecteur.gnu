

set datafile separator ";"
set xlabel "longitude"
set ylabel "latitude"

set title "Graphique Vents"
set xtics rotated by 90
set ytics

set xrange [*:*]
set yrange [*:*]
set autoscale noextend
set terminal png size 1000,750 enhanced font "Helvetica,20"
set output "Vecteur.png"
plot "ValeursRetours.csv" using 2:3:4:5 with vectors arrowstyle 3 notitle 'blabla'