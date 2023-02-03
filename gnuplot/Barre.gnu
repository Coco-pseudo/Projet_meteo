set datafile separator ";"
set xlabel 'Id station'
set ylabel 'Température/pression'
color1= "#80E0A080"


set terminal png size 1000,750 enhanced font "Helvetica,20"
set output "Barre.png"

plot 'ValeursRetours.csv' using 1:3:4 with filledcurves  fc rgb color1 title "min/max",'ValeursRetours.csv'  using 1:2 with lines  title "moyenne"


